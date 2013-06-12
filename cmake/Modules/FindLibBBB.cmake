# - Try to find libbbb
# Once done this will define
#  LIBBBB_FOUND - System has LibBBB
#  LIBBBB_INCLUDE_DIRS - The LibBBB include directories
#  LIBBBB_LIBRARIES - The libraries needed to use LibBBB
#  LIBBBB_DEFINITIONS - Compiler switches required for using LibBBB

find_package(PkgConfig)
pkg_check_modules(PC_LIBBBB QUIET libbbb-1.0.0)
set(LIBBBB_DEFINITIONS ${PC_LIBBBB_CFLAGS_OTHER})

find_path(LIBBBB_INCLUDE_DIR libbbb/libbbb.h
          HINTS ${PC_LIBBBB_INCLUDEDIR} ${PC_LIBBBB_INCLUDE_DIRS} 
          PATHS ENV LIBBBB_INC
          PATH_SUFFIXES libbbb )

find_library(LIBBBB_LIBRARY NAMES bbb libbbb
             HINTS ${PC_LIBBBB_LIBDIR} ${PC_LIBBBB_LIBRARY_DIRS} 
             PATHS ENV LIBBBB_BINARY )

set(LIBBBB_LIBRARIES ${LIBBBB_LIBRARY} )
set(LIBBBB_INCLUDE_DIRS ${LIBBBB_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBBBB_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LIBBBB  DEFAULT_MSG
                                  LIBBBB_LIBRARY LIBBBB_INCLUDE_DIR)

mark_as_advanced(LIBBBB_INCLUDE_DIR LIBBBB_LIBRARY )

