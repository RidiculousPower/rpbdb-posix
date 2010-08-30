/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeBtreeSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseTypeBtreeSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_ErrorController.h"
#include "RPDB_DatabaseTypeSettingsController.h"
#include "RPDB_DatabaseSettingsController.h"
#include "RPDB_Database.h"
#include "RPDB_Data.h"

#include "RPDB_DatabaseTypeBtreeSettingsController_internal.h"
#include "RPDB_RuntimeStorageController_internal.h"
#include "RPDB_Data_internal.h"

#include "RPDB_DatabaseReadWriteSettingsController.h"

#include "RPDB_DatabaseTypeSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DatabaseTypeBtreeSettingsController* RPDB_DatabaseTypeBtreeSettingsController_new( RPDB_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	RPDB_DatabaseTypeBtreeSettingsController*		database_type_btree_settings_controller = calloc( 1, sizeof( RPDB_DatabaseTypeBtreeSettingsController ) );

	database_type_btree_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_btree_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseTypeBtreeSettingsController_free(	RPDB_DatabaseTypeBtreeSettingsController** database_type_btree_settings_controller )	{

	free( *database_type_btree_settings_controller );
	*database_type_btree_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseTypeBtreeSettingsController_parentEnvironment(	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	return database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseTypeBtreeSettingsController_parentDatabase(	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	return database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/*****************************
*  recordNumberRetrieval  *
*****************************/

//	DB_RECNUM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPDB_DatabaseTypeBtreeSettingsController_recordNumberRetrieval( RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	if ( database_type_btree_settings_controller->record_number_retrieval )	{
		return DB_RECNUM;
	}
	return FALSE;
}

	/************************************
	*  turnRecordNumberRetrievalOn  *
	************************************/

	void RPDB_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOn( RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->record_number_retrieval = TRUE;
	}

	/*************************************
	*  turnRecordNumberRetrievalOff  *
	*************************************/

	void RPDB_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOff( RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->record_number_retrieval = FALSE;
	}

/*************************
*  reverseSplitting  *
*************************/

//	DB_REVSPLITOFF		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPDB_DatabaseTypeBtreeSettingsController_reverseSplitting( RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	if ( database_type_btree_settings_controller->reverse_splitting )	{

		return DB_REVSPLITOFF;
	}	

	return FALSE;
}

	/******************************
	*  turnReverseSplittingOn  *
	******************************/

	void RPDB_DatabaseTypeBtreeSettingsController_turnReverseSplittingOn( RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->reverse_splitting = TRUE;
	}

	/********************************
	*  turnReverseSplittingOff  *
	********************************/
	void RPDB_DatabaseTypeBtreeSettingsController_turnReverseSplittingOff( RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->reverse_splitting = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/**************************
*  minimumKeysPerPage  *
**************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_bt_minkey.html
uint32_t RPDB_DatabaseTypeBtreeSettingsController_minimumKeysPerPage( RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	
	RPDB_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= 0;
	
	if ( ! database_type_btree_settings_controller->minimum_keys_per_page
		&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->get_bt_minkey(	database->wrapped_bdb_database,
																					&( database_type_btree_settings_controller->minimum_keys_per_page ) ) ) )	{

			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
														connection_error, 
														"RPDB_DatabaseTypeBtreeSettingsController_minimumKeysPerPage" );
		}
	}
	
	return database_type_btree_settings_controller->minimum_keys_per_page;
}

/******************************
*  setMinimumKeysPerPage  *
******************************/

void RPDB_DatabaseTypeBtreeSettingsController_setMinimumKeysPerPage(	RPDB_DatabaseTypeBtreeSettingsController*	database_type_btree_settings_controller,
																		uint32_t									minimum_keys_per_page )	{

	RPDB_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= 0;

	if ( database->wrapped_bdb_database != NULL )	{
		if ( ( connection_error = database->wrapped_bdb_database->set_bt_minkey(	database->wrapped_bdb_database,
																					minimum_keys_per_page ) ) )	{
			
			RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
														connection_error, 
														"RPDB_DatabaseTypeBtreeSettingsController_minimumKeysPerPage" );
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
void RPDB_DatabaseTypeBtreeSettingsController_setPrefixCompareMethod(	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller,
	 																	int (*prefix_compare_method)(	RPDB_Database*			database, 
																										const RPDB_Data*		data_one, 
																										const RPDB_Data*		data_two ) )	{

	RPDB_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	
	int			connection_error	= 0;

	if ( ( connection_error = database->set_bt_prefix(	database,
	 													( prefix_compare_method == NULL ?
															NULL :
															& RPDB_DatabaseTypeBtreeSettingsController_internal_prefixCompareMethod ) ) ) )	{

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseTypeBtreeSettingsController_prefixCompareMethod" );
	}

	database_type_btree_settings_controller->prefix_compare_method = prefix_compare_method;
}
*/
/****************************
*  prefixCompareMethod  *
****************************/
/*
size_t (*prefix_compare_method)(	RPDB_Database*		database, 
									const DBT*			data_one, 
									const DBT*			data_two ) RPDB_DatabaseTypeBtreeSettingsController_prefixCompareMethod( RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	
	return database_type_btree_settings_controller->prefix_compare_method;
}
*/
/*************************
*  setCompareMethod  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_bt_compare.html
void RPDB_DatabaseTypeBtreeSettingsController_setCompareMethod(	RPDB_DatabaseTypeBtreeSettingsController*	database_type_btree_settings_controller,
 																	int (*compare_method)(	RPDB_Database*			database, 
																							const RPDB_Data*		data_one, 
																							const RPDB_Data*		data_two ) )	{

	RPDB_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	if ( ( connection_error = database->set_bt_compare(	database, 
														( compare_method == NULL ?
															NULL :
															& RPDB_DatabaseTypeBtreeSettingsController_internal_compareMethod ) ) ) )	{

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseTypeBtreeSettingsController_compareMethod" );
	}

	database_type_btree_settings_controller->compare_method = compare_method;
}
*/
/*********************
*  compareMethod  *
*********************/
/*
int (*compare_method)(	RPDB_Database*		database, 
						const DBT*			data_one, 
						const DBT*			data_two ) RPDB_DatabaseTypeBtreeSettingsController_compareMethod( RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	return database_type_btree_settings_controller->compare_method;
}
*/
/**********************************
*  setDuplicateCompareMethod  *
**********************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_dup_compare.html
void RPDB_DatabaseTypeBtreeSettingsController_setDuplicateCompareMethod(	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller,
 																			int (*duplicate_compare_method)(	RPDB_Database*			database, 
																												const RPDB_Data*		data_one, 
																												const RPDB_Data*		data_two ) )	{

	RPDB_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	if ( ( connection_error = database->set_dup_compare(	database, 
															( duplicate_compare_method == NULL ?
																NULL :
																& RPDB_DatabaseTypeBtreeSettingsController_internal_duplicateCompareMethod ) ) ) )	{

		RPDB_ErrorController_internal_throwBDBError(	RPDB_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"RPDB_DatabaseTypeBtreeSettingsController_duplicateCompareMethod" );
	}
	
	database_type_btree_settings_controller->duplicate_compare_method = duplicate_compare_method;
}
*/
/*****************************
*  duplicateCompareMethod  *
*****************************/
/*
int (*duplicate_compare_method)(	RPDB_Database*		database, 
									const DBT*			data_one, 
									const DBT*			data_two ) RPDB_DatabaseTypeBtreeSettingsController_duplicateCompareMethod( RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

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
size_t RPDB_DatabaseTypeBtreeSettingsController_internal_prefixCompareMethod(	DB*				bdb_database, 
																				const DBT*		data_one, 
																				const DBT*		data_two )	{
	
	RPDB_Database*		database	=	RPDB_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );
	
	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller	=	RPDB_DatabaseTypeSettingsController_btreeSettingsController(
																								RPDB_DatabaseSettingsController_databaseTypeSettingsController(
																									RPDB_Database_settingsController( database ) ) );
	
	RPDB_Data*			data_one	=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	NULL, data_one );
	RPDB_Data*			data_two	=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	NULL, data_two );
	
	return *( database_type_btree_settings_controller->prefix_compare_method(	database,
																				data_one,
																				data_two	) );
}
*/
/********************************
*  duplicateCompareMethod  *
********************************/
/*
int RPDB_DatabaseTypeBtreeSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
																				const DBT*		data_one, 
																				const DBT*		data_two)	{

	RPDB_Database*		database	=	RPDB_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller	=	RPDB_DatabaseTypeSettingsController_btreeSettingsController(
																								RPDB_DatabaseSettingsController_databaseTypeSettingsController(
																									RPDB_Database_settingsController( database ) ) );

	RPDB_Data*			data_one	=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	NULL, data_one );
	RPDB_Data*			data_two	=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	NULL, data_two );

	return *( database_type_btree_settings_controller->duplicate_compare_method(	database,
																					data_one,
																					data_two	) );	
}
*/
/********************
*  compareMethod  *
********************/
/*
int RPDB_DatabaseTypeBtreeSettingsController_internal_compareMethod(	DB*				bdb_database, 
																		const DBT*		data_one, 
																		const DBT*		data_two)	{
	
	RPDB_Database*		database	=	RPDB_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller	=	RPDB_DatabaseTypeSettingsController_btreeSettingsController(
																								RPDB_DatabaseSettingsController_databaseTypeSettingsController(
																									RPDB_Database_settingsController( database ) ) );

	RPDB_Data*			data_one	=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	NULL, data_one );
	RPDB_Data*			data_two	=	RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT(	NULL, data_two );

	return *( database_type_btree_settings_controller->compare_method(	database,
																		data_one,
																		data_two	) );
}

*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseTypeBtreeSettingsController* RPDB_DatabaseTypeBtreeSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller_copy	=	RPDB_DatabaseTypeBtreeSettingsController_new( database_type_btree_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_btree_settings_controller_copy->minimum_keys_per_page	=	database_type_btree_settings_controller->minimum_keys_per_page;
	database_type_btree_settings_controller_copy->record_number_retrieval	=	database_type_btree_settings_controller->record_number_retrieval;
	database_type_btree_settings_controller_copy->reverse_splitting	=	database_type_btree_settings_controller->reverse_splitting;

	return database_type_btree_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void RPDB_DatabaseTypeBtreeSettingsController_internal_setFlags(	RPDB_DatabaseTypeBtreeSettingsController*		database_type_btree_settings_controller )	{

	RPDB_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
												RPDB_DatabaseTypeSettingsController_internal_setFlags( database_type_btree_settings_controller->parent_database_type_settings_controller )
												|	RPDB_DatabaseReadWriteSettingsController_duplicates( RPDB_DatabaseSettingsController_readWriteSettingsController( RPDB_Database_settingsController( database ) ) )
												|	RPDB_DatabaseReadWriteSettingsController_sortedDuplicates( RPDB_DatabaseSettingsController_readWriteSettingsController( RPDB_Database_settingsController( database ) ) )
												|	RPDB_DatabaseTypeBtreeSettingsController_recordNumberRetrieval( database_type_btree_settings_controller )
												|	RPDB_DatabaseTypeBtreeSettingsController_reverseSplitting( database_type_btree_settings_controller )	);
}

