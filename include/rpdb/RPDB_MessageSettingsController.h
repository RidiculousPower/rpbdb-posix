/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPDB_MESSAGE_SETTINGS_CONTROLLER
	#define RPDB_MESSAGE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_MessageSettingsController*	RPDB_MessageSettingsController_new(													RPDB_SettingsController*												settings_controller );
	void								RPDB_MessageSettingsController_free(									RPDB_MessageSettingsController** message_settings_controller );
	RPDB_Environment*			RPDB_MessageSettingsController_parentEnvironment(			RPDB_MessageSettingsController* message_settings_controller );
	void								RPDB_MessageSettingsController_free(													RPDB_MessageSettingsController**										message_settings_controller );
	FILE*								RPDB_MessageSettingsController_file(													RPDB_MessageSettingsController*										message_settings_controller );
	void								RPDB_MessageSettingsController_setFile(												RPDB_MessageSettingsController*										message_settings_controller, 
																																FILE*																	message_file );
	int									RPDB_MessageSettingsController_setFileFromPath(										RPDB_MessageSettingsController*										message_settings_controller, 
																																char*																	message_file_path );
																																													
/*
	void																					RPDB_MessageSettingsController_setMessageCallbackMethod(								RPDB_MessageSettingsController*										message_settings_controller, 
																																													void (*message_callback_method)(	RPDB_Environment*								environment, 
																																													const char*																message ) );
	void (*message_callback_method)(	RPDB_Environment*			environment, 
										const char*		message )							RPDB_MessageSettingsController_messageCallbackMethod(									RPDB_MessageSettingsController*										message_settings_controller );
	void																					RPDB_MessageSettingsController_setPanicCallbackMethod(									RPDB_MessageSettingsController*										message_settings_controller,
																																													void *(panic_callback_method)( RPDB_Environment*									environment ) );
	void *(panic_callback_method)( RPDB_Environment*	environment )									RPDB_MessageSettingsController_panicCallbackMethod(									RPDB_MessageSettingsController*										message_settings_controller );
	void																					RPDB_MessageSettingsController_setSiteIsNowReplicationClientCallbackMethod(			RPDB_MessageSettingsController*										message_settings_controller,
																																													void *(site_is_now_replication_client_callback_method)( RPDB_Environment*			environment ) );
	void *(site_is_now_replication_client_callback_method)( RPDB_Environment*	environment )			RPDB_MessageSettingsController_siteIsNowReplicationClientCallbackMethod(				RPDB_MessageSettingsController*										message_settings_controller );
	void																					RPDB_MessageSettingsController_setSiteWonReplicationElectionCallbackMethod(			RPDB_MessageSettingsController*										message_settings_controller,
																																													void *(site_won_replication_election_callback_method)( RPDB_Environment*			environment ) );
	void *(site_won_replication_election_callback_method)( RPDB_Environment*	environment )			RPDB_MessageSettingsController_siteWonReplicationElectionCallbackMethod(				RPDB_MessageSettingsController*										message_settings_controller );
	void																					RPDB_MessageSettingsController_setSiteIsNowMasterOfReplicationGroupCallbackMethod(		RPDB_MessageSettingsController*										message_settings_controller,
																																													void *(site_is_now_master_of_replication_group_callback_method)( RPDB_Environment*	environment ) );
	void *(site_is_now_master_of_replication_group_callback_method)( RPDB_Environment*	environment )	RPDB_MessageSettingsController_siteIsNowMasterOfReplicationGroupCallbackMethod(		RPDB_MessageSettingsController*										message_settings_controller );
	void																					RPDB_MessageSettingsController_setReplicationGroupHasNewMasterCallbackMethod(			RPDB_MessageSettingsController*										message_settings_controller,
																																													void *(replication_group_has_new_master_callback_method)( RPDB_Environment*		environment ) );
	void *(replication_group_has_new_master_callback_method)( RPDB_Environment*	environment )		RPDB_MessageSettingsController_replicationGroupHasNewMasterCallbackMethod(				RPDB_MessageSettingsController*										message_settings_controller );
	void																					RPDB_MessageSettingsController_setReplicationAcknowledgementFailedCallbackMethod(		RPDB_MessageSettingsController*										message_settings_controller,
																																													void *(replication_acknowledgement_failed_callback_method)( RPDB_Environment*		environment ) );
	void *(replication_acknowledgement_failed_callback_method)( RPDB_Environment*	environment )		RPDB_MessageSettingsController_replicationAcknowledgementFailedCallbackMethod(			RPDB_MessageSettingsController*										message_settings_controller );
	void																					RPDB_MessageSettingsController_setReplicationStartupCompletedCallbackMethod(			RPDB_MessageSettingsController*										message_settings_controller,
																																													void *(replication_startup_completed_callback_method)( RPDB_Environment*			environment ) );
	void *(replication_startup_completed_callback_method)( RPDB_Environment*	environment )			RPDB_MessageSettingsController_replicationStartupCompletedCallbackMethod(				RPDB_MessageSettingsController*										message_settings_controller );
	void																					RPDB_MessageSettingsController_setWriteFailedCallbackMethod(							RPDB_MessageSettingsController*										message_settings_controller,
																																													void *(write_failed_callback_method)( RPDB_Environment*							environment ) );
	void *(write_failed_callback_method)( RPDB_Environment*	environment )							RPDB_MessageSettingsController_writeFailedCallbackMethod(								RPDB_MessageSettingsController*										message_settings_controller );
*/

#endif

