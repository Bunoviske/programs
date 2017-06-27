
#include "msp430f5529.h"
#include "uart.h"
#include "wifi.h"
#include "parser.h"


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

      code_check("+EVT+RECV=0,282,T,HTTP/1.1 200 OK\r\nDate: Sat, 08 Apr 2017 19:22:28 GMT\r\nServer: Apache/2.4.6 (CentOS) PHP/7.0.17\r\nX-Powered-By: PHP/7.0.17\r\nContent-Length: 98\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n{\r\n    \"code\": \"200\",\r\n    \"message\": \"Success\",\r\n    \"tokenId\": \"5a06a19ab1bf993e8fce1b536feaedb1\"\r\n}");
      for(;;){
          connect_dhcp();
              connect_http();

              uart_send_array("AT+HTTPREQ=POST,/client/register,",33);

              uart_send_array(json_msg1,strlen(json_msg1));
                    uart_send_array(json_msg2,strlen(json_msg2));
             // sendAndWait(json_msg3);
              analize_server_answer();
              __delay_cycles(8000000);
      }
	
	return 0;
}
