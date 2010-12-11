/*
 *		Rbdb::SettingsController::LogSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_LogSettingsController.h"

#include "Rbdb_LogCursor.h"
#include "Rbdb_Environment.h"

#include "Rbdb_LogSettingsController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_LogSettingsController* Rbdb_LogSettingsController_new( Rbdb_SettingsController* parent_settings_controller )	{
	
	Rbdb_LogSettingsController*		log_settings_controller = calloc( 1, sizeof( Rbdb_LogSettingsController ) );

	log_settings_controller->parent_settings_controller = parent_settings_controller;

	return log_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_LogSettingsController_free(	Rbdb_LogSettingsController** log_settings_controller )	{

	free( *log_settings_controller );
	*log_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_LogSettingsController_parentEnvironment(	Rbdb_LogSettingsController* log_settings_controller )	{
	return log_settings_controller->parent_settings_controller->parent_environment;
}

/***********
*  on  *
***********/

//	DB_INIT_LOG			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int Rbdb_LogSettingsController_on( Rbdb_LogSettingsController* log_settings_controller )	{

	if ( log_settings_controller->on == TRUE )	{
		return DB_INIT_LOG;
	}
	return FALSE;
}

	/**************
	*  turnOn  *
	**************/

	void Rbdb_LogSettingsController_turnOn( Rbdb_LogSettingsController* log_settings_controller )	{
		log_settings_controller->on = TRUE;
	}

/*************
*  off  *
*************/

BOOL Rbdb_LogSettingsController_off( Rbdb_LogSettingsController* log_settings_controller )	{

	if ( log_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

	/*****************
	*  turnOff  *
	*****************/

	void Rbdb_LogSettingsController_turnOff( Rbdb_LogSettingsController* log_settings_controller )	{
		log_settings_controller->on = FALSE;
	}

/*****************
*  buffering  *
*****************/

//	DB_LOG_DIRECT		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
//	Inverted from BDB Default
int Rbdb_LogSettingsController_disableSystemBuffering( Rbdb_LogSettingsController* log_settings_controller )	{
	//	Since the default is inverted from how we want to describe it, we want to return the setting if FALSE
	log_settings_controller->disable_system_buffering = Rbdb_LogSettingsController_internal_config( log_settings_controller, DB_LOG_DIRECT );
	if ( log_settings_controller->disable_system_buffering == TRUE )	{
		return DB_LOG_DIRECT;
	}
	return FALSE;
}

	/*************************
	*  turnBufferingOn  *
	*************************/

	void Rbdb_LogSettingsController_turnDisableSystemBufferingOn( Rbdb_LogSettingsController* log_settings_controller )	{
	
		Rbdb_LogSettingsController_internal_setConfig(	log_settings_controller, 
																										DB_LOG_DIRECT, 
																										TRUE );
		log_settings_controller->disable_system_buffering = TRUE;
	}

	/*************************
	*  turnBufferingOff  *
	*************************/

	void Rbdb_LogSettingsController_turnDisableSystemBufferingOff( Rbdb_LogSettingsController* log_settings_controller )	{
		Rbdb_LogSettingsController_internal_setConfig(	log_settings_controller, 
																										DB_LOG_DIRECT, 
																										FALSE );
		log_settings_controller->disable_system_buffering = FALSE;
	}

/*********************************
*  flushBeforeReturnFromWrite  *
*********************************/

//	DB_LOG_DSYNC		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int Rbdb_LogSettingsController_flushBeforeReturnFromWrite( Rbdb_LogSettingsController* log_settings_controller )	{

	log_settings_controller->flush_before_return_from_write = Rbdb_LogSettingsController_internal_config( log_settings_controller, DB_LOG_DSYNC );

	if ( log_settings_controller->flush_before_return_from_write == TRUE )	{
		return DB_LOG_DSYNC;
	}
	return FALSE;	
}

	/*****************************************
	*  turnFlushBeforeReturnFromWriteOn  *
	*****************************************/

	void Rbdb_LogSettingsController_turnFlushBeforeReturnFromWriteOn( Rbdb_LogSettingsController* log_settings_controller )	{
		Rbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_DSYNC, TRUE );
		log_settings_controller->flush_before_return_from_write = TRUE;
	}

	/*****************************************
	*  turnFlushBeforeReturnFromWriteOff  *
	*****************************************/

	void Rbdb_LogSettingsController_turnFlushBeforeReturnFromWriteOff( Rbdb_LogSettingsController* log_settings_controller )	{
		Rbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_DSYNC, FALSE );
		log_settings_controller->flush_before_return_from_write = FALSE;
	}

/*********************
*  autoremoveLogs  *
*********************/

//	DB_LOG_AUTO_REMOVE	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int Rbdb_LogSettingsController_autoremoveLogs( Rbdb_LogSettingsController* log_settings_controller )	{

	log_settings_controller->autoremove = Rbdb_LogSettingsController_internal_config( log_settings_controller, DB_LOG_AUTO_REMOVE );

	if ( log_settings_controller->autoremove == TRUE )	{
		return DB_LOG_AUTO_REMOVE;
	}
	return FALSE;	
}

	/**************************
	*  turnAutoremoveOn  *
	**************************/

	void Rbdb_LogSettingsController_turnAutoremoveLogsOn( Rbdb_LogSettingsController* log_settings_controller )	{
		Rbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_AUTO_REMOVE, TRUE );
		log_settings_controller->autoremove = TRUE;
	}

	/************************
	*  turnAutoremoveOff  *
	************************/

	void Rbdb_LogSettingsController_turnAutoremoveOff( Rbdb_LogSettingsController* log_settings_controller )	{
		Rbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_AUTO_REMOVE, FALSE );
		log_settings_controller->autoremove = FALSE;
	}

/*********************
*  logInMemory  *
*********************/

//	DB_LOG_IN_MEMORY	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int Rbdb_LogSettingsController_logInMemory( Rbdb_LogSettingsController* log_settings_controller )	{

	log_settings_controller->log_in_memory = Rbdb_LogSettingsController_internal_config( log_settings_controller, DB_LOG_IN_MEMORY );
	
	if ( log_settings_controller->log_in_memory == TRUE )	{
		return DB_LOG_IN_MEMORY;
	}
	return FALSE;	
}

	/*************************
	*  turnLogInMemoryOn  *
	*************************/

	void Rbdb_LogSettingsController_turnLogInMemoryOn( Rbdb_LogSettingsController* log_settings_controller )	{
		Rbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_IN_MEMORY, TRUE );
		log_settings_controller->log_in_memory = TRUE;
	}

	/*************************
	*  turnLogInMemoryOff  *
	*************************/

	void Rbdb_LogSettingsController_turnLogInMemoryOff( Rbdb_LogSettingsController* log_settings_controller )	{
		Rbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_IN_MEMORY, FALSE );
		log_settings_controller->log_in_memory = FALSE;
	}

/*********************
*  zeroAtCreation  *
*********************/

//	DB_LOG_ZERO			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_log_set_config.html
int Rbdb_LogSettingsController_zeroAtCreation( Rbdb_LogSettingsController* log_settings_controller )	{

	log_settings_controller->zero_at_creation = Rbdb_LogSettingsController_internal_config( log_settings_controller, DB_LOG_ZERO );

	if ( log_settings_controller->zero_at_creation == TRUE )	{
		return DB_LOG_ZERO;
	}
	return FALSE;	
}

	/*******************************
	*  turnZeroAtCreationOn  *
	*******************************/

	void Rbdb_LogSettingsController_turnZeroAtCreationOn( Rbdb_LogSettingsController* log_settings_controller )	{
		Rbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_ZERO, TRUE );
		log_settings_controller->zero_at_creation = TRUE;
	}

	/*****************************
	*  turnZeroAtCreationOff  *
	*****************************/

	void Rbdb_LogSettingsController_turnZeroAtCreationOff( Rbdb_LogSettingsController* log_settings_controller )	{
		Rbdb_LogSettingsController_internal_setConfig( log_settings_controller, DB_LOG_ZERO, FALSE );
		log_settings_controller->zero_at_creation = FALSE;
	}

/*********************************
*  forceFlushAfterRecordWrite  *
*********************************/

int Rbdb_LogSettingsController_forceFlushAfterRecordWrite( Rbdb_LogSettingsController* log_settings_controller )	{

	if ( log_settings_controller->force_flush_after_record_write == TRUE )	{
		
		return DB_FLUSH;
	}
	
	return FALSE;
}

	/*****************************************
	*  turnForceFlushAfterRecordWriteOn  *
	*****************************************/

	void Rbdb_LogSettingsController_turnForceFlushAfterRecordWriteOn( Rbdb_LogSettingsController* log_settings_controller )	{
	
		log_settings_controller->force_flush_after_record_write = TRUE;
	}

	/*****************************************
	*  turnForceFlushAfterRecordWriteOff  *
	*****************************************/

	void Rbdb_LogSettingsController_turnForceFlushAfterRecordWriteOff( Rbdb_LogSettingsController* log_settings_controller )	{
	
		log_settings_controller->force_flush_after_record_write = FALSE;
	}

/*****************
*  bufferSize  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_lg_bsize.html
uint32_t Rbdb_LogSettingsController_bufferSize( Rbdb_LogSettingsController* log_settings_controller )	{
	
	Rbdb_Environment*		environment;

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

void Rbdb_LogSettingsController_setBufferSize(	Rbdb_LogSettingsController*	log_settings_controller, 
												uint32_t						buffer_size )	{

	Rbdb_Environment*		environment;

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
char* Rbdb_LogSettingsController_directory( Rbdb_LogSettingsController* log_settings_controller )	{

	Rbdb_Environment*		environment;

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

void Rbdb_LogSettingsController_setDirectory(	Rbdb_LogSettingsController*	log_settings_controller, 
												char*							directory )	{

	Rbdb_Environment*		environment;

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
int Rbdb_LogSettingsController_mode( Rbdb_LogSettingsController* log_settings_controller )	{

	Rbdb_Environment*		environment;

	environment = log_settings_controller->parent_settings_controller->parent_environment;

	if (	log_settings_controller->mode == RBDB_UNITIALIZED
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_lg_filemode(	environment->wrapped_bdb_environment, 
										&( log_settings_controller->mode ) );
	}
	return log_settings_controller->mode;
}

/*****************
*  setMode  *
*****************/

void Rbdb_LogSettingsController_setMode(	Rbdb_LogSettingsController*	log_settings_controller, 
											int								mode )	{

	Rbdb_Environment*		environment;

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
int Rbdb_LogSettingsController_maxLogSize( Rbdb_LogSettingsController* log_settings_controller )	{

	Rbdb_Environment*		environment;

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

void Rbdb_LogSettingsController_setMaxLogSize( Rbdb_LogSettingsController* log_settings_controller, uint32_t max_size )	{

	Rbdb_Environment*	environment	= log_settings_controller->parent_settings_controller->parent_environment;

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
int Rbdb_LogSettingsController_maxRegionSize( Rbdb_LogSettingsController* log_settings_controller )	{

	Rbdb_Environment*		environment;

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

void Rbdb_LogSettingsController_setMaxRegionSize( Rbdb_LogSettingsController* log_settings_controller, uint32_t max_region_size )	{

	Rbdb_Environment*		environment = log_settings_controller->parent_settings_controller->parent_environment;

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

BOOL Rbdb_LogSettingsController_internal_config( Rbdb_LogSettingsController* log_settings_controller, uint32_t which_flag )	{

	Rbdb_Environment*		environment	= log_settings_controller->parent_settings_controller->parent_environment;
	int			on_or_off	=	FALSE;
	
	if (	environment->wrapped_bdb_environment != NULL
		&&	Rbdb_LogSettingsController_on( log_settings_controller ) )	{

		environment->wrapped_bdb_environment->log_get_config(	environment->wrapped_bdb_environment, 
																													which_flag, 
																													& on_or_off );
	}
	
	return ( on_or_off ? TRUE : FALSE );
}

/*****************
*  setConfig  *
*****************/

void Rbdb_LogSettingsController_internal_setConfig(	Rbdb_LogSettingsController* log_settings_controller, 
																										uint32_t which_flag, 
																										BOOL on_or_off )	{

	Rbdb_Environment*		environment	= log_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->log_set_config(	environment->wrapped_bdb_environment, 
																													which_flag, 
																													on_or_off );
	}
}

/*****************
*  openFlags  *
*****************/

int Rbdb_LogSettingsController_internal_openFlags( Rbdb_LogSettingsController* log_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RBDB_NO_FLAGS;
}

/*****************
*  closeFlags  *
*****************/

int Rbdb_LogSettingsController_internal_closeFlags( Rbdb_LogSettingsController* log_settings_controller __attribute__((unused)) )	{

	//	Currently unused - returns 0
	return RBDB_NO_FLAGS;
}

/*************************
*  appendRecordFlags  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/log_put.html
int Rbdb_LogSettingsController_internal_appendRecordFlags( Rbdb_LogSettingsController* log_settings_controller )	{
	
	return Rbdb_LogSettingsController_forceFlushAfterRecordWrite( log_settings_controller );	
}

/*********************
*  setLogConfig  *
********************/

void Rbdb_LogSettingsController_internal_setLogConfig( Rbdb_LogSettingsController* log_settings_controller )	{
	
	Rbdb_Environment*		environment	= log_settings_controller->parent_settings_controller->parent_environment;
	
	if (	environment->wrapped_bdb_environment != NULL
		&&	environment->is_open )	{
	
		environment->wrapped_bdb_environment->log_set_config(	environment->wrapped_bdb_environment,
																Rbdb_LogSettingsController_disableSystemBuffering( log_settings_controller )
																|	Rbdb_LogSettingsController_flushBeforeReturnFromWrite( log_settings_controller )
																|	Rbdb_LogSettingsController_autoremoveLogs( log_settings_controller )
																|	Rbdb_LogSettingsController_logInMemory( log_settings_controller )
																|	Rbdb_LogSettingsController_zeroAtCreation( log_settings_controller ),
																1	);
	}
}
	
/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_LogSettingsController* Rbdb_LogSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_LogSettingsController* log_settings_controller )	{

	Rbdb_LogSettingsController* log_settings_controller_copy	=	Rbdb_LogSettingsController_new( log_settings_controller->parent_settings_controller );

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

