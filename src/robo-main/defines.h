// --------------------------------------------------
// DEFINICOES DAS CONSTANTES
// --------------------------------------------------

// Declaracao dos pinos que serao usados para os motores
// Obs: verificar quais pinos serao utilizados, e quantos serao para cada motor
#define pinoMotorEsquerda
#define pinoMotorDireita

// Declaracao das velocidades iniciais dos motores
// Verificar qual e a velocidade ideal
#define velocidadeInicialEsquerda
#define velocidadeInicialDireita

// Declaracao dos pinos que serao utlizados para os sensores de linha
// Verificar a possibilidade de utilizar mais sensores, para ter mais 
#define pinoSensorLinha1
#define pinoSensorLinha2
#define pinoSensorLinha3

// Declaracao do pino utilizado para verificar o cubo
#define pinoFimDeCurso

// Declaracao dos modos de operacao
#define PERCURSO_IDA 	0
#define PERCURSO_VOLTA 	1

// Declaracao das constantes que serao utilizadas no controle PID
// Verificar os valores ideais para o funcionamento correto do robo
#define Kp
#define Ki
#define Kd

// --------------------------------------------------
// DECLARACAO DAS VARIAVEIS
// --------------------------------------------------

// Declaracao da flag do fim de curso
int flagFimDeCurso;

// Declaracao do vetor para armazenar as entradas dos sensores de linha
int* vetorSensores[3];

// Declaracao da variavel utilizada para controlar os sensores de linha
// Obs: 0 -> sensor do meio na linha. Nao precisa virar
//      1 -> primeiro sensor na linha. Virar para a esquerda
//      2 -> terceiro sensor na linha. Virar para a direita
//      3 -> nenhum sensor na linha. Reencontrar a linha
int erroSensorLinha;

// Declaracao da variavel para controlar o modo de operacao
int modo;

// Declaracao das variaveis utilizadas para controle PID
double valorPID = 0;
double erro = 0;
double erroAnterior = 0;
double P = 0;
double I = 0;
double D = 0;

// Declaracao das variaveis de controle de velocidade do robo
int velocidadeMotorEsquerda;
int velocidadeMotorDireita;