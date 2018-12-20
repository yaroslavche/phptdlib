#ifndef TD_JSON_CLIENT_FUNC_H
#define TD_JSON_CLIENT_FUNC_H

#include <phpcpp.h>

Php::Value td_json_client_func_create();

void td_json_client_func_destroy(Php::Parameters &params);

Php::Value td_json_client_func_execute(Php::Parameters &params);

void td_json_client_func_send(Php::Parameters &params);

Php::Value td_json_client_func_receive(Php::Parameters &params);

#endif