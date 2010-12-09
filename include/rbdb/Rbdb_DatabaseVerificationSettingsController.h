/*
 *		Rbdb::Database::DatabaseVerificationController::DatabaseVerificationSettingsController
 *
 *
 */

#ifndef Rbdb_DATABASE_VERIFICATION_SETTINGS_CONTROLLER
	#define Rbdb_DATABASE_VERIFICATION_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseVerificationSettingsController*	Rbdb_DatabaseVerificationSettingsController_new(									Rbdb_DatabaseSettingsController*					parent_database_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_free(									Rbdb_DatabaseVerificationSettingsController**		database_verification_settings_controller );
	Rbdb_Environment*						Rbdb_DatabaseVerificationSettingsController_parentEnvironment(			Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	Rbdb_Database* Rbdb_DatabaseVerificationSettingsController_parentDatabase(	Rbdb_DatabaseVerificationSettingsController* database_verification_settings_controller );

	FILE*											Rbdb_DatabaseVerificationSettingsController_file(									Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_setFile(								Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller, 
																																		FILE*												data_output_file );
	char*											Rbdb_DatabaseVerificationSettingsController_filePath(								Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_setFilePath(							Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller, 
																																		char*												data_output_file_path );
	BOOL											Rbdb_DatabaseVerificationSettingsController_aggressiveKeyDataPairDump(				Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOn(		Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOff(		Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL											Rbdb_DatabaseVerificationSettingsController_printableCharacters(					Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_turnPrintableCharactersOn(				Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_turnPrintableCharactersOff(			Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL 											Rbdb_DatabaseVerificationSettingsController_skipOrderCheck(						Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_turnSkipOrderCheckOn(					Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_turnSkipOrderCheckOff(					Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL											Rbdb_DatabaseVerificationSettingsController_onlyOrderCheck(						Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_turnOnlyOrderCheckOn(					Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_turnOnlyOrderCheckOff(					Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL											Rbdb_DatabaseVerificationSettingsController_forceOrderCheck(						Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_turnForceOrderCheckOn(					Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											Rbdb_DatabaseVerificationSettingsController_turnForceOrderCheckOff(				Rbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );


#endif

