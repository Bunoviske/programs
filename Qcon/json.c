

String check_json(String aux) {


  String jsonstring;
  //Funcao que verifica se tem conteudo json na resposta do servidor
  int initial_pos, final_pos;
  initial_pos = aux.indexOf('{');
  final_pos = aux.lastIndexOf('}');

  if ((initial_pos != -1) && (final_pos != -1)) {
    //resposta do servidor no formato json
    jsonstring = aux.substring(initial_pos, final_pos + 1);
  }
  else {
    initial_pos = aux.indexOf('[');
    final_pos = aux.lastIndexOf(']');
    if ((initial_pos != -1) && (final_pos != -1)) {
      //resposta do servidor no formato json
      jsonstring = aux.substring(initial_pos, final_pos + 1);
    }
    else {
      jsonstring = "";
    }
  }
  return jsonstring;
}

String parseJson(String parametro, char tipo, String jsonstring)
{
  int i = 0, j = 0, flag = 0, gap;
  String valor = "";
  int fim = jsonstring.length() - 1;
  char comp, comp1;

  if (tipo == 'n') {
    comp = ',';
    comp1 = ' ';
    gap = 1;
  }
  else if (tipo == 's') {
    comp = '\"';
    gap = 2;
  }

  while (i != fim) {
    if (jsonstring[i] == parametro[j]) {
      j++;
      if (j == parametro.length()) {
        flag = 1;
        break;
      }
    }
    else {
      j = 0;
    }
    i++;
  }
  //se flag = 1, achou-se o parametro que se deseja obter a variavel
  if (flag == 1) {
    if (tipo == 's') {
      i += gap;
      while (jsonstring[i] != comp) {
        valor += jsonstring[i];
        i++;
      }
    }
    else {
      i += gap;
      while ((jsonstring[i] != comp) && (jsonstring[i] != comp1)) {
        valor += jsonstring[i];
        i++;
      }
    }
    return valor;
  }
}

String update_parsing(String jsonstring, int flag) {
  String resposta;
  int code;


    if (jsonstring != "") {

      //mandar como parametro o tipo da variavel a ser analisada. s = string e n = numero.
      resposta = parseJson("\"code\": ", 'n', jsonstring);
      code = resposta.toInt();
      if (code == 200) {
        return "ok";
      }
      else if (code == 500) {
        return "500";
      }
      else {
        return "403");
      }
    }

}

String service_parsing(String jsonstring) {
  String resposta;
  int code;

  //fase de cadastro de servico. Cada fase tem determinada resposta do servidor para ser parseada

  if (jsonstring != "") {

    //mandar como parametro o tipo da variavel a ser analisada. s = string e n = numero.
    resposta = parseJson("\"code\": ", 'n', jsonstring);
    code = resposta.toInt();
    if (code == 200) {
      resposta = parseJson("\"action_id\": ", 's', jsonstring);
      return resposta;
    }
    else if (code == 500) {
      return "500";
    }
    return "403";
  }
}


String authentication_parsing(String jsonstring) {
  String resposta;
  int code;

  //fase de autenticacao. Cada fase tem determinada resposta do servidor para ser parseada

  if (jsonstring != "") {

    //mandar como parametro o tipo da variavel a ser analisada. s = string e n = numero.
    resposta = parseJson("\"code\": ", 'n', jsonstring);
    code = resposta.toInt();
    if (code == 200) {
      resposta = parseJson("\"token\": ", 's', jsonstring);
      return resposta;
    }
    return F("403");
  }
}
