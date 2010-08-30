#ifndef RPDB_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_CURSOR_CACHE_PRIORITY_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
   														                                                                        						
BOOL														RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtLeast(							RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority );
BOOL														RPDB_DatabaseCursorCachePrioritySettingsController_internal_isAtMost(							RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller,
																																						DB_CACHE_PRIORITY										cache_priority );
   														                                                                            					
BOOL														RPDB_DatabaseCursorCachePrioritySettingsController_internal_isPriority(						RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority );
void													RPDB_DatabaseCursorCachePrioritySettingsController_internal_setPriorityTo(						RPDB_DatabaseCursorCachePrioritySettingsController*	cursor_cache_priority_settings_controller, 
																																						DB_CACHE_PRIORITY										cache_priority );

RPDB_DatabaseCursorCachePrioritySettingsController* RPDB_DatabaseCursorCachePrioritySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseCursorCachePrioritySettingsController* database_cursor_cache_priority_settings_controller );

#endif

