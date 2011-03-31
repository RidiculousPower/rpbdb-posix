/*
 *		RPbdb::SettingsController::LogSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "LogSettingsController.h"

#include "LogCursor.h"
#include "Environment.h"

#include "LogSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_LogSettingsController* RPbdb_LogSettingsController_new( RPbdb_SettingsController* parent_settings_controller )	{
	
	RPbdb_LogSettingsController*		log_settings_controller = calloc( 1, sizeof( RPbdb_LogSettingsController ) );

	log_settings_controller->parent_settings_controller = parent_settings_controller;

	return log_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_LogSettingsController_free(	RPbdb_LogSettingsController** log_settings_controller )	{

	free( *log_settings_controller );
	*log_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_LogSettingsController_parentEnvironment(	RPbdb_LogSettingsController* log_settings_controller )	{
	return log_settings_controller->parent_settings_controller->parent_environment;
}

/***********
*  on  *
***********/

//	DB_INIT_LOG			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPbdb_LogSettingsController_on( RPbdb_LogSettingsController* log_settings_controller )	{

	if ( log_settings_controller->on == TRUE )	{
		return DB_INIT_LOG;
	}
	return FALSE;
}

	/**************
	*  turnOn  *
	**************/

	void RPbdb_LogSettingsController_turnOn( RPbdb_LogSettingsController* log_settings_controller )	{
		log_settings_controller->on = TRUE;
	}

/*************
*  off  *
*************/

BOOL RPbdb_LogSettingsController_off( RPbdb_LogSettingsController* log_settings_controller )	{

	if ( log_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

	/*****************
	*  turnOff  *
	*****************/

	void RPbdb_LogSettingsController_turnOff( RPbdb_LogSettingsController* log_settings_controller )	{
		log_settings_controller->on = FALSE;
	}

/*****************
*  buffering  *
*****************/

//	DB_LOG_DIRECT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
//	Inverted from BDB Default
int RPbdb_LogSettingsController_disableSystemBuffering( RPbdb_LogSettingsController* log_settings_controller )	{
	//	Since the default is inverted from how we want to describe it, we want to return the setting if FALSE
	log_settings_controller->disable_system_buffering = RPbdb_LogSettingsController_internal_config( log_settings_controller, DB_LOG_DIRECT );
	if ( log_settings_controller->disable_system_buffering == TRUE )	{
		return DB_LOG_DIRECT;
	}
	return FALSE;
}

	/*************************
	*  turnBufferingOn  *
	*************************/

	void RPbdb_LogSettingsController_turnDisableSystemBufferingOn( RPbdb_LogSettingsController* log_settings_controller )	{
	
		RPbdb_LogSettingsController_internal_setConfig(	log_settings_controller, 
																										DB_LOG_DIRECT, 
																										TRUE );
		log_settings_controller->disable_system_buffering = TRUE;
	}

	/*************************
	*  turnBufferingOff  *
	*************************/

	void RPbdb_LogSettingsController_turnDisableSystemBufferingOff( RPbdb_LogSettingsController* log_settings_controller )	{
		RPbdb_LogSettingsController_internal_setConfig(	log_settings_controller, 
																										DB_LOG_DIRECT, 
																										FALSE );
		log_settings_controller->disable_system_buffering = FALSE;
	}

/*********************************
*  flushBeforeReturnFromWrite  *
*********************************/

//	DB_LOG_DSYNC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int RPbdb_LogSettingsController_flushBeforeReturnFromWrite( RPbdb_LogSettingsController* log_settings_controller )	{

	log_settings_controller->flush_before_return_from_write = RPbdb_LogSettingsController_internal_config( log_settings_controller, DB_LOG_DSYNC );

	if ( log_settings_controller->flush_before_return_from_write == TRUE )	{
		return DB_LOG_DSYNC;
	}
	return FALSE;	
}

	/*****************************************
	*  turnFlushBeforeReturnFromWriteOn  *
	*****************************************/

	void RPbdb_LogSettingsController_turnFlushBeforeReturnFromWriteOn( RPbdb_LogSettingsController* log_settings_controller )	{
		RPbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_DSYNC, TRUE );
		log_settings_controller->flush_before_return_from_write = TRUE;
	}

	/*****************************************
	*  turnFlushBeforeReturnFromWriteOff  *
	*****************************************/

	void RPbdb_LogSettingsController_turnFlushBeforeReturnFromWriteOff( RPbdb_LogSettingsController* log_settings_controller )	{
		RPbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_DSYNC, FALSE );
		log_settings_controller->flush_before_return_from_write = FALSE;
	}

/*********************
*  autoremoveLogs  *
*********************/

//	DB_LOG_AUTO_REMOVE	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int RPbdb_LogSettingsController_autoremoveLogs( RPbdb_LogSettingsController* log_settings_controller )	{

	log_settings_controller->autoremove = RPbdb_LogSettingsController_internal_config( log_settings_controller, DB_LOG_AUTO_REMOVE );

	if ( log_settings_controller->autoremove == TRUE )	{
		return DB_LOG_AUTO_REMOVE;
	}
	return FALSE;	
}

	/**************************
	*  turnAutoremoveOn  *
	**************************/

	void RPbdb_LogSettingsController_turnAutoremoveLogsOn( RPbdb_LogSettingsController* log_settings_controller )	{
		RPbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_AUTO_REMOVE, TRUE );
		log_settings_controller->autoremove = TRUE;
	}

	/************************
	*  turnAutoremoveOff  *
	************************/

	void RPbdb_LogSettingsController_turnAutoremoveOff( RPbdb_LogSettingsController* log_settings_controller )	{
		RPbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_AUTO_REMOVE, FALSE );
		log_settings_controller->autoremove = FALSE;
	}

/*********************
*  logInMemory  *
*********************/

//	DB_LOG_IN_MEMORY	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int RPbdb_LogSettingsController_logInMemory( RPbdb_LogSettingsController* log_settings_controller )	{

	log_settings_controller->log_in_memory = RPbdb_LogSettingsController_internal_config( log_settings_controller, DB_LOG_IN_MEMORY );
	
	if ( log_settings_controller->log_in_memory == TRUE )	{
		return DB_LOG_IN_MEMORY;
	}
	return FALSE;	
}

	/*************************
	*  turnLogInMemoryOn  *
	*************************/

	void RPbdb_LogSettingsController_turnLogInMemoryOn( RPbdb_LogSettingsController* log_settings_controller )	{
		RPbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_IN_MEMORY, TRUE );
		log_settings_controller->log_in_memory = TRUE;
	}

	/*************************
	*  turnLogInMemoryOff  *
	*************************/

	void RPbdb_LogSettingsController_turnLogInMemoryOff( RPbdb_LogSettingsController* log_settings_controller )	{
		RPbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_IN_MEMORY, FALSE );
		log_settings_controller->log_in_memory = FALSE;
	}

/*********************
*  zeroAtCreation  *
*********************/

//	DB_LOG_ZERO			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int RPbdb_LogSettingsController_zeroAtCreation( RPbdb_LogSettingsController* log_settings_controller )	{

	log_settings_controller->zero_at_creation = RPbdb_LogSettingsController_internal_config( log_settings_controller, DB_LOG_ZERO );

	if ( log_settings_controller->zero_at_creation == TRUE )	{
		return DB_LOG_ZERO;
	}
	return FALSE;	
}

	/*******************************
	*  turnZeroAtCreationOn  *
	*******************************/

	void RPbdb_LogSettingsController_turnZeroAtCreationOn( RPbdb_LogSettingsController* log_settings_controller )	{
		RPbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_ZERO, TRUE );
		log_settings_controller->zero_at_creation = TRUE;
	}

	/*****************************
	*  turnZeroAtCreationOff  *
	*****************************/

	void RPbdb_LogSettingsController_turnZeroAtCreationOff( RPbdb_LogSettingsController* log_settings_controller )	{
		RPbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_ZERO, FALSE );
		log_settings_controller->zero_at_creation = FALSE;
	}

/*********************************
*  forceFlushAfterRecordWrite  *
*********************************/

int RPbdb_LogSettingsController_forceFlushAfterRecordWrite( RPbdb_LogSettingsController* log_settings_controller )	{

	if ( log_settings_controller->force_flush_after_record_write == TRUE )	{
		
		return DB_FLUSH;
	}
	
	return FALSE;
}

	/*****************************************
	*  turnForceFlushAfterRecordWriteOn  *
	*****************************************/

	void RPbdb_LogSettingsController_turnForceFlushAfterRecordWriteOn( RPbdb_LogSettingsController* log_settings_controller )	{
	
		log_settings_controller->force_flush_after_record_write = TRUE;
	}

	/*****************************************
	*  turnForceFlushAfterRecordWriteOff  *
	*****************************************/

	void RPbdb_LogSettingsController_turnForceFlushAfterRecordWriteOff( RPbdb_LogSettingsController* log_settings_controller )	{
	
		log_settings_controller->force_flush_after_record_write = FALSE;
	}

/*****************
*  bufferSize  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lg_bsize.html
uint32_t RPbdb_LogSettingsController_bufferSize( RPbdb_LogSettingsController* log_settings_controller )	{
	
	RPbdb_Environment*		environment;

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

void RPbdb_LogSettingsController_setBufferSize(	RPbdb_LogSettingsController*	log_settings_controller, 
												uint32_t						buffer_size )	{

	RPbdb_Environment*		environment;

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
char* RPbdb_LogSettingsController_directory( RPbdb_LogSettingsController* log_settings_controller )	{

	RPbdb_Environment*		environment;

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

void RPbdb_LogSettingsController_setDirectory(	RPbdb_LogSettingsController*	log_settings_controller, 
												char*							directory )	{

	RPbdb_Environment*		environment;

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
int RPbdb_LogSettingsController_mode( RPbdb_LogSettingsController* log_settings_controller )	{

	RPbdb_Environment*		environment;

	environment = log_settings_controller->parent_settings_controller->parent_environment;

	if (	log_settings_controller->mode == RPBDB_UNITIALIZED
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lg_filemode(	environment->wrapped_bdb_environment, 
										&( log_settings_controller->mode ) );
	}
	return log_settings_controller->mode;
}

/*****************
*  setMode  *
*****************/

void RPbdb_LogSettingsController_setMode(	RPbdb_LogSettingsController*	log_settings_controller, 
											int								mode )	{

	RPbdb_Environment*		environment;

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
int RPbdb_LogSettingsController_maxLogSize( RPbdb_LogSettingsController* log_settings_controller )	{

	RPbdb_Environment*		environment;

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

void RPbdb_LogSettingsController_setMaxLogSize( RPbdb_LogSettingsController* log_settings_controller, uint32_t max_size )	{

	RPbdb_Environment*	environment	= log_settings_controller->parent_settings_controller->parent_environment;

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
int RPbdb_LogSettingsController_maxRegionSize( RPbdb_LogSettingsController* log_settings_controller )	{

	RPbdb_Environment*		environment;

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

void RPbdb_LogSettingsController_setMaxRegionSize( RPbdb_LogSettingsController* log_settings_controller, uint32_t max_region_size )	{

	RPbdb_Environment*		environment = log_settings_controller->parent_settings_controller->parent_environment;

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

BOOL RPbdb_LogSettingsController_internal_config( RPbdb_LogSettingsController* log_settings_controller, uint32_t which_flag )	{

	RPbdb_Environment*		environment	= log_settings_controller->parent_settings_controller->parent_environment;
	int			on_or_off	=	FALSE;
	
	if (	environment->wrapped_bdb_environment != NULL
		&&	RPbdb_LogSettingsController_on( log_settings_controller ) )	{

		environment->wrapped_bdb_environment->log_get_config(	environment->wrapped_bdb_environment, 
																													which_flag, 
																													& on_or_off );
	}
	
	return ( on_or_off ? TRUE : FALSE );
}

/*****************
*  setConfig  *
*****************/

void RPbdb_LogSettingsController_internal_setConfig(	RPbdb_LogSettingsController* log_settings_controller, 
																										uint32_t which_flag, 
																										BOOL on_or_off )	{

	RPbdb_Environment*		environment	= log_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->log_set_config(	environment->wrapped_bdb_environment, 
																													which_flag, 
																													on_or_off );
	}
}

/*****************
*  openFlags  *
*****************/

int RPbdb_LogSettingsController_internal_openFlags( RPbdb_LogSettingsController* log_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RPBDB_NO_FLAGS;
}

/*****************
*  closeFlags  *
*****************/

int RPbdb_LogSettingsController_internal_closeFlags( RPbdb_LogSettingsController* log_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RPBDB_NO_FLAGS;
}

/*************************
*  appendRecordFlags  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_put.html
int RPbdb_LogSettingsController_internal_appendRecordFlags( RPbdb_LogSettingsController* log_settings_controller )	{
	
	return RPbdb_LogSettingsController_forceFlushAfterRecordWrite( log_settings_controller );	
}

/*********************
*  setLogConfig  *
********************/

void RPbdb_LogSettingsController_internal_setLogConfig( RPbdb_LogSettingsController* log_settings_controller )	{
	
	RPbdb_Environment*		environment	= log_settings_controller->parent_settings_controller->parent_environment;
	
	if (	environment->wrapped_bdb_environment != NULL
		&&	environment->is_open )	{
	
		environment->wrapped_bdb_environment->log_set_config(	environment->wrapped_bdb_environment,
																RPbdb_LogSettingsController_disableSystemBuffering( log_settings_controller )
																|	RPbdb_LogSettingsController_flushBeforeReturnFromWrite( log_settings_controller )
																|	RPbdb_LogSettingsController_autoremoveLogs( log_settings_controller )
																|	RPbdb_LogSettingsController_logInMemory( log_settings_controller )
																|	RPbdb_LogSettingsController_zeroAtCreation( log_settings_controller ),
																1	);
	}
}
	
/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_LogSettingsController* RPbdb_LogSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_LogSettingsController* log_settings_controller )	{

	RPbdb_LogSettingsController* log_settings_controller_copy	=	RPbdb_LogSettingsController_new( log_settings_controller->parent_settings_controller );

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

