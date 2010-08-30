/*
 *		RPDB::SettingsController::JoinSettingsController
 *
 *
 */

#ifndef RPDB_JOINSETTINGS_CONTROLLER
	#define RPDB_JOINSETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

RPDB_DatabaseJoinSettingsController* RPDB_DatabaseJoinSettingsController_new( RPDB_DatabaseSettingsController* parent_database_settings_controller );

	void							RPDB_DatabaseJoinSettingsController_free(								RPDB_DatabaseJoinSettingsController** join_settings_controller );
RPDB_Database* RPDB_DatabaseJoinSettingsController_parentDatabase(	RPDB_DatabaseJoinSettingsController* join_settings_controller );
	RPDB_Environment*		RPDB_DatabaseJoinSettingsController_parentEnvironment(		RPDB_DatabaseJoinSettingsController* join_settings_controller );

	BOOL							RPDB_DatabaseJoinController_degreeOneIsolation(						RPDB_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPDB_DatabaseJoinController_turnDegreeOneIsolationOn(					RPDB_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPDB_DatabaseJoinController_turnDegreeOneIsolationOff(				RPDB_DatabaseJoinSettingsController*		join_settings_controller );

	BOOL							RPDB_DatabaseJoinController_writeLocksInsteadOfReadLocks(			RPDB_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPDB_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOn(		RPDB_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPDB_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOff(	RPDB_DatabaseJoinSettingsController*		join_settings_controller );

	BOOL							RPDB_DatabaseJoinController_noSortBeforeJoin(							RPDB_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPDB_DatabaseJoinController_turnNoSortBeforeJoinOn(					RPDB_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPDB_DatabaseJoinController_turnNoSortBeforeJoinOff(					RPDB_DatabaseJoinSettingsController*		join_settings_controller );

#endif

