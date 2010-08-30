/*
 *		RPDB::RPDB_SettingsController::RPDB_EnvironmentCacheSettingsController
 *
 *
 */

#ifndef RPDB_ENVIRONMENT_CACHE_SETTINGS_CONTROLLER
	#define RPDB_ENVIRONMENT_CACHE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_EnvironmentCacheSettingsController*	RPDB_EnvironmentCacheSettingsController_new(									RPDB_SettingsController*						settings_controller );

	void										RPDB_EnvironmentCacheSettingsController_free(												RPDB_EnvironmentCacheSettingsController**		environment_cache_settings_controller );
	RPDB_Environment*					RPDB_EnvironmentCacheSettingsController_parentEnvironment(				RPDB_EnvironmentCacheSettingsController*		environment_cache_settings_controller );

	BOOL										RPDB_EnvironmentCacheSettingsController_buffering(									RPDB_EnvironmentCacheSettingsController*		cache_settings_controller );
	void										RPDB_EnvironmentCacheSettingsController_turnBufferingOn(						RPDB_EnvironmentCacheSettingsController*		cache_settings_controller );
	void										RPDB_EnvironmentCacheSettingsController_turnBufferingOff(						RPDB_EnvironmentCacheSettingsController*		cache_settings_controller );

	uint64_t RPDB_EnvironmentCacheSettingsController_sizeInBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller );
	double RPDB_EnvironmentCacheSettingsController_sizeInKBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller );
	double RPDB_EnvironmentCacheSettingsController_sizeInMBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller );
	double RPDB_EnvironmentCacheSettingsController_sizeInGBytes( RPDB_EnvironmentCacheSettingsController* cache_settings_controller );
	void RPDB_EnvironmentCacheSettingsController_setSizeInBytes(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint32_t																	size_in_bytes );
	void RPDB_EnvironmentCacheSettingsController_setSizeInKBytes( RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint32_t																	size_kbytes  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInMBytes( RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint32_t																	size_mbytes  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInGBytes( RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint32_t																	size_gbytes  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInGBytesMBytesKBytesBytes(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																									uint32_t																	size_gbytes, 
																																									uint32_t																	additional_size_mbytes, 
																																									uint32_t																	additional_size_kbytes, 
																																									uint32_t																	additional_size_in_bytes  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInMBytesKBytesBytes(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_mbytes, 
																																						uint32_t																	additional_size_kbytes, 
																																						uint32_t																	additional_size_in_bytes  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInKBytesBytes( RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																		uint32_t																		size_kbytes, 
																																		uint32_t																		additional_size_in_bytes  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint32_t																	size_in_bytes,
																																					int																				number_of_regions );
	void RPDB_EnvironmentCacheSettingsController_setSizeInKBytesWithRegions(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_kbytes,
																																						int																				number_of_regions  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInMBytesWithRegions( RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_mbytes,
																																						int																				number_of_regions  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInGBytesWithRegions(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_gbytes,
																																						int																				number_of_regions  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInGBytesMBytesKBytesBytesWithRegions(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																														uint32_t																	size_gbytes, 
																																														uint32_t																	additional_size_mbytes, 
																																														uint32_t																	additional_size_kbytes, 
																																														uint32_t																	additional_size_in_bytes,
																																														int																				number_of_regions  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInMBytesKBytesBytesWithRegions(	RPDB_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																											uint32_t																	size_mbytes, 
																																											uint32_t																	additional_size_kbytes, 
																																											uint32_t																	additional_size_in_bytes,
																																											int																				number_of_regions  );
	void RPDB_EnvironmentCacheSettingsController_setSizeInKBytesBytesWithRegions( RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																								uint32_t																		size_kbytes, 
																																								uint32_t																		additional_size_in_bytes,
																																								int																					number_of_regions  );

	uint64_t									RPDB_EnvironmentCacheSettingsController_maxSizeInBytes(						RPDB_EnvironmentCacheSettingsController*		cache_settings_controller );
	double										RPDB_EnvironmentCacheSettingsController_maxSizeInKBytes(						RPDB_EnvironmentCacheSettingsController*		cache_settings_controller );
	double										RPDB_EnvironmentCacheSettingsController_maxSizeInMBytes(						RPDB_EnvironmentCacheSettingsController*		cache_settings_controller );
	double										RPDB_EnvironmentCacheSettingsController_maxSizeInGBytes(						RPDB_EnvironmentCacheSettingsController*		cache_settings_controller );
	void										RPDB_EnvironmentCacheSettingsController_setMaxSizeInBytes(						RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, uint32_t max_size_in_bytes );
	void										RPDB_EnvironmentCacheSettingsController_setMaxSizeInKBytes(					RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, uint32_t max_size_kbytes );
	void										RPDB_EnvironmentCacheSettingsController_setMaxSizeInMBytes(					RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, uint32_t max_size_mbytes );
	void										RPDB_EnvironmentCacheSettingsController_setMaxSizeInGBytes(					RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, uint32_t max_size_gbytes );
	void										RPDB_EnvironmentCacheSettingsController_setMaxSizeInGBytesMBytesKBytesBytes(	RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																uint32_t										max_size_gbytes, 
																																uint32_t										additional_max_size_mbytes, 
																																uint32_t										additional_max_size_kbytes, 
																																uint32_t										additional_max_size_in_bytes );
	void										RPDB_EnvironmentCacheSettingsController_setMaxSizeInMBytesKBytesBytes(			RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																uint32_t										max_size_bytes, 
																																uint32_t										additional_max_size_kbytes, 
																																uint32_t										additional_max_size_in_bytes );
	void										RPDB_EnvironmentCacheSettingsController_setMaxSizeInKBytesBytes(				RPDB_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																uint32_t										max_size_kbytes, 
																																uint32_t										additional_max_size_in_bytes );


#endif

