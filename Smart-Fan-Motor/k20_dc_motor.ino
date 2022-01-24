#define MOTOR_A D1
#define MOTOR_B D2

#define FAN_OFF 0
#define FAN_FWD 1
#define FAN_BCK 2




void dcMotorSetup() {
  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);
}
int FanStatus;
void setFanByStatus(int newStatus){
  FanStatus = newStatus;
  
  switch(FanStatus){
    case FAN_OFF: fanOff(); break;
    case FAN_FWD: setOnFwd(); break;
    case FAN_BCK: setOnBck(); break;
  }
}

void setOnFwd() {
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, HIGH);
}


void setOnBck() {
  digitalWrite(MOTOR_B, LOW);
  digitalWrite(MOTOR_A, HIGH);
}

void fanOff() {
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, LOW);
}
