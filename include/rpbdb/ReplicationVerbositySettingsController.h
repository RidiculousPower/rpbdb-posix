/*
 *		RPbdb::SettingsController::SettingsVerbosityController::SettingsVerbosityReplicationController
 *
 *
 */

#ifndef RPBDB_REPLICATION_VERBOSITY_SETTINGS_CONTROLLER
	#define RPBDB_REPLICATION_VERBOSITY_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_ReplicationVerbositySettingsController*		RPbdb_ReplicationVerbositySettingsController_new(												RPbdb_ReplicationSettingsController*				replication_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_free(												RPbdb_ReplicationVerbositySettingsController** replication_verbosity_settings_controller );
	RPbdb_Environment*							RPbdb_ReplicationVerbositySettingsController_parentEnvironment(						RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller );

	BOOL												RPbdb_ReplicationVerbositySettingsController_displayAllReplicationInformation(					RPbdb_ReplicationVerbositySettingsController*					verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOn(			RPbdb_ReplicationVerbositySettingsController*					verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOff(			RPbdb_ReplicationVerbositySettingsController*					verbosity_settings_controller );

	BOOL												RPbdb_ReplicationVerbositySettingsController_displayElectionInformation(						RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayElectionInformationOn(					RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayElectionInformationOff(					RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPbdb_ReplicationVerbositySettingsController_displayReplicationMasterLeaseInformation(			RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOn(	RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOff(	RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPbdb_ReplicationVerbositySettingsController_displayMiscProcessingInformation(					RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOn(			RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOff(			RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPbdb_ReplicationVerbositySettingsController_displayMessageProcessingInformation(				RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOn(			RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOff(		RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPbdb_ReplicationVerbositySettingsController_displayClientSynchronizationInformation(			RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOn(		RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOff(	RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPbdb_ReplicationVerbositySettingsController_displayManagerConnectionFailureInformation(		RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOn(	RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOff(	RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPbdb_ReplicationVerbositySettingsController_displayManagerMiscProcessing(						RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOn(				RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPbdb_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOff(				RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

#endif

