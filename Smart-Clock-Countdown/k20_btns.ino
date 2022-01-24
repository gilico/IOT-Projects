#define greenBtn D4
#define DEBOUNCE_TIME 50

typedef struct{
  int pintNumber;
  int btnVal;
  int lastBtnVal;
  unsigned long lastPressTime;
}MyBtn;

MyBtn GreenBtn = {greenBtn, 0,0,0};

void btnSetup(){
  pinMode(GreenBtn.pintNumber, INPUT_PULLUP);
  // set the last val to the val of digital that read the pin - incase the button is pressed in the begin
  GreenBtn.lastBtnVal = digitalRead(GreenBtn.pintNumber);
  GreenBtn.lastPressTime = millis();  
}

bool isBtnPressed(){
  bool ret = false;
  
  GreenBtn.btnVal = digitalRead(GreenBtn.pintNumber);
  
  if (GreenBtn.btnVal == LOW && GreenBtn.lastBtnVal == HIGH
      && millis() - GreenBtn.lastPressTime >  DEBOUNCE_TIME) {
    ret = true;
  }
  GreenBtn.lastBtnVal = GreenBtn.btnVal;
  return ret;
}
