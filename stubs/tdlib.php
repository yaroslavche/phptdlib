<?php
// Start of extension: tdlib
// - parsed on POSIX with PHP 7.3.15 (extension version 0.0.10)

namespace {

    class PhpCpp::Functor
    {
    }

    function td_json_client_create()
    {
    }

    /**
     * @param object $client
     */
    function td_json_client_destroy($client)
    {
    }

    /**
     * @param object $client
     * @param string $query
     */
    function td_json_client_execute($client, $query)
    {
    }

    /**
     * @param object $client
     * @param int $timeout
     */
    function td_json_client_receive($client, $timeout)
    {
    }

    /**
     * @param object $client
     * @param string $query
     */
    function td_json_client_send($client, $query)
    {
    }
}

namespace TDApi {

    class LogConfiguration
    {
        /**
         * @var int
         */
        const LVL_ALL = 1024;

        /**
         * @var int
         */
        const LVL_DEBUG = 4;

        /**
         * @var int
         */
        const LVL_ERROR = 1;

        /**
         * @var int
         */
        const LVL_FATAL_ERROR = 0;

        /**
         * @var int
         */
        const LVL_INFO = 3;

        /**
         * @var int
         */
        const LVL_VERBOSE_DEBUG = 5;

        /**
         * @var int
         */
        const LVL_WARNING = 2;

        /**
         * @param string $logFilePath
         */
        public static function setLogFilePath($logFilePath)
        {
        }

        /**
         * @param int $logMaxFileSize
         */
        public static function setLogMaxFileSize($logMaxFileSize)
        {
        }

        /**
         * @param int $logVerbosityLevel
         */
        public static function setLogVerbosityLevel($logVerbosityLevel)
        {
        }
    }

    class TDLibParameters
    {
        /**
         * @var string
         */
        const API_HASH = 'api_hash';

        /**
         * @var string
         */
        const API_ID = 'api_id';

        /**
         * @var string
         */
        const APPLICATION_VERSION = 'application_version';

        /**
         * @var string
         */
        const DATABASE_DIRECTORY = 'database_directory';

        /**
         * @var string
         */
        const DEVICE_MODEL = 'device_model';

        /**
         * @var string
         */
        const ENABLE_STORAGE_OPTIMIZER = 'enable_storage_optimizer';

        /**
         * @var string
         */
        const FILES_DIRECTORY = 'files_directory';

        /**
         * @var string
         */
        const IGNORE_FILE_NAMES = 'ignore_file_names';

        /**
         * @var string
         */
        const SYSTEM_LANGUAGE_CODE = 'system_language_code';

        /**
         * @var string
         */
        const SYSTEM_VERSION = 'system_version';

        /**
         * @var string
         */
        const USE_CHAT_INFO_DATABASE = 'use_chat_info_database';

        /**
         * @var string
         */
        const USE_FILE_DATABASE = 'use_file_database';

        /**
         * @var string
         */
        const USE_MESSAGE_DATABASE = 'use_message_database';

        /**
         * @var string
         */
        const USE_SECRET_CHATS = 'use_secret_chats';

        /**
         * @var string
         */
        const USE_TEST_DC = 'use_test_dc';

        public function __debugInfo()
        {
        }

        /**
         * @param string $name
         * @param mixed $value
         */
        public function setParameter($name, $value)
        {
        }
    }
}

namespace TDLib {

    class BaseJsonClient
    {
        public function __construct()
        {
        }

        public function __destruct()
        {
        }

        /**
         * @param string $query
         */
        public function execute($query)
        {
        }

        /**
         * @param int $timeout
         */
        public function receive($timeout)
        {
        }

        /**
         * @param string $query
         */
        public function send($query)
        {
        }
    }

    class JsonClient
    {
        public function __construct()
        {
        }

        public function __destruct()
        {
        }

        /**
         * @param string $key
         * @param float|null $timeout
         */
        public function checkDatabaseEncryptionKey($key, $timeout = null)
        {
        }

        /**
         * @param string $query
         */
        public function execute($query)
        {
        }

        /**
         * @param float|null $timeout
         */
        public function getAuthorizationState($timeout = null)
        {
        }

        public function getReceivedResponses()
        {
        }

        /**
         * @param string $query
         * @param int|null $timeout
         */
        public function query($query, $timeout = null)
        {
        }

        /**
         * @param int|null $timeout
         */
        public function receive($timeout = null)
        {
        }

        /**
         * @param string $query
         */
        public function send($query)
        {
        }

        /**
         * @param string $phone_number
         * @param float|null $timeout
         */
        public function setAuthenticationPhoneNumber($phone_number, $timeout = null)
        {
        }

        /**
         * @param string|null $new_encryption_key
         * @param float|null $timeout
         */
        public function setDatabaseEncryptionKey($new_encryption_key = null, $timeout = null)
        {
        }

        /**
         * @param float $defaultTimeout
         */
        public function setDefaultTimeout($defaultTimeout)
        {
        }

        /**
         * @param \TDApi\TDLibParameters $parameters
         * @param float|null $timeout
         */
        public function setTdlibParameters($parameters, $timeout = null)
        {
        }
    }
}
