SET( CMAKE_VERBOSE_MAKEFILE ON )

OPTION( BUILD_SHARED_LIBS "turn OFF for .a libs" ON )

include( RecursivelyIncludeSource )

#	make sure we have libdb
find_package( BerkeleyDB REQUIRED )

get_directory_property( cmake_current_include_dir INCLUDE_DIRECTORIES )

recursively_include_src( ${cmake_current_include_dir} "headers" )
recursively_include_src( ${CMAKE_CURRENT_SOURCE_DIR} "source" )

set( rpdb_include_dirs ${DB_INCLUDE_DIRS} ${cmake_current_include_dir} ${rpdb_directories})
include_directories( ${rpdb_include_dirs} )
LINK_DIRECTORIES( "/usr/local/lib" )

message( STATUS "include dirs: ${rpdb_include_dirs}")

#	define shared library with sources
add_library( rpdb SHARED ${rpdb_src} )
target_link_libraries( rpdb db )

#add_library( rpdb_static STATIC ${rpdb_src} )
#target_link_libraries( rpdb_static ${LIBS} )

# use, i.e. don't skip the full RPATH for the build tree
set( CMAKE_SKIP_BUILD_RPATH  OFF )

# when building, don't use the install RPATH already
# (but later on when installing)
set( CMAKE_BUILD_WITH_INSTALL_RPATH ON )

set( CMAKE_INSTALL_NAME_DIR "@rpath" )

# the RPATH to be used when installing
set( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" )

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )

# Set the build version (VERSION) and the API version (SOVERSION)
set_target_properties( rpdb PROPERTIES VERSION 0.1 SOVERSION 0.1 
														LINKER_LANGUAGE C 
														LINK_FLAGS "-Wl,-rpath,-L${CMAKE_INSTALL_RPATH}"
														INSTALL_RPATH ${CMAKE_INSTALL_RPATH}
														INSTALL_NAME_DIR ${CMAKE_INSTALL_NAME_DIR} )
#set_target_properties( rpdb_static PROPERTIES VERSION 0.1.0 SOVERSION 1)

#	not sure why set is necessary vs. set_target_properties
set( INSTALL_RPATH ${CMAKE_INSTALL_RPATH})
set( INSTALL_NAME_DIR ${CMAKE_INSTALL_NAME_DIR})

# Installation of the library
install( TARGETS rpdb DESTINATION lib PERMISSIONS OWNER_READ GROUP_READ WORLD_READ )
#install( TARGETS rpdb_static DESTINATION lib PERMISSIONS OWNER_READ GROUP_READ WORLD_READ )

# Installation of the library's headers
INSTALL( FILES ${rpdb_headers} DESTINATION "include/rpdb" )
INSTALL( FILES "${cmake_current_include_dir}/../rpdb.h" DESTINATION "include" )
