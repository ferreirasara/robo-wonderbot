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

	// Inicia os servos na posicao 0
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
    if (pinoSensor == HIGH) { // Verifica se o robo esta parado ao lado do braco
        // Abaixa o braco para chegar perto do cubo

        // Liga o eletroima
        digitalWrite(pinoEletroIma, HIGH);

        // Ergue novamente o braco

        // Move o braco para a esquerda (deixar em cima do robo)
        posicaoServoBase = 180; // Verificar qual sera o angulo
        servoBase.write(posicaoServoBase)

        // Abaixa o braco

        // Desliga o eletroima
        digitalWrite(pinoEletroIma, LOW);

        // Ergue novamente o braco

    }
}