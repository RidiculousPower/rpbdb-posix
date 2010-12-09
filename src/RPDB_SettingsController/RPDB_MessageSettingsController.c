/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MessageSettingsController.h"

#include "Rbdb_ErrorController.h"
#include "Rbdb_RuntimeStorageController.h"
#include "Rbdb_SettingsController.h"
#include "Rbdb_Environment.h"

#include "Rbdb_MessageSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_MessageSettingsController* Rbdb_MessageSettingsController_new( Rbdb_SettingsController* settings_controller )	{
	
	Rbdb_MessageSettingsController*		message_settings_controller = calloc( 1, sizeof( Rbdb_MessageSettingsController ) );

	message_settings_controller->parent_settings_controller = settings_controller;
	
	return message_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_MessageSettingsController_free(	Rbdb_MessageSettingsController** message_settings_controller )	{

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
Rbdb_Environment* Rbdb_MessageSettingsController_parentEnvironment(	Rbdb_MessageSettingsController* message_settings_controller )	{
	return message_settings_controller->parent_settings_controller->parent_environment;
}

/*************
*  file  *
*************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_msgfile.html
FILE* Rbdb_MessageSettingsController_file( Rbdb_MessageSettingsController* message_settings_controller )	{

	Rbdb_Environment*		environment	= message_settings_controller->parent_settings_controller->parent_environment;
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

void Rbdb_MessageSettingsController_setFile( Rbdb_MessageSettingsController* message_settings_controller, FILE* message_file )	{

	Rbdb_Environment*		environment	= message_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->set_msgfile(	environment->wrapped_bdb_environment, 
															message_file );
	}
	
	message_settings_controller->message_file = message_file;
}

/*************************
*  setFileFromPath  *
*************************/

int Rbdb_MessageSettingsController_setFileFromPath( Rbdb_MessageSettingsController* message_settings_controller, char* message_file_path )	{

	FILE*		message_file;
	
	message_file = fopen( message_file_path, "w");
	
	if ( message_file == NULL )	{
		Rbdb_ErrorController_throwError(	Rbdb_Environment_errorController( message_settings_controller->parent_settings_controller->parent_environment ),
											-1,
											"Rbdb_MessageSettingsController_file",
											"Could not open file at path." );
		return 1;
	}
	
	Rbdb_MessageSettingsController_setFile(	message_settings_controller, 
												message_file );

	//	Don't we need to close this name at some point?
	
	return FALSE;
}

/*************************
*  setMessageCallback  *
*************************/
/*
void Rbdb_MessageSettingsController_setMessageCallbackMethod(	Rbdb_MessageSettingsController*					message_settings_controller, 
																void (*message_callback_method)(	Rbdb_Environment*			environment, 
																									const char*		message ) )	{
	
	DB_ENV*		environment	= message_settings_controller->parent_settings_controller->parent_environment->environment;

	//	Set the BDB message callback function to our private function; our private function will then pass on to the passed function pointer
	//	If we have a callback function, set it; otherwise, unset callback function (NULL function)
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->set_msgcall(	environment, 
									( message_settings_controller->message_callback == NULL ?
										NULL :
										& Rbdb_MessageSettingsController_internal_messageCallback ) );
	}
	
	message_settings_controller->message_callback = callback;	
}
*/
/*************************
*  messageCallback  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_msgcall.html
void (*message_callback_method)(	Rbdb_Environment*			environment, 
									const char*		message ) Rbdb_MessageSettingsController_messageCallbackMethod( Rbdb_MessageSettingsController* message_settings_controller )	{
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
void Rbdb_MessageSettingsController_internal_messageCallbackMethod(	const DB_ENV*	bdb_environment, 
																		const char*		message )	{

	Rbdb_Environment*								environment					=	Rbdb_RuntimeStorageController_environmentForBDBEnvironment( bdb_environment );
	
	Rbdb_MessageSettingsController*	message_settings_controller	=	Rbdb_SettingsController_messageSettingsController(
																			Rbdb_Environment_settingsController( environment ) );
	
	*( message_settings_controller->message_callback_method )(	environment,
																message );
}
*/
/*********************
*  eventCallback  *
*********************/
/*
//	This callback is called if any internal callbacks are defined. 
void Rbdb_MessageSettingsController_internal_eventCallbackMethod(	DB_ENV*			environment, 
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
Rbdb_MessageSettingsController* Rbdb_MessageSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MessageSettingsController* message_settings_controller )	{

	Rbdb_MessageSettingsController* message_settings_controller_copy	=	Rbdb_MessageSettingsController_new( message_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	message_settings_controller_copy->message_file_is_open	=	message_settings_controller->message_file_is_open;
	message_settings_controller_copy->message_file_path	=	message_settings_controller->message_file_path;
	message_settings_controller_copy->message_file	=	message_settings_controller->message_file;

	return message_settings_controller_copy;
}

