#include <HCSR04.h>		// Biblioteca para os sensores de distancia
#include <AFMotor.h>	// Biblioteca para os motores

// declaracao dos pinos que serao usados para os sensores de distancia
// exemplo: #define "constante" 1
#define trigFrontal
#define echoFrontal
#define trigDireita
#define echoDireita
#define trigEsquerda
#define echoEsquerda

// declaracao dos pinos que serao usados para os motores
// obs: verificar quais pinos serao utilizados, e quantos serao para cada motor
#define pinoMotorEsquerda
#define pinoMotorDireita

// declaracao dos pinos que serao utlizados para os sensores de linha
// verificar a possibilidade de utilizar mais sensores
#define sensorLinha1
#define sensorLinha2
#define sensorLinha3

// declaracao dos objetos que serao utilizados para cada sensor
UltraSonicDistanceSensor sensorFrontal(trigFrontal, echoFrontal);
UltraSonicDistanceSensor sensorDireita(trigDireita, echoDireita);
UltraSonicDistanceSensor sensorEsquerda(trigEsquerda, trigDireita);

// declaracao dos objetos que serao utilizados para cada motor
AF_DCMotor motorDireita(pinoMotorDireita);
AF_DCMotor motorEsquerda(pinoMotorEsquerda);

// declaracao das variaveis para armazenar as distancias
double distanciaFrontal;
double distanciaDireita;
double distanciaEsquerda;

// declaracao da variavel utilizada para controlar os sensores de linha
// obs: -1 >> primeiro sensor na linha. virar para a esquerda
//       0 >> sensor do meio na linha. nao precisa virar
//      +1 >> terceiro sensor na linha. virar para a direita
int sensorLinha;

void setup() {
	// inicializacao dos motores
	// obs: temos que ver uma velocidade ideal para os motores,
	// e passar como parametro para a funcao setSpeed
	motorEsquerda.setSpeed(200);
	motorDireita.setSpeed(200);
	motorEsquerda.run(RELEASE); // RELEASE >> motor parado
	motorDireita.run(RELEASE);

	// inicializacao dos sensores de linha
	pinMode(sensorLinha1, OUTPUT);
	pinMode(sensorLinha2, OUTPUT);
	pinMode(sensorLinha3, OUTPUT);
}

void loop() {
	// liga os motores
	// obs: temes que ver se tem necessidade de fazer alguma verificacao antes de ligar os motores
	motorDireita.run(FORWARD); // FORWARD >> para frente
	motorEsquerda.run(FORWARD);
	// Gera uma interrupcao no processador, para ler os dados dos sensores
	// Com os dados atualizados, atua em cima de cada um
	// Verifica se o robo esta centralizado na linha
	// Caso nao esteja, deve voltar para a linha
	// Caso nao tenha linha, anda um pouco para frente, para ver se nao e uma interrupcao
	// Verifica se tem um obstaculo na frente (caixa)
	// Caso tenha, deve iniciar a rotina para contornar o obstaculo
	// Verifica se o robo chegou no final do percurso
}

void le_sensores() {
	// Aqui ira ler os dados de cada sensor, e armazenar os mesmos nas variaveis globais
	// leitura dos sensores de distancia
	distanciaFrontal = sensorFrontal.measureDistanceCm();
	distanciaDireita = sensorFrontal.measureDistanceCm();
	distanciaEsquerda = sensorFrontal.measureDistanceCm();

	// leitura dos sensores de linha
	if (digitalRead(sensorLinha1) == LOW && digitalRead(sensorLinha1) == HIGH && digitalRead(sensorLinha1) == LOW) {
		// o robo esta na linha
		sensorLinha = 0;
	} else if (digitalRead(sensorLinha1) == LOW && digitalRead(sensorLinha1) == LOW && digitalRead(sensorLinha1) == HIGH) {
		// robo esta fora da linha. virar para a esquerda
		sensorLinha = -1;
	} else if (digitalRead(sensorLinha1) == HIGH && digitalRead(sensorLinha1) == LOW && digitalRead(sensorLinha1) == LOW) {
		// robo esta fora da linha. virar para a direita
		sensorLinha = 1;
	}
}
