/*
 *		RPbdb::Database::DatabaseSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseSettingsController*				RPbdb_DatabaseSettingsController_new(											RPbdb_SettingsController*			settings_controller );

	void											RPbdb_DatabaseSettingsController_free(											RPbdb_DatabaseSettingsController** database_settings_controller );
	RPbdb_Environment*						RPbdb_DatabaseSettingsController_parentEnvironment(					RPbdb_DatabaseSettingsController* database_settings_controller );
	RPbdb_Database* RPbdb_DatabaseSettingsController_parentDatabase(	RPbdb_DatabaseSettingsController* database_settings_controller );

	int												RPbdb_DatabaseSettingsController_checksum(										RPbdb_DatabaseSettingsController*	database_settings_controller );
	void											RPbdb_DatabaseSettingsController_turnChecksumOn(								RPbdb_DatabaseSettingsController*	database_settings_controller );
	void											RPbdb_DatabaseSettingsController_turnChecksumOff(								RPbdb_DatabaseSettingsController*	database_settings_controller );
	int												RPbdb_DatabaseSettingsController_transactionDurability(							RPbdb_DatabaseSettingsController*	database_settings_controller );
	void											RPbdb_DatabaseSettingsController_turnTransactionDurabilityOn(					RPbdb_DatabaseSettingsController*	database_settings_controller );
	void											RPbdb_DatabaseSettingsController_turnTransactionDurabilityOff(					RPbdb_DatabaseSettingsController*	database_settings_controller );
	uint32_t										RPbdb_DatabaseSettingsController_pagesize(										RPbdb_DatabaseSettingsController*	database_settings_controller );
	void											RPbdb_DatabaseSettingsController_setPageSize(									RPbdb_DatabaseSettingsController*	database_settings_controller, 
																																	uint32_t							pagesize );
	BOOL											RPbdb_DatabaseSettingsController_isBigEndian(									RPbdb_DatabaseSettingsController*	database_settings_controller );
	void											RPbdb_DatabaseSettingsController_setByteOrderToBigEndian(						RPbdb_DatabaseSettingsController*	database_settings_controller );
	BOOL											RPbdb_DatabaseSettingsController_isLittleEndian(								RPbdb_DatabaseSettingsController*	database_settings_controller );
	void											RPbdb_DatabaseSettingsController_setByteOrderToLittleEndian(					RPbdb_DatabaseSettingsController*	database_settings_controller );
	BOOL											RPbdb_DatabaseSettingsController_isByteswapped(									RPbdb_DatabaseSettingsController*	database_settings_controller );
	int												RPbdb_DatabaseSettingsController_maxSizePageIn(														RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseErrorSettingsController*			RPbdb_DatabaseSettingsController_errorSettingsController(						RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseCacheSettingsController*			RPbdb_DatabaseSettingsController_cacheSettingsController(						RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseAssociationSettingsController*	RPbdb_DatabaseSettingsController_associationSettingsController(					RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseCompactSettingsController*		RPbdb_DatabaseSettingsController_compactSettingsController(						RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseEncryptionSettingsController*		RPbdb_DatabaseSettingsController_encryptionSettingsController(					RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseVerbositySettingsController*		RPbdb_DatabaseSettingsController_verbositySettingsController(					RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseVerificationSettingsController*	RPbdb_DatabaseSettingsController_verificationSettingsController(				RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseSequenceSettingsController*		RPbdb_DatabaseSettingsController_sequenceSettingsController(					RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseCursorSettingsController*			RPbdb_DatabaseSettingsController_cursorSettingsController(						RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseTypeSettingsController*			RPbdb_DatabaseSettingsController_typeSettingsController(						RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseEncryptionSettingsController*		RPbdb_DatabaseSettingsController_encryptionSettingsController(					RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseJoinSettingsController* RPbdb_DatabaseSettingsController_joinSettingsController( RPbdb_DatabaseSettingsController*	database_settings_controller );
	RPbdb_DatabaseRecordSettingsController* RPbdb_DatabaseSettingsController_recordSettingsController( RPbdb_DatabaseSettingsController*	database_settings_controller );

#endif

