#include <Arduino.h>

//definim pinii (led-uri + butoane)
const int led1 = 10;  //led pt 25%
const int led2 = 9;   //led pt 50%
const int led3 = 8;   //led pt 75%
const int led4 = 7;   //led pt 100%
const int ledRGB_R = 6;  //rgb rosu
const int ledRGB_B = 4;  //rgb albastru
const int ledRGB_G = 5;  //rgb verde
const int start_button = 3; //buton ce porneste incarcarea
const int stop_button = 2;  //buton ce opreste fortat incarcarea

//definim variabile pt starea butoanelor
int startState = HIGH;
int stopState = HIGH;
int lastStartState = HIGH;
int lastStopState = HIGH;

//variabile pt debouncing:
unsigned long lastDebounceTimeStart = 0;
unsigned long lastDebounceTimeStop = 0;
const unsigned long debounceDelay = 50;  

//variabila pt starea procesului de incarcare
bool isLoading = false;


void setup() {
  pinMode(ledRGB_R, OUTPUT);
  pinMode(ledRGB_B, OUTPUT);
  pinMode(ledRGB_G, OUTPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(start_button, INPUT_PULLUP); 
  pinMode(stop_button, INPUT_PULLUP);  

  //steam led-ul rgb pe verde la pornirea montajului
  digitalWrite(ledRGB_R, LOW);  
  digitalWrite(ledRGB_G, HIGH); 
  digitalWrite(ledRGB_B, LOW);  
}


//functie pt animatia finala
void finalAnimation() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(500);

  for (int i = 0; i < 3; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(750);  

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(750); 
  }

  //setam led-ul rgb inapoi la verde
  digitalWrite(ledRGB_R, LOW);  
  digitalWrite(ledRGB_G, HIGH); 
  digitalWrite(ledRGB_B, LOW);  

  isLoading = false;
}


//functie pt verificarea butonului de stop (apasare lunga)
void checkStopButtonPress(unsigned long &buttonPressStartTime) {
  stopState = digitalRead(stop_button);

  if (stopState == LOW) {
    if (buttonPressStartTime == 0) {
      buttonPressStartTime = millis();
    }

    if (millis() - buttonPressStartTime >= 1000) {
      finalAnimation();
    }
  } else {
    buttonPressStartTime = 0;
  }
}


//functie ce incepe incarcarea
void startLoadingProcess() {
  isLoading = true;

  unsigned long buttonPressStartTime = 0;

  //primul led clipeste de 2 ori
  for (int i = 0; i < 2; i++) {
    digitalWrite(led1, HIGH);  
    delay(750);               
    digitalWrite(led1, LOW);  
    delay(750);                

    //verificam daca butonul de stop a fost apasat lung (minim o secunda)
    checkStopButtonPress(buttonPressStartTime);
    if (!isLoading) return;  //iesim din functie daca incarcarea a fost oprita
  }

  //a treia clipire pentru led1, apoi aprindem led2
  digitalWrite(led1, HIGH);
  for (int i = 0; i < 2; i++) {
    digitalWrite(led2, HIGH);  
    delay(750);               
    digitalWrite(led2, LOW);   
    delay(750);               
    
    checkStopButtonPress(buttonPressStartTime);
    if (!isLoading) return;
  }

  digitalWrite(led2, HIGH);
  for (int i = 0; i < 2; i++) {
    digitalWrite(led3, HIGH);  
    delay(750);                
    digitalWrite(led3, LOW);   
    delay(750);               
    
    checkStopButtonPress(buttonPressStartTime);
    if (!isLoading) return;
  }

  digitalWrite(led3, HIGH);
  for (int i = 0; i < 2; i++) {
    digitalWrite(led4, HIGH);  
    delay(750);               
    digitalWrite(led4, LOW);   
    delay(750);                
    
    checkStopButtonPress(buttonPressStartTime);
    if (!isLoading) return;
  }

  isLoading = false;
  finalAnimation();
}


void loop() {

  //citim/verificam starile butoanelor
  int readingStart = digitalRead(start_button);
  int readingStop = digitalRead(stop_button);

  //debouncing pentru butonul de start
  if (readingStart != lastStartState) {
    lastDebounceTimeStart = millis();  //resetam temporizatorul de debounce
  }

  if ((millis() - lastDebounceTimeStart) > debounceDelay) {
    if (readingStart != startState) {
      startState = readingStart;
      
      //verificam daca butonul de start e apasat, daca da incepem procesul de incarcare
      if (startState == LOW) {
        isLoading = true;
        
        //schimba culoarea led-ului rgb pe rosu
        digitalWrite(ledRGB_R, HIGH);  
        digitalWrite(ledRGB_G, LOW); 
        digitalWrite(ledRGB_B, LOW);

        //apelam functia de incarcare (incepem procesul de incarcare)
        startLoadingProcess();
      }
    }
  }

  //memoram/actualizam ultima stare citita pentru butonul de start
  lastStartState = readingStart;

  //debouncing pentru butonul de stop (doar daca incarcarea este activa)
  if (isLoading && (readingStop != lastStopState)) {
    lastDebounceTimeStop = millis();  //resetam temporizatorul de debounce
  }

  if (isLoading && (millis() - lastDebounceTimeStop) > debounceDelay) {
    if (readingStop != stopState) {
      stopState = readingStop;
      //verificam daca butonul de stop a fost apasat. daca da pornim animatia de final
      if (stopState == LOW) {
        finalAnimation();  
      }
    }
  }

  //memoram/actualizam ultima stare citita pentru butonul de stop
  lastStopState = readingStop;
}
