#include <EEPROM.h>
// knoppen voor emotie definieren
const int BlijPin = 2;
const int StressPin = 3;
const int VraagPin = 4;
const int BangPin = 5;
const int DroevigPin = 6;
const int BoosPin = 7;

// variabelen aanmaken voor aantal drukken te capteren
int Blij = 0;
int Stress = 0;
int Vraag = 0;
int Bang = 0;
int Droevig = 0;
int Boos = 0;
int totaal = 0;

//Schrijven naar
int tijd_plaats = 7;

//status toekennende variabele
int BlijStatus = 0;
int StressStatus = 0;
int VraagStatus = 0;
int BangStatus = 0;
int DroevigStatus = 0;
int BoosStatus = 0;

//DEBOUNCEpar
//laatste
int LaatsteBlij = LOW;
int LaatsteStress = LOW;
int LaatsteVraag = LOW;
int LaatsteBang = LOW;
int LaatsteDroevig = LOW;
int LaatsteBoos = LOW;
//debounce
int lastDebounceTime = 0;
const int debounceTime = 50;

int BlijKnop = HIGH;
int StressKnop = HIGH;
int VraagKnop= HIGH;
int BangKnop = HIGH;
int DroevigKnop = HIGH;
int BoosKnop = HIGH;

void setup() {
  //knoppen pinmode toekennen
  pinMode(BlijPin, INPUT_PULLUP);
  pinMode(StressPin, INPUT_PULLUP);
  pinMode(VraagPin, INPUT_PULLUP);
  pinMode(BangPin, INPUT_PULLUP);
  pinMode(DroevigPin, INPUT_PULLUP);
  pinMode(BoosPin, INPUT_PULLUP);

  //LED pinnen pinmode toekennen
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A1, OUTPUT);

}

void loop() {

  unsigned long currentMillis = millis();
  unsigned long seconds = currentMillis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  currentMillis %= 1000;
  minutes %= 60;
  hours %= 24;

  BlijStatus = digitalRead(BlijPin);
  StressStatus = digitalRead(StressPin);
  VraagStatus = digitalRead(VraagPin);
  BangStatus = digitalRead(BangPin);
  DroevigStatus = digitalRead(DroevigPin);
  BoosStatus = digitalRead(BoosPin);

  if(BlijStatus != LaatsteBlij || StressStatus != LaatsteStress || VraagStatus != LaatsteVraag || BangStatus != LaatsteBang || DroevigStatus != LaatsteDroevig || BoosStatus != LaatsteBoos) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceTime) {

//Blij
    if (BlijStatus != BlijKnop) {
      BlijKnop = BlijStatus;

      if (BlijKnop == HIGH) {
        Blij +=1;
        totaal += 1;
        
        EEPROM.update(0,Blij);
        EEPROM.update(6, totaal);
        EEPROM.update(tijd_plaats, hours);
        EEPROM.update(tijd_plaats+1, minutes);
        tijd_plaats += 2;
        for(int a = 8; a < 13; a++){
          digitalWrite(a, HIGH);
          delay(50);
          digitalWrite(a, LOW);
        }
        digitalWrite(A1, HIGH);
        delay(50);
        digitalWrite(A1,LOW);
      }
    }

//stress
    if (StressStatus != StressKnop) {
      StressKnop = StressStatus;

      if (StressKnop == HIGH) {
        Stress +=1;
        totaal += 1;
    
        EEPROM.update(1,Stress);
        EEPROM.update(6, totaal);
        EEPROM.update(tijd_plaats, hours);
        EEPROM.update(tijd_plaats+1, minutes);
        tijd_plaats += 2;
        for(int a = 8; a < 13; a++){
          digitalWrite(a, HIGH);
          delay(50);
          digitalWrite(a, LOW);
        }
        digitalWrite(A1, HIGH);
        delay(50);
        digitalWrite(A1,LOW);
      }
    }
//Vraag
    if (VraagStatus != VraagKnop) {
      VraagKnop = VraagStatus;

      if (VraagKnop == HIGH) {
        Vraag +=1;
        totaal +=1;

        EEPROM.update(2,Vraag);
        EEPROM.update(6, totaal);
        EEPROM.update(tijd_plaats, hours);
        EEPROM.update(tijd_plaats+1, minutes);
        tijd_plaats += 2;
        for(int a = 8; a < 13; a++){
          digitalWrite(a, HIGH);
          delay(50);
          digitalWrite(a, LOW);
        }
        digitalWrite(A1, HIGH);
        delay(50);
        digitalWrite(A1,LOW);
      }
    }
//Bang
    if (BangStatus != BangKnop) {
      BangKnop = BangStatus;

      if (BangKnop == HIGH) {
        Bang += 1;
        totaal += 1;
        
        EEPROM.update(3,Bang);
        EEPROM.update(6, totaal);
        EEPROM.update(tijd_plaats, hours);
        EEPROM.update(tijd_plaats+1, minutes);
        tijd_plaats += 2;
        for(int a = 8; a < 13; a++){
          digitalWrite(a, HIGH);
          delay(50);
          digitalWrite(a, LOW);
        }
        digitalWrite(A1, HIGH);
        delay(50);
        digitalWrite(A1,LOW);
      }
    }
//Droevig
    if (DroevigStatus != DroevigKnop) {
      DroevigKnop = DroevigStatus;

      if (DroevigKnop == HIGH) {
        Droevig += 1;
        totaal += 1;
        
        EEPROM.update(4,Droevig);
        EEPROM.update(6, totaal);
        EEPROM.update(tijd_plaats, hours);
        EEPROM.update(tijd_plaats+1, minutes);
        tijd_plaats += 2;
        for(int a = 8; a < 13; a++){
          digitalWrite(a, HIGH);
          delay(50);
          digitalWrite(a, LOW);
        }
        digitalWrite(A1, HIGH);
        delay(50);
        digitalWrite(A1,LOW);
      }
    }
//Boos
    if (BoosStatus != BoosKnop) {
      BoosKnop = BoosStatus;

      if (BoosKnop == HIGH) {
        Boos += 1;
        totaal += 1;
        
        EEPROM.update(5,Boos);
        EEPROM.update(6, totaal);
        EEPROM.update(tijd_plaats, hours);
        EEPROM.update(tijd_plaats+1, minutes);
        tijd_plaats += 2;
        for(int a = 8; a < 13; a++){
          digitalWrite(a, HIGH);
          delay(50);
          digitalWrite(a, LOW);
        }
        digitalWrite(A1, HIGH);
        delay(50);
        digitalWrite(A1,LOW);
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

