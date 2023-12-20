#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Ultrasonic Sensor 1.....
int echo1 = 14;  // connect digital I/O  to the ECHO/Rx Pin
int trig1 = 15; // connect digital I/O  to the TRIG/TX Pin

//Ultrasonic Sensor 2.....
int echo2 = 16;   // connect digital I/O  to the ECHO/Rx Pin
int trig2 = 17;  // connect digital I/O  to the TRIG/TX Pin


// Black Line Follower
#define IR1 2      //Right sensor
#define IR2 3      //Middle Sensor
#define IR3 4      //Left Sensor

//Right Motor
#define MotorAip1 7
#define MotorAip2 6
//Left motor
#define MotorBip1 10
#define MotorBip2 8


//Servo Motor....
int servoPin = 5;

//Buzzer.....
int bz = 12;

//Constant for algorithm...
int a, b, c, d, e, f;

int distance1, distance2;
Servo servo;
int angle = 0;  // servo position in degrees
String incomingByte ; // for incoming serial data
void setup()
{
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);

  pinMode(echo1, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig2, OUTPUT);

  pinMode(MotorAip1, OUTPUT);
  pinMode(MotorAip2, OUTPUT);
  pinMode(MotorBip1, OUTPUT);
  pinMode(MotorBip2, OUTPUT);
  digitalWrite(MotorAip1, LOW);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, LOW);
  digitalWrite(MotorBip2, LOW);

  pinMode(bz, OUTPUT);
  servo.attach(servoPin);

  servo.write(0);
  digitalWrite(bz, LOW);

  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO IIST");
  lcd.setCursor(0, 1);
  lcd.print("INDORE");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Covid Protective");
  lcd.setCursor(0, 1);
  lcd.print("Robot ");
  delay(2000);
  lcd.clear();
}

void loop()
{
  while (1)
  {
    

    if (digitalRead(IR1) == 0 && digitalRead(IR2) == 1 && digitalRead(IR3) == 0) //IR not on black line
    {
      //Move both the Motors
      digitalWrite(MotorAip1, HIGH);
      digitalWrite(MotorAip2, LOW);
      digitalWrite(MotorBip1, HIGH);
      digitalWrite(MotorBip2, LOW);
      lcd.print("Forward");
      lcd.clear();


    }

    else if (digitalRead(IR1) == 1 && digitalRead(IR2) == 0 && digitalRead(IR3) == 0)
    {
      digitalWrite(MotorAip1, HIGH);
      digitalWrite(MotorAip2, HIGH);
      digitalWrite(MotorBip1, HIGH);
      digitalWrite(MotorBip2, LOW);
      lcd.print("Right");
      lcd.clear();
    }

    else if (digitalRead(IR1) == 0 && digitalRead(IR2) == 0 && digitalRead(IR3) == 1)
    {
      digitalWrite(MotorAip1, HIGH);
      digitalWrite(MotorAip2, LOW);
      digitalWrite(MotorBip1, HIGH);
      digitalWrite(MotorBip2, HIGH);
      lcd.print("Left");
      lcd.clear();

    }

    else if (digitalRead(IR1) == 1 && digitalRead(IR2) == 1 && digitalRead(IR3) == 1) //IR will not glow on black line
    {
      //Stop both Motors
      digitalWrite(MotorAip1, LOW);
      digitalWrite(MotorAip2, LOW);
      digitalWrite(MotorBip1, LOW);
      digitalWrite(MotorBip2, LOW);
      lcd.clear();
      lcd.print("Stop");
      check_social_distancing();
      Serial.write("Stop");
      delay(500);
    }
  }

}

void check_social_distancing()
{
  // Scan from 0 to 180 degrees...
  // Scaning from 0 to 45 and taking reading on 45...
  delay(800);
  for (angle = 0; angle <= 45; angle++)
  {
    servo.write(angle);
    delay(30);
  }

  //Assigning value of Sensor_1 and Sensor_2 to a & b
  delay(800);
  Sensor1();
  a = distance1;
  Sensor2();
  b = distance2;

  //Printing Distance on LCD..
  print_distance();


  // Scaning from 45 to 90 and taking reading on 90 ...
  for (angle = 45; angle <= 90; angle++)
  {
    servo.write(angle);
    delay(30);
  }

  //Assigning value of Sensor_1 and Sensor_2 to c & d
  delay(800);
  Sensor1();
  c = distance1;
  Sensor2();
  d = distance2;

  //Printing Distance on LCD..
  print_distance();


  // Scaning from 90 to 135 and taking reading on 135...
  for (angle = 90; angle <= 135; angle++)
  {
    servo.write(angle);
    delay(30);
  }

  //Assigning value of Sensor_1 and Sensor_2 to e & f
  delay(800);
  Sensor1();
  e = distance1;
  Sensor2();
  f = distance2;

  //Printing Distance on LCD..
  print_distance();

  delay(500);

  // Condition to check servo from 45 to 135
  // Assume a , b , c , d , e , f is 6 Ultrasonic sensor's reading....

  // If No Reading from All Sensor

  if ((a > 20 && b > 20) && (c > 20 && d > 20) && (e > 20 && f > 20))
  {
    lcd.print("Nothing Detected...");
    delay(1000);
    lcd.clear();
  }


  // If Reading  from any one sensor
  else if ((a > 20 && b > 20) && (c > 20 && d > 20) && ((e < 20 && f < 20) || (e > 20 && f < 20) || (e < 20 && f > 20)))
  {
    lcd.print("Only One Object..");
    delay(1000);
    lcd.clear();
  }

  else if (((a < 20 && b < 20) || (a > 20 && b < 20) || (a < 20 && b > 20)) && (c > 20 && d > 20) && (e > 20 && f > 20))
  {
    lcd.print("Only One Object..");
    delay(1000);
    lcd.clear();
  }

  else if ((a > 20 && b > 20)  && ((c < 20 && d < 20) || (c > 20 && d < 20) || (c < 20 && d > 20)) && (e > 20 && f > 20))
  {
    lcd.print("Only One Object..");
    delay(1000);
    lcd.clear();
  }


  // If Two Simultaneous Sensor got reading  c d and e f
  else if ((a > 20 && b > 20) && ((c > 20 && d < 20) || (c < 20 && d > 20) || (c < 20 && d < 20)) && ((e < 20 && f < 20) || (e > 20 && f < 20) || (e < 20 && f > 20)))
  {
    digitalWrite(bz, HIGH);
    delay(2000);
    digitalWrite(bz, LOW);
    No_SocialDistancing();
    delay(800);
    lcd.clear();
  }

  else if (((a < 20 && b < 20) || (a > 20 && b < 20) || (a < 20 && b > 20)) && ((c > 20 && d < 20) || (c < 20 && d > 20) || (c < 20 && d < 20)) && (e > 20 && f > 20))
  {
    digitalWrite(bz, HIGH);
    delay(2000);
    digitalWrite(bz, LOW);
    No_SocialDistancing();
    delay(800);
    lcd.clear();
  }


  // If all Sensor got reading together
  else if (((a < 20 && b < 20) || (a > 20 && b < 20) || (a < 20 && b > 20)) && ((c > 20 && d < 20) || (c < 20 && d > 20) || (c < 20 && d < 20)) && ((e < 20 && f < 20) || (e > 20 && f < 20) || (e < 20 && f > 20)))
  {
    digitalWrite(bz, HIGH);
    delay(2000);
    digitalWrite(bz, LOW);
    No_SocialDistancing();
    delay(800);
    lcd.clear();
  }
  else
  {
    SocialDistancing();
    delay(800);
    lcd.clear();
  }
  delay(500);

  // Shift Servo from 135 - 180 to getvalue on 135 again
  //  for (angle = 135; angle <= 180 ; angle++)
  //  {
  //    servo.write(angle);
  //    delay(30);
  //  }
  //  delay(30);
  for (angle = 135; angle >= 0 ; angle--)
  {
    servo.write(angle);
    delay(30);
  }
  delay(500);
}

void Sensor1()
{
  digitalWrite(trig1, LOW);  // send low pulse for 2μs
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH); // send high pulse for 10μs
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);  // back to low pulse
  distance1 = pulseIn(echo1, HIGH);  // read echo value
  distance1 = distance1 / 29 / 2; // in cm
}
void Sensor2()
{
  digitalWrite(trig2, LOW);  // send low pulse for 2μs
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH); // send high pulse for 10μs
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);  // back to low pulse
  distance2 = pulseIn(echo2, HIGH);  // read echo value
  distance2 = distance2 / 29 / 2; // in cm
}

void print_distance()
{
  lcd.setCursor(0, 0);
  lcd.print("Sensor_1= ");
  lcd.print(distance1);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print("Sensor_2= ");
  lcd.print(distance2);
  lcd.print("cm");
  delay(500);
  lcd.clear();
}

void SocialDistancing()
{
  lcd.setCursor(0, 0);
  lcd.print("Social ");
  lcd.setCursor(0, 1);
  lcd.print("   Distancing....");
}

void No_SocialDistancing()
{
  lcd.setCursor(0, 0);
  lcd.print("No Social ");
  lcd.setCursor(0, 1);
  lcd.print("   Distancing....");
}
