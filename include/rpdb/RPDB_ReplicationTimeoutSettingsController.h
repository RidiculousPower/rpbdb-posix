/*
 *		Rbdb::SettingsController::ReplicationTimeoutSettingsController
 *
 *
 */

#ifndef Rbdb_REPLICATION_TIMEOUT_SETTINGS_CONTROLLER
	#define Rbdb_REPLICATION_TIMEOUT_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_ReplicationTimeoutSettingsController*		Rbdb_ReplicationTimeoutSettingsController_new(									Rbdb_ReplicationSettingsController*			replication_settings_controller );
	void											Rbdb_ReplicationTimeoutSettingsController_free(								Rbdb_ReplicationTimeoutSettingsController**		replication_timeout_settings_controller );
	Rbdb_Environment*						Rbdb_ReplicationTimeoutSettingsController_parentEnvironment(		Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );

	uint32_t	Rbdb_ReplicationTimeoutSettingsController_timeout(								Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		Rbdb_ReplicationTimeoutSettingsController_setTimeout(							Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										timeout );

	uint32_t	Rbdb_ReplicationTimeoutSettingsController_waitTimeBeforeCheckpointWrite(		Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		Rbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeCheckpointWrite(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										wait_time_before_checkpoint_write );

	uint32_t	Rbdb_ReplicationTimeoutSettingsController_waitTimeBeforeRetryConnection(		Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		Rbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeRetryConnection(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller,
																								uint32_t										wait_time_before_retry_connection );

	uint32_t	Rbdb_ReplicationTimeoutSettingsController_electionTimeout(						Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		Rbdb_ReplicationTimeoutSettingsController_setElectionTimeout(					Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										election_timeout );

	uint32_t	Rbdb_ReplicationTimeoutSettingsController_waitTimeBeforeRetryElection(			Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		Rbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeRetryElection(		Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										wait_time_before_retry_election );

	uint32_t	Rbdb_ReplicationTimeoutSettingsController_fullElectionParticipationTimeout(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		Rbdb_ReplicationTimeoutSettingsController_setFullElectionParticipationTimeout(	Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										full_election_participation_timeout );

	uint32_t	Rbdb_ReplicationTimeoutSettingsController_heartbeatMonitorPulse(				Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		Rbdb_ReplicationTimeoutSettingsController_setHeartbeatMonitorPulse(			Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										heartbeat_monitor_pulse );

	uint32_t	Rbdb_ReplicationTimeoutSettingsController_heartbeatBroadcastPulse(				Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		Rbdb_ReplicationTimeoutSettingsController_setHeartbeatBroadcastPulse(			Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										heartbeat_broadcast_pulse );

	uint32_t	Rbdb_ReplicationTimeoutSettingsController_leaseTimeout(						Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		Rbdb_ReplicationTimeoutSettingsController_setLeaseTimeout(						Rbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller,
																								uint32_t										lease_timeout );

#endif

