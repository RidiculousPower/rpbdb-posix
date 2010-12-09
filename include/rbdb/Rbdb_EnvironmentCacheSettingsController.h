/*
 *		Rbdb::Rbdb_SettingsController::Rbdb_EnvironmentCacheSettingsController
 *
 *
 */

#ifndef Rbdb_ENVIRONMENT_CACHE_SETTINGS_CONTROLLER
	#define Rbdb_ENVIRONMENT_CACHE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_EnvironmentCacheSettingsController*	Rbdb_EnvironmentCacheSettingsController_new(									Rbdb_SettingsController*						settings_controller );

	void										Rbdb_EnvironmentCacheSettingsController_free(												Rbdb_EnvironmentCacheSettingsController**		environment_cache_settings_controller );
	Rbdb_Environment*					Rbdb_EnvironmentCacheSettingsController_parentEnvironment(				Rbdb_EnvironmentCacheSettingsController*		environment_cache_settings_controller );

	BOOL										Rbdb_EnvironmentCacheSettingsController_buffering(									Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	void										Rbdb_EnvironmentCacheSettingsController_turnBufferingOn(						Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	void										Rbdb_EnvironmentCacheSettingsController_turnBufferingOff(						Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller );

	uint64_t Rbdb_EnvironmentCacheSettingsController_sizeInBytes( Rbdb_EnvironmentCacheSettingsController* cache_settings_controller );
	double Rbdb_EnvironmentCacheSettingsController_sizeInKBytes( Rbdb_EnvironmentCacheSettingsController* cache_settings_controller );
	double Rbdb_EnvironmentCacheSettingsController_sizeInMBytes( Rbdb_EnvironmentCacheSettingsController* cache_settings_controller );
	double Rbdb_EnvironmentCacheSettingsController_sizeInGBytes( Rbdb_EnvironmentCacheSettingsController* cache_settings_controller );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInBytes(	Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint64_t																	size_in_bytes );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInKBytes( Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint32_t																	size_kbytes  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInMBytes( Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint32_t																	size_mbytes  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInGBytes( Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																uint32_t																	size_gbytes  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInGBytesMBytesKBytesBytes(	Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																									uint32_t																	size_gbytes, 
																																									uint32_t																	additional_size_mbytes, 
																																									uint32_t																	additional_size_kbytes, 
																																									uint32_t																	additional_size_in_bytes  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInMBytesKBytesBytes(	Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_mbytes, 
																																						uint32_t																	additional_size_kbytes, 
																																						uint32_t																	additional_size_in_bytes  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInKBytesBytes( Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																		uint32_t																		size_kbytes, 
																																		uint32_t																		additional_size_in_bytes  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInBytesWithRegions(	Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																					uint64_t																	size_in_bytes,
																																					int																				number_of_regions );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInKBytesWithRegions(	Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_kbytes,
																																						int																				number_of_regions  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInMBytesWithRegions( Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_mbytes,
																																						int																				number_of_regions  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInGBytesWithRegions(	Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																						uint32_t																	size_gbytes,
																																						int																				number_of_regions  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInGBytesMBytesKBytesBytesWithRegions(	Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																														uint32_t																	size_gbytes, 
																																														uint32_t																	additional_size_mbytes, 
																																														uint32_t																	additional_size_kbytes, 
																																														uint32_t																	additional_size_in_bytes,
																																														int																				number_of_regions  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInMBytesKBytesBytesWithRegions(	Rbdb_EnvironmentCacheSettingsController*	cache_settings_controller, 
																																											uint32_t																	size_mbytes, 
																																											uint32_t																	additional_size_kbytes, 
																																											uint32_t																	additional_size_in_bytes,
																																											int																				number_of_regions  );
	void Rbdb_EnvironmentCacheSettingsController_setSizeInKBytesBytesWithRegions( Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																								uint32_t																		size_kbytes, 
																																								uint32_t																		additional_size_in_bytes,
																																								int																					number_of_regions  );

	uint64_t									Rbdb_EnvironmentCacheSettingsController_maxSizeInBytes(						Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	double										Rbdb_EnvironmentCacheSettingsController_maxSizeInKBytes(						Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	double										Rbdb_EnvironmentCacheSettingsController_maxSizeInMBytes(						Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	double										Rbdb_EnvironmentCacheSettingsController_maxSizeInGBytes(						Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller );
	void										Rbdb_EnvironmentCacheSettingsController_setMaxSizeInBytes(						Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller, uint64_t max_size_in_bytes );
	void										Rbdb_EnvironmentCacheSettingsController_setMaxSizeInKBytes(					Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller, uint32_t max_size_kbytes );
	void										Rbdb_EnvironmentCacheSettingsController_setMaxSizeInMBytes(					Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller, uint32_t max_size_mbytes );
	void										Rbdb_EnvironmentCacheSettingsController_setMaxSizeInGBytes(					Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller, uint32_t max_size_gbytes );
	void										Rbdb_EnvironmentCacheSettingsController_setMaxSizeInGBytesMBytesKBytesBytes(	Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																uint32_t										max_size_gbytes, 
																																uint32_t										additional_max_size_mbytes, 
																																uint32_t										additional_max_size_kbytes, 
																																uint32_t										additional_max_size_in_bytes );
	void										Rbdb_EnvironmentCacheSettingsController_setMaxSizeInMBytesKBytesBytes(			Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																uint32_t										max_size_bytes, 
																																uint32_t										additional_max_size_kbytes, 
																																uint32_t										additional_max_size_in_bytes );
	void										Rbdb_EnvironmentCacheSettingsController_setMaxSizeInKBytesBytes(				Rbdb_EnvironmentCacheSettingsController*		cache_settings_controller, 
																																uint32_t										max_size_kbytes, 
																																uint32_t										additional_max_size_in_bytes );


#endif

