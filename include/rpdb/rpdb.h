#ifndef RPDB
	#define RPDB
	
	//	Standard includes for users of RPDB
	
	#include "RPDB_BaseStandardInclude.h"
	
	//	Types and Constants
	#include "RPDB_Types.h"
	#include "RPDB_Constants.h"

	//	Main - version info, etc.
	#include "RPDB_main.h"
	
	//	Environment
	#include "RPDB_Environment.h"
	
	//	Database
	#include "RPDB_DatabaseController.h"
		#include "RPDB_Database.h"
			#include "RPDB_DatabaseCursorController.h"
				#include "RPDB_DatabaseCursor.h"
	
	//	Error
	#include "RPDB_ErrorController.h"
		#include "RPDB_Error.h"
	
	//	Records, Data, Keys
	#include "RPDB_Record.h"
	#include "RPDB_Data.h"
	#include "RPDB_Key.h"
	
	//	Runtime Storage
	#include "RPDB_RuntimeStorageController.h"
		#include "RPDB_RuntimeStorage.h"
	
	//	Settings
	#include "RPDB_SettingsController.h"
		#include "RPDB_DatabaseSettingsController.h"
			#include "RPDB_DatabaseAssociationSettingsController.h"
			#include "RPDB_DatabaseCursorSettingsController.h"
				#include "RPDB_DatabaseCursorReadWriteSettingsController.h"
			#include "RPDB_DatabaseErrorSettingsController.h"
			#include "RPDB_DatabaseReadWriteSettingsController.h"
			#include "RPDB_DatabaseRecordSettingsController.h"
			#include "RPDB_DatabaseTypeSettingsController.h"
				#include "RPDB_DatabaseTypeBtreeSettingsController.h"
		#include "RPDB_DirectorySettingsController.h"
		#include "RPDB_ErrorSettingsController.h"
		#include "RPDB_FileSettingsController.h"
		#include "RPDB_MemoryPoolSettingsController.h"
		
#endif