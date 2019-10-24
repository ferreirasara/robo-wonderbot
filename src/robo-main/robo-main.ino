#include "defines.h" 	// Arquivo header com todas as definicoes de constantes e variaveis
#include <HCSR04.h>		// Biblioteca para os sensores de distancia
#include <AFMotor.h>	// Biblioteca para os motores

// INICIALIZACAO DOS OBJETOS

// Declaracao dos objetos que serao utilizados para cada motor
AF_DCMotor motorDireita(pinoMotorDireita);
AF_DCMotor motorEsquerda(pinoMotorEsquerda);

void setup() {
	// Inicializacao dos motores
	// Obs: temos que ver uma velocidade ideal para os motores,
	// e passar como parametro para a funcao setSpeed
	motorEsquerda.setSpeed(velocidadeInicialEsquerda);
	motorDireita.setSpeed(velocidadeInicialDireita);
	motorEsquerda.run(RELEASE); // RELEASE -> motor parado
	motorDireita.run(RELEASE);

	// Inicializacao dos sensores de linha
	pinMode(pinoSensorLinha1, INPUT);
	pinMode(pinoSensorLinha2, INPUT);
	pinMode(pinoSensorLinha3, INPUT);

	// Inicializacao do fim de curso
	pinMode(pinoFimDeCurso, INPUT);

	// Inicializa o robo no modo de ida, para nao gerar confusao
	modo = PERCURSO_IDA;
}

void loop() {
	// Gera uma interrupcao no processador, para ler os dados dos sensores
	leSensores();
	// Verifica o modo de operacao
	switch (modo) {
		case PERCURSO_IDA:
			continue;
		case PERCURSO_VOLTA:
			continue;
	}
	// Liga os motores
	motorDireita.run(FORWARD); // FORWARD -> para frente
	motorEsquerda.run(FORWARD);
}

void leSensores() {
	// Aqui sera feita a leitura dos dados de cada sensor, e armazenar os mesmos nas variaveis globais

	// Leitura dos sensores de linha
	vetorSensores[0] = digitalRead(pinoSensorLinha1);
	vetorSensores[1] = digitalRead(pinoSensorLinha2);
	vetorSensores[2] = digitalRead(pinoSensorLinha3);

	// Leitura do cubo
	flagFimDeCurso = digitalRead(pinoFimDeCurso);
}

int analisarSensoresLinha() {
	
}

void calcularPID() {
	P = erro;
	I = I + erro;
	D = erro - erroAnterior;
	valorPID = (Kp * P) + (Ki * I) + (Kd * D);
	erroAnterior = erro;
}

void controlePID() {
	// Planejar como sera feito o controle da velocidade em cima do PID
}