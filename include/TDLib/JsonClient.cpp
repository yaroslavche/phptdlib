#include <iostream>

#include <phpcpp.h>

#include <td/telegram/tdjson_export.h>
#include <td/telegram/td_json_client.h>
#include <td/telegram/Log.h>

#include "JsonClient.hpp"

JsonClient::JsonClient(void *&client_ptr)
{
    _client = client_ptr;
}

void JsonClient::__construct(Php::Parameters &params)
{
    td::Log::set_verbosity_level(0);
    // Php::Value object = params[0];
    // if(object.instanceOf("TDLib\\JsonClient"))
    // {
    //     JsonClient *client = (JsonClient *)object.implementation();
    //     this->_client = client->getClientPointer();
    //     Php::out << _client << std::endl << std::flush;
    // }
}

void JsonClient::create()
{
    if(_client == nullptr) _client = td_json_client_create();
}

void JsonClient::destroy()
{
    if(_client == nullptr) Php::Exception("JsonClient not created. Use create() method before destroy");
    td_json_client_destroy(_client); // segfault
}

Php::Value JsonClient::execute(Php::Parameters &params)
{
    if(_client == nullptr) Php::Exception("JsonClient not created. Use create() method before execute");
    const char *query = params[0];
    std::string result = td_json_client_execute(_client, query);
    return result;
}

void JsonClient::send(Php::Parameters &params)
{
    if(_client == nullptr) Php::Exception("JsonClient not created. Use create() method before send");
    const char *query = params[0];
    td_json_client_send(_client, query);
}

Php::Value JsonClient::receive(Php::Parameters &params)
{
    if(_client == nullptr) Php::Exception("JsonClient not created. Use create() method before receive");
    std::string receive = td_json_client_receive(_client, params[0]);
    return receive;
}

Php::Value JsonClient::sendAndWait(Php::Parameters &params)
{
    if(_client == nullptr) Php::Exception("JsonClient not created. Use create() method before sendAndWait");
    const char *query = params[0];
    double timeout = params[1];
    std::string result = "";
    // Php::out << "send query " << query << " with timeout " << timeout << std::endl << std::flush;
    td_json_client_send(_client, query);
    while(true)
    {
        result = td_json_client_receive(_client, timeout);
        if(!result.empty()) return result;
    }
    return result;
}


/**
 * Magic methods
 */

Php::Value JsonClient::__toString()
{
    std::string str = "Object TDLib\\JsonClient";
    return str;
}


Php::Value JsonClient::__get(const Php::Value &name)
{
    Php::out << "__get " << name << std::endl << std::flush;
    return "__get";
}

void JsonClient::__set(const Php::Value &name, const Php::Value &value)
{

}

bool JsonClient::__isset(const Php::Value &name)
{
    return true;
}

void JsonClient::__unset(const Php::Value &name)
{
    Php::error << "__unset " << name << std::endl << std::flush;
}

Php::Value JsonClient::__call(const char *name, Php::Parameters &params)
{
    return "__call";
}

Php::Value JsonClient::__callStatic(const char *name, Php::Parameters &params)
{
    return "__callStatic";
}

Php::Value JsonClient::__invoke(Php::Parameters &params)
{
    return "__invoke";
}
