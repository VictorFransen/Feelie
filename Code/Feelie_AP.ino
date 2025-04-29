#include <SPI.h>
#include <WiFiNINA.h>

// Stel netwerkgegevens in
char ssid[] = "Feelie";    // De naam van het netwerk dat je maakt
char pass[] = "Linde_Victor";  

// Start een server op poort 80
WiFiServer server(80);


const int BlijPin = 2;
const int StressPin = 3;
const int VraagPin = 4;
const int BangPin = 5;
const int DroevigPin = 6;
const int BoosPin = 7;

// status variabelen
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
  Serial.begin(9600); // <--- Belangrijk voor communicatie met ProtoPie

  // Start Access Point Mode
  if (WiFi.beginAP(ssid, pass) != WL_AP_LISTENING) {
    Serial.println("Starten van Access Point mislukt!");
    while (true);
  }

  Serial.println("Access Point gestart!");
  Serial.print("IP adres: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Start de server

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
        Serial.println("Blij");
      }
    }

    if (StressStatus != StressKnop) {
      StressKnop = StressStatus;
      if (StressKnop == HIGH) {
        speelAnimatie();
        Serial.println("Stress");
      }
    }

    if (VraagStatus != VraagKnop) {
      VraagKnop = VraagStatus;
      if (VraagKnop == HIGH) {
        speelAnimatie();
        Serial.println("Vraag");
      }
    }

    if (BangStatus != BangKnop) {
      BangKnop = BangStatus;
      if (BangKnop == HIGH) {
        speelAnimatie();
        Serial.println("Bang");
      }
    }

    if (DroevigStatus != DroevigKnop) {
      DroevigKnop = DroevigStatus;
      if (DroevigKnop == HIGH) {
        speelAnimatie();
        Serial.println("Droevig");
      }
    }

    if (BoosStatus != BoosKnop) {
      BoosKnop = BoosStatus;
      if (BoosKnop == HIGH) {
        speelAnimatie();
        Serial.println("Boos");
      }
    }
  }

  LaatsteBlij = BlijStatus;
  LaatsteStress = StressStatus;
  LaatsteVraag = VraagStatus;
  LaatsteBang = BangStatus;
  LaatsteDroevig = DroevigStatus;
  LaatsteBoos = BoosStatus;


  // data ontvangen van andere bakje via wifi
  WiFiClient client = server.available(); // Wacht op client verbinding
  
  if (client) {
    Serial.println("Client verbonden!");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.println(data);
      }
    }
    client.stop();
    Serial.println("Client verbroken.");
  }
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
