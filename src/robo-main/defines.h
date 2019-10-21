// --------------------------------------------------
// DEFINICOES DAS CONSTANTES
// --------------------------------------------------

// Declaracao dos pinos que serao usados para os sensores de distancia
// Exemplo: #define "constante" 1
#define trigFrontal
#define echoFrontal
#define trigDireita
#define echoDireita
#define trigEsquerda
#define echoEsquerda

// Declaracao dos pinos que serao usados para os motores
// Obs: verificar quais pinos serao utilizados, e quantos serao para cada motor
#define pinoMotorEsquerda
#define pinoMotorDireita

// Declaracao dos pinos que serao utlizados para os sensores de linha
// Verificar a possibilidade de utilizar mais sensores
#define sensorLinha1
#define sensorLinha2
#define sensorLinha3

// Declaracao dos modos de operacao
#define NA_LINHA 0
#define FORA_DA_LINHA 1

// --------------------------------------------------
// DECLARACAO DAS VARIAVEIS
// --------------------------------------------------

// Declaracao das variaveis para armazenar as distancias
double distanciaFrontal;
double distanciaDireita;
double distanciaEsquerda;

// Declaracao do vetor para armazenar as entradas dos sensores de linha
int* vetorSensoresLinha[3];

// Declaracao da variavel utilizada para controlar os sensores de linha
// Obs: 0 -> sensor do meio na linha. Nao precisa virar
//      1 -> primeiro sensor na linha. Virar para a esquerda
//      2 -> terceiro sensor na linha. Virar para a direita
//      3 -> nenhum sensor na linha. Reencontrar a linha
int erroSensorLinha;

// Declaracao da variavel para controlar o modo de operacao
int mode;

// Declaracao da variavel para controle PID
double valorPID;