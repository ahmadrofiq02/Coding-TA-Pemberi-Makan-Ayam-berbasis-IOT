#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>
#include "HX711.h"
#include <Wire.h>
#include "DHT.h"
#define DHTPIN D2

Servo myservo; 
int nilaiservo;
int nilairelay;
String nilaimaksimalberat;
const char* ssid = "NebengBro";
const char* password = "bunda354313ok";
const char* host = "http://makananayam.my.id/";
unsigned long t;
int d;
 
const int LOADCELL_DOUT_PIN = D6;
const int LOADCELL_SCK_PIN = D5;  
HX711 scale;
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

void setup() {
 Serial.begin(9600); 
 pinMode(2, OUTPUT);//NODELED
 //relay
 pinMode(D0, OUTPUT);//LAMPU
 pinMode(D1, OUTPUT);//KIPAS
 //Loadcell
 pinMode(D5,OUTPUT);//SCK
 pinMode(D6,INPUT);//DATA
 

 myservo.attach(D8);
 dht.begin();
 scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
 scale.set_scale(440.0);                     
 scale.tare(50);
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 //delay(500);
 Serial.print(".");
 //----------------------------------------
 digitalWrite(2, LOW);
 delay(250);
 digitalWrite(2, HIGH);
 delay(250);
 //----------------------------------------
 }
 Serial.println("");
 Serial.println("WiFi connected");
 digitalWrite(2, HIGH);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 digitalWrite(D0,HIGH);
}

void loop() {
 WiFiClient client;
 const int httpPort = 80;
 if (!client.connect(host, httpPort))
 {
 Serial.println(host);
 Serial.println("Connection Failed");
 return;
 }
 //Servo
 String servo;
 HTTPClient http;
 servo = String(host) +"/bacaservo.php";
 Serial.println(servo);
 http.begin(servo);
 int httpCode = http.GET();
 String balasanservo = http.getString();
 Serial.print("Nilai Servo: ");
 Serial.println(balasanservo);
 if(balasanservo=="1"){
  if(nilairelay==1){
    myservo.write(0);
    Serial.println("Penutup Makanan Terbuka");  
    Serial.println("Lampu Hidup");
    float berat= scale.get_units(25);
    if(berat<=5){
      berat=0.0;
      }
    if(berat>5){
    Serial.print("Berat= ");
    Serial.print(berat);
    Serial.println(" g");
    }
    scale.power_down();
    delay(250);
    scale.power_up();
     String loadcell;
     HTTPClient http4;
     loadcell = String(host) + "/bacaloadcell.php?berat="+String(berat);
     Serial.println(loadcell);
     http4.begin(loadcell);
     int httpCode4 = http4.GET();
     String balasanloadcell = http4.getString();
     Serial.print("Berat: ");
     Serial.print(balasanloadcell);
     Serial.println("g");
     http4.end();
     delay(250);
    if(balasanloadcell >= nilaimaksimalberat){
      //NilaiLoadCell
     if(nilairelay==1){
     myservo.write(90);
     digitalWrite(D0,LOW);
     Serial.println("Penutup Makanan Tertutup");
     String servo;
     HTTPClient http;
     servo = String(host) +"/bacaservo1.php?baca_servo=0";  // pengirim
     Serial.println(servo);
     http.begin(servo);
     int httpCode = http.GET();
     String balasanservo = http.getString();  // penerima
    }
    else{
     myservo.write(90);
     digitalWrite(D0,HIGH);
     Serial.println("Penutup Makanan Tertutup");  
     Serial.println("Lampu Mati"); 
     nilaiservo=0; 
     }
    }
  }
  else{
    myservo.write(0);
    digitalWrite(D0,LOW);  
    Serial.println("Penutup Makanan Terbuka");  
    Serial.println("Lampu Hidup");
    nilaiservo=1;
    float berat= scale.get_units(25);
    if(berat<=5){
      berat=0.0;
      }
    if(berat>5){
    Serial.print("Berat= ");
    Serial.print(berat);
    Serial.println(" g");
    }
    scale.power_down();
    delay(250);
    scale.power_up();
     String loadcell;
     HTTPClient http4;
     loadcell = String(host) + "/bacaloadcell.php?berat="+String(berat); // pengirim
     Serial.println(loadcell);
     http4.begin(loadcell);
     int httpCode4 = http4.GET(); 
     String balasanloadcell = http4.getString(); // menerima
     Serial.print("Berat: ");
     Serial.print(balasanloadcell);
     Serial.println("g");
     http4.end();
     delay(250);
    if(balasanloadcell >= nilaimaksimalberat){
      //NilaiLoadCell
     if(nilairelay==1){
     myservo.write(90);
     digitalWrite(D0,LOW);
     Serial.println("Penutup Makanan Tertutup"); 
     String servo;
     HTTPClient http;
     servo = String(host) +"/bacaservo1.php?baca_servo=0"; //menerima
     Serial.println(servo);
     http.begin(servo);
     int httpCode = http.GET();
     String balasanservo = http.getString(); // menerima
    }
    else{
     myservo.write(90);
     digitalWrite(D0,HIGH);
     Serial.println("Penutup Makanan Tertutup");  
     Serial.println("Lampu Mati"); 
     nilaiservo=0; 
     }
    }
 }
 }
 else{
  if(nilairelay==1){
     myservo.write(90);
     digitalWrite(D0,LOW);
     Serial.println("Penutup Makanan Tertutup");  
    }
    else{
     myservo.write(90);
     digitalWrite(D0,HIGH);
     Serial.println("Penutup Makanan Tertutup");  
     Serial.println("Lampu Mati"); 
     nilaiservo=0; 
     }
 }
 http.end();
 delay(250);
  //relay
 String relay;
 HTTPClient http1;
 relay = String(host) + "/bacarelay.php"; // mengirim ke database from relay
 Serial.println(relay);
 http1.begin(relay);
 int httpCode1 = http1.GET();
 String balasanrelay = http1.getString(); // memanggil data dari database from relay
 Serial.print("Nilai Relay: ");
 Serial.println(balasanrelay);
 if(balasanrelay=="1"){
  digitalWrite(D0,LOW);
  Serial.println("Lampu Hidup");  
  nilairelay=1;
 }
 else{
  if(nilaiservo==1){
   digitalWrite(D0,LOW);
   Serial.println("Lampu Hidup");  
  }
  if(nilaiservo==0){
   digitalWrite(D0,HIGH);
   Serial.println("Lampu Mati");
   nilairelay=0;
  }
}
 http1.end(); //memeberhentikan pengiriman dan penerima data
 delay(250);
 //relay1
 String relay1;
 HTTPClient http2;
 relay1 = String(host) + "/bacarelay1.php";
 Serial.println(relay1);
 http2.begin(relay1);
 int httpCode2 = http2.GET();
 String balasanrelay1 = http2.getString();
 Serial.print("Nilai Relay1: ");
 Serial.println(balasanrelay1);
 if(balasanrelay1=="1"){
  digitalWrite(D1,LOW);
  Serial.println("Kipas Hidup");  
 }
 else{
   digitalWrite(D1,HIGH);
   Serial.println("Kipas Mati");  
 }
 http2.end();
 delay(250);
//Ultrasonic
 digitalWrite(D4,HIGH);
 delayMicroseconds(10);
 digitalWrite(D4,LOW);
 t=pulseIn(D3,HIGH);
 d=0.304*t/2.0;
 Serial.print("Jarak= ");
 Serial.print(d);
 Serial.println("Cm");
 String ultrasonik;
 HTTPClient http3;
 ultrasonik = String(host) + "/bacaultrasonik.php?baca_ultrasonik="+String(d); //pengirim
 http3.begin(ultrasonik);
 int httpCode3 = http3.GET();
 String balasanultrasonik = http3.getString();
 Serial.print("Jarak: ");
 Serial.print(balasanultrasonik);
 Serial.println("Cm");
 http3.end();
 delay(250);
 //DTH11
 float h = dht.readHumidity();
 float t = dht.readTemperature() ;
 String nilaidht;
 HTTPClient http4;
 nilaidht = String(host) + "/bacasuhukelembaban.php?suhu="+String(t)+"&&kelembaban="+String(h); //pengirim
 Serial.println(nilaidht);
 http4.begin(nilaidht);
 int httpCode4 = http4.GET();
 String balasannilaidht = http4.getString(); // menerima
 Serial.println(balasannilaidht);
 http4.end();
 delay(250);
//NilaiLoadCell
 String nilailoadcell;
 HTTPClient http5;
 nilailoadcell = String(host) + "/bacaberatmaksimal.php";
 Serial.println(nilailoadcell);
 http5.begin(nilailoadcell);
 int httpCode5 = http5.GET();
 String balasannilailoadcell = http5.getString();
 nilaimaksimalberat=balasannilailoadcell;
 Serial.print("Nilai Maksimum LoadCell: ");
 Serial.print(balasannilailoadcell);
 Serial.println("g");
 http5.end();
 delay(250);
}
