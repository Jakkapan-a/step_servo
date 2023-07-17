#include <Servo.h>
// Sensor input
const int SENSOR_1 = 6; // 
const int SENSOR_2 = 7; //

// Servo output
const int SERVO_PIN = 3;

// LED output
const int LED_1 = 4;
const int LED_2 = 5; 

// STATE of the system
enum STATE : int {
  STATE_1,
  STATE_2,
  STATE_3
};

volatile STATE currentState;

// Servo positions
const int POS_1 = 0;
const int POS_2 = 90;
const int POS_3 = 180;

Servo MyServo;
void setup() {
  Serial.begin(9600);
  // Default state
  currentState = STATE_3; 

  // INPUT
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  // OUTPUT
  pinMode(LED_1, OUTPUT); 
  pinMode(LED_2, OUTPUT);
  
  MyServo.attach(SERVO_PIN);
  MyServo.write(POS_1);
}

void loop() { 

  int sensor1_state = digitalRead(SENSOR_1);
  int sensor2_state = digitalRead(SENSOR_2);
  
  /* --------------------------------------------------------------------
  // Check the state of the sensors and set the state
  // --------------------------------------------------------------------*/
  if(sensor1_state == LOW && sensor2_state == LOW){
    // Condition 1
    currentState = STATE_1;
  }else if(sensor1_state == LOW && sensor2_state == HIGH){
    // Condition 2
    currentState = STATE_2;
  }else{
    // Condition none
    currentState = STATE_3;
  }
  /* --------------------------------------------------------------------
  // Set the servo and LEDs
  // --------------------------------------------------------------------*/
  setServo(currentState);
  setLEDs(currentState);
  delay(200);
}

void setServo(STATE state){
  if(state == STATE_1){
    MyServo.write(POS_1);
  }else if(state == STATE_2){
    MyServo.write(POS_2);
  }else if(state == STATE_3){
    MyServo.write(POS_3);
  }
}

void setLEDs(STATE state){
  /* --------------------------------------------------------------------
  // Set the LEDs
  // --------------------------------------------------------------------*/
  if(state == STATE_1){
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
  }else if(state == STATE_2){
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
  }else if(state == STATE_3){
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
  }
}
