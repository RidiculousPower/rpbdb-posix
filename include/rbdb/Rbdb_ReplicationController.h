/*
 *		Rbdb::ReplicationController
 *
 *	
 */

#ifndef RBDB_REPLICATION_CONTROLLER
	#define RBDB_REPLICATION_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_ReplicationController*		Rbdb_ReplicationController_new(							Rbdb_Environment*								environment );
	void								Rbdb_ReplicationController_free(							Rbdb_ReplicationController** replication_controller );
	Rbdb_ReplicationSettingsController*	Rbdb_ReplicationController_settingsController(	Rbdb_ReplicationController* replication_controller );
	Rbdb_Environment*			Rbdb_ReplicationController_parentEnvironment(	Rbdb_ReplicationController* replication_controller );
	Rbdb_ReplicationController*		Rbdb_ReplicationController_initReplicationID(	Rbdb_ReplicationController*		replication_controller );
	Rbdb_ReplicationController*		Rbdb_ReplicationController_start(				Rbdb_ReplicationController*		replication_controller,
	 									   												int									number_of_threads_for_message_processing	);
	void								Rbdb_ReplicationController_processMessage(		Rbdb_ReplicationController*		replication_controller,
	 									   												Rbdb_Record*						control_record,
										   												Rbdb_Record*						replication_record	);
	void								Rbdb_ReplicationController_sync(				Rbdb_ReplicationController*		replication_controller );
	void								Rbdb_ReplicationController_callElection(		Rbdb_ReplicationController*		replication_controller );
	Rbdb_RemoteSite*					Rbdb_ReplicationController_addRemoteSite(		Rbdb_ReplicationController*		replication_controller,
	 				 					  												char*								remote_host,
					 					  												u_int								port	);
	Rbdb_RemoteSite**					Rbdb_ReplicationController_siteList(			Rbdb_ReplicationController*		replication_controller );

#endif

