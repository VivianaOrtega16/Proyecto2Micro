#include <Arduino.h>

// Pines de los switches
const int switchPins[] = {4, 2, 3};  // Switch 1, Switch 2, Switch 3

// Pines de los leds
const int ledPins[] = {8, 9, 10, 11};  // led 1, led 2, led 3, led 4

const int delayTime = 500;  // tiempo de parpadeo en ms

// Array para almacenar los estados de los leds
bool ledStates[4] = {false, false, false, false}; 

//declaracion para imprimir estado de los leds
void imprimirEstadoLeds();

void setup() {
  Serial.begin(9600);  

  // configuramos los pines de los interruptores como entradas
  for (int i = 0; i < 3; i++) {
    pinMode(switchPins[i], INPUT);
  }

  // configuramos los pines de los leds como salidas
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // leer estados de los switches
  int state1 = digitalRead(switchPins[0]);
  int state2 = digitalRead(switchPins[1]);
  int state3 = digitalRead(switchPins[2]);

  // imprimir estados de los switches en el monitor serial
  Serial.println("Switch 1: "); 
  Serial.println(state1);
  Serial.println("Switch 2: "); 
  Serial.println(state2);
  Serial.println("Switch 3: "); 
  Serial.println(state3);

  if (state3 == HIGH) {
    // si el switch 3 esta presionado parpadean todos los leds
    Serial.println("Switch 3 activado-------");

    while (digitalRead(switchPins[2]) == HIGH) {  
      for (int i = 0; i < 4; i++) {
        ledStates[i] = true;
        digitalWrite(ledPins[i], ledStates[i] ? HIGH : LOW);
      }
      Serial.println("todos los leds se encienden");
      imprimirEstadoLeds();
      delay(delayTime);

      for (int i = 0; i < 4; i++) {
        ledStates[i] = false;
        digitalWrite(ledPins[i], ledStates[i] ? HIGH : LOW);
      }
      Serial.println("todos los leds se apagan");
      imprimirEstadoLeds();
      delay(delayTime);
    }
  } else {
    // control individual de leds segun los otros switches
    ledStates[0] = (state1 == HIGH);
    ledStates[1] = (state2 == HIGH);
    ledStates[2] = false;
    ledStates[3] = false;

    // actualizar leds con el array de los estados de los leds
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], ledStates[i] ? HIGH : LOW); // operador ternarioque dice si el ledSatte es true, devuelve High
    }// y si el ledState es false, devuelve low

    // Mensajes en el monitor serial
    if (state1 == HIGH) Serial.println("Switch 1 activado se enciende el led 1");
    if (state2 == HIGH) Serial.println("Switch 2 activado se enciende el led 2");
    if (state1 == LOW && state2 == LOW) Serial.println("Ningun switch esta activado, todos los leds apagados");

    imprimirEstadoLeds();
  }

  delay(2000);  
}
//Funcion para imprimir el estado de los leds 
void imprimirEstadoLeds() {
  Serial.print("estado de los leds: ");
  for (int i = 0; i < 4; i++) {
    Serial.print("led");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(ledStates[i] ? "ON " : "OFF ");
  }
  Serial.println();
}