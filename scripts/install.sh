#!/usr/bin/env bash

# this file can be sourced: $ . ./scripts/install.sh 
PHPTDLIB_SCRIPTS_BASE_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" > /dev/null && pwd)"

# set PHPTDLIB_BASE_PATH and PHPTDLIB_CACHE_DIR
# PHPTDLIB_CACHE_DIR overwrites from first argument of this script, if set. Make dir if not exists
PHPTDLIB_BASE_PATH=$(dirname ${PHPTDLIB_SCRIPTS_BASE_PATH})
PHPTDLIB_CACHE_DIR="${PHPTDLIB_BASE_PATH}/cached_builds"
if [ ! -z "${1}" ]; then
    PHPTDLIB_CACHE_DIR=$1
fi
mkdir -p ${PHPTDLIB_CACHE_DIR}

# include functions
source ${PHPTDLIB_SCRIPTS_BASE_PATH}/functions.sh

# check if CONFIG (required) is set: $ CONFIG=gcc ./scripts/install.sh
if [ -z "${CONFIG}" ]; then
    echo '$CONFIG must be set'
    exit 1
fi

# set PHPTDLIB_CURRENT_OS from TRAVIS_OS_NAME (optional). Default: $(uname -s)
if [ ! -z "${TRAVIS_OS_NAME}" ]; then
    PHPTDLIB_CURRENT_OS=${TRAVIS_OS_NAME}
else
    PHPTDLIB_CURRENT_OS=$(uname -s)
fi

# set PHPTDLIB_CURRENT_BRANCH from TRAVIS_BRANCH (optional). Default: $(get_current_branch), see functions.sh
if [ ! -z "${TRAVIS_BRANCH}" ]; then
    PHPTDLIB_CURRENT_BRANCH=${TRAVIS_BRANCH}
else
    PHPTDLIB_CURRENT_BRANCH=$(get_current_branch)
fi

# declare assoc array with dependencies. LIBRARY_ALIAS => LIBRARY_REPO_HTTPS_URI
declare -A PHPTDLIB_DEPS
PHPTDLIB_DEPS['PHPCPP']="https://github.com/CopernicaMarketingSoftware/PHP-CPP.git"
PHPTDLIB_DEPS['JSON']="https://github.com/nlohmann/json.git"
PHPTDLIB_DEPS['TD']="https://github.com/tdlib/td.git"

# for each library get head hash, check if build cache exists (if not - clone and build) and install
for LIBRARY_ALIAS in "${!PHPTDLIB_DEPS[@]}"
do
    LIBRARY_REPO_HTTPS_URI=${PHPTDLIB_DEPS[${LIBRARY_ALIAS}]}
    LIBRARY_REPO_HEAD_HASH="$(get_repository_head_hash ${LIBRARY_REPO_HTTPS_URI})"

    if [ ! -z "${LIBRARY_REPO_HEAD_HASH}" ]; then
        LIBRARY_CACHE_PATH="${PHPTDLIB_CACHE_DIR}/${PHPTDLIB_CURRENT_OS}/${PHPTDLIB_CURRENT_BRANCH}/${CONFIG}/${LIBRARY_ALIAS}/${LIBRARY_REPO_HEAD_HASH}"
        if [ ! -d "${LIBRARY_CACHE_PATH}" ]; then
            echo "Build ${LIBRARY_ALIAS} in ${LIBRARY_CACHE_PATH}."
            mkdir -p ${LIBRARY_CACHE_PATH}
            cd ${LIBRARY_CACHE_PATH}
            git clone ${LIBRARY_REPO_HTTPS_URI} .
            build ${LIBRARY_ALIAS} ${LIBRARY_CACHE_PATH}
            BUILD_STATUS_CODE=$?
            if [ ${BUILD_STATUS_CODE} == 0 ]; then
                echo "${LIBRARY_ALIAS} successfully builded in ${LIBRARY_CACHE_PATH}."
            else
                echo "Build ${LIBRARY_ALIAS} failed (${BUILD_STATUS_CODE}). Remove cache ${LIBRARY_CACHE_PATH}."
                rm -rf ${LIBRARY_CACHE_PATH}
                cd ${PHPTDLIB_BASE_PATH}
            fi
        else
            echo "${LIBRARY_ALIAS} is up to date. Cache path: ${LIBRARY_CACHE_PATH}."
        fi

        echo "Install ${LIBRARY_ALIAS} from ${LIBRARY_CACHE_PATH}."
        install ${LIBRARY_ALIAS} ${LIBRARY_CACHE_PATH}
        INSTALL_STATUS_CODE=$?
        if [ ${INSTALL_STATUS_CODE} == 0 ]; then
            echo "${LIBRARY_ALIAS} successfully installed from ${LIBRARY_CACHE_PATH}."
        else
            echo "Install ${LIBRARY_ALIAS} failed (${INSTALL_STATUS_CODE}). Remove cache ${LIBRARY_CACHE_PATH}."
            rm -rf ${LIBRARY_CACHE_PATH}
            cd ${PHPTDLIB_BASE_PATH}
        fi
        # PHPTDLIB_DEPS_CACHE_PATH[${LIBRARY_ALIAS}]=${LIBRARY_CACHE_PATH}
    else
        echo "Not found master head hash for ${LIBRARY_ALIAS}. Please check PHPTDLIB_DEPS. Skipped."
    fi
done
