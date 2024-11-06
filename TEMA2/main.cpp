#include <Arduino.h>

// definim pinii pentru ledurile RGB si butoane
const int ledRGB_R = 6;
const int ledRGB_G = 5;
const int ledRGB_B = 4;
const int startBtn = 3;         // buton pentru pornire/oprie joc
const int difficultyBtn = 2;        // buton pentru schimbarea dificultatii

// configuram timpul total al rundei si durata animatiei de start
const unsigned long roundTime = 30000; // 30 secunde

// timpi pentru inceputul rundei si pentru afisarea cuvintelor
unsigned long roundStart = 0;   // momentul in care incepe o runda
unsigned long wordDisplay = 0;     // momentul in care un cuvant nou este afisat

// variabile pentru a retine starea butoanelor
unsigned long lastStartPress = 0;       // timpul la care butonul de start/stop a fost apasat
unsigned long lastDiffPress = 0;        // timpul la care butonul de dificultate a fost apasat
bool startBtnState = HIGH;      // ultima stare a butonului de strt/stop
bool difficultyBtnState = HIGH;         // ultima stare a butonului de dificultate 

// timpul minim dintre doua apasari pentru a preveni apasarile accidentale (debouncing)
const unsigned long debounceDelay = 200;

String currentWord = "";  // cuvantul curent ce trebuie tastat
String userInput = "";    // inputul introdus de utilizator

unsigned long timePerWord = 0;  // timpul alocat pentru fiecare cuvant
int correctWordsCounter = 0;    // contor pentru cuvintele tastate corect

// variabile volatile pentru a gestiona schimbarile de stare ale jocului
volatile bool shouldCycleDifficulty = false;
volatile bool shouldStartGame = false;
volatile bool shouldStopGame = false;
volatile bool isGameStarted = false;
volatile bool shouldChangeWord = false;

// dictionarul de cuvinte pentru joc
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
enum Difficulty {
  UNKNOWN = -1,
  EASY = 0,
  MEDIUM = 1,
  HARD = 2
};

Difficulty difficulty = Difficulty::UNKNOWN;        //setam dificulatea la unknown 

// functie pentru a schimba dificultatea
void cycleDifficulty() {
    shouldCycleDifficulty = false;

    // rotim dificultatea intre EASY, MEDIUM si HARD
    difficulty = (Difficulty)(((int)difficulty + 1) % 3);

    // setam timpul per cuvant in functie de dificultate
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
    // resetam LED-ul RGB la culoarea alba
    digitalWrite(ledRGB_R, HIGH);
    digitalWrite(ledRGB_G, HIGH);
    digitalWrite(ledRGB_B, HIGH);
    
    // resetam variabilele jocului
    difficulty = UNKNOWN;
    timePerWord = 0;
    shouldCycleDifficulty = false;
    shouldStartGame = false;
    shouldStopGame = false;
    isGameStarted = false;
    correctWordsCounter = 0;
    shouldChangeWord = false;
    currentWord = "";
    userInput = "";

    Serial.println("You must choose the difficulty before you can start the game.");
}

// functie pentru a porni jocul
void startGame() {
    shouldStartGame = false;
    shouldStopGame = false;

    // verificam daca dificultatea este setata
    if (difficulty == UNKNOWN) {
        Serial.println("Please choose difficulty.");
        return;
    }

    isGameStarted = true;
    correctWordsCounter = 0;
    userInput = "";  // resetam inputul utilizatorului

    // animatie de numaratoare inversa de 3 secunde
    for (int i = 3; i > 0; i--) {
        Serial.println(i);
        digitalWrite(ledRGB_R, HIGH);
        digitalWrite(ledRGB_G, HIGH);
        digitalWrite(ledRGB_B, HIGH);
        delay(500);  // delay de 500 ms
        digitalWrite(ledRGB_R, LOW);
        digitalWrite(ledRGB_G, LOW);
        digitalWrite(ledRGB_B, LOW);
        delay(500);  // delay de 500 ms
    }

    // aprindem LED-ul in verde pentru a indica ca jocul a pornit
    digitalWrite(ledRGB_R, LOW);
    digitalWrite(ledRGB_G, HIGH);
    digitalWrite(ledRGB_B, LOW);

    roundStart = millis();  // salvam timpul de start al rundei
    shouldChangeWord = true;                // semnalam ca trebuie sa schimbam cuvantul
}

// functie pentru a schimba cuvantul curent
void changeWord() {
    shouldChangeWord = false;

    // selectam un cuvant aleatoriu din lista
    int index = random(0, 50);
    currentWord = words[index];
    userInput = "";  // resetam inputul utilizatorului pentru noul cuvant

    wordDisplay = millis();  // salvam timpul afisarii noului cuvant
    Serial.println("\nNew word: " + currentWord);  // afisam noul cuvant
}

// functie pentru a opri jocul
void stopGame() {
    // afisam scorul final
    Serial.print("Score: ");
    Serial.println(correctWordsCounter);

    idleState();  // punem jocul in stare inactiva
}

void setup() {
    Serial.begin(28800);
    pinMode(ledRGB_R, OUTPUT);
    pinMode(ledRGB_B, OUTPUT);
    pinMode(ledRGB_G, OUTPUT);

    pinMode(startBtn, INPUT_PULLUP); 
    pinMode(difficultyBtn, INPUT_PULLUP);  

    // initializam LED-ul RGB in alb
    digitalWrite(ledRGB_R, HIGH);
    digitalWrite(ledRGB_G, HIGH);
    digitalWrite(ledRGB_B, HIGH);

    // initializam generatorul de numere aleatorii pentru a nu avea aceeasi ordine
    randomSeed(analogRead(A0));

    idleState();  // setam jocul in stare inactiva la inceput
}

void loop() {
    unsigned long currentMillis = millis();

    // verificam butonul de dificultate pentru debounce
    bool difficultyBtnState = digitalRead(difficultyBtn);
    if (difficultyBtnState == LOW && difficultyBtnState == HIGH && currentMillis - lastDiffPress > debounceDelay) {
        lastDiffPress = currentMillis;
        cycleDifficulty();  // schimbam dificultatea
    }
    difficultyBtnState = difficultyBtnState;

    // verificam butonul de start/stop pentru debounce
    bool startBtnState = digitalRead(startBtn);
    if (startBtnState == LOW && startBtnState == HIGH && currentMillis - lastStartPress > debounceDelay) {
        lastStartPress = currentMillis;
        if (isGameStarted) {
            stopGame();  // oprim jocul
        } else {
            startGame();  // pornim jocul
        }
    }
    startBtnState = startBtnState;

    // logica jocului cand este pornit
    if (isGameStarted) {
        // verificam daca timpul pentru cuvantul curent a expirat
        if (millis() - wordDisplay >= timePerWord) {
            shouldChangeWord = true;  // semnalam schimbarea cuvantului
        }

        if (shouldChangeWord) {
            changeWord();  // schimbam cuvantul curent
        }

        // citim inputul utilizatorului
        if (Serial.available()) {
            char inputChar = Serial.read();  // citim caracterul introdus
            
            // afisam caracterul tastat in timp real
            if (inputChar != '\b') {
                Serial.print(inputChar);  // afisam caracterul daca nu este Backspace
            }

            // gestionam stergerea caracterului cu Backspace
            if (inputChar == '\b') {
                if (userInput.length() > 0) {
                    userInput.remove(userInput.length() - 1);  // stergem ultima litera
                    Serial.print("\b \b"); // stergem ultima litera din Serial Monitor
                }
            } else if (isPrintable(inputChar)) {
                userInput += inputChar;  // adaugam caracterul la input
            }

            // verificam daca inputul este gresit
            if (userInput != currentWord.substring(0, userInput.length())) {
                // aprindem LED-ul in rosu pentru input gresit
                digitalWrite(ledRGB_R, HIGH);
                digitalWrite(ledRGB_G, LOW);
                digitalWrite(ledRGB_B, LOW);
            } else {
                // aprindem LED-ul in verde pentru input corect
                digitalWrite(ledRGB_R, LOW);
                digitalWrite(ledRGB_G, HIGH);
                digitalWrite(ledRGB_B, LOW);
            }

            // daca utilizatorul a introdus cuvantul corect
            if (userInput == currentWord) {
                correctWordsCounter++;  // incrementam contorul
                shouldChangeWord = true;  // semnalam schimbarea cuvantului
                wordDisplay = millis();  // resetam timpul pentru noul cuvant
            }
        }

        // verificam daca timpul pentru joc s-a terminat
        if (millis() - roundStart >= roundTime) {
            stopGame();  // oprim jocul
        }
    }
}
