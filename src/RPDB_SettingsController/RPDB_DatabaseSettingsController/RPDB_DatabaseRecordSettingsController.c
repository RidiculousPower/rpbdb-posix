/*
 *		RPDB_settingsController:RPDB_DatabaseRecordSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseRecordSettingsController.h"

	#include "RPDB_DBT.h"

	#include "RPDB_SettingsController.h"
	#include "RPDB_MemoryPoolSettingsController.h"
	#include "RPDB_DatabaseReadWriteSettingsController.h"
	#include "RPDB_DatabaseRecordSettingsController.h"
	#include "RPDB_DatabaseSettingsController.h"
	
	#include "RPDB_Environment.h"

	#include "RPDB_DatabaseRecordSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_DatabaseRecordSettingsController* RPDB_DatabaseRecordSettingsController_new( RPDB_DatabaseSettingsController* database_settings_controller )	{

	RPDB_DatabaseRecordSettingsController*	record_settings_controller = calloc( 1, sizeof( RPDB_DatabaseRecordSettingsController ) );

	record_settings_controller->parent_database_settings_controller = database_settings_controller;

	return record_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseRecordSettingsController_free(	RPDB_DatabaseRecordSettingsController** record_settings_controller )	{

	free( *record_settings_controller );
	*record_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseRecordSettingsController_parentEnvironment(	RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	return record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseRecordSettingsController_parentDatabase(	RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	return record_settings_controller->parent_database_settings_controller->parent_database;
}

/*****************************************
*  databaseAllocatesMemoryUsingMalloc  *
*****************************************/

BOOL RPDB_DatabaseRecordSettingsController_databaseAllocatesMemoryUsingMalloc( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
	//	If we don't have a settings controller as our parent then we have an instance as our parent
	if ( record_settings_controller->parent_database_settings_controller == NULL )	{
		return record_settings_controller->database_allocates_memory_using_malloc;
	}
	else	{
		return RPDB_MemoryPoolSettingsController_databaseAllocatesMemoryUsingMalloc( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller )  );
	}
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOn  *
	*************************************************/

	void RPDB_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
		//	If we don't have a settings controller as our parent then we have an instance as our parent
		if ( record_settings_controller->parent_database_settings_controller == NULL )	{
			record_settings_controller->database_allocates_memory_using_malloc = TRUE;
		}
		else	{
			RPDB_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPDB_DatabaseSettingsController_recordSettingsController( RPDB_SettingsController_databaseSettingsController( RPDB_Environment_settingsController( record_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ) ) ) );
		}
		RPDB_DatabaseRecordSettingsController_internal_updateFlags( record_settings_controller );
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingMallocOff  *
	*************************************************/

	void RPDB_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
		//	If we don't have a settings controller as our parent then we have an instance as our parent
		if ( record_settings_controller->parent_database_settings_controller == NULL )	{
			record_settings_controller->database_allocates_memory_using_malloc = FALSE;
		}
		else	{
			RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) );
		}
		RPDB_DatabaseRecordSettingsController_internal_updateFlags( record_settings_controller );
	}

/*********************************************
*  databaseAllocatesMemoryUsingRealloc  *
*********************************************/

BOOL RPDB_DatabaseRecordSettingsController_databaseAllocatesMemoryUsingRealloc( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
	//	If we don't have a settings controller as our parent then we have an instance as our parent
	if ( record_settings_controller->parent_database_settings_controller == NULL )	{
		return record_settings_controller->database_allocates_memory_using_realloc;
	}
	else	{
		return RPDB_MemoryPoolSettingsController_databaseAllocatesMemoryUsingRealloc( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) );
	}		
}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOn  *
	*************************************************/

	void RPDB_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
		//	If we don't have a settings controller as our parent then we have an instance as our parent
		if ( record_settings_controller->parent_database_settings_controller == NULL )	{
			record_settings_controller->database_allocates_memory_using_realloc = TRUE;
		}
		else	{
			RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) );
		}		
		RPDB_DatabaseRecordSettingsController_internal_updateFlags( record_settings_controller );
	}

	/*************************************************
	*  turnDatabaseAllocatesMemoryUsingReallocOff  *
	*************************************************/

	void RPDB_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
		//	If we don't have a settings controller as our parent then we have an instance as our parent
		if ( record_settings_controller->parent_database_settings_controller == NULL )	{
			record_settings_controller->database_allocates_memory_using_realloc = FALSE;
		}
		else	{
			RPDB_MemoryPoolSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) );
		}		
		RPDB_DatabaseRecordSettingsController_internal_updateFlags( record_settings_controller );
	}

/*********************************
*  applicationAllocatesMemory  *
*********************************/

BOOL RPDB_DatabaseRecordSettingsController_applicationAllocatesMemory( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
	//	If we don't have a settings controller as our parent then we have an instance as our parent
	if ( record_settings_controller->parent_database_settings_controller == NULL )	{
		return record_settings_controller->application_allocates_memory;
	}
	else	{
		return RPDB_MemoryPoolSettingsController_applicationAllocatesMemory( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) );
	}
}

	/*****************************************
	*  turnApplicationAllocatesMemoryOn  *
	*****************************************/

	void RPDB_DatabaseRecordSettingsController_turnApplicationAllocatesMemoryOn( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
		//	If we don't have a settings controller as our parent then we have an instance as our parent
		if ( record_settings_controller->parent_database_settings_controller == NULL )	{
			record_settings_controller->application_allocates_memory = TRUE;
		}
		else	{
			RPDB_MemoryPoolSettingsController_applicationAllocatesMemory( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) );
		}
		RPDB_DatabaseRecordSettingsController_internal_updateFlags( record_settings_controller );
	}

	/*****************************************
	*  turnApplicationAllocatesMemoryOff  *
	*****************************************/

	void RPDB_DatabaseRecordSettingsController_turnApplicationAllocatesMemoryOff( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
		//	If we don't have a settings controller as our parent then we have an instance as our parent
		if ( record_settings_controller->parent_database_settings_controller == NULL )	{
			record_settings_controller->application_allocates_memory = FALSE;
		}
		else	{
			RPDB_MemoryPoolSettingsController_applicationAllocatesMemory( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) );
		}
		RPDB_DatabaseRecordSettingsController_internal_updateFlags( record_settings_controller );
	}

/*****************************
*  databaseFreesMemory  *
*****************************/

BOOL RPDB_DatabaseRecordSettingsController_databaseFreesMemory( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
	//	If we don't have a settings controller as our parent then we have an instance as our parent
	if ( record_settings_controller->parent_database_settings_controller == NULL )	{
		return record_settings_controller->database_free_memory;
	}
	else	{
		return RPDB_MemoryPoolSettingsController_databaseFreesMemory( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) );
	}
}

	/*********************************
	*  turnDatabaseFreesMemoryOn  *
	*********************************/

	void RPDB_DatabaseRecordSettingsController_turnDatabaseFreesMemoryOn( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
		//	If we don't have a settings controller as our parent then we have an instance as our parent
		if ( record_settings_controller->parent_database_settings_controller == NULL )	{
			record_settings_controller->database_free_memory = TRUE;
		}
		else	{
			RPDB_MemoryPoolSettingsController_databaseFreesMemory( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) );
		}
		RPDB_DatabaseRecordSettingsController_internal_updateFlags( record_settings_controller );
	}

	/*********************************
	*  turnDatabaseFreesMemoryOff  *
	*********************************/

	void RPDB_DatabaseRecordSettingsController_turnDatabaseFreesMemoryOff( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
		//	If we don't have a settings controller as our parent then we have an instance as our parent
		if ( record_settings_controller->parent_database_settings_controller == NULL )	{
			record_settings_controller->database_free_memory = FALSE;
		}
		else	{
			RPDB_MemoryPoolSettingsController_databaseFreesMemory( RPDB_SettingsController_memoryPoolSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) );
		}
		RPDB_DatabaseRecordSettingsController_internal_updateFlags( record_settings_controller );
	}

/*********************
*  partialAccess  *
*********************/

BOOL RPDB_DatabaseRecordSettingsController_partialAccess( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
	//	If we don't have a settings controller as our parent then we have an instance as our parent
	if ( record_settings_controller->parent_database_settings_controller == NULL )	{
		return record_settings_controller->partial_access;
	}
	else	{
		return RPDB_DatabaseReadWriteSettingsController_partialAccess( RPDB_DatabaseSettingsController_readWriteSettingsController( RPDB_SettingsController_databaseSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) ) );
	}
}

	/*****************************
	*  turnPartialAccessOn  *
	*****************************/

	void RPDB_DatabaseRecordSettingsController_turnPartialAccessOn( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
		//	If we don't have a settings controller as our parent then we have an instance as our parent
		if ( record_settings_controller->parent_database_settings_controller == NULL )	{
			record_settings_controller->partial_access = TRUE;
		}
		else	{
			RPDB_DatabaseReadWriteSettingsController_partialAccess( RPDB_DatabaseSettingsController_readWriteSettingsController( RPDB_SettingsController_databaseSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) ) );
		}
		RPDB_DatabaseRecordSettingsController_internal_updateFlags( record_settings_controller );
	}

	/*****************************
	*  turnPartialAccessOff  *
	*****************************/

	void RPDB_DatabaseRecordSettingsController_turnPartialAccessOff( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
		//	If we don't have a settings controller as our parent then we have an instance as our parent
		if ( record_settings_controller->parent_database_settings_controller == NULL )	{
			record_settings_controller->partial_access = FALSE;
		}
		else	{
			RPDB_DatabaseReadWriteSettingsController_partialAccess( RPDB_DatabaseSettingsController_readWriteSettingsController( RPDB_SettingsController_databaseSettingsController( record_settings_controller->parent_database_settings_controller->parent_settings_controller ) ) );
		}
		RPDB_DatabaseRecordSettingsController_internal_updateFlags( record_settings_controller );
	}
	
/*****************************
*  syncPriorToWriteReturn  *
*****************************/

//	DB_DSYNC_DB             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
BOOL RPDB_DatabaseRecordSettingsController_syncPriorToWriteReturn( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{

	if ( record_settings_controller->sync_prior_to_write_return == TRUE )	{
		return DB_DSYNC_DB;
	}
	return FALSE;
}

	/**************************************
	*  turnSyncPriorToWriteReturnOn  *
	**************************************/

	void RPDB_DatabaseRecordSettingsController_turnSyncPriorToWriteReturnOn( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{

		record_settings_controller->sync_prior_to_write_return = TRUE;
	}

	/************************************
	*  turnSyncPriorToWriteReturnOff  *
	************************************/

	void RPDB_DatabaseRecordSettingsController_turnSyncPriorToWriteReturnOff( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{

		record_settings_controller->sync_prior_to_write_return = FALSE;
	}

/*********************
*  dataBufferSize  *
*********************/

uint32_t RPDB_DatabaseRecordSettingsController_dataBufferSize( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( record_settings_controller->parent_record == NULL )	{
		
		return record_settings_controller->data_buffer_size;
	}
	else	{

		//	FIX
//		return record_settings_controller->parent_record->wrapped_bdb_dbt->ulen;	
return 0;	
	}
}	

/*************************
*  setDataBufferSize  *
*************************/

void RPDB_DatabaseRecordSettingsController_setDataBufferSize(	RPDB_DatabaseRecordSettingsController*		record_settings_controller, 
													uint32_t							buffer_size )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( record_settings_controller->parent_record == NULL )	{
		
		record_settings_controller->data_buffer_size = buffer_size;
	}
	else	{

		//	FIX
//		record_settings_controller->parent_record->wrapped_bdb_dbt->ulen = buffer_size;
	}
}	

/*****************************
*  partialReadWriteSize  *
*****************************/

//	Returns size of partial write (if applicable)
//	It is an error to attempt a partial put using the DB->put function in a database that supports duplicate records. 
//	Partial puts in databases supporting duplicate records must be done using a DBcursor->put function.
uint32_t RPDB_DatabaseRecordSettingsController_partialReadWriteSize( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( record_settings_controller->parent_record == NULL )	{
		
		return record_settings_controller->partial_read_write_size;
	}
	else	{

//	FIX
//		return record_settings_controller->parent_record->wrapped_bdb_dbt->dlen;
		return 0;	
	}

}	

/*********************************
*  setPartialReadWriteSize  *
*********************************/

void RPDB_DatabaseRecordSettingsController_setPartialReadWriteSize(	RPDB_DatabaseRecordSettingsController*		record_settings_controller, 
															uint32_t							partial_read_write_size )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( record_settings_controller->parent_record == NULL )	{
		
		record_settings_controller->partial_read_write_size = partial_read_write_size;
	}
	else	{

		//	FIX
//		record_settings_controller->parent_record->wrapped_bdb_dbt->dlen = partial_read_write_size;
	}
}	

/*****************************
*  partialReadWriteOffset  *
*****************************/

uint32_t RPDB_DatabaseRecordSettingsController_partialReadWriteOffset( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( record_settings_controller->parent_record == NULL )	{
		
		return record_settings_controller->partial_read_write_offset;
	}
	else	{

		//	FIX
//		return record_settings_controller->parent_record->wrapped_bdb_dbt->doff;
		return 0;	
	}

}	

/*********************************
*  setPartialReadWriteOffset  *
*********************************/

void RPDB_DatabaseRecordSettingsController_setPartialReadWriteOffset(	RPDB_DatabaseRecordSettingsController*		record_settings_controller, 
															uint32_t							partial_read_write_offset )	{

	//	If we are a local settings controller, return the actual buffer length, otherwise return the global setting
	if ( record_settings_controller->parent_record == NULL )	{
		
		record_settings_controller->partial_read_write_offset = partial_read_write_offset;
	}
	else	{

		//	FIX
//		record_settings_controller->parent_record->wrapped_bdb_dbt->doff = partial_read_write_offset;
	}
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/************
*  flags  *
************/

//	Most every other time flags are used when a function is called, so they can be composited on the fly
//	Here flags go in a variable rather than parameter, so we have to update them when we change a setting,
//	and then store the flags for use when appropriate (which is determined by the database handling the DBT). 
void RPDB_DatabaseRecordSettingsController_internal_updateFlags( RPDB_DatabaseRecordSettingsController* record_settings_controller )	{
	
	uint32_t*	flags_pointer	=	NULL;
			
	//	Make sure we're addressing the settings controller belonging to the instance
	//	If we don't have a parent_settings_controller then get our parent_record
	if ( record_settings_controller->parent_database_settings_controller == NULL )	{
		//	FIX
//		flags_pointer = &( record_settings_controller->parent_record->wrapped_bdb_dbt->flags );
	}
	//	Or otherwise the universal settings controller
	else	{
		flags_pointer = &( record_settings_controller->flags );
	}

	//	Update the flags stored in the DBT
	*flags_pointer =	RPDB_DatabaseRecordSettingsController_databaseAllocatesMemoryUsingMalloc( record_settings_controller )
						|	RPDB_DatabaseRecordSettingsController_databaseAllocatesMemoryUsingRealloc( record_settings_controller )
						|	RPDB_DatabaseRecordSettingsController_applicationAllocatesMemory( record_settings_controller )
						|	RPDB_DatabaseRecordSettingsController_partialAccess( record_settings_controller )
						|	RPDB_DatabaseRecordSettingsController_databaseFreesMemory( record_settings_controller );
}	

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseRecordSettingsController* RPDB_DatabaseRecordSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseRecordSettingsController* record_settings_controller )	{

	RPDB_DatabaseRecordSettingsController* record_settings_controller_copy	=	RPDB_DatabaseRecordSettingsController_new( record_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	record_settings_controller_copy->flags	=	record_settings_controller->flags;
	record_settings_controller_copy->database_allocates_memory_using_malloc	=	record_settings_controller->database_allocates_memory_using_malloc;
	record_settings_controller_copy->data_buffer_size	=	record_settings_controller->data_buffer_size;
	record_settings_controller_copy->database_allocates_memory_using_realloc	=	record_settings_controller->database_allocates_memory_using_realloc;
	record_settings_controller_copy->partial_read_write_size	=	record_settings_controller->partial_read_write_size;
	record_settings_controller_copy->partial_access	=	record_settings_controller->partial_access;
	record_settings_controller_copy->sync_prior_to_write_return	=	record_settings_controller->sync_prior_to_write_return;
	record_settings_controller_copy->database_free_memory	=	record_settings_controller->database_free_memory;
	record_settings_controller_copy->application_allocates_memory	=	record_settings_controller->application_allocates_memory;
	record_settings_controller_copy->partial_read_write_offset	=	record_settings_controller->partial_read_write_offset;

	return record_settings_controller_copy;
}

