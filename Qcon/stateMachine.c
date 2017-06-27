//*****************************************************************************************************
//HEADER's

#include "flashMemory.h"
#include "json.h"
#include "Url.h"

typedef struct {

  char *server = "raise.uiot.org"; //mudar para string e otimizar string literal ??
  char *ip = "172, 16, 9, 123";

  char jsonString[1024];
  char token[64];
  char serviceId[20];
  bool tokenExpirado = 0;

  // int pos_final_token = 0;
  // unsigned long previous_time = 0;
  // unsigned long current_time = 0;

} RaiseParameters;

//ponteiro de função da máquina de estados. Ele aponta sempre para a função da máquina de estados que deve ser executada
void (*FSM_SBRT)(RaiseParameters*);
void (*FSM_SBRT_anterior)(RaiseParameters*);

//*****************************************************************************************************
//Prototipos

//FSM
void StateInit(void);       //função que representa o estado inicial da máquina de estados
void StateReadEprom(RaiseParameters*);
void StateAuthentication(RaiseParameters*);
void StateService(RaiseParameters*);
void StateUpdate(RaiseParameters*);

//Metodos privados
void initSerial(int);
void initGPIO();
void readSensor();

//*****************************************************************************************************
//Setup
int main () {

  //inicializacao das variaveis globais

  initSerial(115200);
  initGPIO();


  //INICIALIZA FSM
  StateInit();

  RaiseParameters data;


  //*****************************************************************************************************
  //LOOP
  while (1) {
    (*FSM_SBRT)(&data);
  }

}





//*****************************************************************************************************
//Implementação FSM
void StateInit()
{

  //INICIALIZA A MAQUINA DE ESTADOS

  //TROCA DE ESTADO
  FSM_SBRT = StateReadEprom;
}

void StateReadEprom(RaiseParameters *parametros)
{
  // TOKEN smp vai ser do mesmo tamanho
  char tokenAux[TAM_TOKEN_MAX + 1];
  int addr = 0;
  int i;
  while ((EEPROM.read(addr) != (char)'>') && (addr < TAM_TOKEN_MAX + 1)) {
    tokenAux[addr] = EEPROM.read(addr);
    addr++;
  }

  if (addr == TAM_TOKEN_MAX + 1) {
    FSM_SBRT = StateAuthentication;
    return;
  }
  else {
    id_token = "";
    for (i = 0; i < addr; i++) {
      id_token += (String)tokenAux[i];
    }
    Serial.println(id_token);

    pos_final_token = addr;

    // ACTION ID pode variar o tamanho, então será feita uma leitura dinâmica
    char actionIdAux[TAM_ACTION_ID_MAX + 1];
    addr = pos_final_token + 1;
    i = 0;
    while ((EEPROM.read(addr) != (char)'>') && (i < TAM_ACTION_ID_MAX + 1)) { //é somado um para considerar o caracter q define o fim do action-id
      actionIdAux[i] = EEPROM.read(addr);
      addr++;
      i++;
    }

    if (i == TAM_ACTION_ID_MAX + 1) {
      FSM_SBRT = StateService;
      return;
    }
    else {
      //se tiverem dois servicos, mudar essa parte para que ele reconheça o caracter que divide os dois action-id na memoria
      action_id = "";
      for (int k = 0; k < i; k++) {
        action_id += (String)actionIdAux[k];
      }
      Serial.println(action_id);

      // ITEM ID pode variar o tamanho, então será feita uma leitura dinâmica
      char itemIdAux[TAM_ITEM_ID_MAX + 1];
      addr++;
      i = 0;
      while ((EEPROM.read(addr) != (char)'>') && (i < TAM_ITEM_ID_MAX + 1)) {
        itemIdAux[i] = EEPROM.read(addr);
        addr++;
        i++;
      }

      if (i == TAM_ITEM_ID_MAX + 1 ) {
        FSM_SBRT = StateArguments;
        return;
      }
      else {
        item_id = "";
        for (int k = 0; k < i; k++) {
          item_id += (String)itemIdAux[k];
        }
        Serial.println(item_id);

        FSM_SBRT = StateUpdate;
      }
    }
  }
}


void StateAuthentication(RaiseParameters *parametros)
{
    //conectar no servidor

    if (parametros->tokenExpirado == 0) {
      //autent = autentURL();
    }
    else {
      //autent = expiredTokenURL();
    }


    write_token();



  if (parametros->tokenExpirado == 0) {
    FSM_SBRT = StateService;
  }
  else {
    FSM_SBRT = FSM_SBRT_anterior;
  }

}

void StateService(RaiseParameters *parametros)
{

write_action();

  FSM_SBRT = StateUpdate;
}


void StateUpdate(RaiseParameters *parametros)
{
  readSensor();


  FSM_SBRT = StateUpdate;


}




//*****************************************************************************************************
void readSensor()
{

}


//INICIALIZA A COMUNICAÇão SERIAL
void initSerial(unsigned int baudrate)
{

}

//INICIALIZA pinos GPIO
void initGPIO()
{

}
