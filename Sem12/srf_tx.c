/*
 * File:   aula7.c
 * Author: DNS
 *
 * Created on 27 de Agosto de 2021, 11:01
 */
//configurar o oscilador interno
#pragma config FOSC = INTIO67

//include a biblioteca do computador do MPLAB
#include <xc.h>

//desliga as configuração watchdog time e programação em baixa tensão
#pragma config WDTEN = OFF, LVP = OFF

#include "pic18f45k20.h"
//"PBADEN = OFF" define que os bits 1, 2, 3 e 4 da porta B
//devem ser configurados como pinos I/O digitais.
#pragma config PBADEN = OFF

//define a frequência utilizada pelo microcontrolador
#define _XTAL_FREQ 1000000

//esta função serve apenas para organizar o código
//ela configura os registradores da comunicação
//serial. Para este caso, 1200 bps, 8 bits, sem
//bit de paridade e 1 stop bit

void configura_serial()
{
    //configura o transmissor
    TXSTA = 0b00100000;
    //configura o receptor
    RCSTA = 0b10010000;
    
    //velocidade = Fosc/(64*(SPBRG+1))
    SPBRG = 12;//1200 bps
}

void main(void) {
    //variável que verificará o estado da chave
    unsigned char chave;
    
    //configura a porta B como entrada
    TRISB = 0xff;
    
    //chama a função para configurar a serial
    configura_serial();
    
    //Configura o PORTD, como saída para sinalizar envio
    TRISD = 0x00;
    
    //repete para sempre
    while(1){
        //ler o estado da chave
        chave = PORTB;
        
        //se a chave estiver pressionada
        if(chave==0){
            //transmite o valor 85 (bits alternados)
            TXREG = 0b01010101;
            
            //acende o led indicador de transmissão
            PORTD = 0x01;
            
            //espera transmitir o byte
            while(!(PIR1&0b00010000));
            
            //aguarda meio segundo
            __delay_ms(500);
            
            //apaga o led indicador de transmissão
            PORTD = 0x00;
        }
    }
    return;
}
