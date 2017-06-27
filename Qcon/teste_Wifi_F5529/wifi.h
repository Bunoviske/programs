/*
 * wifi.h
 *
 *  Created on: 6 de abr de 2017
 *      Author: Felipe Machado
 */

#ifndef WIFI_H_
#define WIFI_H_



char wifi_init();
void uart_send_array(char *TxArray, unsigned char ArrayLength);
void uart_wifi_init(void);
void wifi_reset(void);
char wifi_start_AT();
void sendAndWait(char *msg);
void clear_uart();

void analize_server_answer();

/////////////////////////////////////////
void connect_dhcp();
void get_my_ip();
void connect_http();

extern char RXData[500];
extern char flag_sem_resposta;


#endif /* WIFI_H_ */
