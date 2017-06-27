
#include "msp430f5529.h"
#include "uart.h"
#include "wifi.h"


char json_msg1[] = {"{\"name\":\"teste_ATWINC1500\",\"chipset\":\"msp430f5529\",\"mac\":\"FF:FF:FF:FF:FF:FF\","};
char json_msg2[] = {"\"serial\":\"serial\",\"processor\":\"msp430f5529\",\"channel\":\"wifi\",\"timestamp\":1317427200}\r\n"};
char json_msg3[] = {"\"timestamp\":1317427200}\r\n"};


/*
 * main.c
 */
int main(void) {
        WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

      uart_init();
      uart_wifi_init();
      wifi_init();
      connect_dhcp();
      connect_http();

      uart_send_array("AT+HTTPREQ=POST,/client/register,",33);

      uart_send_array(json_msg1,sizeof(json_msg1));
      uart_send_array(json_msg2,sizeof(json_msg2));
     // uart_send_array(json_msg3,sizeof(json_msg3));
     // sendAndWait(json_msg3);
      analize_server_answer();

      __bis_SR_register(GIE);       // Enter LPM0, interrupts enabled


      for(;;){
          connect_dhcp();
              connect_http();

              uart_send_array("AT+HTTPREQ=POST,/client/register,",33);

              uart_send_array(json_msg1,strlen(json_msg1));
                    uart_send_array(json_msg2,strlen(json_msg2));
             // sendAndWait(json_msg3);
              analize_server_answer();
              __delay_cycles(80000000);
      }
	
	return 0;
}
