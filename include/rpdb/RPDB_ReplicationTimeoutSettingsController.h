/*
 *		RPDB::SettingsController::ReplicationTimeoutSettingsController
 *
 *
 */

#ifndef RPDB_REPLICATION_TIMEOUT_SETTINGS_CONTROLLER
	#define RPDB_REPLICATION_TIMEOUT_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_ReplicationTimeoutSettingsController*		RPDB_ReplicationTimeoutSettingsController_new(									RPDB_ReplicationSettingsController*			replication_settings_controller );
	void											RPDB_ReplicationTimeoutSettingsController_free(								RPDB_ReplicationTimeoutSettingsController**		replication_timeout_settings_controller );
	RPDB_Environment*						RPDB_ReplicationTimeoutSettingsController_parentEnvironment(		RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );

	uint32_t	RPDB_ReplicationTimeoutSettingsController_timeout(								RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPDB_ReplicationTimeoutSettingsController_setTimeout(							RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										timeout );

	uint32_t	RPDB_ReplicationTimeoutSettingsController_waitTimeBeforeCheckpointWrite(		RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPDB_ReplicationTimeoutSettingsController_setWaitTimeBeforeCheckpointWrite(	RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										wait_time_before_checkpoint_write );

	uint32_t	RPDB_ReplicationTimeoutSettingsController_waitTimeBeforeRetryConnection(		RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPDB_ReplicationTimeoutSettingsController_setWaitTimeBeforeRetryConnection(	RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller,
																								uint32_t										wait_time_before_retry_connection );

	uint32_t	RPDB_ReplicationTimeoutSettingsController_electionTimeout(						RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPDB_ReplicationTimeoutSettingsController_setElectionTimeout(					RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										election_timeout );

	uint32_t	RPDB_ReplicationTimeoutSettingsController_waitTimeBeforeRetryElection(			RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPDB_ReplicationTimeoutSettingsController_setWaitTimeBeforeRetryElection(		RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										wait_time_before_retry_election );

	uint32_t	RPDB_ReplicationTimeoutSettingsController_fullElectionParticipationTimeout(	RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPDB_ReplicationTimeoutSettingsController_setFullElectionParticipationTimeout(	RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										full_election_participation_timeout );

	uint32_t	RPDB_ReplicationTimeoutSettingsController_heartbeatMonitorPulse(				RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPDB_ReplicationTimeoutSettingsController_setHeartbeatMonitorPulse(			RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										heartbeat_monitor_pulse );

	uint32_t	RPDB_ReplicationTimeoutSettingsController_heartbeatBroadcastPulse(				RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPDB_ReplicationTimeoutSettingsController_setHeartbeatBroadcastPulse(			RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										heartbeat_broadcast_pulse );

	uint32_t	RPDB_ReplicationTimeoutSettingsController_leaseTimeout(						RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPDB_ReplicationTimeoutSettingsController_setLeaseTimeout(						RPDB_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller,
																								uint32_t										lease_timeout );

#endif

