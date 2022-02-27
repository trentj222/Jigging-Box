/*
  Jigging box

  This code is for building a jigging box. 
  
  This is essentially a state machine that is determined 
  by the status of each of 4 switches.
  
  Masterpower pin must be switched for any of them to work,
  otherwise motor is stopped.
  It then drives 2 pins, for forward and reverse of the motor.
  

  created 22 Feb 2022
  by Trent Jesukaitis
*/


int state = 0;
void setup() {
  //start serial connection
  Serial.begin(9600);
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(6, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

}

void loop() {
  //read the pushbutton value into a variable
  int downRed = digitalRead(6);
  int jigRun = digitalRead(10);
  int masterPower = digitalRead(11);
  int upGreen = digitalRead(2);
 // ramp up forward
 

  // state 0 - all off
  // state 1 - bring up
  // state 2 - let down
  // state 3 - jig active
 


  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  delay(50);


  if (downRed == 0 && upGreen == 1 && masterPower == 0 && jigRun == 1 ) {
    state = 2;
    //digitalWrite(7, HIGH);
  }
  if (downRed == 1 && upGreen == 0 && masterPower == 0 && jigRun == 1 ) {
    state = 1;
    //digitalWrite(8, HIGH);

  }
  if (masterPower == 1) {
    state = 0;
  }

  if (downRed == 1 && upGreen == 1 && masterPower == 0 && jigRun == 0 ) {
    state = 3;
    // on and off up down
    //digitalWrite(8, HIGH);
  }
  switch (state) {
    case 0:
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      delay(50);
      break;
    case 1:
      digitalWrite(5, LOW);
      digitalWrite(3, HIGH);
      delay(50);
      break;
    case 2:
      digitalWrite(3, LOW);
      digitalWrite(5, HIGH);
      delay(50);
      break;
    case 3:
      //jigging
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
        delay(700);
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      delay(1000);
      digitalWrite(5, HIGH);
      digitalWrite(3, LOW);
     delay(700);

    default:
     // digitalWrite(3, LOW);
     // digitalWrite(5, LOW);
      delay(50);
      break;

  }
  Serial.println(downRed);
  Serial.println(upGreen);
  Serial.println(jigRun);
  Serial.println(masterPower);
  Serial.println(state);
  state = 0;


}
