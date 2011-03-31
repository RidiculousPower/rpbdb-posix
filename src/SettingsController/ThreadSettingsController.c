/*
 *		RPbdb::SettingsController::ThreadSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "ThreadSettingsController.h"

#include "RuntimeStorageController.h"
#include "RuntimeStorageController_internal.h"
#include "SettingsController.h"
#include "Environment.h"
#include "MutexSettingsController.h"

#include "ThreadSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/
	
RPbdb_ThreadSettingsController* RPbdb_ThreadSettingsController_new( RPbdb_SettingsController* settings_controller )	{

	RPbdb_ThreadSettingsController*		thread_settings_controller = calloc( 1, sizeof( RPbdb_ThreadSettingsController ) );

	thread_settings_controller->parent_settings_controller = settings_controller;

	return thread_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_ThreadSettingsController_free(	RPbdb_ThreadSettingsController** thread_settings_controller )	{

	free( *thread_settings_controller );
	*thread_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_ThreadSettingsController_parentEnvironment(	RPbdb_ThreadSettingsController* thread_settings_controller )	{
	return thread_settings_controller->parent_settings_controller->parent_environment;
}

/**********
*  on  *
**********/

//	DB_THREAD		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
int RPbdb_ThreadSettingsController_on( RPbdb_ThreadSettingsController* thread_settings_controller )	{
	if ( thread_settings_controller->on == TRUE )	{
		return DB_THREAD;
	}
	return FALSE;
}

/************
*  off  *
************/

BOOL RPbdb_ThreadSettingsController_off( RPbdb_ThreadSettingsController* thread_settings_controller )	{
	if ( thread_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

/****************
*  turnOn  *
****************/

void RPbdb_ThreadSettingsController_turnOn( RPbdb_ThreadSettingsController* thread_settings_controller )	{
	thread_settings_controller->on = TRUE;
}

/****************
*  turnOff  *
****************/

void RPbdb_ThreadSettingsController_turnOff( RPbdb_ThreadSettingsController* thread_settings_controller )	{
	thread_settings_controller->on = FALSE;
}

/*********************
*  threadCount  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_thread_count.html
int RPbdb_ThreadSettingsController_threadCount( RPbdb_ThreadSettingsController* thread_settings_controller )	{

	RPbdb_Environment*		environment = thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_thread_count(	environment->wrapped_bdb_environment, 
																&( thread_settings_controller->thread_count ) );
	}

	return thread_settings_controller->thread_count;
}

/**********************
*  setThreadCount  *
**********************/

void RPbdb_ThreadSettingsController_setThreadCount(	RPbdb_ThreadSettingsController*		thread_settings_controller, 
													uint32_t							thread_count )	{

	RPbdb_Environment*		environment = thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_thread_count(	environment->wrapped_bdb_environment, 
																thread_count );
	}
	
	thread_settings_controller->thread_count = thread_count;
}

/************************************************
*  setUniqueThreadIdentifierCallbackMethod  *
************************************************/

void RPbdb_ThreadSettingsController_setUniqueThreadIdentifierCallbackMethod(	RPbdb_ThreadSettingsController*					thread_settings_controller,
 																				RPbdb_UniqueThreadIdentifierCallbackMethod		unique_thread_identifier_callback_method )	{

	RPbdb_Environment*	environment	=	thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		if ( unique_thread_identifier_callback_method == NULL )	{
			environment->wrapped_bdb_environment->set_thread_id(	environment->wrapped_bdb_environment,
																	NULL );
		}
		else {			
			environment->wrapped_bdb_environment->set_thread_id(	environment->wrapped_bdb_environment,
																	& RPbdb_ThreadSettingsController_internal_uniqueThreadIdentifierCallbackMethod );
		}
	}
	thread_settings_controller->unique_thread_identifier_callback_method = unique_thread_identifier_callback_method;
}

/********************************************
*  uniqueThreadIdentifierCallbackMethod  *
********************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_thread_id.html
RPbdb_UniqueThreadIdentifierCallbackMethod RPbdb_ThreadSettingsController_uniqueThreadIdentifierCallbackMethod( RPbdb_ThreadSettingsController* thread_settings_controller )	{

	return thread_settings_controller->unique_thread_identifier_callback_method;
}

/********************************************************************
*  setFormatThreadAndProcessIdentifierForDisplayCallbackMethod  *
********************************************************************/

void RPbdb_ThreadSettingsController_setFormatThreadAndProcessIdentifierForDisplayCallbackMethod(	RPbdb_ThreadSettingsController*										thread_settings_controller,
 																									RPbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod		format_thread_and_process_identifier_for_display_callback_method )	{

	RPbdb_Environment*	environment	=	thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_thread_id_string(	environment->wrapped_bdb_environment,
																	& RPbdb_ThreadSettingsController_internal_formatThreadAndProcessIdentifierForDisplayCallbackMethod );
	}
	thread_settings_controller->format_thread_and_process_identifier_for_display_callback_method = format_thread_and_process_identifier_for_display_callback_method;
}

/****************************************************************
*  formatThreadAndProcessIdentifierForDisplayCallbackMethod  *
****************************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_thread_id_string.html
RPbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod RPbdb_ThreadSettingsController_formatThreadAndProcessIDForDisplayCallbackMethod(	RPbdb_ThreadSettingsController* thread_settings_controller	)	{

	return thread_settings_controller->format_thread_and_process_identifier_for_display_callback_method;
}

/************************************
*  setIsThreadAliveCallbackMethod  *
************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_isalive.html
void RPbdb_ThreadSettingsController_setIsThreadAliveCallback(	RPbdb_ThreadSettingsController* 	thread_settings_controller,
 																RPbdb_IsThreadAliveCallbackMethod		is_thread_alive_callback_method )	{
	
	RPbdb_Environment*	environment	=	thread_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_isalive(	environment->wrapped_bdb_environment,
															& RPbdb_ThreadSettingsController_internal_isThreadAliveCallbackMethod );
	}
	thread_settings_controller->is_thread_alive_callback_method = is_thread_alive_callback_method;
}

/************************************
*  isThreadAliveCallbackMethod  *
************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_isalive.html
RPbdb_IsThreadAliveCallbackMethod RPbdb_ThreadSettingsController_isThreadAliveCallbackMethod( RPbdb_ThreadSettingsController* thread_settings_controller )	{

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

void RPbdb_ThreadSettingsController_internal_uniqueThreadIdentifierCallbackMethod(	DB_ENV*				bdb_environment,
																					pid_t*				process_id,
																					db_threadid_t*		thread_id	)	{
	
	RPbdb_Environment*								environment						=	RPbdb_RuntimeStorageController_internal_environmentForBDBEnvironment(	RPbdb_RuntimeStorageController_sharedInstance(),
																																								bdb_environment );
	
	RPbdb_ThreadSettingsController*		thread_settings_controller		=	RPbdb_SettingsController_threadSettingsController( RPbdb_Environment_settingsController( environment ) );
	
	thread_settings_controller->unique_thread_identifier_callback_method(	environment,
																			process_id,
																			thread_id );
}

/****************************************************************
*  formatThreadAndProcessIdentifierForDisplayCallbackMethod  *
****************************************************************/

char* RPbdb_ThreadSettingsController_internal_formatThreadAndProcessIdentifierForDisplayCallbackMethod(	DB_ENV*			bdb_environment,
																										pid_t			process_id,
																										db_threadid_t	thread_id,
																										char*			string_buffer )	{
	
	RPbdb_Environment*								environment						=	RPbdb_RuntimeStorageController_internal_environmentForBDBEnvironment(	RPbdb_RuntimeStorageController_sharedInstance(),
																																								bdb_environment );

	RPbdb_ThreadSettingsController*		thread_settings_controller		=	RPbdb_SettingsController_threadSettingsController( RPbdb_Environment_settingsController( environment ) );

	return thread_settings_controller->format_thread_and_process_identifier_for_display_callback_method(	environment,
																											process_id,
																											thread_id,
																											string_buffer );
}

/************************************
*  isThreadAliveCallbackMethod  *
************************************/

int RPbdb_ThreadSettingsController_internal_isThreadAliveCallbackMethod(	DB_ENV*			bdb_environment,
																			pid_t			process_id,
																			db_threadid_t	thread_id,
																			uint32_t		flags __attribute__((unused)) )	{
	
	RPbdb_Environment*		environment		=	RPbdb_RuntimeStorageController_internal_environmentForBDBEnvironment(	RPbdb_RuntimeStorageController_sharedInstance(),
																														bdb_environment );
	
	RPbdb_SettingsController*			settings_controller				=	RPbdb_Environment_settingsController( environment );

	RPbdb_ThreadSettingsController*		thread_settings_controller		=	RPbdb_SettingsController_threadSettingsController( settings_controller );
	BOOL	associated_with_single_process	=	FALSE;
	if ( settings_controller->mutex_settings_controller != NULL )	{
		associated_with_single_process	=	RPbdb_MutexSettingsController_associatedWithSingleProcess( settings_controller->mutex_settings_controller );
	}
	return thread_settings_controller->is_thread_alive_callback_method(	environment,
																		process_id,
																		thread_id,
																		associated_with_single_process );
}


/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_ThreadSettingsController* RPbdb_ThreadSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_ThreadSettingsController* thread_settings_controller )	{

	RPbdb_ThreadSettingsController* thread_settings_controller_copy	=	RPbdb_ThreadSettingsController_new( thread_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	thread_settings_controller_copy->thread_count	=	thread_settings_controller->thread_count;
	thread_settings_controller_copy->on	=	thread_settings_controller->on;

	return thread_settings_controller_copy;
}

