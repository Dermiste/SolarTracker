#include <Servo.h>



String sA0;
String sA1;
String sA2;
String sA3;

String vDelta;
String hDelta;

Servo bottomServo;
Servo topServo;
String vMsg;
String hMsg;



int deltaTolerance = 20;
int servoStep = 2;

int stepFactor = 16;

void setup(){
  Serial.begin(9600);
  bottomServo.attach(9); 
  topServo.attach(10);
  
  sA0 = String("A0=");
  sA1 = String("A1=");
  sA2 = String("A2=");
  sA3 = String("A3=");
  
  vMsg = String("to write on v servo :");
  hMsg = String("to write on h servo :");
  
  vDelta = String("Vertical   delta=");
  hDelta = String("Horizontal delta=");
}

void loop(){
  delay(60);
  Serial.println(cumputeValues());
  //Serial.println(vDelta + getVerticalDelta());
  Serial.println(hDelta + getHorizontalDelta());
  //Serial.println(getVerticalDelta());
  correctHPosition();
  correctVPosition();
  
  Serial.println("\r");
  
  //correctVPosition();
}

boolean correctHPosition(){
  int toWrite;
  boolean didCorrect = false;
  int hDelta = getHorizontalDelta();
  int currentServoRead = bottomServo.read();

  if (abs(hDelta) > deltaTolerance){    
    if (hDelta < 0){
      toWrite = currentServoRead + abs(hDelta)/stepFactor;
    } else {
      toWrite = currentServoRead - abs(hDelta)/stepFactor;
    }
    Serial.println(hMsg + toWrite);
    if (toWrite >= 180 || toWrite <= 0){
      didCorrect = false;
    } else {
      didCorrect = true;
      bottomServo.write(toWrite);
    }
  }  
  return didCorrect;
}

void correctVPosition(){
  int toWrite;
  int vDelta = getVerticalDelta();
  int currentServoRead = topServo.read();
  if (abs(vDelta) > deltaTolerance){

    if (vDelta < 0){
      toWrite = currentServoRead + abs(vDelta)/stepFactor;
    } else {
      toWrite = currentServoRead - abs(vDelta)/stepFactor;
    }
    if (toWrite >= 120 || toWrite <= 10){
    
    } else {
      Serial.println(vMsg + toWrite); 
      topServo.write(toWrite);
    }
    
  }   
}

String cumputeValues(){
  int R0 = analogRead(A0);
  int R1 = analogRead(A1);
  int R2 = analogRead(A2);
  int R3 = analogRead(A3);
  return sA0+R0+" - "+sA1+R1 +" - "+sA2+R2 +" - "+sA3+R3;
}

int getHorizontalDelta(){
  int R0 = analogRead(A0);
  int R1 = analogRead(A1);
  int R2 = analogRead(A2);
  int R3 = analogRead(A3);
  
  int totalLeft = R0 + R1;
  int totalRight = R2 + R3;
  return totalLeft - totalRight;
}

int getVerticalDelta(){
  int R0 = analogRead(A0);
  int R1 = analogRead(A1);
  int R2 = analogRead(A2);
  int R3 = analogRead(A3);

  int totalUp = R0 + R3;
  int totalBottom = R1 + R2;
  return totalBottom - totalUp;
}
