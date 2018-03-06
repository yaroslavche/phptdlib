#ifndef TDLIB_BASEJSONCLIENT_H
#define TDLIB_BASEJSONCLIENT_H

class BaseJsonClient : public Php::Base
{
    protected:
        void *_client = NULL;

    public:
        BaseJsonClient();
        BaseJsonClient(bool createClient);
        BaseJsonClient(void *&client_ptr);
        virtual ~BaseJsonClient();

        void __construct(Php::Parameters &params);
        const char *__toString();
        Php::Value __get(const Php::Value &name);
        void __set(const Php::Value &name, const Php::Value &value);
        bool __isset(const Php::Value &name);
        void __unset(const Php::Value &name);
        Php::Value __call(const char *name, Php::Parameters &params);
        static Php::Value __callStatic(const char *name, Php::Parameters &params);
        Php::Value __invoke(Php::Parameters &params);

        void create();
        void destroy();
        Php::Value execute(Php::Parameters &params);
        std::string execute(const char *query);
        void send(Php::Parameters &params);
        void send(const char *query);
        Php::Value receive(Php::Parameters &params);
        std::string receive(double timeout);

        inline void *getClientPointer() { return _client; }
};

#endif // TDLIB_BASEJSONCLIENT_H
