#include <SPI.h>
#include <WiFiNINA.h>
 
// Netwerkgegevens
char ssid[] = "Feelie";
char pass[] = "Linde_Victor";
 
// IP van de server (AP)
IPAddress serverIP(192, 168, 4, 1);
 
// Knop pinnen
const int BlijPin = 2;
const int StressPin = 3;
const int VraagPin = 4;
const int BangPin = 5;
const int DroevigPin = 6;
const int BoosPin = 7;
 
// Knopstatus
int BlijStatus = 0;
int StressStatus = 0;
int VraagStatus = 0;
int BangStatus = 0;
int DroevigStatus = 0;
int BoosStatus = 0;
 
// Vorige status
int LaatsteBlij = LOW;
int LaatsteStress = LOW;
int LaatsteVraag = LOW;
int LaatsteBang = LOW;
int LaatsteDroevig = LOW;
int LaatsteBoos = LOW;
 
// Debounce
unsigned long lastDebounceTime = 0;
const int debounceTime = 50;
 
// Knoptoestand
int BlijKnop = HIGH;
int StressKnop = HIGH;
int VraagKnop = HIGH;
int BangKnop = HIGH;
int DroevigKnop = HIGH;
int BoosKnop = HIGH;
 
void setup() {
  Serial.begin(9600);
 
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
 
  // WiFi één keer verbinden
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nVerbonden met Access Point!");
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
        verzendEmotie("Blij");
      }
    }
 
    if (StressStatus != StressKnop) {
      StressKnop = StressStatus;
      if (StressKnop == HIGH) {
        speelAnimatie();
        verzendEmotie("Stress");
      }
    }
 
    if (VraagStatus != VraagKnop) {
      VraagKnop = VraagStatus;
      if (VraagKnop == HIGH) {
        speelAnimatie();
        verzendEmotie("Vraag");
      }
    }
 
    if (BangStatus != BangKnop) {
      BangKnop = BangStatus;
      if (BangKnop == HIGH) {
        speelAnimatie();
        verzendEmotie("Bang");
      }
    }
 
    if (DroevigStatus != DroevigKnop) {
      DroevigKnop = DroevigStatus;
      if (DroevigKnop == HIGH) {
        speelAnimatie();
        verzendEmotie("Droevig");
      }
    }
 
    if (BoosStatus != BoosKnop) {
      BoosKnop = BoosStatus;
      if (BoosKnop == HIGH) {
        speelAnimatie();
        verzendEmotie("Boos");
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
 
void verzendEmotie(String emotie) {
  const int maxRetries = 5;
  int poging = 0;
  bool success = false;
 
  while (poging < maxRetries && !success) {
    WiFiClient client;
 
    Serial.print("Verbinding maken... poging ");
    Serial.println(poging + 1);
 
    if (client.connect(serverIP, 80)) {
      client.println(emotie + "\n");
      client.flush();
      client.stop();
      Serial.println("Verzonden: " + emotie);
      success = true;
    } else {
      Serial.println("Verbinding mislukt, opnieuw proberen...");
      delay(300);
    }
 
    poging++;
  }
 
  if (!success) {
    Serial.println("⚠️  Verzenden mislukt na meerdere pogingen.");
  }
}