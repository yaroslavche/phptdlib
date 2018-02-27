#ifndef TDLIB_JSON_CLIENT_H
#define TDLIB_JSON_CLIENT_H

class TDLibJsonClient : public Php::Base
{
    private:
        void *_client = NULL;

    public:
        TDLibJsonClient() = default;
        virtual ~TDLibJsonClient() = default;

        void __construct();

        Php::Value create();
        void destroy();
        Php::Value execute(Php::Parameters &params);
        Php::Value send(Php::Parameters &params);
        Php::Value receive(Php::Parameters &params);
        Php::Value sendAndWait(Php::Parameters &params);
};

#endif // TDLIB_JSON_CLIENT_H
