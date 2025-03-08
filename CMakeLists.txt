cmake_minimum_required(VERSION 3.20)
project(SpaceshipGame)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Set SFML directory path (update if necessary)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

# Find the SFML package with required components
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)

# Set the output directory for the executable to be inside the 'bin' folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add your source files
add_executable(SpaceshipGame
        src/main.cpp
        src/Spaceship.h src/Spaceship.cpp
        src/Bullet.h src/Bullet.cpp
        src/Meteor.h src/Meteor.cpp
        src/Enemy.h src/Enemy.cpp
        src/Game.h src/Game.cpp
)

# Link SFML libraries to your project
target_link_libraries(SpaceshipGame sfml-graphics sfml-window sfml-system sfml-audio)
