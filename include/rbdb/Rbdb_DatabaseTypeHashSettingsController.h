/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeHashSettingsController
 *
 *
 */

#ifndef RBDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseTypeHashSettingsController*								Rbdb_DatabaseTypeHashSettingsController_new(							Rbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller );
	void																	Rbdb_DatabaseTypeHashSettingsController_free(	Rbdb_DatabaseTypeHashSettingsController** database_type_hash_settings_controller );
	Rbdb_Environment*												Rbdb_DatabaseTypeHashSettingsController_parentEnvironment(	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller );
	Rbdb_Database* Rbdb_DatabaseTypeHashSettingsController_parentDatabase(	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller );

	uint32_t																Rbdb_DatabaseTypeHashSettingsController_tableSize(						Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	Rbdb_DatabaseTypeHashSettingsController_setTableSize(					Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller, 
																																					uint32_t													number_of_elements );
	uint32_t																Rbdb_DatabaseTypeHashSettingsController_hashDensityFactor(				Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	Rbdb_DatabaseTypeHashSettingsController_setHashDensityFactor(			Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller, 
																																					uint32_t													density );
	void*																	Rbdb_DatabaseTypeHashSettingsController_setHashMethod(					Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void*																	Rbdb_DatabaseTypeHashSettingsController_setCompareMethod(				Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	Rbdb_DatabaseTypeHashSettingsController_setDuplicateCompareMethod(		Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
/*
	void																	Rbdb_DatabaseTypeHashSettingsController_setHashMethod(					Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller,
																																					int (*hash_method)(	Rbdb_Database*							database, 
																																										const void*								bytes, 
																																										uint32_t								length ) );
	uint32_t (*hash_method)(			Rbdb_Database*		database,                                                           				                                                			
										const void*			bytes,                                                              				                                                			
										uint32_t			length )		Rbdb_DatabaseTypeHashSettingsController_hashMethod(					Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	Rbdb_DatabaseTypeHashSettingsController_setCompareMethod(				Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller,
																																					int (*compare_method)(	Rbdb_Database*						database, 
																																											const Rbdb_Data*					data_one, 
																																											const Rbdb_Data*					data_two ) );
	int (*compare_method)(				Rbdb_Database*		database, 
										const DBT*			data_one, 
										const DBT*			data_two )		Rbdb_DatabaseTypeHashSettingsController_compareMethod(					Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	Rbdb_DatabaseTypeHashSettingsController_setDuplicateCompareMethod(		Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller,
																																					int (*duplicate_compare_method)(	Rbdb_Database*			database, 
																																														const Rbdb_Data*		data_one, 
																																														const Rbdb_Data*		data_two ) );
	int (*duplicate_compare_method)(	Rbdb_Database*		database,   	
										const DBT*			data_one,       	
										const DBT*			data_two )		Rbdb_DatabaseTypeHashSettingsController_duplicateCompareMethod(		Rbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );


*/
#endif

