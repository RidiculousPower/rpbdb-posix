/*
 *		Rbdb::SettingsController::SettingsVerbosityController::SettingsVerbosityReplicationController
 *
 *
 */

#ifndef Rbdb_REPLICATION_VERBOSITY_SETTINGS_CONTROLLER
	#define Rbdb_REPLICATION_VERBOSITY_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_ReplicationVerbositySettingsController*		Rbdb_ReplicationVerbositySettingsController_new(												Rbdb_ReplicationSettingsController*				replication_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_free(												Rbdb_ReplicationVerbositySettingsController** replication_verbosity_settings_controller );
	Rbdb_Environment*							Rbdb_ReplicationVerbositySettingsController_parentEnvironment(						Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller );

	BOOL												Rbdb_ReplicationVerbositySettingsController_displayAllReplicationInformation(					Rbdb_ReplicationVerbositySettingsController*					verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOn(			Rbdb_ReplicationVerbositySettingsController*					verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOff(			Rbdb_ReplicationVerbositySettingsController*					verbosity_settings_controller );

	BOOL												Rbdb_ReplicationVerbositySettingsController_displayElectionInformation(						Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayElectionInformationOn(					Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayElectionInformationOff(					Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												Rbdb_ReplicationVerbositySettingsController_displayReplicationMasterLeaseInformation(			Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOn(	Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOff(	Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												Rbdb_ReplicationVerbositySettingsController_displayMiscProcessingInformation(					Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOn(			Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOff(			Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												Rbdb_ReplicationVerbositySettingsController_displayMessageProcessingInformation(				Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOn(			Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOff(		Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												Rbdb_ReplicationVerbositySettingsController_displayClientSynchronizationInformation(			Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOn(		Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOff(	Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												Rbdb_ReplicationVerbositySettingsController_displayManagerConnectionFailureInformation(		Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOn(	Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOff(	Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												Rbdb_ReplicationVerbositySettingsController_displayManagerMiscProcessing(						Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOn(				Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												Rbdb_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOff(				Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

#endif

