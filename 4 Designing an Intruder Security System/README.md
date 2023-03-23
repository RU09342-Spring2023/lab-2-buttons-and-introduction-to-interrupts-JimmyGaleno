# Part 4: Occupancy Detection and Alert System
You are being asked to design a rudimentary occupancy alert system with the following behavior:
- The system when turned on needs to blink the Green LED once every 3 seconds to show it is armed.
- When the occupancy sensor detects someone, it will output a Logic 1, and your system needs to move into a "Warning" state, where the Green LED stops blinking, and the Red LED Blinks once per second (500ms on, 500ms off).
- If the occupancy detector still shows someone there after 10 seconds, your system should indicate this with the RED Led constantly staying on, and move into the ALERT state.
- If the occupancy detector **before** the 15 seconds goes back to a 0, indicating the room is now empty, then the system should go back to the armed state.
- When in the ALERT State, the only way for the system to go back to the Armed state is to press the P4.1 Button.

## Occupancy Sensor
You will be **first** *emulating* the Occupancy Sensor with the P4.1 button. This can be used for pretty much all of your testing and design.

When you have a design that is working, you can then test your code with a [Passive Infrared Occupancy Detector](https://www.amazon.com/DIYmall-HC-SR501-Motion-Infrared-Arduino/dp/B012ZZ4LPM)

## Getting Started
I highly recommend on paper or a whiteboard drawing up a state machine or something to help understand the flow of the system.

From there, you should work on each stage/state and see if the transitions work. For example, can you get the system to go from the armed state to the warning state.

Remember that your code is going to be running in a loop, so you need to make sure you consider how this is going to work when trying to blink the LEDs.

## Do I need to use Interrupts?
Well, it would be cool, but at the end of the day, we are asking you for a design. Start with polling or what you feel comfortable with, but we would like you to try out using the interrupts, maybe at least for the system Disarm Button.

## Navigating multiple states
One way to approach a system with multiple states is to actually use a case statement in your main loop. For example:
```c
#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2

// Put some initialization here

char state = ARMED_STATE;

while(1)
{
  switch (state) {
    case ARMED_STATE:
    {
      // Do something in the ARMED state
      // If something happens, you can move into the WARNING_STATE
      // state = WARNING_STATE
    }
    case WARNING_STATE:
    {
      // Do something in the WARNING_STATE
    }
  }
}
```

## Submission
This code is designed after an occupancy alert system, which uses two buttons and a red and green LED. To start, the green LED on the board blinks every 3 seconds to signify that the system is indeed armed. When the sensor “detects” someone, the green LED then turns off and the red LED blinks every second. If the sensor still “detects” someone after 10 seconds, the system then makes the red LED stop blinking and instead makes it stay constant. Now, if the room is empty before 15 seconds, the system automatically goes back to the armed state which blinks the green LED every 3 seconds. In the code, the P4.1 button acts as the person being detected by the system. For this code, a switch statement is used to switch through all of the different cases when each behavior is performed. There are 3 cases that are used, alert, warning, and alert. These cases switch between each other based on the inputs of buttons P4.1 and P2.3.  
