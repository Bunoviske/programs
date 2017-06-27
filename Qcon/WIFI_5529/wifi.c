/*
 * wifi.c
 *
 *  Created on: 6 de abr de 2017
 *      Author: Felipe Machado
 */

#include "msp430f5529.h"
#include "uart.h"
#include "wifi.h"
#include "parser.h"


volatile unsigned int ii = 0;
volatile unsigned int kk = 0;

char uartStopChar = 0x0A; // (almost) every wifi AT command ends with this symbol

char st_at_cmd[13]={0xA5,0x01,0xF2,0x00,0x00,0x0C,0x00,0x0C,0x00,0x61,0x2F,0x52,0xEF}; // wifi start message

unsigned char segundos;

int CONN = 0;
int HTTP = 0;

volatile char rcvMsg = 0; // rcvMsg changes to 1 when uartStopChar is received in the rcv interrupt


#pragma PERSISTENT(RXData)
char RXData[500] = ""; // assuming the received message won't be longer than 500. if changes are made here, they shall be made in wifi.h and in clear_uart too


char flag_sem_resposta = 0;
char min_sem_resposta;

//////////////////////////////////////////////////////////////////////////////////////

void analize_server_answer()
{
    char a;
    if (!strncmp(RXData,"+ERROR+",7) || (flag_sem_resposta == 1))
        {
       //// build_past(1);
        //past_flag = 1;
        }
    else if(!strncmp(RXData,"+OK+HTTPREQ",11))
    {
       // if(past_flag == 1)
       // {
          //  past_flag = 0;
           // build_past(2);
       // }
        a = RXData[273];
        char b=0;
        switch(a)
        {
        case '2':
           // server_rtc_date_and_table_refresh();
           // alarm_config();
            break;
        case '3':
           // rele_refresh();
            break;
        }

    }
}


//////////////////////////////////////////////////////////////////////////////////////

void connect_dhcp()
{
    clear_uart();
    sendAndWait("AT+MODE\r\n");
//  while (strncmp(RXData,"+OK+MODE",8));
// obs, essa linha comentada talvez retorne. Nesse caso e no caso a seguir, foram comentadas devido a alteracao na sendAndWait
    if((strncmp(RXData, "+",1)) && (flag_sem_resposta == 0))
    {
       // select_and_begin();
    }
    else if(!(strncmp(RXData, "+OK+MODE=IDLE",13)))
    {
        CONN = 0;
        clear_uart();
        sendAndWait("AT+CONN=keizen,2,otux7443\r\n");
        __delay_cycles(20000);
//          while (strncmp(RXData, "+ERROR+CONN", 11) && strncmp(RXData, "+OK+CONN", 8) && strncmp(RXData, "+EVT+DISCONN",12));
// obs, essa linha comentada talvez retorne (alterada)
        if(!(strncmp(RXData, "+OK+CONN", 8)))
        {
            clear_uart();
            while (strncmp(RXData, "+EVT+DHCP",9));
            __delay_cycles(200000);
            CONN=1;
            get_my_ip();
        }

    }
}


//////////////////////////////////////////////////////////////////////////////////////

void get_my_ip()
{
    char json_i = 54;
    char RXData_i;

    for(RXData_i=10;RXData_i<=21;RXData_i++)
    {
      //  json_msg3[json_i] = RXData[RXData_i];
        json_i++;
    }
}


//////////////////////////////////////////////////////////////////////////////////////

void connect_http()
{

    clear_uart();
//  sendAndWait("AT+CLOSEALL\r\n");
    sendAndWait("AT+HTTPOPEN=http://raise.uiot.com.br\r\n");
    sendAndWait("AT+HTTPCFG=Content-Type,application/json\r\n");// configura��o de cabe�alhos
    sendAndWait("AT+HTTPCFG=Content-Length,162\r\n");   //
}

//////////////////////////////////////////////////////////////////////////////////////



char wifi_start_AT()
{
    uart_send_array(st_at_cmd,sizeof st_at_cmd);

    while(!rcvMsg);
    return (!strncmp(RXData, "+OK+AT",6));
}
//////////////////////////////////////////////////////////////////////////////////////

char wifi_init()
{
    wifi_reset();
    char start = wifi_start_AT();
    return start;
}

//////////////////////////////////////////////////////////////////////////////////////


void sendAndWait(char *msg)
{
//  clear_uart();
//  uart_send_array(msg,strlen(msg));
//  while (!rcvMsg);

    clear_uart();


    if((flag_sem_resposta)&& ((RTCMIN - min_sem_resposta >=1) ||(RTCMIN == 1)&&(min_sem_resposta == 59)))
    {
        flag_sem_resposta = 0;
    }

    if(flag_sem_resposta == 0)
    {
        uart_send_array(msg,strlen(msg));

    /* a variavel segundos e zerada sempre que um envio � solicitado (seja por tempo ou por alarme)
     * portano, o que chegara aqui inicialmente sera sempre segundos=0 (nao e necessario criar uma variavel auxiliar para
     * essa contagem
     *
     * A escolha de 30 segundos foi empirica. Constatou-se que para o atmel leva 30s para enviar a resposta +ERROR+HTTPOPEN:-111
     * (Command processing time-out).
     *
     * Quando um tempo menor que 30s (ex 10s ou 5s) foi usado, aparentemente houve um erro no processamento
     * dos comandos seguintes pelo atmel, o que talvez prejudicasse o funcionamento do sistema. N�o foi testada a situa��o com o servidor
     * ligado e respondendo, portanto existe a chance de funcionar mesmo com esses tempos menores.
     *
     * Com o tempo de 30s, n�o houveram casos de erro -102 (The command is not registered) na situa��o de servidor desconectado.
     *
     *
    */
        while(segundos<=2)
        {
            if(rcvMsg)
            {
                return;
            }
            else
            {
                flag_sem_resposta = 1;
                min_sem_resposta = RTCMIN;
            }
        }
    }

}





//////////////////////////////////////////////////////////////////////////////////////

void wifi_reset(void)
{
    P3DIR |= BIT7 + BIT6; // P3.7 = RST_WIFI   P3.6 = EN_WIFI
    P3OUT &= ~(BIT7+BIT6);
    __delay_cycles(9999);
    P3OUT |= BIT6; //enable
    __delay_cycles(9999);
    P3OUT |= BIT7; //rst
    __delay_cycles(9999);
}

//////////////////////////////////////////////////////////////////////////////////////


void uart_wifi_init(void) //UART0
{
    P3SEL |= BIT3+BIT4;                       // P3.3,4 = USCI_A0 TXD/RXD
              UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
              UCA0CTL1 |= UCSSEL_2;                     // SMCLK
              UCA0BR0 = 9;                              // 1MHz 115200 (see User's Guide)
              UCA0BR1 = 0;                              // 1MHz 115200
              UCA0MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
              UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
              UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

    __enable_interrupt();

}

//////////////////////////////////////////////////////////////////////////////////////


void uart_send_array(char *TxArray, unsigned char ArrayLength)
{
    while(ArrayLength--){ // Loop until StringLength == 0 and post decrement
        while(!(UCA0IFG & UCTXIFG)); // Wait for TX buffer to be ready for new data
            UCA0TXBUF = *TxArray; //Write the character at the location specified py the pointer
            TxArray++; //Increment the TxString pointer to point to the next character
    }
}

//////////////////////////////////////////////////////////////////////////////////////

void clear_uart()
{
    rcvMsg = 0;
    ii = 0;
    memset(RXData, '\0', 500);
}

//////////////////////////////////////////////////////////////////////////////////////


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A0_VECTOR             // USCI ISR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch (UCA0IV) {
        case 2: {
            UCA0IFG &= ~ UCRXIFG;
            RXData[ii] = UCA0RXBUF;
            if((RXData[ii] != uartStopChar)&& (ii <500))
                ii++;
            else {
                rcvMsg = 1;
                flag_sem_resposta = 0;
            }
        }
        }
}
