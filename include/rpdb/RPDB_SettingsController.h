/*
 *		RPDB::SettingsController
 *
 *
 */

#ifndef RPDB_SETTINGS_CONTROLLER
	#define RPDB_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_SettingsController*						RPDB_SettingsController_new(							RPDB_Environment*				parent_environment );
	void											RPDB_SettingsController_free(							RPDB_SettingsController**	settings_controller );
	RPDB_Environment*						RPDB_SettingsController_parentEnvironment(	RPDB_SettingsController*	settings_controller );
																																			
	void											RPDB_SettingsController_free(							RPDB_SettingsController**		settings_controller );
																																																																						
	long											RPDB_SettingsController_SHMkey(						RPDB_SettingsController*		settings_controller );
	void											RPDB_SettingsController_setSHMkey(						RPDB_SettingsController*		settings_controller, 
																											long							shm_key );
																																			
	RPDB_DebugSettingsController*					RPDB_SettingsController_debugSettingsController(		RPDB_SettingsController*		settings_controller );
	RPDB_EnvironmentCacheSettingsController*		RPDB_SettingsController_cacheSettingsController(		RPDB_SettingsController*		settings_controller );
	RPDB_FileSettingsController*					RPDB_SettingsController_fileSettingsController(		RPDB_SettingsController*		settings_controller );
	RPDB_ThreadSettingsController*					RPDB_SettingsController_threadSettingsController(		RPDB_SettingsController*		settings_controller );
	RPDB_ErrorSettingsController*					RPDB_SettingsController_errorSettingsController(		RPDB_SettingsController*		settings_controller );
	RPDB_MessageSettingsController*				RPDB_SettingsController_messageSettingsController(		RPDB_SettingsController*		settings_controller );
	RPDB_MemoryPoolSettingsController*				RPDB_SettingsController_memoryPoolSettingsController(	RPDB_SettingsController*		settings_controller );
	RPDB_TransactionSettingsController*			RPDB_SettingsController_transactionSettingsController(	RPDB_SettingsController*		settings_controller );
	RPDB_LockSettingsController*					RPDB_SettingsController_lockSettingsController(		RPDB_SettingsController*		settings_controller );
	RPDB_LogSettingsController*					RPDB_SettingsController_logSettingsController(			RPDB_SettingsController*		settings_controller );
	RPDB_ReplicationSettingsController*			RPDB_SettingsController_replicationSettingsController( RPDB_SettingsController*		settings_controller );
	RPDB_DatabaseSettingsController*				RPDB_SettingsController_databaseSettingsController(	RPDB_SettingsController*		settings_controller );
	RPDB_MutexSettingsController*					RPDB_SettingsController_mutexSettingsController(		RPDB_SettingsController*		settings_controller );
	RPDB_DirectorySettingsController*				RPDB_SettingsController_directorySettingsController( RPDB_SettingsController* settings_controller );

//	RPDB_StatusSettingsController*					RPDB_SettingsController_statusSettingsController(		RPDB_SettingsController*		settings_controller );
		
#endif

