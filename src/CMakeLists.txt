cmake_minimum_required(VERSION 3.10)

# Warning: This skips critical compiler checks. Only use this if Watcom fails CMake's detection
# Necessary to suppress compiler checks for cross compilation using OW2 and C under ARM environments
set(CMAKE_C_COMPILER_WORKS 1)

project(
    DbC
    VERSION 0.1.0
    LANGUAGES C
)

# Toolchain setup
set(CMAKE_SYSTEM_NAME DOS)      # Target DOS
set(CMAKE_C_COMPILER wcl)
set(CMAKE_CXX_COMPILER wcl)
set(CMAKE_LINKER wlink)         # Use Watcom's linker
set(CMAKE_EXECUTABLE_SUFFIX ".exe")

# watcom compiler options
# https://users.pja.edu.pl/~jms/qnx/help/watcom/compiler-tools/cpopts.html
if(WATCOM)
add_compile_options(
    -0                  # Generate 8086/8088 instructions ONLY (no 286+)
    -e1                 # Minimal stack checking (saves bytes for 64KB segments)
    -za99               # undocumented switch enable partial C99 compatibility
    -ml                 # memory model options - large model
    -bt=dos             # Target DOS
    -l=dos              # DOS library
    -od                 # Disable optimizations (prevents 286+ instruction sneaking in)
    -w1                 # Mild warnings (avoid /w3 due to 8086 quirks)
    -zq                 # Quiet mode (cleaner output)
    #-dNDEBUG
)
add_definitions(
    -D__DOS__
    -D__8086__  # Explicit 8086 target
  )
endif()

# WARNING: Using GLOB for convenience. If adding new files, rerun:
#   ./cmk.sh
file(GLOB SOURCES
    CONFIGURE_DEPENDS
    *.c
    CONTRACT/.*
)

# message(Source list="${SOURCES}")

add_executable(DbC ${SOURCES})

# Optional: Install target
#install(TARGETS DbC DESTINATION bin)
