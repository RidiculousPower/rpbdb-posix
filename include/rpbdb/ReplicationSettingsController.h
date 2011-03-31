/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPBDB_REPLICATION_SETTINGS_CONTROLLER
	#define RPBDB_REPLICATION_SETTINGS_CONTROLLER
	 
	#include "BaseStandardInclude.h"
	 
	/****************
	*  Prototypes  *
	****************/

	RPbdb_ReplicationSettingsController*					RPbdb_ReplicationSettingsController_new(											RPbdb_SettingsController*				settings_controller );

	void													RPbdb_ReplicationSettingsController_free(											RPbdb_ReplicationSettingsController**	replication_settings_controller );
	RPbdb_Environment*								RPbdb_ReplicationSettingsController_parentEnvironment(					RPbdb_ReplicationSettingsController*	replication_settings_controller );

	int														RPbdb_ReplicationSettingsController_on(												RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnOn(											RPbdb_ReplicationSettingsController*	replication_settings_controller );
	BOOL													RPbdb_ReplicationSettingsController_off(											RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnOff(										RPbdb_ReplicationSettingsController*	replication_settings_controller );
	int													RPbdb_ReplicationSettingsController_clientToClientSynchronization(					RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnClientToClientSynchronizationOn(			RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnClientToClientSynchronizationOff(			RPbdb_ReplicationSettingsController*	replication_settings_controller );
	int													RPbdb_ReplicationSettingsController_singleBulkTransfer(								RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnSingleBulkTransferOn(						RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnSingleBulkTransferOff(						RPbdb_ReplicationSettingsController*	replication_settings_controller );
	int													RPbdb_ReplicationSettingsController_delayNewSyncUntilExplicitCall(					RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOn(			RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnDelayNewSyncUntilExplicitCallOff(			RPbdb_ReplicationSettingsController*	replication_settings_controller );
	int													RPbdb_ReplicationSettingsController_useMasterLeases(								RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnUseMasterLeasesOn(							RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnUseMasterLeasesOff(							RPbdb_ReplicationSettingsController*	replication_settings_controller );
	int													RPbdb_ReplicationSettingsController_reinitializeOutdatedClients(					RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnReinitializeOutdatedClientsOn(			RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnReinitializeOutdatedClientsOff(			RPbdb_ReplicationSettingsController*	replication_settings_controller );
	int													RPbdb_ReplicationSettingsController_prohibitWait(									RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnProhibitWaitOn(								RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnProhibitWaitOff(							RPbdb_ReplicationSettingsController*	replication_settings_controller );
	int													RPbdb_ReplicationSettingsController_requireStrictMajority(							RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnRequireStrictMajorityOn(					RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_turnRequireStrictMajorityOff(					RPbdb_ReplicationSettingsController*	replication_settings_controller );
	int													RPbdb_ReplicationSettingsController_isMaster(										RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setIsMaster(									RPbdb_ReplicationSettingsController*	replication_settings_controller );
	int													RPbdb_ReplicationSettingsController_isClient(										RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setIsClient(									RPbdb_ReplicationSettingsController*	replication_settings_controller );
	int													RPbdb_ReplicationSettingsController_startAsClientOrRallyElection(					RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setStartAsClientOrRallyElection(				RPbdb_ReplicationSettingsController*	replication_settings_controller );

	double											RPbdb_ReplicationSettingsController_limit(											RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setLimit(										RPbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				uint64_t								limit_in_gbytes, 
																																				uint64_t								limit_in_bytes );
	char*													RPbdb_ReplicationSettingsController_host(											RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setHost(										RPbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				char*									host );
	u_int													RPbdb_ReplicationSettingsController_port(											RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setPort(										RPbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				u_int									port );
	uint32_t												RPbdb_ReplicationSettingsController_siteCount(										RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setSiteCount(									RPbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								site_count );
	uint32_t												RPbdb_ReplicationSettingsController_priorityOrderNumber(							RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setPriorityOrderNumber(							RPbdb_ReplicationSettingsController*	replication_settings_controller,
	 																																			uint32_t								priority_order_number);
	uint32_t												RPbdb_ReplicationSettingsController_retransmissionThresholdMinimum(					RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setRetransmissionThresholdMinimum(				RPbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								retransmission_threshold_minimum );
	uint32_t												RPbdb_ReplicationSettingsController_retransmissionThresholdMaximum(					RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setRetransmissionThresholdMaximum(				RPbdb_ReplicationSettingsController*	replication_settings_controller,
																																				uint32_t								retransmission_threshold_maximum );
	uint32_t												RPbdb_ReplicationSettingsController_slowestClockValue(								RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setSlowestClockValue(							RPbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								slowest_clock_value );
	uint32_t												RPbdb_ReplicationSettingsController_fastestClockSkewValue(							RPbdb_ReplicationSettingsController*	replication_settings_controller );
	void													RPbdb_ReplicationSettingsController_setFastestClockSkewValue(						RPbdb_ReplicationSettingsController*	replication_settings_controller, 
																																				uint32_t								fastest_clock_value );
	RPbdb_ReplicationElectionSettingsController*			RPbdb_ReplicationSettingsController_electionSettingsController(						RPbdb_ReplicationSettingsController*	replication_settings_controller );
	RPbdb_ReplicationTimeoutSettingsController*				RPbdb_ReplicationSettingsController_timeoutSettingsController(						RPbdb_ReplicationSettingsController*	replication_settings_controller );
RPbdb_ReplicationVerbositySettingsController* RPbdb_ReplicationSettingsController_verbositySettingsController( RPbdb_ReplicationSettingsController* replication_settings_controller );

#endif
