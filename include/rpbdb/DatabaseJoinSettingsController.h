/*
 *		RPbdb::SettingsController::JoinSettingsController
 *
 *
 */

#ifndef RPBDB_JOINSETTINGS_CONTROLLER
	#define RPBDB_JOINSETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

RPbdb_DatabaseJoinSettingsController* RPbdb_DatabaseJoinSettingsController_new( RPbdb_DatabaseSettingsController* parent_database_settings_controller );

	void							RPbdb_DatabaseJoinSettingsController_free(								RPbdb_DatabaseJoinSettingsController** join_settings_controller );
RPbdb_Database* RPbdb_DatabaseJoinSettingsController_parentDatabase(	RPbdb_DatabaseJoinSettingsController* join_settings_controller );
	RPbdb_Environment*		RPbdb_DatabaseJoinSettingsController_parentEnvironment(		RPbdb_DatabaseJoinSettingsController* join_settings_controller );

	BOOL							RPbdb_DatabaseJoinController_degreeOneIsolation(						RPbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPbdb_DatabaseJoinController_turnDegreeOneIsolationOn(					RPbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPbdb_DatabaseJoinController_turnDegreeOneIsolationOff(				RPbdb_DatabaseJoinSettingsController*		join_settings_controller );

	BOOL							RPbdb_DatabaseJoinController_writeLocksInsteadOfReadLocks(			RPbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPbdb_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOn(		RPbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPbdb_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOff(	RPbdb_DatabaseJoinSettingsController*		join_settings_controller );

	BOOL							RPbdb_DatabaseJoinController_noSortBeforeJoin(							RPbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPbdb_DatabaseJoinController_turnNoSortBeforeJoinOn(					RPbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							RPbdb_DatabaseJoinController_turnNoSortBeforeJoinOff(					RPbdb_DatabaseJoinSettingsController*		join_settings_controller );

#endif

