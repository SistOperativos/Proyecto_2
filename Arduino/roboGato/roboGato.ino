/* meArm IK test - York Hackspace May 2014
 * Test applying Nick Moriarty's Inverse Kinematics solver
 * to Phenoptix' meArm robot arm, to walk a specified path.
 *
 * Pins:
 * Arduino    Base   Shoulder  Elbow    Gripper
 *    GND    Brown     Brown   Brown     Brown
 *     5V      Red       Red     Red       Red
 *     11    Yellow
 *     10             Yellow
 *      9                     Yellow
 *      6                               Yellow
 */
#include "meArm.h"
#include <Servo.h>

int basePin = 11;
int shoulderPin = 10;
int elbowPin = 9;
int gripperPin = 6;
String msg = " ";

meArm arm;

void setup() {
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
  arm.openGripper();
  Serial.begin(9600);
  
}

void loop() {
  msg = "";
  if(Serial.available()>0){
    msg = Serial.readString();
    if(msg.substring(0) == "a"){
      drawTriangle(1);
    }
    else if (msg.substring(0) == "b"){
      drawTriangle(2);
    }
    else if (msg.substring(0) == "c"){
      drawTriangle(3);
    }
    else if(msg.substring(0) == "d"){
      drawTriangle(4);
    }
    else if(msg.substring(0) == "e"){
      drawTriangle(5);
    }
    else if(msg.substring(0) == "f"){
      drawTriangle(6);
    }
    else if(msg.substring(0) == "g"){
      drawTriangle(7);
    }
    else if(msg.substring(0) == "h"){
      drawTriangle(8);
    }
    else if(msg.substring(0) == "i"){
      drawTriangle(9);
    }
    
  } 
  //Clap - so it's obvious we're at this part of the routine
//  arm.gotoPoint(0,100,50);
//  delay(500);
//  //Go up and left to grab something
//  arm.gotoPoint(50,100,50);
//  delay(500);
//  arm.gotoPoint(50,100,5);
//  delay(500);
 //arm.gotoPoint(-75,20,20);
//  delay(2000);
//  arm.gotoPoint(75,140,10);
//  delay(2000);
  //arm.gotoPoint(50,100,10);
//  delay(2000);
// drawTriangle();

}

void drawTriangle(int Place){
  if (Place == 1) {
    arm.gotoPoint(50,80,10);
    delay(2000);
    arm.gotoPoint(40,120,10);
    delay(2000);
    arm.gotoPoint(50,80,10);
    delay(2000);
    arm.gotoPoint(50,80,10);
    delay(2000);
    arm.gotoPoint(0,100,50);
  }
  else if (Place == 2){
    arm.gotoPoint(25,100,10);
    delay(100);
    arm.gotoPoint(25,140,10);
    delay(100);
    arm.gotoPoint(15,100,10);
    delay(100);
    arm.gotoPoint(25,100,10);
    delay(100);
    arm.gotoPoint(0,100,50);
  }
  if(Place == 3){
    arm.gotoPoint(10,100,10);
    delay(100);
    arm.gotoPoint(10,140,10);
    delay(100);
    arm.gotoPoint(-10,100,10);
    delay(100);
    arm.gotoPoint(10,100,10);
    delay(100);
    arm.gotoPoint(0,100,50);
  }
  else if (Place == 4) {
    arm.gotoPoint(75,120,10);
    delay(10);
    arm.gotoPoint(75,160,10);
    delay(10);
    arm.gotoPoint(50,120,10);
    delay(10);
    arm.gotoPoint(75,120,10);
    delay(10);
    arm.gotoPoint(0,100,50);
  }
  else if (Place == 5) {
    arm.gotoPoint(55,160,10);
    delay(100);
    arm.gotoPoint(55,175,10);
    delay(100);
    arm.gotoPoint(55,160,10);
    delay(100);
    arm.gotoPoint(55,160,10);
    delay(100);
    arm.gotoPoint(0,100,50);
  }
  else if (Place == 6) {
    arm.gotoPoint(10,160,15);
    delay(10);
    arm.gotoPoint(10,180,15);
    delay(10);
    arm.gotoPoint(-10,160,15);
    delay(10);
    arm.gotoPoint(10,160,15);
    delay(10);
    arm.gotoPoint(0,100,50);
  }
  else if (Place == 7) {
    arm.gotoPoint(130,150,25);
    delay(10);
    arm.gotoPoint(130,180,10);
    delay(10);
    arm.gotoPoint(90,150,10);
    delay(10);
    arm.gotoPoint(130,150,25);
    delay(10);
    arm.gotoPoint(0,100,50);
  }
  else if (Place == 8) {
    arm.gotoPoint(75,190,25);
    delay(10);
    arm.gotoPoint(75,210,8);
    delay(10);
    arm.gotoPoint(50,190,8);
    delay(10);
    arm.gotoPoint(75,190,25);
    delay(10);
    arm.gotoPoint(0,100,50);
  }
  else if (Place == 9) {
    arm.gotoPoint(10,190,25);
    delay(10);
    arm.gotoPoint(-10,210,8);
    delay(10);
    arm.gotoPoint(10,190,8);
    delay(10);
    arm.gotoPoint(10,190,25);
    delay(10);
    arm.gotoPoint(0,100,50);
  }
}
