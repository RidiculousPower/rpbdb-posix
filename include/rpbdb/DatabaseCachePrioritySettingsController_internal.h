#ifndef RPBDB_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

        										                                                    										                              	                	
DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_internal_isAtLeast(							RPbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_internal_isAtMost(							RPbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
        										                                                        					                                              	                	
DB_CACHE_PRIORITY								RPbdb_DatabaseCachePrioritySettingsController_internal_isPriority(							RPbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
void											RPbdb_DatabaseCachePrioritySettingsController_internal_setPriorityTo(						RPbdb_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
                                                                                                                                                                                          		
RPbdb_DatabaseCachePrioritySettingsController* RPbdb_DatabaseCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller );

#endif
