/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPDB_REPLICATION_SETTINGS_CONTROLLER
	#define RPDB_REPLICATION_SETTINGS_CONTROLLER
	 
	#include "RPDB_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPDB_ReplicationSettingsController*					RPDB_ReplicationSettingsController_new(											RPDB_SettingsController*				settings_controller );

	void													RPDB_ReplicationSettingsController_free(											RPDB_ReplicationSettingsController**	replication_settings_controller );
	RPDB_Environment*								RPDB_ReplicationSettingsController_parentEnvironment(					RPDB_ReplicationSettingsController*	replication_settings_controller );

	int														RPDB_ReplicationSettingsController_on(												RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnOn(											RPDB_ReplicationSettingsController*	replication_settings_controller );
	BOOL													RPDB_ReplicationSettingsController_off(											RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnOff(										RPDB_ReplicationSettingsController*	replication_settings_controller );
	int													RPDB_ReplicationSettingsController_clientToClientSynchronization(					RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnClientToClientSynchronizationOn(			RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnClientToClientSynchronizationOff(			RPDB_ReplicationSettingsController*	replication_settings_controller );
	int													RPDB_ReplicationSettingsController_singleBulkTransfer(								RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnSingleBulkTransferOn(						RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnSingleBulkTransferOff(						RPDB_ReplicationSettingsController*	replication_settings_controller );
	int													RPDB_ReplicationSettingsController_delayNewSyncUntilExplicitCall(					RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOn(			RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOff(			RPDB_ReplicationSettingsController*	replication_settings_controller );
	int													RPDB_ReplicationSettingsController_useMasterLeases(								RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnUseMasterLeasesOn(							RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnUseMasterLeasesOff(							RPDB_ReplicationSettingsController*	replication_settings_controller );
	int													RPDB_ReplicationSettingsController_reinitializeOutdatedClients(					RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnReinitializeOutdatedClientsOn(			RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnReinitializeOutdatedClientsOff(			RPDB_ReplicationSettingsController*	replication_settings_controller );
	int													RPDB_ReplicationSettingsController_prohibitWait(									RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnProhibitWaitOn(								RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnProhibitWaitOff(							RPDB_ReplicationSettingsController*	replication_settings_controller );
	int													RPDB_ReplicationSettingsController_requireStrictMajority(							RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnRequireStrictMajorityOn(					RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_turnRequireStrictMajorityOff(					RPDB_ReplicationSettingsController*	replication_settings_controller );
	int													RPDB_ReplicationSettingsController_isMaster(										RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setIsMaster(									RPDB_ReplicationSettingsController*	replication_settings_controller );
	int													RPDB_ReplicationSettingsController_isClient(										RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setIsClient(									RPDB_ReplicationSettingsController*	replication_settings_controller );
	int													RPDB_ReplicationSettingsController_startAsClientOrRallyElection(					RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setStartAsClientOrRallyElection(				RPDB_ReplicationSettingsController*	replication_settings_controller );

	double											RPDB_ReplicationSettingsController_limit(											RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setLimit(										RPDB_ReplicationSettingsController*	replication_settings_controller, 
																																				uint64_t								limit_in_gbytes, 
																																				uint64_t								limit_in_bytes );
	char*													RPDB_ReplicationSettingsController_host(											RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setHost(										RPDB_ReplicationSettingsController*	replication_settings_controller, 
																																				char*									host );
	u_int													RPDB_ReplicationSettingsController_port(											RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setPort(										RPDB_ReplicationSettingsController*	replication_settings_controller, 
																																				u_int									port );
	uint32_t												RPDB_ReplicationSettingsController_siteCount(										RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setSiteCount(									RPDB_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								site_count );
	uint32_t												RPDB_ReplicationSettingsController_priorityOrderNumber(							RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setPriorityOrderNumber(							RPDB_ReplicationSettingsController*	replication_settings_controller,
	 																																			uint32_t								priority_order_number);
	uint32_t												RPDB_ReplicationSettingsController_retransmissionThresholdMinimum(					RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setRetransmissionThresholdMinimum(				RPDB_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								retransmission_threshold_minimum );
	uint32_t												RPDB_ReplicationSettingsController_retransmissionThresholdMaximum(					RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setRetransmissionThresholdMaximum(				RPDB_ReplicationSettingsController*	replication_settings_controller,
																																				uint32_t								retransmission_threshold_maximum );
	uint32_t												RPDB_ReplicationSettingsController_slowestClockValue(								RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setSlowestClockValue(							RPDB_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								slowest_clock_value );
	uint32_t												RPDB_ReplicationSettingsController_fastestClockSkewValue(							RPDB_ReplicationSettingsController*	replication_settings_controller );
	void													RPDB_ReplicationSettingsController_setFastestClockSkewValue(						RPDB_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								fastest_clock_value );
	RPDB_ReplicationElectionSettingsController*			RPDB_ReplicationSettingsController_electionSettingsController(						RPDB_ReplicationSettingsController*	replication_settings_controller );
	RPDB_ReplicationTimeoutSettingsController*				RPDB_ReplicationSettingsController_timeoutSettingsController(						RPDB_ReplicationSettingsController*	replication_settings_controller );
RPDB_ReplicationVerbositySettingsController* RPDB_ReplicationSettingsController_verbositySettingsController( RPDB_ReplicationSettingsController* replication_settings_controller );

#endif
