#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
//#include <Servo.h>
//Servo myservo;
#include<stdio.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

double temp_amb;
double temp_obj;

WiFiClient client;
WiFiServer server(80);
String request;
int MotorAip1 = D8;
int MotorAip2 = D7;
// motor two

void frw();   // Forward
void rgt();   //Right
void rw();    //Reverse
void stp();   //Stop
void lft();   //Left

void frwl();  //Forward Left
void frwr();  //Forward Right

void rewr();  //Reverse Right
void rewl();  //Reverse Left

void temp();
//Left motor
int MotorBip1 = D6;
int MotorBip2 = D5;
int IR1 = D0;    //Right sensor
void setup()
{
//  myservo.attach(0);
  pinMode(IR1, INPUT);
  lcd.begin();
  lcd.begin();
  // Print a message to the LCD.
  lcd.backlight();
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Initialize MLX90614
  mlx.begin();
  WiFi.begin("LAPTOP", "7879900833");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  lcd.setCursor(1, 0);
  lcd.print(WiFi.localIP());
  server.begin();
  pinMode(MotorAip1, OUTPUT);
  pinMode(MotorAip2, OUTPUT);
  pinMode(MotorBip1, OUTPUT);
  pinMode(MotorBip2, OUTPUT);
  digitalWrite(MotorAip1, LOW);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, LOW);
  digitalWrite(MotorBip2, LOW);

}

void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request


  if (request.indexOf("/frwl") > 0)  {
    frwl();

  }
  if (request.indexOf("/forward") > 0)  {
    frw();

  }
  if (request.indexOf("/frwr") > 0)  {
    frwr();

  }
  if (request.indexOf("/left") > 0)  {
    lft();

  }
  if (request.indexOf("/stp") > 0)  {
    stp();

  }
  if (request.indexOf("/right") > 0)  {
    rgt();

  }
  if (request.indexOf("/rwl") > 0)  {
    rewl();

  }

  if (request.indexOf("/reverse") > 0)  {
    rw();
  }

  if (request.indexOf("/rwr") > 0)  {
    rewr();
  }
  if (request.indexOf("/temperature") > 0)  {
    temp();
  } 
//  if (digitalRead(IR1) == 0)
//  {
//    delay(150);
//    myservo.write(90);
//    delay(500);
//    myservo.write(180);
//    delay(500);
//    myservo.write(90);
//  }

  client.println("HTTP/1.1 200 OK"); //
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");

  client.println("<link rel=\"shortcut icon\" href=\"https://media-exp1.licdn.com/dms/image/C4E0BAQEzb_74r1fLLg/company-logo_200_200/0/1614056149968?e=2147483647&v=beta&t=gDqZIWfV0Zr7yj4F0_nEFJdsbwQ4atwKBmbFMDUbcIg\" type=\"image/x-icon\">");

  client.println("<script src=\"https://kit.fontawesome.com/afd317a279.js\" crossorigin=\"anonymous\"></script>");

  client.println("<title>Minor Project : COVID PROTECTIVE ROBOT:- PHASE II</title>");

  client.println("<link href=\"https://fonts.googleapis.com/icon?family=Material+Icons\" rel=\"stylesheet\">");

  client.println("<style>html { font-family: Cairo; display: inline; margin: 0px auto; text-align: center; background-color: black; color:white;}");

  client.println("button {background-color: #000000;border: white 1px;color: white;border-radius: 10px 10px;border-style: dotted;padding: 30px 80px;width: 100%;font-size: 15px;text-decoration: none;margin: 2px;font-weight: bold;cursor: pointer;height: auto;justify-content: space-between;transition: all 0.5s;}");
  client.println("button:hover {background-color: #2EE59D;box-shadow: 0px 15px 20px rgba(46, 229, 157, 0.4);color: rgb(0, 0, 0);transform: translate(-7px, -7px);}");
  client.println(".icon:hover {box-shadow: 0px 15px 20px rgba(46, 229, 157, 0.4);color: rgb(0, 0, 0);}");
  client.println(".image {height: auto;position: relative;align-items: center;height: 400px;width: 70%;align-items: center;background-image: url(https://indoreinstitute.com/wp-content/uploads/2021/05/f1.png);background-position: center;background-repeat: no-repeat;background-size: cover;}");
  client.println(".small-underline {width: 50%;height: .1rem;background-color: #00ccff;margin: 0 auto 1rem auto;}");
  client.println(".big-underline {width: 100%;height: 2px;background-color: #00ccff;}");
  client.println(".line {width: 300px;height: 1px;border: solid 1px white;}");
  client.println(".te {font-size: 20px;color: #ff0000;background-color: #000000;width: 300px; text-decoration: none; color: #e65715; padding: 5px; border: solid white 3px;border-radius: 0 20px ; font-family: monospace; transition: all 0.5s; font-weight:1000;padding: 30px 30px;margin-top: 50px;}");
  client.println(".icon {font-size: 70px;color: rgb(255, 255, 255);display: flex;}");
  client.println(".iconlu {font-size: 70px;color: rgb(255, 255, 255);display: flex;rotate: -45deg;}");
  client.println("table {text-align: center;margin: 0;padding: 0;}");
  client.println(".heading{color: black;font-family: monospace;font-style: italic;font-size: 25px;}");
  client.println(".title{font-size: 25px;font-family:monospace;}.team-card{display: flex;flex-direction: row;flex-wrap: wrap;justify-content: space-evenly;transition: all 0.5s; }.card-1{background-image:url(https://indoreinstitute.com/wp-content/uploads/2020/08/Dr.-Keshav-Patidar-300x289.jpg);width: 300px;height:300px;background-position:center;background-repeat: no-repeat;background-size: cover;margin-top: 30px;border-radius: 55px 20px;transition: all 0.5s;}.card-2{background-image: url(https://indoreinstitute.com/wp-content/uploads/2020/08/Mr.-Ankit-Jain-300x289.jpg);width: 300px;height:300px;background-position:center;background-repeat: no-repeat;background-size: cover;margin-top: 30px;border-radius: 55px 20px;transition: all 0.5s;}.card:hover{box-shadow: 0px 15px 20px rgba(255, 255, 255, 0.4);}.card-name{font-family:monospace;font-size: 25px;font-weight: bold;}");
  client.println(".thnx {font-size: 15px;color: #0084ff;background-color: #ffffff;text-decoration: none; border: solid black 1px;border-radius: 20px 20px ; font-family: monospace; transition: all 0.5s; font-weight: bolder;padding: 10px 0;margin-top: 20px;width: 200px;}");
  client.println("@media only screen and (max-width: 800px) {body {background-color: rgba(241, 246, 248, 0.966);color: black;}button {padding: 20px 20px;background-color: white;color: rgb(255, 255, 255);}.icon,.iconlu {font-size: 70px;color: rgb(0, 0, 0);display: flex;}.te {font-size: 20px;color: #ff0000;background-color: #ffffff;width: 300px; text-decoration: none; color: #e65715; padding: 5px; border: solid black 3px;border-radius: 0 20px ; font-family: monospace; transition: all 0.5s; font-weight:1000;padding: 30px 30px;margin-top: 50px;}button:hover {box-shadow: 0px 15px 20px rgba(0, 0, 0, 0.4);color: rgb(255, 255, 255);transform: translate(-7px, -7px);background-color: #00e1ff9b;}.te:hover{color: black;border-color:rgba(255, 255, 255, 0.616) ;}.card:hover{box-shadow: 0px 15px 20px rgba(0, 0, 0, 0.4);}}");

  //  client.println("");
  //  client.println("");

  client.println(".button2 {background-color: #555555;}</style></head>");
  client.println("<body>");
  client.println("<center>");
  client.println("<br>");
  client.println("<table class=\"tablea\"><tr><td><a href=\"/frwl\"><button><i class=\"fa-solid fa-chevron-up iconlu\"\"></i></button></a></td><td><a href=\"/forward\"><button><i class=\"fa-solid fa-chevron-up icon\"\"></i></button></a></td><td><a href=\"/frwr\"><button><i class=\"fa-solid fa-chevron-right iconlu\"\"></i></button></a></td></tr>");
  //
  client.println("<tr><td><a href=\"/left\"><button><i class=\"fa-solid fa-chevron-left icon\"\"></i></button></a></td><td><a href=\"/stp\"><button><i class=\"fa-solid fa-circle-stop icon\"\"></i></button></a></td><td><a href=\"/right\"><button><i class=\"fa-solid fa-chevron-right icon\"\"></i></button></a></td></tr>");
  //
  client.println("<tr><td><a href=\"/rwl\"><button><i class=\"fa-solid fa-chevron-left iconlu\"\"></i></button></a></td><td><a href=\"/reverse\"><button><i class=\"fa-solid fa-chevron-down icon\"\"></i></button></a></td><td><a href=\"/rwr\"><button><i class=\"fa-solid fa-chevron-down iconlu\"\"></i></button></a></td></tr></table>");
  //
  client.println("<a href=\"/temperature\"><button class=\"te\"\">TEMPERATURE</button></a>");
  client.println("<br>");


  if (request.indexOf("/temperature") > 0)  {
    temp();
    client.println("<div class=\"Temperature\">");
    client.print("<h2>Room Temp = </h2>");
    client.println("<h1>");
    client.print(temp_amb );
    client.print(" deg. C</h1>");
    client.print("<div class=\"line\"\"></div>");
    client.print("<h2>Object temp = </h2>");
    client.println("<h1>");
    client.print(temp_obj);
    client.print(" deg. C</h1></div>");
    client.println("<br>");
  }
  else {

  }
  client.println("<h2 class=\"heading\"\">Department of Electronics & Communication Engineering</h2>");
  client.println("<br>");
  client.println("<div class=\"image\"\"></div>");
  client.println("<br>");
  client.println("<br>");
  client.println("<br>");
  client.println("<div class=\"underline\"\"><div class=\"big-underline\"\"></div><br><div class=\"small-underline\"\"></div></div>");
  client.println("<h3 class=\"title\"\">Minor Project : COVID PROTECTIVE ROBOT:- PHASE II</h3>");
  client.println("<div class=\"underline\"\"><div class=\"small-underline\"\"></div><div class=\"big-underline\"\"></div></div>");
  client.println("<br>");
  client.println("<br>");
  client.println("<a href=\"https://jagahpee.github.io/IISTThnx\" target=\"_blank\"\"><button class=\"thnx\"\">Special Thanks To..</button></a>");
  client.println("<br>");
  client.println("<br>");
  client.println("<br>");
  client.println("<center>");
  client.println("<script>let btn = document.querySelector('button');document.body.addEventListener('keydown', (e) =>{if(e.key=='a'||e.key=='4'){window.location.href=\"/left\";}if(e.key=='d'||e.key=='6'){window.location.href=\"/right\";}if(e.key=='x'||e.key=='2'){window.location.href=\"/reverse\";}if(e.key=='w'||e.key=='8'){window.location.href=\"/forward\";}if(e.key=='q'||e.key=='7'){window.location.href=\"/frwl\";}if(e.key=='e'||e.key=='9'){window.location.href=\"/frwr\";}if(e.key=='z'||e.key=='1'){window.location.href=\"/rwl\";}if(e.key=='3'||e.key=='c'){window.location.href=\"/rwr\";}if(e.key=='5'||e.key=='s'){window.location.href=\"/stp\";}if(e.key=='t'||e.key=='0'){window.location.href=\"/temperature\";}})</script>");
  client.println("</body>");
  client.println("</html>");
  delay(1);
}

void frw() {
  Serial.println("Forward");
  digitalWrite(MotorAip1, HIGH);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, HIGH);
  digitalWrite(MotorBip2, LOW);
}

void rw() {
  Serial.println("Reverse");
  digitalWrite(MotorAip1, LOW);
  digitalWrite(MotorAip2, HIGH);
  digitalWrite(MotorBip1, LOW);
  digitalWrite(MotorBip2, HIGH);
}

void lft() {
  Serial.println("Left");
  digitalWrite(MotorAip1, HIGH);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, LOW);
  digitalWrite(MotorBip2, HIGH);
  delay(250);
  digitalWrite(MotorAip1, HIGH);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, HIGH);
  digitalWrite(MotorBip2, LOW);
}
void rgt()
{
  Serial.println("Right");
  digitalWrite(MotorAip1, LOW);
  digitalWrite(MotorAip2, HIGH);
  digitalWrite(MotorBip1, HIGH);
  digitalWrite(MotorBip2, LOW);
  delay(250);
  digitalWrite(MotorAip1, HIGH);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, HIGH);
  digitalWrite(MotorBip2, LOW);

}
void rewl() {
  Serial.println("Reverse Left");
  digitalWrite(MotorAip1, LOW);
  digitalWrite(MotorAip2, HIGH);
  digitalWrite(MotorBip1, HIGH);
  digitalWrite(MotorBip2, LOW);
  delay(150);
  digitalWrite(MotorAip1, LOW);
  digitalWrite(MotorAip2, HIGH);
  digitalWrite(MotorBip1, LOW);
  digitalWrite(MotorBip2, HIGH);
}
void rewr()
{
  Serial.println("Reverse Right");
  digitalWrite(MotorAip1, HIGH);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, LOW);
  digitalWrite(MotorBip2, HIGH);
  delay(150);
  digitalWrite(MotorAip1, LOW);
  digitalWrite(MotorAip2, HIGH);
  digitalWrite(MotorBip1, LOW);
  digitalWrite(MotorBip2, HIGH);
}
void frwl() {
  Serial.println("Forward Left");
  digitalWrite(MotorAip1, HIGH);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, LOW);
  digitalWrite(MotorBip2, HIGH);
  delay(150);
  digitalWrite(MotorAip1, HIGH);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, HIGH);
  digitalWrite(MotorBip2, LOW);
}
void frwr()
{
  Serial.println("Forward Right");
  digitalWrite(MotorAip1, LOW);
  digitalWrite(MotorAip2, HIGH);
  digitalWrite(MotorBip1, HIGH);
  digitalWrite(MotorBip2, LOW);
  delay(150);
  digitalWrite(MotorAip1, HIGH);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, HIGH);
  digitalWrite(MotorBip2, LOW);
}
void stp()
{
  Serial.println("Stop");
  digitalWrite(MotorAip1, LOW);
  digitalWrite(MotorAip2, LOW);
  digitalWrite(MotorBip1, LOW);
  digitalWrite(MotorBip2, LOW);

}
void temp()
{
  temp_amb = mlx.readAmbientTempC();
  temp_obj = mlx.readObjectTempC();
  if (temp_obj > 40) {
    digitalWrite(D4, HIGH);
    Serial.print("Warning...HIGH TEMP...");
    delay(50);
  }
  else {
    digitalWrite(D4, LOW);
  }

  Serial.print("Room Temp = ");
  Serial.println(temp_amb);
  Serial.print("Object temp = ");
  Serial.println(temp_obj);

}
