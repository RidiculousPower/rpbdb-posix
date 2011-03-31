/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeBtreeSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseTypeBtreeSettingsController*							RPbdb_DatabaseTypeBtreeSettingsController_new(								RPbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller );

	void																RPbdb_DatabaseTypeBtreeSettingsController_free(	RPbdb_DatabaseTypeBtreeSettingsController** database_type_btree_settings_controller );
	RPbdb_Environment*											RPbdb_DatabaseTypeBtreeSettingsController_parentEnvironment(	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller );
	RPbdb_Database* RPbdb_DatabaseTypeBtreeSettingsController_parentDatabase(	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller );
																																																				
	BOOL																RPbdb_DatabaseTypeBtreeSettingsController_recordNumberRetrieval(			RPbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																RPbdb_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOn(		RPbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																RPbdb_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOff(		RPbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
																																																				
	BOOL																RPbdb_DatabaseTypeBtreeSettingsController_reverseSplitting(					RPbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																RPbdb_DatabaseTypeBtreeSettingsController_turnReverseSplittingOn(			RPbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																RPbdb_DatabaseTypeBtreeSettingsController_turnReverseSplittingOff(			RPbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
																																																				
	uint32_t															RPbdb_DatabaseTypeBtreeSettingsController_minimumKeysPerPage(				RPbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																RPbdb_DatabaseTypeBtreeSettingsController_setMinimumKeysPerPage(			RPbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller,
																																					uint32_t													minimum_keys_per_page );
																																																				
/*
	void																RPbdb_DatabaseTypeBtreeSettingsController_setPrefixCompareMethod(			RPbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller																																			,
																																					int (*prefix_compare_method)(	RPbdb_Database*				database, 
																																													const RPbdb_Data*			data_one, 
																																													const RPbdb_Data*			data_two ) );
	size_t (*prefix_compare_method)(	RPbdb_Database*		database,                                                                                                                           		
										const DBT*			data_one,                                                                                                                               		
										const DBT*			data_two )		RPbdb_DatabaseTypeBtreeSettingsController_prefixCompareMethod(				RPbdb_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller );
																																																				
	void																	RPbdb_DatabaseTypeBtreeSettingsController_setCompareMethod(					RPbdb_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller,
																																						int (*compare_method)(	RPbdb_Database*					database, 
																																												const DBT*						data_one, 
																																												const DBT*						data_two ));
	int (*compare_method)(				DBRPbdb_Database*	database, 	                                                                                                                        			
										const DBT*			data_one,                                                                                                                               			
										const DBT*			data_two )		RPbdb_DatabaseTypeBtreeSettingsController_compareMethod(					RPbdb_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller );
																																																				
	void																	RPbdb_DatabaseTypeBtreeSettingsController_setDuplicateCompareMethod(		RPbdb_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller,
																																						int (*duplicate_compare_method)(	RPbdb_Database*		database, 
																																															const DBT*			data_one, 
																																															const DBT*			data_two ) );
	int (*duplicate_compare_method)(	RPbdb_Database*		database,                                                                                                                                   	
										const DBT*			data_one,                                                                                                                                       	
										const DBT*			data_two )		RPbdb_DatabaseTypeBtreeSettingsController_duplicateCompareMethod(			RPbdb_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller );

*/
#endif

