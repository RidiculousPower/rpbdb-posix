/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeHashSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseTypeHashSettingsController.h"
#include "RPDB_DatabaseTypeHashSettingsController_internal.h"

#include "RPDB_DatabaseTypeSettingsController.h"
#include "RPDB_DatabaseTypeSettingsController_internal.h"

#include "RPDB_Database.h"

#include "RPDB_Data.h"
#include "RPDB_Data_internal.h"

#include "RPDB_Environment.h"

#include "RPDB_ErrorController.h"

#include "RPDB_DatabaseSettingsController.h"

#include "RPDB_DatabaseRecordSettingsController.h"
#include "RPDB_DatabaseRecordReadWriteSettingsController.h"

#include "RPDB_RuntimeStorageController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseTypeHashSettingsController* RPDB_DatabaseTypeHashSettingsController_new( RPDB_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	RPDB_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller = calloc( 1, sizeof( RPDB_DatabaseTypeHashSettingsController ) );

	database_type_hash_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_hash_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseTypeHashSettingsController_free(	RPDB_DatabaseTypeHashSettingsController** database_type_hash_settings_controller )	{

	free( *database_type_hash_settings_controller );
	*database_type_hash_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseTypeHashSettingsController_parentEnvironment(	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{
	return database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseTypeHashSettingsController_parentDatabase(	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{
	return database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/******************
*  tableSize  *
******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_h_nelem.html
uint32_t RPDB_DatabaseTypeHashSettingsController_tableSize( RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	RPDB_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;

	if (	database_type_hash_settings_controller->table_size == 0
		&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->get_h_nelem(	database->wrapped_bdb_database, 
																				&( database_type_hash_settings_controller->table_size ) ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"RPDB_DatabaseTypeHashSettingsController_tableSize" );
		}
	}
	return database_type_hash_settings_controller->table_size;	
}

/*********************
*  setTableSize  *
*********************/

void RPDB_DatabaseTypeHashSettingsController_setTableSize(	RPDB_DatabaseTypeHashSettingsController*	database_type_hash_settings_controller, 
															uint32_t									number_of_elements )	{

	RPDB_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;
		
	if ( database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_h_nelem(	database->wrapped_bdb_database, 
																				number_of_elements ) ) )	{
		
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"RPDB_DatabaseTypeHashSettingsController_setTableSize" );
		}
	}
	
	database_type_hash_settings_controller->table_size = number_of_elements;
}

/**************************
*  hashDensityFactor  *
**************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_h_ffactor.html
uint32_t RPDB_DatabaseTypeHashSettingsController_hashDensityFactor( RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	RPDB_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	int			connection_error	= RP_NO_ERROR;

	if (	! database_type_hash_settings_controller->density
		&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->get_h_ffactor(	database->wrapped_bdb_database, 
																					&( database_type_hash_settings_controller->density ) ) ) )	{
		
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"RPDB_DatabaseTypeHashSettingsController_hashDensityFactor" );
		}
	}
	
	return database_type_hash_settings_controller->density;
}

/******************************
*  setHashDensityFactor  *
******************************/

void RPDB_DatabaseTypeHashSettingsController_setHashDensityFactor(	RPDB_DatabaseTypeHashSettingsController*	database_type_hash_settings_controller, 
																	uint32_t									density )	{

	RPDB_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;

	database_type_hash_settings_controller->density	=	density;

	if (	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->set_h_ffactor(	database->wrapped_bdb_database, 
																					database_type_hash_settings_controller->density ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"RPDB_DatabaseTypeHashSettingsController_setHashDensityFactor" );
		}
	}
}

/*******************************************************************************************************************************************************************************************
																		Callback Public Methods
*******************************************************************************************************************************************************************************************/
	
/**********************
*  setHashMethod  *
**********************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_h_hash.html
void RPDB_DatabaseTypeHashSettingsController_setHashMethod(	RPDB_DatabaseTypeHashSettingsController*	database_type_hash_settings_controller,
 																int (*hash_method)(	RPDB_Database*			database, 
																					const void*				bytes, 
																					uint32_t				length ) )	{

	RPDB_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	
	int			connection_error	= 0;

	if ( ( connection_error = database->set_h_hash(	database, 
													(	database_type_hash_settings_controller->method == NULL ?
														NULL :
														& RPDB_DatabaseTypeHashSettingsController_internal_hashMethod ) ) ) )	{

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseTypeHashSettingsController_setHashMethod" );
	}
	
	database_type_hash_settings_controller->method = method;
}
*/
/******************
*  hashMethod  *
******************/
/*
int (*hash_method)(	RPDB_Database*			database, 
					const void*				bytes, 
					uint32_t				length ) RPDB_DatabaseTypeHashSettingsController_hashMethod( RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	return database_type_hash_settings_controller->hash_method;
}
*/
/**************************
*  setCompareMethod  *
**************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_h_compare.html
void RPDB_DatabaseTypeHashSettingsController_setCompareMethod(		RPDB_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller,
 																	int (*compare_method)(	RPDB_Database*			database, 
																							const RPDB_Data*		data_one, 
																							const RPDB_Data*		data_two ) )	{

	RPDB_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	void*		compare_method;

	int			connection_error	= 0;
	
	database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	
	compare_method = int (*RPDB_DatabaseTypeHashSettingsController_internal_compareMethod)( DB* database, const DBT* data_one, const DBT* data_two );
	
	database_type_hash_settings_controller->compare_method = compare_method;

	if ( ( connection_error = database->set_h_compare(	database,
														(	database_type_hash_settings_controller->compare_method == NULL ?
															NULL :
															& RPDB_DatabaseTypeHashSettingsController_internal_duplicateCompareMethod ) ) ) )	{

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseTypeHashSettingsController_setCompareMethod" );
	}
}
*/
/*********************
*  compareMethod  *
*********************/
/*
int (*compare_method)(	RPDB_Database*		database, 
						const DBT*			data_one, 
						const DBT*			data_two ) RPDB_DatabaseTypeHashSettingsController_compareMethod( RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	return database_type_hash_settings_controller->compare_method;
}
*/
/**********************************
*  setDuplicateCompareMethod  *
**********************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_dup_compare.html
void RPDB_DatabaseTypeHashSettingsController_setDuplicateCompareMethod(	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller,
 																			int (*duplicate_compare_method)(	RPDB_Database*			database, 
																												const RPDB_Data*		data_one, 
																												const RPDB_Data*		data_two ) )	{

	RPDB_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	database_type_hash_settings_controller->duplicate_compare_method = duplicate_compare_method;
	
	if ( ( connection_error = database->set_dup_compare(	database, 
															(	database_type_hash_settings_controller->duplicate_compare_method == NULL ?
																NULL :
																& RPDB_DatabaseTypeHashSettingsController_internal_compareMethod ) ) ) )	{

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseTypeHashSettingsController_setDuplicateCompareMethod" );
	}
}
*/
/*****************************
*  duplicateCompareMethod  *
*****************************/
/*
int (*duplicate_compare_method)(	RPDB_Database*		database, 
									const DBT*			data_one, 
									const DBT*			data_two ) RPDB_DatabaseTypeHashSettingsController_duplicateCompareMethod( RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	return database_type_hash_settings_controller->duplicate_compare_method;
}
*/
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********************
*  hashMethod  *
********************/
/*
uint32_t RPDB_DatabaseTypeHashSettingsController_internal_hashMethod(	DB*				bdb_database, 
																		const void*		bytes, 
																		uint32_t		length )	{

	RPDB_Database*		database	=	RPDB_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller	=	RPDB_DatabaseTypeSettingsController_hashSettingsController(
																								RPDB_DatabaseSettingsController_databaseTypeSettingsController(
																									RPDB_Database_settingsController( database ) ) );
	return *( database_type_hash_settings_controller->hash_method(	database,
																	bytes,
																	length	) );
}
*/
/********************************
*  duplicateCompareMethod  *
********************************/
/*
int RPDB_DatabaseTypeHashSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
																				const DBT*		data_one, 
																				const DBT*		data_two)	{

	RPDB_Database*		database	=	RPDB_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller	=	RPDB_DatabaseTypeSettingsController_hashSettingsController(
																								RPDB_DatabaseSettingsController_databaseTypeSettingsController(
																									RPDB_Database_settingsController( database ) ) );

	RPDB_Data*			data_one	=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	NULL, data_one );
	RPDB_Data*			data_two	=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	NULL, data_two );

	return *( database_type_hash_settings_controller->duplicate_compare_method(		database,
																					data_one,
																					data_two	) );	
}
*/
/********************
*  compareMethod  *
********************/
/*
int RPDB_DatabaseTypeHashSettingsController_internal_compareMethod(	DB*				bdb_database, 
																		const DBT*		data_one, 
																		const DBT*		data_two)	{
	
	RPDB_Database*		database	=	RPDB_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller	=	RPDB_DatabaseTypeSettingsController_hashSettingsController(
																								RPDB_DatabaseSettingsController_databaseTypeSettingsController(
																									RPDB_Database_settingsController( database ) ) );

	RPDB_Data*			data_one	=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	NULL, data_one );
	RPDB_Data*			data_two	=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	NULL, data_two );

	return *( database_type_hash_settings_controller->compare_method(	database,
																		data_one,
																		data_two	) );
}
*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseTypeHashSettingsController* RPDB_DatabaseTypeHashSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller_copy	=	RPDB_DatabaseTypeHashSettingsController_new( database_type_hash_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_hash_settings_controller_copy->table_size	=	database_type_hash_settings_controller->table_size;
	database_type_hash_settings_controller_copy->density	=	database_type_hash_settings_controller->density;

	return database_type_hash_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void RPDB_DatabaseTypeHashSettingsController_internal_setFlags(	RPDB_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller )	{
	
	RPDB_Database*			database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	RPDB_DatabaseSettingsController*									database_settings_controller										=	RPDB_Database_settingsController( database );
	RPDB_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPDB_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPDB_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
																							RPDB_DatabaseTypeSettingsController_internal_setFlags( database_type_hash_settings_controller->parent_database_type_settings_controller )
																							|	RPDB_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( database_record_read_write_settings_controller )
																							|	RPDB_DatabaseRecordReadWriteSettingsController_sortedDuplicates( database_record_read_write_settings_controller ) );
}

