//  int ledVermelho = 2;
#define LED_VERDE 2
#define LED_AMARELO 3
#define LED_VERMELHO 4
#define LED_AZUL 5
#define INDEFINIDO -1

#define BOTAO_VERDE 8
#define BOTAO_AMARELO 9
#define BOTAO_VERMELHO 10
#define BOTAO_AZUL 11

#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

#define TAMANHO_SEQUENCIA 4

int sequenciaLuzes[TAMANHO_SEQUENCIA];

enum Estados{
  PRONTO_PARA_PROXIMA_RODADA,
  USUARIO_RESPONDENDO,
  JOGO_FINALIZADO_SUCESSO,
  JOGO_FINALIZADO_FALHA
};

int rodada = 0;

int ledsRespondidos = 0;

void setup() {
  
  // Serial.begin(9600);
  // iniciaPortas();
  // iniciaJogo();
}


void loop() {
  
  switch( estadoAtual()){
    case PRONTO_PARA_PROXIMA_RODADA:
         Serial.println("PRONTO_PARA_PROXIMA_RODADA");

         preparaNovaRodada();
       
         break;
    case USUARIO_RESPONDENDO:
        processaRespostaUsuario();
        Serial.println("USUARIO_RESPONDENDO");
        break;
    case JOGO_FINALIZADO_SUCESSO:
        jogoFinalizadoSucesso();
        Serial.println("JOGO_FINALIZADO_SUCESSO");
        break;
    case JOGO_FINALIZADO_FALHA:
        jogoFinalizadoFalha();
        Serial.println("JOGO_FINALIZADO_FALHA");
        break;
  };
   delay(MEIO_SEGUNDO);
}

void iniciaJogo(){

 int jogo = analogRead(0);
  randomSeed(jogo);

  for(int i = 0; i < TAMANHO_SEQUENCIA; i++){
    sequenciaLuzes[i] =  sorteiaCor();
  }

}

int estadoAtual(){
  if(rodada <= TAMANHO_SEQUENCIA){
    if(ledsRespondidos == rodada){
       return PRONTO_PARA_PROXIMA_RODADA;
    }else{
      return USUARIO_RESPONDENDO;
    }
    
  }else if(rodada == TAMANHO_SEQUENCIA + 1){
      return JOGO_FINALIZADO_SUCESSO;
  }else{
    return JOGO_FINALIZADO_FALHA;
  }
}

void preparaNovaRodada(){
    rodada++;
    ledsRespondidos = 0;

    if(rodada <= TAMANHO_SEQUENCIA){
      tocaLedsRodada();
    }
    
}

void processaRespostaUsuario(){

  int resposta = checaRespostaJogador();

  Serial.println(resposta);

  if(resposta == INDEFINIDO){
    return;
  }

  if(resposta == sequenciaLuzes[ledsRespondidos]){
    ledsRespondidos++;
  }else{
    Serial.println("Resposta errada");
    rodada = TAMANHO_SEQUENCIA + 2;
  }

  
}

void tocaLedsRodada(){
    for(int i = 0; i < rodada; i++){
    piscaLed(sequenciaLuzes[i]);
  }
}

int sorteiaCor(){
  
  return random(LED_VERDE, LED_AZUL + 1);
}

void iniciaPortas(){
  pinMode(LED_VERDE,OUTPUT);
  pinMode(LED_AMARELO,OUTPUT);
  pinMode(LED_VERMELHO,OUTPUT);
  pinMode(LED_AZUL,OUTPUT);

  pinMode(BOTAO_VERDE, INPUT_PULLUP);
  pinMode(BOTAO_AMARELO, INPUT_PULLUP);
  pinMode(BOTAO_VERMELHO, INPUT_PULLUP);
  pinMode(BOTAO_AZUL, INPUT_PULLUP);


}

int checaRespostaJogador(){

  if(digitalRead(BOTAO_VERDE) == LOW){
      return piscaLed(LED_VERDE);
  }

  if(digitalRead(BOTAO_AMARELO) == LOW){
      return piscaLed(LED_AMARELO);
  }

  if(digitalRead(BOTAO_VERMELHO) == LOW){
      return piscaLed(LED_VERMELHO);
  }

  if(digitalRead(BOTAO_AZUL) == LOW){
      return piscaLed(LED_AZUL);
  }

  return INDEFINIDO;


}



void jogoFinalizadoSucesso(){
    piscaLed(LED_VERDE);
    piscaLed(LED_AMARELO);
    piscaLed(LED_VERMELHO);
    piscaLed(LED_AZUL);
    delay(MEIO_SEGUNDO);
}

void jogoFinalizadoFalha(){
  digitalWrite(LED_VERDE,HIGH);
  digitalWrite(LED_AMARELO,HIGH);
  digitalWrite(LED_VERMELHO,HIGH);
  digitalWrite(LED_AZUL,HIGH);

  delay(UM_SEGUNDO);

  digitalWrite(LED_VERDE,LOW);
  digitalWrite(LED_AMARELO,LOW);
  digitalWrite(LED_VERMELHO,LOW);
  digitalWrite(LED_AZUL,LOW);
}

int piscaLed(int portaLed){

  
  digitalWrite(portaLed,HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(portaLed,LOW);
  delay(MEIO_SEGUNDO);

  return portaLed;
}
