# Find fftw
#
# This module defines
# FFTW_INCLUDE_DIRS
# FFTW_LIBRARIES
# FFTW_FOUND

find_path(FFTW_INCLUDE_DIR NAMES fftw3.h HINTS /usr/include $ENV{FFTW_HOME}/include)
find_library(FFTW_LIBRARY NAMES fftw3 HINTS /lib /usr/lib $ENV{FFTW_HOME}/lib)

set(FFTW_INCLUDE_DIRS ${FFTW_INCLUDE_DIR})
set(FFTW_LIBRARIES ${FFTW_LIBRARY})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FFTW DEFAULT_MSG FFTW_LIBRARY FFTW_INCLUDE_DIR)

mark_as_advanced(FFTW_INCLUDE_DIR FFTW_LIBRARY)
