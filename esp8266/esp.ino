#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "Wifi (-1)"
#define WIFI_PASSWORD "qku-1991"
#define API_KEY "AIzaSyDB3y0kaHF1hD9pBkRUoha9SnzVoPEiBnY"
#define DATABASE_URL "https://controller-app-1e70b-default-rtdb.asia-southeast1.firebasedatabase.app/" 

#define pianoRelay D0
bool valuePiano;

// notes and value
#define noteDo D1
#define noteRe D2
#define noteMi D3
#define noteFa D4
#define noteSol D5
#define noteLya D6
#define noteSi D7
bool valueDo;
bool valueRe;
bool valueMi;
bool valueFa;
bool valueSol;
bool valueLya;
bool valueSi;

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

void setup() {
  pinMode(pianoRelay, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("okay");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

// Piano (de)activate 
void pianoAndNotes() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/controller/piano")) {
      if (fbdo.dataType() == "boolean") {
        valuePiano = fbdo.intData();
        Serial.println(valuePiano);
        if(valuePiano == true) {
          digitalWrite(pianoRelay, LOW);
        } else {
          digitalWrite(pianoRelay, HIGH);          
        }
      }
    }
    else if (Firebase.RTDB.getInt(&fbdo, "/controller/notes/do") || Firebase.RTDB.getInt(&fbdo, "/controller/notes/re") || Firebase.RTDB.getInt(&fbdo, "/controller/notes/mi") || Firebase.RTDB.getInt(&fbdo, "/controller/notes/fa") || Firebase.RTDB.getInt(&fbdo, "/controller/notes/sol") || Firebase.RTDB.getInt(&fbdo, "/controller/notes/lya") || Firebase.RTDB.getInt(&fbdo, "/controller/notes/si")) {
      
      // do
       if (Firebase.RTDB.getInt(&fbdo, "/controller/notes/do")) {
          if (fbdo.dataType() == "boolean") {
            valueDo = fbdo.intData();
            Serial.println(valueDo);
            if(valueDo == true) {
              digitalWrite(noteDo, LOW);
            } else {
              digitalWrite(noteDo, HIGH);          
            }
          }
        }

        // re
        if (Firebase.RTDB.getInt(&fbdo, "/controller/notes/re")) {
          if (fbdo.dataType() == "boolean") {
            valueRe = fbdo.intData();
            Serial.println(valueRe);
            if(valueRe == true) {
              digitalWrite(noteRe, LOW);
            } else {
              digitalWrite(noteRe, HIGH);          
            }
          }
        }

        // mi
        if (Firebase.RTDB.getInt(&fbdo, "/controller/notes/mi")) {
          if (fbdo.dataType() == "boolean") {
            valueMi = fbdo.intData();
            Serial.println(valueMi);
            if(valueMi == true) {
              digitalWrite(noteMi, LOW);
            } else {
              digitalWrite(noteMi, HIGH);          
            }
          }
        }

        // fa
        if (Firebase.RTDB.getInt(&fbdo, "/controller/notes/fa")) {
          if (fbdo.dataType() == "boolean") {
            valueFa = fbdo.intData();
            Serial.println(valueFa);
            if(valueFa == true) {
              digitalWrite(noteFa, LOW);
            } else {
              digitalWrite(noteFa, HIGH);          
            }
          }
        }

        // sol
        if (Firebase.RTDB.getInt(&fbdo, "/controller/notes/sol")) {
          if (fbdo.dataType() == "boolean") {
            valueSol = fbdo.intData();
            Serial.println(valueSol);
            if(valueSol == true) {
              digitalWrite(noteSol, LOW);
            } else {
              digitalWrite(noteSol, HIGH);          
            }
          }
        }

        // lya
        if (Firebase.RTDB.getInt(&fbdo, "/controller/notes/lya")) {
          if (fbdo.dataType() == "boolean") {
            valueLya = fbdo.intData();
            Serial.println(valueLya);
            if(valueLya == true) {
              digitalWrite(noteLya, LOW);
            } else {
              digitalWrite(noteLya, HIGH);          
            }
          }
        }

        // si
        if (Firebase.RTDB.getInt(&fbdo, "/controller/notes/si")) {
          if (fbdo.dataType() == "boolean") {
            valueSi = fbdo.intData();
            Serial.println(valueSi);
            if(valueSi == true) {
              digitalWrite(noteSi, LOW);
            } else {
              digitalWrite(noteSi, HIGH);          
            }
          }
        }

      } else {
        Serial.println(fbdo.errorReason());
      }
  }
}


void loop() {
  pianoAndNotes();
}