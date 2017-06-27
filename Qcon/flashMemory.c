
void write_token(){

    char aux[id_token.length()];
    id_token.toCharArray(aux,id_token.length()+1);
    int addr;
    for (addr = 0; addr < id_token.length(); addr++){
      EEPROM.write(addr, aux[addr]);
    }
    EEPROM.write(addr, (char)'>');
    pos_final_token = addr;
}



void write_action(){

  int inicio = pos_final_token + 1;
  for(int j = 0; j < NUM_SERVICOS; j++){

    int tam = action_id[j].length();
    int k = 0;
    char aux[tam];
    for (k=0;k< tam; k++){
      aux[k] = (char)action_id[j][k];
    }

    int addr;
    k = 0;

    for (addr = inicio; addr < tam + inicio; addr++){
      EEPROM.write(addr, aux[k]);
      k++;
    }

    if (j+1 == NUM_SERVICOS){
      EEPROM.write(addr, (char)'>');
    }
    else{
      EEPROM.write(addr, (char)'/');
    }

    inicio = addr + 1;
  }

}
