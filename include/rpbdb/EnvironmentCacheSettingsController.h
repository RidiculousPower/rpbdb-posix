/*
 *		RPbdb::RPbdb_SettingsController::RPbdb_EnvironmentCacheSettingsController
 *
 *
 */

#ifndef RPBDB_ENVIRONMENT_CACHE_SETTINGS_CONTROLLER
	#define RPBDB_ENVIRONMENT_CACHE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_EnvironmentCacheSettingsController*	RPbdb_EnvironmentCacheSettingsController_new(									RPbdb_SettingsController*						settings_controller );

	void										RPbdb_EnvironmentCacheSettingsController_free(												RPbdb_EnvironmentCacheSettingsController**		environment_cache_settings_controller );
	RPbdb_Environment*					RPbdb_EnvironmentCacheSettingsController_parentEnvironment(				RPbdb_EnvironmentCacheSettingsController*		environment_cache_settings_controller );

	BOOL										RPbdb_EnvironmentCacheSettingsController_buffering(									RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	void										RPbdb_EnvironmentCacheSettingsController_turnBufferingOn(						RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	void										RPbdb_EnvironmentCacheSettingsController_turnBufferingOff(						RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller );

	uint64_t RPbdb_EnvironmentCacheSettingsController_sizeInBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller );
	double RPbdb_EnvironmentCacheSettingsController_sizeInKBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller );
	double RPbdb_EnvironmentCacheSettingsController_sizeInMBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller );
	double RPbdb_EnvironmentCacheSettingsController_sizeInGBytes( RPbdb_EnvironmentCacheSettingsController* cache_settings_controller );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInBytes(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint64_t																	size_in_bytes );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInKBytes( RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint32_t																	size_kbytes  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInMBytes( RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint32_t																	size_mbytes  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInGBytes( RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint32_t																	size_gbytes  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInGBytesMBytesKBytesBytes(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																									uint32_t																	size_gbytes, 
																																									uint32_t																	additional_size_mbytes, 
																																									uint32_t																	additional_size_kbytes, 
																																									uint32_t																	additional_size_in_bytes  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInMBytesKBytesBytes(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_mbytes, 
																																						uint32_t																	additional_size_kbytes, 
																																						uint32_t																	additional_size_in_bytes  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInKBytesBytes( RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																		uint32_t																		size_kbytes, 
																																		uint32_t																		additional_size_in_bytes  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint64_t																	size_in_bytes,
																																					int																				number_of_regions );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInKBytesWithRegions(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_kbytes,
																																						int																				number_of_regions  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInMBytesWithRegions( RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_mbytes,
																																						int																				number_of_regions  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInGBytesWithRegions(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_gbytes,
																																						int																				number_of_regions  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInGBytesMBytesKBytesBytesWithRegions(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																														uint32_t																	size_gbytes, 
																																														uint32_t																	additional_size_mbytes, 
																																														uint32_t																	additional_size_kbytes, 
																																														uint32_t																	additional_size_in_bytes,
																																														int																				number_of_regions  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInMBytesKBytesBytesWithRegions(	RPbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																											uint32_t																	size_mbytes, 
																																											uint32_t																	additional_size_kbytes, 
																																											uint32_t																	additional_size_in_bytes,
																																											int																				number_of_regions  );
	void RPbdb_EnvironmentCacheSettingsController_setSizeInKBytesBytesWithRegions( RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																								uint32_t																		size_kbytes, 
																																								uint32_t																		additional_size_in_bytes,
																																								int																					number_of_regions  );

	uint64_t									RPbdb_EnvironmentCacheSettingsController_maxSizeInBytes(						RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	double										RPbdb_EnvironmentCacheSettingsController_maxSizeInKBytes(						RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	double										RPbdb_EnvironmentCacheSettingsController_maxSizeInMBytes(						RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	double										RPbdb_EnvironmentCacheSettingsController_maxSizeInGBytes(						RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	void										RPbdb_EnvironmentCacheSettingsController_setMaxSizeInBytes(						RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, uint64_t max_size_in_bytes );
	void										RPbdb_EnvironmentCacheSettingsController_setMaxSizeInKBytes(					RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, uint32_t max_size_kbytes );
	void										RPbdb_EnvironmentCacheSettingsController_setMaxSizeInMBytes(					RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, uint32_t max_size_mbytes );
	void										RPbdb_EnvironmentCacheSettingsController_setMaxSizeInGBytes(					RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, uint32_t max_size_gbytes );
	void										RPbdb_EnvironmentCacheSettingsController_setMaxSizeInGBytesMBytesKBytesBytes(	RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																uint32_t										max_size_gbytes, 
																																uint32_t										additional_max_size_mbytes, 
																																uint32_t										additional_max_size_kbytes, 
																																uint32_t										additional_max_size_in_bytes );
	void										RPbdb_EnvironmentCacheSettingsController_setMaxSizeInMBytesKBytesBytes(			RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																uint32_t										max_size_bytes, 
																																uint32_t										additional_max_size_kbytes, 
																																uint32_t										additional_max_size_in_bytes );
	void										RPbdb_EnvironmentCacheSettingsController_setMaxSizeInKBytesBytes(				RPbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																uint32_t										max_size_kbytes, 
																																uint32_t										additional_max_size_in_bytes );


#endif

