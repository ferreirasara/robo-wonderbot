#include <Servo.h>
#include "defines.h"

// Inicializacao dos objetos
Servo servoBase;
Servo servo1;
Servo servo2;

void setup() {
	// Inicializacao dos servos
	servoBase.attach(pinoServoBase);
	servo1.attach(pinoServo1);
	servo2.attach(pinoServo2);

	// Inicia os servos na posicao 0 (posicao inicial)
	servoBase.write(0);
	servo1.write(0);
	servo2.write(0);

	// Inicializacao do eletroima
	pinMode(pinoEletroIma, OUTPUT);
	digitalWrite(pinoEletroIma, LOW);

	// Inicializacao do sensor
	pinMode(pinoSensor, INPUT);
	
	// Inicia a porta serial
	Serial.begin(9600);
}

void loop() {
  int i;
   if (digitalRead(pinoSensor) == LOW) {
		Serial.println("Robo do lado do braco");
		// Nos testes, o sensor manda um sinal LOW quando o objeto esta proximo
		// OBS: Precisa ajustar a "sensibilidade" do sensor, de modo que detecte somente o robo
		// Abaixa o braco para chegar perto do cubo
		Serial.println("Abaixando braco...");
		for (i = 300; i > 0; --i) {
			servo1.write(i);
			Serial.println(i);
			delay(10);
		}
		delay(100);

		// Liga o eletroima
		Serial.println("Ligando eletroima...");
		digitalWrite(pinoEletroIma, HIGH);
		delay(10);

		// Ergue novamente o braco
		Serial.println("Erguendo braco...");
		for (i = 0; i < 90; ++i) {
			servo1.write(i);
			Serial.println(i);
			delay(10);
		}
		delay(100);

		// Move o braco para a esquerda (deixar em cima do robo)
		Serial.println("Movendo braco para a esquerda...");
		for (i = 0; i < 300; ++i) {
			servoBase.write(i);
			Serial.println(i);
			delay(10);
		}
		delay(100);

		// Abaixa o braco
		Serial.println("Abaixando o braco...");
		for (i = 90; i > 0; --i) {
			servo1.write(i);
			Serial.println(i);
			delay(10);
		}
		delay(100);

		// Desliga o eletroima
		Serial.println("Desligando eletroima");
		digitalWrite(pinoEletroIma, LOW);

		// Ergue novamente o braco
		Serial.println("Erguendo braco");
		for (i = 0; i < 90; ++i) {
			servo1.write(i);
			Serial.println(i);
			delay(10);
		}
		delay(100);
	}
}
