#!/usr/bin/env bash

PHPTDLIB_BUILD_INVALID_LIBRARY_ALIAS=1
PHPTDLIB_BUILD_PHPCPP_FAILED=2
PHPTDLIB_BUILD_JSON_FAILED=3
PHPTDLIB_BUILD_TD_FAILED=4
PHPTDLIB_INSTALL_ERROR=5

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
        *) return ${PHPTDLIB_BUILD_INVALID_LIBRARY_ALIAS};;
    esac
    BUILD_STATUS_CODE=$?
    return ${BUILD_STATUS_CODE}
}

install()
{
    LIBRARY_CACHE_PATH=$1

    cd ${LIBRARY_CACHE_PATH}
    sudo make install ${MAKEFLAGS} || return ${PHPTDLIB_INSTALL_ERROR}
    INSTALL_STATUS_CODE=$?
    return ${INSTALL_STATUS_CODE}
}

build_phpcpp()
{
    make ${MAKEFLAGS} || return ${PHPTDLIB_BUILD_PHPCPP_FAILED}
    return 0
}

build_json()
{
    mkdir build
    cd build
    if [ ! -z "${MAKEFLAGS}" ]; then
        cmake .. -- ${MAKEFLAGS} || return ${PHPTDLIB_BUILD_JSON_FAILED}
    else
        cmake .. || return ${PHPTDLIB_BUILD_JSON_FAILED}
    fi
    return 0
}

build_td()
{
    mkdir build
    cd build
    if [ ! -z "${MAKEFLAGS}" ]; then
        cmake -DCMAKE_BUILD_TYPE=Release .. -- ${MAKEFLAGS} || return ${PHPTDLIB_BUILD_TD_FAILED}
        cmake --build . -- ${MAKEFLAGS} || return ${PHPTDLIB_BUILD_TD_FAILED}
    else
        cmake -DCMAKE_BUILD_TYPE=Release .. || return ${PHPTDLIB_BUILD_TD_FAILED}
        cmake --build . || return ${PHPTDLIB_BUILD_TD_FAILED}
    fi
    return 0
}