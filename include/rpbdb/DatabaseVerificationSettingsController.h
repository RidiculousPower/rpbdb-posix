/*
 *		RPbdb::Database::DatabaseVerificationController::DatabaseVerificationSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_VERIFICATION_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_VERIFICATION_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseVerificationSettingsController*	RPbdb_DatabaseVerificationSettingsController_new(									RPbdb_DatabaseSettingsController*					parent_database_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_free(									RPbdb_DatabaseVerificationSettingsController**		database_verification_settings_controller );
	RPbdb_Environment*						RPbdb_DatabaseVerificationSettingsController_parentEnvironment(			RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	RPbdb_Database* RPbdb_DatabaseVerificationSettingsController_parentDatabase(	RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller );

	FILE*											RPbdb_DatabaseVerificationSettingsController_file(									RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_setFile(								RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller, 
																																		FILE*												data_output_file );
	char*											RPbdb_DatabaseVerificationSettingsController_filePath(								RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_setFilePath(							RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller, 
																																		char*												data_output_file_path );
	BOOL											RPbdb_DatabaseVerificationSettingsController_aggressiveKeyDataPairDump(				RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOn(		RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOff(		RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL											RPbdb_DatabaseVerificationSettingsController_printableCharacters(					RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_turnPrintableCharactersOn(				RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_turnPrintableCharactersOff(			RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL 											RPbdb_DatabaseVerificationSettingsController_skipOrderCheck(						RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_turnSkipOrderCheckOn(					RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_turnSkipOrderCheckOff(					RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL											RPbdb_DatabaseVerificationSettingsController_onlyOrderCheck(						RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_turnOnlyOrderCheckOn(					RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_turnOnlyOrderCheckOff(					RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	BOOL											RPbdb_DatabaseVerificationSettingsController_forceOrderCheck(						RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_turnForceOrderCheckOn(					RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );
	void											RPbdb_DatabaseVerificationSettingsController_turnForceOrderCheckOff(				RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller );


#endif

