#include <iostream>

#include <phpcpp.h>

#include <td/telegram/tdjson_export.h>
#include <td/telegram/td_json_client.h>
#include <td/telegram/Log.h>

#include "BaseJsonClient.hpp"
#include "../TDApi/TDLibParameters.hpp"

BaseJsonClient::BaseJsonClient()
{
    td::Log::set_verbosity_level(0);
    create();
}

BaseJsonClient::BaseJsonClient(bool createClient = true)
{
    td::Log::set_verbosity_level(0);
    if(createClient) create();
}

BaseJsonClient::BaseJsonClient(void *&client_ptr)
{
    _client = client_ptr;
}

BaseJsonClient::~BaseJsonClient()
{
    if(_client) destroy();
}

void BaseJsonClient::create()
{
    if(_client == nullptr) _client = td_json_client_create();
}

void BaseJsonClient::destroy()
{
    if(_client == nullptr) Php::Exception("BaseJsonClient not created. Use create() method before destroy");
    td_json_client_destroy(_client); // segfault if close before parameters set
}

Php::Value BaseJsonClient::execute(Php::Parameters &params)
{
    if(_client == nullptr) Php::Exception("BaseJsonClient not created. Use create() method before execute");
    const char *query = params[0];
    return execute(query);
}

std::string BaseJsonClient::execute(const char *query)
{
    std::string result = td_json_client_execute(_client, query);
    return result;
}

void BaseJsonClient::send(Php::Parameters &params)
{
    if(_client == nullptr) Php::Exception("BaseJsonClient not created. Use create() method before send");
    const char *query = params[0];
    send(query);
}

void BaseJsonClient::send(const char *query)
{
    td_json_client_send(_client, query);
}

Php::Value BaseJsonClient::receive(Php::Parameters &params)
{
    if(_client == nullptr) Php::Exception("BaseJsonClient not created. Use create() method before receive");
    double timeout = params[0];
    return receive(timeout);
}

std::string BaseJsonClient::receive(double timeout)
{
    return td_json_client_receive(_client, timeout);
}

/**
 * Magic methods
 */

void BaseJsonClient::__construct(Php::Parameters &params)
{
    Php::out << "__construct" << std::endl << std::flush;
}

const char *BaseJsonClient::__toString()
{
    const char *str = "Object TDLib\\BaseJsonClient";
    return str;
}

// Php::Value BaseJsonClient::__get(const Php::Value &name)
// {
//     Php::out << "__get " << name << std::endl << std::flush;
//     return "__get";
// }
//
// void BaseJsonClient::__set(const Php::Value &name, const Php::Value &value)
// {
//
// }
//
// bool BaseJsonClient::__isset(const Php::Value &name)
// {
//     return true;
// }
//
// void BaseJsonClient::__unset(const Php::Value &name)
// {
//     Php::error << "__unset " << name << std::endl << std::flush;
// }
//
// Php::Value BaseJsonClient::__call(const char *name, Php::Parameters &params)
// {
//     Php::out << name << std::flush;
//     return "__call";
// }
//
// Php::Value BaseJsonClient::__callStatic(const char *name, Php::Parameters &params)
// {
//     return "__callStatic";
// }
//
// Php::Value BaseJsonClient::__invoke(Php::Parameters &params)
// {
//     return "__invoke";
// }
