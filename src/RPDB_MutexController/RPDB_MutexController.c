/*
 *		RPDB::MutexController
 *
 *	
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MutexController.h"

#include "RPDB_Mutex.h"

#include "RPDB_Data.h"
#include "RPDB_Record.h"

#include "RPDB_SettingsController.h"
#include "RPDB_MutexSettingsController.h"

#include "RPDB_RuntimeStorage.h"

#include <string.h>

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_MutexController* RPDB_MutexController_new( RPDB_Environment* parent_environment )	{
	
	RPDB_MutexController*		mutex_controller = calloc( 1, sizeof( RPDB_MutexController ) );

	mutex_controller->parent_environment = parent_environment;

	return mutex_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MutexController_free( RPDB_MutexController** mutex_controller )	{

	if ( ( *mutex_controller )->runtime_storage != NULL )	{
		RPDB_RuntimeStorage_free( & ( ( *mutex_controller )->runtime_storage ) );
	}

	free( *mutex_controller );
	*mutex_controller	=	NULL;
}

/***************************
*  settingsController  *
***************************/
RPDB_MutexSettingsController* RPDB_MutexController_settingsController(	RPDB_MutexController* mutex_controller )	{
	return mutex_controller->settings_controller;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MutexController_parentEnvironment(	RPDB_MutexController* mutex_controller )	{
	return mutex_controller->parent_environment;
}

/*********************
*  mutexForName  *
*********************/

RPDB_Mutex* RPDB_MutexController_mutexForName(	RPDB_MutexController*		mutex_controller,
 													char*						mutex_name )	{

	RPDB_Mutex*	mutex;

	//	Check and see if mutex_name exists in runtime storage
	//	If it doesn't, we need to create it and store it
	if ( RPDB_RuntimeStorage_rawKeyExists(	mutex_controller->runtime_storage,
											mutex_name,
											( strlen( mutex_name ) + 1 ) * sizeof( char ) ) )	{
													
		mutex	=	RPDB_Data_rawData(	RPDB_Record_data(	RPDB_RuntimeStorage_retrieveRawKey(	mutex_controller->runtime_storage,
																											mutex_name,
																											( strlen( mutex_name ) + 1 ) * sizeof( char ) ) ) );
	}
	else	{
	
		//	Create a mutex for parent database
		mutex	=	RPDB_Mutex_new( mutex_controller );
	
		uintptr_t		new_mutex_address	=	(uintptr_t) mutex;

		//	Store pointer to mutex in runtime storage
		RPDB_RuntimeStorage_insertRawKeyDataPair(	mutex_controller->runtime_storage,
													mutex_name,
													( strlen( mutex_name ) + 1 ) * sizeof( char ),
													& new_mutex_address,
													sizeof( uintptr_t ) );
	}
	
	return mutex;
}

/*****************************
*  closeMutexForName  *
*****************************/

RPDB_Mutex* RPDB_MutexController_closeMutexForName(	RPDB_MutexController*		mutex_controller,
 														char*						mutex_name )	{
	
	RPDB_Mutex*	mutex	=	RPDB_MutexController_mutexForName(	mutex_controller,
																		mutex_name );
	RPDB_Mutex_close( mutex );
	
	return mutex;															
}

/*************************
*  freeMutexForName  *
*************************/

void RPDB_MutexController_freeMutexForName(	RPDB_MutexController*		mutex_controller,
 												char*						mutex_name )	{

	RPDB_Mutex*	mutex	=	RPDB_MutexController_mutexForName(	mutex_controller,
																		mutex_name );
	RPDB_Mutex_free( & mutex );
	
	RPDB_RuntimeStorage_deleteRecordForRawKey(	mutex_controller->runtime_storage,
												mutex_name,
												( strlen( mutex_name ) + 1 ) * sizeof( char ) );
}

/*****************
*  allMutexes  *
*****************/

//	Return a list of database names that have been created and stored in this controller
RPDB_Mutex** RPDB_MutexController_allMutexes( RPDB_MutexController* mutex_controller )	{

	RPDB_RuntimeStorage_countRecords( mutex_controller->runtime_storage );
	
	RPDB_Mutex*	this_mutex;
	
	RPDB_Mutex**	mutex_array	=	calloc(	mutex_controller->runtime_storage->record_count, sizeof( RPDB_Mutex ) );
	
	int				which_mutex	=	0;
	
	while ( ( this_mutex = (RPDB_Mutex*) *(uintptr_t*) RPDB_Record_rawData( RPDB_RuntimeStorage_nextRecord( mutex_controller->runtime_storage ) ) ) )	{
		
		mutex_array[ which_mutex ] = this_mutex;
		
		which_mutex++;
	}
	
	return mutex_array;
}

/*************************
*  closeAllMutexes  *
*************************/

void RPDB_MutexController_closeAllMutexes( RPDB_MutexController* mutex_controller )	{

	RPDB_RuntimeStorage_iterate( mutex_controller->runtime_storage );
	
	RPDB_Mutex*	this_mutex;
	
	while ( ( this_mutex = RPDB_Data_rawData(	RPDB_Record_data(	RPDB_RuntimeStorage_nextRecord( mutex_controller->runtime_storage ) ) ) ) )	{
		
		RPDB_Mutex_close( this_mutex );
	}
}

/*********************
*  freeAllMutexes  *
*********************/

void RPDB_MutexController_freeAllMutexes( RPDB_MutexController* mutex_controller )	{

	RPDB_RuntimeStorage_iterate( mutex_controller->runtime_storage );
	
	RPDB_Mutex*	this_mutex;
	
	while ( ( this_mutex = RPDB_Data_rawData(	RPDB_Record_data(	RPDB_RuntimeStorage_nextRecord( mutex_controller->runtime_storage ) ) ) ) )	{
		
		RPDB_Mutex_free( & this_mutex );
	}
}

