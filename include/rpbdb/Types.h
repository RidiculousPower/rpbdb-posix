#ifndef RPBDB_TYPES
	#define RPBDB_TYPES

	#include <db.h>
	
	#include <cerialize.h>
	
	#include "Constants.h"

	//	File is listed in inverse order of type hierarchy - hierarchy goes bottom to top

typedef struct RPbdb_Environment											RPbdb_Environment;
typedef struct RPbdb_Database												RPbdb_Database;
typedef struct RPbdb_DatabaseCursorController								RPbdb_DatabaseCursorController;
typedef struct RPbdb_DatabaseCursor											RPbdb_DatabaseCursor;
typedef struct RPbdb_DatabaseController										RPbdb_DatabaseController;
typedef struct RPbdb_DatabaseSequenceController								RPbdb_DatabaseSequenceController;
typedef struct RPbdb_DatabaseSequence										RPbdb_DatabaseSequence;
typedef struct RPbdb_Error													RPbdb_Error;
typedef struct RPbdb_ErrorController										RPbdb_ErrorController;
typedef struct RPbdb_DatabaseJoinController											RPbdb_DatabaseJoinController;
typedef struct RPbdb_DatabaseJoinCursor												RPbdb_DatabaseJoinCursor;
typedef struct RPbdb_Lock													RPbdb_Lock;
typedef struct RPbdb_LockController											RPbdb_LockController;
typedef struct RPbdb_Log													RPbdb_Log;
typedef struct RPbdb_LogController											RPbdb_LogController;
typedef struct RPbdb_LogCursorController									RPbdb_LogCursorController;
typedef struct RPbdb_LogCursor												RPbdb_LogCursor;
typedef struct RPbdb_LogSequenceNumber										RPbdb_LogSequenceNumber;
typedef struct RPbdb_Record													RPbdb_Record;
typedef struct RPbdb_DBT													RPbdb_DBT;
typedef RPbdb_DBT 															RPbdb_Key;
typedef struct RPbdb_SecondaryKeys											RPbdb_SecondaryKeysUnused;
typedef RPbdb_DBT	RPbdb_SecondaryKeys;
typedef RPbdb_DBT 															RPbdb_Data;
typedef struct RPbdb_MemoryPoolFilePageController							RPbdb_MemoryPoolFilePageController;
typedef struct RPbdb_MemoryPoolFilePage										RPbdb_MemoryPoolFilePage;
typedef struct RPbdb_MemoryPoolFileController								RPbdb_MemoryPoolFileController;
typedef struct RPbdb_MemoryPoolFile											RPbdb_MemoryPoolFile;
typedef struct RPbdb_MemoryPoolController									RPbdb_MemoryPoolController;
typedef struct RPbdb_Mutex													RPbdb_Mutex;
typedef struct RPbdb_MutexController										RPbdb_MutexController;
typedef struct RPbdb_ReplicationController									RPbdb_ReplicationController;
typedef struct RPbdb_RemoteSite												RPbdb_RemoteSite;
typedef struct RPbdb_RuntimeStorage											RPbdb_RuntimeStorage;
typedef struct RPbdb_RuntimeStorageController								RPbdb_RuntimeStorageController;
typedef struct RPbdb_Transaction											RPbdb_Transaction;
typedef struct RPbdb_TransactionController									RPbdb_TransactionController;
typedef struct RPbdb_TransactionSettingsController							RPbdb_TransactionSettingsController;
typedef struct RPbdb_ThreadSettingsController								RPbdb_ThreadSettingsController;
typedef struct RPbdb_StatusSettingsController								RPbdb_StatusSettingsController;
typedef struct RPbdb_SettingsController										RPbdb_SettingsController;
typedef struct RPbdb_RuntimeStorageSettingsController						RPbdb_RuntimeStorageSettingsController;
typedef struct RPbdb_ReplicationVerbositySettingsController					RPbdb_ReplicationVerbositySettingsController;
typedef struct RPbdb_ReplicationTimeoutSettingsController					RPbdb_ReplicationTimeoutSettingsController;
typedef struct RPbdb_ReplicationSettingsController							RPbdb_ReplicationSettingsController;
typedef struct RPbdb_ReplicationElectionSettingsController					RPbdb_ReplicationElectionSettingsController;
typedef struct RPbdb_DatabaseRecordSettingsController								RPbdb_DatabaseRecordSettingsController;
typedef struct RPbdb_MutexSettingsController								RPbdb_MutexSettingsController;
typedef struct RPbdb_MessageSettingsController								RPbdb_MessageSettingsController;
typedef struct RPbdb_MemoryPoolSettingsController							RPbdb_MemoryPoolSettingsController;
typedef struct RPbdb_MemoryPoolReadWriteSettingsController					RPbdb_MemoryPoolReadWriteSettingsController;
typedef struct RPbdb_MemoryPoolFileSettingsController						RPbdb_MemoryPoolFileSettingsController;
typedef struct RPbdb_MemoryPoolFilePageSettingsController					RPbdb_MemoryPoolFilePageSettingsController;
typedef struct RPbdb_MemoryPoolFileCacheSettingsController					RPbdb_MemoryPoolFileCacheSettingsController;
typedef struct RPbdb_MemoryPoolFileCachePrioritySettingsController			RPbdb_MemoryPoolFileCachePrioritySettingsController;
typedef struct RPbdb_LogSettingsController									RPbdb_LogSettingsController;
typedef struct RPbdb_LockSettingsController									RPbdb_LockSettingsController;
typedef struct RPbdb_LockDeadlockDetectorVerbositySettingsController		RPbdb_LockDeadlockDetectorVerbositySettingsController;
typedef struct RPbdb_LockDeadlockDetectorSettingsController					RPbdb_LockDeadlockDetectorSettingsController;
typedef struct RPbdb_DatabaseJoinSettingsController									RPbdb_DatabaseJoinSettingsController;
typedef struct RPbdb_FileVerbositySettingsController						RPbdb_FileVerbositySettingsController;
typedef struct RPbdb_FileSettingsController									RPbdb_FileSettingsController;
typedef struct RPbdb_ErrorSettingsController								RPbdb_ErrorSettingsController;
typedef struct RPbdb_EnvironmentCacheSettingsController						RPbdb_EnvironmentCacheSettingsController;
typedef struct RPbdb_DirectorySettingsController							RPbdb_DirectorySettingsController;
typedef struct RPbdb_DebugVerbositySettingsController						RPbdb_DebugVerbositySettingsController;
typedef struct RPbdb_DebugSettingsController								RPbdb_DebugSettingsController;
typedef struct RPbdb_DatabaseVerificationSettingsController					RPbdb_DatabaseVerificationSettingsController;
typedef struct RPbdb_DatabaseVerbositySettingsController					RPbdb_DatabaseVerbositySettingsController;
typedef struct RPbdb_DatabaseRecordVariableLengthSettingsController				RPbdb_DatabaseRecordVariableLengthSettingsController;
typedef struct RPbdb_DatabaseTypeSettingsController							RPbdb_DatabaseTypeSettingsController;
typedef struct RPbdb_DatabaseTypeRecnoSettingsController					RPbdb_DatabaseTypeRecnoSettingsController;
typedef struct RPbdb_DatabaseTypeQueueSettingsController					RPbdb_DatabaseTypeQueueSettingsController;
typedef struct RPbdb_DatabaseTypeHashSettingsController						RPbdb_DatabaseTypeHashSettingsController;
typedef struct RPbdb_DatabaseTypeBtreeSettingsController					RPbdb_DatabaseTypeBtreeSettingsController;
typedef struct RPbdb_DatabaseSettingsController								RPbdb_DatabaseSettingsController;
typedef struct RPbdb_DatabaseSequenceSettingsController						RPbdb_DatabaseSequenceSettingsController;
typedef struct RPbdb_DatabaseRecordReadWriteSettingsController					RPbdb_DatabaseRecordReadWriteSettingsController;
typedef struct RPbdb_DatabaseRecordFixedLengthSettingsController					RPbdb_DatabaseRecordFixedLengthSettingsController;
typedef struct RPbdb_DatabaseErrorSettingsController						RPbdb_DatabaseErrorSettingsController;
typedef struct RPbdb_DatabaseEncryptionSettingsController					RPbdb_DatabaseEncryptionSettingsController;
typedef struct RPbdb_DatabaseCursorCacheSettingsController					RPbdb_DatabaseCursorCacheSettingsController;
typedef struct RPbdb_DatabaseCursorCachePrioritySettingsController			RPbdb_DatabaseCursorCachePrioritySettingsController;
typedef struct RPbdb_DatabaseCursorSettingsController						RPbdb_DatabaseCursorSettingsController;
typedef struct RPbdb_DatabaseCursorReadWriteSettingsController				RPbdb_DatabaseCursorReadWriteSettingsController;
typedef struct RPbdb_DatabaseCompactSettingsController						RPbdb_DatabaseCompactSettingsController;
typedef struct RPbdb_DatabaseCacheSettingsController						RPbdb_DatabaseCacheSettingsController;
typedef struct RPbdb_DatabaseCachePrioritySettingsController				RPbdb_DatabaseCachePrioritySettingsController;
typedef struct RPbdb_DatabaseAssociationSettingsController					RPbdb_DatabaseAssociationSettingsController;
typedef struct RPbdb_CompactStatus											RPbdb_CompactStatus;
typedef struct RPbdb_Directory												RPbdb_Directory;
typedef struct RPbdb_DatabaseOpenedDuringTransaction						RPbdb_DatabaseOpenedDuringTransaction;

typedef		RPBDB_SECONDARY_KEY_CREATION_RETURN	(*RPbdb_SecondaryKeyCallbackMethod)(	RPbdb_Database*			secondary_database,
																																									RPbdb_Record*			primary_record,
																																									RPbdb_SecondaryKeys*	secondary_keys_to_return );

/*************************************
*  Thread Settings Callback Methods  *
*************************************/

typedef		BOOL	(*RPbdb_IsThreadAliveCallbackMethod)(	RPbdb_Environment*		environment,
																											pid_t								process_id,
																											db_threadid_t				thread_id,
																											BOOL								associated_with_single_process );
typedef		void	(*RPbdb_UniqueThreadIdentifierCallbackMethod)(	RPbdb_Environment*		environment,
																															pid_t*							process_id,
																															db_threadid_t*			thread_id	);
typedef		char* (*RPbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod)(	RPbdb_Environment*		environment,
																																									pid_t								process_id,
																																									db_threadid_t				thread_id,
																																									char*								string_buffer );

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_TransactionSettingsController	{
	
						//	Parent
						RPbdb_SettingsController*				parent_settings_controller;
	
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
						time_t									recovery_timestamp;
	
						BOOL									started_transaction_recover;
	/*
						//	Callback Public Methods
						int (*rollbackward_callback_method)(	RPbdb_Environment*				environment,                                                                                                                                                                	
																RPbdb_Record*		transaction_log_record );
						int (*rollforward_callback_method)(		RPbdb_Environment*				environment,                                                           				
														   		RPbdb_Record*		transaction_log_record );
						int (*abort_callback_method)(			RPbdb_Environment*				environment,                                                           				
													 			RPbdb_Record*		transaction_log_record );
						int (*apply_callback_method)(			RPbdb_Environment*				environment,                                                           				
													 			RPbdb_Record*		transaction_log_record );
	*/
	
						RPbdb_SettingsController*				environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseRecordSettingsController	{

						//	Parent
						RPbdb_DatabaseSettingsController*		parent_database_settings_controller;
						                                        
						RPbdb_Record*							parent_record;
                                                                						                                        
						RPbdb_DatabaseRecordReadWriteSettingsController*							record_read_write_settings_controller;
						RPbdb_DatabaseRecordVariableLengthSettingsController*				record_variable_length_settings_controller;
						RPbdb_DatabaseRecordFixedLengthSettingsController*						record_fixed_length_settings_controller;

						RPbdb_SettingsController*				environment_settings_controller;

					};


								/****************************
								*	Data Type Definitions	*
								****************************/

								struct RPbdb_MemoryPoolFilePage	{

									//	Parent
									RPbdb_MemoryPoolFilePageController*										parent_memory_pool_file_page_controller;

									db_recno_t					runtime_identifier;

									db_pgno_t*																page_address;

									void*																	page_data;

									DB_MPOOLFILE*															wrapped_bdb_memory_pool_file;

									RPbdb_SettingsController*													environment_settings_controller;
									RPbdb_MemoryPoolFilePageSettingsController*				settings_controller;
									RPbdb_MemoryPoolFilePageSettingsController*				environment_level_settings_controller;
								};

								/****************************
								*	Data Type Definitions	*
								****************************/

								struct RPbdb_MemoryPoolFilePageController	{

									//	Parent
									RPbdb_MemoryPoolFile*										parent_memory_pool_file;

									RPbdb_Database*													runtime_storage_database;

									RPbdb_SettingsController*								environment_settings_controller;
									RPbdb_MemoryPoolFilePageSettingsController*				settings_controller;
									RPbdb_MemoryPoolFilePageSettingsController*				environment_level_settings_controller;
								};

							/****************************
							*	Data Type Definitions	*
							****************************/

							struct RPbdb_MemoryPoolFile	{

								//	Parent
								RPbdb_MemoryPoolFileController*								parent_memory_pool_file_controller;

								db_recno_t					runtime_identifier;

								//	Wrapped BDB memory pool file
								DB_MPOOLFILE*												wrapped_bdb_memory_pool_file;
								
								RPbdb_SettingsController*							environment_settings_controller;
								RPbdb_MemoryPoolFileSettingsController*				settings_controller;
								RPbdb_MemoryPoolFileSettingsController*				environment_level_settings_controller;
							};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct RPbdb_MemoryPoolFileController	{

							//	Parent
							RPbdb_MemoryPoolController*			parent_memory_pool_controller;
							
							RPbdb_Database*									runtime_storage_database;
/*
							int									(*page_in_method)(	RPbdb_Environment*			environment,
							   														void*			page_data,
							   														RPbdb_Data*		page_cookie	);

							int									(*page_out_method)(	RPbdb_Environment*			environment,
							   														void*			page_data,
							   														RPbdb_Data*		page_cookie	);
*/
							RPbdb_SettingsController*							environment_settings_controller;
							RPbdb_MemoryPoolFileSettingsController*				settings_controller;
							RPbdb_MemoryPoolFileSettingsController*				environment_level_settings_controller;
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_MemoryPoolReadWriteSettingsController	{

							//	Parent
							RPbdb_MemoryPoolSettingsController*							parent_memory_pool_settings_controller;

							int															memory_pool_record_read_write_settings_controller;
							int															max_open_files;
							int															max_sequential_writes;
							db_timeout_t													time_to_sleep_before_next_write;
							size_t															max_mapped_db_size;
							BOOL														page_fault_shared_regions;
						BOOL													do_not_write_to_temporary_backing_file;

						BOOL													use_system_memory_for_storage;
						BOOL													use_application_memory_for_storage;
						BOOL													database_allocates_memory_using_malloc;
						BOOL													database_allocates_memory_using_realloc;
						BOOL													application_allocates_memory;
						BOOL													database_free_memory;

							RPbdb_SettingsController*									environment_settings_controller;

						};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct RPbdb_MemoryPoolFilePageSettingsController	{

								//	Parent
								RPbdb_MemoryPoolFileSettingsController*						parent_memory_pool_file_settings_controller;

								BOOL														get_page_creates_page_if_does_not_exist;
								BOOL														get_page_writes_copy_before_eviction;
								BOOL														get_page_writes_before_eviction_without_copy;
								BOOL														get_page_returns_last_page;
								BOOL														get_page_creates_new_page;

								RPbdb_SettingsController*									environment_settings_controller;

							};

								/****************************
								 *	Data Type Definitions	*
								 ****************************/

								struct RPbdb_MemoryPoolFileCachePrioritySettingsController	{

									//	Parent
									RPbdb_MemoryPoolFileCacheSettingsController*				parent_memory_pool_file_cache_settings_controller;

									DB_CACHE_PRIORITY											priority;

									RPbdb_SettingsController*									environment_settings_controller;
								};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct RPbdb_MemoryPoolFileCacheSettingsController	{

								//	Parent
								RPbdb_MemoryPoolFileSettingsController*												parent_memory_pool_file_settings_controller;

								RPbdb_MemoryPoolFileCachePrioritySettingsController*						priority_settings_controller;
							};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_MemoryPoolFileSettingsController	{

							//	Parent
							RPbdb_MemoryPoolSettingsController*						parent_memory_pool_settings_controller;

							RPbdb_MemoryPoolFile*													parent_memory_pool_file;

							uint																					create_with_number_initial_bytes;
							uint8_t*																			file_id;
							int																						file_type;
							int																						log_sequence_number_offset;
							uint64_t																			page_size_in_bytes;
							uint64_t																			max_file_size_in_bytes;
							RPbdb_Data*																		cookie;

							RPbdb_MemoryPoolFileCacheSettingsController*		cache_settings_controller;
							RPbdb_MemoryPoolFilePageSettingsController*		page_settings_controller;

							RPbdb_SettingsController*											environment_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_MemoryPoolSettingsController	{
	
						//	Parent
						RPbdb_SettingsController*								parent_settings_controller;
	
						BOOL													on;
						BOOL													memory_mapping;						
						BOOL													threaded;
						BOOL													remove_file_with_last_reference;
						BOOL													pagesize_factor_mismatch_should_fail;
	
						RPbdb_MemoryPoolFileSettingsController*					file_settings_controller;
						RPbdb_MemoryPoolReadWriteSettingsController*			record_read_write_settings_controller;
	
						RPbdb_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseJoinSettingsController	{

						//	Parent
						RPbdb_DatabaseSettingsController*								parent_database_settings_controller;

						BOOL													degree_one_isolation;
						BOOL													use_write_locks_instead_of_read_locks;
						BOOL													sort_before_join;

						RPbdb_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DirectorySettingsController	{

						//	Parent
						RPbdb_SettingsController*								parent_settings_controller;

						char*													home_directory_path;
						
						RPbdb_Directory*										directories;

						RPbdb_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_RuntimeStorageSettingsController	{
							
						//	Parent
						RPbdb_SettingsController*								parent_settings_controller;
		
						BOOL													store_in_application_memory;
						BOOL													store_in_system_memory;
						BOOL													store_on_disk;
						BOOL													log_runtime_storage_activity;

						BOOL													automatic_default_environment;
						
						RPbdb_SettingsController*								environment_settings_controller;
					};
	
							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct RPbdb_LockDeadlockDetectorVerbositySettingsController	{

								//	Parent
								RPbdb_LockDeadlockDetectorSettingsController*								parent_lock_deadlock_detector_settings_controller;

								BOOL																		display_additional_information_during_deadlock_detection;
								BOOL																		display_wait_table_during_deadlock_detection;

								RPbdb_SettingsController*								environment_settings_controller;
							};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_LockDeadlockDetectorSettingsController	{

							//	Parent
							RPbdb_LockSettingsController*								parent_lock_settings_controller;

							uint32_t																					deadlock_settings;

							RPbdb_LockDeadlockDetectorVerbositySettingsController*		verbosity_settings_controller;

							RPbdb_SettingsController*									environment_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_LockSettingsController	{

						//	Parent
						RPbdb_SettingsController*								parent_settings_controller;

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

						RPbdb_LockDeadlockDetectorSettingsController*			deadlock_detector_settings_controller;

						RPbdb_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_LogSettingsController	{

						//	Parent
						RPbdb_SettingsController*								parent_settings_controller;

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

						RPbdb_SettingsController*								environment_settings_controller;
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_ReplicationVerbositySettingsController	{
	
							//	Parent
							RPbdb_ReplicationSettingsController*								parent_replication_settings_controller;
	
							BOOL																display_all_replication_information;
							BOOL																display_election_information;
							BOOL																display_replication_master_lease_information;
							BOOL																display_misc_processing_information;
							BOOL																display_message_processing_information;
							BOOL																display_client_synchronization_information;
							BOOL																display_manager_connection_failure_information;
							BOOL																display_manager_misc_processing;
	
							RPbdb_SettingsController*											environment_settings_controller;
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_ReplicationTimeoutSettingsController	{
	
							//	Parent
							RPbdb_ReplicationSettingsController*								parent_replication_settings_controller;
	
							uint32_t															timeout;
							uint32_t															wait_time_before_checkpoint_write;
							uint32_t															wait_time_before_retry_connection;
							uint32_t															election_timeout;
							uint32_t															wait_time_before_retry_election;
							uint32_t															full_election_participation_timeout;
							uint32_t															heartbeat_monitor_pulse;
							uint32_t															heartbeat_broadcast_pulse;
							uint32_t															lease_timeout;
	
							RPbdb_SettingsController*											environment_settings_controller;
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_ReplicationElectionSettingsController	{
	
							//	Parent
							RPbdb_ReplicationSettingsController*								parent_replication_settings_controller;
	
							int																	number_of_sites_required_for_election;
							int																	number_of_votes_required_for_election;
	
							BOOL																wait_for_all_clients;
							BOOL																wait_for_all_electable_peers;
							BOOL																never_wait;
							BOOL																wait_for_at_least_one_client;
							BOOL																wait_for_at_least_one_electable_peer;
							BOOL																wait_for_minimum_electable_peers_for_durable_election;
							
							int																	current_ack_policy;
	
							RPbdb_SettingsController*											environment_settings_controller;
						};


					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_ReplicationSettingsController	{
	
						//	Parent
						RPbdb_SettingsController*								parent_settings_controller;
	
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
	
						RPbdb_Record*											additional_start_information;
	
						RPbdb_ReplicationElectionSettingsController*			acknowledgement_policy_settings_controller;
						RPbdb_ReplicationTimeoutSettingsController*				timeout_settings_controller;	
						RPbdb_ReplicationVerbositySettingsController*			verbosity_settings_controller;	
	
						RPbdb_SettingsController*							environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_MutexSettingsController	{
	
						//	Parent
						RPbdb_SettingsController*								parent_settings_controller;
	
						uint32_t												spin_times_before_blocking_for_test_and_spin_mutexes;
						uint32_t												max_allowable_mutexes;
						uint32_t												increment_for_adding_mutexes;
						uint32_t												mutex_alignment;
						BOOL													associated_with_single_process;
						BOOL													self_blocking;
	
						RPbdb_SettingsController*								environment_settings_controller;
	
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseVerificationSettingsController	{

							//	Parent
							RPbdb_DatabaseSettingsController*						parent_database_settings_controller;

							FILE*													file;
							BOOL													file_is_open;
							
							char*													file_path;
							BOOL													aggressive_key_data_pair_dump;
							BOOL													printable_characters;
							BOOL													skip_order_checking;
							BOOL													only_order_check;
							BOOL													force_order_check;
							BOOL													has_done_unordered_check;
							
							RPbdb_SettingsController*								environment_settings_controller;
							
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseRecordVariableLengthSettingsController	{

							//	Parent
							RPbdb_DatabaseRecordSettingsController*						parent_database_record_settings_controller;

							int														delimeter_byte;
							//	FIX	- what happened to these??
							BOOL													index_primary;
							BOOL													secondary_key_is_immutable;

							RPbdb_SettingsController*								environment_settings_controller;

						};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct RPbdb_DatabaseCursorReadWriteSettingsController	{

								//	Parent
								RPbdb_DatabaseCursorSettingsController*						parent_database_cursor_settings_controller;

								BOOL														permit_write;
								BOOL														ignore_lease;
								BOOL														write_locks_instead_of_read_locks;
								BOOL														multiple_data_items;
								BOOL														return_multiple_key_data_pairs;

								RPbdb_SettingsController*									environment_settings_controller;

							};

								/****************************
								 *	Data Type Definitions	*
								 ****************************/

								struct RPbdb_DatabaseCursorCachePrioritySettingsController	{
		
									//	Parent
									RPbdb_DatabaseCursorCacheSettingsController*						parent_database_cursor_cache_settings_controller;
		
									DB_CACHE_PRIORITY													priority;
		
									RPbdb_SettingsController*											environment_settings_controller;
		
								};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct RPbdb_DatabaseCursorCacheSettingsController	{

								//	Parent
								RPbdb_DatabaseCursorSettingsController*						parent_database_cursor_settings_controller;

								//	FIX - seems like these are missing function-wise? did something get deleted? check out this controller
								int															number_cache_regions;
								uint32_t													max_size_in_bytes;

								RPbdb_DatabaseCursorCachePrioritySettingsController*		priority_settings_controller;

								RPbdb_SettingsController*									environment_settings_controller;

							};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseCursorSettingsController	{

							//	Parent
							RPbdb_DatabaseSettingsController*						parent_database_settings_controller;
							RPbdb_DatabaseCursor*									parent_database_cursor;

							//	Variables
							BOOL													duplicate_retains_location;

							//	Controllers
							RPbdb_DatabaseCursorCacheSettingsController*			cache_controller;
							RPbdb_DatabaseCursorReadWriteSettingsController*		record_read_write_settings_controller;

							RPbdb_SettingsController*								environment_settings_controller;

						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseSequenceSettingsController	{
	
							//	Parent
							RPbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
							RPbdb_DatabaseSequence*									parent_sequence;
	
							BOOL																		increasing;
							BOOL																		decreasing;
							BOOL																		wrapping;
							db_seq_t																range_minimum;
							db_seq_t																range_maximum;
							int32_t																	number_of_cached_elements;
							db_seq_t																initial_value;
							int32_t																	default_step_value;
	
							RPbdb_SettingsController*								environment_settings_controller;
	
						};

						/****************************
						 *	Record Storage Type	*
						 ****************************/


						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseRecordReadWriteSettingsController	{
	
							//	Parent
							RPbdb_DatabaseRecordSettingsController*						parent_database_record_settings_controller;
	
							char*													filename;
							BOOL													prohibit_sync_on_close;
							BOOL													ignore_lease;
							BOOL													return_multiple;
							BOOL													append_data;
							BOOL													write_data_only_if_non_duplicate;
							BOOL													prohibit_overwrite;
							BOOL													prohibit_page_compaction;
							BOOL													return_pages_to_filesystem;
							BOOL													multiple_targets;
							BOOL													partial_access;
							BOOL													truncate;
							BOOL													write_locks_instead_of_read_locks;
							BOOL													permit_duplicates;
							BOOL													sort_duplicates;
							BOOL													store_file_not_path;

							uint32_t								update_flags;

							BOOL									sync_prior_to_write_return;
							BOOL									database_allocates_memory_using_malloc;
							BOOL									database_allocates_memory_using_realloc;
							BOOL									application_allocates_memory;
							BOOL									database_free_memory;
							BOOL									record_contains_multiple_data;
							uint32_t								data_buffer_size;
							uint32_t								partial_read_write_size;
							uint32_t								partial_read_write_offset;
							
							BOOL										store_key_typing;
							BOOL										store_data_typing;
							BOOL										record_typing;
							BOOL										creation_stamp;
							BOOL										modification_stamp;
							BOOL										has_footer;

							RPbdb_SettingsController*								environment_settings_controller;
	
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseTypeRecnoSettingsController	{
	
							//	Parent
							RPbdb_DatabaseTypeSettingsController*		parent_database_type_settings_controller;
	
							BOOL										record_renumbering;
							BOOL										snapshot_isolation;
							char*										source_file_path;
	/*
							void										(*append_callback_method)(	RPbdb_Database*		database,
																								  struct RPbdb_Record*		record );
	*/
							RPbdb_SettingsController*					environment_settings_controller;

						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseTypeQueueSettingsController	{
	
							//	Parent
							RPbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller;
	
							BOOL														return_key_data_pairs_in_order;
							uint32_t													number_of_pages_for_underlying_data;
	
							RPbdb_SettingsController*									environment_settings_controller;
	
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseTypeHashSettingsController	{
	
							//	Parent
							RPbdb_DatabaseTypeSettingsController*		parent_database_type_settings_controller;
	
							//	Variables                               
							uint32_t									table_size;
							uint32_t									density;	
	
	/*
							//	Callback Public Methods
							uint32_t									(*hash_method)(					RPbdb_Database*		database, 
																					   const void*			bytes,    
																					   uint32_t			length );
							int											(*compare_method)(				RPbdb_Database*		database, 
																						  const DBT*			data_one, 
																						  const DBT*			data_two );
							int											(*duplicate_compare_method)(	RPbdb_Database*		database, 
																									const DBT*			data_one, 
																									const DBT*			data_two );
	*/
							RPbdb_SettingsController*				environment_settings_controller;

						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseTypeBtreeSettingsController	{
	
							//	Parent
							RPbdb_DatabaseTypeSettingsController*		parent_database_type_settings_controller;
	
							BOOL										record_number_retrieval;
							BOOL										reverse_splitting;
							uint32_t									minimum_keys_per_page;
	/*
							size_t										(*prefix_compare_method)(		RPbdb_Database*		database, 
																								 const DBT*			data_one, 
																								 const DBT*			data_two );
							int											(*compare_method)(				DBRPbdb_Database*	database, 
																						  const DBT*			data_one, 
																						  const DBT*			data_two );
							int											(*duplicate_compare_method)(	RPbdb_Database*		database, 
																									const DBT*			data_one, 
																									const DBT*			data_two );
	*/
	
							RPbdb_SettingsController*				environment_settings_controller;

						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseTypeSettingsController	{
	
						//	Parent
						RPbdb_DatabaseSettingsController*						parent_database_settings_controller;

						RPbdb_Database*											parent_database;

						DBTYPE													default_database_type;
						RPbdb_DatabaseTypeBtreeSettingsController*				btree_settings_controller;
						RPbdb_DatabaseTypeHashSettingsController*				hash_settings_controller;
						RPbdb_DatabaseTypeQueueSettingsController*				queue_settings_controller;
						RPbdb_DatabaseTypeRecnoSettingsController*				recno_settings_controller;
	
						RPbdb_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseVerbositySettingsController	{
	
						//	Parent
						RPbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
						BOOL													display_additional_information_for_db_register_flag;
	
						RPbdb_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseEncryptionSettingsController	{
	
						//	Parent
						RPbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
						BOOL													encrypted;
						
						char*													password;
	
						RPbdb_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseCompactSettingsController	{
	
						//	Parent
						RPbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
						int														fill_percent;
						int														max_pages_to_compact;
						int														timeout;
	
						RPbdb_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseAssociationSettingsController	{
	
						//	Parent
						RPbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
						BOOL													index_primary_database;
						BOOL													secondary_key_is_immutable;
	
						RPbdb_SettingsController*								environment_settings_controller;
	
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseCachePrioritySettingsController	{
	
							//	Parent
							RPbdb_DatabaseCacheSettingsController*						parent_database_cache_settings_controller;
	
							DB_CACHE_PRIORITY											priority;
	
							RPbdb_SettingsController*								environment_settings_controller;
	
						};
	
					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseCacheSettingsController	{
	
						//	Parent
						RPbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
						int														number_cache_regions;
						uint32_t												max_size_in_bytes;
	
						RPbdb_DatabaseCachePrioritySettingsController*			priority_settings_controller;
		
						RPbdb_SettingsController*								environment_settings_controller;
		
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseRecordFixedLengthSettingsController	{

						//	Parent
						RPbdb_DatabaseRecordSettingsController*						parent_database_record_settings_controller;

						uint32_t												record_length;
						int														record_padding_byte;

						RPbdb_SettingsController*								environment_settings_controller;

					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseErrorSettingsController	{
	
						//	Parent
						RPbdb_DatabaseSettingsController*		parent_database_settings_controller;
	
						//	Variables               
						FILE*									error_file;
						BOOL									error_file_is_open;
						char*									error_file_path;
						char*									error_prefix;
	/*
						//	Callback Public Methods
						void									(*error_callback_method)(	RPbdb_Environment*			environment,                                                                                                                                             
																						 const char*		error_prefix_string,                                                                                                                                                            
																						 const char*		error_message	);
	*/
	
						RPbdb_SettingsController*				environment_settings_controller;

					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_DatabaseSettingsController	{
	
					//	Parent
					RPbdb_SettingsController*								parent_settings_controller;
	
					RPbdb_Database*											parent_database;
	
					BOOL													on;
					BOOL													checksum;
					BOOL													transaction_durability_off;
					uint32_t												pagesize;
					BOOL													big_endian;
					BOOL													little_endian;
					BOOL													is_byteswapped;
	
					RPbdb_DatabaseJoinSettingsController*							join_settings_controller;
					RPbdb_DatabaseErrorSettingsController*					error_settings_controller;
					RPbdb_DatabaseCacheSettingsController*					cache_settings_controller;
					RPbdb_DatabaseAssociationSettingsController*			association_settings_controller;
					RPbdb_DatabaseCompactSettingsController*				compact_settings_controller;
					RPbdb_DatabaseEncryptionSettingsController*				encryption_settings_controller;
					RPbdb_DatabaseVerbositySettingsController*				verbosity_settings_controller;
					RPbdb_DatabaseTypeSettingsController*					type_settings_controller;
					RPbdb_DatabaseSequenceSettingsController*					sequence_settings_controller;
					RPbdb_DatabaseCursorSettingsController*					cursor_settings_controller;
					RPbdb_DatabaseVerificationSettingsController*					verification_settings_controller;
					RPbdb_DatabaseRecordSettingsController*							record_settings_controller;

					RPbdb_SettingsController*								environment_settings_controller;

				};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_StatusSettingsController	{

					//	Parent
					RPbdb_SettingsController*								parent_settings_controller;

					BOOL													display_all;
					BOOL													reset_after_display;
					BOOL													display_for_all_subsystems;
					BOOL													no_traversal;
					BOOL													degree_two_isolation;
					BOOL													degree_one_isolation;

					RPbdb_SettingsController*								environment_settings_controller;

				};
				
				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_MessageSettingsController	{
	
					//	Parent
					RPbdb_SettingsController*			parent_settings_controller;
	
					FILE*								message_file;
					BOOL								message_file_is_open;
					char*								message_file_path;
	/*
					void								(*message_callback_method)(										RPbdb_Environment*			environment, 
																				   const char*		message );
					void								*(panic_callback_method)(										RPbdb_Environment*			environment );									
					void								*(site_is_now_replication_client_callback_method)(				RPbdb_Environment*			environment );			
					void								*(site_won_replication_election_callback_method)(				RPbdb_Environment*			environment );			
					void								*(site_is_now_master_of_replication_group_callback_method)(		RPbdb_Environment*			environment );	
					void								*(replication_group_has_new_master_callback_method)(			RPbdb_Environment*			environment );		
					void								*(replication_acknowledgement_failed_callback_method)(			RPbdb_Environment*			environment );		
					void								*(replication_startup_completed_callback_method)(				RPbdb_Environment*			environment );			
					void								*(write_failed_callback_method)(								RPbdb_Environment*			environment );						
*/
					RPbdb_SettingsController*				environment_settings_controller;

				};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_ErrorSettingsController	{

					//	Parent
					RPbdb_SettingsController*		parent_settings_controller;

					FILE*							error_file;
					char*							error_file_path;
					BOOL							error_file_is_open;
					char*							prefix;
/*
					void							(*error_callback_method)(	RPbdb_Environment*					environment,                                                                                                                  
																			 const char*				error_prefix,                                                                                                                               
																			 const char*				error_message );
*/
					RPbdb_SettingsController*				environment_settings_controller;

				};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_ThreadSettingsController	{

					//	Parent
					RPbdb_SettingsController*													parent_settings_controller;

					//	Variables
					BOOL																		on;
					uint32_t																	thread_count;

					RPbdb_IsThreadAliveCallbackMethod											is_thread_alive_callback_method;
					RPbdb_UniqueThreadIdentifierCallbackMethod									unique_thread_identifier_callback_method;
					RPbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod				format_thread_and_process_identifier_for_display_callback_method;
					RPbdb_SettingsController*													environment_settings_controller;

				};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_FileVerbositySettingsController	{

						//	Parent
						RPbdb_FileSettingsController*								parent_file_settings_controller;

						BOOL														display_additional_information_during_open_close_rename_file_operations;
						BOOL														display_additional_information_during_all_file_operations;
						
						RPbdb_SettingsController*								environment_settings_controller;
						
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_FileSettingsController	{

					//	Parent
					RPbdb_SettingsController*								parent_settings_controller;

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

					RPbdb_FileVerbositySettingsController*					verbosity_settings_controller;

					RPbdb_SettingsController*								environment_settings_controller;

				};
		
				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_EnvironmentCacheSettingsController	{

					//	Parent
					RPbdb_SettingsController*								parent_settings_controller;

					BOOL													buffering;
					uint64_t												size_in_bytes;
					uint64_t												max_size_in_bytes;


					RPbdb_SettingsController*								environment_settings_controller;
				};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DebugVerbositySettingsController	{

						//	Parent
						RPbdb_DebugSettingsController*								parent_debug_settings_controller;

						BOOL														display_additional_information_during_recovery;

						RPbdb_SettingsController*									environment_settings_controller;
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_DebugSettingsController	{

					//	Parent
					RPbdb_SettingsController*								parent_settings_controller;
					BOOL													check_for_environment_failure_during_open;
					BOOL													run_normal_recovery_before_opening_environment;
					BOOL													run_catastrophic_recovery_before_opening_environment;
					BOOL													open_in_lockdown;
					BOOL													check_for_recovery_on_load;
					BOOL													prohibit_panic;
					BOOL													panic;
					BOOL													yield_cpu_for_stress_test;

					RPbdb_DebugVerbositySettingsController*					verbosity_settings_controller;

					RPbdb_SettingsController*								environment_settings_controller;
				};

			/****************************
			 *	Data Type Definitions	*
			 ****************************/

			struct RPbdb_SettingsController	{
	
				//	Parent
				RPbdb_Environment*										parent_environment;
				
				//	Variables
				long													shm_key;
	
				//	Controllers
				RPbdb_DatabaseSettingsController*						database_settings_controller;
				RPbdb_DebugSettingsController*							debug_settings_controller;
				RPbdb_EnvironmentCacheSettingsController*				cache_settings_controller;
				RPbdb_FileSettingsController*							file_settings_controller;
				RPbdb_ThreadSettingsController*							thread_settings_controller;
				RPbdb_ErrorSettingsController*							error_settings_controller;
				RPbdb_MessageSettingsController*							message_settings_controller;
				RPbdb_StatusSettingsController*							status_settings_controller;
				RPbdb_MutexSettingsController*							mutex_settings_controller;
				RPbdb_ReplicationSettingsController*							replication_settings_controller;
				RPbdb_LogSettingsController*							log_settings_controller;
				RPbdb_LockSettingsController*							lock_settings_controller;
				RPbdb_RuntimeStorageSettingsController*							runtime_storage_settings_controller;
				RPbdb_DirectorySettingsController*							directory_settings_controller;
				RPbdb_MemoryPoolSettingsController*							memory_pool_settings_controller;
				RPbdb_TransactionSettingsController*					transaction_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct RPbdb_Transaction	{

					//	Parent
					RPbdb_TransactionController*							parent_transaction_controller;
					
					db_recno_t										runtime_identifier;
					
					//	Variables
					char*													name;

					BOOL												is_open;

					uint8_t													global_id;

					RPbdb_DatabaseOpenedDuringTransaction*				databases_opened_during_transaction;

					//	Wrapped BDB Transaction
					DB_TXN*													wrapped_bdb_transaction;

					RPbdb_SettingsController*							environment_settings_controller;
					RPbdb_TransactionSettingsController*				settings_controller;
					RPbdb_TransactionSettingsController*				environment_level_settings_controller;
				};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPbdb_TransactionController	{

				//	Parent
				RPbdb_Environment*										parent_environment;

				RPbdb_Database*	runtime_storage_database;

				uint32_t												current_transaction_index;
				RPbdb_Transaction**										transactions;

				//	Variables
				u_int32_t												maximum_number_of_transactions_to_recover;
				u_int32_t												current_transaction_depth;

				RPbdb_SettingsController*							environment_settings_controller;
				RPbdb_TransactionSettingsController*				settings_controller;
			};


			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPbdb_RuntimeStorageController	{

				//	Variables
				RPbdb_Environment*												runtime_environment;
				RPbdb_Environment*												default_environment;

				RPbdb_DatabaseCursor*										database_cursor;

				//	Runtime Storage instances are stored by name--&db_env
				RPbdb_Database*													runtime_storages_database;

				//	All RPbdb_Environment* and RPbdb_Database* are stored by their wrapped_bdb_database DB* in these databases
				RPbdb_Database*													environment_reference_database;
				RPbdb_Database*													database_reference_database;

				//	Unlike other controllers, the environmental runtime storage settings controller is stored inside the runtime storage controller
				RPbdb_RuntimeStorageSettingsController*							settings_controller;
			};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_RemoteSite	{
	
					//	Parent
					RPbdb_ReplicationController*							parent_replication_controller;
	
					db_recno_t										runtime_identifier;

					//	Variables
					
					char*													host;
					u_int													port;
					
					int														replication_environment_id;
					
					BOOL													connected;
					
					long													hard_timeout;
					long													soft_timeout;
	
					RPbdb_SettingsController*							environment_settings_controller;
					RPbdb_ReplicationSettingsController*				settings_controller;
					RPbdb_ReplicationSettingsController*				environment_level_settings_controller;
				};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPbdb_ReplicationController	{

				//	Parent
				RPbdb_Environment*													parent_environment;

				RPbdb_Database*	runtime_storage_database;

				u_int													site_count;

				//	Variables
				int														replication_environment_id;
				RPbdb_RemoteSite**										remote_site_list;

				RPbdb_SettingsController*							environment_settings_controller;
				RPbdb_ReplicationSettingsController*				settings_controller;
				RPbdb_ReplicationSettingsController*				environment_level_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct RPbdb_Mutex	{

					//	Parent
					RPbdb_MutexController*										parent_mutex_controller;

					db_recno_t										runtime_identifier;

					db_mutex_t													wrapped_bdb_mutex;

					RPbdb_SettingsController*					environment_settings_controller;
					RPbdb_MutexSettingsController*				settings_controller;
					RPbdb_MutexSettingsController*				environment_level_settings_controller;
				};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPbdb_MutexController	{

				//	Parent
				RPbdb_Environment*													parent_environment;

				RPbdb_Database*	runtime_storage_database;

				RPbdb_SettingsController*					environment_settings_controller;
				RPbdb_MutexSettingsController*				settings_controller;
				RPbdb_MutexSettingsController*				environment_level_settings_controller;
			};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPbdb_MemoryPoolController	{

				//	Parent
				RPbdb_Environment*											parent_environment;

				//	Variables
				int												memory_space_for_pages;
/*
				//	Callbacks
				void*											(*malloc_method)(	size_t );
				void*											(*realloc_method)(	void*, 
																					size_t );
				void*											(*free_method)(		void* );
*/
				RPbdb_MemoryPoolFileController*					file_controller;

				RPbdb_SettingsController*						environment_settings_controller;
				RPbdb_MemoryPoolSettingsController*				settings_controller;
				RPbdb_MemoryPoolSettingsController*				environment_level_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct RPbdb_LogCursor	{

					//	Parent
					RPbdb_LogCursorController*					parent_log_cursor_controller;

					db_recno_t										runtime_identifier;

					//	Wrapped BDB log database_cursor
					DB_LOGC*									wrapped_bdb_log_cursor;

					RPbdb_SettingsController*					environment_settings_controller;
					RPbdb_LogSettingsController*				settings_controller;
					RPbdb_LogSettingsController*				environment_level_settings_controller;
				};

							/****************************
							*	Data Type Definitions	*
							****************************/

							struct RPbdb_LogSequenceNumber	{

								//	Parent
								RPbdb_Log*									parent_log;

								//	Wrapped BDB log database_cursor
								DB_LSN*										wrapped_bdb_log_sequence_number;

								RPbdb_SettingsController*					environment_settings_controller;
								RPbdb_LogSettingsController*				settings_controller;
								RPbdb_LogSettingsController*				environment_level_settings_controller;
							};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct RPbdb_Log	{

							//	Parent
							RPbdb_LogController*						parent_log_controller;

							db_recno_t										runtime_identifier;

							//	Variables
							RPbdb_Record*								record;
							RPbdb_LogSequenceNumber*					log_sequence_number;
							
							char*										filename;

							RPbdb_SettingsController*					environment_settings_controller;
							RPbdb_LogSettingsController*				settings_controller;
							RPbdb_LogSettingsController*				environment_level_settings_controller;
						};

					/****************************
					*	Data Type Definitions	*
					****************************/

					struct RPbdb_LogController	{

						//	Parent
						RPbdb_Environment*								parent_environment;

						RPbdb_Database*									runtime_storage_database;

						RPbdb_LogCursorController*						cursor_controller;

						RPbdb_SettingsController*					environment_settings_controller;
						RPbdb_LogSettingsController*				settings_controller;
						RPbdb_LogSettingsController*				environment_level_settings_controller;
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_LogCursorController	{
					
					//	Parent
					RPbdb_LogController*						parent_log_controller;

					RPbdb_Database*	runtime_storage_database;
					
					RPbdb_SettingsController*					environment_settings_controller;
					RPbdb_LogSettingsController*				settings_controller;
					RPbdb_LogSettingsController*				environment_level_settings_controller;
				};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct RPbdb_Lock	{

					//	Parent
					RPbdb_LockController*						parent_lock_controller;

					db_recno_t										runtime_identifier;

					//	Variables
					int											mode;

					uint32_t									timeout;

					//	Object being locked
					void*										object;

					//	Wrapped BDB lock
					DB_LOCK										wrapped_bdb_lock;

					RPbdb_SettingsController*					environment_settings_controller;
					RPbdb_LockSettingsController*				settings_controller;
					RPbdb_LockSettingsController*				environment_level_settings_controller;
				};
	
			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPbdb_LockController	{

				//	Parent
				RPbdb_Environment*							parent_environment;
				
				RPbdb_Database*	runtime_storage_database;
				
				//	Variables
				uint32_t									locker_id;
				RPbdb_Lock**									queued_locks;
				int											number_of_queued_locks;
				int											number_of_locks_last_cleared;

				RPbdb_SettingsController*					environment_settings_controller;
				RPbdb_LockSettingsController*				settings_controller;
				RPbdb_LockSettingsController*				environment_level_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct RPbdb_DatabaseJoinCursor	{

					//	Parent
					RPbdb_DatabaseJoinController*						parent_join_controller;

					db_recno_t										runtime_identifier;

					char*										name;

					//	Variables
					RPbdb_Database*								primary_database;

					RPbdb_DatabaseCursor**						cursor_list;
          int                             number_of_cursors;
					
					BOOL										is_open;
					
					//	Wrapped BDB database_cursor
					DBC*										wrapped_bdb_join_cursor;
					DBC**										wrapped_bdb_cursor_list;

					RPbdb_SettingsController*					environment_settings_controller;
					RPbdb_DatabaseJoinSettingsController*				settings_controller;
					RPbdb_DatabaseJoinSettingsController*				environment_level_settings_controller;
				};
			
			/****************************
			*	Data Type Definitions	*
			****************************/

			struct RPbdb_DatabaseJoinController	{

				//	Parent
				RPbdb_Database*										parent_database;

				RPbdb_Database*	runtime_storage_database;

				RPbdb_SettingsController*							environment_settings_controller;
				RPbdb_DatabaseJoinSettingsController*						settings_controller;
				RPbdb_DatabaseJoinSettingsController*						environment_level_settings_controller;
			};

	
						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseCursor	{
							
							//	Parent
							RPbdb_DatabaseCursorController*				parent_database_cursor_controller;

							db_recno_t										runtime_identifier;
							
							uint32_t								slice_length;
							
							char*										name;
							
							//	Wrapped bdb database_cursor
							DBC*										wrapped_bdb_cursor;
							
							BOOL										is_open;
							
              BOOL                    retrieved_record;
              
							BOOL										iteration_started;
							int											duplicate_iteration_started;
							
							RPbdb_SettingsController*							environment_settings_controller;
							RPbdb_DatabaseCursorSettingsController*				settings_controller;
							RPbdb_DatabaseCursorSettingsController*				environment_level_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseCursorController	{

						//	Parent
						RPbdb_Database*								parent_database;

						RPbdb_Database*	runtime_storage_database;
	
						int											auto_name_count;
						
						RPbdb_SettingsController*							environment_settings_controller;
						RPbdb_DatabaseCursorSettingsController*				settings_controller;
						RPbdb_DatabaseCursorSettingsController*				environment_level_settings_controller;
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct RPbdb_DatabaseSequence	{

							//	Parent
							RPbdb_DatabaseSequenceController*				parent_database_sequence_controller;

							db_recno_t										runtime_identifier;

							BOOL															is_open;

							RPbdb_Database*										parent_storage_database;
							RPbdb_Key*													storage_key;

							//	Wrapped BDB sequence
							DB_SEQUENCE*									wrapped_bdb_sequence;

							RPbdb_SettingsController*								environment_settings_controller;
							RPbdb_DatabaseSequenceSettingsController*				settings_controller;
							RPbdb_DatabaseSequenceSettingsController*				environment_level_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_DatabaseSequenceController	{

						//	Parent
						RPbdb_Database*									parent_database;

						RPbdb_Database*									runtime_storage_database;

						RPbdb_Database*									sequence_storage_database;
	
						RPbdb_SettingsController*								environment_settings_controller;
						RPbdb_DatabaseSequenceSettingsController*				settings_controller;
						RPbdb_DatabaseSequenceSettingsController*				environment_level_settings_controller;
					};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct RPbdb_DBT	{

							//	Parent
							RPbdb_Record*																	parent_record;

							CerializeType								type;

							uint32_t*																			size;
							uint32_t*																			buffer_size;
							uint32_t*																			partial_data_size;
							uint32_t*																			partial_data_offset;
							void**																				raw_data;

							BOOL																					has_footer;
							BOOL																					has_type;

							//	Wrapped BDB DBT
							DBT*																					wrapped_bdb_dbt;

							RPbdb_SettingsController*											environment_settings_controller;
							RPbdb_DatabaseRecordSettingsController*				settings_controller;
							RPbdb_DatabaseRecordSettingsController*				environment_level_settings_controller;
						};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct RPbdb_SecondaryKeys	{

							RPbdb_Record*											parent_record;
							uint32_t												key_count;
							RPbdb_Key**												key_pointers_array;

							//	Wrapped BDB DBT
							DBT*													wrapped_bdb_dbt;							
						};
						
					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct RPbdb_Record	{
	
						//	Parent
						RPbdb_Database*											parent_database;
	
						db_recno_t													runtime_identifier;

						//	Variables
						RPbdb_Key*														key;
						RPbdb_Key*														primary_key;
						RPbdb_SecondaryKeys*									secondary_keys;	
						RPbdb_Data*													data;
	
						BOOL																result;
	
						BOOL																exists_in_database;
						BOOL																requires_update_to_database;
							
						RPbdb_DatabaseRecordSettingsController*				settings_controller;
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_Database	{

					//	Parent
					RPbdb_DatabaseController*						parent_database_controller;

					db_recno_t										runtime_identifier;

					//	Variables
					char*											filename;
					char*											name;
					DBTYPE											type;
					
					RPbdb_Database*	runtime_storage_database;
					
					BOOL											is_secondary;
					RPbdb_Database*									secondary_database;
					RPbdb_Database*									primary_database;
					char*											index_name;
					BOOL											is_open;
					BOOL											opened_in_transaction;
					BOOL											has_associated;
					
					BOOL											verification_file_is_open;
					FILE*											verification_file;
					char*											verification_file_path;

					db_recno_t											record_number;
					
					//	Controllers
					RPbdb_DatabaseCursorController*					cursor_controller;
					RPbdb_DatabaseJoinController*					join_controller;
					RPbdb_DatabaseSequenceController*				sequence_controller;
					//	Callback Public Methods
					RPbdb_SecondaryKeyCallbackMethod					secondary_key_creation_callback_method;

					RPbdb_Environment*								default_environment;

					//	The wrapped BDB database
					DB*												wrapped_bdb_database;

					RPbdb_SettingsController*						environment_settings_controller;
					RPbdb_DatabaseSettingsController*				settings_controller;
					RPbdb_DatabaseSettingsController*				environment_level_settings_controller;
				};

			/****************************
			 *	Data Type Definitions	*
			 ****************************/

			struct RPbdb_DatabaseController	{
	
				//	Parent
				RPbdb_Environment*								parent_environment;
	
				RPbdb_Database*	runtime_storage_database;
	
				RPbdb_SettingsController*						environment_settings_controller;
				RPbdb_DatabaseSettingsController*				settings_controller;
				RPbdb_DatabaseSettingsController*				environment_level_settings_controller;
			};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct RPbdb_Error	{

					//	Parent
					RPbdb_ErrorController*						parent_error_controller;

					int											number;
					char*										function;
					char*										message;

					RPbdb_SettingsController*					environment_settings_controller;
					RPbdb_ErrorSettingsController*				settings_controller;
					RPbdb_ErrorSettingsController*				environment_level_settings_controller;
				};

			/****************************
			 *	Data Type Definitions	*
			 ****************************/

			struct RPbdb_ErrorController	{
	
				//	Parent
				RPbdb_Environment*								parent_environment;
	
				//	Variables
				RPbdb_Error*							error_stack;
	
				RPbdb_SettingsController*				environment_settings_controller;
				RPbdb_ErrorSettingsController*				settings_controller;
				RPbdb_ErrorSettingsController*				environment_level_settings_controller;
			};

		/************************
		*	Class Descriptors	*
		************************/

		struct RPbdb_Environment	{

			//	Variables
			char*									directory;
			char*									name;
			//	FIX - wtf is this a char*?
			char*									create_directory;
			BOOL									is_open;
			
			//	Controllers
			RPbdb_ErrorController*					error_controller;
			RPbdb_DatabaseController*				database_controller;
			RPbdb_LockController*					lock_controller;
			RPbdb_LogController*					log_controller;
			RPbdb_MemoryPoolController*				memory_pool_controller;
			RPbdb_MutexController*					mutex_controller;
			RPbdb_ReplicationController*			replication_controller;
	//		RPbdb_StatusController*					status_controller;
			RPbdb_TransactionController*			transaction_controller;
			RPbdb_SettingsController*				settings_controller;
			RPbdb_SettingsController*				environment_level_settings_controller;
			//	The wrapped BDB environment
			DB_ENV*									wrapped_bdb_environment;

		};

struct RPbdb_Directory {
	
	char*				path;
	RPbdb_Directory*	next;
	
};

struct RPbdb_DatabaseOpenedDuringTransaction	{
	
	RPbdb_Database*								database;
	RPbdb_DatabaseOpenedDuringTransaction*		next;
	
};

#endif