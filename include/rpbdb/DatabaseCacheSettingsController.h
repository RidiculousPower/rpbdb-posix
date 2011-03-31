/*
 *		RPbdb::RPbdb_SettingsController::RPbdb_DatabaseCacheSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_CACHE_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_CACHE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
		
	RPbdb_DatabaseCacheSettingsController*	RPbdb_DatabaseCacheSettingsController_new(											RPbdb_DatabaseSettingsController*			database_settings_controller );

	void									RPbdb_DatabaseCacheSettingsController_free(	RPbdb_DatabaseCacheSettingsController** database_cache_settings_controller );
	RPbdb_Environment*				RPbdb_DatabaseCacheSettingsController_parentEnvironment(	RPbdb_DatabaseCacheSettingsController* database_cache_settings_controller );
	RPbdb_Database* RPbdb_DatabaseCacheSettingsController_parentDatabase(	RPbdb_DatabaseCacheSettingsController* database_cache_settings_controller );

	void									RPbdb_DatabaseCacheSettingsController_internal_initDefaultSettings(							RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	uint64_t								RPbdb_DatabaseCacheSettingsController_maxSizeInBytes(								RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	long									RPbdb_DatabaseCacheSettingsController_maxSizeInKBytes(								RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	long									RPbdb_DatabaseCacheSettingsController_maxSizeInMBytes(								RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	long									RPbdb_DatabaseCacheSettingsController_maxSizeInGBytes(								RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	void									RPbdb_DatabaseCacheSettingsController_setMaxSizeInBytes(							RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_in_bytes );
	void									RPbdb_DatabaseCacheSettingsController_setMaxSizeInKBytes(							RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_kbytes );
	void									RPbdb_DatabaseCacheSettingsController_setMaxSizeInMBytes(							RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_mbytes );
	void									RPbdb_DatabaseCacheSettingsController_setMaxSizeInGBytes(							RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_gbytes );
	void									RPbdb_DatabaseCacheSettingsController_setMaxSizeInGBytesMBytesKBytesBytes(			RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_gbytes, 
																																uint32_t									additional_max_size_mbytes, 
																																uint32_t									additional_max_size_kbytes, 
																																uint32_t									additional_max_size_in_bytes );
	void									RPbdb_DatabaseCacheSettingsController_setMaxSizeInMBytesKBytesBytes(				RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_mbytes, 
																																uint32_t									additional_max_size_kbytes, 
																																uint32_t									additional_max_size_in_bytes );
	void									RPbdb_DatabaseCacheSettingsController_setMaxSizeInKBytesBytes(						RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_kbytes, 
																																uint32_t									additional_max_size_in_bytes );
	int										RPbdb_DatabaseCacheSettingsController_numberCacheRegions(							RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );
	void									RPbdb_DatabaseCacheSettingsController_setNumberCacheRegions(						RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																int											number_cache_regions );		
	RPbdb_DatabaseCachePrioritySettingsController*	RPbdb_DatabaseCacheSettingsController_priorityController(							RPbdb_DatabaseCacheSettingsController*		database_cache_settings_controller );

#endif

