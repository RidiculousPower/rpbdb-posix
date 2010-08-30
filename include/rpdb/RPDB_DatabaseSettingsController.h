/*
 *		RPDB::Database::DatabaseSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseSettingsController*				RPDB_DatabaseSettingsController_new(											RPDB_SettingsController*			settings_controller );

	void											RPDB_DatabaseSettingsController_free(											RPDB_DatabaseSettingsController** database_settings_controller );
	RPDB_Environment*						RPDB_DatabaseSettingsController_parentEnvironment(					RPDB_DatabaseSettingsController* database_settings_controller );
	RPDB_Database* RPDB_DatabaseSettingsController_parentDatabase(	RPDB_DatabaseSettingsController* database_settings_controller );

	int												RPDB_DatabaseSettingsController_checksum(										RPDB_DatabaseSettingsController*	database_settings_controller );
	void											RPDB_DatabaseSettingsController_turnChecksumOn(								RPDB_DatabaseSettingsController*	database_settings_controller );
	void											RPDB_DatabaseSettingsController_turnChecksumOff(								RPDB_DatabaseSettingsController*	database_settings_controller );
	int												RPDB_DatabaseSettingsController_transactionDurability(							RPDB_DatabaseSettingsController*	database_settings_controller );
	void											RPDB_DatabaseSettingsController_turnTransactionDurabilityOn(					RPDB_DatabaseSettingsController*	database_settings_controller );
	void											RPDB_DatabaseSettingsController_turnTransactionDurabilityOff(					RPDB_DatabaseSettingsController*	database_settings_controller );
	uint32_t										RPDB_DatabaseSettingsController_pagesize(										RPDB_DatabaseSettingsController*	database_settings_controller );
	void											RPDB_DatabaseSettingsController_setPageSize(									RPDB_DatabaseSettingsController*	database_settings_controller, 
																																	uint32_t							pagesize );
	BOOL											RPDB_DatabaseSettingsController_isBigEndian(									RPDB_DatabaseSettingsController*	database_settings_controller );
	void											RPDB_DatabaseSettingsController_setByteOrderToBigEndian(						RPDB_DatabaseSettingsController*	database_settings_controller );
	BOOL											RPDB_DatabaseSettingsController_isLittleEndian(								RPDB_DatabaseSettingsController*	database_settings_controller );
	void											RPDB_DatabaseSettingsController_setByteOrderToLittleEndian(					RPDB_DatabaseSettingsController*	database_settings_controller );
	BOOL											RPDB_DatabaseSettingsController_isByteswapped(									RPDB_DatabaseSettingsController*	database_settings_controller );
	int												RPDB_DatabaseSettingsController_maxSizePageIn(														RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseErrorSettingsController*			RPDB_DatabaseSettingsController_errorSettingsController(						RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseFixedRecordSettingsController*	RPDB_DatabaseSettingsController_fixedRecordSettingsController(					RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseCacheSettingsController*			RPDB_DatabaseSettingsController_cacheSettingsController(						RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseAssociationSettingsController*	RPDB_DatabaseSettingsController_associationSettingsController(					RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseCompactSettingsController*		RPDB_DatabaseSettingsController_compactSettingsController(						RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseEncryptionSettingsController*		RPDB_DatabaseSettingsController_encryptionSettingsController(					RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseVerbositySettingsController*		RPDB_DatabaseSettingsController_verbositySettingsController(					RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseVerificationSettingsController*	RPDB_DatabaseSettingsController_verificationSettingsController(				RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseSequenceSettingsController*		RPDB_DatabaseSettingsController_sequenceSettingsController(					RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseCursorSettingsController*			RPDB_DatabaseSettingsController_cursorSettingsController(						RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseTypeSettingsController*			RPDB_DatabaseSettingsController_typeSettingsController(						RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseEncryptionSettingsController*		RPDB_DatabaseSettingsController_encryptionSettingsController(					RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseReadWriteSettingsController*		RPDB_DatabaseSettingsController_readWriteSettingsController(					RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseRecordSettingsController*			RPDB_DatabaseSettingsController_recordSettingsController(						RPDB_DatabaseSettingsController*	database_settings_controller );
	RPDB_DatabaseJoinSettingsController* RPDB_DatabaseSettingsController_joinSettingsController( RPDB_DatabaseSettingsController*	database_settings_controller );
	
#endif

