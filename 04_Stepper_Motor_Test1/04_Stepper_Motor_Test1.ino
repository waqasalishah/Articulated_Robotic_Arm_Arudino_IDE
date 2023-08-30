//




//Defintion of Pins
int PUL = 27; //define Pulse pin
int DIR = 26; //define Direction pin
int ENA = 25; //define Enable Pin


void setup() {


}

void loop() {
  
  for (int i = 0; i < 6400; i++) //Forward 5000 steps
  {
    digitalWrite(DIR, LOW);
    digitalWrite(ENA, LOW);
    digitalWrite(PUL, HIGH);
    delay(1);
    digitalWrite(PUL, LOW);
    delay(1);
  }

  delay(5000);
  for (int i = 0; i < 6400; i++) //Backward 5000 steps
  {
    digitalWrite(DIR, HIGH);
    digitalWrite(ENA, LOW);
    digitalWrite(PUL, HIGH);
    delay(1);
    digitalWrite(PUL, LOW);
    delay(1);
  }
  delay(5000);
}
