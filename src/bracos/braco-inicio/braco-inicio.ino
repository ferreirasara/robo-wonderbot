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
  int i;
//	if (digitalRead(pinoSensor) == LOW) { // Verifica se o robo esta parado ao lado do braco
   if (true) {
		// Nos testes, o sensor manda um sinal LOW quando o objeto esta proximo
		// OBS: Precisa ajustar a "sensibilidade" do sensor, de modo que detecte somente o robo
		// Abaixa o braco para chegar perto do cubo
//		for (i = 300; i > 0; --i) {
//			servo1.write(i);
//			delay(10);
//		}
    while(true) {
      servo1.write(90);
    }
		// Liga o eletroima
		//digitalWrite(pinoEletroIma, HIGH);

		// Ergue novamente o braco
		for (i = 0; i < 90; ++i) {
			//servo1.write(i);
			//delay(10);
		}

		// Move o braco para a esquerda (deixar em cima do robo)
		for (i = 0; i < 300; ++i) {
			servoBase.write(i);
			delay(10);
		}

		// Abaixa o braco
		for (i = 90; i > 0; --i) {
			//servo1.write(i);
			//delay(10);
		}
		// Desliga o eletroima
		//digitalWrite(pinoEletroIma, LOW);

		// Ergue novamente o braco
		for (i = 0; i < 90; ++i) {
			//servo1.write(i);
			//delay(10);
		}
	}
}
