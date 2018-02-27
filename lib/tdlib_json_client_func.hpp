#ifndef TDLIB_JSON_CLIENT_FUNC_H
#define TDLIB_JSON_CLIENT_FUNC_H

Php::Value libtd_td_json_client_create();
void libtd_td_json_client_destroy();
Php::Value libtd_td_json_client_execute(Php::Parameters &params);
Php::Value libtd_td_json_client_send(Php::Parameters &params);
Php::Value libtd_td_json_client_receive(Php::Parameters &params);
Php::Value libtd_td_json_client_send_and_wait(Php::Parameters &params);

#endif // TDLIB_JSON_CLIENT_FUNC_H
