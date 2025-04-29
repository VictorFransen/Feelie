#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "Feelie";
char pass[] = "Linde_Victor";

IPAddress serverIP(192, 168, 4, 1);

const int BlijPin = 2;
const int StressPin = 3;
const int VraagPin = 4;
const int BangPin = 5;
const int DroevigPin = 6;
const int BoosPin = 7;

int BlijStatus = 0;
int StressStatus = 0;
int VraagStatus = 0;
int BangStatus = 0;
int DroevigStatus = 0;
int BoosStatus = 0;

int LaatsteBlij = LOW;
int LaatsteStress = LOW;
int LaatsteVraag = LOW;
int LaatsteBang = LOW;
int LaatsteDroevig = LOW;
int LaatsteBoos = LOW;

int lastDebounceTime = 0;
const int debounceTime = 50;

int BlijKnop = HIGH;
int StressKnop = HIGH;
int VraagKnop = HIGH;
int BangKnop = HIGH;
int DroevigKnop = HIGH;
int BoosKnop = HIGH;

void setup() {
  Serial.begin(9600);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("Verbonden met Access Point!");

  pinMode(BlijPin, INPUT_PULLUP);
  pinMode(StressPin, INPUT_PULLUP);
  pinMode(VraagPin, INPUT_PULLUP);
  pinMode(BangPin, INPUT_PULLUP);
  pinMode(DroevigPin, INPUT_PULLUP);
  pinMode(BoosPin, INPUT_PULLUP);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A1, OUTPUT);
}

void loop() {
  BlijStatus = digitalRead(BlijPin);
  StressStatus = digitalRead(StressPin);
  VraagStatus = digitalRead(VraagPin);
  BangStatus = digitalRead(BangPin);
  DroevigStatus = digitalRead(DroevigPin);
  BoosStatus = digitalRead(BoosPin);

  if (BlijStatus != LaatsteBlij || StressStatus != LaatsteStress || VraagStatus != LaatsteVraag ||
      BangStatus != LaatsteBang || DroevigStatus != LaatsteDroevig || BoosStatus != LaatsteBoos) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceTime) {

    if (BlijStatus != BlijKnop) {
      BlijKnop = BlijStatus;
      if (BlijKnop == HIGH) {
        speelAnimatie();
        WiFiClient client;
        if (client.connect(serverIP, 80)) {
          client.println("Blij1\n");
          client.stop();
        }
      }
    }

    if (StressStatus != StressKnop) {
      StressKnop = StressStatus;
      if (StressKnop == HIGH) {
        speelAnimatie();
        WiFiClient client;
        if (client.connect(serverIP, 80)) {
          client.println("Stress1\n");
          client.stop();
        }
      }
    }

    if (VraagStatus != VraagKnop) {
      VraagKnop = VraagStatus;
      if (VraagKnop == HIGH) {
        speelAnimatie();
        WiFiClient client;
        if (client.connect(serverIP, 80)) {
          client.println("Vraag1\n");
          client.stop();
        }
      }
    }

    if (BangStatus != BangKnop) {
      BangKnop = BangStatus;
      if (BangKnop == HIGH) {
        speelAnimatie();
        WiFiClient client;
        if (client.connect(serverIP, 80)) {
          client.println("Bang1\n");
          client.stop();
        }
      }
    }

    if (DroevigStatus != DroevigKnop) {
      DroevigKnop = DroevigStatus;
      if (DroevigKnop == HIGH) {
        speelAnimatie();
        WiFiClient client;
        if (client.connect(serverIP, 80)) {
          client.println("Droevig1\n");
          client.stop();
        }
      }
    }

    if (BoosStatus != BoosKnop) {
      BoosKnop = BoosStatus;
      if (BoosKnop == HIGH) {
        speelAnimatie();
        Serial.println("Boos");
        WiFiClient client;
        if (client.connect(serverIP, 80)) {
          client.println("Boos1\n");
          client.stop();
        }
      }
    }
  }

  LaatsteBlij = BlijStatus;
  LaatsteStress = StressStatus;
  LaatsteVraag = VraagStatus;
  LaatsteBang = BangStatus;
  LaatsteDroevig = DroevigStatus;
  LaatsteBoos = BoosStatus;
}

void speelAnimatie() {
  for (int a = 8; a < 13; a++) {
    digitalWrite(a, HIGH);
    delay(50);
    digitalWrite(a, LOW);
  }
  digitalWrite(A1, HIGH);
  delay(50);
  digitalWrite(A1, LOW);
}