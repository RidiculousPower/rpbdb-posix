/*
 *		RPBDB::SettingsController::SettingsStatusController
 *
 *
 */

#ifndef RPBDB_STATUSSETTINGS_CONTROLLER
	#define RPBDB_STATUSSETTINGS_CONTROLLER

	#include "RPBDB_BaseStandardInclude.h"

	/****************
	*	Prototypes	*
	****************/

	RPBDB_StatusController*		RPBDB_StatusSettingsController_new(													RPBDB_SettingsController*			settings_controller );
	void						RPBDB_StatusSettingsController_free(												RPBDB_StatusSettingsController*		status_settings_controller );
	RPBDB_Environment*	RPBDB_StatusSettingsController_parentEnvironment(						RPBDB_StatusSettingsController*		status_settings_controller );

	BOOL						RPBDB_StatusSettingsController_displayAllInformation(								RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnDisplayAllInformationOn(							RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnDisplayAllInformationOff(						RPBDB_StatusSettingsController*		status_settings_controller );

	BOOL						RPBDB_StatusSettingsController_resetStatisticsAfterDisplay(							RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnResetStatisticsAfterDisplayOn(					RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnResetStatisticsAfterDisplayOff(					RPBDB_StatusSettingsController*		status_settings_controller );

	BOOL						RPBDB_StatusSettingsController_displayAllSubsystemInformation(						RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnDisplayAllSubsystemInformationOn(				RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnDisplayAllSubsystemInformationOff(				RPBDB_StatusSettingsController*		status_settings_controller );

	BOOL						RPBDB_StatusSettingsController_retrieveCachedStatistics(			RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnRetrieveCachedStatisticsOn(		RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnRetrieveCachedStatisticsOff(	RPBDB_StatusSettingsController*		status_settings_controller );

	BOOL						RPBDB_StatusSettingsController_degreeTwoIsolation(									RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnDegreeTwoIsolationOn(							RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnDegreeTwoIsolationOff(							RPBDB_StatusSettingsController*		status_settings_controller );

	BOOL						RPBDB_StatusSettingsController_degreeOneIsolation(									RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnDegreeOneIsolationOn(							RPBDB_StatusSettingsController*		status_settings_controller );
	void						RPBDB_StatusSettingsController_turnDegreeOneIsolationOff(							RPBDB_StatusSettingsController*		status_settings_controller );

#endif

