/*
 *		RPbdb::SettingsController::ReplicationTimeoutSettingsController
 *
 *
 */

#ifndef RPBDB_REPLICATION_TIMEOUT_SETTINGS_CONTROLLER
	#define RPBDB_REPLICATION_TIMEOUT_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_ReplicationTimeoutSettingsController*		RPbdb_ReplicationTimeoutSettingsController_new(									RPbdb_ReplicationSettingsController*			replication_settings_controller );
	void											RPbdb_ReplicationTimeoutSettingsController_free(								RPbdb_ReplicationTimeoutSettingsController**		replication_timeout_settings_controller );
	RPbdb_Environment*						RPbdb_ReplicationTimeoutSettingsController_parentEnvironment(		RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );

	uint32_t	RPbdb_ReplicationTimeoutSettingsController_timeout(								RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPbdb_ReplicationTimeoutSettingsController_setTimeout(							RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										timeout );

	uint32_t	RPbdb_ReplicationTimeoutSettingsController_waitTimeBeforeCheckpointWrite(		RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeCheckpointWrite(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										wait_time_before_checkpoint_write );

	uint32_t	RPbdb_ReplicationTimeoutSettingsController_waitTimeBeforeRetryConnection(		RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeRetryConnection(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller,
																								uint32_t										wait_time_before_retry_connection );

	uint32_t	RPbdb_ReplicationTimeoutSettingsController_electionTimeout(						RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPbdb_ReplicationTimeoutSettingsController_setElectionTimeout(					RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										election_timeout );

	uint32_t	RPbdb_ReplicationTimeoutSettingsController_waitTimeBeforeRetryElection(			RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPbdb_ReplicationTimeoutSettingsController_setWaitTimeBeforeRetryElection(		RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										wait_time_before_retry_election );

	uint32_t	RPbdb_ReplicationTimeoutSettingsController_fullElectionParticipationTimeout(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPbdb_ReplicationTimeoutSettingsController_setFullElectionParticipationTimeout(	RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										full_election_participation_timeout );

	uint32_t	RPbdb_ReplicationTimeoutSettingsController_heartbeatMonitorPulse(				RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPbdb_ReplicationTimeoutSettingsController_setHeartbeatMonitorPulse(			RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										heartbeat_monitor_pulse );

	uint32_t	RPbdb_ReplicationTimeoutSettingsController_heartbeatBroadcastPulse(				RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPbdb_ReplicationTimeoutSettingsController_setHeartbeatBroadcastPulse(			RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller, 
																								uint32_t										heartbeat_broadcast_pulse );

	uint32_t	RPbdb_ReplicationTimeoutSettingsController_leaseTimeout(						RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller );
	void		RPbdb_ReplicationTimeoutSettingsController_setLeaseTimeout(						RPbdb_ReplicationTimeoutSettingsController*		replication_timeout_settings_controller,
																								uint32_t										lease_timeout );

#endif

