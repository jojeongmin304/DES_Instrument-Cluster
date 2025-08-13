# Define the target system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Define the sysroot path (where the Pi's libraries and headers are)
# IMPORTANT: Use an absolute path here to avoid issues.
set(CMAKE_SYSROOT $ENV{HOME}/rpi-sysroot)

# Specify the compilers.
# Since the host and target architecture are the same, we can use the host's native compilers.
# While CMake might find these automatically, being explicit is good practice.
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# This is the most critical part:
# Force CMake to find libraries, headers, and packages ONLY inside the sysroot.
# This prevents it from accidentally linking against your host system's libraries.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)