#include <Time.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

#define WIFI_SSID "Insert WiFi ID here"
#define WIFI_PASSWORD "Insert WiFi password here"
#define FIREBASE_HOST "Insert Firebase Host here"
#define FIREBASE_AUTH "Insert Firebase Auth here"

int timezone=3*3600;
int dst=0;
String t;

void setup() {
   // Initialize the serial port
  Serial.begin(115200);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK"); 

}

void loop() {

delay(1000);
int i=0;
 while(Serial.available() > 0) {
    delay(3000);
    t = Serial.read();
    Serial.println(t);
    Firebase.setString("WaterLevel/Percentage", t);                                  //setup path and send readings  
    i++;
    if(i==20)
    {
      time_t timepast = now();
      Firebase.pushString("PastWaterLevel/Percent",t); 
      Firebase.pushString("PastWaterLevel/Time",String(timepast));   
      i=0;
    }
    if (Firebase.failed()) { 
     Serial.print("pushing WaterLevel failed:"); 
     Serial.println(Firebase.error());   
     return; 
    }else
    {
      Serial.println("Transmission finised");
    }
    
  }
  

  // Send a message over the serial port
 

}
