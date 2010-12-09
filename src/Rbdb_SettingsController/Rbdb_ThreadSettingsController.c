/*
 *		Rbdb::SettingsController::ThreadSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_ThreadSettingsController.h"

#include "Rbdb_RuntimeStorageController.h"
#include "Rbdb_RuntimeStorageController_internal.h"
#include "Rbdb_SettingsController.h"
#include "Rbdb_Environment.h"
#include "Rbdb_MutexSettingsController.h"

#include "Rbdb_ThreadSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  new  *
************/
	
Rbdb_ThreadSettingsController* Rbdb_ThreadSettingsController_new( Rbdb_SettingsController* settings_controller )	{

	Rbdb_ThreadSettingsController*		thread_settings_controller = calloc( 1, sizeof( Rbdb_ThreadSettingsController ) );

	thread_settings_controller->parent_settings_controller = settings_controller;

	return thread_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_ThreadSettingsController_free(	Rbdb_ThreadSettingsController** thread_settings_controller )	{

	free( *thread_settings_controller );
	*thread_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_ThreadSettingsController_parentEnvironment(	Rbdb_ThreadSettingsController* thread_settings_controller )	{
	return thread_settings_controller->parent_settings_controller->parent_environment;
}

/**********
*  on  *
**********/

//	DB_THREAD		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
int Rbdb_ThreadSettingsController_on( Rbdb_ThreadSettingsController* thread_settings_controller )	{
	if ( thread_settings_controller->on == TRUE )	{
		return DB_THREAD;
	}
	return FALSE;
}

/************
*  off  *
************/

BOOL Rbdb_ThreadSettingsController_off( Rbdb_ThreadSettingsController* thread_settings_controller )	{
	if ( thread_settings_controller->on == FALSE )	{
		return TRUE;
	}
	return FALSE;
}

/****************
*  turnOn  *
****************/

void Rbdb_ThreadSettingsController_turnOn( Rbdb_ThreadSettingsController* thread_settings_controller )	{
	thread_settings_controller->on = TRUE;
}

/****************
*  turnOff  *
****************/

void Rbdb_ThreadSettingsController_turnOff( Rbdb_ThreadSettingsController* thread_settings_controller )	{
	thread_settings_controller->on = FALSE;
}

/*********************
*  threadCount  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_thread_count.html
int Rbdb_ThreadSettingsController_threadCount( Rbdb_ThreadSettingsController* thread_settings_controller )	{

	Rbdb_Environment*		environment = thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_thread_count(	environment->wrapped_bdb_environment, 
																&( thread_settings_controller->thread_count ) );
	}

	return thread_settings_controller->thread_count;
}

/**********************
*  setThreadCount  *
**********************/

void Rbdb_ThreadSettingsController_setThreadCount(	Rbdb_ThreadSettingsController*		thread_settings_controller, 
													uint32_t							thread_count )	{

	Rbdb_Environment*		environment = thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_thread_count(	environment->wrapped_bdb_environment, 
																thread_count );
	}
	
	thread_settings_controller->thread_count = thread_count;
}

/************************************************
*  setUniqueThreadIdentifierCallbackMethod  *
************************************************/

void Rbdb_ThreadSettingsController_setUniqueThreadIdentifierCallbackMethod(	Rbdb_ThreadSettingsController*					thread_settings_controller,
 																				Rbdb_UniqueThreadIdentifierCallbackMethod		unique_thread_identifier_callback_method )	{

	Rbdb_Environment*	environment	=	thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		if ( unique_thread_identifier_callback_method == NULL )	{
			environment->wrapped_bdb_environment->set_thread_id(	environment->wrapped_bdb_environment,
																	NULL );
		}
		else {			
			environment->wrapped_bdb_environment->set_thread_id(	environment->wrapped_bdb_environment,
																	& Rbdb_ThreadSettingsController_internal_uniqueThreadIdentifierCallbackMethod );
		}
	}
	thread_settings_controller->unique_thread_identifier_callback_method = unique_thread_identifier_callback_method;
}

/********************************************
*  uniqueThreadIdentifierCallbackMethod  *
********************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_thread_id.html
Rbdb_UniqueThreadIdentifierCallbackMethod Rbdb_ThreadSettingsController_uniqueThreadIdentifierCallbackMethod( Rbdb_ThreadSettingsController* thread_settings_controller )	{

	return thread_settings_controller->unique_thread_identifier_callback_method;
}

/********************************************************************
*  setFormatThreadAndProcessIdentifierForDisplayCallbackMethod  *
********************************************************************/

void Rbdb_ThreadSettingsController_setFormatThreadAndProcessIdentifierForDisplayCallbackMethod(	Rbdb_ThreadSettingsController*										thread_settings_controller,
 																									Rbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod		format_thread_and_process_identifier_for_display_callback_method )	{

	Rbdb_Environment*	environment	=	thread_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_thread_id_string(	environment->wrapped_bdb_environment,
																	& Rbdb_ThreadSettingsController_internal_formatThreadAndProcessIdentifierForDisplayCallbackMethod );
	}
	thread_settings_controller->format_thread_and_process_identifier_for_display_callback_method = format_thread_and_process_identifier_for_display_callback_method;
}

/****************************************************************
*  formatThreadAndProcessIdentifierForDisplayCallbackMethod  *
****************************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_thread_id_string.html
Rbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod Rbdb_ThreadSettingsController_formatThreadAndProcessIDForDisplayCallbackMethod(	Rbdb_ThreadSettingsController* thread_settings_controller	)	{

	return thread_settings_controller->format_thread_and_process_identifier_for_display_callback_method;
}

/************************************
*  setIsThreadAliveCallbackMethod  *
************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_isalive.html
void Rbdb_ThreadSettingsController_setIsThreadAliveCallback(	Rbdb_ThreadSettingsController* 	thread_settings_controller,
 																Rbdb_IsThreadAliveCallbackMethod		is_thread_alive_callback_method )	{
	
	Rbdb_Environment*	environment	=	thread_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_isalive(	environment->wrapped_bdb_environment,
															& Rbdb_ThreadSettingsController_internal_isThreadAliveCallbackMethod );
	}
	thread_settings_controller->is_thread_alive_callback_method = is_thread_alive_callback_method;
}

/************************************
*  isThreadAliveCallbackMethod  *
************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_isalive.html
Rbdb_IsThreadAliveCallbackMethod Rbdb_ThreadSettingsController_isThreadAliveCallbackMethod( Rbdb_ThreadSettingsController* thread_settings_controller )	{

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

void Rbdb_ThreadSettingsController_internal_uniqueThreadIdentifierCallbackMethod(	DB_ENV*				bdb_environment,
																					pid_t*				process_id,
																					db_threadid_t*		thread_id	)	{
	
	Rbdb_Environment*								environment						=	Rbdb_RuntimeStorageController_internal_environmentForBDBEnvironment(	Rbdb_RuntimeStorageController_sharedInstance(),
																																								bdb_environment );
	
	Rbdb_ThreadSettingsController*		thread_settings_controller		=	Rbdb_SettingsController_threadSettingsController( Rbdb_Environment_settingsController( environment ) );
	
	thread_settings_controller->unique_thread_identifier_callback_method(	environment,
																			process_id,
																			thread_id );
}

/****************************************************************
*  formatThreadAndProcessIdentifierForDisplayCallbackMethod  *
****************************************************************/

char* Rbdb_ThreadSettingsController_internal_formatThreadAndProcessIdentifierForDisplayCallbackMethod(	DB_ENV*			bdb_environment,
																										pid_t			process_id,
																										db_threadid_t	thread_id,
																										char*			string_buffer )	{
	
	Rbdb_Environment*								environment						=	Rbdb_RuntimeStorageController_internal_environmentForBDBEnvironment(	Rbdb_RuntimeStorageController_sharedInstance(),
																																								bdb_environment );

	Rbdb_ThreadSettingsController*		thread_settings_controller		=	Rbdb_SettingsController_threadSettingsController( Rbdb_Environment_settingsController( environment ) );

	return thread_settings_controller->format_thread_and_process_identifier_for_display_callback_method(	environment,
																											process_id,
																											thread_id,
																											string_buffer );
}

/************************************
*  isThreadAliveCallbackMethod  *
************************************/

int Rbdb_ThreadSettingsController_internal_isThreadAliveCallbackMethod(	DB_ENV*			bdb_environment,
																			pid_t			process_id,
																			db_threadid_t	thread_id,
																			uint32_t		flags __attribute__((unused)) )	{
	
	Rbdb_Environment*		environment		=	Rbdb_RuntimeStorageController_internal_environmentForBDBEnvironment(	Rbdb_RuntimeStorageController_sharedInstance(),
																														bdb_environment );
	
	Rbdb_SettingsController*			settings_controller				=	Rbdb_Environment_settingsController( environment );

	Rbdb_ThreadSettingsController*		thread_settings_controller		=	Rbdb_SettingsController_threadSettingsController( settings_controller );
	BOOL	associated_with_single_process	=	FALSE;
	if ( settings_controller->mutex_settings_controller != NULL )	{
		associated_with_single_process	=	Rbdb_MutexSettingsController_associatedWithSingleProcess( settings_controller->mutex_settings_controller );
	}
	return thread_settings_controller->is_thread_alive_callback_method(	environment,
																		process_id,
																		thread_id,
																		associated_with_single_process );
}


/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_ThreadSettingsController* Rbdb_ThreadSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_ThreadSettingsController* thread_settings_controller )	{

	Rbdb_ThreadSettingsController* thread_settings_controller_copy	=	Rbdb_ThreadSettingsController_new( thread_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	thread_settings_controller_copy->thread_count	=	thread_settings_controller->thread_count;
	thread_settings_controller_copy->on	=	thread_settings_controller->on;

	return thread_settings_controller_copy;
}

