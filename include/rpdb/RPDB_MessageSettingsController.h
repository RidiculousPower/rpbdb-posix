/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef Rbdb_MESSAGE_SETTINGS_CONTROLLER
	#define Rbdb_MESSAGE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_MessageSettingsController*	Rbdb_MessageSettingsController_new(													Rbdb_SettingsController*												settings_controller );
	void								Rbdb_MessageSettingsController_free(									Rbdb_MessageSettingsController** message_settings_controller );
	Rbdb_Environment*			Rbdb_MessageSettingsController_parentEnvironment(			Rbdb_MessageSettingsController* message_settings_controller );
	void								Rbdb_MessageSettingsController_free(													Rbdb_MessageSettingsController**										message_settings_controller );
	FILE*								Rbdb_MessageSettingsController_file(													Rbdb_MessageSettingsController*										message_settings_controller );
	void								Rbdb_MessageSettingsController_setFile(												Rbdb_MessageSettingsController*										message_settings_controller, 
																																FILE*																	message_file );
	int									Rbdb_MessageSettingsController_setFileFromPath(										Rbdb_MessageSettingsController*										message_settings_controller, 
																																char*																	message_file_path );
																																													
/*
	void																					Rbdb_MessageSettingsController_setMessageCallbackMethod(								Rbdb_MessageSettingsController*										message_settings_controller, 
																																													void (*message_callback_method)(	Rbdb_Environment*								environment, 
																																													const char*																message ) );
	void (*message_callback_method)(	Rbdb_Environment*			environment, 
										const char*		message )							Rbdb_MessageSettingsController_messageCallbackMethod(									Rbdb_MessageSettingsController*										message_settings_controller );
	void																					Rbdb_MessageSettingsController_setPanicCallbackMethod(									Rbdb_MessageSettingsController*										message_settings_controller,
																																													void *(panic_callback_method)( Rbdb_Environment*									environment ) );
	void *(panic_callback_method)( Rbdb_Environment*	environment )									Rbdb_MessageSettingsController_panicCallbackMethod(									Rbdb_MessageSettingsController*										message_settings_controller );
	void																					Rbdb_MessageSettingsController_setSiteIsNowReplicationClientCallbackMethod(			Rbdb_MessageSettingsController*										message_settings_controller,
																																													void *(site_is_now_replication_client_callback_method)( Rbdb_Environment*			environment ) );
	void *(site_is_now_replication_client_callback_method)( Rbdb_Environment*	environment )			Rbdb_MessageSettingsController_siteIsNowReplicationClientCallbackMethod(				Rbdb_MessageSettingsController*										message_settings_controller );
	void																					Rbdb_MessageSettingsController_setSiteWonReplicationElectionCallbackMethod(			Rbdb_MessageSettingsController*										message_settings_controller,
																																													void *(site_won_replication_election_callback_method)( Rbdb_Environment*			environment ) );
	void *(site_won_replication_election_callback_method)( Rbdb_Environment*	environment )			Rbdb_MessageSettingsController_siteWonReplicationElectionCallbackMethod(				Rbdb_MessageSettingsController*										message_settings_controller );
	void																					Rbdb_MessageSettingsController_setSiteIsNowMasterOfReplicationGroupCallbackMethod(		Rbdb_MessageSettingsController*										message_settings_controller,
																																													void *(site_is_now_master_of_replication_group_callback_method)( Rbdb_Environment*	environment ) );
	void *(site_is_now_master_of_replication_group_callback_method)( Rbdb_Environment*	environment )	Rbdb_MessageSettingsController_siteIsNowMasterOfReplicationGroupCallbackMethod(		Rbdb_MessageSettingsController*										message_settings_controller );
	void																					Rbdb_MessageSettingsController_setReplicationGroupHasNewMasterCallbackMethod(			Rbdb_MessageSettingsController*										message_settings_controller,
																																													void *(replication_group_has_new_master_callback_method)( Rbdb_Environment*		environment ) );
	void *(replication_group_has_new_master_callback_method)( Rbdb_Environment*	environment )		Rbdb_MessageSettingsController_replicationGroupHasNewMasterCallbackMethod(				Rbdb_MessageSettingsController*										message_settings_controller );
	void																					Rbdb_MessageSettingsController_setReplicationAcknowledgementFailedCallbackMethod(		Rbdb_MessageSettingsController*										message_settings_controller,
																																													void *(replication_acknowledgement_failed_callback_method)( Rbdb_Environment*		environment ) );
	void *(replication_acknowledgement_failed_callback_method)( Rbdb_Environment*	environment )		Rbdb_MessageSettingsController_replicationAcknowledgementFailedCallbackMethod(			Rbdb_MessageSettingsController*										message_settings_controller );
	void																					Rbdb_MessageSettingsController_setReplicationStartupCompletedCallbackMethod(			Rbdb_MessageSettingsController*										message_settings_controller,
																																													void *(replication_startup_completed_callback_method)( Rbdb_Environment*			environment ) );
	void *(replication_startup_completed_callback_method)( Rbdb_Environment*	environment )			Rbdb_MessageSettingsController_replicationStartupCompletedCallbackMethod(				Rbdb_MessageSettingsController*										message_settings_controller );
	void																					Rbdb_MessageSettingsController_setWriteFailedCallbackMethod(							Rbdb_MessageSettingsController*										message_settings_controller,
																																													void *(write_failed_callback_method)( Rbdb_Environment*							environment ) );
	void *(write_failed_callback_method)( Rbdb_Environment*	environment )							Rbdb_MessageSettingsController_writeFailedCallbackMethod(								Rbdb_MessageSettingsController*										message_settings_controller );
*/

#endif

