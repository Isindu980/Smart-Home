#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Replace with your Firebase and WiFi credentials
#define FIREBASE_HOST "iotapp10-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "KcMFtrB6MPTWWjI7tv4pV8sNdjd7zfS9BGoUGLoK"
#define WIFI_SSID "Galaxy A23"
#define WIFI_PASSWORD "12345678TT"

const int BULB1_PIN = D2;  // Define the pin where the first bulb is connected
const int BULB2_PIN = D3;  // Define the pin where the second bulb is connected
const int BULB3_PIN = D4;  // Define the pin where the third bulb is connected
const int BULB4_PIN = D5;  // Define the pin where the fourth bulb is connected
const int FAN_PIN = D6;    // Define the pin where the fan is connected

void setup() {
  pinMode(BULB1_PIN, OUTPUT);
  pinMode(BULB2_PIN, OUTPUT);
  pinMode(BULB3_PIN, OUTPUT);
  pinMode(BULB4_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  
  Serial.begin(9600);
  delay(500);
  
  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected.");
  Serial.println(WiFi.localIP());
  
  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Read the values from Firebase
  bool bulb1 = Firebase.getBool("bulb1");
  bool bulb2 = Firebase.getBool("bulb2");
  bool bulb3 = Firebase.getBool("bulb3");
  bool bulb4 = Firebase.getBool("bulb4");
  bool fan = Firebase.getBool("fan");
  
  Serial.print("Bulb1: ");
  Serial.println(bulb1);
  Serial.print("Bulb2: ");
  Serial.println(bulb2);
  Serial.print("Bulb3: ");
  Serial.println(bulb3);
  Serial.print("Bulb4: ");
  Serial.println(bulb4);
  Serial.print("Fan: ");
  Serial.println(fan);

  // Control the bulbs and fan based on Firebase values
  digitalWrite(BULB1_PIN, bulb1 ? LOW : HIGH);
  
  digitalWrite(BULB2_PIN, bulb2 ? LOW : HIGH);
  digitalWrite(BULB3_PIN, bulb3 ? LOW : HIGH);
  digitalWrite(BULB4_PIN, bulb4 ? LOW : HIGH);
  digitalWrite(FAN_PIN, fan ? LOW : HIGH);
  
  delay(10); // Add a delay to avoid rapid toggling and to allow time for Firebase to update
}
