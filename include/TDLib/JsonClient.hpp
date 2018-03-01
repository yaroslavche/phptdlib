#ifndef TDLIB_JSONCLIENT_H
#define TDLIB_JSONCLIENT_H

class JsonClient : public Php::Base
{
    private:
        void *_client = NULL;

    public:
        JsonClient() = default;
        JsonClient(void *&client_ptr);
        virtual ~JsonClient() = default;

        void __construct(Php::Parameters &params);
        Php::Value __toString();
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
        void send(Php::Parameters &params);
        Php::Value receive(Php::Parameters &params);
        Php::Value sendAndWait(Php::Parameters &params);

        // cpp space (not registered in extension)
        inline void *getClientPointer() { return _client; }
};

#endif // TDLIB_JSONCLIENT_H
