/*
 *		RPDB::JoinController::JoinCursor
 *
 *
 */

#ifndef RPDB_JOIN_CURSOR
	#define RPDB_JOIN_CURSOR

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseJoinCursor*				RPDB_DatabaseJoinCursor_new(								RPDB_DatabaseJoinController*		parent_join_controller );

	void							RPDB_DatabaseJoinCursor_free(	RPDB_DatabaseJoinCursor** join_cursor );
	RPDB_DatabaseJoinSettingsController*		RPDB_DatabaseJoinCursor_settingsController(	RPDB_DatabaseJoinCursor* join_cursor );
	RPDB_Environment*				RPDB_DatabaseJoinCursor_parentEnvironment(	RPDB_DatabaseJoinCursor* join_cursor );
RPDB_DatabaseJoinController* RPDB_DatabaseJoinCursor_parentDatabaseJoinController(	RPDB_DatabaseJoinCursor* join_cursor );
RPDB_Database* RPDB_DatabaseJoinCursor_parentDatabase(	RPDB_DatabaseJoinCursor* join_cursor );

BOOL RPDB_DatabaseJoinCursor_isOpen( RPDB_DatabaseJoinCursor* join_cursor );
	void							RPDB_DatabaseJoinCursor_close(								RPDB_DatabaseJoinCursor*			join_cursor );
	RPDB_Record*					RPDB_DatabaseJoinCursor_retrieveKey(				RPDB_DatabaseJoinCursor*			join_cursor,
	 																	  				RPDB_Key*					key	);
	RPDB_Record* RPDB_DatabaseJoinCursor_iterate(	RPDB_DatabaseJoinCursor*	join_cursor );
	RPDB_Record*					RPDB_DatabaseJoinCursor_retrievePrimaryKeysForJoinData(	RPDB_DatabaseJoinCursor*			join_cursor );
	RPDB_DatabaseJoinSettingsController*	RPDB_DatabaseJoinCursor_settingsController(				RPDB_DatabaseJoinCursor*			join_cursor );


#endif

