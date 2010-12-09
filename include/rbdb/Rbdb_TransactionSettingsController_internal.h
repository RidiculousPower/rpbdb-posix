#ifndef Rbdb_TRANSACTION_SETTINGS_CONTROLLER_INTERNAL
	#define Rbdb_TRANSACTION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
/*
int														Rbdb_TransactionSettingsController_internal_transactionRecoveryCallbackMethod(		DB_ENV*										bdb_environment, 
   																																			DBT*										transaction_log_record, 
   																																			DB_LSN*										lsn, 
   																																			db_recops									recovery_operation );
*/
Rbdb_TransactionSettingsController*		Rbdb_TransactionSettingsController_internal_copyOfDefaultSettingsForInstance(		Rbdb_TransactionSettingsController*		transaction_settings_controller );
int													Rbdb_TransactionSettingsController_internal_beginFlags(				Rbdb_TransactionSettingsController*		transaction_settings_controller );
int													Rbdb_TransactionSettingsController_internal_discardFlags(				Rbdb_TransactionSettingsController*		transaction_settings_controller );
int													Rbdb_TransactionSettingsController_internal_commitFlags(				Rbdb_TransactionSettingsController*		transaction_settings_controller );
int													Rbdb_TransactionSettingsController_internal_commitCheckpointFlags(		Rbdb_TransactionSettingsController*		transaction_settings_controller );
int													Rbdb_TransactionSettingsController_internal_recoverFlags(				Rbdb_TransactionSettingsController*		transaction_settings_controller );	

Rbdb_TransactionSettingsController* Rbdb_TransactionSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_TransactionSettingsController* transaction_settings_controller );
	
#endif

