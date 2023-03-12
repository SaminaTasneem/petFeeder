#include <ESP8266WiFi.h>
#include <Servo.h>
#include <FirebaseESP8266.h>

// Replace with your network credentials
const char* ssid = "shaap";
const char* password = "nrmc8365";

// Replace with your Firebase project details
String firebase_host = "nodemcu-6216c-default-rtdb.firebaseio.com";
String database_name = "String/txt";
String firebase_secret = "XME3H7pZweXxIpB4ccEO8SeUELDKIoARsjiBy2eQ";

// Replace with your servo pin number
const int servo_pin = 4;

// Create a Servo object
Servo myservo;
String last_value="";
unsigned long last_servo_on_time = 0;

void setup() {
  // Start the serial connection
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected");

  // Initialize the servo object
  myservo.attach(servo_pin);

  // Initialize the Firebase database
  Firebase.begin(firebase_host, firebase_secret);
}

void loop() {
  // Get the string value from Firebase database
  FirebaseData fbdo;
  Firebase.getString(fbdo, "/String/text/txt");
  String value = fbdo.stringData();
  Serial.println("Value from Firebase: " + value);

  if (value == "ON") {
    // Turn on the servo
    myservo.write(180);
  } else if (value == "OFF") {
    // Turn off the servo
    myservo.write(0);
  } else if (value == "5s") {
    if(last_value!="5s"){
       myservo.write(180);
       delay(5000);
       myservo.write(0);
    //last_servo_on_time = millis();
    }
  }  else if (value == "10s") {
    if(last_value!="10s"){
       myservo.write(180);
       delay(10000);
       myservo.write(0);
    //last_servo_on_time = millis();
    }
  }

  last_value=value;
  // Convert the string to an integer
  //int angle = value.toInt();

  // Set the servo angle based on the value from Firebase

  // Wait for a short period of time before getting the value again
  delay(500);
}
