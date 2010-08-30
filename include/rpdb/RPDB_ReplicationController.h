/*
 *		RPDB::ReplicationController
 *
 *	
 */

#ifndef RPDB_REPLICATION_CONTROLLER
	#define RPDB_REPLICATION_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_ReplicationController*		RPDB_ReplicationController_new(							RPDB_Environment*								environment );
	void								RPDB_ReplicationController_free(							RPDB_ReplicationController** replication_controller );
	RPDB_ReplicationSettingsController*	RPDB_ReplicationController_settingsController(	RPDB_ReplicationController* replication_controller );
	RPDB_Environment*			RPDB_ReplicationController_parentEnvironment(	RPDB_ReplicationController* replication_controller );
	RPDB_ReplicationController*		RPDB_ReplicationController_initReplicationID(	RPDB_ReplicationController*		replication_controller );
	RPDB_ReplicationController*		RPDB_ReplicationController_start(				RPDB_ReplicationController*		replication_controller,
	 									   												int									number_of_threads_for_message_processing	);
	void								RPDB_ReplicationController_processMessage(		RPDB_ReplicationController*		replication_controller,
	 									   												RPDB_Record*						control_record,
										   												RPDB_Record*						replication_record	);
	void								RPDB_ReplicationController_sync(				RPDB_ReplicationController*		replication_controller );
	void								RPDB_ReplicationController_callElection(		RPDB_ReplicationController*		replication_controller );
	RPDB_RemoteSite*					RPDB_ReplicationController_addRemoteSite(		RPDB_ReplicationController*		replication_controller,
	 				 					  												char*								remote_host,
					 					  												u_int								port	);
	RPDB_RemoteSite**					RPDB_ReplicationController_siteList(			RPDB_ReplicationController*		replication_controller );

#endif

