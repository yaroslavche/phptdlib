#include "tdlib_json_client.hpp"
#include <td/telegram/Log.h>

void TDLibJsonClient::__construct()
{
    Php::Value self(this);
    // Php::out << this << std::flush;
    // self["client"] = "test";
}

Php::Value TDLibJsonClient::create()
{
    td::Log::set_verbosity_level(1);
    _client = td_json_client_create();
    return _client;
}

void TDLibJsonClient::destroy()
{
    if(_client == NULL) Php::error << "TDLibJsonClient not created. Create client before using" << std::flush;
    td_json_client_destroy(_client);
    return;
}

Php::Value TDLibJsonClient::execute(Php::Parameters &params)
{
    if(_client == NULL) Php::error << "TDLibJsonClient not created. Create client before using" << std::flush;
    td_json_client_execute(_client, params[0]);
    return true;
}

Php::Value TDLibJsonClient::send(Php::Parameters &params)
{
    if(_client == NULL) Php::error << "TDLibJsonClient not created. Create client before using" << std::flush;
    const char *query = params[0];
    double timeout = params[1];
    Php::out << "send query " << query << " with timeout " << timeout << std::endl << std::flush;
    td_json_client_send(_client, query);
    std::string result = "";
    while(true)
    {
        result = td_json_client_receive(_client, timeout);
        if(!result.empty()) break;
    }
    return result;
}

Php::Value TDLibJsonClient::receive(Php::Parameters &params)
{
    if(_client == NULL) Php::error << "TDLibJsonClient not created. Create client before using" << std::flush;
    std::string receive = td_json_client_receive(_client, params[0]);
    return receive;
}
