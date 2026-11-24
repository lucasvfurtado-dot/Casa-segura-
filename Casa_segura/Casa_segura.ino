#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo porta;
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
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
