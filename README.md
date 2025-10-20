# 📱 ESP-LineMessage Library for ESP32 / ESP8266

ไลบรารี **LINE Messaging API สำหรับ ESP32 / ESP8266**
ช่วยให้คุณสามารถส่งข้อความ, รูปภาพ, และสติ๊กเกอร์ ไปยัง LINE ได้อย่างง่ายดายผ่านโค้ด Arduino เพียงไม่กี่บรรทัด 🚀

---

## ✨ คุณสมบัติหลัก

* ✅ รองรับ **ESP32** และ **ESP8266**
* 💬 ส่งข้อความ LINE ได้โดยตรงผ่าน HTTPS
* 🖼️ รองรับการส่งรูปภาพ (Image)
* 😄 รองรับการส่งสติ๊กเกอร์ (Sticker)
* 🔒 ใช้ `WiFiClientSecure` สำหรับ HTTPS (ตั้งค่า `setInsecure()` เพื่อข้าม SSL verify)
* ⚙️ เขียนโค้ดง่าย ใช้คลาสเดียว `LINEMessage`

---

## 📁 โครงสร้างไฟล์

```
ESP-LineMessage/
├── LINEMessage.cpp
├── LINEMessage.h
└── examples/
    └── ESP-LineMessage-example/
        └── ESP-LineMessage-example.ino
```

> ⚠️ ต้องวางโฟลเดอร์ `ESP-LineMessage` ไว้ใน
> `Documents/Arduino/libraries/` เพื่อให้ Arduino IDE มองเห็น

---

## ⚙️ การติดตั้ง

1. เปิดโฟลเดอร์ `Documents/Arduino/libraries/`
2. คัดลอกโฟลเดอร์ `ESP-LineMessage` ไปวางในนั้น
3. เปิด Arduino IDE → เมนู **Sketch → Include Library → ESP-LineMessage**
   ถ้ามีชื่อในรายการแสดงว่าติดตั้งสำเร็จ ✅

---

## 💡 ตัวอย่างโค้ด

```cpp
#include <Arduino.h>
#include "LINEMessage.h"

// ตั้งค่า WiFi และ LINE Token
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASS";
String LINE_ACCESS_TOKEN = "YOUR_LINE_ACCESS_TOKEN";
String USER_ID = "YOUR_LINE_USER_ID"; // หรือ Group ID

// สร้าง instance
LINEMessage line(LINE_ACCESS_TOKEN, USER_ID);

void setup() {
  Serial.begin(115200);

  // เชื่อมต่อ WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // ✅ ส่งข้อความ
  line.sendMessage("Hello from ESP!");

  // ✅ ส่งสติ๊กเกอร์ (packageId 446)
  line.sendSticker("1988");

  // ✅ ส่งภาพ
  line.sendImage(
    "https://example.com/original.jpg",
    "https://example.com/original.jpg"
  );
}

void loop() {
  // โค้ดอื่น ๆ ของคุณ
}
```

---

## 📡 ฟังก์ชันที่มี

| ฟังก์ชัน                     | รายละเอียด                                               |
| ---------------------------- | -------------------------------------------------------- |
| `LINEMessage(token, userId)` | สร้างอ็อบเจกต์ใหม่ด้วย Token และ User ID                 |
| `sendMessage("ข้อความ")`     | ส่งข้อความตัวอักษร                                       |
| `sendSticker("stickerId")`   | ส่งสติ๊กเกอร์ (packageId 446)                            |
| `sendImage(url, preview)`    | ส่งภาพจาก URL                                            |
| *(อัตโนมัติ)*                | ใช้ HTTPS (`WiFiClientSecure`) และมีการตรวจสอบสถานะ WiFi |

---

## 🧠 ตัวอย่าง Sticker ID

LINE มีสติ๊กเกอร์มากมาย ลองใช้ package 446 ที่เป็น default เช่น:

| Sticker ID | หมายถึง              |
| ---------- | -------------------- |
| `1988`     | Brown ยิ้ม           |
| `1989`     | Brown หัวเราะ        |
| `1990`     | Cony เขิน            |
| `1991`     | Brown/Cony รักกัน ❤️ |

---

## 🛠️ การสร้างและตั้งค่า LINE Official Account

### 1. สร้าง LINE OA

1. เข้า [https://account.line.biz/](https://account.line.biz/)
2. กด **Create New** → ตั้งชื่อ / ข้อมูล OA ของคุณ
3. ไปที่ **LINE Official Account Manager**

### 2. เปิดใช้งาน Messaging API

1. เข้าหน้า **Messaging API**
2. คลิก **Use Messaging API**
3. สร้าง Provider ใหม่ (ใส่ชื่ออะไรก็ได้)
4. คลิก **OK** เพื่อยืนยัน
5. จากนั้นไปที่ **LINE Developers Console**

---

## ⚙️ ตั้งค่าใน LINE Developers Console

1. เข้า [https://developers.line.biz/](https://developers.line.biz/)
2. เลือก Provider → เลือก Channel
3. ไปที่แท็บ **Messaging API**
4. กดปุ่ม **Issue Channel Access Token**
5. คัดลอก token ไปใส่ในโค้ด Arduino

   ```cpp
   String LINE_ACCESS_TOKEN = "YOUR_CHANNEL_ACCESS_TOKEN";
   ```

---

## 🆔 วิธีหา User ID / Group ID

### 🔹 วิธีดู User ID ด้วย Webhook

1. ใช้เว็บ [https://typedwebhook.tools/](https://typedwebhook.tools/)
2. คัดลอกลิงก์ Webhook ไปใส่ใน **LINE Developers → Webhook URL**
3. กด Save แล้วทดสอบส่งข้อความมาที่ OA
4. กลับมาดูใน typedwebhook.tools → จะเห็น JSON
   ดูในฟิลด์ `source.userId`

### 🔹 วิธีดู Group ID

1. เชิญ LINE OA ของคุณเข้ากลุ่ม
2. ส่งข้อความในกลุ่ม
3. กลับมาดูใน typedwebhook.tools → ดูฟิลด์ `source.groupId`

---

## 🧩 การใช้งานจริง

| กรณีใช้งาน           | ตัวอย่าง                                 |
| -------------------- | ---------------------------------------- |
| แจ้งเตือน Sensor     | `line.sendMessage("Temperature High!");` |
| แจ้งเตือนผ่านรูปภาพ  | `line.sendImage(url, preview);`          |
| แจ้งเตือนแบบอารมณ์ดี | `line.sendSticker("1988");`              |

---

## 🔒 Dependencies

* WiFi.h / ESP8266WiFi.h
* HTTPClient.h / ESP8266HTTPClient.h
* WiFiClientSecure.h

> ติดตั้งโดยอัตโนมัติเมื่อใช้ Arduino Core for ESP32 / ESP8266

---

## 🧰 Supported Boards

* ✅ ESP32
* ✅ ESP8266 (NodeMCU, Wemos, ฯลฯ)

---

## 📄 License

MIT License © 2025
Created by **Phoovadet (NoobDev)**
[GitHub: @phoovadetnoobdev](https://github.com/phoovadetnoobdev)
