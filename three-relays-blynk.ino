/*************************************************************
Blynk project.
Open this link and project will be auto created on blynk-cloud
http://tinyurl.com/yd3zle46
 *************************************************************/

 /* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <BlynkSimpleEsp8266.h>

ESP8266WiFiMulti wifiMulti;

#define DEBUG Serial
#define DB(x) Serial.println(x)
#define Db(x) Serial.print(x) 

//server Gith
//char BLYNK_AUTH[] = "13849dbd56804695b91e63f34f85e0e1";
char BLYNK_AUTH[] = "6277cbbac56e48eab1a982b3bce7ee46";
char BLYNK_DOMAIN[] = "10.210.6.73";

//server blynk
//char BLYNK_AUTH[] = "13f528fc01334179874d55be89d04dc1";
//char BLYNK_DOMAIN[] = "blynk-cloud.com";

int	 BLYNK_PORT = 8442;
WidgetTerminal Terminal(V0);
// Your WiFi credentials.
// Set password to "" for open networks.

//char ssid[] = "Dingtea T2_sau";
//char pass[] = "133nguyenvanlinh";

#define R1 D2
#define R2 D6
#define R3 D5


typedef enum {
	SMARTCONFIG = 1,
	WIFIMULTI = 2
} WiFi_Setup_Mode_t;

void wifi_init(int mode) {
	WiFi.setAutoConnect(true);
	WiFi.setAutoReconnect(true);
	WiFi.mode(WIFI_STA);

	if (mode == SMARTCONFIG)
	{
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

		//WiFi.begin("Nokia 6", "mic12345678");
		WiFi.printDiag(Serial);
		Serial.println(F("\nConnecting..."));
		if (WiFi.waitForConnectResult() == WL_CONNECTED)
		{
			Serial.println(F("connected\n"));
		}
		else
		{
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

	else if (mode = WIFIMULTI)
	{
		wifiMulti.addAP("MIC", "");
		wifiMulti.addAP("DTU", "");
		//wifiMulti.addAP("IoT Wifi", "mic@dtu12345678()");
		//wifiMulti.addAP("Nokia 6", "mic12345678");
		//wifiMulti.addAP("GithAP", "giathinh123");
		Serial.println("Connecting Wifi...");
		bool ledStt = false;
		while (wifiMulti.run() != WL_CONNECTED) {
			delay(50);
			ledStt = !ledStt;
			digitalWrite(LED_BUILTIN, ledStt);
		}
		Serial.println("");
		Serial.println("WiFi connected");
		Serial.println("IP address: ");
		Serial.println(WiFi.localIP());
	}
}

BLYNK_WRITE(V1) {
	int buttonStt = param.asInt();
	digitalWrite(R1, buttonStt);
	Blynk.virtualWrite(V11, buttonStt);
	Db(F("#V1: "));
	DB(buttonStt);
	Terminal.print("#V1: ");
	Terminal.println(buttonStt);
	Terminal.flush();
}
BLYNK_WRITE(V2) {
	int buttonStt = param.asInt();
	digitalWrite(R2, buttonStt);
	Blynk.virtualWrite(V12, buttonStt);
	Db(F("#V2: "));
	DB(buttonStt);
	Terminal.print("#V2: ");
	Terminal.println(buttonStt);
	Terminal.flush();
}
BLYNK_WRITE(V3) {
	int buttonStt = param.asInt();
	digitalWrite(R3, buttonStt);
	Blynk.virtualWrite(V13, buttonStt);
	Db(F("#V3: "));
	DB(buttonStt);
	Terminal.print("#V3: ");
	Terminal.println(buttonStt);
	Terminal.flush();
}
//====

BLYNK_WRITE(V11) {
	int buttonStt = param.asInt();
	digitalWrite(R1, buttonStt);
	Blynk.virtualWrite(V1, buttonStt);
	Db(F("#V11: "));
	DB(buttonStt);
	Terminal.print("#V11: ");
	Terminal.println(buttonStt);
	Terminal.flush();
}
BLYNK_WRITE(V12) {
	int buttonStt = param.asInt();
	digitalWrite(R2, buttonStt);
	Blynk.virtualWrite(V2, buttonStt);
	Db(F("#V12: "));
	DB(buttonStt);
	Terminal.print("#V12: ");
	Terminal.println(buttonStt);
	Terminal.flush();
}
BLYNK_WRITE(V13) {
	int buttonStt = param.asInt();
	digitalWrite(R3, buttonStt);
	Blynk.virtualWrite(V3, buttonStt);
	Db(F("#V13: "));
	DB(buttonStt);
	Terminal.print("#V13: ");
	Terminal.println(buttonStt);
	Terminal.flush();
}


//=======================================

void setup()
{
	// Debug console
	Serial.begin(74880);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(R1, OUTPUT);
	pinMode(R2, OUTPUT);
	pinMode(R3, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	//WiFi.begin(ssid, pass);
	wifi_init(WIFIMULTI);
	digitalWrite(LED_BUILTIN, HIGH);

	Blynk.config(BLYNK_AUTH, BLYNK_DOMAIN, BLYNK_PORT);
	Serial.println(F("Connect to Blynk server"));
	while ((wifiMulti.run() != WL_CONNECTED) && (!Blynk.connect())) {
		Serial.print(F("."));
		delay(50);
	}

	Blynk.syncAll();
	Terminal.println(BLYNK_AUTH);
}

void loop()
{
	if (wifiMulti.run() != WL_CONNECTED) {
		delay(1);
		return;
	}
	Blynk.run();
	delay(1);
}