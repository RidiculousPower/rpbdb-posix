/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeHashSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseTypeHashSettingsController.h"
#include "DatabaseTypeHashSettingsController_internal.h"

#include "DatabaseTypeSettingsController.h"
#include "DatabaseTypeSettingsController_internal.h"

#include "Database.h"

#include "Data.h"
#include "DBT_internal.h"

#include "Environment.h"

#include "ErrorController.h"

#include "DatabaseSettingsController.h"

#include "DatabaseRecordSettingsController.h"
#include "DatabaseRecordReadWriteSettingsController.h"

#include "RuntimeStorageController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseTypeHashSettingsController* RPbdb_DatabaseTypeHashSettingsController_new( RPbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	RPbdb_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseTypeHashSettingsController ) );

	database_type_hash_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_hash_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseTypeHashSettingsController_free(	RPbdb_DatabaseTypeHashSettingsController** database_type_hash_settings_controller )	{

	free( *database_type_hash_settings_controller );
	*database_type_hash_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseTypeHashSettingsController_parentEnvironment(	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{
	return database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseTypeHashSettingsController_parentDatabase(	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{
	return database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/******************
*  tableSize  *
******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_h_nelem.html
uint32_t RPbdb_DatabaseTypeHashSettingsController_tableSize( RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	RPbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;

	if (	database_type_hash_settings_controller->table_size == 0
		&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->get_h_nelem(	database->wrapped_bdb_database, 
																				&( database_type_hash_settings_controller->table_size ) ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"DatabaseTypeHashSettingsController_tableSize" );
		}
	}
	return database_type_hash_settings_controller->table_size;	
}

/*********************
*  setTableSize  *
*********************/

void RPbdb_DatabaseTypeHashSettingsController_setTableSize(	RPbdb_DatabaseTypeHashSettingsController*	database_type_hash_settings_controller, 
															uint32_t									number_of_elements )	{

	RPbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;
		
	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->set_h_nelem(	database->wrapped_bdb_database, 
																				number_of_elements ) ) )	{
		
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"DatabaseTypeHashSettingsController_setTableSize" );
		}
	}
	
	database_type_hash_settings_controller->table_size = number_of_elements;
}

/**************************
*  hashDensityFactor  *
**************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_h_ffactor.html
uint32_t RPbdb_DatabaseTypeHashSettingsController_hashDensityFactor( RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	RPbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	int			connection_error	= RP_NO_ERROR;

	if (	! database_type_hash_settings_controller->density
		&&	database != NULL
		&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->get_h_ffactor(	database->wrapped_bdb_database, 
																					&( database_type_hash_settings_controller->density ) ) ) )	{
		
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"DatabaseTypeHashSettingsController_hashDensityFactor" );
		}
	}
	
	return database_type_hash_settings_controller->density;
}

/******************************
*  setHashDensityFactor  *
******************************/

void RPbdb_DatabaseTypeHashSettingsController_setHashDensityFactor(	RPbdb_DatabaseTypeHashSettingsController*	database_type_hash_settings_controller, 
																																		uint32_t									density )	{

	RPbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;

	database_type_hash_settings_controller->density	=	density;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->set_h_ffactor(	database->wrapped_bdb_database, 
																					database_type_hash_settings_controller->density ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"DatabaseTypeHashSettingsController_setHashDensityFactor" );
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
void RPbdb_DatabaseTypeHashSettingsController_setHashMethod(	RPbdb_DatabaseTypeHashSettingsController*	database_type_hash_settings_controller,
 																int (*hash_method)(	RPbdb_Database*			database, 
																					const void*				bytes, 
																					uint32_t				length ) )	{

	RPbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	
	int			connection_error	= 0;

	if ( ( connection_error = database->set_h_hash(	database, 
													(	database_type_hash_settings_controller->method == NULL ?
														NULL :
														& RPbdb_DatabaseTypeHashSettingsController_internal_hashMethod ) ) ) )	{

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseTypeHashSettingsController_setHashMethod" );
	}
	
	database_type_hash_settings_controller->method = method;
}
*/
/******************
*  hashMethod  *
******************/
/*
int (*hash_method)(	RPbdb_Database*			database, 
					const void*				bytes, 
					uint32_t				length ) RPbdb_DatabaseTypeHashSettingsController_hashMethod( RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	return database_type_hash_settings_controller->hash_method;
}
*/
/**************************
*  setCompareMethod  *
**************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_h_compare.html
void RPbdb_DatabaseTypeHashSettingsController_setCompareMethod(		RPbdb_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller,
 																	int (*compare_method)(	RPbdb_Database*			database, 
																							const RPbdb_Data*		data_one, 
																							const RPbdb_Data*		data_two ) )	{

	RPbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	void*		compare_method;

	int			connection_error	= 0;
	
	database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	
	compare_method = int (*RPbdb_DatabaseTypeHashSettingsController_internal_compareMethod)( DB* database, const DBT* data_one, const DBT* data_two );
	
	database_type_hash_settings_controller->compare_method = compare_method;

	if ( ( connection_error = database->set_h_compare(	database,
														(	database_type_hash_settings_controller->compare_method == NULL ?
															NULL :
															& RPbdb_DatabaseTypeHashSettingsController_internal_duplicateCompareMethod ) ) ) )	{

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseTypeHashSettingsController_setCompareMethod" );
	}
}
*/
/*********************
*  compareMethod  *
*********************/
/*
int (*compare_method)(	RPbdb_Database*		database, 
						const DBT*			data_one, 
						const DBT*			data_two ) RPbdb_DatabaseTypeHashSettingsController_compareMethod( RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	return database_type_hash_settings_controller->compare_method;
}
*/
/**********************************
*  setDuplicateCompareMethod  *
**********************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_dup_compare.html
void RPbdb_DatabaseTypeHashSettingsController_setDuplicateCompareMethod(	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller,
 																			int (*duplicate_compare_method)(	RPbdb_Database*			database, 
																												const RPbdb_Data*		data_one, 
																												const RPbdb_Data*		data_two ) )	{

	RPbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	database_type_hash_settings_controller->duplicate_compare_method = duplicate_compare_method;
	
	if ( ( connection_error = database->set_dup_compare(	database, 
															(	database_type_hash_settings_controller->duplicate_compare_method == NULL ?
																NULL :
																& RPbdb_DatabaseTypeHashSettingsController_internal_compareMethod ) ) ) )	{

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseTypeHashSettingsController_setDuplicateCompareMethod" );
	}
}
*/
/*****************************
*  duplicateCompareMethod  *
*****************************/
/*
int (*duplicate_compare_method)(	RPbdb_Database*		database, 
									const DBT*			data_one, 
									const DBT*			data_two ) RPbdb_DatabaseTypeHashSettingsController_duplicateCompareMethod( RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

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
uint32_t RPbdb_DatabaseTypeHashSettingsController_internal_hashMethod(	DB*				bdb_database, 
																		const void*		bytes, 
																		uint32_t		length )	{

	RPbdb_Database*		database	=	RPbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller	=	RPbdb_DatabaseTypeSettingsController_hashSettingsController(
																								RPbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									RPbdb_Database_settingsController( database ) ) );
	return *( database_type_hash_settings_controller->hash_method(	database,
																	bytes,
																	length	) );
}
*/
/********************************
*  duplicateCompareMethod  *
********************************/
/*
int RPbdb_DatabaseTypeHashSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
																				const DBT*		data_one, 
																				const DBT*		data_two)	{

	RPbdb_Database*		database	=	RPbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller	=	RPbdb_DatabaseTypeSettingsController_hashSettingsController(
																								RPbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									RPbdb_Database_settingsController( database ) ) );

	RPbdb_Data*			data_one	=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT(	NULL, data_one );
	RPbdb_Data*			data_two	=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT(	NULL, data_two );

	return *( database_type_hash_settings_controller->duplicate_compare_method(		database,
																					data_one,
																					data_two	) );	
}
*/
/********************
*  compareMethod  *
********************/
/*
int RPbdb_DatabaseTypeHashSettingsController_internal_compareMethod(	DB*				bdb_database, 
																		const DBT*		data_one, 
																		const DBT*		data_two)	{
	
	RPbdb_Database*		database	=	RPbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller	=	RPbdb_DatabaseTypeSettingsController_hashSettingsController(
																								RPbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									RPbdb_Database_settingsController( database ) ) );

	RPbdb_Data*			data_one	=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT(	NULL, data_one );
	RPbdb_Data*			data_two	=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT(	NULL, data_two );

	return *( database_type_hash_settings_controller->compare_method(	database,
																		data_one,
																		data_two	) );
}
*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseTypeHashSettingsController* RPbdb_DatabaseTypeHashSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller_copy	=	RPbdb_DatabaseTypeHashSettingsController_new( database_type_hash_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_hash_settings_controller_copy->table_size	=	database_type_hash_settings_controller->table_size;
	database_type_hash_settings_controller_copy->density	=	database_type_hash_settings_controller->density;

	return database_type_hash_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void RPbdb_DatabaseTypeHashSettingsController_internal_setFlags(	RPbdb_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller )	{
	
	RPbdb_Database*			database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	RPbdb_DatabaseSettingsController*									database_settings_controller										=	RPbdb_Database_settingsController( database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
																							RPbdb_DatabaseTypeSettingsController_internal_setFlags( database_type_hash_settings_controller->parent_database_type_settings_controller )
																							|	RPbdb_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( database_record_read_write_settings_controller )
																							|	RPbdb_DatabaseRecordReadWriteSettingsController_sortedDuplicates( database_record_read_write_settings_controller ) );
}

