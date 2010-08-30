/*
 *		RPDB::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeQueueSettingsController
 *
 *
 */

#ifndef RPDB_DATABASE_TYPE_QUEUE_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_TYPE_QUEUE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseTypeQueueSettingsController*		RPDB_DatabaseTypeQueueSettingsController_new(										RPDB_DatabaseTypeSettingsController*						parent_database_type_settings_controller );
	void											RPDB_DatabaseTypeQueueSettingsController_free(	RPDB_DatabaseTypeQueueSettingsController** database_type_queue_settings_controller );
	RPDB_Environment*						RPDB_DatabaseTypeQueueSettingsController_parentEnvironment(	RPDB_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller );
	RPDB_Database* RPDB_DatabaseTypeQueueSettingsController_parentDatabase(	RPDB_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller );

	BOOL												RPDB_DatabaseTypeQueueSettingsController_returnKeyDataPairsInOrder(				RPDB_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
		void												RPDB_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOn(		RPDB_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
		void												RPDB_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOff(		RPDB_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
	uint32_t										RPDB_DatabaseTypeQueueSettingsController_numberOfPagesForUnderlyingData(			RPDB_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
	void											RPDB_DatabaseTypeQueueSettingsController_setNumberOfPagesForUnderlyingData(		RPDB_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller, 
																																		uint32_t										number_of_pages_for_underlying_data );

#endif

