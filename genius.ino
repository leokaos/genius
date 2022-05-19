#include "notes.h"

#define PIN_AMARELO 9
#define PIN_VERDE 10
#define PIN_VERMELHO 11

#define BTN_AMARELO 2
#define BTN_VERDE 3
#define BTN_VERMELHO 4

#define PIN_BUZZER 7

int melodiaVitoria[] = {NOTE_C4, NOTE_D4, NOTE_F4};
int duracaoVitoria[] = {5, 5, 5};

int melodiaDerrota[] = { NOTE_E4, NOTE_E6, NOTE_C4, NOTE_A4, NOTE_A6 };
int duracaoDerrota[] = {4, 4, 4, 4, 4};

void setup() {

  pinMode(PIN_AMARELO, OUTPUT);
  pinMode(PIN_VERDE, OUTPUT);
  pinMode(PIN_VERMELHO, OUTPUT);

  pinMode(BTN_AMARELO, INPUT_PULLUP);
  pinMode(BTN_VERDE, INPUT_PULLUP);
  pinMode(BTN_VERMELHO, INPUT_PULLUP);

  pinMode(PIN_BUZZER, OUTPUT);
}

int dificuldade = 1;
int sequencia[10] = {};

boolean esperando = false;
int atual = 0;

void loop() {

  if (!esperando) {

    createNew();

    for (int x = 0; x < dificuldade; x++) {
      ascender(sequencia[x], 200);
      delay(100);
    }

    esperando = true;

  } else {

    check(BTN_AMARELO, PIN_AMARELO);
    check(BTN_VERDE, PIN_VERDE);
    check(BTN_VERMELHO, PIN_VERMELHO);

    if (atual == dificuldade) {
      
      playSong(melodiaVitoria, duracaoVitoria, 3);

      if (dificuldade == 10) {
        dificuldade = 1;
      } else {
        dificuldade++;
      }

      esperando = false;
      atual = 0;
    }

  }

}

void check(int btn, int pin) {

  if (digitalRead(btn) == LOW ) {
    ascender(pin, 200);
    delay(300);

    if (sequencia[atual] == pin) {
      atual++;
    } else {
      playSong(melodiaDerrota, duracaoDerrota, 5);
      dificuldade = 1;
      esperando = false;
    }

  }
}

void ascender(int btn, int tempoAcesso) {
  digitalWrite(btn, HIGH);
  tone(PIN_BUZZER, 300, 100);
  delay(tempoAcesso);
  digitalWrite(btn, LOW);
}

void reset() {
  atual = 0;
  dificuldade = 1;
}

void createNew() {

  for (int x = 0; x < dificuldade; x++) {
    sequencia[x] = random(9, 12);
  }

}

void playSong(int melodia[], int duracao[], int tamanho) {

  for (int thisNote = 0; thisNote < tamanho; thisNote++) {
    int noteDuration = 1000 / duracao[thisNote];
    tone(7, melodia[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(7);
  }

  delay(1000);

}
