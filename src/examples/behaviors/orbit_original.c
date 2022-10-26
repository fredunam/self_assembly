#include <kilolib.h>
#include "stdlib.h"

// Constants for orbit control.
#define TOO_CLOSE_DISTANCE 75
#define DESIRED_DISTANCE 90

// Constants for motion handling function.
#define STOP 0
#define FORWARD 1
#define LEFT 2
#define RIGHT 3

int current_motion = STOP;
int distance;
int new_message = 0;

// Function to handle motion.
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

void setup()
{
}

void loop()
{
    // Update the motion whenever a message is received.
    if (new_message == 1)
    {
        new_message = 0;

        // If too close, move forward to get back into orbit.
        if (distance < TOO_CLOSE_DISTANCE)
        {
            set_color(RGB(0, 1, 0));
            set_motion(FORWARD);
            printf("< TOO CLOSE -> Forward\n");
        }
            // If not too close, turn left or right depending on distance,
            // to maintain orbit.
        else
        {
            if (distance < DESIRED_DISTANCE)
            {
                set_color(RGB(1, 0, 0));
                set_motion(LEFT);
            printf("< DESIRED_DISTANCE -> Left\n");
            }
            else
            {
                set_color(RGB(0, 0, 1));
                set_motion(RIGHT);
                printf("> DESIRED_DISTANCE -> Right\n");
            }
        }
    }
}

void message_rx(message_t *m, distance_measurement_t *d)
{
    new_message = 1;
    distance = estimate_distance(d);
}

int main()
{
    kilo_init();
    kilo_message_rx = message_rx;
    kilo_start(setup, loop);

    return 0;
}