
/*
Arduino Sketch (Program) to contol servo motors driving a micro-robot
J.F. Briere and J. Trudeau 
Latest version October 3, 2018
*/

#include <Servo.h>// Library that loads commands to servo objects

Servo leftDrive;  // create servo object for the left wheel
Servo rightDrive; // another servo object for the right wheel

int pos = 0;    // variable to store the servo position

void setup()
{
  leftDrive.attach(9);  // attaches the servo on pin 9 
  rightDrive.attach(10);  // attaches the servo on pin 10
  
}

//example routine, drives in a circle or forward

void loop()
{

dontMove(1000); 
turnRight(1000);

}


/*the following functions are examples that can be tweaked to make the robot move
on curved paths or at varying speeds by changing the numbers associated with the servo objects. 
0 is full power continuous counterclockwise (CCW) rotation that reduces power in the range up to 90
90 is full stop 
180 is full power clockwise (CW) rotation that reduces power in the range down to 90.

NOTE: Depending on how you have connected your servos forward motion of the wheels may 
correspond to CW or CCW rotation. 
For example, for foward motion the right wheel may rotate CW and the left wheel CCW.
*/

//turns right for t  milliseconds by reducing power to the right wheel moving 
void turnRight(int t)
{
  leftDrive.write(0);
  rightDrive.write(110);
  delay(t); 
}


//stops moving for t milliseconds
void dontMove(int t)
{
  leftDrive.write(90);
  rightDrive.write(90);
  delay(t);
}

//end.

