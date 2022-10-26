#include <kilolib.h>
#include "stdlib.h"

#define TOO_CLOSE_DISTANCE 50
#define DESIRED_DISTANCE 65
#define EPSILON_MARGIN 5
#define MOTOR_ON_DURATION 100
#define NUMBER_COMMUNICATION 3

#define FORWARD 0
#define LEFT 1
#define RIGHT 2
#define STOP 3


#define NEIGHBOURS_IN_RANGE 1
#define COMPARE_DESIRED_DISTANCE 2
#define ORBIT_AND_UPDATE_INDEX 3
#define FINISH 4
#define INFINITY 5

message_t message;
int state, message_rx_status, index=3, check=0, x, y, max_index=2, message_sent;
float distance, last_distance, min_distance, temp;

int current_motion = STOP;
int new_message = 0;
int reception_id[3] = {0,0,0};
float reception_distance[3]={0,0,0};

int neighbours[8][2] = {
        {0 ,0} ,
        {0 ,0} ,
        {0 ,0} ,
        {1 ,2} ,
        {2 ,3} ,
        {3 ,4} ,
        {4 ,5} ,
        {5 ,6}
        };

float distance_multiplier[8][2] = {
        {0,0},
        {0,0},
        {0,0},
        {1,1},
        {1,1.4},
        {1,1},
        {1 ,1.4} ,
        {1 ,1}
        };

message_t *message_tx(){
    return &message;
}

void message_tx_success(){
    message_sent = 1;
    set_color(RGB(1,0,1));
    delay(100);
    set_color(RGB(0,0,0));
}

void message_rx(message_t *m, distance_measurement_t *d){
    new_message = 1;
    // Kilobot no longer receives a message
    if(message_rx_status == 0){
        distance = 1000;
    }
    if(message_rx_status != NUMBER_COMMUNICATION){
        printf("message_rx_status : %d | NUMBER_COMMUNICATION: %d\n", message_rx_status, NUMBER_COMMUNICATION);
        temp = estimate_distance(d);
        if(temp < distance){
            distance = temp;
            printf("distance: %d\n", distance);
        }
        reception_id[message_rx_status] =(*m).data[0];
        if(reception_id[message_rx_status] > max_index){
            max_index = reception_id[message_rx_status];
        }
        reception_distance[message_rx_status] = temp;
        message_rx_status++;
    }
}

void measure_distance(){
    message_rx_status = 0;
}

void set_motion(int new_motion)
{
    // Only take an action if the motion is being changed.
    if (current_motion != new_motion)
    {
        current_motion = new_motion;

        if (current_motion == STOP)
        {
            set_motors(0, 0);
        }
        else if (current_motion == FORWARD)
        {
            spinup_motors();
            set_motors(kilo_straight_left, kilo_straight_right);
        }
        else if (current_motion == LEFT)
        {
            spinup_motors();
            set_motors(kilo_turn_left, 0);
        }
        else if (current_motion == RIGHT)
        {
            spinup_motors();
            set_motors(0, kilo_turn_right);
        }
    }
}

//void move(int direction){
//    switch (direction) {
//        case FORWARD:
//            spinup_motors();
//            set_motors(kilo_straight_left, kilo_straight_right);
//            delay(MOTOR_ON_DURATION);
//            set_motors(0,0);
//            break;
//        case LEFT:
//            spinup_motors();
//            set_motors(kilo_straight_left, 0);
//            delay(MOTOR_ON_DURATION);
//            set_motors(0,0);
//            break;
//        case RIGHT:
//            spinup_motors();
//            set_motors(0, kilo_straight_right);
//            delay(MOTOR_ON_DURATION);
//            set_motors(0,0);
//            break;
//        default:
//            break;
//    }
//}

void setup(){
    state = NEIGHBOURS_IN_RANGE;
    set_color(RGB(0,0,1));
}

void loop(){
    if(new_message == 1){
        new_message = 0;
        switch (state) {
            case NEIGHBOURS_IN_RANGE:
                printf("NEIGHBOURS_IN_RANGE\n");
                state = COMPARE_DESIRED_DISTANCE;
                message_rx_status = 0;
                break;
            case COMPARE_DESIRED_DISTANCE:
                printf("COMPARE_DESIRED_RANGE\n");
                if (message_rx_status == NUMBER_COMMUNICATION) {
                    for (int i = 0; i < NUMBER_COMMUNICATION; ++i) {
                        for (int j = i + 1; j < NUMBER_COMMUNICATION; j++) {
                            if (reception_id[i] == neighbours[index][0] && reception_id[j] == neighbours[index][1]) {
                                x = i;
                                y = j;
                                check = 1;
                                break;
                            }
                        }
                        if (check == 1) {
                            break;
                        }
                    }
                    if ((check == 1) && (reception_distance[x] >
                                         distance_multiplier[index][0] * DESIRED_DISTANCE
                                         - EPSILON_MARGIN && reception_distance[x] <
                                                             distance_multiplier[index][0] * DESIRED_DISTANCE +
                                                             EPSILON_MARGIN) &&
                        (reception_distance[y] > distance_multiplier[index][1] * DESIRED_DISTANCE - EPSILON_MARGIN &&
                         reception_distance[y] < distance_multiplier[index][1] * DESIRED_DISTANCE + EPSILON_MARGIN)) {
                        state = FINISH;
                    } else {
                        state = ORBIT_AND_UPDATE_INDEX;
                    }
                }
                break;
            case ORBIT_AND_UPDATE_INDEX:
                printf("ORBIT_AND_UPDATE_INDEX\n");
                if(distance < TOO_CLOSE_DISTANCE){
                    set_motion(FORWARD);
                    printf("< TOO_CLOSE -< Forward\n");
                } else if (distance > DESIRED_DISTANCE) {
                    printf("distance > DESIRED_DISTANCE -> Right\n");
                    set_color(RGB(1, 0, 0));
                    set_motion(RIGHT);
                    state = NEIGHBOURS_IN_RANGE;
                } else {
                    printf("distance < DESIRED_DISTANCE -> Left\n");
                    set_color(RGB(0, 0, 1));
                    set_motion(LEFT);
                    state = NEIGHBOURS_IN_RANGE;
                }
                if (max_index + 1 > index) {
                    index = max_index + 1;
                }
                break;
            case FINISH:
                printf("FINISH\n");
                set_color(RGB(0, 1, 0));
                message.type = NORMAL;
                message.data[0] = index;
                message.crc = message_crc(&message);
                kilo_message_tx = message_tx;
                kilo_message_tx_success = message_tx_success;
                state = INFINITY;
                break;
            case INFINITY:
                printf("INFINITY\n");
                break;
            default:
                break;
        }


    }

}

int main(){
    kilo_init();
    kilo_message_rx = message_rx;
    kilo_start(setup, loop);
    return 0;
}

