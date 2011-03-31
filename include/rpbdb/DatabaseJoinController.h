/*
 *		RPbdb::JoinController
 *
 *
 */

#ifndef RPBDB_JOINCONTROLLER
	#define RPBDB_JOINCONTROLLER

	#include "BaseStandardInclude.h"
	
	/****************
	*  Prototypes  *
	****************/

RPbdb_DatabaseJoinController* RPbdb_DatabaseJoinController_new( RPbdb_Database* parent_database );

	void							RPbdb_DatabaseJoinController_free(	RPbdb_DatabaseJoinController** join_controller );
	RPbdb_DatabaseJoinSettingsController*	RPbdb_DatabaseJoinController_settingsController(	RPbdb_DatabaseJoinController* join_controller );
RPbdb_Database* RPbdb_DatabaseJoinController_parentDatabase(	RPbdb_DatabaseJoinController* join_controller );
	RPbdb_Environment*		RPbdb_DatabaseJoinController_parentEnvironment(	RPbdb_DatabaseJoinController* join_controller );

	RPbdb_DatabaseJoinCursor*				RPbdb_DatabaseJoinController_join(					RPbdb_DatabaseJoinController*			join_cursor_controller,
																				RPbdb_DatabaseCursor**			cursor_list );
	void							RPbdb_DatabaseJoinController_closeAllCursors(		RPbdb_DatabaseJoinController*			join_controller );
	void							RPbdb_DatabaseJoinController_freeAllCursors(		RPbdb_DatabaseJoinController*			join_controller );

#endif

