#include <Arduino.h>
// definim pinii pentru ledurile RGB si butoane
const int ledRGB_R = 6;
const int ledRGB_G = 5;
const int ledRGB_B = 4;
const int startBtn = 3;       // buton pentru pornire/oprie joc
const int difficultyBtn = 2;   // buton pentru schimbarea dificultatii

// timpul minim dintre doua apasari pentru a preveni apasarile accidentale (debouncing)
const unsigned long debounceDelay = 200;

// variabile pentru a retine starea butoanelor
unsigned long lastDifficultyPressTime = 0;
unsigned long lastStartStopPressTime = 0;
bool startBtnLastState = HIGH;
bool difficultyBtnLastState = HIGH;

// configuram timpul total al rundei si durata animatiei de start
const unsigned long roundTime = 30000; // 30 secunde

// timpi pentru inceputul rundei si pentru afisarea cuvintelor
unsigned long roundStart = 0;
unsigned long wordStart = 0;
String currentWord = "";
String userInput = "";  // inputul introdus de utilizator

// variabile volatile pentru a gestiona schimbarile de stare ale jocului
volatile bool shouldChangeGameMode = false;
volatile bool shouldStartGame = false;
volatile bool shouldStopGame = false;
volatile bool gameStarted = false;
volatile bool shouldChangeWord = false;

unsigned long timePerWord = 0;
int correctWords = 0;

// lista de cuvinte pentru joc
const String words[50] = {
  "spark", "blissful", "wander", "eclipse", "luminous", "fragment", "radiant", "echoes",
  "cascade", "voyage", "horizon", "illusion", "whisper", "enchant", "meander", "quaint",
  "serene", "mystic", "paradox", "whimsy", "fable", "nebula", "solitude", "reverie",
  "breeze", "glisten", "embers", "wistful", "serendipity", "sapphire", "ephemeral", "celestial",
  "nostalgia", "galaxy", "velvet", "phantom", "ethereal", "labyrinth", "shimmer", "silhouette",
  "wanderlust", "tranquil", "zephyr", "nirvana", "epiphany", "radiance", "kaleidoscope", "enigma",
  "twilight", "ripple"
};

// enum pentru dificultate
enum gameMode {
  UNKNOWN = -1,
  EASY = 0,
  MEDIUM = 1,
  HARD = 2
};

gameMode difficulty = gameMode::UNKNOWN;

// functie pentru a schimba dificultatea
void changeGameMode() {
    shouldChangeGameMode = false;
    difficulty = (gameMode)(((int)difficulty + 1) % 3); // schimbam prin cele trei nivele: usor, mediu, greu
    switch (difficulty) {
        case EASY:
            Serial.println("Easy mode on!");
            timePerWord = 4000; // 4 secunde per cuvant
            break;
        case MEDIUM:
            Serial.println("Medium mode on!");
            timePerWord = 3000; // 3 secunde per cuvant
            break;
        case HARD:
            Serial.println("Hard mode on!");
            timePerWord = 2000; // 2 secunde per cuvant
            break;
        default:
            Serial.println("Unknown difficulty. Please try again!");
            difficulty = UNKNOWN;
            timePerWord = 0;
            break;
    }
}

// functie pentru a seta starea inactiva (joc oprit)
void idleState() {
    digitalWrite(ledRGB_R, HIGH);  
    digitalWrite(ledRGB_G, HIGH); 
    digitalWrite(ledRGB_B, HIGH); 
    difficulty = UNKNOWN;
    timePerWord = 0;
    shouldChangeGameMode = false;
    shouldStartGame = false;
    shouldStopGame = false;
    gameStarted = false;
    correctWords = 0;
    shouldChangeWord = false;
    currentWord = "";
    userInput = "";
    Serial.println("You must choose the difficulty before you can start the game.");
}

// functie pentru a porni jocul
void startGame() {
    shouldStartGame = false;
    shouldStopGame = false;
    if (difficulty == UNKNOWN) {
        Serial.println("Please choose difficulty.");
        return;
    }
    gameStarted = true;
    correctWords = 0;
    userInput = "";  // resetam inputul utilizatorului
    for (int i = 3; i > 0; i--) {
        Serial.println(i);
        digitalWrite(ledRGB_R, HIGH);  
        digitalWrite(ledRGB_G, HIGH); 
        digitalWrite(ledRGB_B, HIGH); 
        delay(500);
        digitalWrite(ledRGB_R, LOW);  
        digitalWrite(ledRGB_G, LOW); 
        digitalWrite(ledRGB_B, LOW); 
        delay(500);
    }
    digitalWrite(ledRGB_R, LOW);  
    digitalWrite(ledRGB_G, HIGH); 
    digitalWrite(ledRGB_B, LOW); 
    roundStart = millis();
    shouldChangeWord = true;
}

// functie pentru a opri jocul
void stopGame() {
    Serial.print("Score: ");
    Serial.println(correctWords);
    idleState();
}

// functie pentru a schimba cuvantul curent
void changeWord() {
    shouldChangeWord = false;
    int index = random(0, 50);
    currentWord = words[index];
    userInput = "";  // resetam inputul utilizatorului pentru noul cuvant
    wordStart = millis();  // salvam momentul afisarii noului cuvant
    Serial.println("\nNew word: " + currentWord);  // afisam noul cuvant
}

void setup() {
    Serial.begin(28800);
    pinMode(ledRGB_R, OUTPUT);
    pinMode(ledRGB_B, OUTPUT);
    pinMode(ledRGB_G, OUTPUT);
    pinMode(startBtn, INPUT_PULLUP); 
    pinMode(difficultyBtn, INPUT_PULLUP);  
    digitalWrite(ledRGB_R, HIGH);  
    digitalWrite(ledRGB_G, HIGH); 
    digitalWrite(ledRGB_B, HIGH);  
    randomSeed(analogRead(A0));  // initializam generatorul de numere aleatorii pentru a nu avea aceeasi ordine
    idleState();
}

void loop() {
    unsigned long currentMillis = millis();

    // verificam butonul de dificultate pentru debounce
    bool difficultyBtnState = digitalRead(difficultyBtn);

    if (difficultyBtnState == LOW && difficultyBtnLastState == HIGH && currentMillis - lastDifficultyPressTime > debounceDelay) {
        lastDifficultyPressTime = currentMillis;
        changeGameMode();
    }

    difficultyBtnLastState = difficultyBtnState;
    // verificam butonul de start/stop pentru debounce
    bool startBtnState = digitalRead(startBtn);
    if (startBtnState == LOW && startBtnLastState == HIGH && currentMillis - lastStartStopPressTime > debounceDelay) {
        lastStartStopPressTime = currentMillis;
        if (gameStarted) {
            stopGame();
        } else {
            startGame();
        }
    }

    startBtnLastState = startBtnState;
    // logica jocului cand este pornit
    if (gameStarted) {
        // verificam daca timpul pentru cuvantul curent a expirat si schimbam cuvantul
        if (millis() - wordStart >= timePerWord) {
            shouldChangeWord = true;
        }

        if (shouldChangeWord) {
            changeWord();
        }

        // citire si verificare continua a cuvantului in timp real
        if (Serial.available()) {
            char inputChar = Serial.read();  // citim caracterul introdus
            
            // afisam caracterul tastat in timp real
            if (inputChar != '\b') {
                Serial.print(inputChar);  // afisam caracterul tastat daca nu este Backspace
            }

            if (inputChar == '\b') {  // verificam daca este Backspace
                if (userInput.length() > 0) {
                    userInput.remove(userInput.length() - 1);  // stergem ultima litera
                    Serial.print("\b \b"); // sterge vizual ultima litera din Serial Monitor
                }
            } else if (isPrintable(inputChar)) {
                userInput += inputChar;  // adaugam caracterul la input
            }

            // verificam daca inputul este gresit
            if (userInput != currentWord.substring(0, userInput.length())) {
                digitalWrite(ledRGB_R, HIGH);  
                digitalWrite(ledRGB_G, LOW); 
                digitalWrite(ledRGB_B, LOW); 
            } else {
                digitalWrite(ledRGB_R, LOW);  
                digitalWrite(ledRGB_G, HIGH); 
                digitalWrite(ledRGB_B, LOW); 
            }

            // daca utilizatorul a introdus cuvantul corect, generam un cuvant nou si resetam timpul
            if (userInput == currentWord) {
                correctWords++;
                shouldChangeWord = true;
                wordStart = millis();  // resetam temporizatorul pentru noul cuvant
            }
        }

        // verificam daca timpul pentru joc s-a terminat
        if (millis() - roundStart >= roundTime) {
            stopGame();
        }
    }
}
