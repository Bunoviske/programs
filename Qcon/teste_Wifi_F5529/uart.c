/*
 * uart.c
 *
 *  Created on: 6 de abr de 2017
 *      Author: Felipe Machado
 */

#include "msp430f5529.h"
#include "uart.h"
#include "wifi.h"


void uart_init(void)
{
          P3SEL |= BIT3+BIT4;                       // P3.3,4 = USCI_A0 TXD/RXD
          UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
          UCA0CTL1 |= UCSSEL_2;                     // SMCLK
          UCA0BR0 = 9;                              // 1MHz 115200 (see User's Guide)
          UCA0BR1 = 0;                              // 1MHz 115200
          UCA0MCTL |= UCBRS_1 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
          UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
          UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}
