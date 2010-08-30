#ifndef RPDB_DATABASE_CURSOR_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_CURSOR_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPDB_DatabaseCursorController* RPDB_DatabaseCursorController_internal_newWithoutRuntimeStorage( RPDB_Database* parent_database );
char* RPDB_DatabaseCursorController_internal_uniqueIdentifier( RPDB_DatabaseCursorController* database_cursor_controller );

#endif
