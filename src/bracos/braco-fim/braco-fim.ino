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
}

void loop() {
	if (digitalRead(pinoSensor) == LOW) { // Verifica se o robo esta parado ao lado do braco
		// Nos testes, o sensor manda um sinal LOW quando o objeto esta proximo
		// OBS: Precisa ajustar a "sensibilidade" do sensor, de modo que detecte somente o robo
		// Abaixa o braco para chegar perto do cubo
		for (int i = 90; i > 0; --i) {
			posicaoServo1.write(i);
			delay(1);
		}
		// Liga o eletroima
		digitalWrite(pinoEletroIma, HIGH);

		// Ergue novamente o braco
		for (int i = 0; i < 90; ++i) {
			posicaoServo1.write(i);
			delay(1);
		}

		// Move o braco para a esquerda (deixar em cima do robo)
		for (int i = 0; i < 180; ++i) {
			posicaoServoBase.write(i);
			delay(1);
		}

		// Abaixa o braco
		for (int i = 90; i > 0; --i) {
			posicaoServo1.write(i);
			delay(1);
		}
		// Desliga o eletroima
		digitalWrite(pinoEletroIma, LOW);

		// Ergue novamente o braco
		for (int i = 0; i < 90; ++i) {
			posicaoServo1.write(i);
			delay(1);
		}
	}
}