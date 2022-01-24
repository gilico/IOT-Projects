bool isTimerWorking;
int secondsLeft;
int measureTotalTime = 60;

void setup() {
  rtcSetup();
  setup_7seg();
  btnSetup();
  wifi_setup();
  isTimerWorking = false;
  Serial.begin(9600);
  
}

void loop() {
  wifi_loop();
  if (isBtnPressed()) {
    //start measure
    isTimerWorking = true;
    secondsLeft = measureTotalTime;
    setMeasureStart();
  }
  if (isTimerWorking) {
    secondsLeft= measureTotalTime - getSecPassed();
    showTimeLeft();
  }
}
