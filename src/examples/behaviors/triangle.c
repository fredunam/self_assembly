#include <kilolib.h>
#include <stdlib.h>
#include <stdio.h>

#define PERFECT_DISTANCE 90

#define STOP 0
#define FORWARD 1
#define LEFT 2
#define RIGHT 3

int new_message;
int distance, speaker_index, nbBots=0, state, temp_distance[2];

int current_motion = STOP;

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
          printf("(loop) dist 1 = %d, dist 2 = %d\n", temp_distance[0], temp_distance[1]);
        if(temp_distance[0] < temp_distance[1]){
              printf("(loop) d0 < d1 - Left\n");
            set_motion(LEFT);
            delay(500);
            set_motion(FORWARD);
            delay(500);
        } else if (temp_distance[0] > temp_distance[1]){
              printf("(loop) d0 > d1 - Right\n");
            set_motion(RIGHT);
            delay(500);
            set_motion(FORWARD);
            delay(500);
        } else {
              printf("(loop) d0 == d1 - Stop\n");
            set_motion(STOP);
        }

    }

}

void message_rx(message_t *m, distance_measurement_t *d) {
    new_message = 1;
      printf("(message_rx) kb%d a reçu un nouveau message lors du %d ticks\n", kilo_uid, kilo_ticks);
      printf("(message_rx) kb%d a envoyé un message\n", speaker_index);

    speaker_index = (*m).data[0];
    temp_distance[speaker_index-1] = estimate_distance(d);
      printf("dist 1 = %d\n", temp_distance[speaker_index-1]);

      printf("(message_rx) message envoyé par kb%d : distance = %d\n", speaker_index, temp_distance[speaker_index-1]);
    if(nbBots < speaker_index){
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
