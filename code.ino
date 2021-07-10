#include "FirebaseESP8266.h" // 파이어베이스 라이브러리
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define FIREBASE_HOST "host"
#define FIREBASE_AUTH "pw" // 데이터베이스 비밀번호

FirebaseData firebaseData;
//FirebaseJson json;

const char* ssid = "iptime"; // should be changed
const char* pass = "rjsemfwlak"; // should be changed

Servo myservo;

void setup(void){
  Serial.begin(115200);
  Serial.println(".");
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  myservo.attach(D5);   // Servo attached to D5 pin
  myservo.write(0);
}
 
void loop(void){
  if (Firebase.getString(firebaseData, "User/a/state"))  {
    String value = firebaseData.stringData(); // 값을 문자열로 받아와서 value에
    Serial.println(value); // 시리얼모니터에 값을 출력
    
    if (value == "1"){
      myservo.write(90);
      //Firebase.setStringAsync(firebaseData, "User/a/state", "0");
    }
    else if (value == "0"){
      myservo.write(0);
      //Firebase.setString("User/a/state", "1");
    }
  }
  else
  {
    Serial.println(firebaseData.errorReason()); // 에러 메시지 출력
  }
  delay(500); // 0.5초마다 반복

} 
