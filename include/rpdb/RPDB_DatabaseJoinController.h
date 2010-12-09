/*
 *		Rbdb::JoinController
 *
 *
 */

#ifndef Rbdb_JOINCONTROLLER
	#define Rbdb_JOINCONTROLLER

	#include "Rbdb_BaseStandardInclude.h"
	
	/****************
	*  Prototypes  *
	****************/

Rbdb_DatabaseJoinController* Rbdb_DatabaseJoinController_new( Rbdb_Database* parent_database );

	void							Rbdb_DatabaseJoinController_free(	Rbdb_DatabaseJoinController** join_controller );
	Rbdb_DatabaseJoinSettingsController*	Rbdb_DatabaseJoinController_settingsController(	Rbdb_DatabaseJoinController* join_controller );
Rbdb_Database* Rbdb_DatabaseJoinController_parentDatabase(	Rbdb_DatabaseJoinController* join_controller );
	Rbdb_Environment*		Rbdb_DatabaseJoinController_parentEnvironment(	Rbdb_DatabaseJoinController* join_controller );

	Rbdb_DatabaseJoinCursor*				Rbdb_DatabaseJoinController_join(					Rbdb_DatabaseJoinController*			join_cursor_controller,
																				Rbdb_DatabaseCursor**			cursor_list );
	void							Rbdb_DatabaseJoinController_closeAllCursors(		Rbdb_DatabaseJoinController*			join_controller );
	void							Rbdb_DatabaseJoinController_freeAllCursors(		Rbdb_DatabaseJoinController*			join_controller );

#endif

