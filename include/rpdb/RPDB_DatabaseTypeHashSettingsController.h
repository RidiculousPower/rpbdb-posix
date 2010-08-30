/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeHashSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseTypeHashSettingsController*								RPDB_DatabaseTypeHashSettingsController_new(							RPDB_DatabaseTypeSettingsController*						parent_database_type_settings_controller );
	void																	RPDB_DatabaseTypeHashSettingsController_free(	RPDB_DatabaseTypeHashSettingsController** database_type_hash_settings_controller );
	RPDB_Environment*												RPDB_DatabaseTypeHashSettingsController_parentEnvironment(	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller );
	RPDB_Database* RPDB_DatabaseTypeHashSettingsController_parentDatabase(	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller );

	uint32_t																RPDB_DatabaseTypeHashSettingsController_tableSize(						RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	RPDB_DatabaseTypeHashSettingsController_setTableSize(					RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller, 
																																					uint32_t													number_of_elements );
	uint32_t																RPDB_DatabaseTypeHashSettingsController_hashDensityFactor(				RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	RPDB_DatabaseTypeHashSettingsController_setHashDensityFactor(			RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller, 
																																					uint32_t													density );
	void*																	RPDB_DatabaseTypeHashSettingsController_setHashMethod(					RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void*																	RPDB_DatabaseTypeHashSettingsController_setCompareMethod(				RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	RPDB_DatabaseTypeHashSettingsController_setDuplicateCompareMethod(		RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
/*
	void																	RPDB_DatabaseTypeHashSettingsController_setHashMethod(					RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller,
																																					int (*hash_method)(	RPDB_Database*							database, 
																																										const void*								bytes, 
																																										uint32_t								length ) );
	uint32_t (*hash_method)(			RPDB_Database*		database,                                                           				                                                			
										const void*			bytes,                                                              				                                                			
										uint32_t			length )		RPDB_DatabaseTypeHashSettingsController_hashMethod(					RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	RPDB_DatabaseTypeHashSettingsController_setCompareMethod(				RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller,
																																					int (*compare_method)(	RPDB_Database*						database, 
																																											const RPDB_Data*					data_one, 
																																											const RPDB_Data*					data_two ) );
	int (*compare_method)(				RPDB_Database*		database, 
										const DBT*			data_one, 
										const DBT*			data_two )		RPDB_DatabaseTypeHashSettingsController_compareMethod(					RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );
	void																	RPDB_DatabaseTypeHashSettingsController_setDuplicateCompareMethod(		RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller,
																																					int (*duplicate_compare_method)(	RPDB_Database*			database, 
																																														const RPDB_Data*		data_one, 
																																														const RPDB_Data*		data_two ) );
	int (*duplicate_compare_method)(	RPDB_Database*		database,   	
										const DBT*			data_one,       	
										const DBT*			data_two )		RPDB_DatabaseTypeHashSettingsController_duplicateCompareMethod(		RPDB_DatabaseTypeHashSettingsController*					database_type_hash_settings_controller );


*/
#endif

