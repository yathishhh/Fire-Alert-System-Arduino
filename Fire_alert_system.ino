
int RELAY = 26;
int Flame_sensor = 28;
int Flame_detected;
#include <SoftwareSerial.h>

//-----------------------------------------------------------------------------------
//Alert reciever's phone number with country code
const String PHONE_1 = "+916363496335";
const String PHONE_2 = ""; //optional
const String PHONE_3 = ""; //optional 
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
#define rxPin 17
#define txPin 16
SoftwareSerial sim800L(rxPin,txPin);
void setup()
{
  //Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  tone(26,1000,1000);
  pinMode(Flame_sensor, INPUT);
  //Serial.begin(115200);
  
  //-----------------------------------------------------------------------------------
  //Begin serial communication: SIM800L
  //sim800L.begin(9600);
  
  //-----------------------------------------------------------------------------------
  pinMode(Flame_sensor, INPUT);
  
  //-----------------------------------------------------------------------------------
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY,LOW);
  
  //----------------------------------------------------------------------------------
  //Serial.println("Initializing...");
  //Once the handshake test is successful, it will back to OK
  // sim800L.println("AT");
  // delay(1000);
  // sim800L.println("AT+CMGF=1");
  // delay(1000);
}
void loop()
{
//   Flame_detected = digitalRead(Flame_sensor);
//   Serial.println(Flame_detected);
//  delay(100);
  
  while(sim800L.available()){
  Serial.println(sim800L.readString());
  }
  
  Flame_detected = digitalRead(Flame_sensor);
  Serial.println(Flame_detected);
  delay(100);

  //The fire is detected, trigger Alarm and send sms
   if (Flame_detected == 0)
   {
     Serial.println("Flame detected...! take action immediately.");
     
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(RELAY, HIGH);
    delay(500);
    send_multi_sms();
    make_multi_call();
    
 

     
  }
  else
  {
    Serial.println("No Flame detected. stay cool");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(RELAY, LOW);
  }
//-----------------------------
}



//-----------------------------------------------------------------------------------
void send_multi_sms()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    send_sms("Fire detected...! take action immediately.", PHONE_1);
  }
  if(PHONE_2 != ""){
    Serial.print("Phone 2: ");
    send_sms("Fire detected...! take action immediately.", PHONE_2);
  }
  if(PHONE_3 != ""){
    Serial.print("Phone 3: ");
    send_sms("Fire detected...! take action immediately.", PHONE_3);
  }
}
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
void make_multi_call()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    make_call(PHONE_1);
  }
  if(PHONE_2 != ""){
    Serial.print("Phone 2: ");
    make_call(PHONE_2);
  }
  if(PHONE_3 != ""){
    Serial.print("Phone 3: ");
    make_call(PHONE_3);
  }
}
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
void send_sms(String text, String phone)
{
    Serial.println("sending sms....");
    delay(50);
    sim800L.print("AT+CMGF=1\r");
    delay(1000);
    sim800L.print("AT+CMGS=\""+phone+"\"\r");
    delay(1000);
    sim800L.print(text);
    delay(100);
    sim800L.write(0x1A); //ascii code for ctrl-26 //Serial2.println((char)26); //ascii code for ctrl-26
    delay(5000);
}
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
void make_call(String phone)
{
    Serial.println("calling....");
    sim800L.println("ATD"+phone+";");
    delay(20000); //20 sec delay
    sim800L.println("ATH");
    delay(1000); //1 sec delay
}