#!/usr/bin/env bash

PHPTDLIB_INVALID_LIBRARY_ALIAS=1
PHPTDLIB_BUILD_PHPCPP_FAILED=2
PHPTDLIB_BUILD_JSON_FAILED=3
PHPTDLIB_BUILD_TD_FAILED=4
PHPTDLIB_INSTALL_MAKEFILE_NOT_FOUND=5
PHPTDLIB_INSTALL_PHPCPP_FAILED=6
PHPTDLIB_INSTALL_JSON_FAILED=7
PHPTDLIB_INSTALL_TD_FAILED=8


get_repository_head_hash()
{
    LIBRARY_REPO_HTTPS_URI=$1

    if [ ! -z "${LIBRARY_REPO_HTTPS_URI}" ]; then
        echo $(git ls-remote ${LIBRARY_REPO_HTTPS_URI} | grep refs/heads/master | cut -f 1)
    fi
    return 0
}

get_current_branch()
{
    echo $(git branch | grep \* | cut -d ' ' -f2)
    return 0
}

build()
{
    LIBRARY_ALIAS=$1
    LIBRARY_CACHE_PATH=$2

    cd ${LIBRARY_CACHE_PATH}
    case ${LIBRARY_ALIAS} in
        "PHPCPP") build_phpcpp;;
        "JSON") build_json;;
        "TD") build_td;;
        *) return ${PHPTDLIB_INVALID_LIBRARY_ALIAS};;
    esac
    BUILD_STATUS_CODE=$?
    return ${BUILD_STATUS_CODE}
}

install()
{
    LIBRARY_ALIAS=$1
    LIBRARY_CACHE_PATH=$2

    cd ${LIBRARY_CACHE_PATH}
    case ${LIBRARY_ALIAS} in
        "PHPCPP") install_phpcpp;;
        "JSON") install_json;;
        "TD") install_td;;
        *) return ${PHPTDLIB_INVALID_LIBRARY_ALIAS};;
    esac
    INSTALL_STATUS_CODE=$?
    return ${INSTALL_STATUS_CODE}
}

build_phpcpp()
{
    make || return ${PHPTDLIB_BUILD_PHPCPP_FAILED}
    return 0
}

build_json()
{
    mkdir build
    cd build
    cmake .. || return ${PHPTDLIB_BUILD_JSON_FAILED}
    return 0
}

build_td()
{
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release .. || return ${PHPTDLIB_BUILD_TD_FAILED}
    cmake --build . || return ${PHPTDLIB_BUILD_TD_FAILED}
    return 0
}

install_phpcpp()
{
    sudo make install || return ${PHPTDLIB_INSTALL_PHPCPP_FAILED}
    return 0
}

install_json()
{
    cd build
    sudo make install || return ${PHPTDLIB_INSTALL_JSON_FAILED}
    return 0
}

install_td()
{
    cd build
    sudo make install || return ${PHPTDLIB_INSTALL_TD_FAILED}
    return 0
}

#get_error_message()
#{
#    CODE=$1
#
#    case ${CODE} in
#        "${PHPTDLIB_BUILD_PHPCPP_FAILED}") echo "PHP-CPP build failed";;
#        "${PHPTDLIB_BUILD_JSON_FAILED}") echo "json build failed";;
#        "${PHPTDLIB_BUILD_TD_FAILED}") echo "td build failed";;
#        "${PHPTDLIB_INSTALL_ERROR}") echo "Install failed";;
#        "${PHPTDLIB_INVALID_LIBRARY_ALIAS}") echo "Unknown library alias";;
#        *) echo "Unhandled error";;
#    esac
#    return 0
#}