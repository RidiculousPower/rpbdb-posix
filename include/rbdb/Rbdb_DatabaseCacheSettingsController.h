/*
 *		Rbdb::Rbdb_SettingsController::Rbdb_DatabaseCacheSettingsController
 *
 *
 */

#ifndef RBDB_DATABASE_CACHE_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_CACHE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
		
	Rbdb_DatabaseCacheSettingsController*	Rbdb_DatabaseCacheSettingsController_new(											Rbdb_DatabaseSettingsController*			database_settings_controller );

	void									Rbdb_DatabaseCacheSettingsController_free(	Rbdb_DatabaseCacheSettingsController** database_cache_settings_controller );
	Rbdb_Environment*				Rbdb_DatabaseCacheSettingsController_parentEnvironment(	Rbdb_DatabaseCacheSettingsController* database_cache_settings_controller );
	Rbdb_Database* Rbdb_DatabaseCacheSettingsController_parentDatabase(	Rbdb_DatabaseCacheSettingsController* database_cache_settings_controller );

	void									Rbdb_DatabaseCacheSettingsController_internal_initDefaultSettings(							Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	uint64_t								Rbdb_DatabaseCacheSettingsController_maxSizeInBytes(								Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	long									Rbdb_DatabaseCacheSettingsController_maxSizeInKBytes(								Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	long									Rbdb_DatabaseCacheSettingsController_maxSizeInMBytes(								Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	long									Rbdb_DatabaseCacheSettingsController_maxSizeInGBytes(								Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	void									Rbdb_DatabaseCacheSettingsController_setMaxSizeInBytes(							Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_in_bytes );
	void									Rbdb_DatabaseCacheSettingsController_setMaxSizeInKBytes(							Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_kbytes );
	void									Rbdb_DatabaseCacheSettingsController_setMaxSizeInMBytes(							Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_mbytes );
	void									Rbdb_DatabaseCacheSettingsController_setMaxSizeInGBytes(							Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_gbytes );
	void									Rbdb_DatabaseCacheSettingsController_setMaxSizeInGBytesMBytesKBytesBytes(			Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_gbytes, 
																																uint32_t									additional_max_size_mbytes, 
																																uint32_t									additional_max_size_kbytes, 
																																uint32_t									additional_max_size_in_bytes );
	void									Rbdb_DatabaseCacheSettingsController_setMaxSizeInMBytesKBytesBytes(				Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_mbytes, 
																																uint32_t									additional_max_size_kbytes, 
																																uint32_t									additional_max_size_in_bytes );
	void									Rbdb_DatabaseCacheSettingsController_setMaxSizeInKBytesBytes(						Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_kbytes, 
																																uint32_t									additional_max_size_in_bytes );
	int										Rbdb_DatabaseCacheSettingsController_numberCacheRegions(							Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	void									Rbdb_DatabaseCacheSettingsController_setNumberCacheRegions(						Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																int											number_cache_regions );		
	Rbdb_DatabaseCachePrioritySettingsController*	Rbdb_DatabaseCacheSettingsController_priorityController(							Rbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );

#endif

