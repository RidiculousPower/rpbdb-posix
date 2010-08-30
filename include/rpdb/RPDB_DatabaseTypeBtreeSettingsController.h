/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeBtreeSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseTypeBtreeSettingsController*							RPDB_DatabaseTypeBtreeSettingsController_new(								RPDB_DatabaseTypeSettingsController*						parent_database_type_settings_controller );

	void																RPDB_DatabaseTypeBtreeSettingsController_free(	RPDB_DatabaseTypeBtreeSettingsController** database_type_btree_settings_controller );
	RPDB_Environment*											RPDB_DatabaseTypeBtreeSettingsController_parentEnvironment(	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller );
	RPDB_Database* RPDB_DatabaseTypeBtreeSettingsController_parentDatabase(	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller );
																																																				
	BOOL																RPDB_DatabaseTypeBtreeSettingsController_recordNumberRetrieval(			RPDB_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																RPDB_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOn(		RPDB_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																RPDB_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOff(		RPDB_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
																																																				
	BOOL																RPDB_DatabaseTypeBtreeSettingsController_reverseSplitting(					RPDB_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																RPDB_DatabaseTypeBtreeSettingsController_turnReverseSplittingOn(			RPDB_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																RPDB_DatabaseTypeBtreeSettingsController_turnReverseSplittingOff(			RPDB_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
																																																				
	uint32_t															RPDB_DatabaseTypeBtreeSettingsController_minimumKeysPerPage(				RPDB_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																RPDB_DatabaseTypeBtreeSettingsController_setMinimumKeysPerPage(			RPDB_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller,
																																					uint32_t													minimum_keys_per_page );
																																																				
/*
	void																RPDB_DatabaseTypeBtreeSettingsController_setPrefixCompareMethod(			RPDB_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller																																			,
																																					int (*prefix_compare_method)(	RPDB_Database*				database, 
																																													const RPDB_Data*			data_one, 
																																													const RPDB_Data*			data_two ) );
	size_t (*prefix_compare_method)(	RPDB_Database*		database,                                                                                                                           		
										const DBT*			data_one,                                                                                                                               		
										const DBT*			data_two )		RPDB_DatabaseTypeBtreeSettingsController_prefixCompareMethod(				RPDB_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller );
																																																				
	void																	RPDB_DatabaseTypeBtreeSettingsController_setCompareMethod(					RPDB_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller,
																																						int (*compare_method)(	RPDB_Database*					database, 
																																												const DBT*						data_one, 
																																												const DBT*						data_two ));
	int (*compare_method)(				DBRPDB_Database*	database, 	                                                                                                                        			
										const DBT*			data_one,                                                                                                                               			
										const DBT*			data_two )		RPDB_DatabaseTypeBtreeSettingsController_compareMethod(					RPDB_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller );
																																																				
	void																	RPDB_DatabaseTypeBtreeSettingsController_setDuplicateCompareMethod(		RPDB_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller,
																																						int (*duplicate_compare_method)(	RPDB_Database*		database, 
																																															const DBT*			data_one, 
																																															const DBT*			data_two ) );
	int (*duplicate_compare_method)(	RPDB_Database*		database,                                                                                                                                   	
										const DBT*			data_one,                                                                                                                                       	
										const DBT*			data_two )		RPDB_DatabaseTypeBtreeSettingsController_duplicateCompareMethod(			RPDB_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller );

*/
#endif

