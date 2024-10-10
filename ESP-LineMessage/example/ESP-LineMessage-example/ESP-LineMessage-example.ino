#include <Arduino.h>
#include "LINEMessage.h"

// ข้อมูล WiFi และ LINE API
const char* ssid = "";
const char* password = "";
String LINE_ACCESS_TOKEN = "";
String USER_ID = "";

// สร้าง instance ของ LINEMessage
LINEMessage line(LINE_ACCESS_TOKEN, USER_ID);

void setup() {
  Serial.begin(115200);
  
  // เชื่อมต่อ WiFi (ผู้ใช้เขียนเอง)
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  
  // ตัวอย่างการส่งข้อความ
  line.sendMessage("Hello from ESP!");

  // ตัวอย่างการส่งสติ๊กเกอร์
  line.sendSticker("1988"); // ปรับ stickerId ตามต้องการ

  // ตัวอย่างการส่งภาพ
  line.sendImage("https://example.com/original.jpg", "https://example.com/original.jpg");
}

void loop() {
  // โค้ดหลักที่ทำงานอยู่ในลูป
}
