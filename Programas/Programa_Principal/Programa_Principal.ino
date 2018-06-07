//----------------------------------------------------------------
//-- Robo Otto
//-- Adaptado por Luciana Rocha Cardoso e Reinaldo Carlos Matias
//-- 22/05/2018
//-----------------------------------------------------------------
//-- Versão Colaborativa
//-----------------------------------------------------------------
//
//  Siglas de Referencias
//  SE = Superior Esquerdo
//  IE = Inferior Esquerdo
//  SD = Superior Direito
//  ID = Inferior Esquerdo
//
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//-- DECLARAÇÃO DE BIBLITOECAS
//-----------------------------------------------------------------
#include <IRremote.h>
#include <Buzzer.h>
#include <Servo.h>
//-----------------------------------------------------------------


//-----------------------------------------------------------------
//-- Pinagem dos Servos
//-----------------------------------------------------------------
/*
           ---------------
          |     O   O     |
          |---------------|
  SD 1==> |               | <== SE 2
           ---------------
              ||     ||
  ID 3==>   -----   ------  <== IE 4
           |-----   ------|

  SERVO   PINO
  servo1  [3]
  servo2  [2]
  servo3  [5]
  servo4  [4]
*/


//-----------------------------------------------------------------
//-- DECLARAÇÃO DE PINAGENS
//-----------------------------------------------------------------
int pinoRecepitorIR = 11; //Receptor do Controle
int ledVermelho = 12;     //Led do Nariz
int pin_buzzer = 10;      //Buzzer
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//-- DECLARAÇÃO DE VARIAVEIS
//-----------------------------------------------------------------
int i;                    //ITERATOR
const int posIniSD = 67;
const int posIniSE = 62;
const int posIniID = 80;
const int posIniIE = 65;
//-----------------------------------------------------------------


//-----------------------------------------------------------------
//-- DECLARAÇÃO DE RECURSOS
//-----------------------------------------------------------------
Servo servo1, servo2, servo3, servo4;
Buzzer Alarme(pin_buzzer);
IRrecv irrecv(pinoRecepitorIR);
decode_results results;
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//-- Inicialização
//-----------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  servo1.attach(3); // anexa o servomotor (físico), no pino 3, ao objeto servo1 (lógico), SD
  servo2.attach(2); // anexa o servomotor (físico), no pino 2, ao objeto servo2 (lógico), SE
  servo3.attach(5); // anexa o servomotor (físico), no pino 5, ao objeto servo3 (lógico), ID
  servo4.attach(4); // anexa o servomotor (físico), no pino 4, ao objeto servo4 (lógico), IE
  pinMode(ledVermelho, OUTPUT); // Definindo os pinos dos leds como saida
  irrecv.enableIRIn(); // Inicializa o receptor IR do controle remoto
}

void loop()
{
  servosPosicaoInicial();
  delay(500);
  
  if (irrecv.decode(&results))     // Executa caso seja precionado algum botão no contole
  {

    Serial.println(results.value, HEX);

    if (results.value == 0xFF629D) //Verifica se a tecla /\ foi acionada
    {

    }
    
    if (results.value == 0xFF22DD) //Verifica se a tecla < foi acionada
    {

    }
    
    if (results.value == 0xFFC23D) //Verifica se a tecla > foi acionada
    {

    }

    if (results.value == 0xFF02FD) //Verifica se a tecla \/ foi acionada
    {

    }
    
    if (results.value == 0xFF6897) //Verifica se a tecla 1 foi acionada
    {
      //Chama o programa piscaNariz
      piscaNariz(3, 500, 250);
    }

    if (results.value == 0xFF9867) //Verifica se a tecla 2 foi acionada
    {

    }

    if (results.value == 0xFFB04F) //Verifica se a tecla 3 foi acionada
    {

    }

    if (results.value == 0xFF30CF) //Verifica se a tecla 4 foi acionada
    {

    }

    if (results.value == 0xFF18E7) //Verifica se a tecla 5 foi acionada
    {

    }

    if (results.value == 0xFF7A85) //Verifica se a tecla 6 foi acionada
    {

    }

    if (results.value == 0xFF10EF) //Verifica se a tecla 7 foi acionada
    {

    }

    if (results.value == 0xFF38C7) //Verifica se a tecla 8 foi acionada
    {

    }

    if (results.value == 0xFF5AA5) //Verifica se a tecla 9 foi acionada
    {

    }

    if (results.value == 0xFF4AB5) //Verifica se a tecla 0 foi acionada
    {

    }

    if (results.value == 0xFF42BD) //Verifica se a tecla * foi acionada
    {

    }

    if (results.value == 0xFF52AD) //Verifica se a tecla # foi acionada
    {

    }

  irrecv.resume();  //Le o valor da tecla pressionada

  }
}


//-----------------------------------------------------------------
//-- Posiciona os Motores na posição inicial
//-----------------------------------------------------------------
void servosPosicaoInicial() {
  servo1.write(posIniSD); //aqui o motor ficará a 0 graus, SD
  servo2.write(posIniSE); //aqui o motor ficará a 0 graus, SE
  servo3.write(posIniID); //aqui o motor ficará a 0 graus, ID
  servo4.write(posIniIE); //aqui o motor ficará a 0 graus, IE
}


//-----------------------------------------------------------------
//-- Acende e apaga o led do Nariz, conforme parametros onde:
//-- vezes    = Número de vezes que o nariz irá pisca
//-- tempoluz = Tempo em Milissegundos que o led ficara aceso e o bip tocará
//-- tempopausa = Tempo em Milissegundos que o led permanecerá apagado
//-----------------------------------------------------------------
void piscaNariz(int vezes, int tempoluz, int tempopausa) {
  for (i = 0; i < vezes; i++) {       //Repete o número de vezes definido
    digitalWrite(ledVermelho, HIGH);  //Acende o LED
    Alarme.beep(tempoluz);            //Aciona o beep
    digitalWrite(ledVermelho, LOW);   //Apaga o LED
    delay(tempopausa);                //Aguarda para repetir
  }
}

