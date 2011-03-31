/*
 *		RPbdb::SettingsController
 *
 *
 */

#ifndef RPBDB_SETTINGS_CONTROLLER
	#define RPBDB_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_SettingsController*						RPbdb_SettingsController_new(							RPbdb_Environment*				parent_environment );
	void											RPbdb_SettingsController_free(							RPbdb_SettingsController**	settings_controller );
	RPbdb_Environment*						RPbdb_SettingsController_parentEnvironment(	RPbdb_SettingsController*	settings_controller );
																																			
	void											RPbdb_SettingsController_free(							RPbdb_SettingsController**		settings_controller );
																																																																						
	long											RPbdb_SettingsController_SHMkey(						RPbdb_SettingsController*		settings_controller );
	void											RPbdb_SettingsController_setSHMkey(						RPbdb_SettingsController*		settings_controller, 
																											long							shm_key );
																																			
	RPbdb_DebugSettingsController*					RPbdb_SettingsController_debugSettingsController(		RPbdb_SettingsController*		settings_controller );
	RPbdb_EnvironmentCacheSettingsController*		RPbdb_SettingsController_cacheSettingsController(		RPbdb_SettingsController*		settings_controller );
	RPbdb_FileSettingsController*					RPbdb_SettingsController_fileSettingsController(		RPbdb_SettingsController*		settings_controller );
	RPbdb_ThreadSettingsController*					RPbdb_SettingsController_threadSettingsController(		RPbdb_SettingsController*		settings_controller );
	RPbdb_ErrorSettingsController*					RPbdb_SettingsController_errorSettingsController(		RPbdb_SettingsController*		settings_controller );
	RPbdb_MessageSettingsController*				RPbdb_SettingsController_messageSettingsController(		RPbdb_SettingsController*		settings_controller );
	RPbdb_MemoryPoolSettingsController*				RPbdb_SettingsController_memoryPoolSettingsController(	RPbdb_SettingsController*		settings_controller );
	RPbdb_TransactionSettingsController*			RPbdb_SettingsController_transactionSettingsController(	RPbdb_SettingsController*		settings_controller );
	RPbdb_LockSettingsController*					RPbdb_SettingsController_lockSettingsController(		RPbdb_SettingsController*		settings_controller );
	RPbdb_LogSettingsController*					RPbdb_SettingsController_logSettingsController(			RPbdb_SettingsController*		settings_controller );
	RPbdb_ReplicationSettingsController*			RPbdb_SettingsController_replicationSettingsController( RPbdb_SettingsController*		settings_controller );
	RPbdb_DatabaseSettingsController*				RPbdb_SettingsController_databaseSettingsController(	RPbdb_SettingsController*		settings_controller );
	RPbdb_MutexSettingsController*					RPbdb_SettingsController_mutexSettingsController(		RPbdb_SettingsController*		settings_controller );
	RPbdb_DirectorySettingsController*				RPbdb_SettingsController_directorySettingsController( RPbdb_SettingsController* settings_controller );

//	RPbdb_StatusSettingsController*					RPbdb_SettingsController_statusSettingsController(		RPbdb_SettingsController*		settings_controller );
		
#endif

