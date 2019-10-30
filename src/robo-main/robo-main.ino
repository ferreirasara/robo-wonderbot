#include "defines.h" 	// Arquivo header com todas as definicoes de constantes e variaveis
#include <AFMotor.h>	// Biblioteca para os motores

// --------------------------------------------------
// INICIALIZACAO DOS OBJETOS
// --------------------------------------------------

// Declaracao dos objetos que serao utilizados para cada motor
// Verificar se sera utilizada a biblioteca, ou o controle vai ser feito manualmente
// AF_DCMotor motorDireita(pinoMotorDireita);
// AF_DCMotor motorEsquerda(pinoMotorEsquerda);

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

	// Inicializa o robo no modo de inicio, para nao gerar confusao
	modo = INICIO;
}

void loop() {
	// Gera uma interrupcao no processador, para ler os dados dos sensores
	leSensores();
	// Verifica o modo de operacao
	switch (modo) {
		case INICIO:
			while (flagFimDeCurso == LOW) { // Verificar se a chave ativada gera LOW ou HIGH
				// Enquanto o robo nao recebe o cubo, fica parado esperando
				motorEsquerda.run(RELEASE);
				motorDireita.run(RELEASE);
			}
			if (flagFimDeCurso == HIGH) {
				// Quando o robo está com o cubo, pode seguir em frente
				modo = PERCURSO;
				motorEsquerda.run(FORWARD);
				motorDireita.run(FORWARD);
				delay(1000); // Tempo para o robo sair da linha horizontal
			}
		case PERCURSO:
			if (semLinha()) {
				// Seta os dois motores com a velocidade inicial,
				// para garantir que o mesmo vai seguir em linha reta
				motorEsquerda.setSpeed(velocidadeInicialEsquerda);
				motorDireita.setSpeed(velocidadeInicialDireita);
				motorEsquerda.run(FORWARD);
				motorDireita.run(FORWARD);
				delay(1000); // verificar quanto tempo o robo deve andar para reencontrar a linha
				break; // Volta para o inicio do laco
			}
			if (fimPercurso()) {
				// Robo chegou ao fim do percurso
				modo = FIM;
				break;
			}
			analisaSensores(); // Analisa os dados dos sensores para saber se o robo esta na linha
			calcularPID(); // Faz o calculo do PID para controlar os motores
			controlePID(); // A partir do calculo PID, ajusta os motores
		case FIM:
			while (flagFimDeCurso == HIGH) { // Verificar se a chave ativada gera LOW ou HIGH
				// Enquanto o robo ainda esta com o cubo, fica parado esperando
				motorEsquerda.run(RELEASE);
				motorDireita.run(RELEASE);
			}
			if (flagFimDeCurso == LOW) {
				// Quando o robo está sem o cubo, pode seguir em frente
				modo = PERCURSO;
				motorEsquerda.run(FORWARD);
				motorDireita.run(FORWARD);
				delay(1000); // Tempo para o robo sair da linha horizontal
			}
	}
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

bool fimPercurso() {
	if (vetorSensores[0] == HIGH && vetorSensores[1] == HIGH && vetorSensores[2] == HIGH) {
		// Robo chegou ao final do percurso, precisa devolver o cubo
		return true;
	}
}

bool semLinha() {
	if (vetorSensores[0] == LOW && vetorSensores[1] == LOW && vetorSensores[2] == LOW) {
		// Robo nao identificou a linha, pode ser uma interrupção
		return true;
	}
}

void analisaSensores() {
	if (vetorSensores[0] == LOW && vetorSensores[1] == HIGH && vetorSensores[2] == LOW) {
		erro = -2;
	} else if (vetorSensores[0] == LOW && vetorSensores[1] == HIGH && vetorSensores[2] == LOW) {
		erro = -1;	
	} else if (vetorSensores[0] == LOW && vetorSensores[1] == HIGH && vetorSensores[2] == LOW) {
		erro = 0;	
	} else if (vetorSensores[0] == LOW && vetorSensores[1] == HIGH && vetorSensores[2] == LOW) {
		erro = 1;
	} else if (vetorSensores[0] == LOW && vetorSensores[1] == HIGH && vetorSensores[2] == LOW) {
		erro = 2;
	}
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