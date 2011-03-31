#ifndef RPBDB_TRANSACTION_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_TRANSACTION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
/*
int														RPbdb_TransactionSettingsController_internal_transactionRecoveryCallbackMethod(		DB_ENV*										bdb_environment, 
   																																			DBT*										transaction_log_record, 
   																																			DB_LSN*										lsn, 
   																																			db_recops									recovery_operation );
*/
RPbdb_TransactionSettingsController*		RPbdb_TransactionSettingsController_internal_copyOfDefaultSettingsForInstance(		RPbdb_TransactionSettingsController*		transaction_settings_controller );
int													RPbdb_TransactionSettingsController_internal_beginFlags(				RPbdb_TransactionSettingsController*		transaction_settings_controller );
int													RPbdb_TransactionSettingsController_internal_discardFlags(				RPbdb_TransactionSettingsController*		transaction_settings_controller );
int													RPbdb_TransactionSettingsController_internal_commitFlags(				RPbdb_TransactionSettingsController*		transaction_settings_controller );
int													RPbdb_TransactionSettingsController_internal_commitCheckpointFlags(		RPbdb_TransactionSettingsController*		transaction_settings_controller );
int													RPbdb_TransactionSettingsController_internal_recoverFlags(				RPbdb_TransactionSettingsController*		transaction_settings_controller );	

RPbdb_TransactionSettingsController* RPbdb_TransactionSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_TransactionSettingsController* transaction_settings_controller );
	
#endif

