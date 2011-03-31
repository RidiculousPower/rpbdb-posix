#ifndef RPBDB_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
   														                                                                        						
BOOL														RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast(							RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority );
BOOL														RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost(							RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller,
																																						DB_CACHE_PRIORITY										cache_priority );
   														                                                                            					
BOOL														RPbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority(						RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority );
void													RPbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo(						RPbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority );

RPbdb_DatabaseCursorCachePrioritySettingsController* RPbdb_DatabaseCursorCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );

#endif

