#ifndef RBDB_TYPES
	#define RBDB_TYPES

	#include <db.h>
	#include "Rbdb_Constants.h"

	//	File is listed in inverse order of type hierarchy - hierarchy goes bottom to top

typedef struct Rbdb_Environment											Rbdb_Environment;
typedef struct Rbdb_Database												Rbdb_Database;
typedef struct Rbdb_DatabaseCursorController								Rbdb_DatabaseCursorController;
typedef struct Rbdb_DatabaseCursor											Rbdb_DatabaseCursor;
typedef struct Rbdb_DatabaseController										Rbdb_DatabaseController;
typedef struct Rbdb_DatabaseSequenceController								Rbdb_DatabaseSequenceController;
typedef struct Rbdb_DatabaseSequence										Rbdb_DatabaseSequence;
typedef struct Rbdb_Error													Rbdb_Error;
typedef struct Rbdb_ErrorController										Rbdb_ErrorController;
typedef struct Rbdb_DatabaseJoinController											Rbdb_DatabaseJoinController;
typedef struct Rbdb_DatabaseJoinCursor												Rbdb_DatabaseJoinCursor;
typedef struct Rbdb_Lock													Rbdb_Lock;
typedef struct Rbdb_LockController											Rbdb_LockController;
typedef struct Rbdb_Log													Rbdb_Log;
typedef struct Rbdb_LogController											Rbdb_LogController;
typedef struct Rbdb_LogCursorController									Rbdb_LogCursorController;
typedef struct Rbdb_LogCursor												Rbdb_LogCursor;
typedef struct Rbdb_LogSequenceNumber										Rbdb_LogSequenceNumber;
typedef struct Rbdb_Record													Rbdb_Record;
typedef struct Rbdb_DBT													Rbdb_DBT;
typedef Rbdb_DBT 															Rbdb_Key;
typedef struct Rbdb_SecondaryKeys											Rbdb_SecondaryKeys;
typedef Rbdb_DBT 															Rbdb_Data;
typedef struct Rbdb_MemoryPoolFilePageController							Rbdb_MemoryPoolFilePageController;
typedef struct Rbdb_MemoryPoolFilePage										Rbdb_MemoryPoolFilePage;
typedef struct Rbdb_MemoryPoolFileController								Rbdb_MemoryPoolFileController;
typedef struct Rbdb_MemoryPoolFile											Rbdb_MemoryPoolFile;
typedef struct Rbdb_MemoryPoolController									Rbdb_MemoryPoolController;
typedef struct Rbdb_Mutex													Rbdb_Mutex;
typedef struct Rbdb_MutexController										Rbdb_MutexController;
typedef struct Rbdb_ReplicationController									Rbdb_ReplicationController;
typedef struct Rbdb_RemoteSite												Rbdb_RemoteSite;
typedef struct Rbdb_RuntimeStorage											Rbdb_RuntimeStorage;
typedef struct Rbdb_RuntimeStorageController								Rbdb_RuntimeStorageController;
typedef struct Rbdb_Transaction											Rbdb_Transaction;
typedef struct Rbdb_TransactionController									Rbdb_TransactionController;
typedef struct Rbdb_TransactionSettingsController							Rbdb_TransactionSettingsController;
typedef struct Rbdb_ThreadSettingsController								Rbdb_ThreadSettingsController;
typedef struct Rbdb_StatusSettingsController								Rbdb_StatusSettingsController;
typedef struct Rbdb_SettingsController										Rbdb_SettingsController;
typedef struct Rbdb_RuntimeStorageSettingsController						Rbdb_RuntimeStorageSettingsController;
typedef struct Rbdb_ReplicationVerbositySettingsController					Rbdb_ReplicationVerbositySettingsController;
typedef struct Rbdb_ReplicationTimeoutSettingsController					Rbdb_ReplicationTimeoutSettingsController;
typedef struct Rbdb_ReplicationSettingsController							Rbdb_ReplicationSettingsController;
typedef struct Rbdb_ReplicationElectionSettingsController					Rbdb_ReplicationElectionSettingsController;
typedef struct Rbdb_DatabaseRecordSettingsController								Rbdb_DatabaseRecordSettingsController;
typedef struct Rbdb_MutexSettingsController								Rbdb_MutexSettingsController;
typedef struct Rbdb_MessageSettingsController								Rbdb_MessageSettingsController;
typedef struct Rbdb_MemoryPoolSettingsController							Rbdb_MemoryPoolSettingsController;
typedef struct Rbdb_MemoryPoolReadWriteSettingsController					Rbdb_MemoryPoolReadWriteSettingsController;
typedef struct Rbdb_MemoryPoolFileSettingsController						Rbdb_MemoryPoolFileSettingsController;
typedef struct Rbdb_MemoryPoolFilePageSettingsController					Rbdb_MemoryPoolFilePageSettingsController;
typedef struct Rbdb_MemoryPoolFileCacheSettingsController					Rbdb_MemoryPoolFileCacheSettingsController;
typedef struct Rbdb_MemoryPoolFileCachePrioritySettingsController			Rbdb_MemoryPoolFileCachePrioritySettingsController;
typedef struct Rbdb_LogSettingsController									Rbdb_LogSettingsController;
typedef struct Rbdb_LockSettingsController									Rbdb_LockSettingsController;
typedef struct Rbdb_LockDeadlockDetectorVerbositySettingsController		Rbdb_LockDeadlockDetectorVerbositySettingsController;
typedef struct Rbdb_LockDeadlockDetectorSettingsController					Rbdb_LockDeadlockDetectorSettingsController;
typedef struct Rbdb_DatabaseJoinSettingsController									Rbdb_DatabaseJoinSettingsController;
typedef struct Rbdb_FileVerbositySettingsController						Rbdb_FileVerbositySettingsController;
typedef struct Rbdb_FileSettingsController									Rbdb_FileSettingsController;
typedef struct Rbdb_ErrorSettingsController								Rbdb_ErrorSettingsController;
typedef struct Rbdb_EnvironmentCacheSettingsController						Rbdb_EnvironmentCacheSettingsController;
typedef struct Rbdb_DirectorySettingsController							Rbdb_DirectorySettingsController;
typedef struct Rbdb_DebugVerbositySettingsController						Rbdb_DebugVerbositySettingsController;
typedef struct Rbdb_DebugSettingsController								Rbdb_DebugSettingsController;
typedef struct Rbdb_DatabaseVerificationSettingsController					Rbdb_DatabaseVerificationSettingsController;
typedef struct Rbdb_DatabaseVerbositySettingsController					Rbdb_DatabaseVerbositySettingsController;
typedef struct Rbdb_DatabaseRecordVariableLengthSettingsController				Rbdb_DatabaseRecordVariableLengthSettingsController;
typedef struct Rbdb_DatabaseTypeSettingsController							Rbdb_DatabaseTypeSettingsController;
typedef struct Rbdb_DatabaseTypeRecnoSettingsController					Rbdb_DatabaseTypeRecnoSettingsController;
typedef struct Rbdb_DatabaseTypeQueueSettingsController					Rbdb_DatabaseTypeQueueSettingsController;
typedef struct Rbdb_DatabaseTypeHashSettingsController						Rbdb_DatabaseTypeHashSettingsController;
typedef struct Rbdb_DatabaseTypeBtreeSettingsController					Rbdb_DatabaseTypeBtreeSettingsController;
typedef struct Rbdb_DatabaseSettingsController								Rbdb_DatabaseSettingsController;
typedef struct Rbdb_DatabaseSequenceSettingsController						Rbdb_DatabaseSequenceSettingsController;
typedef struct Rbdb_DatabaseRecordReadWriteSettingsController					Rbdb_DatabaseRecordReadWriteSettingsController;
typedef struct Rbdb_DatabaseRecordFixedLengthSettingsController					Rbdb_DatabaseRecordFixedLengthSettingsController;
typedef struct Rbdb_DatabaseErrorSettingsController						Rbdb_DatabaseErrorSettingsController;
typedef struct Rbdb_DatabaseEncryptionSettingsController					Rbdb_DatabaseEncryptionSettingsController;
typedef struct Rbdb_DatabaseCursorCacheSettingsController					Rbdb_DatabaseCursorCacheSettingsController;
typedef struct Rbdb_DatabaseCursorCachePrioritySettingsController			Rbdb_DatabaseCursorCachePrioritySettingsController;
typedef struct Rbdb_DatabaseCursorSettingsController						Rbdb_DatabaseCursorSettingsController;
typedef struct Rbdb_DatabaseCursorReadWriteSettingsController				Rbdb_DatabaseCursorReadWriteSettingsController;
typedef struct Rbdb_DatabaseCompactSettingsController						Rbdb_DatabaseCompactSettingsController;
typedef struct Rbdb_DatabaseCacheSettingsController						Rbdb_DatabaseCacheSettingsController;
typedef struct Rbdb_DatabaseCachePrioritySettingsController				Rbdb_DatabaseCachePrioritySettingsController;
typedef struct Rbdb_DatabaseAssociationSettingsController					Rbdb_DatabaseAssociationSettingsController;
typedef struct Rbdb_CompactStatus											Rbdb_CompactStatus;
typedef struct Rbdb_Directory												Rbdb_Directory;
typedef struct Rbdb_DatabaseOpenedDuringTransaction						Rbdb_DatabaseOpenedDuringTransaction;

typedef struct Rbdb_DataFooter1												Rbdb_DataFooter1;
typedef	enum   Rbdb_DatabaseRecordStorageType										Rbdb_DatabaseRecordStorageType;

typedef		RBDB_SECONDARY_KEY_CREATION_RETURN	(*Rbdb_SecondaryKeyCallbackMethod)(	Rbdb_Database*			secondary_database,
																																									Rbdb_Record*			primary_record,
																																									Rbdb_SecondaryKeys*	secondary_keys_to_return );

/*************************************
*  Thread Settings Callback Methods  *
*************************************/

typedef		BOOL	(*Rbdb_IsThreadAliveCallbackMethod)(	Rbdb_Environment*		environment,
																											pid_t								process_id,
																											db_threadid_t				thread_id,
																											BOOL								associated_with_single_process );
typedef		void	(*Rbdb_UniqueThreadIdentifierCallbackMethod)(	Rbdb_Environment*		environment,
																															pid_t*							process_id,
																															db_threadid_t*			thread_id	);
typedef		char* (*Rbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod)(	Rbdb_Environment*		environment,
																																									pid_t								process_id,
																																									db_threadid_t				thread_id,
																																									char*								string_buffer );

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_TransactionSettingsController	{
	
						//	Parent
						Rbdb_SettingsController*				parent_settings_controller;
	
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
						int (*rollbackward_callback_method)(	Rbdb_Environment*				environment,                                                                                                                                                                	
																Rbdb_Record*		transaction_log_record );
						int (*rollforward_callback_method)(		Rbdb_Environment*				environment,                                                           				
														   		Rbdb_Record*		transaction_log_record );
						int (*abort_callback_method)(			Rbdb_Environment*				environment,                                                           				
													 			Rbdb_Record*		transaction_log_record );
						int (*apply_callback_method)(			Rbdb_Environment*				environment,                                                           				
													 			Rbdb_Record*		transaction_log_record );
	*/
	
						Rbdb_SettingsController*				environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseRecordSettingsController	{

						//	Parent
						Rbdb_DatabaseSettingsController*		parent_database_settings_controller;
						                                        
						Rbdb_Record*							parent_record;
                                                                						                                        
						Rbdb_DatabaseRecordReadWriteSettingsController*							record_read_write_settings_controller;
						Rbdb_DatabaseRecordVariableLengthSettingsController*				record_variable_length_settings_controller;
						Rbdb_DatabaseRecordFixedLengthSettingsController*						record_fixed_length_settings_controller;

						Rbdb_SettingsController*				environment_settings_controller;

					};


								/****************************
								*	Data Type Definitions	*
								****************************/

								struct Rbdb_MemoryPoolFilePage	{

									//	Parent
									Rbdb_MemoryPoolFilePageController*										parent_memory_pool_file_page_controller;

									db_recno_t					runtime_identifier;

									db_pgno_t*																page_address;

									void*																	page_data;

									DB_MPOOLFILE*															wrapped_bdb_memory_pool_file;

									Rbdb_SettingsController*													environment_settings_controller;
									Rbdb_MemoryPoolFilePageSettingsController*				settings_controller;
									Rbdb_MemoryPoolFilePageSettingsController*				environment_level_settings_controller;
								};

								/****************************
								*	Data Type Definitions	*
								****************************/

								struct Rbdb_MemoryPoolFilePageController	{

									//	Parent
									Rbdb_MemoryPoolFile*										parent_memory_pool_file;

									Rbdb_Database*													runtime_storage_database;

									Rbdb_SettingsController*								environment_settings_controller;
									Rbdb_MemoryPoolFilePageSettingsController*				settings_controller;
									Rbdb_MemoryPoolFilePageSettingsController*				environment_level_settings_controller;
								};

							/****************************
							*	Data Type Definitions	*
							****************************/

							struct Rbdb_MemoryPoolFile	{

								//	Parent
								Rbdb_MemoryPoolFileController*								parent_memory_pool_file_controller;

								db_recno_t					runtime_identifier;

								//	Wrapped BDB memory pool file
								DB_MPOOLFILE*												wrapped_bdb_memory_pool_file;
								
								Rbdb_SettingsController*							environment_settings_controller;
								Rbdb_MemoryPoolFileSettingsController*				settings_controller;
								Rbdb_MemoryPoolFileSettingsController*				environment_level_settings_controller;
							};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct Rbdb_MemoryPoolFileController	{

							//	Parent
							Rbdb_MemoryPoolController*			parent_memory_pool_controller;
							
							Rbdb_Database*									runtime_storage_database;
/*
							int									(*page_in_method)(	Rbdb_Environment*			environment,
							   														void*			page_data,
							   														Rbdb_Data*		page_cookie	);

							int									(*page_out_method)(	Rbdb_Environment*			environment,
							   														void*			page_data,
							   														Rbdb_Data*		page_cookie	);
*/
							Rbdb_SettingsController*							environment_settings_controller;
							Rbdb_MemoryPoolFileSettingsController*				settings_controller;
							Rbdb_MemoryPoolFileSettingsController*				environment_level_settings_controller;
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_MemoryPoolReadWriteSettingsController	{

							//	Parent
							Rbdb_MemoryPoolSettingsController*							parent_memory_pool_settings_controller;

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

							Rbdb_SettingsController*									environment_settings_controller;

						};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct Rbdb_MemoryPoolFilePageSettingsController	{

								//	Parent
								Rbdb_MemoryPoolFileSettingsController*						parent_memory_pool_file_settings_controller;

								BOOL														get_page_creates_page_if_does_not_exist;
								BOOL														get_page_writes_copy_before_eviction;
								BOOL														get_page_writes_before_eviction_without_copy;
								BOOL														get_page_returns_last_page;
								BOOL														get_page_creates_new_page;

								Rbdb_SettingsController*									environment_settings_controller;

							};

								/****************************
								 *	Data Type Definitions	*
								 ****************************/

								struct Rbdb_MemoryPoolFileCachePrioritySettingsController	{

									//	Parent
									Rbdb_MemoryPoolFileCacheSettingsController*				parent_memory_pool_file_cache_settings_controller;

									DB_CACHE_PRIORITY											priority;

									Rbdb_SettingsController*									environment_settings_controller;
								};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct Rbdb_MemoryPoolFileCacheSettingsController	{

								//	Parent
								Rbdb_MemoryPoolFileSettingsController*												parent_memory_pool_file_settings_controller;

								Rbdb_MemoryPoolFileCachePrioritySettingsController*						priority_settings_controller;
							};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_MemoryPoolFileSettingsController	{

							//	Parent
							Rbdb_MemoryPoolSettingsController*						parent_memory_pool_settings_controller;

							Rbdb_MemoryPoolFile*													parent_memory_pool_file;

							uint																					create_with_number_initial_bytes;
							uint8_t*																			file_id;
							int																						file_type;
							int																						log_sequence_number_offset;
							uint64_t																			page_size_in_bytes;
							uint64_t																			max_file_size_in_bytes;
							Rbdb_Data*																		cookie;

							Rbdb_MemoryPoolFileCacheSettingsController*		cache_settings_controller;
							Rbdb_MemoryPoolFilePageSettingsController*		page_settings_controller;

							Rbdb_SettingsController*											environment_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_MemoryPoolSettingsController	{
	
						//	Parent
						Rbdb_SettingsController*								parent_settings_controller;
	
						BOOL													on;
						BOOL													memory_mapping;						
						BOOL													threaded;
						BOOL													remove_file_with_last_reference;
						BOOL													pagesize_factor_mismatch_should_fail;
	
						Rbdb_MemoryPoolFileSettingsController*					file_settings_controller;
						Rbdb_MemoryPoolReadWriteSettingsController*			record_read_write_settings_controller;
	
						Rbdb_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseJoinSettingsController	{

						//	Parent
						Rbdb_DatabaseSettingsController*								parent_database_settings_controller;

						BOOL													degree_one_isolation;
						BOOL													use_write_locks_instead_of_read_locks;
						BOOL													sort_before_join;

						Rbdb_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DirectorySettingsController	{

						//	Parent
						Rbdb_SettingsController*								parent_settings_controller;

						char*													home_directory_path;
						
						Rbdb_Directory*										directories;

						Rbdb_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_RuntimeStorageSettingsController	{
							
						//	Parent
						Rbdb_SettingsController*								parent_settings_controller;
		
						BOOL													store_in_application_memory;
						BOOL													store_in_system_memory;
						BOOL													store_on_disk;
						BOOL													log_runtime_storage_activity;

						BOOL													automatic_default_environment;
						
						Rbdb_SettingsController*								environment_settings_controller;
					};
	
							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct Rbdb_LockDeadlockDetectorVerbositySettingsController	{

								//	Parent
								Rbdb_LockDeadlockDetectorSettingsController*								parent_lock_deadlock_detector_settings_controller;

								BOOL																		display_additional_information_during_deadlock_detection;
								BOOL																		display_wait_table_during_deadlock_detection;

								Rbdb_SettingsController*								environment_settings_controller;
							};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_LockDeadlockDetectorSettingsController	{

							//	Parent
							Rbdb_LockSettingsController*								parent_lock_settings_controller;

							uint32_t																					deadlock_settings;

							Rbdb_LockDeadlockDetectorVerbositySettingsController*		verbosity_settings_controller;

							Rbdb_SettingsController*									environment_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_LockSettingsController	{

						//	Parent
						Rbdb_SettingsController*								parent_settings_controller;

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

						Rbdb_LockDeadlockDetectorSettingsController*			deadlock_detector_settings_controller;

						Rbdb_SettingsController*								environment_settings_controller;
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_LogSettingsController	{

						//	Parent
						Rbdb_SettingsController*								parent_settings_controller;

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

						Rbdb_SettingsController*								environment_settings_controller;
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_ReplicationVerbositySettingsController	{
	
							//	Parent
							Rbdb_ReplicationSettingsController*								parent_replication_settings_controller;
	
							BOOL																display_all_replication_information;
							BOOL																display_election_information;
							BOOL																display_replication_master_lease_information;
							BOOL																display_misc_processing_information;
							BOOL																display_message_processing_information;
							BOOL																display_client_synchronization_information;
							BOOL																display_manager_connection_failure_information;
							BOOL																display_manager_misc_processing;
	
							Rbdb_SettingsController*											environment_settings_controller;
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_ReplicationTimeoutSettingsController	{
	
							//	Parent
							Rbdb_ReplicationSettingsController*								parent_replication_settings_controller;
	
							uint32_t															timeout;
							uint32_t															wait_time_before_checkpoint_write;
							uint32_t															wait_time_before_retry_connection;
							uint32_t															election_timeout;
							uint32_t															wait_time_before_retry_election;
							uint32_t															full_election_participation_timeout;
							uint32_t															heartbeat_monitor_pulse;
							uint32_t															heartbeat_broadcast_pulse;
							uint32_t															lease_timeout;
	
							Rbdb_SettingsController*											environment_settings_controller;
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_ReplicationElectionSettingsController	{
	
							//	Parent
							Rbdb_ReplicationSettingsController*								parent_replication_settings_controller;
	
							int																	number_of_sites_required_for_election;
							int																	number_of_votes_required_for_election;
	
							BOOL																wait_for_all_clients;
							BOOL																wait_for_all_electable_peers;
							BOOL																never_wait;
							BOOL																wait_for_at_least_one_client;
							BOOL																wait_for_at_least_one_electable_peer;
							BOOL																wait_for_minimum_electable_peers_for_durable_election;
							
							int																	current_ack_policy;
	
							Rbdb_SettingsController*											environment_settings_controller;
						};


					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_ReplicationSettingsController	{
	
						//	Parent
						Rbdb_SettingsController*								parent_settings_controller;
	
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
	
						Rbdb_Record*											additional_start_information;
	
						Rbdb_ReplicationElectionSettingsController*			acknowledgement_policy_settings_controller;
						Rbdb_ReplicationTimeoutSettingsController*				timeout_settings_controller;	
						Rbdb_ReplicationVerbositySettingsController*			verbosity_settings_controller;	
	
						Rbdb_SettingsController*							environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_MutexSettingsController	{
	
						//	Parent
						Rbdb_SettingsController*								parent_settings_controller;
	
						uint32_t												spin_times_before_blocking_for_test_and_spin_mutexes;
						uint32_t												max_allowable_mutexes;
						uint32_t												increment_for_adding_mutexes;
						uint32_t												mutex_alignment;
						BOOL													associated_with_single_process;
						BOOL													self_blocking;
	
						Rbdb_SettingsController*								environment_settings_controller;
	
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseVerificationSettingsController	{

							//	Parent
							Rbdb_DatabaseSettingsController*						parent_database_settings_controller;

							FILE*													file;
							BOOL													file_is_open;
							
							char*													file_path;
							BOOL													aggressive_key_data_pair_dump;
							BOOL													printable_characters;
							BOOL													skip_order_checking;
							BOOL													only_order_check;
							BOOL													force_order_check;
							BOOL													has_done_unordered_check;
							
							Rbdb_SettingsController*								environment_settings_controller;
							
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseRecordVariableLengthSettingsController	{

							//	Parent
							Rbdb_DatabaseRecordSettingsController*						parent_database_record_settings_controller;

							int														delimeter_byte;
							//	FIX	- what happened to these??
							BOOL													index_primary;
							BOOL													secondary_key_is_immutable;

							Rbdb_SettingsController*								environment_settings_controller;

						};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct Rbdb_DatabaseCursorReadWriteSettingsController	{

								//	Parent
								Rbdb_DatabaseCursorSettingsController*						parent_database_cursor_settings_controller;

								BOOL														permit_write;
								BOOL														ignore_lease;
								BOOL														write_locks_instead_of_read_locks;
								BOOL														multiple_data_items;
								BOOL														return_multiple_key_data_pairs;

								Rbdb_SettingsController*									environment_settings_controller;

							};

								/****************************
								 *	Data Type Definitions	*
								 ****************************/

								struct Rbdb_DatabaseCursorCachePrioritySettingsController	{
		
									//	Parent
									Rbdb_DatabaseCursorCacheSettingsController*						parent_database_cursor_cache_settings_controller;
		
									DB_CACHE_PRIORITY													priority;
		
									Rbdb_SettingsController*											environment_settings_controller;
		
								};

							/****************************
							 *	Data Type Definitions	*
							 ****************************/

							struct Rbdb_DatabaseCursorCacheSettingsController	{

								//	Parent
								Rbdb_DatabaseCursorSettingsController*						parent_database_cursor_settings_controller;

								//	FIX - seems like these are missing function-wise? did something get deleted? check out this controller
								int															number_cache_regions;
								uint32_t													max_size_in_bytes;

								Rbdb_DatabaseCursorCachePrioritySettingsController*		priority_settings_controller;

								Rbdb_SettingsController*									environment_settings_controller;

							};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseCursorSettingsController	{

							//	Parent
							Rbdb_DatabaseSettingsController*						parent_database_settings_controller;
							Rbdb_DatabaseCursor*									parent_database_cursor;

							//	Variables
							BOOL													duplicate_retains_location;

							//	Controllers
							Rbdb_DatabaseCursorCacheSettingsController*			cache_controller;
							Rbdb_DatabaseCursorReadWriteSettingsController*		record_read_write_settings_controller;

							Rbdb_SettingsController*								environment_settings_controller;

						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseSequenceSettingsController	{
	
							//	Parent
							Rbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
							Rbdb_DatabaseSequence*									parent_sequence;
	
							BOOL													increasing;
							BOOL													decreasing;
							BOOL													wrapping;
							db_seq_t												range_minimum;
							db_seq_t												range_maximum;
							int32_t													number_of_cached_elements;
							db_seq_t												initial_value;
							int32_t													default_step_value;
	
							Rbdb_SettingsController*								environment_settings_controller;
	
						};

						/****************************
						 *	Record Storage Type	*
						 ****************************/

						enum Rbdb_DatabaseRecordStorageType	{
							
							RbdbType_Raw,
							RbdbType_Integer,
							RbdbType_Float,
							RbdbType_Complex,
							RbdbType_Rational,
							RbdbType_String,
							RbdbType_Symbol,
							RbdbType_Regexp,
							RbdbType_Match,
							RbdbType_File,
							RbdbType_TrueFalse,
							RbdbType_ClassName
							
						};

						/****************************
						 *	Data Footer	*
						 ****************************/
						
						#define	RBDB_DATABASE_DATA_FOOTER_VERSION	1
						struct Rbdb_DataFooter1	{
							
							struct timeval										creation_stamp;
							struct timeval										modification_stamp;

							//	we keep key type in the data footer so that info is all in the same place
							//	every time a key is written, key_type is updated in data
							Rbdb_DatabaseRecordStorageType		key_type;
							Rbdb_DatabaseRecordStorageType		data_type;
							
							//	version needs to be last so we can look from the end to check
							int																version;
							
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseRecordReadWriteSettingsController	{
	
							//	Parent
							Rbdb_DatabaseRecordSettingsController*						parent_database_record_settings_controller;
	
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

							Rbdb_SettingsController*								environment_settings_controller;
	
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseTypeRecnoSettingsController	{
	
							//	Parent
							Rbdb_DatabaseTypeSettingsController*		parent_database_type_settings_controller;
	
							BOOL										record_renumbering;
							BOOL										snapshot_isolation;
							char*										source_file_path;
	/*
							void										(*append_callback_method)(	Rbdb_Database*		database,
																								  struct Rbdb_Record*		record );
	*/
							Rbdb_SettingsController*					environment_settings_controller;

						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseTypeQueueSettingsController	{
	
							//	Parent
							Rbdb_DatabaseTypeSettingsController*						parent_database_type_settings_controller;
	
							BOOL														return_key_data_pairs_in_order;
							uint32_t													number_of_pages_for_underlying_data;
	
							Rbdb_SettingsController*									environment_settings_controller;
	
						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseTypeHashSettingsController	{
	
							//	Parent
							Rbdb_DatabaseTypeSettingsController*		parent_database_type_settings_controller;
	
							//	Variables                               
							uint32_t									table_size;
							uint32_t									density;	
	
	/*
							//	Callback Public Methods
							uint32_t									(*hash_method)(					Rbdb_Database*		database, 
																					   const void*			bytes,    
																					   uint32_t			length );
							int											(*compare_method)(				Rbdb_Database*		database, 
																						  const DBT*			data_one, 
																						  const DBT*			data_two );
							int											(*duplicate_compare_method)(	Rbdb_Database*		database, 
																									const DBT*			data_one, 
																									const DBT*			data_two );
	*/
							Rbdb_SettingsController*				environment_settings_controller;

						};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseTypeBtreeSettingsController	{
	
							//	Parent
							Rbdb_DatabaseTypeSettingsController*		parent_database_type_settings_controller;
	
							BOOL										record_number_retrieval;
							BOOL										reverse_splitting;
							uint32_t									minimum_keys_per_page;
	/*
							size_t										(*prefix_compare_method)(		Rbdb_Database*		database, 
																								 const DBT*			data_one, 
																								 const DBT*			data_two );
							int											(*compare_method)(				DBRbdb_Database*	database, 
																						  const DBT*			data_one, 
																						  const DBT*			data_two );
							int											(*duplicate_compare_method)(	Rbdb_Database*		database, 
																									const DBT*			data_one, 
																									const DBT*			data_two );
	*/
	
							Rbdb_SettingsController*				environment_settings_controller;

						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseTypeSettingsController	{
	
						//	Parent
						Rbdb_DatabaseSettingsController*						parent_database_settings_controller;

						Rbdb_Database*											parent_database;

						DBTYPE													default_database_type;
						Rbdb_DatabaseTypeBtreeSettingsController*				btree_settings_controller;
						Rbdb_DatabaseTypeHashSettingsController*				hash_settings_controller;
						Rbdb_DatabaseTypeQueueSettingsController*				queue_settings_controller;
						Rbdb_DatabaseTypeRecnoSettingsController*				recno_settings_controller;
	
						Rbdb_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseVerbositySettingsController	{
	
						//	Parent
						Rbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
						BOOL													display_additional_information_for_db_register_flag;
	
						Rbdb_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseEncryptionSettingsController	{
	
						//	Parent
						Rbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
						BOOL													encrypted;
						
						char*													password;
	
						Rbdb_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseCompactSettingsController	{
	
						//	Parent
						Rbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
						int														fill_percent;
						int														max_pages_to_compact;
						int														timeout;
	
						Rbdb_SettingsController*								environment_settings_controller;
	
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseAssociationSettingsController	{
	
						//	Parent
						Rbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
						BOOL													index_primary_database;
						BOOL													secondary_key_is_immutable;
	
						Rbdb_SettingsController*								environment_settings_controller;
	
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseCachePrioritySettingsController	{
	
							//	Parent
							Rbdb_DatabaseCacheSettingsController*						parent_database_cache_settings_controller;
	
							DB_CACHE_PRIORITY											priority;
	
							Rbdb_SettingsController*								environment_settings_controller;
	
						};
	
					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseCacheSettingsController	{
	
						//	Parent
						Rbdb_DatabaseSettingsController*						parent_database_settings_controller;
	
						int														number_cache_regions;
						uint32_t												max_size_in_bytes;
	
						Rbdb_DatabaseCachePrioritySettingsController*			priority_settings_controller;
		
						Rbdb_SettingsController*								environment_settings_controller;
		
					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseRecordFixedLengthSettingsController	{

						//	Parent
						Rbdb_DatabaseRecordSettingsController*						parent_database_record_settings_controller;

						uint32_t												record_length;
						int														record_padding_byte;

						Rbdb_SettingsController*								environment_settings_controller;

					};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseErrorSettingsController	{
	
						//	Parent
						Rbdb_DatabaseSettingsController*		parent_database_settings_controller;
	
						//	Variables               
						FILE*									error_file;
						BOOL									error_file_is_open;
						char*									error_file_path;
						char*									error_prefix;
	/*
						//	Callback Public Methods
						void									(*error_callback_method)(	Rbdb_Environment*			environment,                                                                                                                                             
																						 const char*		error_prefix_string,                                                                                                                                                            
																						 const char*		error_message	);
	*/
	
						Rbdb_SettingsController*				environment_settings_controller;

					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_DatabaseSettingsController	{
	
					//	Parent
					Rbdb_SettingsController*								parent_settings_controller;
	
					Rbdb_Database*											parent_database;
	
					BOOL													on;
					BOOL													checksum;
					BOOL													transaction_durability_off;
					uint32_t												pagesize;
					BOOL													big_endian;
					BOOL													little_endian;
					BOOL													is_byteswapped;
	
					Rbdb_DatabaseJoinSettingsController*							join_settings_controller;
					Rbdb_DatabaseErrorSettingsController*					error_settings_controller;
					Rbdb_DatabaseCacheSettingsController*					cache_settings_controller;
					Rbdb_DatabaseAssociationSettingsController*			association_settings_controller;
					Rbdb_DatabaseCompactSettingsController*				compact_settings_controller;
					Rbdb_DatabaseEncryptionSettingsController*				encryption_settings_controller;
					Rbdb_DatabaseVerbositySettingsController*				verbosity_settings_controller;
					Rbdb_DatabaseTypeSettingsController*					type_settings_controller;
					Rbdb_DatabaseSequenceSettingsController*					sequence_settings_controller;
					Rbdb_DatabaseCursorSettingsController*					cursor_settings_controller;
					Rbdb_DatabaseVerificationSettingsController*					verification_settings_controller;
					Rbdb_DatabaseRecordSettingsController*							record_settings_controller;

					Rbdb_SettingsController*								environment_settings_controller;

				};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_StatusSettingsController	{

					//	Parent
					Rbdb_SettingsController*								parent_settings_controller;

					BOOL													display_all;
					BOOL													reset_after_display;
					BOOL													display_for_all_subsystems;
					BOOL													no_traversal;
					BOOL													degree_two_isolation;
					BOOL													degree_one_isolation;

					Rbdb_SettingsController*								environment_settings_controller;

				};
				
				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_MessageSettingsController	{
	
					//	Parent
					Rbdb_SettingsController*			parent_settings_controller;
	
					FILE*								message_file;
					BOOL								message_file_is_open;
					char*								message_file_path;
	/*
					void								(*message_callback_method)(										Rbdb_Environment*			environment, 
																				   const char*		message );
					void								*(panic_callback_method)(										Rbdb_Environment*			environment );									
					void								*(site_is_now_replication_client_callback_method)(				Rbdb_Environment*			environment );			
					void								*(site_won_replication_election_callback_method)(				Rbdb_Environment*			environment );			
					void								*(site_is_now_master_of_replication_group_callback_method)(		Rbdb_Environment*			environment );	
					void								*(replication_group_has_new_master_callback_method)(			Rbdb_Environment*			environment );		
					void								*(replication_acknowledgement_failed_callback_method)(			Rbdb_Environment*			environment );		
					void								*(replication_startup_completed_callback_method)(				Rbdb_Environment*			environment );			
					void								*(write_failed_callback_method)(								Rbdb_Environment*			environment );						
*/
					Rbdb_SettingsController*				environment_settings_controller;

				};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_ErrorSettingsController	{

					//	Parent
					Rbdb_SettingsController*		parent_settings_controller;

					FILE*							error_file;
					char*							error_file_path;
					BOOL							error_file_is_open;
					char*							prefix;
/*
					void							(*error_callback_method)(	Rbdb_Environment*					environment,                                                                                                                  
																			 const char*				error_prefix,                                                                                                                               
																			 const char*				error_message );
*/
					Rbdb_SettingsController*				environment_settings_controller;

				};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_ThreadSettingsController	{

					//	Parent
					Rbdb_SettingsController*													parent_settings_controller;

					//	Variables
					BOOL																		on;
					uint32_t																	thread_count;

					Rbdb_IsThreadAliveCallbackMethod											is_thread_alive_callback_method;
					Rbdb_UniqueThreadIdentifierCallbackMethod									unique_thread_identifier_callback_method;
					Rbdb_FormatThreadAndProcessIdentifierForDisplayCallbackMethod				format_thread_and_process_identifier_for_display_callback_method;
					Rbdb_SettingsController*													environment_settings_controller;

				};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_FileVerbositySettingsController	{

						//	Parent
						Rbdb_FileSettingsController*								parent_file_settings_controller;

						BOOL														display_additional_information_during_open_close_rename_file_operations;
						BOOL														display_additional_information_during_all_file_operations;
						
						Rbdb_SettingsController*								environment_settings_controller;
						
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_FileSettingsController	{

					//	Parent
					Rbdb_SettingsController*								parent_settings_controller;

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

					Rbdb_FileVerbositySettingsController*					verbosity_settings_controller;

					Rbdb_SettingsController*								environment_settings_controller;

				};
		
				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_EnvironmentCacheSettingsController	{

					//	Parent
					Rbdb_SettingsController*								parent_settings_controller;

					BOOL													buffering;
					uint64_t												size_in_bytes;
					uint64_t												max_size_in_bytes;


					Rbdb_SettingsController*								environment_settings_controller;
				};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DebugVerbositySettingsController	{

						//	Parent
						Rbdb_DebugSettingsController*								parent_debug_settings_controller;

						BOOL														display_additional_information_during_recovery;

						Rbdb_SettingsController*									environment_settings_controller;
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_DebugSettingsController	{

					//	Parent
					Rbdb_SettingsController*								parent_settings_controller;
					BOOL													check_for_environment_failure_during_open;
					BOOL													run_normal_recovery_before_opening_environment;
					BOOL													run_catastrophic_recovery_before_opening_environment;
					BOOL													open_in_lockdown;
					BOOL													check_for_recovery_on_load;
					BOOL													prohibit_panic;
					BOOL													panic;
					BOOL													yield_cpu_for_stress_test;

					Rbdb_DebugVerbositySettingsController*					verbosity_settings_controller;

					Rbdb_SettingsController*								environment_settings_controller;
				};

			/****************************
			 *	Data Type Definitions	*
			 ****************************/

			struct Rbdb_SettingsController	{
	
				//	Parent
				Rbdb_Environment*										parent_environment;
				
				//	Variables
				long													shm_key;
	
				//	Controllers
				Rbdb_DatabaseSettingsController*						database_settings_controller;
				Rbdb_DebugSettingsController*							debug_settings_controller;
				Rbdb_EnvironmentCacheSettingsController*				cache_settings_controller;
				Rbdb_FileSettingsController*							file_settings_controller;
				Rbdb_ThreadSettingsController*							thread_settings_controller;
				Rbdb_ErrorSettingsController*							error_settings_controller;
				Rbdb_MessageSettingsController*							message_settings_controller;
				Rbdb_StatusSettingsController*							status_settings_controller;
				Rbdb_MutexSettingsController*							mutex_settings_controller;
				Rbdb_ReplicationSettingsController*							replication_settings_controller;
				Rbdb_LogSettingsController*							log_settings_controller;
				Rbdb_LockSettingsController*							lock_settings_controller;
				Rbdb_RuntimeStorageSettingsController*							runtime_storage_settings_controller;
				Rbdb_DirectorySettingsController*							directory_settings_controller;
				Rbdb_MemoryPoolSettingsController*							memory_pool_settings_controller;
				Rbdb_TransactionSettingsController*					transaction_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct Rbdb_Transaction	{

					//	Parent
					Rbdb_TransactionController*							parent_transaction_controller;
					
					db_recno_t										runtime_identifier;
					
					//	Variables
					char*													name;

					BOOL												is_open;

					uint8_t													global_id;

					Rbdb_DatabaseOpenedDuringTransaction*				databases_opened_during_transaction;

					//	Wrapped BDB Transaction
					DB_TXN*													wrapped_bdb_transaction;

					Rbdb_SettingsController*							environment_settings_controller;
					Rbdb_TransactionSettingsController*				settings_controller;
					Rbdb_TransactionSettingsController*				environment_level_settings_controller;
				};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct Rbdb_TransactionController	{

				//	Parent
				Rbdb_Environment*										parent_environment;

				Rbdb_Database*	runtime_storage_database;

				uint32_t												current_transaction_index;
				Rbdb_Transaction**										transactions;

				//	Variables
				u_int32_t												maximum_number_of_transactions_to_recover;
				u_int32_t												current_transaction_depth;

				Rbdb_SettingsController*							environment_settings_controller;
				Rbdb_TransactionSettingsController*				settings_controller;
			};


			/****************************
			*	Data Type Definitions	*
			****************************/

			struct Rbdb_RuntimeStorageController	{

				//	Variables
				Rbdb_Environment*												runtime_environment;
				Rbdb_Environment*												default_environment;

				Rbdb_DatabaseCursor*										database_cursor;

				//	Runtime Storage instances are stored by name--&db_env
				Rbdb_Database*													runtime_storages_database;

				//	All Rbdb_Environment* and Rbdb_Database* are stored by their wrapped_bdb_database DB* in these databases
				Rbdb_Database*													environment_reference_database;
				Rbdb_Database*													database_reference_database;

				//	Unlike other controllers, the environmental runtime storage settings controller is stored inside the runtime storage controller
				Rbdb_RuntimeStorageSettingsController*							settings_controller;
			};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_RemoteSite	{
	
					//	Parent
					Rbdb_ReplicationController*							parent_replication_controller;
	
					db_recno_t										runtime_identifier;

					//	Variables
					
					char*													host;
					u_int													port;
					
					int														replication_environment_id;
					
					BOOL													connected;
					
					long													hard_timeout;
					long													soft_timeout;
	
					Rbdb_SettingsController*							environment_settings_controller;
					Rbdb_ReplicationSettingsController*				settings_controller;
					Rbdb_ReplicationSettingsController*				environment_level_settings_controller;
				};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct Rbdb_ReplicationController	{

				//	Parent
				Rbdb_Environment*													parent_environment;

				Rbdb_Database*	runtime_storage_database;

				u_int													site_count;

				//	Variables
				int														replication_environment_id;
				Rbdb_RemoteSite**										remote_site_list;

				Rbdb_SettingsController*							environment_settings_controller;
				Rbdb_ReplicationSettingsController*				settings_controller;
				Rbdb_ReplicationSettingsController*				environment_level_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct Rbdb_Mutex	{

					//	Parent
					Rbdb_MutexController*										parent_mutex_controller;

					db_recno_t										runtime_identifier;

					db_mutex_t													wrapped_bdb_mutex;

					Rbdb_SettingsController*					environment_settings_controller;
					Rbdb_MutexSettingsController*				settings_controller;
					Rbdb_MutexSettingsController*				environment_level_settings_controller;
				};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct Rbdb_MutexController	{

				//	Parent
				Rbdb_Environment*													parent_environment;

				Rbdb_Database*	runtime_storage_database;

				Rbdb_SettingsController*					environment_settings_controller;
				Rbdb_MutexSettingsController*				settings_controller;
				Rbdb_MutexSettingsController*				environment_level_settings_controller;
			};

			/****************************
			*	Data Type Definitions	*
			****************************/

			struct Rbdb_MemoryPoolController	{

				//	Parent
				Rbdb_Environment*											parent_environment;

				//	Variables
				int												memory_space_for_pages;
/*
				//	Callbacks
				void*											(*malloc_method)(	size_t );
				void*											(*realloc_method)(	void*, 
																					size_t );
				void*											(*free_method)(		void* );
*/
				Rbdb_MemoryPoolFileController*					file_controller;

				Rbdb_SettingsController*						environment_settings_controller;
				Rbdb_MemoryPoolSettingsController*				settings_controller;
				Rbdb_MemoryPoolSettingsController*				environment_level_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct Rbdb_LogCursor	{

					//	Parent
					Rbdb_LogCursorController*					parent_log_cursor_controller;

					db_recno_t										runtime_identifier;

					//	Wrapped BDB log database_cursor
					DB_LOGC*									wrapped_bdb_log_cursor;

					Rbdb_SettingsController*					environment_settings_controller;
					Rbdb_LogSettingsController*				settings_controller;
					Rbdb_LogSettingsController*				environment_level_settings_controller;
				};

							/****************************
							*	Data Type Definitions	*
							****************************/

							struct Rbdb_LogSequenceNumber	{

								//	Parent
								Rbdb_Log*									parent_log;

								//	Wrapped BDB log database_cursor
								DB_LSN*										wrapped_bdb_log_sequence_number;

								Rbdb_SettingsController*					environment_settings_controller;
								Rbdb_LogSettingsController*				settings_controller;
								Rbdb_LogSettingsController*				environment_level_settings_controller;
							};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct Rbdb_Log	{

							//	Parent
							Rbdb_LogController*						parent_log_controller;

							db_recno_t										runtime_identifier;

							//	Variables
							Rbdb_Record*								record;
							Rbdb_LogSequenceNumber*					log_sequence_number;
							
							char*										filename;

							Rbdb_SettingsController*					environment_settings_controller;
							Rbdb_LogSettingsController*				settings_controller;
							Rbdb_LogSettingsController*				environment_level_settings_controller;
						};

					/****************************
					*	Data Type Definitions	*
					****************************/

					struct Rbdb_LogController	{

						//	Parent
						Rbdb_Environment*								parent_environment;

						Rbdb_Database*									runtime_storage_database;

						Rbdb_LogCursorController*						cursor_controller;

						Rbdb_SettingsController*					environment_settings_controller;
						Rbdb_LogSettingsController*				settings_controller;
						Rbdb_LogSettingsController*				environment_level_settings_controller;
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_LogCursorController	{
					
					//	Parent
					Rbdb_LogController*						parent_log_controller;

					Rbdb_Database*	runtime_storage_database;
					
					Rbdb_SettingsController*					environment_settings_controller;
					Rbdb_LogSettingsController*				settings_controller;
					Rbdb_LogSettingsController*				environment_level_settings_controller;
				};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct Rbdb_Lock	{

					//	Parent
					Rbdb_LockController*						parent_lock_controller;

					db_recno_t										runtime_identifier;

					//	Variables
					int											mode;

					uint32_t									timeout;

					//	Object being locked
					void*										object;

					//	Wrapped BDB lock
					DB_LOCK										wrapped_bdb_lock;

					Rbdb_SettingsController*					environment_settings_controller;
					Rbdb_LockSettingsController*				settings_controller;
					Rbdb_LockSettingsController*				environment_level_settings_controller;
				};
	
			/****************************
			*	Data Type Definitions	*
			****************************/

			struct Rbdb_LockController	{

				//	Parent
				Rbdb_Environment*							parent_environment;
				
				Rbdb_Database*	runtime_storage_database;
				
				//	Variables
				uint32_t									locker_id;
				Rbdb_Lock**									queued_locks;
				int											number_of_queued_locks;
				int											number_of_locks_last_cleared;

				Rbdb_SettingsController*					environment_settings_controller;
				Rbdb_LockSettingsController*				settings_controller;
				Rbdb_LockSettingsController*				environment_level_settings_controller;
			};

				/****************************
				*	Data Type Definitions	*
				****************************/

				struct Rbdb_DatabaseJoinCursor	{

					//	Parent
					Rbdb_DatabaseJoinController*						parent_join_controller;

					db_recno_t										runtime_identifier;

					char*										name;

					//	Variables
					Rbdb_Database*								primary_database;

					Rbdb_DatabaseCursor**						cursor_list;
					
					BOOL										is_open;
					
					//	Wrapped BDB database_cursor
					DBC*										wrapped_bdb_join_cursor;
					DBC**										wrapped_bdb_cursor_list;

					Rbdb_SettingsController*					environment_settings_controller;
					Rbdb_DatabaseJoinSettingsController*				settings_controller;
					Rbdb_DatabaseJoinSettingsController*				environment_level_settings_controller;
				};
			
			/****************************
			*	Data Type Definitions	*
			****************************/

			struct Rbdb_DatabaseJoinController	{

				//	Parent
				Rbdb_Database*										parent_database;

				Rbdb_Database*	runtime_storage_database;

				Rbdb_SettingsController*							environment_settings_controller;
				Rbdb_DatabaseJoinSettingsController*						settings_controller;
				Rbdb_DatabaseJoinSettingsController*						environment_level_settings_controller;
			};

	
						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseCursor	{
							
							//	Parent
							Rbdb_DatabaseCursorController*				parent_database_cursor_controller;

							db_recno_t										runtime_identifier;
							
							uint32_t								slice_length;
							
							char*										name;
							
							//	Wrapped bdb database_cursor
							DBC*										wrapped_bdb_cursor;
							
							BOOL										is_open;
							
							BOOL										iteration_started;
							int											duplicate_iteration_started;
							
							Rbdb_SettingsController*							environment_settings_controller;
							Rbdb_DatabaseCursorSettingsController*				settings_controller;
							Rbdb_DatabaseCursorSettingsController*				environment_level_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseCursorController	{

						//	Parent
						Rbdb_Database*								parent_database;

						Rbdb_Database*	runtime_storage_database;
	
						int											auto_name_count;
						
						Rbdb_SettingsController*							environment_settings_controller;
						Rbdb_DatabaseCursorSettingsController*				settings_controller;
						Rbdb_DatabaseCursorSettingsController*				environment_level_settings_controller;
					};

						/****************************
						 *	Data Type Definitions	*
						 ****************************/

						struct Rbdb_DatabaseSequence	{

							//	Parent
							Rbdb_DatabaseSequenceController*				parent_database_sequence_controller;

							db_recno_t										runtime_identifier;

							BOOL															is_open;

							Rbdb_Database*										parent_storage_database;
							Rbdb_Key*													storage_key;

							//	Wrapped BDB sequence
							DB_SEQUENCE*									wrapped_bdb_sequence;

							Rbdb_SettingsController*								environment_settings_controller;
							Rbdb_DatabaseSequenceSettingsController*				settings_controller;
							Rbdb_DatabaseSequenceSettingsController*				environment_level_settings_controller;
						};

					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_DatabaseSequenceController	{

						//	Parent
						Rbdb_Database*									parent_database;

						Rbdb_Database*									runtime_storage_database;

						Rbdb_Database*									sequence_storage_database;
	
						Rbdb_SettingsController*								environment_settings_controller;
						Rbdb_DatabaseSequenceSettingsController*				settings_controller;
						Rbdb_DatabaseSequenceSettingsController*				environment_level_settings_controller;
					};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct Rbdb_DBT	{

							//	Parent
							Rbdb_Record*																	parent_record;

							Rbdb_DatabaseRecordStorageType								type;

							uint32_t*																			size;
							uint32_t*																			buffer_size;
							uint32_t*																			partial_data_size;
							uint32_t*																			partial_data_offset;
							void*																					raw_data;

							struct timeval																creation_stamp;
							struct timeval																modification_stamp;

							//	Wrapped BDB DBT
							DBT*																					wrapped_bdb_dbt;

							Rbdb_SettingsController*											environment_settings_controller;
							Rbdb_DatabaseRecordSettingsController*				settings_controller;
							Rbdb_DatabaseRecordSettingsController*				environment_level_settings_controller;
						};

						/****************************
						*	Data Type Definitions	*
						****************************/

						struct Rbdb_SecondaryKeys	{

							Rbdb_Record*											parent_record;
							uint32_t												key_count;
							Rbdb_Key**												key_pointers_array;

							//	Wrapped BDB DBT
							DBT*													wrapped_bdb_dbt;							
						};
						
					/****************************
					 *	Data Type Definitions	*
					 ****************************/

					struct Rbdb_Record	{
	
						//	Parent
						Rbdb_Database*											parent_database;
	
						db_recno_t													runtime_identifier;

						//	Variables
						Rbdb_Key*														key;
						Rbdb_Key*														primary_key;
						Rbdb_SecondaryKeys*									secondary_keys;	
						Rbdb_Data*													data;
	
						BOOL																result;
	
						BOOL																exists_in_database;
						BOOL																requires_update_to_database;
	
						BOOL																has_footer;
						
						Rbdb_DatabaseRecordSettingsController*				settings_controller;
					};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_Database	{

					//	Parent
					Rbdb_DatabaseController*						parent_database_controller;

					db_recno_t										runtime_identifier;

					//	Variables
					char*											filename;
					char*											name;
					DBTYPE											type;
					
					Rbdb_Database*	runtime_storage_database;
					
					BOOL											is_secondary;
					Rbdb_Database*									secondary_database;
					Rbdb_Database*									primary_database;
					char*											index_name;
					BOOL											is_open;
					BOOL											opened_in_transaction;
					BOOL											has_associated;
					
					BOOL											verification_file_is_open;
					FILE*											verification_file;
					char*											verification_file_path;
					
					//	Controllers
					Rbdb_DatabaseCursorController*					cursor_controller;
					Rbdb_DatabaseJoinController*					join_controller;
					Rbdb_DatabaseSequenceController*				sequence_controller;
					//	Callback Public Methods
					Rbdb_SecondaryKeyCallbackMethod					secondary_key_creation_callback_method;

					Rbdb_Environment*								default_environment;

					//	The wrapped BDB database
					DB*												wrapped_bdb_database;

					Rbdb_SettingsController*						environment_settings_controller;
					Rbdb_DatabaseSettingsController*				settings_controller;
					Rbdb_DatabaseSettingsController*				environment_level_settings_controller;
				};

			/****************************
			 *	Data Type Definitions	*
			 ****************************/

			struct Rbdb_DatabaseController	{
	
				//	Parent
				Rbdb_Environment*								parent_environment;
	
				db_recno_t											record_number;

				Rbdb_Database*	runtime_storage_database;
	
				Rbdb_SettingsController*						environment_settings_controller;
				Rbdb_DatabaseSettingsController*				settings_controller;
				Rbdb_DatabaseSettingsController*				environment_level_settings_controller;
			};

				/****************************
				 *	Data Type Definitions	*
				 ****************************/

				struct Rbdb_Error	{

					//	Parent
					Rbdb_ErrorController*						parent_error_controller;

					int											number;
					char*										function;
					char*										message;

					Rbdb_SettingsController*					environment_settings_controller;
					Rbdb_ErrorSettingsController*				settings_controller;
					Rbdb_ErrorSettingsController*				environment_level_settings_controller;
				};

			/****************************
			 *	Data Type Definitions	*
			 ****************************/

			struct Rbdb_ErrorController	{
	
				//	Parent
				Rbdb_Environment*								parent_environment;
	
				//	Variables
				Rbdb_Error*							error_stack;
	
				Rbdb_SettingsController*				environment_settings_controller;
				Rbdb_ErrorSettingsController*				settings_controller;
				Rbdb_ErrorSettingsController*				environment_level_settings_controller;
			};

		/************************
		*	Class Descriptors	*
		************************/

		struct Rbdb_Environment	{

			//	Variables
			char*									directory;
			char*									name;
			//	FIX - wtf is this a char*?
			char*									create_directory;
			BOOL									is_open;
			
			//	Controllers
			Rbdb_ErrorController*					error_controller;
			Rbdb_DatabaseController*				database_controller;
			Rbdb_LockController*					lock_controller;
			Rbdb_LogController*					log_controller;
			Rbdb_MemoryPoolController*				memory_pool_controller;
			Rbdb_MutexController*					mutex_controller;
			Rbdb_ReplicationController*			replication_controller;
	//		Rbdb_StatusController*					status_controller;
			Rbdb_TransactionController*			transaction_controller;
			Rbdb_SettingsController*				settings_controller;
			Rbdb_SettingsController*				environment_level_settings_controller;
			//	The wrapped BDB environment
			DB_ENV*									wrapped_bdb_environment;

		};

struct Rbdb_Directory {
	
	char*				path;
	Rbdb_Directory*	next;
	
};

struct Rbdb_DatabaseOpenedDuringTransaction	{
	
	Rbdb_Database*								database;
	Rbdb_DatabaseOpenedDuringTransaction*		next;
	
};

#endif