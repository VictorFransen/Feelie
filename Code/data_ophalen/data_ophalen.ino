#include <EEPROM.h>
int Blij;
int Stress;
int Vraag;
int Bang;
int Droevig;
int Boos;
int totaal;
float tijd;

void setup() {
  Serial.begin(9600);
  Blij = EEPROM.read(0);
  Stress = EEPROM.read(1);
  Vraag = EEPROM.read(2);
  Bang = EEPROM.read(3);
  Droevig = EEPROM.read(4);
  Boos = EEPROM.read(5);
  totaal = EEPROM.read(6);

  int tijd_totaal = (2*totaal) + 7;


  Serial.print("Blij = ");
  Serial.println(Blij);
  Serial.print("Stress = ");
  Serial.println(Stress);
  Serial.print("Vraag = ");
  Serial.println(Vraag);
  Serial.print("Bang = ");
  Serial.println(Bang);
  Serial.print("Droevig = ");
  Serial.println(Droevig);
  Serial.print("Boos = ");
  Serial.println(Boos);
  Serial.print("totaal = ");
  Serial.println(totaal);

  for(int a = 7; a < tijd_totaal; a = a + 2){
    int uur = EEPROM.read(a);
    int minuten = EEPROM.read(a+1);
    Serial.print("tijd: ");
    Serial.print(uur);
    Serial.print(":");
    Serial.println(minuten);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
