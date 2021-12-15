cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(EXT_NAME tdlib)
set(EXT_VERSION 0.0.10)
project(${EXT_NAME} VERSION ${EXT_VERSION} LANGUAGES CXX)



set(PHP_CONFIG_FILENAME php-config)


#To compile for another PHP version choose the correct php-config, for example
#   set(PHP_CONFIG_FILENAME php-config7.2)

#If you want to preinstalled libraries (not to compile them every time), set the following flags:
#   set(USE_SHARED_TD ON)
#   set(USE_SHARED_JSON ON)
#   set(USE_SHARED_PHPCPP ON)

#By default tests are compiled in debug build and not compiled in release. If you want to
#change this begaviour manualy, you can set the following constant to ON or OFF:
#   set(TDLIB_BUILD_TESTS ON)


#PHP-CPP has an error in CMakeLists.txt. So, currently we can use it only as a shared library:
set(USE_SHARED_PHPCPP ON)






set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(ColourBold  "${Esc}[1m")
    set(Red         "${Esc}[31m")
    set(Green       "${Esc}[32m")
    set(Yellow      "${Esc}[33m")
    set(Blue        "${Esc}[34m")
    set(Magenta     "${Esc}[35m")
    set(Cyan        "${Esc}[36m")
    set(White       "${Esc}[37m")
    set(BoldRed     "${Esc}[1;31m")
    set(BoldGreen   "${Esc}[1;32m")
    set(BoldYellow  "${Esc}[1;33m")
    set(BoldBlue    "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan    "${Esc}[1;36m")
    set(BoldWhite   "${Esc}[1;37m")
endif()


###################
#Determining PHP properties
###################

find_program(PHP_CONFIG NAMES ${PHP_CONFIG_FILENAME})
if(NOT PHP_CONFIG)
    message(SEND_ERROR "Failed to find ${PHP_CONFIG_FILENAME}")
    return()
endif()

execute_process(
        COMMAND ${PHP_CONFIG} --php-binary
        OUTPUT_VARIABLE PHP_BINARY
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
        COMMAND ${PHP_CONFIG} --include-dir
        OUTPUT_VARIABLE PHP_INCLUDE_DIR
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
execute_process(
        COMMAND ${PHP_BINARY} -r "echo PHP_INT_SIZE*8;"
        OUTPUT_VARIABLE PHP_BIT_ARCHITECTURE
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(PHP_VERSION_NUMBER LESS 70000)
    message(SEND_ERROR "PHP-CPP works only with PHP ^7.0. For older PHP versions, use the PHP-CPP-LEGACY instead.")
    return()
endif()



###################
#Compiling dependencies
###################

if(USE_SHARED_TD)
    find_package(Td 1.7.10 REQUIRED)
    if(NOT Td_FOUND)
        message(SEND_ERROR "Failed to find Td")
        return()
    endif()
    set(TD_LINK
            Td::TdJson
            Td::TdStatic
            )
else()
    add_subdirectory(modules/td EXCLUDE_FROM_ALL)
    set(TD_LINK
            Td::TdJsonStatic
            Td::TdStatic
            )
endif()

if(USE_SHARED_PHPCPP)
    find_library(PHPCPP phpcpp)
    if(NOT PHPCPP)
        message(SEND_ERROR "Failed to find PHP-CPP")
        return()
    endif()
else()
    # PHP-CPP now has incorrect CMakeLists.txt, so it could not be compiled via add_subdirectory.
    # Waiting for fixes in PR 399 to be applied. Use USE_SHARED_PHPCPP instead of this.
    message(SEND_ERROR "Currently PHP-CPP can be used only as a shared library. Use -DUSE_SHARED_PHPCPP option")

    set(PHPCPP_PHP_PATH "${PHP_INCLUDE_DIR}" CACHE STRING "")
    if("${PHP_BIT_ARCHITECTURE}" STREQUAL "64")
        set(PHPCPP_ARCH "x86_64" CACHE STRING "")
    else()
        set(PHPCPP_ARCH "x86" CACHE STRING "")
    endif()
    include_directories(modules/PHP-CPP modules/PHP-CPP/include)
    add_subdirectory(modules/PHP-CPP EXCLUDE_FROM_ALL)
endif()

if(USE_SHARED_JSON)
    find_file(NLOHMANN_JSON_INCLUDE_FILE nlohmann/json.hpp)
    if(NOT NLOHMANN_JSON_INCLUDE_FILE)
        message(SEND_ERROR "Failed to find nlohmann_json")
    endif()
    set(NLOHMANN_JSON_LINK, "")
else()
    set(JSON_BuildTests OFF CACHE INTERNAL "")
    include_directories(modules/json/include)
    add_subdirectory(modules/json EXCLUDE_FROM_ALL)
    set(NLOHMANN_JSON_LINK, "nlohmann_json::nlohmann_json")
endif()


###################
#Compiling phptdlib
###################

set(SOURCE_FILES
        tdlib.cpp
        include/TDLib/BaseJsonClient.cpp
        include/TDLib/JsonClient.cpp
        include/TDApi/TDLibParameters.cpp
        include/TDApi/TDLibLogConfiguration.cpp
        include/td_json_client_func.cpp
        include/common.cpp
        )
set(EXT_INI_FILE ${EXT_NAME}.ini)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if(APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
endif()

add_library(${EXT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${EXT_NAME}
        PRIVATE
            ${TD_LINK}
            ${NLOHMANN_JSON_LINK}
        PUBLIC
            phpcpp
        )


###################
#Generating configuration file
###################
set(EXT_LIBRARY_FILENAME "${CMAKE_SHARED_LIBRARY_PREFIX}${EXT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}")
set(EXT_INI_CONTENTS "extension=${EXT_LIBRARY_FILENAME}")
file(WRITE ${PROJECT_BINARY_DIR}/${EXT_INI_FILE} "${EXT_INI_CONTENTS}")

###################
#Extension installation instructions
###################

install(TARGETS ${EXT_NAME} DESTINATION ${PHP_EXTENSIONS_DIR})

if("${PHP_CONFIG_DIR}" STREQUAL "")
    install(CODE "MESSAGE(\"\nThe extension is installed to ${PHP_EXTENSIONS_DIR}/${EXT_LIBRARY_FILENAME}

Now you have to ${Red}add the following line${ColourReset} at the end of your php.ini
${BoldRed}manually${ColourReset} ${Red}to be able to use the extension${ColourReset}:
    ${EXT_INI_CONTENTS}\")")
else()
    install(FILES ${PROJECT_BINARY_DIR}/${EXT_INI_FILE} DESTINATION ${PHP_CONFIG_DIR})
endif()

if(NOT DEFINED TDLIB_BUILD_TESTS)
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(TDLIB_BUILD_TESTS ON)
    else()
        set(TDLIB_BUILD_TESTS OFF)
    endif()
endif()

if(TDLIB_BUILD_TESTS)
    set(INTERFACE_POSITION_INDEPENDENT_CODE ON)

    file(GLOB TEST_SOURCES tests/src/*.cpp)

    add_executable(tester
            ${SOURCE_FILES}
            ${TEST_SOURCES}
            )

    target_link_libraries(tester
            ${TD_LINK}
            ${NLOHMANN_JSON_LINK}
            phpcpp
            php7
            )
endif()
