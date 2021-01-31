#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_2KHZ);
AF_DCMotor motor2(2, MOTOR12_2KHZ);

int ir_sensor = A3;

void setup() {
    Serial.begin(9600);
    Serial.println("Motor Started!");
    
    motor1.setSpeed(250);
    motor1.run(RELEASE);

    motor2.setSpeed(250);
    motor2.run(RELEASE);



    pinMode(ir_sensor, INPUT);
}

void loop() {

  if(digitalRead(ir_sensor) == LOW) {
      motor1.run(RELEASE);
      motor2.run(RELEASE);


  }
  else {
      motor1.run(FORWARD);
      motor2.run(FORWARD);

  }

}
