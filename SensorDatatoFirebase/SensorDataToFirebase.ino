#include <FirebaseArduino.h>                                                //Libraries needed
#include <ESP8266WiFi.h>
#include <DHT.h>
#define FIREBASE_HOST "covid19-6157f.firebaseio.com"                 // the project name address from firebase id
#define FIREBASE_AUTH "OxePjl6f7oEAfOkrbetxVv29FCJY83FMBtPf4BJp"            // the secret key generated from firebase  
#define WIFI_SSID "MI"                                                   // input your home or public wifi name 
#define WIFI_PASSWORD "12345678"                                            //password of wifi ssid
#define DHTPIN D4                                                           // what digital pin we're connected to
#define DHTTYPE DHT11                                                       // select dht type as DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);                             
void setup() 
{
  Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  dht.begin();                                                               //Start reading dht sensor
}

void loop() 
{
  //Code for AM2302 or DHT22 or DHT11
  float h = dht.readHumidity();                                              // Reading humidity  
   float t = dht.readTemperature();                                          // Read temperature as Celsius (the default)
   Serial.print(h);                                                          //Printing initial values of temperature and 
   Serial.print("\n");                                                       //temperature 
   Serial.println(t); 
  if (isnan(h) || isnan(t)) 
  {                                                                          // Check if any reads failed and exit early 
                                                                             //(to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
 }
  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h) + String("%");                                //convert integer humidity to string humidity 
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("Â°C ");
  String fireTemp = String(t) + String("Â°C");                               //convert integer temperature to string temperature
  delay(4000);
  
  Firebase.pushString("/DHT11/Humidity", fireHumid);                                  //setup path and send readings
  Firebase.pushString("/DHT11/Temperature", fireTemp);                                //setup path and send readings

}
