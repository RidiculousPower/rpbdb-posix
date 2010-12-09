/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeBtreeSettingsController
 *
 *
 */

#ifndef Rbdb_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseTypeBtreeSettingsController*							Rbdb_DatabaseTypeBtreeSettingsController_new(								Rbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller );

	void																Rbdb_DatabaseTypeBtreeSettingsController_free(	Rbdb_DatabaseTypeBtreeSettingsController** database_type_btree_settings_controller );
	Rbdb_Environment*											Rbdb_DatabaseTypeBtreeSettingsController_parentEnvironment(	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller );
	Rbdb_Database* Rbdb_DatabaseTypeBtreeSettingsController_parentDatabase(	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller );
																																																				
	BOOL																Rbdb_DatabaseTypeBtreeSettingsController_recordNumberRetrieval(			Rbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																Rbdb_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOn(		Rbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																Rbdb_DatabaseTypeBtreeSettingsController_turnRecordNumberRetrievalOff(		Rbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
																																																				
	BOOL																Rbdb_DatabaseTypeBtreeSettingsController_reverseSplitting(					Rbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																Rbdb_DatabaseTypeBtreeSettingsController_turnReverseSplittingOn(			Rbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																Rbdb_DatabaseTypeBtreeSettingsController_turnReverseSplittingOff(			Rbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
																																																				
	uint32_t															Rbdb_DatabaseTypeBtreeSettingsController_minimumKeysPerPage(				Rbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller );
	void																Rbdb_DatabaseTypeBtreeSettingsController_setMinimumKeysPerPage(			Rbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller,
																																					uint32_t													minimum_keys_per_page );
																																																				
/*
	void																Rbdb_DatabaseTypeBtreeSettingsController_setPrefixCompareMethod(			Rbdb_DatabaseTypeBtreeSettingsController*					database_type_btree_settings_controller																																			,
																																					int (*prefix_compare_method)(	Rbdb_Database*				database, 
																																													const Rbdb_Data*			data_one, 
																																													const Rbdb_Data*			data_two ) );
	size_t (*prefix_compare_method)(	Rbdb_Database*		database,                                                                                                                           		
										const DBT*			data_one,                                                                                                                               		
										const DBT*			data_two )		Rbdb_DatabaseTypeBtreeSettingsController_prefixCompareMethod(				Rbdb_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller );
																																																				
	void																	Rbdb_DatabaseTypeBtreeSettingsController_setCompareMethod(					Rbdb_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller,
																																						int (*compare_method)(	Rbdb_Database*					database, 
																																												const DBT*						data_one, 
																																												const DBT*						data_two ));
	int (*compare_method)(				DBRbdb_Database*	database, 	                                                                                                                        			
										const DBT*			data_one,                                                                                                                               			
										const DBT*			data_two )		Rbdb_DatabaseTypeBtreeSettingsController_compareMethod(					Rbdb_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller );
																																																				
	void																	Rbdb_DatabaseTypeBtreeSettingsController_setDuplicateCompareMethod(		Rbdb_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller,
																																						int (*duplicate_compare_method)(	Rbdb_Database*		database, 
																																															const DBT*			data_one, 
																																															const DBT*			data_two ) );
	int (*duplicate_compare_method)(	Rbdb_Database*		database,                                                                                                                                   	
										const DBT*			data_one,                                                                                                                                       	
										const DBT*			data_two )		Rbdb_DatabaseTypeBtreeSettingsController_duplicateCompareMethod(			Rbdb_DatabaseTypeBtreeSettingsController*				database_type_btree_settings_controller );

*/
#endif

