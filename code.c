#include "FirebaseESP8266.h" // 파이어베이스 라이브러리
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define FIREBASE_HOST "host"
#define FIREBASE_AUTH "pw" // 데이터베이스 비밀번호

FirebaseData firebaseData;
FirebaseJson json;

const char* ssid = "iptime"; // should be changed
const char* pass = "rjsemfwlak"; // should be changed

ESP8266WebServer server(80);
Servo myservo;

//void userCreate(void){
//  
//}
//
//void userLoad(void){
//  
//}

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

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  //firebaseData.setBSSLBufferSize(1024, 1024);
  //Set the size of HTTP response buffers in the case where we want to work with large data.
  //firebaseData.setResponseSize(1024);
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  //Firebase.setInt("haha",1);
  //Firebase.stream("/User/a")
  myservo.attach(D5);   // Servo attached to D5 pin
  myservo.write(0);
}
 
void loop(void){
//   if (Firebase.failed()) {
//    Serial.println("streaming error");
//    Serial.println(Firebase.error());
//  }
//  
//  if (Firebase.available()) {
//     FirebaseDataObject event = Firebase.readEvent();
//     String eventType = event.getString("type");
//     eventType.toLowerCase();
//     
//     Serial.print("event: ");
//     Serial.println(eventType);
//     if (eventType == "put") {
//       Serial.print("data: ");
//       Serial.println(event.getString("data"));
//       String path = event.getString("path");
//       String data = event.getString("data");
//      Serial.println(path);
//     }
//  }   
  if (Firebase.getString(firebaseData, "User/a/state")) // 해당하는 key가 있으면 (앱 인벤터에서는 tag)
  {
    String value = firebaseData.stringData(); // 값을 문자열로 받아와서 value에
    Serial.println(value); // 시리얼모니터에 값을 출력
    
    if (value == "1"){
      Serial.println("ON");
      myservo.write(90);
      //Firebase.Set
    }
    else if (value == "0"){
      Serial.println("OFF");
      myservo.write(0);
    }
  }
  else
  {
    Serial.println(firebaseData.errorReason()); // 에러 메시지 출력
  }
  delay(1000); // 1초마다 반복

} 
