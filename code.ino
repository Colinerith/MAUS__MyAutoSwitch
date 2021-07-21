#include "FirebaseESP8266.h" // 파이어베이스 라이브러리
#include <Servo.h>
#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>

#define FIREBASE_HOST "/"
#define FIREBASE_AUTH "" // 데이터베이스 비밀번호

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
  //myservo.write(0);
}
int flag = 0; //0:off, 1:on

void loop(void){
  if (Firebase.getString(firebaseData, "Switch/a/state"))  {
    String value = firebaseData.stringData(); // 값을 문자열로 받아와서 value에
    //Serial.println(value); // 시리얼모니터에 값을 출력
    //Serial.println(myservo.read());
    if (value == "0"){
      if(flag == 1){ // on에서 off로 바뀐거면
        myservo.write(130);
        delay(1000);
        myservo.write(90);
        //Firebase.setStringAsync(firebaseData, "Switch/a/state", "0");
        flag = 0;
      }
      // 계속 off인 상태면 무시
    }
    else if (value == "1"){
      if(flag == 0){
        myservo.write(40);
        delay(1000);
        myservo.write(90);
        //Firebase.setString("Switch/a/state", "1");
        flag = 1;
      }
    }
  }
  else{
    Serial.println(firebaseData.errorReason()); // 에러 메시지 출력
  }
  delay(1000); // 1초마다 반복
} 
