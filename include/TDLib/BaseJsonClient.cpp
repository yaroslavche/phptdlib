#include "BaseJsonClient.hpp"
#include <cassert>
#include <td/telegram/td_json_client.h>


BaseJsonClient::BaseJsonClient(void *&client_ptr)
{
    _client = client_ptr;
}

void BaseJsonClient::create()
{
    if(_client == nullptr) _client = td_json_client_create();
}

void BaseJsonClient::destroy()
{
    assert(_client != nullptr);
    td_json_client_destroy(_client);
    _client = nullptr;
}

Php::Value BaseJsonClient::execute(Php::Parameters &params)
{
    assert(_client != nullptr);
    const char *query = params[0];
    return execute(query);
}

std::string BaseJsonClient::execute(const char *query)
{
    assert(_client != nullptr);
    std::string result = td_json_client_execute(_client, query);
    return result;
}

void BaseJsonClient::send(Php::Parameters &params)
{
    assert(_client != nullptr);
    const char *query = params[0];
    send(query);
}

void BaseJsonClient::send(const char *query)
{
    assert(_client != nullptr);
    td_json_client_send(_client, query);
}

Php::Value BaseJsonClient::receive(Php::Parameters &params)
{
    assert(_client != nullptr);
    double timeout = params[0];
    return receive(timeout);
}

std::string BaseJsonClient::receive(double timeout)
{
    assert(_client != nullptr);
    const char* result = td_json_client_receive(_client, timeout);
    if(result == nullptr) {
        return "";
    } else return result;
}

/**
 * Magic methods
 */

void BaseJsonClient::__construct(Php::Parameters &params)
{
    create();
}

void BaseJsonClient::__destruct()
{
    if(_client != nullptr) destroy();
}
