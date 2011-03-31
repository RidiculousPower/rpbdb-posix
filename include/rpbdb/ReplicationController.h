/*
 *		RPbdb::ReplicationController
 *
 *	
 */

#ifndef RPBDB_REPLICATION_CONTROLLER
	#define RPBDB_REPLICATION_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_ReplicationController*		RPbdb_ReplicationController_new(							RPbdb_Environment*								environment );
	void								RPbdb_ReplicationController_free(							RPbdb_ReplicationController** replication_controller );
	RPbdb_ReplicationSettingsController*	RPbdb_ReplicationController_settingsController(	RPbdb_ReplicationController* replication_controller );
	RPbdb_Environment*			RPbdb_ReplicationController_parentEnvironment(	RPbdb_ReplicationController* replication_controller );
	RPbdb_ReplicationController*		RPbdb_ReplicationController_initReplicationID(	RPbdb_ReplicationController*		replication_controller );
	RPbdb_ReplicationController*		RPbdb_ReplicationController_start(				RPbdb_ReplicationController*		replication_controller,
	 									   												int									number_of_threads_for_message_processing	);
	void								RPbdb_ReplicationController_processMessage(		RPbdb_ReplicationController*		replication_controller,
	 									   												RPbdb_Record*						control_record,
										   												RPbdb_Record*						replication_record	);
	void								RPbdb_ReplicationController_sync(				RPbdb_ReplicationController*		replication_controller );
	void								RPbdb_ReplicationController_callElection(		RPbdb_ReplicationController*		replication_controller );
	RPbdb_RemoteSite*					RPbdb_ReplicationController_addRemoteSite(		RPbdb_ReplicationController*		replication_controller,
	 				 					  												char*								remote_host,
					 					  												u_int								port	);
	RPbdb_RemoteSite**					RPbdb_ReplicationController_siteList(			RPbdb_ReplicationController*		replication_controller );

#endif

