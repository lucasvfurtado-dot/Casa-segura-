#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo porta;

// Pinos
int pir = 8;
int buzzer = 6;
int ledVermelho = 13;
int ledVerde = A3;
int contraste = A0;
int botao1 = A1;
int botao2 = A2;
int botao3 = A5;

// Senha (botões 1, 3, 2, 1)
int senha[4] = {1, 3, 2, 1};
int digitada[4];
int posicao = 0;
int erros = 0;

void telaArmado() {
  lcd.clear();
  lcd.print("Sistema ARMADO");
  lcd.setCursor(0, 1);
  lcd.print("Digite a senha");
}

void mostrarSenha() {
  lcd.setCursor(0, 1);
  lcd.print("Senha: ");
  for (int i = 0; i < posicao; i++) {
    lcd.print("*");
  }
  for (int i = posicao; i < 4; i++) {
    lcd.print("_");
  }
  lcd.print("     ");
}

int lerBotao() {
  if (digitalRead(botao1) == LOW) {
    delay(50);
    while (digitalRead(botao1) == LOW) {}
    return 1;
  }
  if (digitalRead(botao2) == LOW) {
    delay(50);
    while (digitalRead(botao2) == LOW) {}
    return 2;
  }
  if (digitalRead(botao3) == LOW) {
    delay(50);
    while (digitalRead(botao3) == LOW) {}
    return 3;
  }
  return 0;
}
void abrirPorta() {
  for (int a = 0; a <= 90; a++) {
    porta.write(a);
    delay(15);
  }
}

void fecharPorta() {
  for (int a = 90; a >= 0; a--) {
    porta.write(a);
    delay(15);
  }
}
// Som de alarme de casa (dois tons agudos alternando)
void tocarAlarme(int vezes) {
  for (int i = 0; i < vezes; i++) {
    tone(buzzer, 3200);
    delay(120);
    tone(buzzer, 2400);
    delay(120);
  }
  noTone(buzzer);
}

// Confere se a senha digitada está certa
void conferirSenha() {
  bool certa = true;
  for (int i = 0; i < 4; i++) {
    if (digitada[i] != senha[i]) {
      certa = false;
    }
  }
  posicao = 0;

  if (certa) {
    erros = 0;
    lcd.clear();
    lcd.print("Senha correta!");
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);
    abrirPorta();

    // Contagem de 10 segundos com a porta aberta
    for (int t = 10; t > 0; t--) {
      lcd.clear();
      lcd.print("Sist. DESARMADO");
      lcd.setCursor(0, 1);
      lcd.print("Arma em ");
      lcd.print(t);
      lcd.print("s");
      delay(1000);
    }

    // Arma sozinho
    lcd.clear();
    lcd.print("Armando...");
    fecharPorta();
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, HIGH);
    delay(3000);   // tempo para sair da frente do sensor
    telaArmado();
  } else {
    erros++;
    lcd.clear();
    lcd.print("Senha errada!");
    if (erros >= 3) {
      tocarAlarme(12);   // 3 erros: alarme por uns 3 segundos
      erros = 0;
    } else {
      tone(buzzer, 600);
      delay(1000);
      noTone(buzzer);
    }
    telaArmado();
  }
}

void setup() {
  lcd.begin(16, 2);
  porta.attach(9);

  pinMode(contraste, OUTPUT);
  digitalWrite(contraste, LOW);

  pinMode(pir, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(botao3, INPUT_PULLUP);

  porta.write(0);
  digitalWrite(ledVermelho, HIGH);
  telaArmado();
}

void loop() {

  int botao = lerBotao();
  if (botao != 0) {
    digitada[posicao] = botao;
    posicao++;
    mostrarSenha();
  }

  
  if (posicao == 4) {
    conferirSenha();
  }

  
  if (digitalRead(pir) == HIGH) {
    lcd.clear();
    lcd.print("ALERTA! Presenca");
    while (digitalRead(pir) == HIGH) {
      tocarAlarme(1);
    }
    posicao = 0;
    telaArmado();
  }
}