# Target Game
* Summary: a simple target game when the random plate is chosen to stand up, the player needs to use the pointer place to point at the center of the plate to put it down. Everytime the player shoots down a target, he/she will earn a point. The game will be on for 10 seconds, if the player can earn more than 3 points during the given time, a sound of winning game will be toggled, if not there will be a different sound which noted timeout but the player is not a winner.
* Requirement/goal:  basic functions are  a random plate is chosen to stand up, putting the plates down when receiving signal from the laser, showing scores to the player, the game is only running in the given period of time, and the start/reset buttons to control the game, a different sound for win/lose game.

## System Design
### Block Diagram:

### Flowchart: tasks diagram
* Target task:

* Score display task

## Implement Details
### Hardware design: circuit picture

### Schematics:

## Testing/Evaluation:
### Testing environment:
> All the required components are set up based on the design circuit and schematics.
> Mac/laptop to power up the microcontroller.
> An arduino and a K64F microcontroller are both implemented in the designed software with all the functions needed for the system to work.
Run the test by actual actions on the designed system.
### Required equipments:
- Aduino microcontroller
- K64f microcontroller
- Photoresistors
- Buttons
- 7 segment display
- Buzzer/speaker
- Servo motors
- A shift register 74HC595IC
- 220ohm resistors
- Wires
- Breadboards
- Pointer laser
### Test case scenarios
* Case 1:
  > Start the game, and observe if the game stops after 10second, there should be a sound at the end when the game stops, then reset the game.
* Case 2:
  > Try to earn more than 3 points to check the sound of the winning.
* Case 3:
  > Try to earn 3 points or less for checking the sound of failing.
* Case 3:
  > Reset the game before the time is out, the game should be reset.
* Case 4:
  > Press the start button during the game
## Discussion
### Challenge & Limitaions:
> When pressing the reset button during the game, even though the game is reset on the Arduino, the timer function is still running in the backgound until done. Then, K65f will still send the signal to the Arduino indicating the time out and it will bring its state to the End start, which will toggle the sound on the speaker. Thus, we should only reset the game when the time is out or it is in End state.

> When the sound is playing, the Arduino will only read the reset button when the sound is finished at each period, so it causes the Reset button to be detected only on the certain edge.

> One of the photoresistor is broken, so it not always work as expected, so some time it hard to test the system work in certain scenario (such as trying to earn more than 3 points to check the winning sound)
### Possible improvement:
Instead of using the Arduino to control the speaker, we can switch it to K64F, and use the Interrupt function to detect the input into the Reset button at fixed frequency, thus we can avoid the deployment of detecting the Reset button while the music is playing. 
Need to figure it out how to stop and reset the delayby1ms(), when the Reset button is pressed during the game (while timer is still running)
## Roles and Responsibilities
  I work on this project on my own. All the work and code is produced by me. Some of the code is my previous work from CS120B, and I also made use of some lecture codes. I made some modifications on them in order to meet some new features. I also had some advice and help from the TA and professor.
## Conclusion
  I successfully implemented and got the system to work for its basic function. I have tested the system on different scenarios in order  to check if it works properly. Thus, there are some limitations which need to be improved to help the system work more sufficiently.

### Demo link: https://www.youtube.com/watch?v=_MSbQoYgQDY

