/*
 *		RPDB::SettingsController::LogSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_LogSettingsController.h"

#include "RPDB_LogCursor.h"
#include "RPDB_Environment.h"

#include "RPDB_LogSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_LogSettingsController* RPDB_LogSettingsController_new( RPDB_SettingsController* parent_settings_controller )	{
	
	RPDB_LogSettingsController*		log_settings_controller = calloc( 1, sizeof( RPDB_LogSettingsController ) );

	log_settings_controller->parent_settings_controller = parent_settings_controller;

	return log_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_LogSettingsController_free(	RPDB_LogSettingsController** log_settings_controller )	{

	free( *log_settings_controller );
	*log_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_LogSettingsController_parentEnvironment(	RPDB_LogSettingsController* log_settings_controller )	{
	return log_settings_controller->parent_settings_controller->parent_environment;
}

/***********
*  on  *
***********/

//	DB_INIT_LOG			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_LogSettingsController_on( RPDB_LogSettingsController* log_settings_controller )	{

	if ( log_settings_controller->on == TRUE )	{
		return DB_INIT_LOG;
	}
	return FALSE;
}

	/**************
	*  turnOn  *
	**************/

	void RPDB_LogSettingsController_turnOn( RPDB_LogSettingsController* log_settings_controller )	{
		log_settings_controller->on = TRUE;
	}

/*************
*  off  *
*************/

BOOL RPDB_LogSettingsController_off( RPDB_LogSettingsController* log_settings_controller )	{

	if ( log_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

	/*****************
	*  turnOff  *
	*****************/

	void RPDB_LogSettingsController_turnOff( RPDB_LogSettingsController* log_settings_controller )	{
		log_settings_controller->on = FALSE;
	}

/*****************
*  buffering  *
*****************/

//	DB_LOG_DIRECT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
//	Inverted from BDB Default
int RPDB_LogSettingsController_disableSystemBuffering( RPDB_LogSettingsController* log_settings_controller )	{
	//	Since the default is inverted from how we want to describe it, we want to return the setting if FALSE
	log_settings_controller->disable_system_buffering = RPDB_LogSettingsController_internal_config( log_settings_controller, DB_LOG_DIRECT );
	if ( log_settings_controller->disable_system_buffering == TRUE )	{
		return DB_LOG_DIRECT;
	}
	return FALSE;
}

	/*************************
	*  turnBufferingOn  *
	*************************/

	void RPDB_LogSettingsController_turnDisableSystemBufferingOn( RPDB_LogSettingsController* log_settings_controller )	{
	
		RPDB_LogSettingsController_internal_setConfig(	log_settings_controller, 
																										DB_LOG_DIRECT, 
																										TRUE );
		log_settings_controller->disable_system_buffering = TRUE;
	}

	/*************************
	*  turnBufferingOff  *
	*************************/

	void RPDB_LogSettingsController_turnDisableSystemBufferingOff( RPDB_LogSettingsController* log_settings_controller )	{
		RPDB_LogSettingsController_internal_setConfig(	log_settings_controller, 
																										DB_LOG_DIRECT, 
																										FALSE );
		log_settings_controller->disable_system_buffering = FALSE;
	}

/*********************************
*  flushBeforeReturnFromWrite  *
*********************************/

//	DB_LOG_DSYNC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int RPDB_LogSettingsController_flushBeforeReturnFromWrite( RPDB_LogSettingsController* log_settings_controller )	{

	log_settings_controller->flush_before_return_from_write = RPDB_LogSettingsController_internal_config( log_settings_controller, DB_LOG_DSYNC );

	if ( log_settings_controller->flush_before_return_from_write == TRUE )	{
		return DB_LOG_DSYNC;
	}
	return FALSE;	
}

	/*****************************************
	*  turnFlushBeforeReturnFromWriteOn  *
	*****************************************/

	void RPDB_LogSettingsController_turnFlushBeforeReturnFromWriteOn( RPDB_LogSettingsController* log_settings_controller )	{
		RPDB_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_DSYNC, TRUE );
		log_settings_controller->flush_before_return_from_write = TRUE;
	}

	/*****************************************
	*  turnFlushBeforeReturnFromWriteOff  *
	*****************************************/

	void RPDB_LogSettingsController_turnFlushBeforeReturnFromWriteOff( RPDB_LogSettingsController* log_settings_controller )	{
		RPDB_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_DSYNC, FALSE );
		log_settings_controller->flush_before_return_from_write = FALSE;
	}

/*********************
*  autoremoveLogs  *
*********************/

//	DB_LOG_AUTO_REMOVE	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int RPDB_LogSettingsController_autoremoveLogs( RPDB_LogSettingsController* log_settings_controller )	{

	log_settings_controller->autoremove = RPDB_LogSettingsController_internal_config( log_settings_controller, DB_LOG_AUTO_REMOVE );

	if ( log_settings_controller->autoremove == TRUE )	{
		return DB_LOG_AUTO_REMOVE;
	}
	return FALSE;	
}

	/**************************
	*  turnAutoremoveOn  *
	**************************/

	void RPDB_LogSettingsController_turnAutoremoveLogsOn( RPDB_LogSettingsController* log_settings_controller )	{
		RPDB_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_AUTO_REMOVE, TRUE );
		log_settings_controller->autoremove = TRUE;
	}

	/************************
	*  turnAutoremoveOff  *
	************************/

	void RPDB_LogSettingsController_turnAutoremoveOff( RPDB_LogSettingsController* log_settings_controller )	{
		RPDB_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_AUTO_REMOVE, FALSE );
		log_settings_controller->autoremove = FALSE;
	}

/*********************
*  logInMemory  *
*********************/

//	DB_LOG_IN_MEMORY	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int RPDB_LogSettingsController_logInMemory( RPDB_LogSettingsController* log_settings_controller )	{

	log_settings_controller->log_in_memory = RPDB_LogSettingsController_internal_config( log_settings_controller, DB_LOG_IN_MEMORY );
	
	if ( log_settings_controller->log_in_memory == TRUE )	{
		return DB_LOG_IN_MEMORY;
	}
	return FALSE;	
}

	/*************************
	*  turnLogInMemoryOn  *
	*************************/

	void RPDB_LogSettingsController_turnLogInMemoryOn( RPDB_LogSettingsController* log_settings_controller )	{
		RPDB_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_IN_MEMORY, TRUE );
		log_settings_controller->log_in_memory = TRUE;
	}

	/*************************
	*  turnLogInMemoryOff  *
	*************************/

	void RPDB_LogSettingsController_turnLogInMemoryOff( RPDB_LogSettingsController* log_settings_controller )	{
		RPDB_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_IN_MEMORY, FALSE );
		log_settings_controller->log_in_memory = FALSE;
	}

/*********************
*  zeroAtCreation  *
*********************/

//	DB_LOG_ZERO			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int RPDB_LogSettingsController_zeroAtCreation( RPDB_LogSettingsController* log_settings_controller )	{

	log_settings_controller->zero_at_creation = RPDB_LogSettingsController_internal_config( log_settings_controller, DB_LOG_ZERO );

	if ( log_settings_controller->zero_at_creation == TRUE )	{
		return DB_LOG_ZERO;
	}
	return FALSE;	
}

	/*******************************
	*  turnZeroAtCreationOn  *
	*******************************/

	void RPDB_LogSettingsController_turnZeroAtCreationOn( RPDB_LogSettingsController* log_settings_controller )	{
		RPDB_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_ZERO, TRUE );
		log_settings_controller->zero_at_creation = TRUE;
	}

	/*****************************
	*  turnZeroAtCreationOff  *
	*****************************/

	void RPDB_LogSettingsController_turnZeroAtCreationOff( RPDB_LogSettingsController* log_settings_controller )	{
		RPDB_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_ZERO, FALSE );
		log_settings_controller->zero_at_creation = FALSE;
	}

/*********************************
*  forceFlushAfterRecordWrite  *
*********************************/

int RPDB_LogSettingsController_forceFlushAfterRecordWrite( RPDB_LogSettingsController* log_settings_controller )	{

	if ( log_settings_controller->force_flush_after_record_write == TRUE )	{
		
		return DB_FLUSH;
	}
	
	return FALSE;
}

	/*****************************************
	*  turnForceFlushAfterRecordWriteOn  *
	*****************************************/

	void RPDB_LogSettingsController_turnForceFlushAfterRecordWriteOn( RPDB_LogSettingsController* log_settings_controller )	{
	
		log_settings_controller->force_flush_after_record_write = TRUE;
	}

	/*****************************************
	*  turnForceFlushAfterRecordWriteOff  *
	*****************************************/

	void RPDB_LogSettingsController_turnForceFlushAfterRecordWriteOff( RPDB_LogSettingsController* log_settings_controller )	{
	
		log_settings_controller->force_flush_after_record_write = FALSE;
	}

/*****************
*  bufferSize  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lg_bsize.html
uint32_t RPDB_LogSettingsController_bufferSize( RPDB_LogSettingsController* log_settings_controller )	{
	
	RPDB_Environment*		environment;

	environment = log_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lg_bsize(	environment->wrapped_bdb_environment, 
															&( log_settings_controller->buffer_size ) );
	}

	return log_settings_controller->buffer_size;
}

/*********************
*  setBufferSize  *
*********************/

void RPDB_LogSettingsController_setBufferSize(	RPDB_LogSettingsController*	log_settings_controller, 
												uint32_t						buffer_size )	{

	RPDB_Environment*		environment;

	environment = log_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lg_bsize(	environment->wrapped_bdb_environment, 
															buffer_size );
	}
	
	log_settings_controller->buffer_size = buffer_size;	
}

/*****************
*  directory  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lg_dir.html
char* RPDB_LogSettingsController_directory( RPDB_LogSettingsController* log_settings_controller )	{

	RPDB_Environment*		environment;

	environment = log_settings_controller->parent_settings_controller->parent_environment;

	if (	log_settings_controller->directory == NULL
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lg_dir(	environment->wrapped_bdb_environment, 
															(const char**) &( log_settings_controller->directory ) );
	}

	return log_settings_controller->directory;
}

/*********************
*  setDirectory  *
*********************/

void RPDB_LogSettingsController_setDirectory(	RPDB_LogSettingsController*	log_settings_controller, 
												char*							directory )	{

	RPDB_Environment*		environment;

	environment = log_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_lg_dir( environment->wrapped_bdb_environment, directory );
	}
	
	log_settings_controller->directory = directory;
}

/*************
*  mode  *
*************/

//	Set the absolute file mode for created log files. This method is only useful for the rare Berkeley DB application that does not control its umask value.
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lg_mode.html
int RPDB_LogSettingsController_mode( RPDB_LogSettingsController* log_settings_controller )	{

	RPDB_Environment*		environment;

	environment = log_settings_controller->parent_settings_controller->parent_environment;

	if (	log_settings_controller->mode == RPDB_UNITIALIZED
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lg_filemode(	environment->wrapped_bdb_environment, 
										&( log_settings_controller->mode ) );
	}
	return log_settings_controller->mode;
}

/*****************
*  setMode  *
*****************/

void RPDB_LogSettingsController_setMode(	RPDB_LogSettingsController*	log_settings_controller, 
											int								mode )	{

	RPDB_Environment*		environment;

	environment = log_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_lg_filemode(	environment->wrapped_bdb_environment, 
																mode );
	}
	
	log_settings_controller->mode = mode;
}

/*****************
*  maxLogSize  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lg_max.html
int RPDB_LogSettingsController_maxLogSize( RPDB_LogSettingsController* log_settings_controller )	{

	RPDB_Environment*		environment;

	environment = log_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lg_max(	environment->wrapped_bdb_environment, 
															(uint32_t*) &( log_settings_controller->max_size ) );
	}

	return log_settings_controller->max_size;
}

/*********************
*  setMaxLogSize  *
*********************/

void RPDB_LogSettingsController_setMaxLogSize( RPDB_LogSettingsController* log_settings_controller, uint32_t max_size )	{

	RPDB_Environment*	environment	= log_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lg_max(	environment->wrapped_bdb_environment, 
															max_size );
	}
	
	log_settings_controller->max_size = max_size;
}

/*********************
*  maxRegionSize  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lg_regionmax.html
int RPDB_LogSettingsController_maxRegionSize( RPDB_LogSettingsController* log_settings_controller )	{

	RPDB_Environment*		environment;

	environment = log_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lg_regionmax(	environment->wrapped_bdb_environment, 
																(uint32_t*) &( log_settings_controller->max_region_size ) );
	}

	return log_settings_controller->max_region_size;
}

/*************************
*  setMaxRegionSize  *
*************************/

void RPDB_LogSettingsController_setMaxRegionSize( RPDB_LogSettingsController* log_settings_controller, uint32_t max_region_size )	{

	RPDB_Environment*		environment = log_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_lg_regionmax(	environment->wrapped_bdb_environment,
																max_region_size );
	}
	
	log_settings_controller->max_region_size = max_region_size;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/**************
*  config  *
**************/

BOOL RPDB_LogSettingsController_internal_config( RPDB_LogSettingsController* log_settings_controller, uint32_t which_flag )	{

	RPDB_Environment*		environment	= log_settings_controller->parent_settings_controller->parent_environment;
	int			on_or_off	=	FALSE;
	
	if (	environment->wrapped_bdb_environment != NULL
		&&	RPDB_LogSettingsController_on( log_settings_controller ) )	{

		environment->wrapped_bdb_environment->log_get_config(	environment->wrapped_bdb_environment, 
																													which_flag, 
																													& on_or_off );
	}
	
	return ( on_or_off ? TRUE : FALSE );
}

/*****************
*  setConfig  *
*****************/

void RPDB_LogSettingsController_internal_setConfig(	RPDB_LogSettingsController* log_settings_controller, 
																										uint32_t which_flag, 
																										BOOL on_or_off )	{

	RPDB_Environment*		environment	= log_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->log_set_config(	environment->wrapped_bdb_environment, 
																													which_flag, 
																													on_or_off );
	}
}

/*****************
*  openFlags  *
*****************/

int RPDB_LogSettingsController_internal_openFlags( RPDB_LogSettingsController* log_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RPDB_NO_FLAGS;
}

/*****************
*  closeFlags  *
*****************/

int RPDB_LogSettingsController_internal_closeFlags( RPDB_LogSettingsController* log_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RPDB_NO_FLAGS;
}

/*************************
*  appendRecordFlags  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_put.html
int RPDB_LogSettingsController_internal_appendRecordFlags( RPDB_LogSettingsController* log_settings_controller )	{
	
	return RPDB_LogSettingsController_forceFlushAfterRecordWrite( log_settings_controller );	
}

/*********************
*  setLogConfig  *
********************/

void RPDB_LogSettingsController_internal_setLogConfig( RPDB_LogSettingsController* log_settings_controller )	{
	
	RPDB_Environment*		environment	= log_settings_controller->parent_settings_controller->parent_environment;
	
	if (	environment->wrapped_bdb_environment != NULL
		&&	environment->is_open )	{
	
		environment->wrapped_bdb_environment->log_set_config(	environment->wrapped_bdb_environment,
																RPDB_LogSettingsController_disableSystemBuffering( log_settings_controller )
																|	RPDB_LogSettingsController_flushBeforeReturnFromWrite( log_settings_controller )
																|	RPDB_LogSettingsController_autoremoveLogs( log_settings_controller )
																|	RPDB_LogSettingsController_logInMemory( log_settings_controller )
																|	RPDB_LogSettingsController_zeroAtCreation( log_settings_controller ),
																1	);
	}
}
	
/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_LogSettingsController* RPDB_LogSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_LogSettingsController* log_settings_controller )	{

	RPDB_LogSettingsController* log_settings_controller_copy	=	RPDB_LogSettingsController_new( log_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	log_settings_controller_copy->buffer_size	=	log_settings_controller->buffer_size;
	log_settings_controller_copy->zero_at_creation	=	log_settings_controller->zero_at_creation;
	log_settings_controller_copy->directory	=	log_settings_controller->directory;
	log_settings_controller_copy->log_in_memory	=	log_settings_controller->log_in_memory;
	log_settings_controller_copy->disable_system_buffering	=	log_settings_controller->disable_system_buffering;
	log_settings_controller_copy->mode	=	log_settings_controller->mode;
	log_settings_controller_copy->force_flush_after_record_write	=	log_settings_controller->force_flush_after_record_write;
	log_settings_controller_copy->max_region_size	=	log_settings_controller->max_region_size;
	log_settings_controller_copy->max_size	=	log_settings_controller->max_size;
	log_settings_controller_copy->autoremove	=	log_settings_controller->autoremove;
	log_settings_controller_copy->flush_before_return_from_write	=	log_settings_controller->flush_before_return_from_write;
	log_settings_controller_copy->on	=	log_settings_controller->on;

	return log_settings_controller_copy;
}

