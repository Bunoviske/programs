

String autentURL() {

  String URL = F("/devices?name=");
  URL += host_name;
  URL += F("&description=");
  URL += description_autent;
  URL += F("&chipset_id=");
  URL += id_chipset;
  URL += F("&processor_id=");
  URL += id_processor;
  URL += F("&mac=");
  URL += mac_aux;
  URL += F("&serial=");
  URL += hd_serial;

  return URL;

}

String expiredTokenURL() {
  String URL = F("/devices?name=");
  URL += host_name;
  URL += F("&description=");
  URL += description_autent;
  URL += F("&chipset_id=");
  URL += id_chipset;
  URL += F("&processor_id=");
  URL += id_processor;
  URL += F("&mac=");
  URL += mac_aux;
  URL += F("&serial=");
  URL += hd_serial;
  URL += F("&token=");
  URL += id_token;

  return URL;
}


String serviceURL() {

  String URL = F("/services?token=");
  URL += id_token;
  URL += F("&name=");
  URL += nome_service_servico1;
  URL += F("&type=");
  URL += inf_type;
  URL += F("&scpdurl=");
  URL += scpdurl;
  URL += F("&description=");
  URL += description_service;
  URL += F("&control_url=");
  URL += control_url;
  URL += F("&event_sud_url=");
  URL += event_sud_url;
  URL += F("&refresh_rate=");
  URL += refresh_rate;


  return URL;
}



String updateURL(String return_value, int i) {
  String URL;

    URL = F("/arguments?token=");
    URL += id_token;
    URL += F("&action_id=");
    URL += action_id;
    URL += F("&name=");
    URL += nome_update_servico1;
    URL += F("&default_value=");
    URL += default_value_servico1;
    URL += F("&return_value=");
    URL += F("id_tag");



  return URL;

}
