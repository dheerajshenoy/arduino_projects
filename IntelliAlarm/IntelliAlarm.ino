#include <Wire.h>
#include <ds3231.h>
#include <AFMotor.h>

struct ts t;

// USER ALARM TIME VARIABLES
int uhr, umin, usec, uday, umon, uyear;

// ALARM STOP BUTTON
int stopBtn = 6;
int speaker = 7;
int irInput = 8;

// MOTOR CONFIG
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4); 

bool alarm = false;

class intelliAlarm {
    public:

	// SET ALARM
	void setAlarm() {
  
	    uhr   = 1;
	    umin  = 1;
	    usec  = 1;
	    uday  = 1;
	    umon  = 1;
	    uyear = 1;

	    printf("Alarm set for %d:%d:%d on %d/%d/%d", uhr, umin, usec, uday, umon, uyear);

	}

	// SOUND ALARM
	void soundAlarm() {
	    digitalWrite(speaker, HIGH);
	    delay(1000);
	    digitalWrite(speaker, LOW);
	    delay(1000);
	}

	void turn() {
	    
	    motor1.run(RELEASE);
	    motor2.run(RELEASE);
	    motor3.run(RELEASE);
	    motor4.run(RELEASE);


	}

	// INITIAL MOTOR SETUP
	void startMoving() {
	    
	    motor1.setSpeed(200);
	    motor1.run(RELEASE);

	    motor2.setSpeed(200);
	    motor2.run(RELEASE);
	      
	    motor3.setSpeed(200);
	    motor3.run(RELEASE);
	      
	    motor4.setSpeed(200);
	    motor4.run(RELEASE);

	    if(irInput == HIGH)
		turn();
	    else
	    {
		motor1.run(FORWARD);
		motor2.run(FORWARD);
		motor3.run(FORWARD);
		motor4.run(FORWARD);
	    }

      
	}

	// COMPARE THE CURRENT TIME WITH THE ALARM TIME	
	void checkAlarm() {

	    if(uhr == t.hour && umin == t.min && usec == t.sec && uday == t.mday && umon == t.mon && uyear == t.year) {
		alarm = true;
		while(alarm) {
		    soundAlarm();
		    startMoving();
		}
	    }


	}
	

	// SYNC TIME FUNCTION 
	void syncTime() {
	    
	    t.mday = 1;
	    t.mon  = 1;
	    t.year = 1;
	    t.hour = 1;
	    t.min  = 1;
	    t.sec  = 1;

	    DS3231_set(t);
	}

};

intelliAlarm alarmObj;

void setup() {

    Serial.begin(9600);
    Wire.begin();
    DS3231_init(DS3231_CONTROL_INTCN);
    // alarmObj.syncTime();
    alarmObj.setAlarm();

}

void loop() {
    DS3231_get(&t);
    Serial.print("Date: ");
    Serial.print(t.mday);
    Serial.print("/");
    Serial.print(t.mon);
    Serial.print("/");
    Serial.print(t.year);
    Serial.print("\t Hour: ");
    Serial.print(t.hour);
    Serial.print(":");
    Serial.print(t.min);
    Serial.print(":");
    Serial.print(t.sec);

    digitalRead(stopBtn);
    
    if(stopBtn == HIGH) {
	alarm = false;
	Serial.print("Alarm stopped");
    }

    alarmObj.checkAlarm();

    delay(1000);
}
