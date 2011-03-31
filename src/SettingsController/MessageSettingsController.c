/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MessageSettingsController.h"

#include "ErrorController.h"
#include "RuntimeStorageController.h"
#include "SettingsController.h"
#include "Environment.h"

#include "MessageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_MessageSettingsController* RPbdb_MessageSettingsController_new( RPbdb_SettingsController* settings_controller )	{
	
	RPbdb_MessageSettingsController*		message_settings_controller = calloc( 1, sizeof( RPbdb_MessageSettingsController ) );

	message_settings_controller->parent_settings_controller = settings_controller;
	
	return message_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_MessageSettingsController_free(	RPbdb_MessageSettingsController** message_settings_controller )	{

	//	Make sure file is open so we don't close a closed file.
	if ( ( *message_settings_controller )->message_file_is_open )	{

		fclose( ( *message_settings_controller )->message_file );
		( *message_settings_controller )->message_file_is_open	=	FALSE;
		( *message_settings_controller )->message_file			=	NULL;
	}

	free( *message_settings_controller );
	*message_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MessageSettingsController_parentEnvironment(	RPbdb_MessageSettingsController* message_settings_controller )	{
	return message_settings_controller->parent_settings_controller->parent_environment;
}

/*************
*  file  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_msgfile.html
FILE* RPbdb_MessageSettingsController_file( RPbdb_MessageSettingsController* message_settings_controller )	{

	RPbdb_Environment*		environment	= message_settings_controller->parent_settings_controller->parent_environment;
	FILE*		message_file;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_msgfile(	environment->wrapped_bdb_environment,
															& message_file );
	}
	
	//	Store for access
	message_settings_controller->message_file = message_file;

	return message_file;
}

/*****************
*  setFile  *
*****************/

void RPbdb_MessageSettingsController_setFile( RPbdb_MessageSettingsController* message_settings_controller, FILE* message_file )	{

	RPbdb_Environment*		environment	= message_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_msgfile(	environment->wrapped_bdb_environment, 
															message_file );
	}
	
	message_settings_controller->message_file = message_file;
}

/*************************
*  setFileFromPath  *
*************************/

int RPbdb_MessageSettingsController_setFileFromPath( RPbdb_MessageSettingsController* message_settings_controller, char* message_file_path )	{

	FILE*		message_file;
	
	message_file = fopen( message_file_path, "w");
	
	if ( message_file == NULL )	{
		RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController( message_settings_controller->parent_settings_controller->parent_environment ),
											-1,
											"MessageSettingsController_file",
											"Could not open file at path." );
		return 1;
	}
	
	RPbdb_MessageSettingsController_setFile(	message_settings_controller, 
												message_file );

	//	Don't we need to close this name at some point?
	
	return FALSE;
}

/*************************
*  setMessageCallback  *
*************************/
/*
void RPbdb_MessageSettingsController_setMessageCallbackMethod(	RPbdb_MessageSettingsController*					message_settings_controller, 
																void (*message_callback_method)(	RPbdb_Environment*			environment, 
																									const char*		message ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;

	//	Set the BDB message callback function to our private function; our private function will then pass on to the passed function pointer
	//	If we have a callback function, set it; otherwise, unset callback function (NULL function)
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->set_msgcall(	environment, 
									( message_settings_controller->message_callback == NULL ?
										NULL :
										& RPbdb_MessageSettingsController_internal_messageCallback ) );
	}
	
	message_settings_controller->message_callback = callback;	
}
*/
/*************************
*  messageCallback  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_msgcall.html
void (*message_callback_method)(	RPbdb_Environment*			environment, 
									const char*		message ) RPbdb_MessageSettingsController_messageCallbackMethod( RPbdb_MessageSettingsController* message_settings_controller )	{
	return message_settings_controller->message_callback;
}
*/


/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************************
*  messageCallback  *
*************************/
	/*
void RPbdb_MessageSettingsController_internal_messageCallbackMethod(	const DB_ENV*	bdb_environment, 
																		const char*		message )	{

	RPbdb_Environment*								environment					=	RPbdb_RuntimeStorageController_environmentForBDBEnvironment( bdb_environment );
	
	RPbdb_MessageSettingsController*	message_settings_controller	=	RPbdb_SettingsController_messageSettingsController(
																			RPbdb_Environment_settingsController( environment ) );
	
	*( message_settings_controller->message_callback_method )(	environment,
																message );
}
*/
/*********************
*  eventCallback  *
*********************/
/*
//	This callback is called if any internal callbacks are defined. 
void RPbdb_MessageSettingsController_internal_eventCallbackMethod(	DB_ENV*			environment, 
																	uint32_t		event, 
																	void*			event_info )	{
	
	switch ( event )	{
		
		//	Panic occuring
		case DB_EVENT_PANIC:
			if ( message_settings_controller->panic_callback_method != NULL )	{
				*( message_settings_controller->panic_callback_method )(	environment );
			}
			break;
		
		//	Site is now replication client
		case DB_EVENT_REP_CLIENT:
			if ( message_settings_controller->site_is_now_replication_client_callback_method != NULL )	{
				*( message_settings_controller->site_is_now_replication_client_callback_method )(	environment );
			}
			break;
		
		//	This site won replication election
		case DB_EVENT_REP_ELECTED:
			if ( message_settings_controller->site_won_replication_election_callback_method != NULL )	{
				*( message_settings_controller->site_won_replication_election_callback_method )(	environment );
			}
			break;
		
		//	Local site is now master site of replication group
		case DB_EVENT_REP_MASTER:
			if ( message_settings_controller->site_is_now_master_of_replication_group_callback_method != NULL )	{
				*( message_settings_controller->site_is_now_master_of_replication_group_callback_method )(	environment );
			}
			break;
		
		//	Replication group has new master (not local site)
		case DB_EVENT_REP_NEWMASTER:
			if ( message_settings_controller->replication_group_has_new_master_callback_method != NULL )	{
				//	 The event_info parameter points to an integer containing the environment ID of the new master.
				*( message_settings_controller->replication_group_has_new_master_callback_method )(	environment,
																									event_info );
			}
			break;
		
		//	Acknowledgement failed - no durability for replication transactions
		case DB_EVENT_REP_PERM_FAILED:
			if ( message_settings_controller->replication_acknowledgement_failed_callback_method != NULL )	{
				*( message_settings_controller->replication_acknowledgement_failed_callback_method )(	environment );
			}
			break;
		
		//	Startup sync, processing live log records from master
		case DB_EVENT_REP_STARTUPDONE:
			if ( message_settings_controller->replication_startup_completed_callback_method != NULL )	{
				*( message_settings_controller->replication_startup_completed_callback_method )(	environment );
			}
			break;
		
		//	A Write Failed
		case DB_EVENT_WRITE_FAILED:
			if ( message_settings_controller->write_failed_callback_method != NULL )	{
				*( message_settings_controller->write_failed_callback_method )(	environment );
			}
			break;
		
	}
}
*/	

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_MessageSettingsController* RPbdb_MessageSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MessageSettingsController* message_settings_controller )	{

	RPbdb_MessageSettingsController* message_settings_controller_copy	=	RPbdb_MessageSettingsController_new( message_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	message_settings_controller_copy->message_file_is_open	=	message_settings_controller->message_file_is_open;
	message_settings_controller_copy->message_file_path	=	message_settings_controller->message_file_path;
	message_settings_controller_copy->message_file	=	message_settings_controller->message_file;

	return message_settings_controller_copy;
}

