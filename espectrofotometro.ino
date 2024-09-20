// inclusao da biblioteca 'LiquidCrystal'
#include <LiquidCrystal.h>


int ledAzul = 8;
int ledVerde = 9;
int ledVermelho = 10;

int ldr;

int corAtual = 0;
float percentual;

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

void setup()
{
  
  
  
 lcd.begin(16, 2);  // Configura o LCD como 16 colunas e 2 linhas
 lcd.setCursor(0, 0);
 lcd.print("ESPECTROFOTOMETRO!");  // Exibe um texto simples
 
 Serial.begin (9600); //iniciar a comunicação serial
 Serial.println ("\n\nESPECTROFOTOMETRO!");
 
 pinMode(ledAzul,OUTPUT);
 pinMode(ledVerde,OUTPUT);
 pinMode(ledVermelho,OUTPUT);

 
}

void loop()
{
  
  switch (corAtual) {
    case 0:
      Vermelho();   // Função para acionamento na cor vermelha
      break;
    case 1:
      Verde();      // Função para acionamento na cor verde
      break;
    case 2:
      Azul();       // Função para acionamento na cor azul
      break;
    
  }

  corAtual++;  // Passa para a próxima cor no próximo ciclo
  if (corAtual > 2) {  // Se todas as cores já passaram, reinicia o ciclo
    corAtual = 0;
  }
  
  delay(1000);
  for (int i = 0; i < 18; i++) {
    lcd.scrollDisplayLeft();
    delay(150);  // Ajuste o valor do delay para controlar a velocidade
  }

  delay(500);  // Espera um pouco antes de começar novamente

  // Opcional: rolar de volta para a direita (pode remover esta parte se não quiser rolar de volta)
  for (int i = 0; i < 18; i++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  
  delay(1000);


//leitura do LDR
   ldr = analogRead(A1);
  //float percentual = map(ldr,0.0,1023.0,0.0,100.0);
  float percentual = map(ldr,1023.0,0.0,100.0,0.0);
 
//envia dados para o serial monitor
  Serial.print("Luz: ");  
  delay(50);    
     
//envia dados para o serial monitor
  Serial.print(percentual);
  Serial.print("% ");
  Serial.print(ldr);
  Serial.print("\n");

//Define posição do lcd
  lcd.setCursor(0, 1);		// Exibe na segunda linha
  lcd.print("Luz  ");
  lcd.print(percentual);
  lcd.print("%  ");
  lcd.print(ldr);
 

  delay(2000); //intervalo de 5 seguntos para o sensor capturar a luz
  
  DesligarLuzes();
  delay(50);
  
 
}

void Vermelho() {
  digitalWrite(ledVermelho, HIGH);  // Liga vermelho
}

void Verde() {
  digitalWrite(ledVerde, HIGH);     // Liga verde
}

void Azul() {
  digitalWrite(ledAzul, HIGH);      // Liga azul
}

void DesligarLuzes() {
  digitalWrite(ledAzul, LOW);      // Desliga azul
  digitalWrite(ledVerde, LOW);     // Desliga verde
  digitalWrite(ledVermelho, LOW);  // Desliga vermelho
}
