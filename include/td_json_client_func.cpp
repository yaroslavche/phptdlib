#include "TDLib/BaseJsonClient.hpp"

Php::Value td_json_client_func_create()
{
    void *client_ptr = td_json_client_create();
    BaseJsonClient *client = new BaseJsonClient(client_ptr);
    return Php::Object("TDLib\\BaseJsonClient", client);
}

void td_json_client_func_destroy(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\BaseJsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\BaseJsonClient.");
    BaseJsonClient *client = (BaseJsonClient *)object.implementation();
    td_json_client_destroy(client->getClientPointer()); // segfault
    delete client;
}

Php::Value td_json_client_func_execute(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\BaseJsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\BaseJsonClient.");
    const char *query = params[1];
    BaseJsonClient *client = (BaseJsonClient *)object.implementation();
    std::string result = td_json_client_execute(client->getClientPointer(), query);
    return result;
}

void td_json_client_func_send(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\BaseJsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\BaseJsonClient.");
    const char *query = params[1];
    BaseJsonClient *client = (BaseJsonClient *)object.implementation();
    td_json_client_send(client->getClientPointer(), query);
}

Php::Value td_json_client_func_receive(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\BaseJsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\BaseJsonClient.");
    double timeout = params[1];
    BaseJsonClient *client = (BaseJsonClient *)object.implementation();
    std::string result = td_json_client_receive(client->getClientPointer(), timeout);
    return result;
}
