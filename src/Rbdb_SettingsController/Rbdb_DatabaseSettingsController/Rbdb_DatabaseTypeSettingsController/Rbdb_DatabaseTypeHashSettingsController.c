/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeHashSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseTypeHashSettingsController.h"
#include "Rbdb_DatabaseTypeHashSettingsController_internal.h"

#include "Rbdb_DatabaseTypeSettingsController.h"
#include "Rbdb_DatabaseTypeSettingsController_internal.h"

#include "Rbdb_Database.h"

#include "Rbdb_Data.h"
#include "Rbdb_DBT_internal.h"

#include "Rbdb_Environment.h"

#include "Rbdb_ErrorController.h"

#include "Rbdb_DatabaseSettingsController.h"

#include "Rbdb_DatabaseRecordSettingsController.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"

#include "Rbdb_RuntimeStorageController_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseTypeHashSettingsController* Rbdb_DatabaseTypeHashSettingsController_new( Rbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	Rbdb_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseTypeHashSettingsController ) );

	database_type_hash_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_hash_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseTypeHashSettingsController_free(	Rbdb_DatabaseTypeHashSettingsController** database_type_hash_settings_controller )	{

	free( *database_type_hash_settings_controller );
	*database_type_hash_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseTypeHashSettingsController_parentEnvironment(	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{
	return database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseTypeHashSettingsController_parentDatabase(	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{
	return database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/******************
*  tableSize  *
******************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_h_nelem.html
uint32_t Rbdb_DatabaseTypeHashSettingsController_tableSize( Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	Rbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;

	if (	database_type_hash_settings_controller->table_size == 0
		&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->get_h_nelem(	database->wrapped_bdb_database, 
																				&( database_type_hash_settings_controller->table_size ) ) ) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"Rbdb_DatabaseTypeHashSettingsController_tableSize" );
		}
	}
	return database_type_hash_settings_controller->table_size;	
}

/*********************
*  setTableSize  *
*********************/

void Rbdb_DatabaseTypeHashSettingsController_setTableSize(	Rbdb_DatabaseTypeHashSettingsController*	database_type_hash_settings_controller, 
															uint32_t									number_of_elements )	{

	Rbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;
		
	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->set_h_nelem(	database->wrapped_bdb_database, 
																				number_of_elements ) ) )	{
		
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"Rbdb_DatabaseTypeHashSettingsController_setTableSize" );
		}
	}
	
	database_type_hash_settings_controller->table_size = number_of_elements;
}

/**************************
*  hashDensityFactor  *
**************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_h_ffactor.html
uint32_t Rbdb_DatabaseTypeHashSettingsController_hashDensityFactor( Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	Rbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	int			connection_error	= RP_NO_ERROR;

	if (	! database_type_hash_settings_controller->density
		&&	database != NULL
		&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->get_h_ffactor(	database->wrapped_bdb_database, 
																					&( database_type_hash_settings_controller->density ) ) ) )	{
		
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
															connection_error, 
															"Rbdb_DatabaseTypeHashSettingsController_hashDensityFactor" );
		}
	}
	
	return database_type_hash_settings_controller->density;
}

/******************************
*  setHashDensityFactor  *
******************************/

void Rbdb_DatabaseTypeHashSettingsController_setHashDensityFactor(	Rbdb_DatabaseTypeHashSettingsController*	database_type_hash_settings_controller, 
																																		uint32_t									density )	{

	Rbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= RP_NO_ERROR;

	database_type_hash_settings_controller->density	=	density;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{

		if ( ( connection_error = database->wrapped_bdb_database->set_h_ffactor(	database->wrapped_bdb_database, 
																					database_type_hash_settings_controller->density ) ) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"Rbdb_DatabaseTypeHashSettingsController_setHashDensityFactor" );
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
void Rbdb_DatabaseTypeHashSettingsController_setHashMethod(	Rbdb_DatabaseTypeHashSettingsController*	database_type_hash_settings_controller,
 																int (*hash_method)(	Rbdb_Database*			database, 
																					const void*				bytes, 
																					uint32_t				length ) )	{

	Rbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	
	int			connection_error	= 0;

	if ( ( connection_error = database->set_h_hash(	database, 
													(	database_type_hash_settings_controller->method == NULL ?
														NULL :
														& Rbdb_DatabaseTypeHashSettingsController_internal_hashMethod ) ) ) )	{

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseTypeHashSettingsController_setHashMethod" );
	}
	
	database_type_hash_settings_controller->method = method;
}
*/
/******************
*  hashMethod  *
******************/
/*
int (*hash_method)(	Rbdb_Database*			database, 
					const void*				bytes, 
					uint32_t				length ) Rbdb_DatabaseTypeHashSettingsController_hashMethod( Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	return database_type_hash_settings_controller->hash_method;
}
*/
/**************************
*  setCompareMethod  *
**************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_h_compare.html
void Rbdb_DatabaseTypeHashSettingsController_setCompareMethod(		Rbdb_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller,
 																	int (*compare_method)(	Rbdb_Database*			database, 
																							const Rbdb_Data*		data_one, 
																							const Rbdb_Data*		data_two ) )	{

	Rbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	void*		compare_method;

	int			connection_error	= 0;
	
	database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	
	compare_method = int (*Rbdb_DatabaseTypeHashSettingsController_internal_compareMethod)( DB* database, const DBT* data_one, const DBT* data_two );
	
	database_type_hash_settings_controller->compare_method = compare_method;

	if ( ( connection_error = database->set_h_compare(	database,
														(	database_type_hash_settings_controller->compare_method == NULL ?
															NULL :
															& Rbdb_DatabaseTypeHashSettingsController_internal_duplicateCompareMethod ) ) ) )	{

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseTypeHashSettingsController_setCompareMethod" );
	}
}
*/
/*********************
*  compareMethod  *
*********************/
/*
int (*compare_method)(	Rbdb_Database*		database, 
						const DBT*			data_one, 
						const DBT*			data_two ) Rbdb_DatabaseTypeHashSettingsController_compareMethod( Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	return database_type_hash_settings_controller->compare_method;
}
*/
/**********************************
*  setDuplicateCompareMethod  *
**********************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_dup_compare.html
void Rbdb_DatabaseTypeHashSettingsController_setDuplicateCompareMethod(	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller,
 																			int (*duplicate_compare_method)(	Rbdb_Database*			database, 
																												const Rbdb_Data*		data_one, 
																												const Rbdb_Data*		data_two ) )	{

	Rbdb_Database*		database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	database_type_hash_settings_controller->duplicate_compare_method = duplicate_compare_method;
	
	if ( ( connection_error = database->set_dup_compare(	database, 
															(	database_type_hash_settings_controller->duplicate_compare_method == NULL ?
																NULL :
																& Rbdb_DatabaseTypeHashSettingsController_internal_compareMethod ) ) ) )	{

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseTypeHashSettingsController_setDuplicateCompareMethod" );
	}
}
*/
/*****************************
*  duplicateCompareMethod  *
*****************************/
/*
int (*duplicate_compare_method)(	Rbdb_Database*		database, 
									const DBT*			data_one, 
									const DBT*			data_two ) Rbdb_DatabaseTypeHashSettingsController_duplicateCompareMethod( Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

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
uint32_t Rbdb_DatabaseTypeHashSettingsController_internal_hashMethod(	DB*				bdb_database, 
																		const void*		bytes, 
																		uint32_t		length )	{

	Rbdb_Database*		database	=	Rbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller	=	Rbdb_DatabaseTypeSettingsController_hashSettingsController(
																								Rbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									Rbdb_Database_settingsController( database ) ) );
	return *( database_type_hash_settings_controller->hash_method(	database,
																	bytes,
																	length	) );
}
*/
/********************************
*  duplicateCompareMethod  *
********************************/
/*
int Rbdb_DatabaseTypeHashSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
																				const DBT*		data_one, 
																				const DBT*		data_two)	{

	Rbdb_Database*		database	=	Rbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller	=	Rbdb_DatabaseTypeSettingsController_hashSettingsController(
																								Rbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									Rbdb_Database_settingsController( database ) ) );

	Rbdb_Data*			data_one	=	(Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT(	NULL, data_one );
	Rbdb_Data*			data_two	=	(Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT(	NULL, data_two );

	return *( database_type_hash_settings_controller->duplicate_compare_method(		database,
																					data_one,
																					data_two	) );	
}
*/
/********************
*  compareMethod  *
********************/
/*
int Rbdb_DatabaseTypeHashSettingsController_internal_compareMethod(	DB*				bdb_database, 
																		const DBT*		data_one, 
																		const DBT*		data_two)	{
	
	Rbdb_Database*		database	=	Rbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller	=	Rbdb_DatabaseTypeSettingsController_hashSettingsController(
																								Rbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									Rbdb_Database_settingsController( database ) ) );

	Rbdb_Data*			data_one	=	(Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT(	NULL, data_one );
	Rbdb_Data*			data_two	=	(Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT(	NULL, data_two );

	return *( database_type_hash_settings_controller->compare_method(	database,
																		data_one,
																		data_two	) );
}
*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseTypeHashSettingsController* Rbdb_DatabaseTypeHashSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller )	{

	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller_copy	=	Rbdb_DatabaseTypeHashSettingsController_new( database_type_hash_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_hash_settings_controller_copy->table_size	=	database_type_hash_settings_controller->table_size;
	database_type_hash_settings_controller_copy->density	=	database_type_hash_settings_controller->density;

	return database_type_hash_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void Rbdb_DatabaseTypeHashSettingsController_internal_setFlags(	Rbdb_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller )	{
	
	Rbdb_Database*			database = database_type_hash_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
																							Rbdb_DatabaseTypeSettingsController_internal_setFlags( database_type_hash_settings_controller->parent_database_type_settings_controller )
																							|	Rbdb_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( database_record_read_write_settings_controller )
																							|	Rbdb_DatabaseRecordReadWriteSettingsController_sortedDuplicates( database_record_read_write_settings_controller ) );
}

