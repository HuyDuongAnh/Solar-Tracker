/*  This setup code sets the control buttons to I/O states.
    It also contains the logic of how the buttons control the actuator/slew motors.
*/
#define actuator_retract 22
#define actuator_extend 23
#define slew_cw 26
#define slew_ccw 28
#define button4 24 //controls actuator retract
#define button3 29 //controls actuator extend
#define button2 25 //controls slew clockwise
#define button1 27 //controls slew counter-clockwise
#define hall_sensor 2

volatile int countPos = 0;
volatile int countNeg = 0;
int deg = 0;

void setup() {
  // Set pins value to high
  digitalWrite(actuator_retract, HIGH);
  digitalWrite(actuator_extend, HIGH);
  digitalWrite(slew_ccw, HIGH);
  digitalWrite(slew_cw, HIGH);

  // Assign actuator and slew to be output pins 
  pinMode(actuator_retract, OUTPUT);
  pinMode(actuator_extend, OUTPUT);
  pinMode(slew_ccw, OUTPUT);
  pinMode(slew_cw, OUTPUT); 

  // Assign buttons to be input pins
  pinMode(button4, INPUT);
  pinMode(button3, INPUT);
  pinMode(button2, INPUT);
  pinMode(button1, INPUT);

  // Set button pin values to be low
  digitalWrite(button4, LOW);
  digitalWrite(button3, LOW);
  digitalWrite(button2, LOW);
  digitalWrite(button1, LOW);

  //Set serial baud rate
  Serial.begin(9600);

  //Set up interrupt
  attachInterrupt(digitalPinToInterrupt(2), magnet_detect, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Button 4 controls retraction of the actuator
  if(digitalRead(button4) == HIGH)
    digitalWrite(actuator_retract, LOW);
  else
    digitalWrite(actuator_retract, HIGH);
    
  // Button 3 controls extension of the actuator 
  if(digitalRead(button3) == HIGH)
    digitalWrite(actuator_extend, LOW);
  else
    digitalWrite(actuator_extend, HIGH);

  // Button 2 controls slew in clockwise direction 
  if(digitalRead(button2) == HIGH) {
    digitalWrite(slew_cw, LOW);    
    if(countPos - countNeg >= 112*deg)
    {
      Serial.print("degrees = ");
      Serial.print(deg);
      Serial.print("\n");
      deg++;
    }
  }
  else {
    digitalWrite(slew_cw, HIGH);
  }
  
  // Button 1 controls slew in counterclockwise direction
  if(digitalRead(button1) == HIGH) {
    digitalWrite(slew_ccw, LOW);
    if(countPos - countNeg <= 112*deg)
    {
      Serial.print("degrees = ");
      Serial.print(deg);
      Serial.print("\n");
      deg--;
    }
  }
  else {
    digitalWrite(slew_ccw, HIGH);  
  }
}

void magnet_detect() {
  if(digitalRead(button2) == HIGH)
    countPos++;
  if(digitalRead(button1) == HIGH)
    countNeg++;
}

