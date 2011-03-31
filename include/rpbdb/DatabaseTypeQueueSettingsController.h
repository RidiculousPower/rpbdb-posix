/*
 *		RPbdb::SettingsController::DatabaseSettingsController::DatabaseTypeSettingsController::DatabaseTypeQueueSettingsController
 *
 *
 */

#ifndef RPBDB_DATABASE_TYPE_QUEUE_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_TYPE_QUEUE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseTypeQueueSettingsController*		RPbdb_DatabaseTypeQueueSettingsController_new(										RPbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller );
	void											RPbdb_DatabaseTypeQueueSettingsController_free(	RPbdb_DatabaseTypeQueueSettingsController** database_type_queue_settings_controller );
	RPbdb_Environment*						RPbdb_DatabaseTypeQueueSettingsController_parentEnvironment(	RPbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller );
	RPbdb_Database* RPbdb_DatabaseTypeQueueSettingsController_parentDatabase(	RPbdb_DatabaseTypeQueueSettingsController* database_type_queue_settings_controller );

	BOOL												RPbdb_DatabaseTypeQueueSettingsController_returnKeyDataPairsInOrder(				RPbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
		void												RPbdb_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOn(		RPbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
		void												RPbdb_DatabaseTypeQueueSettingsController_turnReturnKeyDataPairsInOrderOff(		RPbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
	uint32_t										RPbdb_DatabaseTypeQueueSettingsController_numberOfPagesForUnderlyingData(			RPbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller );
	void											RPbdb_DatabaseTypeQueueSettingsController_setNumberOfPagesForUnderlyingData(		RPbdb_DatabaseTypeQueueSettingsController*		database_type_queue_settings_controller, 
																																		uint32_t										number_of_pages_for_underlying_data );

#endif

