cmake_minimum_required(VERSION 3.0)
project(QHangman)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to create code from Qt designer ui files
set(CMAKE_AUTOUIC ON)

option(ENABLE_OFFENSIVE "Enable offensive messages" OFF)
if(ENABLE_OFFENSIVE)
	message(STATUS "Enabled offensive messages")
	add_definitions(-DENABLE_OFFENSIVE)
endif()

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

qt5_add_resources(qhangman_RES src/resources/hangman.qrc)

set(qhangman_SRC
	src/main.cpp
	src/qhangman.cpp
	#src/word.cpp
)

# Tell CMake to create the helloworld executable
add_executable(qhangman ${PLATFORM_TARGET} ${qhangman_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(qhangman Qt5::Widgets)

# Install the executable
install(TARGETS qhangman DESTINATION bin)
