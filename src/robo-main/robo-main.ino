#include "defines.h" 	// Arquivo header com todas as definicoes de constantes e variaveis
#include <HCSR04.h>		// Biblioteca para os sensores de distancia
#include <AFMotor.h>	// Biblioteca para os motores

// INICIALIZACAO DOS OBJETOS

// Declaracao dos objetos que serao utilizados para cada sensor
UltraSonicDistanceSensor sensorFrontal(trigFrontal, echoFrontal);
UltraSonicDistanceSensor sensorDireita(trigDireita, echoDireita);
UltraSonicDistanceSensor sensorEsquerda(trigEsquerda, trigDireita);

// Declaracao dos objetos que serao utilizados para cada motor
AF_DCMotor motorDireita(pinoMotorDireita);
AF_DCMotor motorEsquerda(pinoMotorEsquerda);

void setup() {
	// Inicializacao dos motores
	// Obs: temos que ver uma velocidade ideal para os motores,
	// e passar como parametro para a funcao setSpeed
	motorEsquerda.setSpeed(200);
	motorDireita.setSpeed(200);
	motorEsquerda.run(RELEASE); // RELEASE -> motor parado
	motorDireita.run(RELEASE);

	// Inicializacao dos sensores de linha
	pinMode(sensorLinha1, INPUT);
	pinMode(sensorLinha2, INPUT);
	pinMode(sensorLinha3, INPUT);
}

void loop() {
	// Liga os motores
	// Obs: temes que ver se tem necessidade de fazer alguma verificacao antes de ligar os motores
	motorDireita.run(FORWARD); // FORWARD -> para frente
	motorEsquerda.run(FORWARD);
	// Gera uma interrupcao no processador, para ler os dados dos sensores
	leSensores();
	// Com os dados atualizados, atua em cima de cada um
	// Verificacao de erros para os sensores de linha
	erroSensorLinha = analisarSensoresLinha();
	// Verifica o modo de operacao
	switch (mode) {
		case NA_LINHA:
			continue;
		case FORA_DA_LINHA:
			// Caso nao tenha linha, anda um pouco para frente, para ver se nao e uma interrupcao
			continue;
	}
	// Verifica se tem um obstaculo na frente (caixa)
	// Caso tenha, deve iniciar a rotina para contornar o obstaculo
	// Verifica se o robo chegou no final do percurso
}

void leSensores() {
	// Aqui sera feita a leitura dos dados de cada sensor, e armazenar os mesmos nas variaveis globais
	// Leitura dos sensores de distancia
	distanciaFrontal = sensorFrontal.measureDistanceCm();
	distanciaDireita = sensorFrontal.measureDistanceCm();
	distanciaEsquerda = sensorFrontal.measureDistanceCm();

	// Leitura dos sensores de linha
	vetorSensoresLinha[0] = digitalRead(sensorLinha1);
	vetorSensoresLinha[1] = digitalRead(sensorLinha2);
	vetorSensoresLinha[2] = digitalRead(sensorLinha3);
}

int analisarSensoresLinha() {
	// Verifica se o robo esta centralizado na linha
	if (vetorSensoresLinha[0] == LOW && vetorSensoresLinha[1] == HIGH && vetorSensoresLinha[3] == LOW) {
		// O robo esta na linha
		mode = NA_LINHA;
		return 0;
	} else if (vetorSensoresLinha[0] == HIGH && vetorSensoresLinha[1] == LOW && vetorSensoresLinha[3] == LOW) {
		// O robo esta fora da linha. Virar para a esquerda
		mode = NA_LINHA;
		return 1;
	} else if (vetorSensoresLinha[0] == LOW && vetorSensoresLinha[1] == LOW && vetorSensoresLinha[3] == HIGH) {
		// O robo esta fora da linha. Virar para a direita
		mode = NA_LINHA;
		return 2;
	} else if (vetorSensoresLinha[0] == LOW && vetorSensoresLinha[1] == LOW && vetorSensoresLinha[3] == LOW) {
		// O robo saiu da linha. Reencontrar a linha
		mode = FORA_DA_LINHA;
		return 3;
	} else {
		// Verificar se pode acontecer outras situacoes,
		// or exemplo todos em high, mais de um em high.
	}
}

