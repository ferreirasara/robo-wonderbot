void setup() {
  // put your setup code here, to run once:
  // Uma variavel para cada sensor. Serao variaveis globais,
  // para poderem ser acessadas e escritas pela funcao de ler os sensores
  // SEGUE_LINHA_1
  // SEGUE_LINHA_2
  // SEGUE_LINHA_3
  // DISTANCIA_FRONTAL
  // DISTANCIA_LATERAL
  // MOTOR_1
  // MOTOR_2
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
}
