#include <arduino_code\libraries\motor_control\motor_control.h>
#include <arduino_code\libraries\HC_SR04\HC_SR04.h>
#include <arduino_code\libraries\SODAR\SODAR.h>
#include <arduino_code\libraries\PID\PID_v1.h>
#include <arduino_code\libraries\MPU6050\MPU6050.h>

 

// Servo Pin declaration
#define SERVO_PIN 9  //servo connect to D9

 

//Ultrasonic distance sensor pin declaration
#define TRIG_PIN 10
#define ECHO_PIN 2
#define ECHO_INT 0
#define CENTER 91
#define RESOLUTION 45
#define UPPER_RANGE 136
#define LOWER_RANGE 46

 

//Global Variable
SODAR group7Sodar(TRIG_PIN, ECHO_PIN, ECHO_INT, SERVO_PIN, 91, RESOLUTION, UPPER_RANGE, LOWER_RANGE);

 

//Define Variables we'll be connecting to
double input, output;
double setpoint=0;
int power = 120;//power to the robot
//i found that it worked best at 120. 150 was a little too fast for the distance sensor to pick what it needed to up on all sides

 

//Specify the links and initial tuning parameters
double kp=2, ki=0, kd=0;
PID straight(&input, &output, &setpoint, kp, ki, kd, DIRECT);

 

//IMU initailize
MPU6050 IMU(4, 5);

 


//int rwc = 150;
int turnTime = 5;

 

void setup()
{
  motor_setup();//setup motor pins
  IMU.initialize();//initialize MPU6050 sensor
  delay(500); //Add delay so finger press on reset button does not mess up calibration
  IMU.calibrate();  //calibrate the sensor(robot cannot move during this time)
  straight.SetMode(1);
  straight.SetOutputLimits(-150, 150);
  straight.SetSampleTime(50);
  Serial.begin(9600);

 

 

//  mysodar.init();

 

  pinMode(SERVO_PIN, OUTPUT);
  
  group7Sodar.initialize_arrays();
  group7Sodar.init();

 

}

 

void loop()
{
 IMU.update();
  //compute
  straight.Compute();
  input = IMU.get_ang_vel('z');
  raw_motor_control(power-output, power+output); //Need to make schema of robot for this
  
group7Sodar.update();
if (group7Sodar.distance[1] <= 10 ) {
    backward(0);
    backward(255);
    delay(10);
  }
else if (group7Sodar.distance[1] <= 50 ) {
    obstacle_detection();
  }
}

 


void obstacle_detection(){ 
dwell();
group7Sodar.update();
int arr0 = group7Sodar.distance[0];
int arr2 = group7Sodar.distance[2];
if (arr0 > arr2){
  raw_motor_control(200, -100);
  delay(turnTime);
  raw_motor_control(power-output, power+output);
}

 

else if (arr2 > arr0){
   raw_motor_control(-100, 200);
  delay(turnTime);
  raw_motor_control(power-output, power+output);
}

 

else if (arr2 == arr0){
  raw_motor_control(-100, -100);
  delay(500);
  dwell();
}
   

 


}