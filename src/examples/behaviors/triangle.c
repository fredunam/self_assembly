#include <kilolib.h>
#include <stdlib.h>
#include <stdio.h>

#define PERFECT_DISTANCE 99

#define STOP 0
#define FORWARD 1
#define LEFT 2
#define RIGHT 3

int new_message;
int distance, speaker_index, nbBots = 0, state, temp_distance[2], threshold = 2, rand_move;

int current_motion = STOP;
int inComm = 0;

void set_motion(int new_motion) {
    // Only take an action if the motion is being changed.
    if (current_motion != new_motion) {
        current_motion = new_motion;

        if (current_motion == STOP) {
            set_motors(0, 0);
        } else if (current_motion == FORWARD) {
            spinup_motors();
            set_motors(kilo_straight_left, kilo_straight_right);
        } else if (current_motion == LEFT) {
            spinup_motors();
            set_motors(kilo_turn_left, 0);
        } else if (current_motion == RIGHT) {
            spinup_motors();
            set_motors(0, kilo_turn_right);
        }
    }
}

void setup() {

}

void loop() {
    if (new_message == 1) {
        new_message = 0;
        inComm = 1;
        printf("(loop - new_mess == 1) kilo_ticks : %d\n", kilo_ticks);
        printf("(loop) dist 1 = %d, dist 2 = %d\n", temp_distance[0], temp_distance[1]);
        if (temp_distance[0] < temp_distance[1] &&
                abs(temp_distance[0] - temp_distance[1]) > threshold) {
            printf("(loop) d1 < d2 - Left\n");
            set_motion(LEFT);
            //delay(30);
            set_motion(FORWARD);
            //delay(50);
        } else if (temp_distance[0] > temp_distance[1] &&
                   abs(temp_distance[0] - temp_distance[1]) > threshold) {
            printf("(loop) d1 > d2 - Right\n");
            set_motion(RIGHT);
            //delay(30);
            set_motion(FORWARD);
            //delay(50);
        } else if (temp_distance[0] == temp_distance[1] &&
                   (temp_distance[0] != PERFECT_DISTANCE && temp_distance[1] != PERFECT_DISTANCE)) {
            printf("(loop) continue d'avancer\n");
            set_motion(LEFT);
            set_motion(RIGHT);
        } else {
            printf("(loop) d1 == d2 - Stop\n");

            set_motion(STOP);
        }

    } else if (inComm == 0){
        //random movement
        rand_move = rand()%3;
        printf("(loop) kilo_ticks : %d\n", kilo_ticks);
        printf("(loop) rand_move = %d\n", rand_move);
        switch (rand_move) {
            case 0:
                set_motion(LEFT);
                break;
            case 1:
                set_motion(RIGHT);
                break;
            case 2:
                set_motion(FORWARD);
        }
    }

}

void message_rx(message_t *m, distance_measurement_t *d) {
    new_message = 1;
    printf("(message_rx) kb%d a reçu un nouveau message lors du %d ticks\n", kilo_uid, kilo_ticks);
    printf("(message_rx) kb%d a envoyé un message\n", speaker_index);

    speaker_index = (*m).data[0];
    temp_distance[speaker_index - 1] = estimate_distance(d);
    printf("dist 1 = %d\n", temp_distance[speaker_index - 1]);

    printf("(message_rx) message envoyé par kb%d : distance = %d\n", speaker_index, temp_distance[speaker_index - 1]);
    if (nbBots < speaker_index) {
        nbBots = speaker_index;
    }
    printf("(message_rx) nbBots in range : %d\n", nbBots);

}

int main() {
    kilo_init();

    kilo_message_rx = message_rx;
    kilo_start(setup, loop);

    return 0;
}
