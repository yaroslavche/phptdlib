#include <phpcpp.h>

extern "C" {

    PHPCPP_EXPORT void *get_module()
    {
        static Php::Extension tdlib("tdlib", "0.0.1");
        return tdlib;
    }
}
