#ifndef TDLIB_BASEJSONCLIENT_H
#define TDLIB_BASEJSONCLIENT_H

#include <phpcpp.h>

class BaseJsonClient : public Php::Base {
protected:
    void *_client = nullptr;

public:
    BaseJsonClient() = default;

    explicit BaseJsonClient(void *&client_ptr);

    ~BaseJsonClient() override = default;

    std::string execute(const char *query);

    void send(const char *query);

    std::string receive(double timeout);

    // export
    virtual void __construct(Php::Parameters &params);

    virtual void __destruct();

    void create();

    void destroy();

    virtual Php::Value execute(Php::Parameters &params);

    virtual void send(Php::Parameters &params);

    virtual Php::Value receive(Php::Parameters &params);
};

#endif // TDLIB_BASEJSONCLIENT_H
