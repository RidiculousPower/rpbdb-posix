/*
 *		RPDB::Database::DatabaseVerificationController::DatabaseVerificationSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_VERIFICATION_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_VERIFICATION_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseVerificationSettingsController*	RPDB_DatabaseVerificationSettingsController_new(									RPDB_DatabaseSettingsController*					parent_database_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_free(									RPDB_DatabaseVerificationSettingsController**		database_verification_settings_controller );
	RPDB_Environment*						RPDB_DatabaseVerificationSettingsController_parentEnvironment(			RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	RPDB_Database* RPDB_DatabaseVerificationSettingsController_parentDatabase(	RPDB_DatabaseVerificationSettingsController* database_verification_settings_controller );

	FILE*											RPDB_DatabaseVerificationSettingsController_file(									RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_setFile(								RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller, 
																																		FILE*												data_output_file );
	char*											RPDB_DatabaseVerificationSettingsController_filePath(								RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_setFilePath(							RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller, 
																																		char*												data_output_file_path );
	BOOL											RPDB_DatabaseVerificationSettingsController_aggressiveKeyDataPairDump(				RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOn(		RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOff(		RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL											RPDB_DatabaseVerificationSettingsController_printableCharacters(					RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_turnPrintableCharactersOn(				RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_turnPrintableCharactersOff(			RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL 											RPDB_DatabaseVerificationSettingsController_skipOrderCheck(						RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_turnSkipOrderCheckOn(					RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_turnSkipOrderCheckOff(					RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL											RPDB_DatabaseVerificationSettingsController_onlyOrderCheck(						RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_turnOnlyOrderCheckOn(					RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_turnOnlyOrderCheckOff(					RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL											RPDB_DatabaseVerificationSettingsController_forceOrderCheck(						RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_turnForceOrderCheckOn(					RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPDB_DatabaseVerificationSettingsController_turnForceOrderCheckOff(				RPDB_DatabaseVerificationSettingsController*		database_verification_settings_controller );


#endif

