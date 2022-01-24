#define GREEN_BTN_PIN D4
#define RED_BTN_PIN D3
#define DEBOUNCE_TIME 100
#define NUMBERS_OF_CHANNELS 2

#define FAN_OFF 0
#define FAN_FWD 1
#define FAN_BCK 2

typedef struct{
  int pinNumber;
  bool isFanOn;
  int fanWay;
  int btnVal;
  int lastBtnVal;
  unsigned long lastPressTime;
}FanChannel;

FanChannel Channels[NUMBERS_OF_CHANNELS] = {
  {GREEN_BTN_PIN, false,FAN_FWD,0,0,0},
  {RED_BTN_PIN, false,FAN_BCK,0,0,0}
};

void btnsSetup(){
  for(int i = 0; i< NUMBERS_OF_CHANNELS; i++){
    pinMode(Channels[i].pinNumber, INPUT_PULLUP);
    Channels[i].lastBtnVal = digitalRead(Channels[i].pinNumber);
    Channels[i].lastPressTime = millis();
  }
}

void checkBtns(){

  for(int i = 0; i < NUMBERS_OF_CHANNELS; i++){
    
    Channels[i].btnVal = digitalRead(Channels[i].pinNumber);
    
    if (((Channels[i].btnVal == LOW) && (Channels[i].lastBtnVal == HIGH))&&
       (millis() - Channels[i].lastPressTime >  DEBOUNCE_TIME)){
        
        Channels[i].lastPressTime = millis();

        if(Channels[i].isFanOn)
        {
          setFanByStatus(FAN_OFF);
          Channels[i].isFanOn = false;
        }
        else
        {
          setFanByStatus(Channels[i].fanWay);
          Channels[i].isFanOn = true;
        }
    }
    Channels[i].lastBtnVal = Channels[i].btnVal;
  }
  delay(DEBOUNCE_TIME);
}
