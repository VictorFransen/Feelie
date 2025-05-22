const int ledpin = 6;
int i = 0;
void setup() {
  pinMode(ledpin, OUTPUT);

}

void loop() {
  for(i;i<256;i++){
    analogWrite(ledpin, i);
    delay(5);
  }
  delay(1000);
  for(i;i>0;i--){
    analogWrite(ledpin, i);
    delay(5);
  }
  delay(1000);

}