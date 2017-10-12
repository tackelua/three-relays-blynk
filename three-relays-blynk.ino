/*************************************************************
Blynk project.
Open this link and project will be auto creat on blynk-cloud
http://tinyurl.com/yd3zle46
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DEBUG Serial
#define DB(x) Serial.println(x)
#define Db(x) Serial.print(x)

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char BLYNK_AUTH[] = "1e72d2ce724743ff98e3817d07a76edb";
WidgetTerminal Terminal(V0);
// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "YourNetworkName";
//char pass[] = "YourPassword";

#define R1 D2
#define R2 D5
#define R3 D6


void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  wifi_init();
  digitalWrite(LED_BUILTIN, HIGH);

  Blynk.config(BLYNK_AUTH, "blynk-cloud.com", 8442);
  Serial.println(F("Connect to Blynk server"));
  while (!Blynk.connect()) {
    Serial.print(F("."));
    delay(50);
  }
  
  Blynk.syncAll();
}

void loop()
{
  Blynk.run();
}

void wifi_init() {
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.mode(WIFI_STA);

  //Serial.println(F("SmartConfig started."));
  //WiFi.beginSmartConfig();
  //while (1) {
  //  delay(1000);
  //  if (WiFi.smartConfigDone()) {
  //    Serial.println(F("SmartConfig: Success"));
  //    WiFi.printDiag(Serial);
  //    //WiFi.stopSmartConfig();
  //    break;
  //  }
  //}

  WiFi.printDiag(Serial);

  Serial.println(F("\nConnecting..."));

  if (WiFi.waitForConnectResult() == WL_CONNECTED)
  {
    Serial.println(F("connected\n"));
  }
  else
  {
    Serial.println(F("connect again\n"));
    if (WiFi.waitForConnectResult() == WL_CONNECTED)
    {
      Serial.println(F("connected\n"));
      return;
    }

    Serial.println(F("SmartConfig started."));
    WiFi.beginSmartConfig();
    while (1) {
      delay(500);
      if (WiFi.smartConfigDone()) {
        Serial.println(F("SmartConfig: Success"));
        WiFi.printDiag(Serial);
        //WiFi.stopSmartConfig();
        break;
      }
    }
  }
}

BLYNK_WRITE(V1) {
  int buttonStt = param.asInt();
  digitalWrite(R1, buttonStt);
  Blynk.virtualWrite(V11, buttonStt);
  Terminal.print("#V1: ");
  Terminal.println(buttonStt);
  Terminal.flush();
  Db(F("#V1: "));
  DB(buttonStt);
}
BLYNK_WRITE(V2) {
  int buttonStt = param.asInt();
  digitalWrite(R2, buttonStt);
  Blynk.virtualWrite(V12, buttonStt);
  Terminal.print("#V2: ");
  Terminal.println(buttonStt);
  Terminal.flush();
  Db(F("#V2: "));
  DB(buttonStt);
}
BLYNK_WRITE(V3) {
  int buttonStt = param.asInt();
  digitalWrite(R3, buttonStt);
  Blynk.virtualWrite(V13, buttonStt);
  Terminal.print("#V3: ");
  Terminal.println(buttonStt);
  Terminal.flush();
  Db(F("#V3: "));
  DB(buttonStt);
}
//====

BLYNK_WRITE(V11) {
  int buttonStt = param.asInt();
  digitalWrite(R1, buttonStt);
  Blynk.virtualWrite(V1, buttonStt);
  Terminal.print("#V11: ");
  Terminal.println(buttonStt);
  Terminal.flush();
  Db(F("#V11: "));
  DB(buttonStt);
}
BLYNK_WRITE(V12) {
  int buttonStt = param.asInt();
  digitalWrite(R2, buttonStt);
  Blynk.virtualWrite(V2, buttonStt);
  Terminal.print("#V12: ");
  Terminal.println(buttonStt);
  Terminal.flush();
  Db(F("#V12: "));
  DB(buttonStt);
}
BLYNK_WRITE(V13) {
  int buttonStt = param.asInt();
  digitalWrite(R3, buttonStt);
  Blynk.virtualWrite(V3, buttonStt);
  Terminal.print("#V13: ");
  Terminal.println(buttonStt);
  Terminal.flush();
  Db(F("#V13: "));
  DB(buttonStt);
}
