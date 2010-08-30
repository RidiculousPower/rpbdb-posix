#ifndef RPDB_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

        										                                                    										                              	                	
DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_internal_isAtLeast(							RPDB_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_internal_isAtMost(							RPDB_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
        										                                                        					                                              	                	
DB_CACHE_PRIORITY								RPDB_DatabaseCachePrioritySettingsController_internal_isPriority(							RPDB_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
void											RPDB_DatabaseCachePrioritySettingsController_internal_setPriorityTo(						RPDB_DatabaseCachePrioritySettingsController*		database_cache_priority_settings_controller, 
																																			DB_CACHE_PRIORITY									cache_priority );
                                                                                                                                                                                          		
RPDB_DatabaseCachePrioritySettingsController* RPDB_DatabaseCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCachePrioritySettingsController* database_cache_priority_settings_controller );

#endif
