/*
 *		Rbdb::SettingsController::JoinSettingsController
 *
 *
 */

#ifndef RBDB_JOINSETTINGS_CONTROLLER
	#define RBDB_JOINSETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

Rbdb_DatabaseJoinSettingsController* Rbdb_DatabaseJoinSettingsController_new( Rbdb_DatabaseSettingsController* parent_database_settings_controller );

	void							Rbdb_DatabaseJoinSettingsController_free(								Rbdb_DatabaseJoinSettingsController** join_settings_controller );
Rbdb_Database* Rbdb_DatabaseJoinSettingsController_parentDatabase(	Rbdb_DatabaseJoinSettingsController* join_settings_controller );
	Rbdb_Environment*		Rbdb_DatabaseJoinSettingsController_parentEnvironment(		Rbdb_DatabaseJoinSettingsController* join_settings_controller );

	BOOL							Rbdb_DatabaseJoinController_degreeOneIsolation(						Rbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							Rbdb_DatabaseJoinController_turnDegreeOneIsolationOn(					Rbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							Rbdb_DatabaseJoinController_turnDegreeOneIsolationOff(				Rbdb_DatabaseJoinSettingsController*		join_settings_controller );

	BOOL							Rbdb_DatabaseJoinController_writeLocksInsteadOfReadLocks(			Rbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							Rbdb_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOn(		Rbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							Rbdb_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOff(	Rbdb_DatabaseJoinSettingsController*		join_settings_controller );

	BOOL							Rbdb_DatabaseJoinController_noSortBeforeJoin(							Rbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							Rbdb_DatabaseJoinController_turnNoSortBeforeJoinOn(					Rbdb_DatabaseJoinSettingsController*		join_settings_controller );
	void							Rbdb_DatabaseJoinController_turnNoSortBeforeJoinOff(					Rbdb_DatabaseJoinSettingsController*		join_settings_controller );

#endif

