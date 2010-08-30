/*
 *		RPDB::SettingsController::SettingsVerbosityController::SettingsVerbosityReplicationController
 *
 *
 */

#ifndef RPDB_REPLICATION_VERBOSITY_SETTINGS_CONTROLLER
	#define RPDB_REPLICATION_VERBOSITY_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_ReplicationVerbositySettingsController*		RPDB_ReplicationVerbositySettingsController_new(												RPDB_ReplicationSettingsController*				replication_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_free(												RPDB_ReplicationVerbositySettingsController** replication_verbosity_settings_controller );
	RPDB_Environment*							RPDB_ReplicationVerbositySettingsController_parentEnvironment(						RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller );

	BOOL												RPDB_ReplicationVerbositySettingsController_displayAllReplicationInformation(					RPDB_ReplicationVerbositySettingsController*					verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOn(			RPDB_ReplicationVerbositySettingsController*					verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOff(			RPDB_ReplicationVerbositySettingsController*					verbosity_settings_controller );

	BOOL												RPDB_ReplicationVerbositySettingsController_displayElectionInformation(						RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayElectionInformationOn(					RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayElectionInformationOff(					RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPDB_ReplicationVerbositySettingsController_displayReplicationMasterLeaseInformation(			RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOn(	RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOff(	RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPDB_ReplicationVerbositySettingsController_displayMiscProcessingInformation(					RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOn(			RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOff(			RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPDB_ReplicationVerbositySettingsController_displayMessageProcessingInformation(				RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOn(			RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOff(		RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPDB_ReplicationVerbositySettingsController_displayClientSynchronizationInformation(			RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOn(		RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOff(	RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPDB_ReplicationVerbositySettingsController_displayManagerConnectionFailureInformation(		RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOn(	RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOff(	RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

	BOOL												RPDB_ReplicationVerbositySettingsController_displayManagerMiscProcessing(						RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOn(				RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );
	void												RPDB_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOff(				RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller );

#endif

