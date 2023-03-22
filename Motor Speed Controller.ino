#define SENSOR_PIN 0
#define PWM1_Output 3
#define IN1M1_Output 4
#define IN2M1_Output 5
#define PWM2_Output 6
#define SWSELECT 7
#define PUSHBUTTON 8
#define PWM1LIN 10
#define PWM2LIN 11
#define SPEAKE 12

bool s = 0;
int i = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(SWSELECT, INPUT_PULLUP);
  pinMode(PUSHBUTTON, INPUT_PULLUP);
  pinMode(PWM1_Output, OUTPUT);
  pinMode(IN1M1_Output, OUTPUT);
  pinMode(IN2M1_Output, OUTPUT);
  pinMode(PWM2_Output, OUTPUT);
  pinMode(PWM1LIN, OUTPUT);
  pinMode(PWM2LIN, OUTPUT);
  pinMode(SPEAKE, OUTPUT);
  //pinMode(IN1M2_Output, OUTPUT);
  //pinMode(IN2M2_Output, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(SPEAKE, 0);
  digitalWrite(IN1M1_Output, 0);
  digitalWrite(IN2M1_Output, 0);
  digitalWrite(PWM1_Output, 0);
  digitalWrite(PWM2_Output, 0);

}

void loop()
{
  int  maxspeed = analogRead(SENSOR_PIN) / 4;
  Serial.print("maxspeed = ");
  Serial.println(maxspeed);
  if (digitalRead(PUSHBUTTON) == 0) {
    i=i+2;
    if (i > maxspeed) {
      i =  maxspeed;
    }
  } else {
    i = 0;
  }
  Serial.print("Speed = ");
  Serial.println(i);
  if (i > 50) {
    if (s == 0) {
      digitalWrite(SPEAKE, 1);
      s = 1;
    } else {
      digitalWrite(SPEAKE, 0);
      s = 0;
    }
  } else {
    digitalWrite(SPEAKE, 0);
  }
  // sensor value is in the range 0 to 1023
  // the lower half of it we use for reverse rotation; the upper half for forward rotation
  if (digitalRead(SWSELECT) == 0) {
    digitalWrite(IN1M1_Output, 1);
    digitalWrite(IN2M1_Output, 0);
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(IN1M1_Output, 0);
    digitalWrite(IN2M1_Output, 1);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  analogWrite(PWM1_Output, i/1.5);
  analogWrite(PWM2_Output, i);
  digitalWrite(LED_BUILTIN, HIGH);
}
