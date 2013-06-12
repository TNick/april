# - Try to find cmd-test
# Once done this will define
#  CMDTEST_FOUND - System has cmd-test
#  CMDTEST_INCLUDE_DIRS - The cmd-test include directories
#  CMDTEST_LIBRARIES - The libraries needed to use cmd-test
#  CMDTEST_DEFINITIONS - Compiler switches required for using cmd-test

find_package(PkgConfig)
pkg_check_modules(PC_CMDTEST QUIET cmd-test)
set(CMDTEST_DEFINITIONS ${PC_CMDTEST_CFLAGS_OTHER})

find_program(CMDTEST_PROGRAM NAMES cmd-test
             HINTS ${PC_CMDTEST_LIBDIR} ${PC_CMDTEST_LIBRARY_DIRS} 
             PATHS ENV CMDTEST_BINARY )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CMDTEST_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CMDTEST  DEFAULT_MSG
                                  CMDTEST_PROGRAM)

mark_as_advanced( CMDTEST_PROGRAM )

