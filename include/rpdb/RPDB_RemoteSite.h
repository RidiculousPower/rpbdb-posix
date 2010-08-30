/*
 *		RPDB::DatabaseController::Database::DatabaseCursorController
 *
 *
 */

#ifndef RPDB_REMOTE_SITE
	#define RPDB_REMOTE_SITE

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_RemoteSite*			RPDB_RemoteSite_new(							RPDB_ReplicationController*			parent_replication_controller );
	void						RPDB_RemoteSite_free(							RPDB_RemoteSite**						remote_site );
	RPDB_ReplicationSettingsController*	RPDB_RemoteSite_settingsController(	RPDB_RemoteSite* remote_site );
	RPDB_Environment*	RPDB_RemoteSite_parentEnvironment(	RPDB_RemoteSite*		remote_site );

#endif

