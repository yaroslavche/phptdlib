#ifndef TDLIB_TD_JSON_CLIENT_FUNC_H
#define TDLIB_TD_JSON_CLIENT_FUNC_H

Php::Value td_json_client_func_create();
void td_json_client_func_destroy(Php::Parameters &params);
Php::Value td_json_client_func_execute(Php::Parameters &params);
void td_json_client_func_send(Php::Parameters &params);
Php::Value td_json_client_func_receive(Php::Parameters &params);

#endif // TDLIB_TD_JSON_CLIENT_FUNC_H