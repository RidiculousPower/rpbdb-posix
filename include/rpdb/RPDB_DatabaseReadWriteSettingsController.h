/*
*		RPDB::SettingsController::DatabaseSettingsController::DatabaseReadWriteSettingsController
*		RPDB::DatabaseController::Database::DatabaseSettingsController::DatabaseReadWriteSettingsController
*
*/

#ifndef RPDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseReadWriteSettingsController*	RPDB_DatabaseReadWriteSettingsController_new(									RPDB_DatabaseSettingsController*						database_settings_controller );

	void										RPDB_DatabaseReadWriteSettingsController_free(									RPDB_DatabaseReadWriteSettingsController** database_read_write_settings_controller );
	RPDB_Environment*					RPDB_DatabaseReadWriteSettingsController_parentEnvironment(	RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller );
	RPDB_Database* RPDB_DatabaseReadWriteSettingsController_parentDatabase(	RPDB_DatabaseReadWriteSettingsController* database_read_write_settings_controller );

	char*										RPDB_DatabaseReadWriteSettingsController_filename(								RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_setFilename(							RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller,
																																char*													filename	);
	BOOL											RPDB_DatabaseReadWriteSettingsController_prohibitSyncOnClose(					RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnProhibitSyncOnCloseOn(			RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnProhibitSyncOnCloseOff(			RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	BOOL											RPDB_DatabaseReadWriteSettingsController_ignoreLease(							RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnIgnoreLeaseOn(							RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnIgnoreLeaseOff(							RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	BOOL											RPDB_DatabaseReadWriteSettingsController_returnMultiple(						RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnReturnMultipleOn(					RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnReturnMultipleOff(				RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	BOOL											RPDB_DatabaseReadWriteSettingsController_prohibitDuplicateData(				RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnProhibitDuplicateDataOn(			RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnProhibitDuplicateDataOff(			RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	BOOL 										RPDB_DatabaseReadWriteSettingsController_prohibitOverwrite(					RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnProhibitOverwriteOn(				RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnProhibitOverwriteOff(				RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	BOOL											RPDB_DatabaseReadWriteSettingsController_prohibitPageCompaction(				RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnProhibitPageCompactionOn(				RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnProhibitPageCompactionOff(				RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	BOOL											RPDB_DatabaseReadWriteSettingsController_returnPagesToFilesystem(				RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnReturnPagesToFilesystemOn(		RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnReturnPagesToFilesystemOff(		RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	BOOL											RPDB_DatabaseReadWriteSettingsController_partialAccess(						RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnPartialAccessOn(						RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnPartialAccessOff(						RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	BOOL											RPDB_DatabaseReadWriteSettingsController_truncateFileOnOpen(					RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnTruncateFileOnOpenOn(				RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnTruncateFileOnOpenOff(			RPDB_DatabaseReadWriteSettingsController*				database_read_write_settings_controller );
	BOOL										RPDB_DatabaseReadWriteSettingsController_writeLocksInsteadOfReadLocks(			RPDB_DatabaseReadWriteSettingsController*				database_write_retrieve_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn(		RPDB_DatabaseReadWriteSettingsController*				database_write_retrieve_settings_controller );
	void										RPDB_DatabaseReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff(		RPDB_DatabaseReadWriteSettingsController*				database_write_retrieve_settings_controller );
	BOOL RPDB_DatabaseReadWriteSettingsController_duplicates( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPDB_DatabaseReadWriteSettingsController_turnDuplicatesOn( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPDB_DatabaseReadWriteSettingsController_turnDuplicatesOff( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller );
	BOOL RPDB_DatabaseReadWriteSettingsController_sortedDuplicates( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPDB_DatabaseReadWriteSettingsController_turnSortedDuplicatesOn( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPDB_DatabaseReadWriteSettingsController_turnSortedDuplicatesOff( RPDB_DatabaseReadWriteSettingsController* database_write_retrieve_settings_controller );
		
	
#endif

