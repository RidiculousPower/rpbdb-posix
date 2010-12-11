/*
 *		Rbdb::Database::DatabaseSettingsController
 *
 *
 */

#ifndef RBDB_DATABASE_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseSettingsController*				Rbdb_DatabaseSettingsController_new(											Rbdb_SettingsController*			settings_controller );

	void											Rbdb_DatabaseSettingsController_free(											Rbdb_DatabaseSettingsController** database_settings_controller );
	Rbdb_Environment*						Rbdb_DatabaseSettingsController_parentEnvironment(					Rbdb_DatabaseSettingsController* database_settings_controller );
	Rbdb_Database* Rbdb_DatabaseSettingsController_parentDatabase(	Rbdb_DatabaseSettingsController* database_settings_controller );

	int												Rbdb_DatabaseSettingsController_checksum(										Rbdb_DatabaseSettingsController*	database_settings_controller );
	void											Rbdb_DatabaseSettingsController_turnChecksumOn(								Rbdb_DatabaseSettingsController*	database_settings_controller );
	void											Rbdb_DatabaseSettingsController_turnChecksumOff(								Rbdb_DatabaseSettingsController*	database_settings_controller );
	int												Rbdb_DatabaseSettingsController_transactionDurability(							Rbdb_DatabaseSettingsController*	database_settings_controller );
	void											Rbdb_DatabaseSettingsController_turnTransactionDurabilityOn(					Rbdb_DatabaseSettingsController*	database_settings_controller );
	void											Rbdb_DatabaseSettingsController_turnTransactionDurabilityOff(					Rbdb_DatabaseSettingsController*	database_settings_controller );
	uint32_t										Rbdb_DatabaseSettingsController_pagesize(										Rbdb_DatabaseSettingsController*	database_settings_controller );
	void											Rbdb_DatabaseSettingsController_setPageSize(									Rbdb_DatabaseSettingsController*	database_settings_controller, 
																																	uint32_t							pagesize );
	BOOL											Rbdb_DatabaseSettingsController_isBigEndian(									Rbdb_DatabaseSettingsController*	database_settings_controller );
	void											Rbdb_DatabaseSettingsController_setByteOrderToBigEndian(						Rbdb_DatabaseSettingsController*	database_settings_controller );
	BOOL											Rbdb_DatabaseSettingsController_isLittleEndian(								Rbdb_DatabaseSettingsController*	database_settings_controller );
	void											Rbdb_DatabaseSettingsController_setByteOrderToLittleEndian(					Rbdb_DatabaseSettingsController*	database_settings_controller );
	BOOL											Rbdb_DatabaseSettingsController_isByteswapped(									Rbdb_DatabaseSettingsController*	database_settings_controller );
	int												Rbdb_DatabaseSettingsController_maxSizePageIn(														Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseErrorSettingsController*			Rbdb_DatabaseSettingsController_errorSettingsController(						Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseCacheSettingsController*			Rbdb_DatabaseSettingsController_cacheSettingsController(						Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseAssociationSettingsController*	Rbdb_DatabaseSettingsController_associationSettingsController(					Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseCompactSettingsController*		Rbdb_DatabaseSettingsController_compactSettingsController(						Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseEncryptionSettingsController*		Rbdb_DatabaseSettingsController_encryptionSettingsController(					Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseVerbositySettingsController*		Rbdb_DatabaseSettingsController_verbositySettingsController(					Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseVerificationSettingsController*	Rbdb_DatabaseSettingsController_verificationSettingsController(				Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseSequenceSettingsController*		Rbdb_DatabaseSettingsController_sequenceSettingsController(					Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseCursorSettingsController*			Rbdb_DatabaseSettingsController_cursorSettingsController(						Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseTypeSettingsController*			Rbdb_DatabaseSettingsController_typeSettingsController(						Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseEncryptionSettingsController*		Rbdb_DatabaseSettingsController_encryptionSettingsController(					Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseJoinSettingsController* Rbdb_DatabaseSettingsController_joinSettingsController( Rbdb_DatabaseSettingsController*	database_settings_controller );
	Rbdb_DatabaseRecordSettingsController* Rbdb_DatabaseSettingsController_recordSettingsController( Rbdb_DatabaseSettingsController*	database_settings_controller );

#endif

