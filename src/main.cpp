

/*
Copyright (c) 2023 Tel @ TEL's BENCH 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/     
 
#include <Arduino.h>

//Inputs
#define In_UP 14         //A0
#define In_DOWN 15       //A1
#define In_LEFT 16       //A2
#define In_RIGHT 17      //A3
#define In_A_or_B 18     //A4
#define In_C_or_Start 19 //A5

//Outputs
#define Out_UP 2        //D2
#define Out_DOWN 3      //D3
#define Out_LEFT 4      //D4
#define Out_RIGHT 5     //D5
#define Out_A 6         //D6
#define Out_B 7         //D7
#define Out_C 8         //D8
#define Out_Start 9     //D9
#define Out_SELECT 10   //D10

#define SELECT_A LOW
#define SELECT_B HIGH

void setup(){

  //Inputs
  pinMode(In_UP ,INPUT);
  pinMode(In_DOWN ,INPUT);
  pinMode(In_LEFT ,INPUT);
  pinMode(In_RIGHT ,INPUT);
  pinMode(In_A_or_B ,INPUT);
  pinMode(In_C_or_Start ,INPUT);

  //Outputs
  pinMode(Out_UP ,OUTPUT);
  pinMode(Out_DOWN ,OUTPUT);
  pinMode(Out_LEFT ,OUTPUT);
  pinMode(Out_RIGHT ,OUTPUT);
  pinMode(Out_A ,OUTPUT);
  pinMode(Out_B ,OUTPUT);
  pinMode(Out_C ,OUTPUT);
  pinMode(Out_Start ,OUTPUT);
  pinMode(Out_SELECT ,OUTPUT);

}

void TestLeds(){
  int currentLed = Out_UP;
  while( currentLed++<=Out_Start){
    digitalWrite(currentLed,HIGH);
    delay(150);
    digitalWrite(currentLed,LOW);
  }
}

int GetInputHighLowStatus( int pin ){
  const int threshold  =  165;
  int val = analogRead( pin );
  return val<threshold ? LOW : HIGH;
}

void SetSelect( int state ){
  digitalWrite(Out_SELECT,state);
}

void ScanInputs(){

  //UP
  digitalWrite(Out_UP,!GetInputHighLowStatus(In_UP) );
  //DOWN
  digitalWrite(Out_DOWN,!GetInputHighLowStatus(In_DOWN));
  //LEFT
  SetSelect(SELECT_B);
  digitalWrite(Out_LEFT,!GetInputHighLowStatus(In_LEFT));
  //RIGHT
    SetSelect(SELECT_B);
  digitalWrite(Out_RIGHT,!GetInputHighLowStatus(In_RIGHT));

  //A
  SetSelect(SELECT_A);
  digitalWrite(Out_A,!GetInputHighLowStatus(In_A_or_B));
  //B
  SetSelect(SELECT_B);
  digitalWrite(Out_B,!GetInputHighLowStatus(In_A_or_B));
  //C
  SetSelect(SELECT_B);
  digitalWrite(Out_C,!GetInputHighLowStatus(In_C_or_Start));
  //Start
  SetSelect(SELECT_A);
  digitalWrite(Out_Start,!GetInputHighLowStatus(In_C_or_Start));

}


void loop() {

  ScanInputs();

}