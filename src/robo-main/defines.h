// --------------------------------------------------
// DEFINICOES DAS CONSTANTES
// --------------------------------------------------

// Declaracao dos pinos que serao usados para os motores
// Serao usados tres pinos para cada motor
#define pino1MotorEsquerda 50
#define pino2MotorEsquerda 52
#define pinoVelocidadeMotorEsquerda 3
#define pino1MotorDireita 46
#define pino2MotorDireita 48
#define pinoVelocidadeMotorDireita 2

// Declaracao das velocidades iniciais dos motores
// Verificar qual e a velocidade ideal
#define velocidadeInicialEsquerda 60
#define velocidadeInicialDireita 60

// Declaracao dos pinos que serao utlizados para os sensores de linha
// Verificar a possibilidade de utilizar mais sensores, para ter mais 
#define pinoSensorLinha1 47
#define pinoSensorLinha2 49
#define pinoSensorLinha3 51

// Declaracao do pino utilizado para verificar o cubo
#define pinoCubo 41

// Declaracao dos pinos utilizados para o sensor ultrassonico
#define trigger 33
#define echo 31

// Declaracao dos modos de operacao
#define INICIO		0
#define PERCURSO 	1
#define FIM 		  2

// Declaracao das constantes que serao utilizadas no controle PID
// Verificar os valores ideais para o funcionamento correto do robo
#define Kp 5
#define Ki 5
#define Kd 5

// --------------------------------------------------
// DECLARACAO DAS VARIAVEIS
// --------------------------------------------------

// Declaracao do vetor para armazenar as entradas dos sensores de linha
int* vetorSensores[3];
// Declaracao da variavel do sensor do cubo
int cubo;

// Declaracao da variavel para controlar o modo de operacao
// Inicializa o robo no modo de inicio, para nao gerar confusao
int modo = INICIO;

// Declaracao das variaveis utilizadas para controle PID
float valorPID = 0;
float erro = 0;
float erroAnterior = 0;
float P = 0;
float I = 0;
float D = 0;

// Declaracao das variaveis de controle de velocidade do robo
int velocidadeMotorEsquerda;
int velocidadeMotorDireita;

// Declaracao das variaveis para controle do sensor ultrassonico
long tempo;
double distancia;
