#include <td/telegram/td_json_client.h>
#include "TDLib/BaseJsonClient.hpp"
#include "td_json_client_func.hpp"

Php::Value td_json_client_func_create()
{
    void *client_ptr = td_json_client_create();
    auto *client = new BaseJsonClient(client_ptr);
    return Php::Object("TDLib\\BaseJsonClient", client);
}

void td_json_client_func_destroy(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\BaseJsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\BaseJsonClient.");
    auto *client = (BaseJsonClient *)object.implementation();

    client->destroy();
}

Php::Value td_json_client_func_execute(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\BaseJsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\BaseJsonClient.");
    const char *query = params[1];
    auto *client = (BaseJsonClient *)object.implementation();

    std::string result = client->execute(query);
    return result;
}

void td_json_client_func_send(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\BaseJsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\BaseJsonClient.");
    const char *query = params[1];
    auto *client = (BaseJsonClient *)object.implementation();

    client->send(query);
}

Php::Value td_json_client_func_receive(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\BaseJsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\BaseJsonClient.");
    double timeout = params[1];
    auto *client = (BaseJsonClient *)object.implementation();

    std::string result = client->receive(timeout);
    return result;
}
