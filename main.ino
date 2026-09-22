// ===== PINS =====
const int RED_LED = 25;
const int GREEN_LED = 26;

const int RED_BUTTON = 32;
const int GREEN_BUTTON = 33;

const int BUZZER = 27;

// ===== GAME =====
const int WIN_SCORE = 15;

int sequence[WIN_SCORE];
int currentLength = 1;


// =========================
// SETUP
// =========================
void setup() {

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);

  // Makes random sequence less predictable
  randomSeed(micros());

  startGame();
}


// =========================
// MAIN LOOP
// =========================
void loop() {

  showSequence();

  bool correct = playerTurn();

  if (correct) {

    playCorrect();

    // Did they reach 15?
    if (currentLength >= WIN_SCORE) {
      playWin();

      // Flash both LEDs
      for (int i = 0; i < 5; i++) {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, HIGH);
        delay(200);

        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        delay(200);
      }

      delay(2000);
      startGame();
    }

    else {
      currentLength++;
      delay(700);
    }
  }

  else {

    playWrong();

    digitalWrite(RED_LED, HIGH);
    delay(800);
    digitalWrite(RED_LED, LOW);

    delay(1000);

    startGame();
  }
}


// =========================
// START / RESET GAME
// =========================
void startGame() {

  currentLength = 1;

  // Create full 15-step sequence
  for (int i = 0; i < WIN_SCORE; i++) {
    sequence[i] = random(0, 2);
  }

  // Starting sound
  tone(BUZZER, 500, 100);
  delay(150);
  tone(BUZZER, 700, 100);

  delay(800);
}


// =========================
// SHOW MEMORY SEQUENCE
// =========================
void showSequence() {

  delay(500);

  for (int i = 0; i < currentLength; i++) {

    if (sequence[i] == 0) {

      // RED
      digitalWrite(RED_LED, HIGH);
      tone(BUZZER, 400, 200);

      delay(400);

      digitalWrite(RED_LED, LOW);
    }

    else {

      // GREEN
      digitalWrite(GREEN_LED, HIGH);
      tone(BUZZER, 650, 200);

      delay(400);

      digitalWrite(GREEN_LED, LOW);
    }

    delay(200);
  }
}


// =========================
// PLAYER INPUT
// =========================
bool playerTurn() {

  for (int i = 0; i < currentLength; i++) {

    int playerChoice = waitForButton();

    if (playerChoice != sequence[i]) {
      return false;
    }
  }

  return true;
}


// =========================
// WAIT FOR BUTTON PRESS
// =========================
int waitForButton() {

  while (true) {

    // RED button
    if (digitalRead(RED_BUTTON) == LOW) {

      digitalWrite(RED_LED, HIGH);
      tone(BUZZER, 400, 100);

      delay(150);

      // Wait until released
      while (digitalRead(RED_BUTTON) == LOW) {
        delay(10);
      }

      digitalWrite(RED_LED, LOW);

      delay(100);

      return 0;
    }


    // GREEN button
    if (digitalRead(GREEN_BUTTON) == LOW) {

      digitalWrite(GREEN_LED, HIGH);
      tone(BUZZER, 650, 100);

      delay(150);

      // Wait until released
      while (digitalRead(GREEN_BUTTON) == LOW) {
        delay(10);
      }

      digitalWrite(GREEN_LED, LOW);

      delay(100);

      return 1;
    }
  }
}


// =========================
// CORRECT SOUND
// =========================
void playCorrect() {

  tone(BUZZER, 700, 120);
  delay(140);

  tone(BUZZER, 1000, 150);
  delay(200);
}


// =========================
// WRONG SOUND
// =========================
void playWrong() {

  tone(BUZZER, 300, 250);
  delay(270);

  tone(BUZZER, 180, 400);
  delay(450);
}


// =========================
// WINNING SOUND
// =========================
void playWin() {

  tone(BUZZER, 523, 150);
  delay(180);

  tone(BUZZER, 659, 150);
  delay(180);

  tone(BUZZER, 784, 150);
  delay(180);

  tone(BUZZER, 1047, 500);
  delay(550);
}
