/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeBtreeSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseTypeBtreeSettingsController.h"

#include "Environment.h"
#include "ErrorController.h"
#include "DatabaseTypeSettingsController.h"
#include "DatabaseSettingsController.h"
#include "Database.h"
#include "Data.h"

#include "DatabaseTypeBtreeSettingsController_internal.h"
#include "RuntimeStorageController_internal.h"
#include "DBT_internal.h"

#include "DatabaseRecordSettingsController.h"
#include "DatabaseRecordReadWriteSettingsController.h"

#include "DatabaseTypeSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseTypeBtreeSettingsController* RPbdb_DatabaseTypeBtreeSettingsController_new( RPbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller )	{

	RPbdb_DatabaseTypeBtreeSettingsController*		database_type_btree_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseTypeBtreeSettingsController ) );

	database_type_btree_settings_controller->parent_database_type_settings_controller = parent_database_type_settings_controller;

	return database_type_btree_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseTypeBtreeSettingsController_free(	RPbdb_DatabaseTypeBtreeSettingsController** database_type_btree_settings_controller )	{

	free( *database_type_btree_settings_controller );
	*database_type_btree_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseTypeBtreeSettingsController_parentEnvironment(	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	return database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseTypeBtreeSettingsController_parentDatabase(	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	return database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database;
}

/*******************************************************************************************************************************************************************************************
																		Switch Settings
*******************************************************************************************************************************************************************************************/

/*****************************
*  recordNumberRetrieval  *
*****************************/

//	DB_RECNUM			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPbdb_DatabaseTypeBtreeSettingsController_recordNumberRetrieval( RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	if ( database_type_btree_settings_controller->record_number_retrieval )	{
		return DB_RECNUM;
	}
	return FALSE;
}

	/************************************
	*  turnRecordNumberRetrievalOn  *
	************************************/

	void RPbdb_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOn( RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->record_number_retrieval = TRUE;
	}

	/*************************************
	*  turnRecordNumberRetrievalOff  *
	*************************************/

	void RPbdb_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOff( RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->record_number_retrieval = FALSE;
	}

/*************************
*  reverseSplitting  *
*************************/

//	DB_REVSPLITOFF		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_flags.html
BOOL RPbdb_DatabaseTypeBtreeSettingsController_reverseSplitting( RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	if ( database_type_btree_settings_controller->reverse_splitting )	{

		return DB_REVSPLITOFF;
	}	

	return FALSE;
}

	/******************************
	*  turnReverseSplittingOn  *
	******************************/

	void RPbdb_DatabaseTypeBtreeSettingsController_turnReverseSplittingOn( RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->reverse_splitting = TRUE;
	}

	/********************************
	*  turnReverseSplittingOff  *
	********************************/
	void RPbdb_DatabaseTypeBtreeSettingsController_turnReverseSplittingOff( RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

		database_type_btree_settings_controller->reverse_splitting = FALSE;
	}

/*******************************************************************************************************************************************************************************************
																		Set Settings
*******************************************************************************************************************************************************************************************/

/**************************
*  minimumKeysPerPage  *
**************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_bt_minkey.html
uint32_t RPbdb_DatabaseTypeBtreeSettingsController_minimumKeysPerPage( RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	
	RPbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= 0;
	
	if ( ! database_type_btree_settings_controller->minimum_keys_per_page
		&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->get_bt_minkey(	database->wrapped_bdb_database,
																					&( database_type_btree_settings_controller->minimum_keys_per_page ) ) ) )	{

			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
														connection_error, 
														"DatabaseTypeBtreeSettingsController_minimumKeysPerPage" );
		}
	}
	
	return database_type_btree_settings_controller->minimum_keys_per_page;
}

/******************************
*  setMinimumKeysPerPage  *
******************************/

void RPbdb_DatabaseTypeBtreeSettingsController_setMinimumKeysPerPage(	RPbdb_DatabaseTypeBtreeSettingsController*	database_type_btree_settings_controller,
																																			uint32_t									minimum_keys_per_page )	{

	RPbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;

	int			connection_error	= 0;

	if (		database != NULL
			&&	database->wrapped_bdb_database != NULL )	{
		
		if ( ( connection_error = database->wrapped_bdb_database->set_bt_minkey(	database->wrapped_bdb_database,
																																							minimum_keys_per_page ) ) )	{
			
			RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
																										connection_error, 
																										"DatabaseTypeBtreeSettingsController_minimumKeysPerPage" );
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
void RPbdb_DatabaseTypeBtreeSettingsController_setPrefixCompareMethod(	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller,
	 																	int (*prefix_compare_method)(	RPbdb_Database*			database, 
																										const RPbdb_Data*		data_one, 
																										const RPbdb_Data*		data_two ) )	{

	RPbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;
	
	int			connection_error	= 0;

	if ( ( connection_error = database->set_bt_prefix(	database,
	 													( prefix_compare_method == NULL ?
															NULL :
															& RPbdb_DatabaseTypeBtreeSettingsController_internal_prefixCompareMethod ) ) ) )	{

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseTypeBtreeSettingsController_prefixCompareMethod" );
	}

	database_type_btree_settings_controller->prefix_compare_method = prefix_compare_method;
}
*/
/****************************
*  prefixCompareMethod  *
****************************/
/*
size_t (*prefix_compare_method)(	RPbdb_Database*		database, 
									const DBT*			data_one, 
									const DBT*			data_two ) RPbdb_DatabaseTypeBtreeSettingsController_prefixCompareMethod( RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{
	
	return database_type_btree_settings_controller->prefix_compare_method;
}
*/
/*************************
*  setCompareMethod  *
*************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_bt_compare.html
void RPbdb_DatabaseTypeBtreeSettingsController_setCompareMethod(	RPbdb_DatabaseTypeBtreeSettingsController*	database_type_btree_settings_controller,
 																	int (*compare_method)(	RPbdb_Database*			database, 
																							const RPbdb_Data*		data_one, 
																							const RPbdb_Data*		data_two ) )	{

	RPbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	if ( ( connection_error = database->set_bt_compare(	database, 
														( compare_method == NULL ?
															NULL :
															& RPbdb_DatabaseTypeBtreeSettingsController_internal_compareMethod ) ) ) )	{

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseTypeBtreeSettingsController_compareMethod" );
	}

	database_type_btree_settings_controller->compare_method = compare_method;
}
*/
/*********************
*  compareMethod  *
*********************/
/*
int (*compare_method)(	RPbdb_Database*		database, 
						const DBT*			data_one, 
						const DBT*			data_two ) RPbdb_DatabaseTypeBtreeSettingsController_compareMethod( RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	return database_type_btree_settings_controller->compare_method;
}
*/
/**********************************
*  setDuplicateCompareMethod  *
**********************************/
/*
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_set_dup_compare.html
void RPbdb_DatabaseTypeBtreeSettingsController_setDuplicateCompareMethod(	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller,
 																			int (*duplicate_compare_method)(	RPbdb_Database*			database, 
																												const RPbdb_Data*		data_one, 
																												const RPbdb_Data*		data_two ) )	{

	RPbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database->wrapped_bdb_database;

	int			connection_error	= 0;

	if ( ( connection_error = database->set_dup_compare(	database, 
															( duplicate_compare_method == NULL ?
																NULL :
																& RPbdb_DatabaseTypeBtreeSettingsController_internal_duplicateCompareMethod ) ) ) )	{

		RPbdb_ErrorController_internal_throwBDBError(	RPbdb_Environment_errorController( database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment ),
													connection_error, 
													"DatabaseTypeBtreeSettingsController_duplicateCompareMethod" );
	}
	
	database_type_btree_settings_controller->duplicate_compare_method = duplicate_compare_method;
}
*/
/*****************************
*  duplicateCompareMethod  *
*****************************/
/*
int (*duplicate_compare_method)(	RPbdb_Database*		database, 
									const DBT*			data_one, 
									const DBT*			data_two ) RPbdb_DatabaseTypeBtreeSettingsController_duplicateCompareMethod( RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

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
size_t RPbdb_DatabaseTypeBtreeSettingsController_internal_prefixCompareMethod(	DB*				bdb_database, 
																				const DBT*		data_one, 
																				const DBT*		data_two )	{
	
	RPbdb_Database*		database	=	RPbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );
	
	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller	=	RPbdb_DatabaseTypeSettingsController_btreeSettingsController(
																								RPbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									RPbdb_Database_settingsController( database ) ) );
	
	RPbdb_Data*			data_one	=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT(	NULL, data_one );
	RPbdb_Data*			data_two	=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT(	NULL, data_two );
	
	return *( database_type_btree_settings_controller->prefix_compare_method(	database,
																				data_one,
																				data_two	) );
}
*/
/********************************
*  duplicateCompareMethod  *
********************************/
/*
int RPbdb_DatabaseTypeBtreeSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
																				const DBT*		data_one, 
																				const DBT*		data_two)	{

	RPbdb_Database*		database	=	RPbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller	=	RPbdb_DatabaseTypeSettingsController_btreeSettingsController(
																								RPbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									RPbdb_Database_settingsController( database ) ) );

	RPbdb_Data*			data_one	=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT(	NULL, data_one );
	RPbdb_Data*			data_two	=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT(	NULL, data_two );

	return *( database_type_btree_settings_controller->duplicate_compare_method(	database,
																					data_one,
																					data_two	) );	
}
*/
/********************
*  compareMethod  *
********************/
/*
int RPbdb_DatabaseTypeBtreeSettingsController_internal_compareMethod(	DB*				bdb_database, 
																		const DBT*		data_one, 
																		const DBT*		data_two)	{
	
	RPbdb_Database*		database	=	RPbdb_RuntimeStorageController_internal_databaseForBDBDatabase( bdb_database );

	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller	=	RPbdb_DatabaseTypeSettingsController_btreeSettingsController(
																								RPbdb_DatabaseSettingsController_databaseTypeSettingsController(
																									RPbdb_Database_settingsController( database ) ) );

	RPbdb_Data*			data_one	=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT(	NULL, data_one );
	RPbdb_Data*			data_two	=	(RPbdb_Data*) RPbdb_DBT_internal_newFromBDBDBT(	NULL, data_two );

	return *( database_type_btree_settings_controller->compare_method(	database,
																		data_one,
																		data_two	) );
}

*/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseTypeBtreeSettingsController* RPbdb_DatabaseTypeBtreeSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller )	{

	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller_copy	=	RPbdb_DatabaseTypeBtreeSettingsController_new( database_type_btree_settings_controller->parent_database_type_settings_controller );

	//	Instances and Pointers
	database_type_btree_settings_controller_copy->minimum_keys_per_page	=	database_type_btree_settings_controller->minimum_keys_per_page;
	database_type_btree_settings_controller_copy->record_number_retrieval	=	database_type_btree_settings_controller->record_number_retrieval;
	database_type_btree_settings_controller_copy->reverse_splitting	=	database_type_btree_settings_controller->reverse_splitting;

	return database_type_btree_settings_controller_copy;
}

/****************
*  setFlags  *
***************/

void RPbdb_DatabaseTypeBtreeSettingsController_internal_setFlags(	RPbdb_DatabaseTypeBtreeSettingsController*		database_type_btree_settings_controller )	{

	RPbdb_Database*			database = database_type_btree_settings_controller->parent_database_type_settings_controller->parent_database_settings_controller->parent_database;
	
	RPbdb_DatabaseSettingsController*									database_settings_controller										=	RPbdb_Database_settingsController( database );
	RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller							=	RPbdb_DatabaseSettingsController_recordSettingsController( database_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller	=	RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( database_record_settings_controller );
	
	database->wrapped_bdb_database->set_flags(	database->wrapped_bdb_database,
												RPbdb_DatabaseTypeSettingsController_internal_setFlags( database_type_btree_settings_controller->parent_database_type_settings_controller )
												|	RPbdb_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( database_record_read_write_settings_controller )
												|	RPbdb_DatabaseRecordReadWriteSettingsController_sortedDuplicates( database_record_read_write_settings_controller )
												|	RPbdb_DatabaseTypeBtreeSettingsController_recordNumberRetrieval( database_type_btree_settings_controller )
												|	RPbdb_DatabaseTypeBtreeSettingsController_reverseSplitting( database_type_btree_settings_controller )	);
}

