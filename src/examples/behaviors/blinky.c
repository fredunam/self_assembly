#include <kilolib.h>

#define STOP 0
#define FORWARD 1
#define LEFT 2
#define RIGHT 3

int current_motion = STOP;

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
    // Put any setup code here. This is run once before entering the loop.
}

void loop()
{
    // Put the main code here. This is run repeatedly.
    
    // Set the LED red.
    set_color(RGB(1, 0, 0));
    // Wait half a second (500 ms).
    delay(500);
//    // Set the LED blue.
//    set_color(RGB(0, 0, 1));
//    // Wait half a second (500 ms).
//    delay(500);
//    // No LED.
//    set_color(RGB(0, 0, 0));
//    // Wait half a second (500 ms).
//    delay(2000);
//    // Set the LED green.
//    set_color(RGB(0, 1, 0));
//    // Wait half a second (500 ms).
//    delay(1000);


    set_motors(kilo_turn_left, 0);
    delay(2000);
    set_motion(FORWARD);
    delay(2000);
//    set_motion(FORWARD);
//    delay(2000);
//    set_motors(kilo_turn_left, 0);
//    delay(2000);
//    set_motion(FORWARD);
//    delay(2000);
//    set_motors(kilo_turn_left, 0);
//    delay(2000);
//    set_motion(FORWARD);
//    delay(2000);
//    set_motors(kilo_turn_left, 0);
//    delay(2000);
    set_motion(STOP);
    delay(5000);
}

int main()
{
    // Initialize the hardware.
    kilo_init();
    // Register the program.
    kilo_start(setup, loop);
    
    return 0;
}
