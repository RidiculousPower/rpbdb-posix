/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */

#ifndef RPBDB_MESSAGE_SETTINGS_CONTROLLER
	#define RPBDB_MESSAGE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_MessageSettingsController*	RPbdb_MessageSettingsController_new(													RPbdb_SettingsController*												settings_controller );
	void								RPbdb_MessageSettingsController_free(									RPbdb_MessageSettingsController** message_settings_controller );
	RPbdb_Environment*			RPbdb_MessageSettingsController_parentEnvironment(			RPbdb_MessageSettingsController* message_settings_controller );
	void								RPbdb_MessageSettingsController_free(													RPbdb_MessageSettingsController**										message_settings_controller );
	FILE*								RPbdb_MessageSettingsController_file(													RPbdb_MessageSettingsController*										message_settings_controller );
	void								RPbdb_MessageSettingsController_setFile(												RPbdb_MessageSettingsController*										message_settings_controller, 
																																FILE*																	message_file );
	int									RPbdb_MessageSettingsController_setFileFromPath(										RPbdb_MessageSettingsController*										message_settings_controller, 
																																char*																	message_file_path );
																																													
/*
	void																					RPbdb_MessageSettingsController_setMessageCallbackMethod(								RPbdb_MessageSettingsController*										message_settings_controller, 
																																													void (*message_callback_method)(	RPbdb_Environment*								environment, 
																																													const char*																message ) );
	void (*message_callback_method)(	RPbdb_Environment*			environment, 
										const char*		message )							RPbdb_MessageSettingsController_messageCallbackMethod(									RPbdb_MessageSettingsController*										message_settings_controller );
	void																					RPbdb_MessageSettingsController_setPanicCallbackMethod(									RPbdb_MessageSettingsController*										message_settings_controller,
																																													void *(panic_callback_method)( RPbdb_Environment*									environment ) );
	void *(panic_callback_method)( RPbdb_Environment*	environment )									RPbdb_MessageSettingsController_panicCallbackMethod(									RPbdb_MessageSettingsController*										message_settings_controller );
	void																					RPbdb_MessageSettingsController_setSiteIsNowReplicationClientCallbackMethod(			RPbdb_MessageSettingsController*										message_settings_controller,
																																													void *(site_is_now_replication_client_callback_method)( RPbdb_Environment*			environment ) );
	void *(site_is_now_replication_client_callback_method)( RPbdb_Environment*	environment )			RPbdb_MessageSettingsController_siteIsNowReplicationClientCallbackMethod(				RPbdb_MessageSettingsController*										message_settings_controller );
	void																					RPbdb_MessageSettingsController_setSiteWonReplicationElectionCallbackMethod(			RPbdb_MessageSettingsController*										message_settings_controller,
																																													void *(site_won_replication_election_callback_method)( RPbdb_Environment*			environment ) );
	void *(site_won_replication_election_callback_method)( RPbdb_Environment*	environment )			RPbdb_MessageSettingsController_siteWonReplicationElectionCallbackMethod(				RPbdb_MessageSettingsController*										message_settings_controller );
	void																					RPbdb_MessageSettingsController_setSiteIsNowMasterOfReplicationGroupCallbackMethod(		RPbdb_MessageSettingsController*										message_settings_controller,
																																													void *(site_is_now_master_of_replication_group_callback_method)( RPbdb_Environment*	environment ) );
	void *(site_is_now_master_of_replication_group_callback_method)( RPbdb_Environment*	environment )	RPbdb_MessageSettingsController_siteIsNowMasterOfReplicationGroupCallbackMethod(		RPbdb_MessageSettingsController*										message_settings_controller );
	void																					RPbdb_MessageSettingsController_setReplicationGroupHasNewMasterCallbackMethod(			RPbdb_MessageSettingsController*										message_settings_controller,
																																													void *(replication_group_has_new_master_callback_method)( RPbdb_Environment*		environment ) );
	void *(replication_group_has_new_master_callback_method)( RPbdb_Environment*	environment )		RPbdb_MessageSettingsController_replicationGroupHasNewMasterCallbackMethod(				RPbdb_MessageSettingsController*										message_settings_controller );
	void																					RPbdb_MessageSettingsController_setReplicationAcknowledgementFailedCallbackMethod(		RPbdb_MessageSettingsController*										message_settings_controller,
																																													void *(replication_acknowledgement_failed_callback_method)( RPbdb_Environment*		environment ) );
	void *(replication_acknowledgement_failed_callback_method)( RPbdb_Environment*	environment )		RPbdb_MessageSettingsController_replicationAcknowledgementFailedCallbackMethod(			RPbdb_MessageSettingsController*										message_settings_controller );
	void																					RPbdb_MessageSettingsController_setReplicationStartupCompletedCallbackMethod(			RPbdb_MessageSettingsController*										message_settings_controller,
																																													void *(replication_startup_completed_callback_method)( RPbdb_Environment*			environment ) );
	void *(replication_startup_completed_callback_method)( RPbdb_Environment*	environment )			RPbdb_MessageSettingsController_replicationStartupCompletedCallbackMethod(				RPbdb_MessageSettingsController*										message_settings_controller );
	void																					RPbdb_MessageSettingsController_setWriteFailedCallbackMethod(							RPbdb_MessageSettingsController*										message_settings_controller,
																																													void *(write_failed_callback_method)( RPbdb_Environment*							environment ) );
	void *(write_failed_callback_method)( RPbdb_Environment*	environment )							RPbdb_MessageSettingsController_writeFailedCallbackMethod(								RPbdb_MessageSettingsController*										message_settings_controller );
*/

#endif

