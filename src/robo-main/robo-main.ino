#include "defines.h" 	// Arquivo header com todas as definicoes de constantes e variaveis

void setup() {
	// Inicializacao dos pinos da ponte h
	pinMode(pino1MotorDireita, OUTPUT);
	pinMode(pino2MotorDireita, OUTPUT);
	pinMode(pino1MotorEsquerda, OUTPUT);
	pinMode(pino2MotorEsquerda, OUTPUT);
	pinMode(pinoVelocidadeMotorDireita, OUTPUT);
	pinMode(pinoVelocidadeMotorEsquerda, OUTPUT);

	// Inicializacao dos sensores de linha
	pinMode(pinoSensorLinha1, INPUT);
	pinMode(pinoSensorLinha2, INPUT);
	pinMode(pinoSensorLinha3, INPUT);

	// Inicializacao do cubo
	pinMode(pinoCubo, INPUT);

	// Definindo o pino "trigger" como saída
	pinMode(trigger, OUTPUT);
	// Definindo o pino "echo" como entrada
	pinMode(echo, INPUT);
	// "Limpar" o pino trigger
	digitalWrite(trigger, LOW);
}

void loop() {
	// Gera uma interrupcao no processador, para ler os dados dos sensores
	leSensores();
	delay(10);
	// Verifica o modo de operacao
	switch (modo) {
		case INICIO:
			if (cubo == LOW) { // Verificar se a chave ativada gera LOW ou HIGH
				// Enquanto o robo nao recebe o cubo, fica parado esperando
				paraRobo();
				delay(500);
			} else {
				// Quando o robo está com o cubo, pode seguir em frente
				modo = PERCURSO;
				movimentaRobo();
			}
			break;
		case PERCURSO:
			// Verifica a ausencia da linha
			if (vetorSensores[0] == LOW && vetorSensores[1] == LOW && vetorSensores[2] == LOW) {
				// Seta os dois motores com a velocidade inicial,
				// para garantir que o mesmo vai seguir em linha reta
				movimentaRobo();
				delay(10);
				break;
			}
			// Verifica se os tres sensores estão apontando para a linha (fim do percurso)
			if (vetorSensores[0] == HIGH && vetorSensores[1] == HIGH && vetorSensores[2] == HIGH) {
				paraRobo();
				delay(10);
				// Robo chegou ao fim do percurso
				modo = FIM;
				break;
			}
			analisaSensores(); // Analisa os dados dos sensores para saber se o robo esta na linha
			while (distancia <= 15) {
				paraRobo();
				delay(10);
				leSensores();
				if (distancia > 15) {
					movimentaRobo();
					break;
				}
			}
			calcularPID(); // Faz o calculo do PID para controlar os motores
			controlePID(); // A partir do calculo PID, ajusta os motores
			break;
		case FIM:
			if (cubo == HIGH) { // Verificar se a chave ativada gera LOW ou HIGH
				// Enquanto o robo ainda esta com o cubo, fica parado esperando
				paraRobo();
				delay(500);
			} else {
				// Quando o robo está com o cubo, pode seguir em frente
				modo = PERCURSO;
				movimentaRobo();
				delay(10);
			}
    		break;
	}
}

void paraRobo() {
	// Ao setar todos os pinos em HIGH, os motores ficam parados
	digitalWrite(pino1MotorDireita, HIGH);
	digitalWrite(pino2MotorDireita, HIGH);
	digitalWrite(pino1MotorEsquerda, HIGH);
	digitalWrite(pino2MotorEsquerda, HIGH);
}

void movimentaRobo() {
	digitalWrite(pino1MotorDireita, HIGH);
	digitalWrite(pino2MotorDireita, LOW);
	digitalWrite(pino1MotorEsquerda, HIGH);
	digitalWrite(pino2MotorEsquerda, LOW);
	
	// Ajusta a velocidade para voltar a velocidade inicial
	analogWrite(pinoVelocidadeMotorDireita, velocidadeInicialDireita);
	delay(10);
	analogWrite(pinoVelocidadeMotorEsquerda, velocidadeInicialEsquerda);
	delay(10);
}

void leSensores() {
	// Aqui sera feita a leitura dos dados de cada sensor, e armazenar os mesmos nas variaveis globais

	// Leitura dos sensores de linha
	vetorSensores[0] = digitalRead(pinoSensorLinha1);
	vetorSensores[1] = digitalRead(pinoSensorLinha2);
	vetorSensores[2] = digitalRead(pinoSensorLinha3);
	delay(10);

	cubo = digitalRead(pinoCubo);
	delay(10);
	// Transmitindo o sinal do trigger, ligando-o
	digitalWrite(trigger, HIGH);
	// Tempo de transmissão de sinal (trigger ligado)
	delayMicroseconds(10);
	// Desligando o trigger
	digitalWrite(trigger, LOW);
	// Conta o tempo do pino "echo" ligado(HIGH) e armazena na variável "tempo"
	tempo = pulseIn(echo, HIGH);
	// Formula para calcular a distancia (em cm)
	distancia = (tempo * 0.034) / 2;
}

void analisaSensores() {
	if (vetorSensores[0] == HIGH && vetorSensores[1] == LOW && vetorSensores[2] == LOW) {
		erro = -2;
	} else if (vetorSensores[0] == HIGH && vetorSensores[1] == HIGH && vetorSensores[2] == LOW) {
		erro = -1;	
	} else if (vetorSensores[0] == LOW && vetorSensores[1] == HIGH && vetorSensores[2] == LOW) {
		erro = 0;	
	} else if (vetorSensores[0] == LOW && vetorSensores[1] == HIGH && vetorSensores[2] == HIGH) {
		erro = 1;
	} else if (vetorSensores[0] == LOW && vetorSensores[1] == LOW && vetorSensores[2] == HIGH) {
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
	// Um motor sempre será o inverso do outro.
	// Ex: um com 100, outro com 155 (a soma deve ser 255, o maximo da saida PWM)
	// Calcula a porcentagem para alteração na velocidade
	float porcentagem = valorPID / 255;
	float porcentagemInverso = 100 - porcentagem;
	if (erro < 0) {
		velocidadeMotorDireita = 255 * porcentagem;
		velocidadeMotorEsquerda = 255 * porcentagemInverso;
	} else if (erro > 0) {
		velocidadeMotorEsquerda = 255 * porcentagem;
		velocidadeMotorDireita = 255 * porcentagemInverso;
	} else {
		// Se o erro é 0, o robo esta na linha e pode andar reto
		movimentaRobo();
	}
}
