/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeBtreeSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseTypeBtreeSettingsController.h"

#include "Rbdb_Environment.h"
#include "Rbdb_ErrorController.h"
#include "Rbdb_DatabaseTypeSettingsController.h"
#include "Rbdb_DatabaseSettingsController.h"
#include "Rbdb_Database.h"
#include "Rbdb_Data.h"

#include "Rbdb_DatabaseTypeBtreeSettingsController_internal.h"
#include "Rbdb_RuntimeStorageController_internal.h"
#include "Rbdb_DBT_internal.h"

#include "Rbdb_DatabaseRecordSettingsController.h"
#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"

#include "Rbdb_DatabaseTypeSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseTypeBtreeSettingsController* Rbdb_DatabaseTypeBtreeSettingsController_new( Rbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	Rbdb_DatabaseTypeBtreeSettingsController*		database_type_btree_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseTypeBtreeSettingsController ) );

	database_type_btree_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_btree_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseTypeBtreeSettingsController_free(	Rbdb_DatabaseTypeBtreeSettingsController** database_type_btree_settings_controller )	{

	free( *database_type_btree_settings_controller );
	*database_type_btree_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseTypeBtreeSettingsController_parentEnvironment(	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	return database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseTypeBtreeSettingsController_parentDatabase(	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	return database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/*****************************
*  recordNumberRetrieval  *
*****************************/

//	DB_RECNUM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL Rbdb_DatabaseTypeBtreeSettingsController_recordNumberRetrieval( Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	if ( database_type_btree_settings_controller->record_number_retrieval )	{
		return DB_RECNUM;
	}
	return FALSE;
}

	/************************************
	*  turnRecordNumberRetrievalOn  *
	************************************/

	void Rbdb_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOn( Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->record_number_retrieval = TRUE;
	}

	/*************************************
	*  turnRecordNumberRetrievalOff  *
	*************************************/

	void Rbdb_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOff( Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->record_number_retrieval = FALSE;
	}

/*************************
*  reverseSplitting  *
*************************/

//	DB_REVSPLITOFF		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL Rbdb_DatabaseTypeBtreeSettingsController_reverseSplitting( Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	if ( database_type_btree_settings_controller->reverse_splitting )	{

		return DB_REVSPLITOFF;
	}	

	return FALSE;
}

	/******************************
	*  turnReverseSplittingOn  *
	******************************/

	void Rbdb_DatabaseTypeBtreeSettingsController_turnReverseSplittingOn( Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->reverse_splitting = TRUE;
	}

	/********************************
	*  turnReverseSplittingOff  *
	********************************/
	void Rbdb_DatabaseTypeBtreeSettingsController_turnReverseSplittingOff( Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->reverse_splitting = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/**************************
*  minimumKeysPerPage  *
**************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_bt_minkey.html
uint32_t Rbdb_DatabaseTypeBtreeSettingsController_minimumKeysPerPage( Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	
	Rbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= 0;
	
	if ( ! database_type_btree_settings_controller->minimum_keys_per_page
		&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->get_bt_minkey(	database->wrapped_bdb_database,
																					&( database_type_btree_settings_controller->minimum_keys_per_page ) ) ) )	{

			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
														connection_error, 
														"Rbdb_DatabaseTypeBtreeSettingsController_minimumKeysPerPage" );
		}
	}
	
	return database_type_btree_settings_controller->minimum_keys_per_page;
}

/******************************
*  setMinimumKeysPerPage  *
******************************/

void Rbdb_DatabaseTypeBtreeSettingsController_setMinimumKeysPerPage(	Rbdb_DatabaseTypeBtreeSettingsController*	database_type_btree_settings_controller,
																																			uint32_t									minimum_keys_per_page )	{

	Rbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= 0;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->set_bt_minkey(	database->wrapped_bdb_database,
																																							minimum_keys_per_page ) ) )	{
			
			Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"Rbdb_DatabaseTypeBtreeSettingsController_minimumKeysPerPage" );
		}
	}

	database_type_btree_settings_controller->minimum_keys_per_page = minimum_keys_per_page;
}

/*******************************************************************************************************************************************************************************************
																		Callback Public Methods
*******************************************************************************************************************************************************************************************/
	
/********************************
*  setPrefixCompareMethod  *
********************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_bt_prefix.html
void Rbdb_DatabaseTypeBtreeSettingsController_setPrefixCompareMethod(	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller,
	 																	int (*prefix_compare_method)(	Rbdb_Database*			database, 
																										const Rbdb_Data*		data_one, 
																										const Rbdb_Data*		data_two ) )	{

	Rbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	
	int			connection_error	= 0;

	if ( ( connection_error = database->set_bt_prefix(	database,
	 													( prefix_compare_method == NULL ?
															NULL :
															& Rbdb_DatabaseTypeBtreeSettingsController_internal_prefixCompareMethod ) ) ) )	{

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseTypeBtreeSettingsController_prefixCompareMethod" );
	}

	database_type_btree_settings_controller->prefix_compare_method = prefix_compare_method;
}
*/
/****************************
*  prefixCompareMethod  *
****************************/
/*
size_t (*prefix_compare_method)(	Rbdb_Database*		database, 
									const DBT*			data_one, 
									const DBT*			data_two ) Rbdb_DatabaseTypeBtreeSettingsController_prefixCompareMethod( Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	
	return database_type_btree_settings_controller->prefix_compare_method;
}
*/
/*************************
*  setCompareMethod  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_bt_compare.html
void Rbdb_DatabaseTypeBtreeSettingsController_setCompareMethod(	Rbdb_DatabaseTypeBtreeSettingsController*	database_type_btree_settings_controller,
 																	int (*compare_method)(	Rbdb_Database*			database, 
																							const Rbdb_Data*		data_one, 
																							const Rbdb_Data*		data_two ) )	{

	Rbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	if ( ( connection_error = database->set_bt_compare(	database, 
														( compare_method == NULL ?
															NULL :
															& Rbdb_DatabaseTypeBtreeSettingsController_internal_compareMethod ) ) ) )	{

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseTypeBtreeSettingsController_compareMethod" );
	}

	database_type_btree_settings_controller->compare_method = compare_method;
}
*/
/*********************
*  compareMethod  *
*********************/
/*
int (*compare_method)(	Rbdb_Database*		database, 
						const DBT*			data_one, 
						const DBT*			data_two ) Rbdb_DatabaseTypeBtreeSettingsController_compareMethod( Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	return database_type_btree_settings_controller->compare_method;
}
*/
/**********************************
*  setDuplicateCompareMethod  *
**********************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_dup_compare.html
void Rbdb_DatabaseTypeBtreeSettingsController_setDuplicateCompareMethod(	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller,
 																			int (*duplicate_compare_method)(	Rbdb_Database*			database, 
																												const Rbdb_Data*		data_one, 
																												const Rbdb_Data*		data_two ) )	{

	Rbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	if ( ( connection_error = database->set_dup_compare(	database, 
															( duplicate_compare_method == NULL ?
																NULL :
																& Rbdb_DatabaseTypeBtreeSettingsController_internal_duplicateCompareMethod ) ) ) )	{

		Rbdb_ErrorController_internal_throwBDBError(	Rbdb_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"Rbdb_DatabaseTypeBtreeSettingsController_duplicateCompareMethod" );
	}
	
	database_type_btree_settings_controller->duplicate_compare_method = duplicate_compare_method;
}
*/
/*****************************
*  duplicateCompareMethod  *
*****************************/
/*
int (*duplicate_compare_method)(	Rbdb_Database*		database, 
									const DBT*			data_one, 
									const DBT*			data_two ) Rbdb_DatabaseTypeBtreeSettingsController_duplicateCompareMethod( Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	return database_type_btree_settings_controller->duplicate_compare_method;
}
*/
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/****************************
*  prefixCompareMethod  *
****************************/
/*
size_t Rbdb_DatabaseTypeBtreeSettingsController_internal_prefixCompareMethod(	DB*				bdb_database, 
																				const DBT*		data_one, 
																				const DBT*		data_two )	{
	
	Rbdb_Database*		database	=	Rbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );
	
	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller	=	Rbdb_DatabaseTypeSettingsController_btreeSettingsController(
																								Rbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									Rbdb_Database_settingsController( database ) ) );
	
	Rbdb_Data*			data_one	=	(Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT(	NULL, data_one );
	Rbdb_Data*			data_two	=	(Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT(	NULL, data_two );
	
	return *( database_type_btree_settings_controller->prefix_compare_method(	database,
																				data_one,
																				data_two	) );
}
*/
/********************************
*  duplicateCompareMethod  *
********************************/
/*
int Rbdb_DatabaseTypeBtreeSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
																				const DBT*		data_one, 
																				const DBT*		data_two)	{

	Rbdb_Database*		database	=	Rbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller	=	Rbdb_DatabaseTypeSettingsController_btreeSettingsController(
																								Rbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									Rbdb_Database_settingsController( database ) ) );

	Rbdb_Data*			data_one	=	(Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT(	NULL, data_one );
	Rbdb_Data*			data_two	=	(Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT(	NULL, data_two );

	return *( database_type_btree_settings_controller->duplicate_compare_method(	database,
																					data_one,
																					data_two	) );	
}
*/
/********************
*  compareMethod  *
********************/
/*
int Rbdb_DatabaseTypeBtreeSettingsController_internal_compareMethod(	DB*				bdb_database, 
																		const DBT*		data_one, 
																		const DBT*		data_two)	{
	
	Rbdb_Database*		database	=	Rbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller	=	Rbdb_DatabaseTypeSettingsController_btreeSettingsController(
																								Rbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									Rbdb_Database_settingsController( database ) ) );

	Rbdb_Data*			data_one	=	(Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT(	NULL, data_one );
	Rbdb_Data*			data_two	=	(Rbdb_Data*) Rbdb_DBT_internal_newFromBDBDBT(	NULL, data_two );

	return *( database_type_btree_settings_controller->compare_method(	database,
																		data_one,
																		data_two	) );
}

*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseTypeBtreeSettingsController* Rbdb_DatabaseTypeBtreeSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller_copy	=	Rbdb_DatabaseTypeBtreeSettingsController_new( database_type_btree_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_btree_settings_controller_copy->minimum_keys_per_page	=	database_type_btree_settings_controller->minimum_keys_per_page;
	database_type_btree_settings_controller_copy->record_number_retrieval	=	database_type_btree_settings_controller->record_number_retrieval;
	database_type_btree_settings_controller_copy->reverse_splitting	=	database_type_btree_settings_controller->reverse_splitting;

	return database_type_btree_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void Rbdb_DatabaseTypeBtreeSettingsController_internal_setFlags(	Rbdb_DatabaseTypeBtreeSettingsController*		database_type_btree_settings_controller )	{

	Rbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	Rbdb_DatabaseSettingsController*									database_settings_controller										=	Rbdb_Database_settingsController( database );
	Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	Rbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
												Rbdb_DatabaseTypeSettingsController_internal_setFlags( database_type_btree_settings_controller->parent_database_type_settings_controller )
												|	Rbdb_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( database_record_read_write_settings_controller )
												|	Rbdb_DatabaseRecordReadWriteSettingsController_sortedDuplicates( database_record_read_write_settings_controller )
												|	Rbdb_DatabaseTypeBtreeSettingsController_recordNumberRetrieval( database_type_btree_settings_controller )
												|	Rbdb_DatabaseTypeBtreeSettingsController_reverseSplitting( database_type_btree_settings_controller )	);
}

