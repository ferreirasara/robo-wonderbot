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
        posicaoServo1 = 0; // Verificar qual sera o angulo
        servoBase.write(posicaoServoBase);

        // Liga o eletroima
        digitalWrite(pinoEletroIma, HIGH);

        // Ergue novamente o braco
        posicaoServo1 = 0; // Verificar qual sera o angulo
        servoBase.write(posicaoServoBase);

        // Move o braco para a esquerda (deixar em cima do robo)
        posicaoServoBase = 0; // Verificar qual sera o angulo
        servoBase.write(posicaoServoBase);

        // Abaixa o braco
        posicaoServo1 = 0; // Verificar qual sera o angulo
        servoBase.write(posicaoServoBase);

        // Desliga o eletroima
        digitalWrite(pinoEletroIma, LOW);

        // Ergue novamente o braco
        posicaoServo1 = 0; // Verificar qual sera o angulo
        servoBase.write(posicaoServoBase);
    }
}
