#ifndef RBDB
	#define RBDB
	
	//	Standard includes for users of Rbdb
	
	#include "Rbdb_BaseStandardInclude.h"
	
	//	Types and Constants
	#include "Rbdb_Types.h"
	#include "Rbdb_Constants.h"

	//	Main - version info, etc.
	#include "Rbdb_main.h"
	
	//	Environment
	#include "Rbdb_Environment.h"
	
	//	Database
	#include "Rbdb_DatabaseController.h"
		#include "Rbdb_Database.h"
			#include "Rbdb_DatabaseCursorController.h"
				#include "Rbdb_DatabaseCursor.h"
	
	//	Error
	#include "Rbdb_ErrorController.h"
		#include "Rbdb_Error.h"
	
	//	Records, Data, Keys
	#include "Rbdb_Record.h"
	#include "Rbdb_Data.h"
	#include "Rbdb_Key.h"
	
	//	Runtime Storage
	#include "Rbdb_RuntimeStorageController.h"
		#include "Rbdb_RuntimeStorage.h"
	
	//	Settings
	#include "Rbdb_SettingsController.h"
		#include "Rbdb_DatabaseSettingsController.h"
			#include "Rbdb_DatabaseAssociationSettingsController.h"
			#include "Rbdb_DatabaseCursorSettingsController.h"
				#include "Rbdb_DatabaseCursorReadWriteSettingsController.h"
			#include "Rbdb_DatabaseErrorSettingsController.h"
			#include "Rbdb_DatabaseRecordReadWriteSettingsController.h"
			#include "Rbdb_DatabaseRecordSettingsController.h"
			#include "Rbdb_DatabaseTypeSettingsController.h"
				#include "Rbdb_DatabaseTypeBtreeSettingsController.h"
		#include "Rbdb_DirectorySettingsController.h"
		#include "Rbdb_ErrorSettingsController.h"
		#include "Rbdb_FileSettingsController.h"
		#include "Rbdb_MemoryPoolSettingsController.h"
		
#endif