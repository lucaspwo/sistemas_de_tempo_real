#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <EEPROM.h>

// Pinagem para o display
#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8

// Pinos para LED RGB
#define azul  5
#define verde 6
#define verme 7

// Botoes para entrada do usuario
#define b_azul  A3
#define b_amar  A2
#define b_verm  A1
#define b_verde A0

// Definicoes de cores para o display
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, cs, dc, rst); // Inicializacao do display

int SWarray[10];

unsigned int resultado = 0; // Var. para guardar o tempo de resposta em millis
bool acerto[10] = {false, false, false, false, false, false, false, false, false, false}; // Var. para guardar quais repostas foram acertadas
int acertos = 0;  // Var. para contar a quantidade de respostas certas
unsigned int score = 0; // Var. para receber a pontuacao do usuario
int addr = 0; // Valor da primeira posicao da eeprom
unsigned int hiscore; // Var. para armazenar a pontuacao da eeprom

bool debug = false;       // Modo debug: true para saida de valores na serial
bool modoRapido = false;  // Modo rapido: true para pular a exibicao das instrucoes
bool resetHiscore = false;// Resetar a pontuacao na eeprom: true para escrever o valor do proximo teste

void setup(void) {
  randomSeed(analogRead(5));

  if(debug)
    Serial.begin(9600);
  display.begin();
  display.fillScreen(BLACK);

  intro();

  if(!modoRapido)
    instrucoes();
  
  contagem();
  
  teste();

  estatisticas();
}

void loop() {
}

void intro(){
  display.fillScreen(BLACK);
  display.setCursor(0,23);
  display.print("Teste de reflexo");
  display.setCursor(7,33);
  display.print("DCA0125 - UFRN");
  delay(5000);
}

void instrucoes(){
  display.fillScreen(BLACK);
  display.setCursor(0,0);
  display.setTextColor(YELLOW);
  display.print("INSTRUCOES:\n");
  display.setTextColor(WHITE);
  display.print("Aperte o botao\ncorrespondente a\ncor para marcar\num acerto, den-\ntro de 5 segun-\ndos.");
  delay(10000);
  display.fillScreen(BLACK);
  display.setCursor(0,0);
  display.setTextColor(YELLOW);
  display.print("INSTRUCOES:\n");
  display.setTextColor(WHITE);
  display.print("Caso aperte um\nbotao ERRADO ou\ndemore mais de 5\nsegundos para a-\npertar o botao\ncorreto...");
  delay(10000);
  display.fillScreen(BLACK);
  display.setCursor(0,0);
  display.setTextColor(YELLOW);
  display.print("INSTRUCOES:\n");
  display.setTextColor(WHITE);
  display.print("... sera conta-\nbilizada uma pe-\nnalidade de 5\nsegundos na pon-tuacao do teste.");
  delay(10000);
  display.fillScreen(BLACK);
  display.setCursor(0,0);
  display.setTextColor(YELLOW);
  display.print("INSTRUCOES:\n");
  display.setTextColor(WHITE);
  display.print("Botoes (da esq. para dir.):\n\n");
  display.setTextColor(BLUE);
  display.print("1- Azul\n");
  display.setTextColor(YELLOW);
  display.print("2- Amarelo\n");
  display.setTextColor(RED);
  display.print("3- Vermelho\n");
  display.setTextColor(GREEN);
  display.print("4- Verde\n");
  delay(10000);
}

void contagem(){
  display.fillScreen(BLACK);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.print("Iniciando em:\n");
  display.fillCircle(48, 32, 15, RED);
  display.setCursor(44,26);
  display.setTextSize(2);
  display.print("5");
  display.setCursor(44,25);
  display.setTextSize(1);
  display.setTextColor(BLUE);
  display.print("\n\n\n\n     1 ");
  display.setTextColor(YELLOW);
  display.print("2 ");
  display.setTextColor(RED);
  display.print("3 ");
  display.setTextColor(GREEN);
  display.print("4");
  delay(1000);
  display.fillCircle(48, 32, 15, CYAN);
  display.setCursor(44,26);
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.print("4");
  delay(1000);
  display.fillCircle(48, 32, 15, GREEN);
  display.setCursor(44,26);
  display.setTextSize(2);
  display.setTextColor(BLUE);
  display.print("3");
  delay(1000);
  display.fillCircle(48, 32, 15, WHITE);
  display.setCursor(44,26);
  display.setTextSize(2);
  display.setTextColor(RED);
  display.print("2");
  delay(1000);
  display.fillCircle(48, 32, 15, YELLOW);
  display.setCursor(44,26);
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.print("1");
  delay(1000);
  display.fillScreen(BLACK);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,23);
  display.print("INICIOU!");
  display.setCursor(44,25);
  display.setTextSize(1);
  display.setTextColor(BLUE);
  display.print("\n\n\n\n     1 ");
  display.setTextColor(YELLOW);
  display.print("2 ");
  display.setTextColor(RED);
  display.print("3 ");
  display.setTextColor(GREEN);
  display.print("4");
}

void estatisticas(){
  display.fillScreen(BLACK);
  display.setCursor(0,0);
  display.setTextColor(YELLOW);
  display.setTextSize(1);
  display.print("RESULTADOS:\n\n");
  display.setTextColor(WHITE);
  display.print("Acertos: ");
  display.print(acertos);
  display.print("\n");
  display.print("Tempo medio: \n");
  display.print(float(resultado)/10000, 4);
  display.print("s\n");
  display.print("Score: ");
  display.print(score);
  if(resetHiscore)
    hiscore = 0;
  else
    EEPROM.get(addr, hiscore);
  if(score > hiscore){
    EEPROM.put(addr, score);
    EEPROM.get(addr, hiscore);
    display.print("\n");
    display.print("Hi-score: ");
    display.print(hiscore);
    display.print("\n");
    display.setTextColor(RED);
    display.print(" NO");
    display.setTextColor(YELLOW);
    display.print("VO ");
    display.setTextColor(GREEN);
    display.print("HI");
    display.setTextColor(CYAN);
    display.print("-S");
    display.setTextColor(BLUE);
    display.print("CO");
    display.setTextColor(MAGENTA);
    display.print("RE");
    display.setTextColor(WHITE);
    display.print("!");
  } else {
    display.print("\n");
    display.print("Hi-score: ");
    display.print(hiscore);
  }
}

void teste(){
  for(int j=0; j<10; j++){
    delay(1000);
    switch (int(random(4))){
     case 0:
      piscaAmarelo(j);
      break;
     case 1:
      piscaVermelho(j);
      break;
     case 2:
      piscaAzul(j);
      break;
     case 3:
      piscaVerde(j);
      break;
    }
  }
  score = 50000;
  for(int l=0; l<10; l++){
    if(debug){
      Serial.print("SWarray["); Serial.print(l); Serial.print("]: ");
      Serial.println(SWarray[l]);
    }
    if(acerto[l] == true){
      resultado = resultado + SWarray[l];
      score = score - SWarray[l];
      acertos = acertos + 1;
    }
    if(acerto[l] == false){
      resultado = resultado + SWarray[l];
      score = score - 5000;
    }
  }
  if(debug){
    Serial.print("Resultado: ");
    Serial.println(resultado);
  }
}

void piscaAzul(int v){
  pinMode(azul, OUTPUT);
  pinMode(verde, INPUT);
  pinMode(verme, INPUT);
  digitalWrite(azul, LOW);

  int agora = millis();
  while(millis() - agora < 5000){
    if(analogRead(b_azul) > 1000){
      acerto[v] = true;
      break;
    }
    if(analogRead(b_verm) > 1000 || analogRead(b_amar) > 1000 || analogRead(b_verde) > 1000){
      break;
    }
  }
  SWarray[v] = millis() - agora;
  pinMode(azul, INPUT);
  pinMode(verde, INPUT);
  pinMode(verme, INPUT);
  if(debug){
    Serial.print("Az: ");
    Serial.println(SWarray[v]);
  }
}

void piscaVermelho(int v){
  pinMode(azul, INPUT);
  pinMode(verde, INPUT);
  pinMode(verme, OUTPUT);
  digitalWrite(verme, LOW);

  int agora = millis();
  while(millis() - agora < 5000){
    if(analogRead(b_verm) > 1000){
      acerto[v] = true;
      break;
    }
    if(analogRead(b_azul) > 1000 || analogRead(b_amar) > 1000 || analogRead(b_verde) > 1000){
      break;
    }
  }
  SWarray[v] = millis() - agora;
  pinMode(azul, INPUT);
  pinMode(verde, INPUT);
  pinMode(verme, INPUT);
  if(debug){
    Serial.print("Vm: ");
    Serial.println(SWarray[v]);
  }
}

void piscaAmarelo(int v){
  pinMode(azul, INPUT);
  pinMode(verde, OUTPUT);
  pinMode(verme, OUTPUT);
  digitalWrite(verme, LOW);
  digitalWrite(verde, LOW);

  int agora = millis();
  while(millis() - agora < 5000){
    if(analogRead(b_amar) > 1000){
      acerto[v] = true;
      break;
    }
    if(analogRead(b_azul) > 1000 || analogRead(b_verm) > 1000 || analogRead(b_verde) > 1000){
      break;
    }
  }
  SWarray[v] = millis() - agora;
  pinMode(azul, INPUT);
  pinMode(verde, INPUT);
  pinMode(verme, INPUT);
  if(debug){
    Serial.print("Am: ");
    Serial.println(SWarray[v]);
  }
}

void piscaVerde(int v){
  pinMode(azul, INPUT);
  pinMode(verde, OUTPUT);
  pinMode(verme, INPUT);
  digitalWrite(verde, LOW);
  
  int agora = millis();
  while(millis() - agora < 5000){
    if(analogRead(b_verde) > 1000){
      acerto[v] = true;
      break;
    }
    if(analogRead(b_azul) > 1000 || analogRead(b_verm) > 1000 || analogRead(b_amar) > 1000){
      break;
    }
  }
  SWarray[v] = millis() - agora;
  pinMode(azul, INPUT);
  pinMode(verde, INPUT);
  pinMode(verme, INPUT);
  if(debug){
    Serial.print("Vd: ");
    Serial.println(SWarray[v]);
  }
}
