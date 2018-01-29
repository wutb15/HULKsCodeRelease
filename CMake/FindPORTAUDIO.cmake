# Find portaudio
# 
# This module defines
# PORTAUDIO_INCLUDE_DIR
# PORTAUDIO_LIBRARIES
# PORTAUDIO_FOUND

find_path(PORTAUDIO_INCLUDE_DIR NAMES portaudio.h HINTS /usr/include $ENV{PORTAUDIO_HOME}/include)
find_library(PORTAUDIO_LIBRARY NAMES portaudio HINTS /lib /usr/lib $ENV{PORTAUDIO_HOME}/lib)

set(PORTAUDIO_INCLUDE_DIRS ${PORTAUDIO_INCLUDE_DIR})
set(PORTAUDIO_LIBRARIES ${PORTAUDIO_LIBRARY})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PORTAUDIO DEFAULT_MSG PORTAUDIO_LIBRARY PORTAUDIO_INCLUDE_DIR)

mark_as_advanced(PORTAUDIO_INCLUDE_DIR PORTAUDIO_LIBRARY)