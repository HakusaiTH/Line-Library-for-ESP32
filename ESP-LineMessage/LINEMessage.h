#ifndef LINEMESSAGE_H
#define LINEMESSAGE_H

#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClientSecure.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <HTTPClient.h>
  #include <WiFiClientSecure.h>
#endif

class LINEMessage {
  public:
    LINEMessage(const String& token, const String& userId);
    void sendMessage(const String& message);
    void sendSticker(const String& stickerId);
    void sendImage(const String& originalContentUrl, const String& previewImageUrl);
    
  private:
    String _token;
    String _userId;
};

#endif // LINEMESSAGE_H
