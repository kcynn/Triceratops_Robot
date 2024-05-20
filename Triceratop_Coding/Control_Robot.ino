#include <WiFi.h>
#include <PubSubClient.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <SCServo.h>
#include <math.h>

SCSCL sc;

// Wi-Fi settings
const char* ssid = "your wifi";
const char* password = "your password";

// MQTT settings
const char* mqtt_server = "broker.hivemq.com";  // Example HiveMQ broker
const char* mqtt_topic = "Triceratops";

WiFiClient espClient;
PubSubClient client(espClient);
DFRobotDFPlayerMini myDFPlayer;
SoftwareSerial mySoftwareSerial(3, 2);  // RX, TX for DFPlayer Mini

bool walking = false;
bool isPlaying = false;      // Track the playing status
bool mqttConnected = false;  // Track the MQTT connection status
bool shaking = false;        // ตัวแปรสถานะการเขย่าหัว

unsigned long previousMillis = 0;
 
const long interval = 100;

// การตั้งค่าเครือข่ายประสาทเทียม
#define C1_MAX 0.05
#define C1_MIN -0.05
#define C2_MAX 0.05
#define C2_MIN -0.05
#define C3_MAX 0.05
#define C3_MIN -0.05
#define C4_MAX 0.05
#define C4_MIN -0.05

#define A 626
#define B 320
#define C 706
#define D 450
#define E 755
#define F 340
#define G 620
#define H 350
#define I 290
#define J 550

float C1[8];
float C2[8];
float O1[8];
float O2[8];
float C3[8];
float O3[8];
float C4[8];
float O4[8];

float alpha = 1.08;
float phi = M_PI / 9.0;
float W11 = alpha * cos(phi), W12 = alpha * sin(phi), W21 = -alpha * sin(phi), W22 = alpha * cos(phi), W31 = alpha * cos(phi), W32 = alpha * sin(phi), W41 = -alpha * sin(phi), W42 = alpha * cos(phi);

int i = 1;

float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}





void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // Convert payload to String
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // ตรวจสอบข้อความที่รับเข้ามาและดำเนินการตามที่กำหนด
  if (message == "playsound" && !isPlaying) {
    Serial.println("Play Song");
    myDFPlayer.play(2);  // เล่นเพลงที่ตำแหน่งที่ 2 (ปรับตำแหน่งตามต้องการ)
    isPlaying = true;
  } else if (message == "shakehead" && !shaking) {
    Serial.println("Shake a Head");
    shaking = true;  // ตั้งค่าสถานะการเขย่าหัวเป็น true เพื่อเข้าสู่โหมดการเขย่าหัว
  } else if (message == "forward" && !walking) {
    Serial.println("Walking ");
    walking = true;
  } else if (message == "stop") {
    Serial.println("Stop");
    myDFPlayer.stop();
    sc.RegWritePos(5, 452, 0, 800);  // ทำให้หัวหยุดเขย่า
    sc.RegWriteAction();
    sc.RegWritePos(1, 426, 0, 800);
    sc.RegWritePos(2, 597, 0, 800);
    sc.RegWritePos(6, 597, 0, 500);
    sc.RegWritePos(7, 426, 0, 500);
    sc.RegWritePos(3, 426, 0, 500);
    sc.RegWritePos(4, 568, 0, 500);
    sc.RegWritePos(8, 597, 0, 500);
    sc.RegWritePos(9, 426, 0, 500);
    sc.RegWritePos(5, 426, 0, 500);
    sc.RegWriteAction();
    delay(10000);
    isPlaying = false;  // ออกจากโหมดเล่นเพลง
    shaking = false;    // ออกจากโหมดการเขย่าหัว
    walking = false;    // ออกจากโหมดเดิน
  }
}


void reconnect() {
  while (!client.connected()) {
    if (!mqttConnected) {
      Serial.print("Attempting MQTT connection...");
    }
    if (client.connect("ArduinoClient")) {
      if (!mqttConnected) {
        Serial.println("connected");
        mqttConnected = true;
      }
      client.subscribe(mqtt_topic);
    } else {
      if (mqttConnected) {
        mqttConnected = false;
      }
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("SD Card fail");
    while (true)
      ;  // Halt the program if initialization fails
  }
  Serial.println("DFPlayer Mini online.");
  myDFPlayer.volume(30);  // Set volume level (0 to 30)

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.begin(115200);
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  delay(1000);

  sc.RegWritePos(5, 452, 0, 800);
  sc.RegWriteAction();
  delay(10000);  //[(P1-P0)/V]*1000+100

  //ใส่โค๊ดยืน
  // ตำแหน่งเริ่มต้นสำหรับเซอร์โวมอเตอร์ (ตำแหน่งยืน)
  sc.RegWritePos(1, 426, 0, 800);
  sc.RegWritePos(2, 597, 0, 800);
  sc.RegWritePos(6, 597, 0, 500);
  sc.RegWritePos(7, 426, 0, 500);
  sc.RegWritePos(3, 426, 0, 500);
  sc.RegWritePos(4, 568, 0, 500);
  sc.RegWritePos(8, 597, 0, 500);
  sc.RegWritePos(9, 426, 0, 500);
  sc.RegWritePos(5, 426, 0, 500);
  sc.RegWriteAction();
  delay(10000);

  // การเริ่มต้นเครือข่ายประสาทเทียม
  C1[0] = 0.05;
  C2[0] = 0.05;
  C3[0] = 0.05;
  C4[0] = 0.05;
  O1[0] = tanh(C1[0]);
  O2[0] = tanh(C2[0]);
  O3[0] = tanh(C3[0]);
  O4[0] = tanh(C4[0]);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    // ทำงานในส่วนของการเขย่าหัวอย่างต่อเนื่อง
    C1[i] = (O1[i - 1] * W11) + (O2[i - 1] * W21);
    O1[i] = tanh(C1[i]);
    C2[i] = (O2[i - 1] * W22) + (O1[i - 1] * W12);
    O2[i] = tanh(C2[i]);
    C3[i] = (O3[i - 1] * W31) + (O4[i - 1] * W41);
    O3[i] = tanh(C3[i]);
    C4[i] = (O4[i - 1] * W42) + (O3[i - 1] * W32);
    O4[i] = tanh(C4[i]);

    if (shaking) {
      // // ทำงานในส่วนของการเขย่าหัวอย่างต่อเนื่อง
      // C1[i] = (O1[i-1] * W11) + (O2[i-1] * W21);
      // O1[i] = tanh(C1[i]);
      // C2[i] = (O2[i-1] * W22) + (O1[i-1] * W12);
      // O2[i] = tanh(C2[i]);
      // C3[i] = (O3[i-1] * W31) + (O4[i-1] * W41);
      // O3[i] = tanh(C3[i]);
      // C4[i] = (O4[i-1] * W42) + (O3[i-1] * W32);
      // O4[i] = tanh(C4[i]);
      float pos9 = map(O2[i - 1], -1, 1, J, I);
      sc.RegWritePos(5, (int)pos9, 0, 50);
      //delay(100);
    }
    if (walking) {
      // // การคำนวณเครือข่ายประสาทเทียม
      // C1[i] = (O1[i-1] * W11) + (O2[i-1] * W21);
      // O1[i] = tanh(C1[i]);
      // C2[i] = (O2[i-1] * W22) + (O1[i-1] * W12);
      // O2[i] = tanh(C2[i]);
      // C3[i] = (O3[i-1] * W31) + (O4[i-1] * W41);
      // O3[i] = tanh(C3[i]);
      // C4[i] = (O4[i-1] * W42) + (O3[i-1] * W32);
      // O4[i] = tanh(C4[i]);


      // การแปลงค่าผลลัพธ์ของเครือข่ายประสาทเทียมไปยังตำแหน่งเซอร์โว
      float pos1 = map(O2[i], -1, 1, B + 140, A + 200);
      float pos2 = map(O2[i - 1], -1, 1, B, A);
      float pos3 = map(O4[i], -1, 1, D - 230, C - 150);
      float pos4 = map(O4[i - 1], -1, 1, D, C);
      float pos5 = map(O3[i], -1, 1, F - 170, E);
      float pos6 = map(O3[i - 1], -1, 1, F, E);
      float pos7 = map(O1[i], -1, 1, H + 100, G + 120);
      float pos8 = map(O1[i - 1], -1, 1, H, G);
      // ตัวอย่าง: การขยับเซอร์โวตามผลลัพธ์ของเครือข่ายประสาทเทียม
      sc.RegWritePos(6, (int)pos1, 0, 300);
      sc.RegWritePos(7, (int)pos2, 0, 300);
      sc.RegWritePos(1, (int)pos3, 0, 300);
      sc.RegWritePos(2, (int)pos4, 0, 300);
      sc.RegWritePos(3, (int)pos5, 0, 300);
      sc.RegWritePos(4, (int)pos6, 0, 300);
      sc.RegWritePos(8, (int)pos7, 0, 300);
      sc.RegWritePos(9, (int)pos8, 0, 300);
      //sc.RegWriteAction();

      // เพิ่มการหน่วงเวลาและการกระทำอื่นๆ ตามต้องการ
      //delay(100);
    }

        // การเพิ่มค่า index ของ loop และรีเซ็ต
    i++;
    if (i >= 8) {
      i = 1;  // รีเซ็ตเพื่อหลีกเลี่ยงการเข้าถึงอาร์เรย์นอกขอบเขต
      C1[0] = C1[7];
      C2[0] = C2[7];
      C3[0] = C3[7];
      C4[0] = C4[7];
      O1[0] = tanh(C1[0]);
      O2[0] = tanh(C2[0]);
      O3[0] = tanh(C3[0]);
      O4[0] = tanh(C4[0]);
    }
    sc.RegWriteAction();
  }
}