#include <Arduino.h>
#include <SPI.h>

// prototipurile functiilor
void initiateButtonChallenge(char selectedColor);
void evaluateButtonPress();
void lightUpLED(char selectedColor);
void turnOffAllLEDs();

volatile char spiCommand = '\0';
volatile bool newSPICommand = false;

// pini de conectare
const int analogButtonPin = A0;
const int buzzerControlPin = 2;
const int commonSmallLEDPin = 3;

// pini led rgb pentru fiecare jucator
const int p1RedLEDPin = 4;
const int p1GreenLEDPin = 5;
const int p1BlueLEDPin = 6;

const int p2RedLEDPin = 7;
const int p2GreenLEDPin = 8;
const int p2BlueLEDPin = 9;

// variabile pentru starea jocului
unsigned long buttonPressStartTime = 0;
bool isWaitingForButtonPress = false;
bool isPlayerOneActive = true;

void setup() {
  Serial.begin(115200);         // pentru debugging
  SPCR |= bit(SPE);             // activeaza spi in modul slave
  pinMode(MISO, OUTPUT);        // seteaza MISO ca iesire pentru spi
  SPI.attachInterrupt();        // activeaza intreruperea spi

  // configurarea pinurilor pentru led-uri si buzzer
  pinMode(buzzerControlPin, OUTPUT);
  pinMode(commonSmallLEDPin, OUTPUT);

  pinMode(p1RedLEDPin, OUTPUT);
  pinMode(p1GreenLEDPin, OUTPUT);
  pinMode(p1BlueLEDPin, OUTPUT);
  pinMode(p2RedLEDPin, OUTPUT);
  pinMode(p2GreenLEDPin, OUTPUT);
  pinMode(p2BlueLEDPin, OUTPUT);

  digitalWrite(commonSmallLEDPin, HIGH);  // led-urile mici active pe durata jocului
}

// intrerupere spi
ISR(SPI_STC_vect) {
  char receivedData = SPDR;
  if (receivedData != '#') {  // ignora comanda '#' daca este primita
    spiCommand = receivedData;
    newSPICommand = true;
  }
}

void loop() {
  if (newSPICommand) {
    newSPICommand = false;

    // verifica daca comanda primita este o culoare valida
    if (spiCommand == 'r' || spiCommand == 'g' || spiCommand == 'b') {
      initiateButtonChallenge(spiCommand);
    } else {
      SPDR = '$';  // trimite raspuns implicit pentru comenzi necunoscute
    }
  }

  if (isWaitingForButtonPress) {
    evaluateButtonPress();
  }
}

void initiateButtonChallenge(char selectedColor) {
  Serial.print("received command: ");
  Serial.print(spiCommand);
  Serial.println(isPlayerOneActive ? " for player 1" : " for player 2");

  buttonPressStartTime = millis();  // incepe cronometrul pentru apasarea butonului
  isWaitingForButtonPress = true;
  lightUpLED(selectedColor);  // aprinde led-ul corespunzator
}

void evaluateButtonPress() {
  unsigned long elapsedTime = millis() - buttonPressStartTime;
  int buttonReadValue = analogRead(analogButtonPin);
  Serial.print("button value: ");  // debugging
  Serial.println(buttonReadValue);

  bool isButtonPressed = false;

  // verifica apasarile pentru fiecare jucator si comanda
  if (isPlayerOneActive) {
    if ((spiCommand == 'r' && buttonReadValue >= 90 && buttonReadValue <= 110) ||
        (spiCommand == 'g' && buttonReadValue >= 140 && buttonReadValue <= 160) ||
        (spiCommand == 'b' && buttonReadValue >= 200 && buttonReadValue <= 220)) {
      isButtonPressed = true;
    }
  } else {
    if ((spiCommand == 'r' && buttonReadValue >= 280 && buttonReadValue <= 320) ||
        (spiCommand == 'g' && buttonReadValue >= 450 && buttonReadValue <= 490) ||
        (spiCommand == 'b' && buttonReadValue >= 1000 && buttonReadValue <= 1023)) {
      isButtonPressed = true;
    }
  }

  if (isButtonPressed) {
    isWaitingForButtonPress = false;
    char scoreGrade;

    // determina scorul pe baza timpului de raspuns
    if (elapsedTime <= 300) {
      scoreGrade = 'e';  // excellent
    } else if (elapsedTime <= 600) {
      scoreGrade = 'g';  // good
    } else if (elapsedTime <= 1000) {
      scoreGrade = 'm';  // mediocre
    } else {
      scoreGrade = 'i';  // invalid
    }

    SPDR = scoreGrade;  // trimite scorul prin spi
    if (scoreGrade != 'i') {
      tone(buzzerControlPin, 659, 200);  // emite un sunet daca scorul este valid
    }
    isPlayerOneActive = !isPlayerOneActive;  // schimba jucatorul activ
  } else if (elapsedTime > 900) {  // timeout
    isWaitingForButtonPress = false;
    SPDR = 'i';  // trimite scor de timeout
    isPlayerOneActive = !isPlayerOneActive;  // schimba jucatorul activ
  }
}

void lightUpLED(char selectedColor) {
  turnOffAllLEDs();  // stinge toate led-urile inainte de a aprinde unul nou
  int targetLEDPin;

  // selecteaza led-ul corespunzator in functie de jucator si culoare
  if (isPlayerOneActive) {
    targetLEDPin = (selectedColor == 'r') ? p1RedLEDPin :
                   (selectedColor == 'g') ? p1GreenLEDPin :
                   p1BlueLEDPin;
    Serial.print("lighting player 1 led: ");
  } else {
    targetLEDPin = (selectedColor == 'r') ? p2RedLEDPin :
                   (selectedColor == 'g') ? p2GreenLEDPin :
                   p2BlueLEDPin;
    Serial.print("lighting player 2 led: ");
  }

  Serial.println(targetLEDPin);  // debugging: pinul led-ului aprins
  digitalWrite(targetLEDPin, HIGH);
}

void turnOffAllLEDs() {
  // stinge toate led-urile
  digitalWrite(p1RedLEDPin, LOW);
  digitalWrite(p1GreenLEDPin, LOW);
  digitalWrite(p1BlueLEDPin, LOW);
  digitalWrite(p2RedLEDPin, LOW);
  digitalWrite(p2GreenLEDPin, LOW);
  digitalWrite(p2BlueLEDPin, LOW);
}
