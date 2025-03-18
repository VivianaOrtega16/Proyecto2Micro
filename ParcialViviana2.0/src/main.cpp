#include <Arduino.h>

// Pines de los switches
const int switchPins[] = {4, 2, 3};  // Switch 1, Switch 2, Switch 3

// Pines de los LEDs
const int ledPins[] = {8, 9, 10, 11};  // LED 1, LED 2, LED 3, LED 4

const int delayTime = 500;  // Tiempo de parpadeo en ms

// Array para almacenar los estados de los LEDs
bool ledStates[4] = {false, false, false, false}; 

//declaracion para imprimir estado de los LEDs
void imprimirEstadoLeds();

void setup() {
  Serial.begin(9600);  // Inicia la comunicación serial a 9600 

  // Configuramos los pines de los interruptores como entradas
  for (int i = 0; i < 3; i++) {
    pinMode(switchPins[i], INPUT);
  }

  // Configuramos los pines de los LEDs como salidas
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Leer estados de los switches
  int state1 = digitalRead(switchPins[0]);
  int state2 = digitalRead(switchPins[1]);
  int state3 = digitalRead(switchPins[2]);

  // Imprimir estados de los switches en el monitor serial
  Serial.println("Switch 1: "); 
  Serial.println(state1);
  Serial.println("Switch 2: "); 
  Serial.println(state2);
  Serial.println("Switch 3: "); 
  Serial.println(state3);

  if (state3 == HIGH) {
    // Si el switch 3 está presionado, hacer parpadear todos los LEDs
    Serial.println("Switch 3 activado -> Todos los LEDs parpadean");

    while (digitalRead(switchPins[2]) == HIGH) {  // Mantener parpadeo mientras el switch esté presionado
      for (int i = 0; i < 4; i++) {
        ledStates[i] = true;
        digitalWrite(ledPins[i], ledStates[i] ? HIGH : LOW);
      }
      Serial.println("Todos los LEDs encendidos");
      imprimirEstadoLeds();
      delay(delayTime);

      for (int i = 0; i < 4; i++) {
        ledStates[i] = false;
        digitalWrite(ledPins[i], ledStates[i] ? HIGH : LOW);
      }
      Serial.println("Todos los LEDs apagados");
      imprimirEstadoLeds();
      delay(delayTime);
    }
  } else {
    // Control individual de LEDs segun los otros switches
    ledStates[0] = (state1 == HIGH);
    ledStates[1] = (state2 == HIGH);
    ledStates[2] = false;
    ledStates[3] = false;

    // Actualizar LEDs con el array ledStates
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], ledStates[i] ? HIGH : LOW);
    }

    // Mensajes en el monitor serial
    if (state1 == HIGH) Serial.println("Switch 1 activado -> LED 1 encendido");
    if (state2 == HIGH) Serial.println("Switch 2 activado -> LED 2 encendido");
    if (state1 == LOW && state2 == LOW) Serial.println("Ningún switch activo -> LEDs apagados");

    imprimirEstadoLeds();
  }

  delay(2000);  
}

// Función para imprimir el estado de los LEDs en el Monitor Serial
void imprimirEstadoLeds() {
  Serial.print("Estado de los LEDs: ");
  for (int i = 0; i < 4; i++) {
    Serial.print("LED");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(ledStates[i] ? "ON " : "OFF ");
  }
  Serial.println();
}