Servo servo;
int t = 0;
int timeStop = 0;
bool valveClosed = true;
bool isCrusing = false;
bool manueverDone = false;
int altDiff = 0; //avg difference between last 5 readings of alt
int tCruise = 0;
void setup() {
  servo.attach(0);

}

void loop() {
  if (alt >= 50000 && valveClosed) {
    t = millis() + 9000;
    servo.write(180);
    valveClosed = false;
  }
  if (55000 <= alt && !valveClosed) {
    t = millis() + 9000;
    servo.write(0);
    valveClosed = true;
    manueverDone = true;
  }
  if (millis() > t) {
    servo.write(90);
  }
  if (altDiff < 100 && manueverDone) {
    isCruising = true;
    tCruise = millis() + 300000;
  }
  if (millis() > tCruise && isCruising) {
    t = millis() + 216_000_000;
    servo.write(180);
    valveClosed = false;
    isCruising = false;
  }
  if (millis() > (t + 60000) && !isCruising && manueverDone) {
    t = millis() + 216_000_000;
    servo.write(180);
    valveClosed = false;
    isCruising = false;
  }

}
