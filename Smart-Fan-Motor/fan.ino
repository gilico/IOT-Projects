


bool isFanFwd = true;
bool isBtnPressed = false;

void setup(){
  dcMotorSetup();
  btnsSetup();
  wifi_setup();
  Serial.begin(9600);
}


void loop(){
  checkBtns();
  wifi_loop();
}
