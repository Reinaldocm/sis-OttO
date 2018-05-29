//----------------------------------------------------------------
//-- Robo Otto
//-- Adaptado por Luciana Rocha Cardoso
//-- 22/05/2018
//-----------------------------------------------------------------
//-- Primeira versão de teste para projeto de OTTO escolar simples
//-----------------------------------------------------------------

//nao foi usado estas bibliotecas
//#include <Oscillator.h>
//#include <US.h>
//#include <Otto.h>
//Otto Otto;  //This is Otto!
//---------------------------------------------------------

#include <IRremote.h>
#include <Buzzer.h>
#include <Servo.h>

//---------------------------------------------------------
//-- Primeiro passo: Certificar que os pinos dos servos estão na posição correta
/*
         ---------------
        |     O   O     |
        |---------------|
  YR 1==> |               | <== YL 2
         ---------------
            ||     ||
  RR 3==>   -----   ------  <== RL 4
         |-----   ------|

  servo1 [3]
  servo2 [2]
  servo3 [5]
  servo4 [4]
*/

//-----servo
Servo servo1, servo2, servo3, servo4;
//---------

int pinoRecepitorIR = 11;
int ledVermelho = 12;

// Definindo o código de cada ação que deverá ser realizada

int pin_buzzer = 10; //porta do buzzer
Buzzer Alarme(pin_buzzer);
IRrecv irrecv(pinoRecepitorIR);
decode_results results;
int i;

void setup()
{
  Serial.begin(9600);
  servo1.attach(3); // anexa o servomotor (físico), no pino 3, ao objeto servo1 (lógico), cima direita
  servo2.attach(2); // anexa o servomotor (físico), no pino 2, ao objeto servo2 (lógico), cima esquerda
  servo3.attach(5); // anexa o servomotor (físico), no pino 5, ao objeto servo3 (lógico), baixo direita
  servo4.attach(4); // anexa o servomotor (físico), no pino 4, ao objeto servo4 (lógico), baixa esquerda
  pinMode(ledVermelho, OUTPUT); // Definindo os pinos dos leds como saida

  irrecv.enableIRIn(); // Inicializa o receptor IR do controle remoto
}

void loop()
{
  servo1.write(69); //aqui o motor ficará a 0 graus, cima direita
  servo2.write(62); //aqui o motor ficará a 0 graus, cima esquerda
  servo3.write(85); //aqui o motor ficará a 0 graus, baixa direita
  servo4.write(65); //aqui o motor ficará a 0 graus

  delay(500);

  if (irrecv.decode(&results)) // Executa caso receba algum códico
  {
    Serial.println(results.value, HEX);

    if (results.value == 0xFF22DD) //Verifica se a tecla < foi acionada
    {
      digitalWrite(ledVermelho, HIGH); //Acende o led vermelho
    }
    if (results.value == 0xFFC23D) //Verifica se a tecla > foi acionada
    {
      digitalWrite(ledVermelho, LOW); //Apaga o led vermelho
    }
    if (results.value == 0xFF6897) //Verifica se a tecla 1 foi acionada
    {
      for (i = 0; i < 5; i++) {
        digitalWrite(ledVermelho, HIGH); //Acende o led vermelho
        Alarme.beep(500);     //beep de 500 ms
        digitalWrite(ledVermelho, LOW); //Acende o led vermelho
        delay(500);         //aguarda 500 mseg
      }
    }

    //danca lado esquerdo
    if (results.value == 0xFF02FD) { //Verifica se a tecla Ok foi acionada
      for (i = 0; i < 3; i++) {
        servo3.write(-45); //aqui o motor ficará em 90 graus
        servo4.write(-45); //aqui o motor ficará em 90 graus
        delay(1500);
        servo3.write(90); //aqui o motor ficará em 90 graus
        servo4.write(90); //aqui o motor ficará em 90 graus
        delay(1500);
      }
    }

    //danca lado direito
    if (results.value == 0xFF9867) { //Verifica se a tecla 2 foi acionada
      for (i = 0; i < 3; i++) {
        servo3.write(160); //aqui o motor ficará em 45 graus
        servo4.write(145); //aqui o motor ficará em 45 graus
        delay(1500);
        servo3.write(85); //aqui o motor ficará em 90 graus
        servo4.write(65); //aqui o motor ficará em 90 graus
        delay(1500);
      }
    }

    //usar o sensor de distancia para andar ainda faze o teste
    if (results.value == 0xFF629D) { //Verifica se a tecla para cima ^ foi acionada
      for (i = 0; i < 3; i++) {
        //perna direita
        servo1.write(130); //aqui o motor ficará em 45 graus, vira
        delay(500);
        servo3.write(30); //aqui o motor ficará em 45 graus, levanta
        delay(500);
        servo1.write(69); //aqui o motor ficará em 90 graus, desvira
        delay(500);
        servo3.write(85); //aqui o motor ficará em 90 graus, abaixar
        delay(500);

        //perna esquerda
        servo2.write(10); //aqui o motor ficará em 45 graus, vira
        delay(500);
        servo4.write(120); //aqui o motor ficará em 45 graus, levanta
        delay(500);
        servo2.write(62); //aqui o motor ficará em 90 graus, desvira
        delay(500);
        servo4.write(65); //aqui o motor ficará em 90 graus, abaixa

        delay(1000);
      }
    }




    irrecv.resume();  //Le o valor da próxima tecla pressionada
  }
}


