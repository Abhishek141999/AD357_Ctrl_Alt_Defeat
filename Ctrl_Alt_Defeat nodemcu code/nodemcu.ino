#include <dummy.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define FIREBASE_HOST "flood-assesment.firebaseio.com"
#define FIREBASE_AUTH "x7MHVRZDZ67crjl5Uv8Vid3PxXx7OO7aNybfb61A"


#define WIFI_SSID "Redmi"
#define WIFI_PASSWORD "987654320"



const int trigPin = D1;
const int echoPin = D2;
const int buzzer = D4;


long duration = 0;

double distance = 0;


void setup()
{


    Serial.print("Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting...");
    pinMode(buzzer, OUTPUT);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected to: ");
    Serial.println(WiFi.localIP());

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    

    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600);
    

}

void loop()
{

    getDistance();
    
    Serial.print("Distance: ");
    Serial.println(distance);
  
    delay(500);
}

void getDistance()
{
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    
    duration = pulseIn(echoPin, HIGH);

    
    distance = duration * 0.034 / 2;
    
     
   
    if (distance<=10)
    {
      Firebase.setFloat("High alert", 1);
      tone(buzzer,1000); 
      delay(1000); 
      
    }
    else
    {
      Firebase.setFloat("High alert", 0);
      noTone(buzzer);     
      delay(1000);
      
    }
   Firebase.setFloat("distance", distance);
        
}
