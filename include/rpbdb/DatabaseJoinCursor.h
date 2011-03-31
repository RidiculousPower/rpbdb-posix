/*
 *		RPbdb::JoinController::JoinCursor
 *
 *
 */

#ifndef RPBDB_JOIN_CURSOR
	#define RPBDB_JOIN_CURSOR

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseJoinCursor*				RPbdb_DatabaseJoinCursor_new(								RPbdb_DatabaseJoinController*		parent_join_controller );

	void							RPbdb_DatabaseJoinCursor_free(	RPbdb_DatabaseJoinCursor** join_cursor );
	RPbdb_DatabaseJoinSettingsController*		RPbdb_DatabaseJoinCursor_settingsController(	RPbdb_DatabaseJoinCursor* join_cursor );
	RPbdb_Environment*				RPbdb_DatabaseJoinCursor_parentEnvironment(	RPbdb_DatabaseJoinCursor* join_cursor );
RPbdb_DatabaseJoinController* RPbdb_DatabaseJoinCursor_parentDatabaseJoinController(	RPbdb_DatabaseJoinCursor* join_cursor );
RPbdb_Database* RPbdb_DatabaseJoinCursor_parentDatabase(	RPbdb_DatabaseJoinCursor* join_cursor );

BOOL RPbdb_DatabaseJoinCursor_isOpen( RPbdb_DatabaseJoinCursor* join_cursor );
	void							RPbdb_DatabaseJoinCursor_close(								RPbdb_DatabaseJoinCursor*			join_cursor );
	RPbdb_Record*					RPbdb_DatabaseJoinCursor_retrieveKey(				RPbdb_DatabaseJoinCursor*			join_cursor,
	 																	  				RPbdb_Key*					key	);
	RPbdb_Record* RPbdb_DatabaseJoinCursor_iterate(	RPbdb_DatabaseJoinCursor*	join_cursor );
	RPbdb_Record*					RPbdb_DatabaseJoinCursor_retrievePrimaryKeysForJoinData(	RPbdb_DatabaseJoinCursor*			join_cursor );
	RPbdb_DatabaseJoinSettingsController*	RPbdb_DatabaseJoinCursor_settingsController(				RPbdb_DatabaseJoinCursor*			join_cursor );


#endif

