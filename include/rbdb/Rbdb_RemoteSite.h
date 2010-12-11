/*
 *		Rbdb::DatabaseController::Database::DatabaseCursorController
 *
 *
 */

#ifndef RBDB_REMOTE_SITE
	#define RBDB_REMOTE_SITE

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_RemoteSite*			Rbdb_RemoteSite_new(							Rbdb_ReplicationController*			parent_replication_controller );
	void						Rbdb_RemoteSite_free(							Rbdb_RemoteSite**						remote_site );
	Rbdb_ReplicationSettingsController*	Rbdb_RemoteSite_settingsController(	Rbdb_RemoteSite* remote_site );
	Rbdb_Environment*	Rbdb_RemoteSite_parentEnvironment(	Rbdb_RemoteSite*		remote_site );

#endif

