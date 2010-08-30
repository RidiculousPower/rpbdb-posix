/*
 *		RPDB::SettingsController::ThreadSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_ThreadSettingsController.h"

#include "RPDB_RuntimeStorageController.h"
#include "RPDB_RuntimeStorageController_internal.h"
#include "RPDB_SettingsController.h"
#include "RPDB_Environment.h"
#include "RPDB_MutexSettingsController.h"

#include "RPDB_ThreadSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/
	
RPDB_ThreadSettingsController* RPDB_ThreadSettingsController_new( RPDB_SettingsController* settings_controller )	{

	RPDB_ThreadSettingsController*		thread_settings_controller = calloc( 1, sizeof( RPDB_ThreadSettingsController ) );

	thread_settings_controller->parent_settings_controller = settings_controller;

	return thread_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_ThreadSettingsController_free(	RPDB_ThreadSettingsController** thread_settings_controller )	{

	free( *thread_settings_controller );
	*thread_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_ThreadSettingsController_parentEnvironment(	RPDB_ThreadSettingsController* thread_settings_controller )	{
	return thread_settings_controller->parent_settings_controller->parent_environment;
}

/**********
*  on  *
**********/

//	DB_THREAD		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
int RPDB_ThreadSettingsController_on( RPDB_ThreadSettingsController* thread_settings_controller )	{
	if ( thread_settings_controller->on == TRUE )	{
		return DB_THREAD;
	}
	return FALSE;
}

/************
*  off  *
************/

BOOL RPDB_ThreadSettingsController_off( RPDB_ThreadSettingsController* thread_settings_controller )	{
	if ( thread_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

/****************
*  turnOn  *
****************/

void RPDB_ThreadSettingsController_turnOn( RPDB_ThreadSettingsController* thread_settings_controller )	{
	thread_settings_controller->on = TRUE;
}

/****************
*  turnOff  *
****************/

void RPDB_ThreadSettingsController_turnOff( RPDB_ThreadSettingsController* thread_settings_controller )	{
	thread_settings_controller->on = FALSE;
}

/*********************
*  threadCount  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_thread_count.html
int RPDB_ThreadSettingsController_threadCount( RPDB_ThreadSettingsController* thread_settings_controller )	{

	RPDB_Environment*		environment = thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_thread_count(	environment->wrapped_bdb_environment, 
																&( thread_settings_controller->thread_count ) );
	}

	return thread_settings_controller->thread_count;
}

/**********************
*  setThreadCount  *
**********************/

void RPDB_ThreadSettingsController_setThreadCount(	RPDB_ThreadSettingsController*		thread_settings_controller, 
													uint32_t							thread_count )	{

	RPDB_Environment*		environment = thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_thread_count(	environment->wrapped_bdb_environment, 
																thread_count );
	}
	
	thread_settings_controller->thread_count = thread_count;
}

/************************************************
*  setUniqueThreadIdentifierCallbackMethod  *
************************************************/

void RPDB_ThreadSettingsController_setUniqueThreadIdentifierCallbackMethod(	RPDB_ThreadSettingsController*					thread_settings_controller,
 																				RPDB_UniqueThreadIdentifierCallbackMethod		unique_thread_identifier_callback_method )	{

	RPDB_Environment*	environment	=	thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		if ( unique_thread_identifier_callback_method == NULL )	{
			environment->wrapped_bdb_environment->set_thread_id(	environment->wrapped_bdb_environment,
																	NULL );
		}
		else {			
			environment->wrapped_bdb_environment->set_thread_id(	environment->wrapped_bdb_environment,
																	& RPDB_ThreadSettingsController_internal_uniqueThreadIdentifierCallbackMethod );
		}
	}
	thread_settings_controller->unique_thread_identifier_callback_method = unique_thread_identifier_callback_method;
}

/********************************************
*  uniqueThreadIdentifierCallbackMethod  *
********************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_thread_id.html
RPDB_UniqueThreadIdentifierCallbackMethod RPDB_ThreadSettingsController_uniqueThreadIdentifierCallbackMethod( RPDB_ThreadSettingsController* thread_settings_controller )	{

	return thread_settings_controller->unique_thread_identifier_callback_method;
}

/********************************************************************
*  setFormatThreadAndProcessIdentifierForDisplayCallbackMethod  *
********************************************************************/

void RPDB_ThreadSettingsController_setFormatThreadAndProcessIdentifierForDisplayCallbackMethod(	RPDB_ThreadSettingsController*										thread_settings_controller,
 																									RPDB_FormatThreadAndProcessIdentifierForDisplayCallbackMethod		format_thread_and_process_identifier_for_display_callback_method )	{

	RPDB_Environment*	environment	=	thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_thread_id_string(	environment->wrapped_bdb_environment,
																	& RPDB_ThreadSettingsController_internal_formatThreadAndProcessIdentifierForDisplayCallbackMethod );
	}
	thread_settings_controller->format_thread_and_process_identifier_for_display_callback_method = format_thread_and_process_identifier_for_display_callback_method;
}

/****************************************************************
*  formatThreadAndProcessIdentifierForDisplayCallbackMethod  *
****************************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_thread_id_string.html
RPDB_FormatThreadAndProcessIdentifierForDisplayCallbackMethod RPDB_ThreadSettingsController_formatThreadAndProcessIDForDisplayCallbackMethod(	RPDB_ThreadSettingsController* thread_settings_controller	)	{

	return thread_settings_controller->format_thread_and_process_identifier_for_display_callback_method;
}

/************************************
*  setIsThreadAliveCallbackMethod  *
************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_isalive.html
void RPDB_ThreadSettingsController_setIsThreadAliveCallback(	RPDB_ThreadSettingsController* 	thread_settings_controller,
 																RPDB_IsThreadAliveCallbackMethod		is_thread_alive_callback_method )	{
	
	RPDB_Environment*	environment	=	thread_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_isalive(	environment->wrapped_bdb_environment,
															& RPDB_ThreadSettingsController_internal_isThreadAliveCallbackMethod );
	}
	thread_settings_controller->is_thread_alive_callback_method = is_thread_alive_callback_method;
}

/************************************
*  isThreadAliveCallbackMethod  *
************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_isalive.html
RPDB_IsThreadAliveCallbackMethod RPDB_ThreadSettingsController_isThreadAliveCallbackMethod( RPDB_ThreadSettingsController* thread_settings_controller )	{

	return thread_settings_controller->is_thread_alive_callback_method;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********************************************
*  uniqueThreadIdentifierCallbackMethod  *
********************************************/

void RPDB_ThreadSettingsController_internal_uniqueThreadIdentifierCallbackMethod(	DB_ENV*				bdb_environment,
																					pid_t*				process_id,
																					db_threadid_t*		thread_id	)	{
	
	RPDB_Environment*								environment						=	RPDB_RuntimeStorageController_internal_environmentForBDBEnvironment(	RPDB_RuntimeStorageController_sharedInstance(),
																																								bdb_environment );
	
	RPDB_ThreadSettingsController*		thread_settings_controller		=	RPDB_SettingsController_threadSettingsController( RPDB_Environment_settingsController( environment ) );
	
	thread_settings_controller->unique_thread_identifier_callback_method(	environment,
																			process_id,
																			thread_id );
}

/****************************************************************
*  formatThreadAndProcessIdentifierForDisplayCallbackMethod  *
****************************************************************/

char* RPDB_ThreadSettingsController_internal_formatThreadAndProcessIdentifierForDisplayCallbackMethod(	DB_ENV*			bdb_environment,
																										pid_t			process_id,
																										db_threadid_t	thread_id,
																										char*			string_buffer )	{
	
	RPDB_Environment*								environment						=	RPDB_RuntimeStorageController_internal_environmentForBDBEnvironment(	RPDB_RuntimeStorageController_sharedInstance(),
																																								bdb_environment );

	RPDB_ThreadSettingsController*		thread_settings_controller		=	RPDB_SettingsController_threadSettingsController( RPDB_Environment_settingsController( environment ) );

	return thread_settings_controller->format_thread_and_process_identifier_for_display_callback_method(	environment,
																											process_id,
																											thread_id,
																											string_buffer );
}

/************************************
*  isThreadAliveCallbackMethod  *
************************************/

int RPDB_ThreadSettingsController_internal_isThreadAliveCallbackMethod(	DB_ENV*			bdb_environment,
																			pid_t			process_id,
																			db_threadid_t	thread_id,
																			uint32_t		flags __attribute__((unused)) )	{
	
	RPDB_Environment*		environment		=	RPDB_RuntimeStorageController_internal_environmentForBDBEnvironment(	RPDB_RuntimeStorageController_sharedInstance(),
																														bdb_environment );
	
	RPDB_SettingsController*			settings_controller				=	RPDB_Environment_settingsController( environment );

	RPDB_ThreadSettingsController*		thread_settings_controller		=	RPDB_SettingsController_threadSettingsController( settings_controller );
	BOOL	associated_with_single_process	=	FALSE;
	if ( settings_controller->mutex_settings_controller != NULL )	{
		associated_with_single_process	=	RPDB_MutexSettingsController_associatedWithSingleProcess( settings_controller->mutex_settings_controller );
	}
	return thread_settings_controller->is_thread_alive_callback_method(	environment,
																		process_id,
																		thread_id,
																		associated_with_single_process );
}


/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_ThreadSettingsController* RPDB_ThreadSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_ThreadSettingsController* thread_settings_controller )	{

	RPDB_ThreadSettingsController* thread_settings_controller_copy	=	RPDB_ThreadSettingsController_new( thread_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	thread_settings_controller_copy->thread_count	=	thread_settings_controller->thread_count;
	thread_settings_controller_copy->on	=	thread_settings_controller->on;

	return thread_settings_controller_copy;
}

