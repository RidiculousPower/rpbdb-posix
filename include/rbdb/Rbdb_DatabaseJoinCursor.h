/*
 *		Rbdb::JoinController::JoinCursor
 *
 *
 */

#ifndef RBDB_JOIN_CURSOR
	#define RBDB_JOIN_CURSOR

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseJoinCursor*				Rbdb_DatabaseJoinCursor_new(								Rbdb_DatabaseJoinController*		parent_join_controller );

	void							Rbdb_DatabaseJoinCursor_free(	Rbdb_DatabaseJoinCursor** join_cursor );
	Rbdb_DatabaseJoinSettingsController*		Rbdb_DatabaseJoinCursor_settingsController(	Rbdb_DatabaseJoinCursor* join_cursor );
	Rbdb_Environment*				Rbdb_DatabaseJoinCursor_parentEnvironment(	Rbdb_DatabaseJoinCursor* join_cursor );
Rbdb_DatabaseJoinController* Rbdb_DatabaseJoinCursor_parentDatabaseJoinController(	Rbdb_DatabaseJoinCursor* join_cursor );
Rbdb_Database* Rbdb_DatabaseJoinCursor_parentDatabase(	Rbdb_DatabaseJoinCursor* join_cursor );

BOOL Rbdb_DatabaseJoinCursor_isOpen( Rbdb_DatabaseJoinCursor* join_cursor );
	void							Rbdb_DatabaseJoinCursor_close(								Rbdb_DatabaseJoinCursor*			join_cursor );
	Rbdb_Record*					Rbdb_DatabaseJoinCursor_retrieveKey(				Rbdb_DatabaseJoinCursor*			join_cursor,
	 																	  				Rbdb_Key*					key	);
	Rbdb_Record* Rbdb_DatabaseJoinCursor_iterate(	Rbdb_DatabaseJoinCursor*	join_cursor );
	Rbdb_Record*					Rbdb_DatabaseJoinCursor_retrievePrimaryKeysForJoinData(	Rbdb_DatabaseJoinCursor*			join_cursor );
	Rbdb_DatabaseJoinSettingsController*	Rbdb_DatabaseJoinCursor_settingsController(				Rbdb_DatabaseJoinCursor*			join_cursor );


#endif

