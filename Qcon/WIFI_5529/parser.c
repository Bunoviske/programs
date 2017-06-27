/*
 * parser.c
 *
 *  Created on: 8 de abr de 2017
 *      Author: victo
 */


char * code_check(const char * str){
    char token[32];
    unsigned int i = 32;
    char * failure = 0;
    while(*str != '\"')
        str++;
    if(!strncmp(str,"\"code\": \"200\"", 13)){
        str += 59;
        for(i = 31;i >= 0;i--){
            token[i] = str[i];
        }
    }
    else return failure;
    return token;
}

/*  "code": "200",
    "message": "Success",
    "tokenId": "9a06a19ab1bf993e8fce1b536feaedb1"
*/
