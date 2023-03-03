#include <ezButton.h>

#define VRX_PIN 33
#define VRY_PIN 25
#define SW_PIN 18 // Pull-up resistor
#define DEBOUNCE_DELAY 50 // ms

volatile int lastInterruptTime = 0;

/*
 * Typical value = 1800 - 1900
 * Consider -x when x < 1000 and +x when x > 3000
 * The same for the "y" coordinate
 */

const int THRESHOLD_LOW = 1000;
const int THRESHOLD_HIGH = 3000;

enum direction_t { LEFT, RIGHT, UP, DOWN, CENTER };
direction_t direction = CENTER;
ezButton button(SW_PIN);

int counter = 0;

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);
  button.setDebounceTime(50);
  attachInterrupt(digitalPinToInterrupt(SW_PIN), btnInterruption, FALLING);
}

void loop() {
  button.loop();

  int valueX = analogRead(VRX_PIN);
  int valueY = analogRead(VRY_PIN);
  int buttonState = button.getState();

  if (valueX < THRESHOLD_LOW) {
    direction = LEFT;
  } else if (valueX > THRESHOLD_HIGH) {
    direction = RIGHT;
  } else if (valueY < THRESHOLD_LOW) {
    direction = UP;
  } else if (valueY > THRESHOLD_HIGH) {
    direction = DOWN;
  } else {
    direction = CENTER;
  }

  //printValues(valueX, valueY, button);
  
  // printDirection();
  // printButtonStatus(buttonState);
  // Serial.println("Button is pressed: " + String(button.isPressed()));
  // Serial.println("Button is released: " + String(button.isReleased()));
  delay(2000);

  Serial.println("Counter: " + String(counter));
}

void printDirection() {
  Serial.println("Direction: " + String(direction));
}

void btnInterruption() {
  int currentTime = millis();  // Registrar el tiempo actual
  if (currentTime - lastInterruptTime > DEBOUNCE_DELAY) {  // Verificar si ha pasado suficiente tiempo desde la última interrupción
    counter++;  // Contar la interrupción
    lastInterruptTime = currentTime;  // Actualizar el tiempo de la última interrupción
  }
}

void printButtonStatus(int button) {
  Serial.println("Button: " + String(button));
}

void printValues(int x, int y, int button) {
  Serial.println("x = " + String(x));
  Serial.println("y = " + String(y));
  Serial.println("Button: " + String(button));
}