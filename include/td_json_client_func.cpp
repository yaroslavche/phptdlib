#include "TDLib/JsonClient.hpp"

Php::Value td_json_client_func_create()
{
    void *client_ptr = td_json_client_create();
    // Php::out << "create " << client_ptr << std::endl << std::flush;
    JsonClient *client = new JsonClient(client_ptr);
    return Php::Object("TDLib\\JsonClient", client);
}

void td_json_client_func_destroy(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\JsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\JsonClient.");
    JsonClient *client = (JsonClient *)object.implementation();
    // Php::out << "destroy " << client->getClientPointer() << std::endl << std::flush;
    td_json_client_destroy(client->getClientPointer()); // segfault
    delete client;
}

Php::Value td_json_client_func_execute(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\JsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\JsonClient.");
    const char *query = params[1];
    JsonClient *client = (JsonClient *)object.implementation();
    // Php::out << "execute " << client->getClientPointer() << std::endl << std::flush;
    std::string result = td_json_client_execute(client->getClientPointer(), query);
    return result;
}

void td_json_client_func_send(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\JsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\JsonClient.");
    const char *query = params[1];
    JsonClient *client = (JsonClient *)object.implementation();
    // Php::out << "send " << client->getClientPointer() << std::endl << std::flush;
    td_json_client_send(client->getClientPointer(), query);
}

Php::Value td_json_client_func_receive(Php::Parameters &params)
{
    Php::Value object = params[0];
    if(!object.instanceOf("TDLib\\JsonClient")) throw Php::Exception("First parameter must be instance of TDLib\\JsonClient.");
    double timeout = params[1];
    JsonClient *client = (JsonClient *)object.implementation();
    // Php::out << "receive " << client->getClientPointer() << std::endl << std::flush;
    std::string result = td_json_client_receive(client->getClientPointer(), timeout);
    return result;
}
