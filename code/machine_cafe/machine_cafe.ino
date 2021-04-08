#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

//Bluetooth
SoftwareSerial mySerial(10, 11); // RX, TX

//Servo
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int servoStart = 220; //Valeur Min
const int servoEnd = 420; //Valeur Max
int ordre = 0;
String readString;

int brochePouce=0;
int brocheIndex=2;
int brocheM=4;
int brocheA=6;
int brocheO=8;

void setup() {
  //Servo
  pwm.begin(); 
  pwm.setPWMFreq(50);

  //Bluetooth
  pinMode(9,OUTPUT); digitalWrite(9,HIGH);
  mySerial.begin(38400);

  //Liason série
  Serial.begin(9600);
  Serial.println ("Main_Bionique_prete");
}

void loop(){

  while (mySerial.available()) {
    char c = mySerial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(9);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() > 0) {
    int ordre = readString.toInt();
    Serial.println (ordre);
    if ((ordre > (servoStart + 1000)) && (ordre < (servoEnd + 1000))) {
      pwm.setPWM(brochePouce,0,ordre-1000);
    }
    else if ((ordre > (servoStart + 2000)) && (ordre < (servoEnd + 2000))){
      pwm.setPWM(brocheIndex,0,ordre-2000);
    }
    else if ((ordre > (servoStart + 3000)) && (ordre < (servoEnd + 3000))){
      pwm.setPWM(brocheM,0,ordre-3000);   
      pwm.setPWM(brocheA,0,ordre-3000);   
      pwm.setPWM(brocheO,0,ordre-3000);   
    }
    else{
      Serial.print("echec : ");
      Serial.println (ordre);
    }
    readString=""; //empty for next input
  } 
}
