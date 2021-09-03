/*
 * File:   aula7_Rx.c
 * Author: DNS
 *
 * Created on 27 de Agosto de 2021, 20:51
 */
//configurar o oscilador interno
#pragma config FOSC = INTIO67
#include <xc.h>
#pragma config WDTEN = OFF, LVP = OFF
#include "pic18f45k20.h"
#define _XTAL_FREQ 1000000

// esta função serve apenas para organizar o código
// ela configura os registradores da comunicação
// serial. Para este caso, 1200 bps, 8 bits, sem
// bit de paridade e 1 stop bit
void configura_serial()
{
      // configura o transmissor
      TXSTA = 0b00100000;
      // configura o receptor
      RCSTA = 0b10010000;

      // velocidade = Fosc/(64*(SPBRG+1))
      SPBRG = 12; // 1200 bps
}

 

void main (void)
{
      // variável que armazenará o valor recebido da serial
      unsigned char valor_recebido;

      // chama a função para configurar a serial
      configura_serial();

      // configura a porta B como saída
      TRISD = 0;

      // repete para sempre
      while(1){

            // prepara para receber
           RCSTA = 0b10010000;
            // espera chegar algum dado na serial
           while ((PIR1&32)==0);

                  // ler o valor recebido
                  valor_recebido = RCREG;

                  // reseta a serial para uma nova recepção
                  RCSTA = 0b10000000;

                  // compara para ver se é o valor correto
                  // e então acende o LED
                  if (valor_recebido == 85)
                        PORTD = 0xff;

                  // espera alguns instantes
                  __delay_ms(500);

                  // apaga o LED
                  PORTD=0;
      }
}
