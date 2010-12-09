#ifndef Rbdb_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	#define Rbdb_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

        										                                                    										                              	                	
DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast(							Rbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_internal_isAtMost(							Rbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
        										                                                        					                                              	                	
DB_CACHE_PRIORITY								Rbdb_DatabaseCachePrioritySettingsController_internal_isPriority(							Rbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
void											Rbdb_DatabaseCachePrioritySettingsController_internal_setPriorityTo(						Rbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
                                                                                                                                                                                          		
Rbdb_DatabaseCachePrioritySettingsController* Rbdb_DatabaseCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller );

#endif
