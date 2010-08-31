/*
 *		RPDB::JoinController
 *
 *
 */

#ifndef RPDB_JOINCONTROLLER
	#define RPDB_JOINCONTROLLER

	#include "RPDB_BaseStandardInclude.h"
	
	/****************
	*  Prototypes  *
	****************/

RPDB_DatabaseJoinController* RPDB_DatabaseJoinController_new( RPDB_Database* parent_database );

	void							RPDB_DatabaseJoinController_free(	RPDB_DatabaseJoinController** join_controller );
	RPDB_DatabaseJoinSettingsController*	RPDB_DatabaseJoinController_settingsController(	RPDB_DatabaseJoinController* join_controller );
RPDB_Database* RPDB_DatabaseJoinController_parentDatabase(	RPDB_DatabaseJoinController* join_controller );
	RPDB_Environment*		RPDB_DatabaseJoinController_parentEnvironment(	RPDB_DatabaseJoinController* join_controller );

	RPDB_DatabaseJoinCursor*				RPDB_DatabaseJoinController_join(					RPDB_DatabaseJoinController*			join_cursor_controller,
																				RPDB_DatabaseCursor**			cursor_list );
	void							RPDB_DatabaseJoinController_closeAllCursors(		RPDB_DatabaseJoinController*			join_controller );
	void							RPDB_DatabaseJoinController_freeAllCursors(		RPDB_DatabaseJoinController*			join_controller );

#endif

