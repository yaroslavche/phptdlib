#include "tdlib_json_client.hpp"

void TDLibJsonClient::__construct()
{
    Php::Value self(this);
    // Php::out << this << std::flush;
    // self["client"] = "test";
}

Php::Value TDLibJsonClient::create()
{
    _client = td_json_client_create();
    return _client;
}

void TDLibJsonClient::destroy()
{
    td_json_client_destroy(_client);
    return;
}

Php::Value TDLibJsonClient::execute(Php::Parameters &params)
{
    td_json_client_execute(_client, params[0]);
    return true;
}

void TDLibJsonClient::send(Php::Parameters &params)
{
    td_json_client_send(_client, params[0]);
    return;
}

Php::Value TDLibJsonClient::receive(Php::Parameters &params)
{
    std::string receive = td_json_client_receive(_client, params[0]);
    return receive;
}
