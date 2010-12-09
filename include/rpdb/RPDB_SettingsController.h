/*
 *		Rbdb::SettingsController
 *
 *
 */

#ifndef Rbdb_SETTINGS_CONTROLLER
	#define Rbdb_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_SettingsController*						Rbdb_SettingsController_new(							Rbdb_Environment*				parent_environment );
	void											Rbdb_SettingsController_free(							Rbdb_SettingsController**	settings_controller );
	Rbdb_Environment*						Rbdb_SettingsController_parentEnvironment(	Rbdb_SettingsController*	settings_controller );
																																			
	void											Rbdb_SettingsController_free(							Rbdb_SettingsController**		settings_controller );
																																																																						
	long											Rbdb_SettingsController_SHMkey(						Rbdb_SettingsController*		settings_controller );
	void											Rbdb_SettingsController_setSHMkey(						Rbdb_SettingsController*		settings_controller, 
																											long							shm_key );
																																			
	Rbdb_DebugSettingsController*					Rbdb_SettingsController_debugSettingsController(		Rbdb_SettingsController*		settings_controller );
	Rbdb_EnvironmentCacheSettingsController*		Rbdb_SettingsController_cacheSettingsController(		Rbdb_SettingsController*		settings_controller );
	Rbdb_FileSettingsController*					Rbdb_SettingsController_fileSettingsController(		Rbdb_SettingsController*		settings_controller );
	Rbdb_ThreadSettingsController*					Rbdb_SettingsController_threadSettingsController(		Rbdb_SettingsController*		settings_controller );
	Rbdb_ErrorSettingsController*					Rbdb_SettingsController_errorSettingsController(		Rbdb_SettingsController*		settings_controller );
	Rbdb_MessageSettingsController*				Rbdb_SettingsController_messageSettingsController(		Rbdb_SettingsController*		settings_controller );
	Rbdb_MemoryPoolSettingsController*				Rbdb_SettingsController_memoryPoolSettingsController(	Rbdb_SettingsController*		settings_controller );
	Rbdb_TransactionSettingsController*			Rbdb_SettingsController_transactionSettingsController(	Rbdb_SettingsController*		settings_controller );
	Rbdb_LockSettingsController*					Rbdb_SettingsController_lockSettingsController(		Rbdb_SettingsController*		settings_controller );
	Rbdb_LogSettingsController*					Rbdb_SettingsController_logSettingsController(			Rbdb_SettingsController*		settings_controller );
	Rbdb_ReplicationSettingsController*			Rbdb_SettingsController_replicationSettingsController( Rbdb_SettingsController*		settings_controller );
	Rbdb_DatabaseSettingsController*				Rbdb_SettingsController_databaseSettingsController(	Rbdb_SettingsController*		settings_controller );
	Rbdb_MutexSettingsController*					Rbdb_SettingsController_mutexSettingsController(		Rbdb_SettingsController*		settings_controller );
	Rbdb_DirectorySettingsController*				Rbdb_SettingsController_directorySettingsController( Rbdb_SettingsController* settings_controller );

//	Rbdb_StatusSettingsController*					Rbdb_SettingsController_statusSettingsController(		Rbdb_SettingsController*		settings_controller );
		
#endif

