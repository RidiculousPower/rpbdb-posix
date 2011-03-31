/*
 *		RPbdb::DatabaseController::Database::DatabaseCursorController
 *
 *
 */

#ifndef RPBDB_REMOTE_SITE
	#define RPBDB_REMOTE_SITE

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_RemoteSite*			RPbdb_RemoteSite_new(							RPbdb_ReplicationController*			parent_replication_controller );
	void						RPbdb_RemoteSite_free(							RPbdb_RemoteSite**						remote_site );
	RPbdb_ReplicationSettingsController*	RPbdb_RemoteSite_settingsController(	RPbdb_RemoteSite* remote_site );
	RPbdb_Environment*	RPbdb_RemoteSite_parentEnvironment(	RPbdb_RemoteSite*		remote_site );

#endif

