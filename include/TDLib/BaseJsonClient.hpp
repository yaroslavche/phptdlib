#ifndef TDLIB_BASEJSONCLIENT_H
#define TDLIB_BASEJSONCLIENT_H

#include <phpcpp.h>

class BaseJsonClient : public Php::Base {
protected:
    void *_client = NULL;

public:
    BaseJsonClient() = default;

    BaseJsonClient(void *&client_ptr);

    virtual ~BaseJsonClient() = default;

    std::string execute(const char *query);

    void send(const char *query);

    std::string receive(double timeout);

    // export
    void __construct(Php::Parameters &params);

    void __destruct();

    void create();

    void destroy();

    Php::Value execute(Php::Parameters &params);

    void send(Php::Parameters &params);

    Php::Value receive(Php::Parameters &params);
};

#endif // TDLIB_BASEJSONCLIENT_H
