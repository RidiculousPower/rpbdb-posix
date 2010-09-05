#ifndef RPDB_CONSTANTS
	#define RPDB_CONSTANTS

	 /***************
	 *  Constants  *
	 ****************/
	
	typedef enum BOOL_e	{
	
		FALSE	= 0,
		TRUE	= 1
		
	}	BOOL;
	
	typedef enum RPDB_SECONDARY_KEY_CREATION_RETURN_e	{
		
		RPDB_SECONDARY_KEY_CREATION_FAILED_DO_NOT_INDEX										= 1,
		RPDB_RECORD_ALLOCATED_BY_APPLICATION															= 2,
		RPDB_RECORD_CONTAINS_MULTIPLE_SECONDARY_KEYS											= 3,
		RPDB_RECORD_ALLOCATED_BY_APPLICATION_FOR_MULTIPLE_SECONDARY_KEYS	= 4
		
	}	RPDB_SECONDARY_KEY_CREATION_RETURN;
	
	#define RPDB_NO_FLAGS 0
	#define RPDB_FUNCTION_HAS_NO_FLAGS RPDB_NO_FLAGS
	#define RPDB_UNITIALIZED -42

	#define RPDB_EMPTY_KEY_EXISTS				-1
	#define RPDB_DATABASE_NOT_OPEN				-2
	#define RPDB_DATABASE_ALREADY_ASSOCIATED	-3

	#define RP_NO_ERROR 0
	
	#define RPDB_IN_MEMORY ""

	#define RPDB_MULTIPLE_ACCESS 1

	#define RP_IN_ENVIRONMENT 42
	
	#define RP_TYPE_UNKNOWN 37
	
	//	Logfile names are usually quite short - on the order of 10 characters
	#define	MAX_LOGFILE_FILENAME_LENGTH 20

	#define RP_ERROR_NOT_DB_QUEUE															-1
	#define	RP_ERROR_NOT_DB_QUEUE_OR_DB_RECNO									-2
	#define RP_ERROR_NO_SETTING_DB_CACHE_WHILE_IN_ENVIRONMENT	-3
	#define RP_ERROR_PERCENT_OUT_OF_BOUNDS										-4
	#define RP_ERROR_NO_FILE_AT_PATH													-5
	#define RPDB_ERROR_TRANSACTION_OPEN												-6
	#define RPDB_ERROR_DUPLICATES_NOT_SUPPORTED								-7
	#define RPDB_ERROR_DEFAULT_ENVIRONMENT_NOT_FOUND					-8
	#define RPDB_ERROR_ENVIRONMENT_NOT_FOUND									-9
	
	#define RPDB_ERROR_MESSAGE_TRANSACTION_OPEN								"Transaction is already open."
	#define RPDB_ERROR_MESSAGE_DEFAULT_ENVIRONMENT_NOT_FOUND	"Default Environment was missing."
	#define RPDB_ERROR_MESSAGE_ENVIRONMENT_NOT_FOUND					"Requested Environment was missing."
	
	#define RPDB_DEFAULT_ENVIRONMENT_HOME_DIRECTORY						"./"

	#define RPDB_DEFAULT_ENVIRONMENT_LOG											TRUE
	//	FALSE means log to stderr, TRUE means to environment.err.log
	#define RPDB_DEFAULT_ENVIRONMENT_LOG_TO_FILE							FALSE	
	#define RPDB_DEFAULT_ENVIRONMENT_LOG_DIRECTORY						"error_log"
	#define RPDB_DEFAULT_ENVIRONMENT_LOG_FILE									"environment"
	#define RPDB_DEFAULT_ENVIRONMENT_LOG_FILE_SUFFIX					".err.log"	
	
	#define RPDB_DEFAULT_DATABASE_LOG													TRUE
	//	FALSE means log to stderr, TRUE means to database_name.db.err.log
	#define RPDB_DEFAULT_DATABASE_LOG_TO_FILE									RPDB_DEFAULT_ENVIRONMENT_LOG_TO_FILE
	//	Log in place writes the log file where the database is kept
	#define RPDB_DEFAULT_DATABASE_LOG_IN_PLACE								FALSE
	//	Alternatively, the log files can be written to a single directory
	#define RPDB_DEFAULT_DATABASE_LOG_IN_DIRECTORY						RPDB_DEFAULT_ENVIRONMENT_LOG_DIRECTORY
	#define RPDB_DEFAULT_DATABASE_LOG_FILE_SUFFIX							RPDB_DEFAULT_ENVIRONMENT_LOG_FILE_SUFFIX
	
	#define RPDB_DATABASE_FILENAME_EXTENSION									"db"
	#define RPDB_DELIMITER																		"-##-"
	#define	RPDB_ENVIRONMENT_AUTO_HANDLE											"environment_auto_name_"
	#define	RPDB_DATABASE_AUTO_HANDLE													"database_auto_name_"
	
	#define RPDB_DATABASE_CURSOR_DEFAULT_HANDLE								"cursor"
	#define RPDB_DATABASE_CURSOR_HANDLE_DELIMETER							"_"

	#define RPDB_MAX_ADDRESS_STRING_LENGTH										8

	//	Defaults
	#define RPDB_DEFAULT_MEMORY_POOL_ON												1
	#define RPDB_DEFAULT_CONCURRENT_DATA_STORE_ON							0
	#define RPDB_DEFAULT_TRANSACTION_DATA_STORE_ON						1
	#define RPDB_DEFAULT_SET_ENVIRONMENT_PATH_ON							1
	#define RPDB_DEFAULT_CREATE_IF_NECESSARY									1
	#define RPDB_DEFAULT_TO_BTREE															1
	#define RPDB_DEFAULT_FAILCHECK														1
	#define RPDB_DEFAULT_LOG_ENVIRONMENT											1

	//	8 seems to be the minimum for the thread bucket to be enabled
	//	based on comments here: http://dbaspot.com/forums/berkeley-db/266115-is_alive-example.html
	//	otherwise we get: "is_alive method specified but no thread region allocated"
	//	have not personally investigated
	#define RPDB_DEFAULT_THREAD_COUNT													16
	
	//	Runtime storage stores recno => address or address => address
	//	so keys are sizeof(db_recno_t) or sizeof(uintptr_t)
	//	and data are sizeof(uintptr_t)
	//	Generally both rb_recno_t and uintptr_t are 8bits
	#define RPDB_RUNTIME_STORAGE_CACHE_SIZE_IN_MB							5
	//	The minimum page size is 512, which will be far more than large enough
	#define RPDB_RUNTIME_STORAGE_PAGE_SIZE_IN_K								512
	
#endif