//  int ledVermelho = 2;
#define LED_VERMELHO 2
#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_VERMELHO,OUTPUT);
  digitalWrite(LED_VERMELHO,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  piscaLed(LED_VERMELHO);
  
}

void piscaLed(int portaLed){

  Serial.println(portaLed);
  digitalWrite(portaLed,HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(portaLed,LOW);
  delay(MEIO_SEGUNDO);
}
