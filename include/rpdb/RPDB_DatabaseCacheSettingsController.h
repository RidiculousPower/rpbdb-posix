/*
 *		RPDB::RPDB_SettingsController::RPDB_DatabaseCacheSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_CACHE_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_CACHE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/
		
	RPDB_DatabaseCacheSettingsController*	RPDB_DatabaseCacheSettingsController_new(											RPDB_DatabaseSettingsController*			database_settings_controller );

	void									RPDB_DatabaseCacheSettingsController_free(	RPDB_DatabaseCacheSettingsController** database_cache_settings_controller );
	RPDB_Environment*				RPDB_DatabaseCacheSettingsController_parentEnvironment(	RPDB_DatabaseCacheSettingsController* database_cache_settings_controller );
	RPDB_Database* RPDB_DatabaseCacheSettingsController_parentDatabase(	RPDB_DatabaseCacheSettingsController* database_cache_settings_controller );

	void									RPDB_DatabaseCacheSettingsController_internal_initDefaultSettings(							RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller );
	uint64_t								RPDB_DatabaseCacheSettingsController_maxSizeInBytes(								RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller );
	long									RPDB_DatabaseCacheSettingsController_maxSizeInKBytes(								RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller );
	long									RPDB_DatabaseCacheSettingsController_maxSizeInMBytes(								RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller );
	long									RPDB_DatabaseCacheSettingsController_maxSizeInGBytes(								RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller );
	void									RPDB_DatabaseCacheSettingsController_setMaxSizeInBytes(							RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_in_bytes );
	void									RPDB_DatabaseCacheSettingsController_setMaxSizeInKBytes(							RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_kbytes );
	void									RPDB_DatabaseCacheSettingsController_setMaxSizeInMBytes(							RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_mbytes );
	void									RPDB_DatabaseCacheSettingsController_setMaxSizeInGBytes(							RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_gbytes );
	void									RPDB_DatabaseCacheSettingsController_setMaxSizeInGBytesMBytesKBytesBytes(			RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_gbytes, 
																																uint32_t									additional_max_size_mbytes, 
																																uint32_t									additional_max_size_kbytes, 
																																uint32_t									additional_max_size_in_bytes );
	void									RPDB_DatabaseCacheSettingsController_setMaxSizeInMBytesKBytesBytes(				RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_mbytes, 
																																uint32_t									additional_max_size_kbytes, 
																																uint32_t									additional_max_size_in_bytes );
	void									RPDB_DatabaseCacheSettingsController_setMaxSizeInKBytesBytes(						RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																uint32_t									max_size_kbytes, 
																																uint32_t									additional_max_size_in_bytes );
	int										RPDB_DatabaseCacheSettingsController_numberCacheRegions(							RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller );
	void									RPDB_DatabaseCacheSettingsController_setNumberCacheRegions(						RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller, 
																																int											number_cache_regions );		
	RPDB_DatabaseCachePrioritySettingsController*	RPDB_DatabaseCacheSettingsController_priorityController(							RPDB_DatabaseCacheSettingsController*		database_cache_settings_controller );

#endif

