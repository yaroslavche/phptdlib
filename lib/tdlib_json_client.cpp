#include "tdlib_json_client.hpp"

void TDLibJsonClient::__construct()
{
    // td::Log::set_verbosity_level(0);
}

Php::Value TDLibJsonClient::create()
{
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
    const char *query = params[0];
    td_json_client_execute(_client, query);
    return true;
}

Php::Value TDLibJsonClient::send(Php::Parameters &params)
{
    if(_client == NULL) Php::error << "TDLibJsonClient not created. Create client before using" << std::flush;
    const char *query = params[0];
    td_json_client_send(_client, query);
    return true;
}

Php::Value TDLibJsonClient::receive(Php::Parameters &params)
{
    if(_client == NULL) Php::error << "TDLibJsonClient not created. Create client before using" << std::flush;
    std::string receive = td_json_client_receive(_client, params[0]);
    return receive;
}

Php::Value TDLibJsonClient::sendAndWait(Php::Parameters &params)
{
    const char *query = params[0];
    double timeout = params[1];
    std::string result = "";
    Php::out << "send query " << query << " with timeout " << timeout << std::endl << std::flush;
    td_json_client_send(_client, query);
    while(true)
    {
        result = td_json_client_receive(_client, timeout);
        if(!result.empty()) return result;
    }
    return result;
}
