/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RBDB_REPLICATION_SETTINGS_CONTROLLER
	#define RBDB_REPLICATION_SETTINGS_CONTROLLER
	 
	#include "Rbdb_BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	Rbdb_ReplicationSettingsController*					Rbdb_ReplicationSettingsController_new(											Rbdb_SettingsController*				settings_controller );

	void													Rbdb_ReplicationSettingsController_free(											Rbdb_ReplicationSettingsController**	replication_settings_controller );
	Rbdb_Environment*								Rbdb_ReplicationSettingsController_parentEnvironment(					Rbdb_ReplicationSettingsController*	replication_settings_controller );

	int														Rbdb_ReplicationSettingsController_on(												Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnOn(											Rbdb_ReplicationSettingsController*	replication_settings_controller );
	BOOL													Rbdb_ReplicationSettingsController_off(											Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnOff(										Rbdb_ReplicationSettingsController*	replication_settings_controller );
	int													Rbdb_ReplicationSettingsController_clientToClientSynchronization(					Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnClientToClientSynchronizationOn(			Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnClientToClientSynchronizationOff(			Rbdb_ReplicationSettingsController*	replication_settings_controller );
	int													Rbdb_ReplicationSettingsController_singleBulkTransfer(								Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnSingleBulkTransferOn(						Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnSingleBulkTransferOff(						Rbdb_ReplicationSettingsController*	replication_settings_controller );
	int													Rbdb_ReplicationSettingsController_delayNewSyncUntilExplicitCall(					Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOn(			Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOff(			Rbdb_ReplicationSettingsController*	replication_settings_controller );
	int													Rbdb_ReplicationSettingsController_useMasterLeases(								Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnUseMasterLeasesOn(							Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnUseMasterLeasesOff(							Rbdb_ReplicationSettingsController*	replication_settings_controller );
	int													Rbdb_ReplicationSettingsController_reinitializeOutdatedClients(					Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnReinitializeOutdatedClientsOn(			Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnReinitializeOutdatedClientsOff(			Rbdb_ReplicationSettingsController*	replication_settings_controller );
	int													Rbdb_ReplicationSettingsController_prohibitWait(									Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnProhibitWaitOn(								Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnProhibitWaitOff(							Rbdb_ReplicationSettingsController*	replication_settings_controller );
	int													Rbdb_ReplicationSettingsController_requireStrictMajority(							Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnRequireStrictMajorityOn(					Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_turnRequireStrictMajorityOff(					Rbdb_ReplicationSettingsController*	replication_settings_controller );
	int													Rbdb_ReplicationSettingsController_isMaster(										Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setIsMaster(									Rbdb_ReplicationSettingsController*	replication_settings_controller );
	int													Rbdb_ReplicationSettingsController_isClient(										Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setIsClient(									Rbdb_ReplicationSettingsController*	replication_settings_controller );
	int													Rbdb_ReplicationSettingsController_startAsClientOrRallyElection(					Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setStartAsClientOrRallyElection(				Rbdb_ReplicationSettingsController*	replication_settings_controller );

	double											Rbdb_ReplicationSettingsController_limit(											Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setLimit(										Rbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				uint64_t								limit_in_gbytes, 
																																				uint64_t								limit_in_bytes );
	char*													Rbdb_ReplicationSettingsController_host(											Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setHost(										Rbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				char*									host );
	u_int													Rbdb_ReplicationSettingsController_port(											Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setPort(										Rbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				u_int									port );
	uint32_t												Rbdb_ReplicationSettingsController_siteCount(										Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setSiteCount(									Rbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								site_count );
	uint32_t												Rbdb_ReplicationSettingsController_priorityOrderNumber(							Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setPriorityOrderNumber(							Rbdb_ReplicationSettingsController*	replication_settings_controller,
	 																																			uint32_t								priority_order_number);
	uint32_t												Rbdb_ReplicationSettingsController_retransmissionThresholdMinimum(					Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setRetransmissionThresholdMinimum(				Rbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								retransmission_threshold_minimum );
	uint32_t												Rbdb_ReplicationSettingsController_retransmissionThresholdMaximum(					Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setRetransmissionThresholdMaximum(				Rbdb_ReplicationSettingsController*	replication_settings_controller,
																																				uint32_t								retransmission_threshold_maximum );
	uint32_t												Rbdb_ReplicationSettingsController_slowestClockValue(								Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setSlowestClockValue(							Rbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								slowest_clock_value );
	uint32_t												Rbdb_ReplicationSettingsController_fastestClockSkewValue(							Rbdb_ReplicationSettingsController*	replication_settings_controller );
	void													Rbdb_ReplicationSettingsController_setFastestClockSkewValue(						Rbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								fastest_clock_value );
	Rbdb_ReplicationElectionSettingsController*			Rbdb_ReplicationSettingsController_electionSettingsController(						Rbdb_ReplicationSettingsController*	replication_settings_controller );
	Rbdb_ReplicationTimeoutSettingsController*				Rbdb_ReplicationSettingsController_timeoutSettingsController(						Rbdb_ReplicationSettingsController*	replication_settings_controller );
Rbdb_ReplicationVerbositySettingsController* Rbdb_ReplicationSettingsController_verbositySettingsController( Rbdb_ReplicationSettingsController* replication_settings_controller );

#endif
