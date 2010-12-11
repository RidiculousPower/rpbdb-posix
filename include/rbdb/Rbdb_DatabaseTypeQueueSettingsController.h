/*
 *		Rbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeQueueSettingsController
 *
 *
 */

#ifndef RBDB_DATABASE_TYPE_QUEUE_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_TYPE_QUEUE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseTypeQueueSettingsController*		Rbdb_DatabaseTypeQueueSettingsController_new(										Rbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller );
	void											Rbdb_DatabaseTypeQueueSettingsController_free(	Rbdb_DatabaseTypeQueueSettingsController** database_type_queue_settings_controller );
	Rbdb_Environment*						Rbdb_DatabaseTypeQueueSettingsController_parentEnvironment(	Rbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller );
	Rbdb_Database* Rbdb_DatabaseTypeQueueSettingsController_parentDatabase(	Rbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller );

	BOOL												Rbdb_DatabaseTypeQueueSettingsController_returnKeyDataPairsInOrder(				Rbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
		void												Rbdb_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOn(		Rbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
		void												Rbdb_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOff(		Rbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
	uint32_t										Rbdb_DatabaseTypeQueueSettingsController_numberOfPagesForUnderlyingData(			Rbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
	void											Rbdb_DatabaseTypeQueueSettingsController_setNumberOfPagesForUnderlyingData(		Rbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller, 
																																		uint32_t										number_of_pages_for_underlying_data );

#endif

