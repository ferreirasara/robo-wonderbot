#include <HCSR04.h>

// declaracao dos pinos que serao usados para os sensores de distancia
int trigFrontal;
int echoFrontal;
int trigDireita;
int echoDireita;
int trigEsquerda;
int echoEsquerda;

// declaracao das variaveis para armazenar as distancias
double distanciaFrontal;
double distanciaDireita;
double distanciaEsquerda;

// declaracao dos objetos que serao utilizados para cada sensor
UltraSonicDistanceSensor sensorFrontal(trigFrontal, echoFrontal);
UltraSonicDistanceSensor sensorDireita(trigDireita, echoDireita);
UltraSonicDistanceSensor sensorEsquerda(trigEsquerda, trigDireita);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
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
}
