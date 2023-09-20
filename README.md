# On-demand Traffic light control
The system aims to provide an on-demand traffic control system. It includes a pedestrian button to allow for pedestrians to pass.

    the project implement simple operating system using scheduler to decide the next state.

    the main idea is that it make small delay in every state called then retrun to the scheduler to catch if there is any change happening in the program if no return to the state until time out.  
![simulation](images&videos/simulation.gif)
## State machine: 
<!-- <h1 align="center">state machine</h1> -->

![state machine](images&videos/state_machine.png)

## Software requirements: 
#### In normal mode:

* Cars' LEDs will be changed every five seconds starting from Green then yellow then red then yellow then Green.

- The Yellow LED will blink for five seconds before moving to Green or Red LEDs.

### In pedestrian mode:

- Change from normal mode to pedestrian mode when the pedestrian button is pressed.

- If pressed when the cars' Red LED is on, the pedestrian's Green LED and the cars' Red LEDs will be on for five seconds, this means that pedestrians can cross the street while the pedestrian's Green LED is on.

- If pressed when the cars' Green LED is on or the cars' Yellow LED is blinking, the pedestrian Red LED will be on then both Yellow LEDs start to blink for five seconds, then the cars' Red LED and pedestrian Green LEDs are on for five seconds, this means that pedestrian must wait until the Green LED is on.

- At the end of the two states, the cars' Red LED will be off and both Yellow LEDs start blinking for 5 seconds and the pedestrian's Green LED is still on.

- After the five seconds the pedestrian Green LED will be off and both the pedestrian Red LED and the cars' Green LED will be on.
Traffic lights signals are going to the normal mode again.

## Hardware requirements:

* ATmega32 microcontroller.
* One push button connected to INT0 pin for pedestrian.
* Three LEDs for cars - Green, Yellow, and Red, connected on port A, pins 0, 1, and 2
* Three LEDs for pedestrians - Green, Yellow, and Red, connected on port B, pins 0, 1, and 2

