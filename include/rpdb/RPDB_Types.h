#ifndef RPDB_TYPES
	#define RPDB_TYPES

	#include <db.h>
	#include "RPDB_Constants.h"

	//	File is listed in inverse order of type hierarchy - hierarchy goes bottom to top

typedef struct RPDB_Environment											RPDB_Environment;
typedef struct RPDB_Database												RPDB_Database;
typedef struct RPDB_DatabaseCursorController								RPDB_DatabaseCursorController;
typedef struct RPDB_DatabaseCursor											RPDB_DatabaseCursor;
typedef struct RPDB_DatabaseController										RPDB_DatabaseController;
typedef struct RPDB_DatabaseVerificationController							RPDB_DatabaseVerificationController;
typedef struct RPDB_DatabaseSequenceController								RPDB_DatabaseSequenceController;
typedef struct RPDB_DatabaseSequence										RPDB_DatabaseSequence;
typedef struct RPDB_Error													RPDB_Error;
typedef struct RPDB_ErrorController										RPDB_ErrorController;
typedef struct RPDB_DatabaseJoinController											RPDB_DatabaseJoinController;
typedef struct RPDB_DatabaseJoinCursor												RPDB_DatabaseJoinCursor;
typedef struct RPDB_Lock													RPDB_Lock;
typedef struct RPDB_LockController											RPDB_LockController;
typedef struct RPDB_Log													RPDB_Log;
typedef struct RPDB_LogController											RPDB_LogController;
typedef struct RPDB_LogCursorController									RPDB_LogCursorController;
typedef struct RPDB_LogCursor												RPDB_LogCursor;
typedef struct RPDB_LogSequenceNumber										RPDB_LogSequenceNumber;
typedef struct RPDB_Record													RPDB_Record;
typedef struct RPDB_DBT													RPDB_DBT;
typedef RPDB_DBT 															RPDB_Key;
typedef struct RPDB_SecondaryKeys											RPDB_SecondaryKeys;
typedef RPDB_DBT 															RPDB_Data;
typedef struct RPDB_MemoryPoolFilePageController							RPDB_MemoryPoolFilePageController;
typedef struct RPDB_MemoryPoolFilePage										RPDB_MemoryPoolFilePage;
typedef struct RPDB_MemoryPoolFileController								RPDB_MemoryPoolFileController;
typedef struct RPDB_MemoryPoolFile											RPDB_MemoryPoolFile;
typedef struct RPDB_MemoryPoolController									RPDB_MemoryPoolController;
typedef struct RPDB_Mutex													RPDB_Mutex;
typedef struct RPDB_MutexController										RPDB_MutexController;
typedef struct RPDB_ReplicationController									RPDB_ReplicationController;
typedef struct RPDB_RemoteSite												RPDB_RemoteSite;
typedef struct RPDB_RuntimeStorage											RPDB_RuntimeStorage;
typedef struct RPDB_RuntimeStorageController								RPDB_RuntimeStorageController;
typedef struct RPDB_Transaction											RPDB_Transaction;
typedef struct RPDB_TransactionController									RPDB_TransactionController;
typedef struct RPDB_TransactionSettingsController							RPDB_TransactionSettingsController;
typedef struct RPDB_ThreadSettingsController								RPDB_ThreadSettingsController;
typedef struct RPDB_StatusSettingsController								RPDB_StatusSettingsController;
typedef struct RPDB_SettingsController										RPDB_SettingsController;
typedef struct RPDB_RuntimeStorageSettingsController						RPDB_RuntimeStorageSettingsController;
typedef struct RPDB_ReplicationVerbositySettingsController					RPDB_ReplicationVerbositySettingsController;
typedef struct RPDB_ReplicationTimeoutSettingsController					RPDB_ReplicationTimeoutSettingsController;
typedef struct RPDB_ReplicationSettingsController							RPDB_ReplicationSettingsController;
typedef struct RPDB_ReplicationElectionSettingsController					RPDB_ReplicationElectionSettingsController;
typedef struct RPDB_DatabaseRecordSettingsController								RPDB_DatabaseRecordSettingsController;
typedef struct RPDB_MutexSettingsController								RPDB_MutexSettingsController;
typedef struct RPDB_MessageSettingsController								RPDB_MessageSettingsController;
typedef struct RPDB_MemoryPoolSettingsController							RPDB_MemoryPoolSettingsController;
typedef struct RPDB_MemoryPoolReadWriteSettingsController					RPDB_MemoryPoolReadWriteSettingsController;
typedef struct RPDB_MemoryPoolFileSettingsController						RPDB_MemoryPoolFileSettingsController;
typedef struct RPDB_MemoryPoolFilePageSettingsController					RPDB_MemoryPoolFilePageSettingsController;
typedef struct RPDB_MemoryPoolFileCachePrioritySettingsController			RPDB_MemoryPoolFileCachePrioritySettingsController;
typedef struct RPDB_LogSettingsController									RPDB_LogSettingsController;
typedef struct RPDB_LockSettingsController									RPDB_LockSettingsController;
typedef struct RPDB_LockDeadlockDetectorVerbositySettingsController		RPDB_LockDeadlockDetectorVerbositySettingsController;
typedef struct RPDB_LockDeadlockDetectorSettingsController					RPDB_LockDeadlockDetectorSettingsController;
typedef struct RPDB_DatabaseJoinSettingsController									RPDB_DatabaseJoinSettingsController;
typedef struct RPDB_FileVerbositySettingsController						RPDB_FileVerbositySettingsController;
typedef struct RPDB_FileSettingsController									RPDB_FileSettingsController;
typedef struct RPDB_ErrorSettingsController								RPDB_ErrorSettingsController;
typedef struct RPDB_EnvironmentCacheSettingsController						RPDB_EnvironmentCacheSettingsController;
typedef struct RPDB_DirectorySettingsController							RPDB_DirectorySettingsController;
typedef struct RPDB_DebugVerbositySettingsController						RPDB_DebugVerbositySettingsController;
typedef struct RPDB_DebugSettingsController								RPDB_DebugSettingsController;
typedef struct RPDB_DatabaseVerificationSettingsController					RPDB_DatabaseVerificationSettingsController;
typedef struct RPDB_DatabaseVerbositySettingsController					RPDB_DatabaseVerbositySettingsController;
typedef struct RPDB_DatabaseVariableRecordSettingsController				RPDB_DatabaseVariableRecordSettingsController;
typedef struct RPDB_DatabaseTypeSettingsController							RPDB_DatabaseTypeSettingsController;
typedef struct RPDB_DatabaseTypeRecnoSettingsController					RPDB_DatabaseTypeRecnoSettingsController;
typedef struct RPDB_DatabaseTypeQueueSettingsController					RPDB_DatabaseTypeQueueSettingsController;
typedef struct RPDB_DatabaseTypeHashSettingsController						RPDB_DatabaseTypeHashSettingsController;
typedef struct RPDB_DatabaseTypeBtreeSettingsController					RPDB_DatabaseTypeBtreeSettingsController;
typedef struct RPDB_DatabaseSettingsController								RPDB_DatabaseSettingsController;
typedef struct RPDB_DatabaseSequenceSettingsController						RPDB_DatabaseSequenceSettingsController;
typedef struct RPDB_DatabaseReadWriteSettingsController					RPDB_DatabaseReadWriteSettingsController;
typedef struct RPDB_DatabaseFixedRecordSettingsController					RPDB_DatabaseFixedRecordSettingsController;
typedef struct RPDB_DatabaseErrorSettingsController						RPDB_DatabaseErrorSettingsController;
typedef struct RPDB_DatabaseEncryptionSettingsController					RPDB_DatabaseEncryptionSettingsController;
typedef struct RPDB_DatabaseCursorCacheSettingsController					RPDB_DatabaseCursorCacheSettingsController;
typedef struct RPDB_DatabaseCursorCachePrioritySettingsController			RPDB_DatabaseCursorCachePrioritySettingsController;
typedef struct RPDB_DatabaseCursorSettingsController						RPDB_DatabaseCursorSettingsController;
typedef struct RPDB_DatabaseCursorReadWriteSettingsController				RPDB_DatabaseCursorReadWriteSettingsController;
typedef struct RPDB_DatabaseCompactSettingsController						RPDB_DatabaseCompactSettingsController;
typedef struct RPDB_DatabaseCacheSettingsController						RPDB_DatabaseCacheSettingsController;
typedef struct RPDB_DatabaseCachePrioritySettingsController				RPDB_DatabaseCachePrioritySettingsController;
typedef struct RPDB_DatabaseAssociationSettingsController					RPDB_DatabaseAssociationSettingsController;
typedef struct RPDB_CompactStatus											RPDB_CompactStatus;
typedef struct RPDB_Directory												RPDB_Directory;
typedef struct RPDB_DatabaseOpenedDuringTransaction						RPDB_DatabaseOpenedDuringTransaction;

typedef		RPDB_SECONDARY_KEY_CREATION_RETURN	(*RPDB_SecondaryKeyCallbackMethod)(	RPDB_Database*			secondary_database,
																																									RPDB_Record*			primary_record,
																																									RPDB_SecondaryKeys*	secondary_keys_to_return );

/*************************************
*  Thread Settings Callback Methods  *
*************************************/

typedef		BOOL	(*RPDB_IsThreadAliveCallbackMethod)(	RPDB_Environment*		environment,
															pid_t					process_id,
															db_threadid_t			thread_id,
															BOOL					associated_with_single_process );
typedef		void	(*RPDB_UniqueThreadIdentifierCallbackMethod)(	RPDB_Environment*		environment,
																	pid_t*					process_id,
																	db_threadid_t*			thread_id	);
typedef		char* (*RPDB_FormatThreadAndProcessIdentifierForDisplayCallbackMethod)(	RPDB_Environment*				environment,
																						pid_t				process_id,
																						db_threadid_t		thread_id,
																						char*				string_buffer );

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_TransactionSettingsController	{
	
						//	Parent
						RPDB_SettingsController*				parent_settings_controller;
	
						BOOL									on;
	
						//	Variables
						BOOL									prohibit_sync_on_write;
						BOOL									prohibit_sync_on_commit;
						BOOL									timeout_returns_deny_not_deadlock;
						BOOL									enclose_db_open_in_transaction;
						BOOL									concurrent_data_store_locking;
						BOOL									snapshot_isolation;
						BOOL									degree_one_isolation;
						BOOL									degree_two_isolation;
						BOOL									enclose_all_activity_in_transaction;
						BOOL									environmental_snapshot_isolation;
						BOOL									sync_on_commit;
						BOOL									wait_for_locks;
						long									maximum_number_of_transactions_to_recover;
						uint32_t								timeout_in_microseconds;
						uint32_t								max_open;
						time_t*									recovery_timestamp;
	
						BOOL									started_transaction_recover;
	/*
						//	Callback Public Methods
						int (*rollbackward_callback_method)(	RPDB_Environment*				environment,                                                                                                                                                                	
																RPDB_Record*		transaction_log_record );
						int (*rollforward_callback_method)(		RPDB_Environment*				environment,                                                           				
														   		RPDB_Record*		transaction_log_record );
						int (*abort_callback_method)(			RPDB_Environment*				environment,                                                           				
													 			RPDB_Record*		transaction_log_record );
						int (*apply_callback_method)(			RPDB_Environment*				environment,                                                           				
													 			RPDB_Record*		transaction_log_record );
	*/
	
						RPDB_SettingsController*				environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseRecordSettingsController	{

						//	Parent
						RPDB_DatabaseSettingsController*		parent_database_settings_controller;
						                                        
						RPDB_Record*							parent_record;
                                                                
						BOOL									database_allocates_memory_using_malloc;
						BOOL									database_allocates_memory_using_realloc;
						BOOL									application_allocates_memory;
						BOOL									database_free_memory;
						BOOL									partial_access;
						BOOL									record_contains_multiple_data;
						BOOL									sync_prior_to_write_return;
						uint32_t								data_buffer_size;
						uint32_t								partial_read_write_size;
						uint32_t								partial_read_write_offset;
						                                        
						uint32_t								flags;

						RPDB_SettingsController*				environment_settings_controller;

					};


								/****************************
								*	Data Type Definitions	*
								****************************/

								struct RPDB_MemoryPoolFilePage	{

									//	Parent
									RPDB_MemoryPoolFilePageController*										parent_memory_pool_file_page_controller;

									db_recno_t					runtime_identifier;

									db_pgno_t*																page_address;

									void*																	page_data;

									DB_MPOOLFILE*															wrapped_bdb_memory_pool_file;

									RPDB_SettingsController*								environment_settings_controller;
									RPDB_MemoryPoolFilePageSettingsController*				settings_controller;
									RPDB_MemoryPoolFilePageSettingsController*				environment_level_settings_controller;
								};

								/****************************
								*	Data Type Definitions	*
								****************************/

								struct RPDB_MemoryPoolFilePageController	{

									//	Parent
									RPDB_MemoryPoolFile*										parent_memory_pool_file;

									RPDB_Database*													runtime_storage_database;

									RPDB_SettingsController*								environment_settings_controller;
									RPDB_MemoryPoolFilePageSettingsController*				settings_controller;
									RPDB_MemoryPoolFilePageSettingsController*				environment_level_settings_controller;
								};

							/****************************
							*	Data Type Definitions	*
							****************************/

							struct RPDB_MemoryPoolFile	{

								//	Parent
								RPDB_MemoryPoolFileController*								parent_memory_pool_file_controller;

								db_recno_t					runtime_identifier;

								//	Wrapped BDB memory pool file
								DB_MPOOLFILE*												wrapped_bdb_memory_pool_file;
								
								RPDB_SettingsController*							environment_settings_controller;
								RPDB_MemoryPoolFileSettingsController*				settings_controller;
								RPDB_MemoryPoolFileSettingsController*				environment_level_settings_controller;
							};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct RPDB_MemoryPoolFileController	{

							//	Parent
							RPDB_MemoryPoolController*			parent_memory_pool_controller;
							
							RPDB_Database*									runtime_storage_database;
/*
							int									(*page_in_method)(	RPDB_Environment*			environment,
							   														void*			page_data,
							   														RPDB_Data*		page_cookie	);

							int									(*page_out_method)(	RPDB_Environment*			environment,
							   														void*			page_data,
							   														RPDB_Data*		page_cookie	);
*/
							RPDB_SettingsController*							environment_settings_controller;
							RPDB_MemoryPoolFileSettingsController*				settings_controller;
							RPDB_MemoryPoolFileSettingsController*				environment_level_settings_controller;
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_MemoryPoolReadWriteSettingsController	{

							//	Parent
							RPDB_MemoryPoolSettingsController*							parent_memory_pool_settings_controller;

							int															memory_pool_read_write_settings_controller;
							int															max_open_files;
							int															max_sequential_writes;
							db_timeout_t													time_to_sleep_before_next_write;
							size_t															max_mapped_db_size;
							BOOL														page_fault_shared_regions;

							RPDB_SettingsController*									environment_settings_controller;

						};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct RPDB_MemoryPoolFilePageSettingsController	{

								//	Parent
								RPDB_MemoryPoolFileSettingsController*						parent_memory_pool_file_settings_controller;

								BOOL														get_page_creates_page_if_does_not_exist;
								BOOL														get_page_writes_copy_before_eviction;
								BOOL														get_page_writes_before_eviction_without_copy;
								BOOL														get_page_returns_last_page;
								BOOL														get_page_creates_new_page;

								RPDB_SettingsController*									environment_settings_controller;

							};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct RPDB_MemoryPoolFileCachePrioritySettingsController	{

								//	Parent
								RPDB_MemoryPoolFileSettingsController*						parent_memory_pool_file_settings_controller;

								DB_CACHE_PRIORITY											priority;

								RPDB_SettingsController*									environment_settings_controller;
							};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_MemoryPoolFileSettingsController	{

							//	Parent
							RPDB_MemoryPoolSettingsController*						parent_memory_pool_settings_controller;

							RPDB_MemoryPoolFile*													parent_memory_pool_file;

							uint																					create_with_number_initial_bytes;
							uint8_t*																			file_id;
							int																						file_type;
							int																						log_sequence_number_offset;
							uint64_t																			page_size_in_bytes;
							uint64_t																			max_file_size_in_bytes;
							RPDB_Record*																	cookie;

							RPDB_MemoryPoolFileCachePrioritySettingsController*	priority_settings_controller;
							RPDB_MemoryPoolFilePageSettingsController*				page_settings_controller;

							RPDB_SettingsController*								environment_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_MemoryPoolSettingsController	{
	
						//	Parent
						RPDB_SettingsController*								parent_settings_controller;
	
						BOOL													on;
						BOOL													memory_mapping;						
						BOOL													do_not_write_to_temporary_backing_file;
						BOOL													remove_file_with_last_reference;
						BOOL													use_system_memory_for_storage;
						BOOL													use_application_memory_for_storage;
						BOOL													threaded;
						BOOL													database_allocates_memory_using_malloc;
						BOOL													database_allocates_memory_using_realloc;
						BOOL													application_allocates_memory;
						BOOL													database_free_memory;
						BOOL													pagesize_factor_mismatch_should_fail;
	
						RPDB_MemoryPoolFileSettingsController*					file_settings_controller;
						RPDB_MemoryPoolReadWriteSettingsController*			read_write_settings_controller;
	
						RPDB_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseJoinSettingsController	{

						//	Parent
						RPDB_DatabaseSettingsController*								parent_database_settings_controller;

						BOOL													degree_one_isolation;
						BOOL													use_write_locks_instead_of_read_locks;
						BOOL													sort_before_join;

						RPDB_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DirectorySettingsController	{

						//	Parent
						RPDB_SettingsController*								parent_settings_controller;

						char*													home_directory_path;
						
						RPDB_Directory*										directories;

						RPDB_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_RuntimeStorageSettingsController	{
							
						//	Parent
						RPDB_SettingsController*								parent_settings_controller;
		
						BOOL													store_in_application_memory;
						BOOL													store_in_system_memory;
						BOOL													store_on_disk;
						BOOL													log_runtime_storage_activity;

						BOOL													automatic_default_environment;
						
						RPDB_SettingsController*								environment_settings_controller;
					};
	
							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct RPDB_LockDeadlockDetectorVerbositySettingsController	{

								//	Parent
								RPDB_LockDeadlockDetectorSettingsController*								parent_lock_deadlock_detector_settings_controller;

								BOOL																		display_additional_information_during_deadlock_detection;
								BOOL																		display_wait_table_during_deadlock_detection;

								RPDB_SettingsController*								environment_settings_controller;
							};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_LockDeadlockDetectorSettingsController	{

							//	Parent
							RPDB_LockSettingsController*								parent_lock_settings_controller;

							uint32_t													deadlock_settings;

							RPDB_LockDeadlockDetectorVerbositySettingsController*		verbosity_settings_controller;

							RPDB_SettingsController*									environment_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_LockSettingsController	{

						//	Parent
						RPDB_SettingsController*								parent_settings_controller;

						//	Variables
						BOOL													on;
						BOOL													prohibit_locking;
						BOOL													timeout_returns_deny_not_deadlock;
						BOOL													not_waiting_for_conflicts;
						BOOL													lock_for_environment_not_database;
						uint32_t														timeout;
						uint8_t*												conflict_matrix;
						int														conflict_matrix_size;
						uint32_t												max_lockers;
						uint32_t												max_locks;
						uint32_t														max_objects;
						uint32_t														partitions;

						RPDB_LockDeadlockDetectorSettingsController*			deadlock_detector_settings_controller;

						RPDB_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_LogSettingsController	{

						//	Parent
						RPDB_SettingsController*								parent_settings_controller;

						//	Variables
						BOOL													on;
						BOOL													disable_system_buffering;
						BOOL													flush_before_return_from_write;
						BOOL													autoremove;
						BOOL													log_in_memory;
						BOOL													zero_at_creation;
						BOOL													force_flush_after_record_write;

						uint32_t												buffer_size;
						char*													directory;
						int														mode;
						uint32_t												max_size;
						uint32_t												max_region_size;

						RPDB_SettingsController*								environment_settings_controller;
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_ReplicationVerbositySettingsController	{
	
							//	Parent
							RPDB_ReplicationSettingsController*								parent_replication_settings_controller;
	
							BOOL																display_all_replication_information;
							BOOL																display_election_information;
							BOOL																display_replication_master_lease_information;
							BOOL																display_misc_processing_information;
							BOOL																display_message_processing_information;
							BOOL																display_client_synchronization_information;
							BOOL																display_manager_connection_failure_information;
							BOOL																display_manager_misc_processing;
	
							RPDB_SettingsController*											environment_settings_controller;
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_ReplicationTimeoutSettingsController	{
	
							//	Parent
							RPDB_ReplicationSettingsController*								parent_replication_settings_controller;
	
							uint32_t															timeout;
							uint32_t															wait_time_before_checkpoint_write;
							uint32_t															wait_time_before_retry_connection;
							uint32_t															election_timeout;
							uint32_t															wait_time_before_retry_election;
							uint32_t															full_election_participation_timeout;
							uint32_t															heartbeat_monitor_pulse;
							uint32_t															heartbeat_broadcast_pulse;
							uint32_t															lease_timeout;
	
							RPDB_SettingsController*											environment_settings_controller;
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_ReplicationElectionSettingsController	{
	
							//	Parent
							RPDB_ReplicationSettingsController*								parent_replication_settings_controller;
	
							int																	number_of_sites_required_for_election;
							int																	number_of_votes_required_for_election;
	
							BOOL																wait_for_all_clients;
							BOOL																wait_for_all_electable_peers;
							BOOL																never_wait;
							BOOL																wait_for_at_least_one_client;
							BOOL																wait_for_at_least_one_electable_peer;
							BOOL																wait_for_minimum_electable_peers_for_durable_election;
							
							int																	current_ack_policy;
	
							RPDB_SettingsController*											environment_settings_controller;
						};


					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_ReplicationSettingsController	{
	
						//	Parent
						RPDB_SettingsController*								parent_settings_controller;
	
						BOOL													on;
						BOOL													client_to_client_synchronization;
						BOOL													single_bulk_transfer;
						BOOL													delay_new_sync_until_explicit_call;
						BOOL													use_master_leases;
						BOOL													prohibit_auto_init_for_old_clients;
						BOOL													prohibit_wait;
						BOOL													require_strict_majority;
						BOOL													is_master;
						BOOL													is_client;
						BOOL													start_as_client_or_rally_election;
						;
						uint64_t												limit_in_gbytes;
						uint64_t												limit_in_bytes;
						char*													host;
						u_int													port;
						uint32_t												site_count;
						uint32_t												priority_order_number;
						uint32_t												retransmission_threshold_minimum;
						uint32_t												retransmission_threshold_maximum;
						uint32_t												slowest_clock_value;
						uint32_t												fastest_clock_value;
	
						RPDB_Record*											additional_start_information;
	
						RPDB_ReplicationElectionSettingsController*			acknowledgement_policy_settings_controller;
						RPDB_ReplicationTimeoutSettingsController*				timeout_settings_controller;	
						RPDB_ReplicationVerbositySettingsController*			verbosity_settings_controller;	
	
						RPDB_SettingsController*							environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_MutexSettingsController	{
	
						//	Parent
						RPDB_SettingsController*								parent_settings_controller;
	
						uint32_t												spin_times_before_blocking_for_test_and_spin_mutexes;
						uint32_t												max_allowable_mutexes;
						uint32_t												increment_for_adding_mutexes;
						uint32_t												mutex_alignment;
						BOOL													associated_with_single_process;
						BOOL													self_blocking;
	
						RPDB_SettingsController*								environment_settings_controller;
	
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseVerificationSettingsController	{

							//	Parent
							RPDB_DatabaseSettingsController*						parent_database_settings_controller;

							FILE*													file;
							BOOL													file_is_open;
							
							char*													file_path;
							BOOL													aggressive_key_data_pair_dump;
							BOOL													printable_characters;
							BOOL													skip_order_checking;
							BOOL													only_order_check;
							BOOL													force_order_check;
							BOOL													has_done_unordered_check;
							
							RPDB_SettingsController*								environment_settings_controller;
							
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseVariableRecordSettingsController	{

							//	Parent
							RPDB_DatabaseSettingsController*						parent_database_settings_controller;

							int														record_delimeter;
							//	FIX	- what happened to these??
							BOOL													index_primary;
							BOOL													secondary_key_is_immutable;

							RPDB_SettingsController*								environment_settings_controller;

						};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct RPDB_DatabaseCursorReadWriteSettingsController	{

								//	Parent
								RPDB_DatabaseCursorSettingsController*						parent_database_cursor_settings_controller;

								BOOL														permit_write;
								BOOL														ignore_lease;
								BOOL														write_locks_instead_of_read_locks;
								BOOL														multiple_data_items;
								BOOL														return_multiple_key_data_pairs;

								RPDB_SettingsController*									environment_settings_controller;

							};

								/****************************
								 *	Data Type Definitions	*
								 ****************************/

								struct RPDB_DatabaseCursorCachePrioritySettingsController	{
		
									//	Parent
									RPDB_DatabaseCursorCacheSettingsController*						parent_database_cursor_cache_settings_controller;
		
									DB_CACHE_PRIORITY													priority;
		
									RPDB_SettingsController*											environment_settings_controller;
		
								};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct RPDB_DatabaseCursorCacheSettingsController	{

								//	Parent
								RPDB_DatabaseCursorSettingsController*						parent_database_cursor_settings_controller;

								//	FIX - seems like these are missing function-wise? did something get deleted? check out this controller
								int															number_cache_regions;
								uint32_t													max_size_in_bytes;

								RPDB_DatabaseCursorCachePrioritySettingsController*		priority_settings_controller;

								RPDB_SettingsController*									environment_settings_controller;

							};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseCursorSettingsController	{

							//	Parent
							RPDB_DatabaseSettingsController*						parent_database_settings_controller;
							RPDB_DatabaseCursor*									parent_database_cursor;

							//	Variables
							BOOL													duplicate_retains_location;

							//	Controllers
							RPDB_DatabaseCursorCacheSettingsController*			cache_controller;
							RPDB_DatabaseCursorReadWriteSettingsController*		read_write_settings_controller;

							RPDB_SettingsController*								environment_settings_controller;

						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseSequenceSettingsController	{
	
							//	Parent
							RPDB_DatabaseSettingsController*						parent_database_settings_controller;
	
							RPDB_DatabaseSequence*									parent_sequence;
	
							BOOL													increasing;
							BOOL													decreasing;
							BOOL													wrapping;
							db_seq_t												range_minimum;
							db_seq_t												range_maximum;
							int32_t													number_of_cached_elements;
							db_seq_t												initial_value;
							int32_t													default_step_value;
	
							RPDB_SettingsController*								environment_settings_controller;
	
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseReadWriteSettingsController	{
	
							//	Parent
							RPDB_DatabaseSettingsController*						parent_database_settings_controller;
	
							char*													filename;
							BOOL													prohibit_sync_on_close;
							BOOL													ignore_lease;
							BOOL													return_multiple;
							BOOL													append_data;
							BOOL													prohibit_duplicate_data;
							BOOL													prohibit_overwrite;
							BOOL													prohibit_page_compaction;
							BOOL													return_pages_to_filesystem;
							BOOL													multiple_targets;
							BOOL													partial_access;
							BOOL													truncate;
							BOOL													write_locks_instead_of_read_locks;
							BOOL													permit_duplicates;
							BOOL													sort_duplicates;

							RPDB_SettingsController*								environment_settings_controller;
	
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseTypeRecnoSettingsController	{
	
							//	Parent
							RPDB_DatabaseTypeSettingsController*		parent_database_type_settings_controller;
	
							BOOL										record_renumbering;
							BOOL										snapshot_isolation;
							char*										source_file_path;
	/*
							void										(*append_callback_method)(	RPDB_Database*		database,
																								  struct RPDB_Record*		record );
	*/
							RPDB_SettingsController*					environment_settings_controller;

						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseTypeQueueSettingsController	{
	
							//	Parent
							RPDB_DatabaseTypeSettingsController*						parent_database_type_settings_controller;
	
							BOOL														return_key_data_pairs_in_order;
							uint32_t													number_of_pages_for_underlying_data;
	
							RPDB_SettingsController*									environment_settings_controller;
	
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseTypeHashSettingsController	{
	
							//	Parent
							RPDB_DatabaseTypeSettingsController*		parent_database_type_settings_controller;
	
							//	Variables                               
							uint32_t									table_size;
							uint32_t									density;	
	
	/*
							//	Callback Public Methods
							uint32_t									(*hash_method)(					RPDB_Database*		database, 
																					   const void*			bytes,    
																					   uint32_t			length );
							int											(*compare_method)(				RPDB_Database*		database, 
																						  const DBT*			data_one, 
																						  const DBT*			data_two );
							int											(*duplicate_compare_method)(	RPDB_Database*		database, 
																									const DBT*			data_one, 
																									const DBT*			data_two );
	*/
							RPDB_SettingsController*				environment_settings_controller;

						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseTypeBtreeSettingsController	{
	
							//	Parent
							RPDB_DatabaseTypeSettingsController*		parent_database_type_settings_controller;
	
							BOOL										record_number_retrieval;
							BOOL										reverse_splitting;
							uint32_t									minimum_keys_per_page;
	/*
							size_t										(*prefix_compare_method)(		RPDB_Database*		database, 
																								 const DBT*			data_one, 
																								 const DBT*			data_two );
							int											(*compare_method)(				DBRPDB_Database*	database, 
																						  const DBT*			data_one, 
																						  const DBT*			data_two );
							int											(*duplicate_compare_method)(	RPDB_Database*		database, 
																									const DBT*			data_one, 
																									const DBT*			data_two );
	*/
	
							RPDB_SettingsController*				environment_settings_controller;

						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseTypeSettingsController	{
	
						//	Parent
						RPDB_DatabaseSettingsController*						parent_database_settings_controller;

						RPDB_Database*											parent_database;

						DBTYPE													default_database_type;
						RPDB_DatabaseTypeBtreeSettingsController*				btree_settings_controller;
						RPDB_DatabaseTypeHashSettingsController*				hash_settings_controller;
						RPDB_DatabaseTypeQueueSettingsController*				queue_settings_controller;
						RPDB_DatabaseTypeRecnoSettingsController*				recno_settings_controller;
	
						RPDB_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseVerbositySettingsController	{
	
						//	Parent
						RPDB_DatabaseSettingsController*						parent_database_settings_controller;
	
						BOOL													display_additional_information_for_db_register_flag;
	
						RPDB_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseEncryptionSettingsController	{
	
						//	Parent
						RPDB_DatabaseSettingsController*						parent_database_settings_controller;
	
						BOOL													encrypted;
						
						char*													password;
	
						RPDB_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseCompactSettingsController	{
	
						//	Parent
						RPDB_DatabaseSettingsController*						parent_database_settings_controller;
	
						int														fill_percent;
						int														max_pages_to_compact;
						int														timeout;
	
						RPDB_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseAssociationSettingsController	{
	
						//	Parent
						RPDB_DatabaseSettingsController*						parent_database_settings_controller;
	
						BOOL													index_primary_database;
						BOOL													secondary_key_is_immutable;
	
						RPDB_SettingsController*								environment_settings_controller;
	
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseCachePrioritySettingsController	{
	
							//	Parent
							RPDB_DatabaseCacheSettingsController*						parent_database_cache_settings_controller;
	
							DB_CACHE_PRIORITY											priority;
	
							RPDB_SettingsController*								environment_settings_controller;
	
						};
	
					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseCacheSettingsController	{
	
						//	Parent
						RPDB_DatabaseSettingsController*						parent_database_settings_controller;
	
						int														number_cache_regions;
						uint32_t												max_size_in_bytes;
	
						RPDB_DatabaseCachePrioritySettingsController*			priority_settings_controller;
		
						RPDB_SettingsController*								environment_settings_controller;
		
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseFixedRecordSettingsController	{

						//	Parent
						RPDB_DatabaseSettingsController*						parent_database_settings_controller;

						uint32_t												record_length;
						int														record_padding_byte;

						RPDB_SettingsController*								environment_settings_controller;

					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseErrorSettingsController	{
	
						//	Parent
						RPDB_DatabaseSettingsController*		parent_database_settings_controller;
	
						//	Variables               
						FILE*									error_file;
						BOOL									error_file_is_open;
						char*									error_file_path;
						char*									error_prefix;
	/*
						//	Callback Public Methods
						void									(*error_callback_method)(	RPDB_Environment*			environment,                                                                                                                                             
																						 const char*		error_prefix_string,                                                                                                                                                            
																						 const char*		error_message	);
	*/
	
						RPDB_SettingsController*				environment_settings_controller;

					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_DatabaseSettingsController	{
	
					//	Parent
					RPDB_SettingsController*								parent_settings_controller;
	
					RPDB_Database*											parent_database;
	
					BOOL													on;
					BOOL													checksum;
					BOOL													transaction_durability_off;
					uint32_t												pagesize;
					BOOL													big_endian;
					BOOL													little_endian;
					BOOL													is_byteswapped;
	
					RPDB_DatabaseJoinSettingsController*							join_settings_controller;
					RPDB_DatabaseErrorSettingsController*					error_settings_controller;
					RPDB_DatabaseFixedRecordSettingsController*			fixed_record_settings_controller;
					RPDB_DatabaseCacheSettingsController*					cache_settings_controller;
					RPDB_DatabaseAssociationSettingsController*			association_settings_controller;
					RPDB_DatabaseCompactSettingsController*				compact_settings_controller;
					RPDB_DatabaseEncryptionSettingsController*				encryption_settings_controller;
					RPDB_DatabaseVerbositySettingsController*				verbosity_settings_controller;
					RPDB_DatabaseTypeSettingsController*					type_settings_controller;
					RPDB_DatabaseSequenceSettingsController*					sequence_settings_controller;
					RPDB_DatabaseReadWriteSettingsController*					read_write_settings_controller;
					RPDB_DatabaseCursorSettingsController*					cursor_settings_controller;
					RPDB_DatabaseVariableRecordSettingsController*					variable_record_settings_controller;
					RPDB_DatabaseVerificationSettingsController*					verification_settings_controller;
					RPDB_DatabaseRecordSettingsController*							record_settings_controller;

					RPDB_SettingsController*								environment_settings_controller;

				};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_StatusSettingsController	{

					//	Parent
					RPDB_SettingsController*								parent_settings_controller;

					BOOL													display_all;
					BOOL													reset_after_display;
					BOOL													display_for_all_subsystems;
					BOOL													no_traversal;
					BOOL													degree_two_isolation;
					BOOL													degree_one_isolation;

					RPDB_SettingsController*								environment_settings_controller;

				};
				
				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_MessageSettingsController	{
	
					//	Parent
					RPDB_SettingsController*			parent_settings_controller;
	
					FILE*								message_file;
					BOOL								message_file_is_open;
					char*								message_file_path;
	/*
					void								(*message_callback_method)(										RPDB_Environment*			environment, 
																				   const char*		message );
					void								*(panic_callback_method)(										RPDB_Environment*			environment );									
					void								*(site_is_now_replication_client_callback_method)(				RPDB_Environment*			environment );			
					void								*(site_won_replication_election_callback_method)(				RPDB_Environment*			environment );			
					void								*(site_is_now_master_of_replication_group_callback_method)(		RPDB_Environment*			environment );	
					void								*(replication_group_has_new_master_callback_method)(			RPDB_Environment*			environment );		
					void								*(replication_acknowledgement_failed_callback_method)(			RPDB_Environment*			environment );		
					void								*(replication_startup_completed_callback_method)(				RPDB_Environment*			environment );			
					void								*(write_failed_callback_method)(								RPDB_Environment*			environment );						
*/
					RPDB_SettingsController*				environment_settings_controller;

				};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_ErrorSettingsController	{

					//	Parent
					RPDB_SettingsController*		parent_settings_controller;

					FILE*							error_file;
					char*							error_file_path;
					BOOL							error_file_is_open;
					char*							prefix;
/*
					void							(*error_callback_method)(	RPDB_Environment*					environment,                                                                                                                  
																			 const char*				error_prefix,                                                                                                                               
																			 const char*				error_message );
*/
					RPDB_SettingsController*				environment_settings_controller;

				};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_ThreadSettingsController	{

					//	Parent
					RPDB_SettingsController*													parent_settings_controller;

					//	Variables
					BOOL																		on;
					uint32_t																	thread_count;

					RPDB_IsThreadAliveCallbackMethod											is_thread_alive_callback_method;
					RPDB_UniqueThreadIdentifierCallbackMethod									unique_thread_identifier_callback_method;
					RPDB_FormatThreadAndProcessIdentifierForDisplayCallbackMethod				format_thread_and_process_identifier_for_display_callback_method;
					RPDB_SettingsController*													environment_settings_controller;

				};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_FileVerbositySettingsController	{

						//	Parent
						RPDB_FileSettingsController*								parent_file_settings_controller;

						BOOL														display_additional_information_during_open_close_rename_file_operations;
						BOOL														display_additional_information_during_all_file_operations;
						
						RPDB_SettingsController*								environment_settings_controller;
						
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_FileSettingsController	{

					//	Parent
					RPDB_SettingsController*								parent_settings_controller;

					char*													intermediate_directory_mode;
					char*													temp_directory;
					BOOL													permit_environment_based_file_naming;
					BOOL													use_environment_home_permissions_for_file_naming;
					BOOL													create_if_necessary;
					BOOL													error_if_exists_on_create;
					BOOL													open_read_only;
					BOOL													force_removal;
					BOOL													xa_compliant;
					int														file_creation_mode;

					RPDB_FileVerbositySettingsController*					verbosity_settings_controller;

					RPDB_SettingsController*								environment_settings_controller;

				};
		
				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_EnvironmentCacheSettingsController	{

					//	Parent
					RPDB_SettingsController*								parent_settings_controller;

					BOOL													buffering;
					uint64_t												size_in_bytes;
					uint64_t												max_size_in_bytes;


					RPDB_SettingsController*								environment_settings_controller;
				};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DebugVerbositySettingsController	{

						//	Parent
						RPDB_DebugSettingsController*								parent_debug_settings_controller;

						BOOL														display_additional_information_during_recovery;

						RPDB_SettingsController*									environment_settings_controller;
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_DebugSettingsController	{

					//	Parent
					RPDB_SettingsController*								parent_settings_controller;
					BOOL													check_for_environment_failure_during_open;
					BOOL													run_normal_recovery_before_opening_environment;
					BOOL													run_catastrophic_recovery_before_opening_environment;
					BOOL													open_in_lockdown;
					BOOL													check_for_recovery_on_load;
					BOOL													prohibit_panic;
					BOOL													panic;
					BOOL													yield_cpu_for_stress_test;

					RPDB_DebugVerbositySettingsController*					verbosity_settings_controller;

					RPDB_SettingsController*								environment_settings_controller;
				};

			/****************************
			 *	Data Type Definitions	*
			 ****************************/

			struct RPDB_SettingsController	{
	
				//	Parent
				RPDB_Environment*										parent_environment;
				
				//	Variables
				long													shm_key;
	
				//	Controllers
				RPDB_DatabaseSettingsController*						database_settings_controller;
				RPDB_DebugSettingsController*							debug_settings_controller;
				RPDB_EnvironmentCacheSettingsController*				cache_settings_controller;
				RPDB_FileSettingsController*							file_settings_controller;
				RPDB_ThreadSettingsController*							thread_settings_controller;
				RPDB_ErrorSettingsController*							error_settings_controller;
				RPDB_MessageSettingsController*							message_settings_controller;
				RPDB_StatusSettingsController*							status_settings_controller;
				RPDB_MutexSettingsController*							mutex_settings_controller;
				RPDB_ReplicationSettingsController*							replication_settings_controller;
				RPDB_LogSettingsController*							log_settings_controller;
				RPDB_LockSettingsController*							lock_settings_controller;
				RPDB_RuntimeStorageSettingsController*							runtime_storage_settings_controller;
				RPDB_DirectorySettingsController*							directory_settings_controller;
				RPDB_MemoryPoolSettingsController*							memory_pool_settings_controller;
				RPDB_TransactionSettingsController*					transaction_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct RPDB_Transaction	{

					//	Parent
					RPDB_TransactionController*							parent_transaction_controller;
					
					db_recno_t										runtime_identifier;
					
					//	Variables
					char*													name;

					BOOL												is_open;

					uint8_t													global_id;

					RPDB_DatabaseOpenedDuringTransaction*				databases_opened_during_transaction;

					//	Wrapped BDB Transaction
					DB_TXN*													wrapped_bdb_transaction;

					RPDB_SettingsController*							environment_settings_controller;
					RPDB_TransactionSettingsController*				settings_controller;
					RPDB_TransactionSettingsController*				environment_level_settings_controller;
				};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPDB_TransactionController	{

				//	Parent
				RPDB_Environment*										parent_environment;

				RPDB_Database*	runtime_storage_database;

				uint32_t												current_transaction_index;
				RPDB_Transaction**										transactions;

				//	Variables
				u_int32_t												maximum_number_of_transactions_to_recover;
				u_int32_t												current_transaction_depth;

				RPDB_SettingsController*							environment_settings_controller;
				RPDB_TransactionSettingsController*				settings_controller;
			};


			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPDB_RuntimeStorageController	{

				//	Variables
				RPDB_Environment*												runtime_environment;
				RPDB_Environment*												default_environment;

				RPDB_DatabaseCursor*										database_cursor;

				//	Runtime Storage instances are stored by name--&db_env
				RPDB_Database*													runtime_storages_database;

				//	All RPDB_Environment* and RPDB_Database* are stored by their wrapped_bdb_database DB* in these databases
				RPDB_Database*													environment_reference_database;
				RPDB_Database*													database_reference_database;

				//	Unlike other controllers, the environmental runtime storage settings controller is stored inside the runtime storage controller
				RPDB_RuntimeStorageSettingsController*							settings_controller;
			};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_RemoteSite	{
	
					//	Parent
					RPDB_ReplicationController*							parent_replication_controller;
	
					db_recno_t										runtime_identifier;

					//	Variables
					
					char*													host;
					u_int													port;
					
					int														replication_environment_id;
					
					BOOL													connected;
					
					long													hard_timeout;
					long													soft_timeout;
	
					RPDB_SettingsController*							environment_settings_controller;
					RPDB_ReplicationSettingsController*				settings_controller;
					RPDB_ReplicationSettingsController*				environment_level_settings_controller;
				};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPDB_ReplicationController	{

				//	Parent
				RPDB_Environment*													parent_environment;

				RPDB_Database*	runtime_storage_database;

				u_int													site_count;

				//	Variables
				int														replication_environment_id;
				RPDB_RemoteSite**										remote_site_list;

				RPDB_SettingsController*							environment_settings_controller;
				RPDB_ReplicationSettingsController*				settings_controller;
				RPDB_ReplicationSettingsController*				environment_level_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct RPDB_Mutex	{

					//	Parent
					RPDB_MutexController*										parent_mutex_controller;

					db_recno_t										runtime_identifier;

					db_mutex_t													wrapped_bdb_mutex;

					RPDB_SettingsController*					environment_settings_controller;
					RPDB_MutexSettingsController*				settings_controller;
					RPDB_MutexSettingsController*				environment_level_settings_controller;
				};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPDB_MutexController	{

				//	Parent
				RPDB_Environment*													parent_environment;

				RPDB_Database*	runtime_storage_database;

				RPDB_SettingsController*					environment_settings_controller;
				RPDB_MutexSettingsController*				settings_controller;
				RPDB_MutexSettingsController*				environment_level_settings_controller;
			};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPDB_MemoryPoolController	{

				//	Parent
				RPDB_Environment*											parent_environment;

				//	Variables
				int												memory_space_for_pages;
/*
				//	Callbacks
				void*											(*malloc_method)(	size_t );
				void*											(*realloc_method)(	void*, 
																					size_t );
				void*											(*free_method)(		void* );
*/
				RPDB_MemoryPoolFileController*					file_controller;

				RPDB_SettingsController*						environment_settings_controller;
				RPDB_MemoryPoolSettingsController*				settings_controller;
				RPDB_MemoryPoolSettingsController*				environment_level_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct RPDB_LogCursor	{

					//	Parent
					RPDB_LogCursorController*					parent_log_cursor_controller;

					db_recno_t										runtime_identifier;

					//	Wrapped BDB log database_cursor
					DB_LOGC*									wrapped_bdb_log_cursor;

					RPDB_SettingsController*					environment_settings_controller;
					RPDB_LogSettingsController*				settings_controller;
					RPDB_LogSettingsController*				environment_level_settings_controller;
				};

							/****************************
							*	Data Type Definitions	*
							****************************/

							struct RPDB_LogSequenceNumber	{

								//	Parent
								RPDB_Log*									parent_log;

								//	Wrapped BDB log database_cursor
								DB_LSN*										wrapped_bdb_log_sequence_number;

								RPDB_SettingsController*					environment_settings_controller;
								RPDB_LogSettingsController*				settings_controller;
								RPDB_LogSettingsController*				environment_level_settings_controller;
							};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct RPDB_Log	{

							//	Parent
							RPDB_LogController*						parent_log_controller;

							db_recno_t										runtime_identifier;

							//	Variables
							RPDB_Record*								record;
							RPDB_LogSequenceNumber*					log_sequence_number;
							
							char*										filename;

							RPDB_SettingsController*					environment_settings_controller;
							RPDB_LogSettingsController*				settings_controller;
							RPDB_LogSettingsController*				environment_level_settings_controller;
						};

					/****************************
					*	Data Type Definitions	*
					****************************/

					struct RPDB_LogController	{

						//	Parent
						RPDB_Environment*								parent_environment;

						RPDB_Database*									runtime_storage_database;

						RPDB_LogCursorController*						cursor_controller;

						RPDB_SettingsController*					environment_settings_controller;
						RPDB_LogSettingsController*				settings_controller;
						RPDB_LogSettingsController*				environment_level_settings_controller;
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_LogCursorController	{
					
					//	Parent
					RPDB_LogController*						parent_log_controller;

					RPDB_Database*	runtime_storage_database;
					
					RPDB_SettingsController*					environment_settings_controller;
					RPDB_LogSettingsController*				settings_controller;
					RPDB_LogSettingsController*				environment_level_settings_controller;
				};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct RPDB_Lock	{

					//	Parent
					RPDB_LockController*						parent_lock_controller;

					db_recno_t										runtime_identifier;

					//	Variables
					int											mode;

					uint32_t									timeout;

					//	Object being locked
					void*										object;

					//	Wrapped BDB lock
					DB_LOCK										wrapped_bdb_lock;

					RPDB_SettingsController*					environment_settings_controller;
					RPDB_LockSettingsController*				settings_controller;
					RPDB_LockSettingsController*				environment_level_settings_controller;
				};
	
			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPDB_LockController	{

				//	Parent
				RPDB_Environment*							parent_environment;
				
				RPDB_Database*	runtime_storage_database;
				
				//	Variables
				uint32_t									locker_id;
				RPDB_Lock**									queued_locks;
				int											number_of_queued_locks;
				int											number_of_locks_last_cleared;

				RPDB_SettingsController*					environment_settings_controller;
				RPDB_LockSettingsController*				settings_controller;
				RPDB_LockSettingsController*				environment_level_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct RPDB_DatabaseJoinCursor	{

					//	Parent
					RPDB_DatabaseJoinController*						parent_join_controller;

					db_recno_t										runtime_identifier;

					char*										name;

					//	Variables
					RPDB_Database*								primary_database;

					RPDB_DatabaseCursor**						cursor_list;
					
					BOOL										is_open;
					
					//	Wrapped BDB database_cursor
					DBC*										wrapped_bdb_join_cursor;
					DBC**										wrapped_bdb_cursor_list;

					RPDB_SettingsController*					environment_settings_controller;
					RPDB_DatabaseJoinSettingsController*				settings_controller;
					RPDB_DatabaseJoinSettingsController*				environment_level_settings_controller;
				};
			
			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPDB_DatabaseJoinController	{

				//	Parent
				RPDB_Database*										parent_database;

				RPDB_Database*	runtime_storage_database;

				RPDB_SettingsController*							environment_settings_controller;
				RPDB_DatabaseJoinSettingsController*						settings_controller;
				RPDB_DatabaseJoinSettingsController*						environment_level_settings_controller;
			};

	
						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseCursor	{
							
							//	Parent
							RPDB_DatabaseCursorController*				parent_database_cursor_controller;

							db_recno_t										runtime_identifier;
							
							uint32_t								slice_length;
							
							char*										name;
							
							//	Wrapped bdb database_cursor
							DBC*										wrapped_bdb_cursor;
							
							BOOL										is_open;
							
							BOOL										iteration_started;
							int											duplicate_iteration_started;
							
							RPDB_SettingsController*							environment_settings_controller;
							RPDB_DatabaseCursorSettingsController*				settings_controller;
							RPDB_DatabaseCursorSettingsController*				environment_level_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseCursorController	{

						//	Parent
						RPDB_Database*								parent_database;

						RPDB_Database*	runtime_storage_database;
	
						int											auto_name_count;
						
						RPDB_SettingsController*							environment_settings_controller;
						RPDB_DatabaseCursorSettingsController*				settings_controller;
						RPDB_DatabaseCursorSettingsController*				environment_level_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseVerificationController	{

						//	Parent
						RPDB_Database*									parent_database;

						//	Variables
						char*											file_path;
						FILE*											file;
						BOOL											file_is_open;

						RPDB_SettingsController*									environment_settings_controller;
						RPDB_DatabaseVerificationSettingsController*				settings_controller;
						RPDB_DatabaseVerificationSettingsController*				environment_level_settings_controller;
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPDB_DatabaseSequence	{

							//	Parent
							RPDB_DatabaseSequenceController*				parent_database_sequence_controller;

							db_recno_t										runtime_identifier;
							
							//	Variables
							db_seq_t										current_value;

							//	Wrapped BDB sequence
							DB_SEQUENCE*									wrapped_bdb_sequence;

							RPDB_SettingsController*								environment_settings_controller;
							RPDB_DatabaseSequenceSettingsController*				settings_controller;
							RPDB_DatabaseSequenceSettingsController*				environment_level_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_DatabaseSequenceController	{

						//	Parent
						RPDB_Database*									parent_database;

						RPDB_Database*	runtime_storage_database;
	
						RPDB_SettingsController*								environment_settings_controller;
						RPDB_DatabaseSequenceSettingsController*				settings_controller;
						RPDB_DatabaseSequenceSettingsController*				environment_level_settings_controller;
					};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct RPDB_DBT	{

							//	Parent
							RPDB_Record*											parent_record;

							uint32_t*												size;
							uint32_t*												buffer_size;
							uint32_t*												partial_data_size;
							uint32_t*												partial_data_offset;
							void*													raw_data;

							//	Wrapped BDB DBT
							DBT*													wrapped_bdb_dbt;

							RPDB_SettingsController*							environment_settings_controller;
							RPDB_DatabaseRecordSettingsController*				settings_controller;
							RPDB_DatabaseRecordSettingsController*				environment_level_settings_controller;
						};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct RPDB_SecondaryKeys	{

							RPDB_Record*											parent_record;
							uint32_t												key_count;
							RPDB_Key**												key_pointers_array;

							//	Wrapped BDB DBT
							DBT*													wrapped_bdb_dbt;							
						};
						
					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPDB_Record	{
	
						//	Parent
						RPDB_Database*											parent_database;
	
						db_recno_t										runtime_identifier;

						//	Variables
						RPDB_Key*														key;
						RPDB_Key*														primary_key;
						RPDB_SecondaryKeys*									secondary_keys;	
						RPDB_Data*													data;
	
						BOOL																result;
	
						int																	exists_in_database;
						int																	requires_update_to_database;
	
						RPDB_DatabaseRecordSettingsController*				settings_controller;
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_Database	{

					//	Parent
					RPDB_DatabaseController*						parent_database_controller;

					db_recno_t										runtime_identifier;

					//	Variables
					char*											filename;
					char*											name;
					DBTYPE											type;
					
					RPDB_Database*	runtime_storage_database;
					
					BOOL											is_secondary;
					RPDB_Database*									secondary_database;
					RPDB_Database*									primary_database;
					char*											index_name;
					BOOL											is_open;
					BOOL											opened_in_transaction;
					BOOL											has_associated;
					
					//	Controllers
					RPDB_DatabaseCursorController*					cursor_controller;
					RPDB_DatabaseJoinController*					join_controller;
					RPDB_DatabaseVerificationController*			verification_controller;
					RPDB_DatabaseSequenceController*				sequence_controller;
					//	Callback Public Methods
					RPDB_SecondaryKeyCallbackMethod					secondary_key_creation_callback_method;

					RPDB_Environment*								default_environment;

					//	The wrapped BDB database
					DB*												wrapped_bdb_database;

					RPDB_SettingsController*						environment_settings_controller;
					RPDB_DatabaseSettingsController*				settings_controller;
					RPDB_DatabaseSettingsController*				environment_level_settings_controller;
				};

			/****************************
			 *	Data Type Definitions	*
			 ****************************/

			struct RPDB_DatabaseController	{
	
				//	Parent
				RPDB_Environment*								parent_environment;
	
				db_recno_t											record_number;

				RPDB_Database*	runtime_storage_database;
	
				RPDB_SettingsController*						environment_settings_controller;
				RPDB_DatabaseSettingsController*				settings_controller;
				RPDB_DatabaseSettingsController*				environment_level_settings_controller;
			};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPDB_Error	{

					//	Parent
					RPDB_ErrorController*						parent_error_controller;

					int											number;
					char*										function;
					char*										message;

					RPDB_SettingsController*					environment_settings_controller;
					RPDB_ErrorSettingsController*				settings_controller;
					RPDB_ErrorSettingsController*				environment_level_settings_controller;
				};

			/****************************
			 *	Data Type Definitions	*
			 ****************************/

			struct RPDB_ErrorController	{
	
				//	Parent
				RPDB_Environment*								parent_environment;
	
				//	Variables
				RPDB_Error*							error_stack;
	
				RPDB_SettingsController*				environment_settings_controller;
				RPDB_ErrorSettingsController*				settings_controller;
				RPDB_ErrorSettingsController*				environment_level_settings_controller;
			};

		/************************
		*	Class Descriptors	*
		************************/

		struct RPDB_Environment	{

			//	Variables
			char*									directory;
			char*									name;
			//	FIX - wtf is this a char*?
			char*									create_directory;
			BOOL									is_open;
			
			//	Controllers
			RPDB_ErrorController*					error_controller;
			RPDB_DatabaseController*				database_controller;
			RPDB_LockController*					lock_controller;
			RPDB_LogController*					log_controller;
			RPDB_MemoryPoolController*				memory_pool_controller;
			RPDB_MutexController*					mutex_controller;
			RPDB_ReplicationController*			replication_controller;
	//		RPDB_StatusController*					status_controller;
			RPDB_TransactionController*			transaction_controller;
			RPDB_SettingsController*				settings_controller;
			RPDB_SettingsController*				environment_level_settings_controller;
			//	The wrapped BDB environment
			DB_ENV*									wrapped_bdb_environment;

		};

struct RPDB_Directory {
	
	char*				path;
	RPDB_Directory*	next;
	
};

struct RPDB_DatabaseOpenedDuringTransaction	{
	
	RPDB_Database*								database;
	RPDB_DatabaseOpenedDuringTransaction*		next;
	
};

#endif