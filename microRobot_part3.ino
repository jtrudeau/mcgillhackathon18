
/*
Arduino Sketch (Program) to contol servo motors driving a micro-robot and perform a Random walk
Latest version October 30, 2018

Based on https://github.com/jingnanshi/RandomWalk-arduino
*/

#include <Servo.h>// Library that loads commands to servo objects
#include <math.h>  // for the absolute value function

// Ultrasonic sensor
long duration;
int distance;
int trigPin = 3;
int echoPin = 4;  

int pos = 0;    // variable to store the servo position

Servo leftDrive;  // create servo object for the left wheel
Servo rightDrive; // another servo object for the right wheel

int pos = 0;    // variable to store the servo position
const int BOUNDARY = 520;
const int TURN_POWER = TURN_POWER;
const int FORWARD_DELAY = 20;

const int random_forward_degree = 10;
const int delay_per_degree = 20;

const int random_turn_base = 120;
const int random_turn_ceiling = 240;

void setup()
{
  leftDrive.attach(9);  // attaches the servo on pin 9 
  rightDrive.attach(10);  // attaches the servo on pin 10
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  dontMove(5000);
}

//random walk routine 

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.print("Distance: ");  
  Serial.println(distance); // open serial monitor to see data output
  
  // see if the robot is about to hit a wall. set boundary as necessary
  if (distance > BOUNDARY){ 
    halt();
    // randomly turn
    randomTurn();
  } else {
    // randomly move forward
    randomForward();
  }

}

// choose a random angle to turn

void randomTurn(){
  // turn left or right random number
  long randNumber1 = random(1,10);
  // turning degree random number
  long randNumber2 = random(random_turn_base,random_turn_ceiling);
  int turn_time  = (int) randNumber2 * delay_per_degree;

  // turn right
  if (randNumber1 >= 5){
    
    turnRight(TURN_POWER);
    delay(turn_time);
    halt();
  }
  // turn left
  else{
    turnLeft(TURN_POWER);
    delay(turn_time);
    halt();
  }
}

/* randomForward(): randomly choose an angle and move forward
*
*/

void randomForward(){
  long rand_turn = random(random_forward_degree);
  long rand_dir = random(1,10);

  if (rand_dir > 5){

    turnRight(TURN_POWER);
    delay(rand_turn * delay_per_degree);

  } else {
    turnLeft(TURN_POWER);
    delay(rand_turn * delay_per_degree);

  }
  driveForward(TURN_POWER);
  dontMove(20); 
  
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


//drives straight forward for t milliseconds
void driveForward(int t)
{
  leftDrive.write(0);
  rightDrive.write(180);
  delay(t); 
}

//turns right for t  milliseconds by reducing power to the right wheel moving 
void turnRight(int t)
{
  leftDrive.write(0);
  rightDrive.write(110);
  delay(t); 
}

//turns left for t  milliseconds by reducing power to the left wheel moving 
void turnLeft(int t)
{
  leftDrive.write(20);
  rightDrive.write(180);
  delay(t); 
}

//stops moving for t milliseconds
void dontMove(int t)
{
  leftDrive.write(90);
  rightDrive.write(90);
  delay(t);
}

//drives straight backward full power for t milliseconds
void driveBackward(int t)
{
  leftDrive.write(180);
  rightDrive.write(0);
  delay(t); 
}

//end.

