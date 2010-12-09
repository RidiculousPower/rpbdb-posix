#ifndef Rbdb_CONSTANTS
	#define Rbdb_CONSTANTS

	 /***************
	 *  Constants  *
	 ****************/
	
	#ifndef FALSE
		#define FALSE 0
	#endif
	#ifndef TRUE
		#define TRUE 1
	#endif
	
	#ifndef BOOL
		typedef int BOOL;
	#endif
	
	typedef enum Rbdb_SECONDARY_KEY_CREATION_RETURN_e	{
		
		Rbdb_SECONDARY_KEY_CREATION_FAILED_DO_NOT_INDEX										= 1,
		Rbdb_RECORD_ALLOCATED_BY_APPLICATION															= 2,
		Rbdb_RECORD_CONTAINS_MULTIPLE_SECONDARY_KEYS											= 3,
		Rbdb_RECORD_ALLOCATED_BY_APPLICATION_FOR_MULTIPLE_SECONDARY_KEYS	= 4
		
	}	Rbdb_SECONDARY_KEY_CREATION_RETURN;
	
	#define Rbdb_NO_FLAGS 0
	#define Rbdb_FUNCTION_HAS_NO_FLAGS Rbdb_NO_FLAGS
	#define Rbdb_UNITIALIZED -42

	#define Rbdb_EMPTY_KEY_EXISTS				-1
	#define Rbdb_DATABASE_NOT_OPEN				-2
	#define Rbdb_DATABASE_ALREADY_ASSOCIATED	-3

	#define RP_NO_ERROR 0
	
	#define Rbdb_IN_MEMORY ""

	#define Rbdb_MULTIPLE_ACCESS 1

	#define RP_IN_ENVIRONMENT 42
	
	#define RP_TYPE_UNKNOWN 37
	
	//	Logfile names are usually quite short - on the order of 10 characters
	#define	MAX_LOGFILE_FILENAME_LENGTH 20

	#define RP_ERROR_NOT_DB_QUEUE															-1
	#define	RP_ERROR_NOT_DB_QUEUE_OR_DB_RECNO									-2
	#define RP_ERROR_NO_SETTING_DB_CACHE_WHILE_IN_ENVIRONMENT	-3
	#define RP_ERROR_PERCENT_OUT_OF_BOUNDS										-4
	#define RP_ERROR_NO_FILE_AT_PATH													-5
	#define Rbdb_ERROR_TRANSACTION_OPEN												-6
	#define Rbdb_ERROR_DUPLICATES_NOT_SUPPORTED								-7
	#define Rbdb_ERROR_DEFAULT_ENVIRONMENT_NOT_FOUND					-8
	#define Rbdb_ERROR_ENVIRONMENT_NOT_FOUND									-9
	
	#define Rbdb_ERROR_MESSAGE_TRANSACTION_OPEN								"Transaction is already open."
	#define Rbdb_ERROR_MESSAGE_DEFAULT_ENVIRONMENT_NOT_FOUND	"Default Environment was missing."
	#define Rbdb_ERROR_MESSAGE_ENVIRONMENT_NOT_FOUND					"Requested Environment was missing."
	
	#define Rbdb_DEFAULT_ENVIRONMENT_HOME_DIRECTORY						"./"

	#define Rbdb_DEFAULT_ENVIRONMENT_LOG											TRUE
	//	FALSE means log to stderr, TRUE means to environment.err.log
	#define Rbdb_DEFAULT_ENVIRONMENT_LOG_TO_FILE							FALSE	
	#define Rbdb_DEFAULT_ENVIRONMENT_LOG_DIRECTORY						"error_log"
	#define Rbdb_DEFAULT_ENVIRONMENT_LOG_FILE									"environment"
	#define Rbdb_DEFAULT_ENVIRONMENT_LOG_FILE_SUFFIX					".err.log"	
	
	#define Rbdb_DEFAULT_DATABASE_LOG													TRUE
	//	FALSE means log to stderr, TRUE means to database_name.db.err.log
	#define Rbdb_DEFAULT_DATABASE_LOG_TO_FILE									Rbdb_DEFAULT_ENVIRONMENT_LOG_TO_FILE
	//	Log in place writes the log file where the database is kept
	#define Rbdb_DEFAULT_DATABASE_LOG_IN_PLACE								FALSE
	//	Alternatively, the log files can be written to a single directory
	#define Rbdb_DEFAULT_DATABASE_LOG_IN_DIRECTORY						Rbdb_DEFAULT_ENVIRONMENT_LOG_DIRECTORY
	#define Rbdb_DEFAULT_DATABASE_LOG_FILE_SUFFIX							Rbdb_DEFAULT_ENVIRONMENT_LOG_FILE_SUFFIX
	
	#define Rbdb_DATABASE_FILENAME_EXTENSION									"db"
	#define Rbdb_DELIMITER																		"-##-"
	#define	Rbdb_ENVIRONMENT_AUTO_HANDLE											"environment_auto_name_"
	#define	Rbdb_DATABASE_AUTO_HANDLE													"database_auto_name_"
	#define Rbdb_SECONDARY_DATABASE_INDEX_DELIMITER						"__idx__"
	
	#define Rbdb_DATABASE_CURSOR_DEFAULT_HANDLE								"cursor"
	#define Rbdb_DATABASE_CURSOR_HANDLE_DELIMETER							"_"

	#define Rbdb_MAX_ADDRESS_STRING_LENGTH										8

	//	Defaults
	#define Rbdb_DEFAULT_MEMORY_POOL_ON												1
	#define Rbdb_DEFAULT_CONCURRENT_DATA_STORE_ON							0
	#define Rbdb_DEFAULT_TRANSACTION_DATA_STORE_ON						1
	#define Rbdb_DEFAULT_SET_ENVIRONMENT_PATH_ON							1
	#define Rbdb_DEFAULT_CREATE_IF_NECESSARY									1
	#define Rbdb_DEFAULT_TO_BTREE															1
	#define Rbdb_DEFAULT_FAILCHECK														1
	#define Rbdb_DEFAULT_LOG_ENVIRONMENT											1

	//	8 seems to be the minimum for the thread bucket to be enabled
	//	based on comments here: http://dbaspot.com/forums/berkeley-db/266115-is_alive-example.html
	//	otherwise we get: "is_alive method specified but no thread region allocated"
	//	have not personally investigated
	#define Rbdb_DEFAULT_THREAD_COUNT													16
	
	//	Runtime storage stores recno => address or address => address
	//	so keys are sizeof(db_recno_t) or sizeof(uintptr_t)
	//	and data are sizeof(uintptr_t)
	//	Generally both rb_recno_t and uintptr_t are 8bits
	#define Rbdb_RUNTIME_STORAGE_CACHE_SIZE_IN_MB							5
	//	The minimum page size is 512, which will be far more than large enough
	#define Rbdb_RUNTIME_STORAGE_PAGE_SIZE_IN_K								512

	//	we don't want one runtime storage of "name" to close/free another runtime storage of "name"'s instances			
	//	for this reason, each runtime storage needs its own unique identifier
	#define Rbdb_RUNTIME_STORAGE( parent, runtime_storage_name )																																																\
		Rbdb_RuntimeStorageController*	runtime_storage_controller	=	Rbdb_RuntimeStorageController_sharedInstance();																			\
		Rbdb_DatabaseController*	runtime_database_controller	=	Rbdb_Environment_databaseController(	runtime_storage_controller->runtime_environment );	\
		char*		runtime_database_identifier		=	calloc( strlen( runtime_storage_name ) + 1, sizeof( char ) );																							\
		sprintf(	runtime_database_identifier, "%s-%p", runtime_storage_name, parent );																											\
		Rbdb_Database*	runtime_storage_database	=	Rbdb_Database_new(	runtime_database_controller,																											\
																																		runtime_database_identifier );																										\
		runtime_storage_database	=	Rbdb_Database_internal_initForRuntimeStorage(	runtime_storage_database );																							\
		parent->runtime_storage_database	=	runtime_storage_database;
			
#endif