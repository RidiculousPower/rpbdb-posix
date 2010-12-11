#ifndef RBDB_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
   														                                                                        						
BOOL														Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast(							Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority );
BOOL														Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isAtMost(							Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller,
																																						DB_CACHE_PRIORITY										cache_priority );
   														                                                                            					
BOOL														Rbdb_DatabaseCursorCachePrioritySettingsController_internal_isPriority(						Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority );
void													Rbdb_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo(						Rbdb_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority );

Rbdb_DatabaseCursorCachePrioritySettingsController* Rbdb_DatabaseCursorCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );

#endif

