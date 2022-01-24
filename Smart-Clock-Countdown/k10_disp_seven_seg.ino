#include <ASCIIDic.h>
#include <NX7Seg.h>
#define redLed D1
#define CLK_DIO   D5   // sclk
#define LATCH_DIO D6 //rclk
#define DATA_DIO  D7  // dio

nx7seg my4x7seg = nx7seg(LATCH_DIO, CLK_DIO, DATA_DIO, false);

void setup_7seg() {
  /* Set DIO pins to outputs */
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
  pinMode(redLed, OUTPUT);
  Serial.begin(9600);
}
void showTimeLeft() {
  int sec = secondsLeft % 60;
  int min = secondsLeft / 60;
  my4x7seg.writeDigit(sec % 10, 0);
  my4x7seg.writeDigit(sec / 10, 1);
  my4x7seg.writeDigit(min % 10, 2);
  my4x7seg.writeDigit(min / 10, 3);
//  my4x7seg.refresh(1000);

  if(secondsLeft <= 0){
      isTimerWorking = true;
      displayOFF();
  }
}

void showTimeGen(int hh, int mm){
 
  my4x7seg.writeDigit(mm % 10, 0);
  my4x7seg.writeDigit(mm / 10, 1);
  my4x7seg.writeDigit(hh % 10, 2);
  my4x7seg.writeDigit(hh / 10, 3);
  my4x7seg.refresh(100);
}

void displayOFF() {
  char* data = "----";
  my4x7seg.write(data, 4);
  digitalWrite(redLed, HIGH);
  my4x7seg.refresh(2147483647);
}
