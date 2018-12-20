cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(EXT_NAME tdlib)
set(EXT_VERSION 0.0.7)
project(${EXT_NAME} VERSION ${EXT_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)



FIND_PROGRAM(PHP_CONFIG NAMES php-config)
if(NOT PHP_CONFIG)
    message(SEND_ERROR "Failed to find php-config")
    return()
endif()

execute_process(
        COMMAND ${PHP_CONFIG} --include-dir
        OUTPUT_VARIABLE PHPCPP_PHP_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
        COMMAND ${PHP_CONFIG} --configure-options
        COMMAND sed -ne "s/^.*--with-config-file-scan-dir=\\([^ ]*\\).*/\\1/p"
        OUTPUT_VARIABLE PHP_CONFIG_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
        COMMAND ${PHP_CONFIG} --extension-dir
        OUTPUT_VARIABLE PHP_EXTENSIONS_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
        COMMAND ${PHP_CONFIG} --vernum
        OUTPUT_VARIABLE PHP_VERSION_NUMBER
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(PHP_VERSION_NUMBER LESS 70000)
    message(SEND_ERROR "PHP-CPP works only with PHP ^7.0. For older PHP versions, use the PHP-CPP-LEGACY instead.")
    return()
endif()





add_subdirectory(modules/td)


# PHP-CPP now has incorrect CMakeLists.txt
# Waiting for fixes in PR 399 to be applied
# todo: uncomment when the PHP-CPP problems will be fixed
#SET(PHPCPP_ARCH "x86_64" CACHE STRING "")
#include_directories(modules/PHP-CPP modules/PHP-CPP/include)
#add_subdirectory(modules/PHP-CPP)
find_library(PHPCPP phpcpp)
if(NOT PHPCPP)
	message(SEND_ERROR "Failed to find PHP-CPP")
	return()
endif()


set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(modules/json)



set(SOURCE_FILES
        tdlib.cpp
        include/TDLib/BaseJsonClient.cpp
        include/TDLib/JsonClient.cpp
        include/TDApi/TDLibParameters.cpp
        include/TDApi/TDLibLogConfiguration.cpp
        include/td_json_client_func.cpp
        )
set(EXT_INI_FILE ${EXT_NAME}.ini)


set(CMAKE_SHARED_LIBRARY_PREFIX "")
add_library(${EXT_NAME} SHARED ${SOURCE_FILES})


target_link_libraries(${EXT_NAME}
        PRIVATE
            Td::TdJson
            Td::TdStatic
            nlohmann_json::nlohmann_json
        PUBLIC
            phpcpp
        )

add_custom_command(TARGET ${EXT_NAME}
    POST_BUILD
    COMMAND echo 'extension=${CMAKE_SHARED_LIBRARY_PREFIX}${EXT_NAME}.so' > ${EXT_INI_FILE}
    COMMAND sudo cp -f ${EXT_INI_FILE}; ${PHP_CONFIG_DIR}
    COMMAND rm -f ${EXT_INI_FILE}
    COMMAND sudo cp -f $<TARGET_FILE:${EXT_NAME}> ${PHP_EXTENSIONS_DIR}
    COMMAND rm -f $<TARGET_FILE:${EXT_NAME}>
)
