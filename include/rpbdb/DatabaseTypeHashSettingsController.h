/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeHashSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseTypeHashSettingsController*								RPbdb_DatabaseTypeHashSettingsController_new(							RPbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller );
	void																	RPbdb_DatabaseTypeHashSettingsController_free(	RPbdb_DatabaseTypeHashSettingsController** database_type_hash_settings_controller );
	RPbdb_Environment*												RPbdb_DatabaseTypeHashSettingsController_parentEnvironment(	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller );
	RPbdb_Database* RPbdb_DatabaseTypeHashSettingsController_parentDatabase(	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller );

	uint32_t																RPbdb_DatabaseTypeHashSettingsController_tableSize(						RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	RPbdb_DatabaseTypeHashSettingsController_setTableSize(					RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller, 
																																					uint32_t													number_of_elements );
	uint32_t																RPbdb_DatabaseTypeHashSettingsController_hashDensityFactor(				RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	RPbdb_DatabaseTypeHashSettingsController_setHashDensityFactor(			RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller, 
																																					uint32_t													density );
	void*																	RPbdb_DatabaseTypeHashSettingsController_setHashMethod(					RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void*																	RPbdb_DatabaseTypeHashSettingsController_setCompareMethod(				RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	RPbdb_DatabaseTypeHashSettingsController_setDuplicateCompareMethod(		RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
/*
	void																	RPbdb_DatabaseTypeHashSettingsController_setHashMethod(					RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller,
																																					int (*hash_method)(	RPbdb_Database*							database, 
																																										const void*								bytes, 
																																										uint32_t								length ) );
	uint32_t (*hash_method)(			RPbdb_Database*		database,                                                           				                                                			
										const void*			bytes,                                                              				                                                			
										uint32_t			length )		RPbdb_DatabaseTypeHashSettingsController_hashMethod(					RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	RPbdb_DatabaseTypeHashSettingsController_setCompareMethod(				RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller,
																																					int (*compare_method)(	RPbdb_Database*						database, 
																																											const RPbdb_Data*					data_one, 
																																											const RPbdb_Data*					data_two ) );
	int (*compare_method)(				RPbdb_Database*		database, 
										const DBT*			data_one, 
										const DBT*			data_two )		RPbdb_DatabaseTypeHashSettingsController_compareMethod(					RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	RPbdb_DatabaseTypeHashSettingsController_setDuplicateCompareMethod(		RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller,
																																					int (*duplicate_compare_method)(	RPbdb_Database*			database, 
																																														const RPbdb_Data*		data_one, 
																																														const RPbdb_Data*		data_two ) );
	int (*duplicate_compare_method)(	RPbdb_Database*		database,   	
										const DBT*			data_one,       	
										const DBT*			data_two )		RPbdb_DatabaseTypeHashSettingsController_duplicateCompareMethod(		RPbdb_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );


*/
#endif

