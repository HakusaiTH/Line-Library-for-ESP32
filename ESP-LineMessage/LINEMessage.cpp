#include "LINEMessage.h"

LINEMessage::LINEMessage(const String& token, const String& userId)
  : _token(token), _userId(userId) {}

// ฟังก์ชันส่งข้อความไปยังผู้ใช้ LINE
void LINEMessage::sendMessage(const String& message) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;  // ใช้ WiFiClientSecure เพื่อรองรับ HTTPS
    client.setInsecure();  // ละเว้นการตรวจสอบใบรับรอง SSL
    HTTPClient http;
    String url = "https://api.line.me/v2/bot/message/push";

    http.begin(client, url);
    http.addHeader("Authorization", "Bearer " + _token);
    http.addHeader("Content-Type", "application/json");

    String data = "{\"to\":\"" + _userId + "\",\"messages\":[{\"type\":\"text\",\"text\":\"" + message + "\"}]}";
    int httpResponseCode = http.POST(data);
    
    if (httpResponseCode == 200) {
      Serial.println("Message sent successfully!");
    } else {
      Serial.print("Error sending message. HTTP response code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Error: Not connected to WiFi.");
  }
}

// ฟังก์ชันส่งสติ๊กเกอร์
void LINEMessage::sendSticker(const String& stickerId) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;  // ใช้ WiFiClientSecure เพื่อรองรับ HTTPS
    client.setInsecure();  // ละเว้นการตรวจสอบใบรับรอง SSL
    HTTPClient http;
    String url = "https://api.line.me/v2/bot/message/push";

    http.begin(client, url);
    http.addHeader("Authorization", "Bearer " + _token);
    http.addHeader("Content-Type", "application/json");

    String data = "{\"to\":\"" + _userId + "\",\"messages\":[{\"type\":\"sticker\",\"packageId\":\"446\",\"stickerId\":\"" + stickerId + "\"}]}";
    int httpResponseCode = http.POST(data);
    
    if (httpResponseCode == 200) {
      Serial.println("Sticker sent successfully!");
    } else {
      Serial.print("Error sending sticker. HTTP response code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Error: Not connected to WiFi.");
  }
}

// ฟังก์ชันส่งภาพ
void LINEMessage::sendImage(const String& originalContentUrl, const String& previewImageUrl) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;  // ใช้ WiFiClientSecure เพื่อรองรับ HTTPS
    client.setInsecure();  // ละเว้นการตรวจสอบใบรับรอง SSL
    HTTPClient http;
    String url = "https://api.line.me/v2/bot/message/push";

    http.begin(client, url);
    http.addHeader("Authorization", "Bearer " + _token);
    http.addHeader("Content-Type", "application/json");

    String data = "{\"to\":\"" + _userId + "\",\"messages\":[{\"type\":\"image\",\"originalContentUrl\":\"" + originalContentUrl + "\",\"previewImageUrl\":\"" + previewImageUrl + "\"}]}";
    int httpResponseCode = http.POST(data);
    
    if (httpResponseCode == 200) {
      Serial.println("Image sent successfully!");
    } else {
      Serial.print("Error sending image. HTTP response code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Error: Not connected to WiFi.");
  }
}
