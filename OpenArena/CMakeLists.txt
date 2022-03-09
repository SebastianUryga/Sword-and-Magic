cmake_minimum_required(VERSION 3.0)

project(arena)

#add_compile_options(-Wall -Wextra -g)

add_compile_options(-O3 -flto -march=native)

set(SRCS 
	src/OpenArena.cpp
	src/AnimationComponent.cpp
	src/Animator.cpp
	src/Game.cpp
	src/Battlefiled.cpp
	src/BattleHandler.cpp
	src/BattlePathFinder.cpp
	src/BattleUnit.cpp
	src/Button.cpp
	src/GameConstants.cpp
	src/Graphics.cpp
	src/Graphics2.cpp
	src/GuiHandler.cpp
	src/Garrnison.cpp
	src/InterfaceElem.cpp
	src/Monster.cpp
	src/CreatureInfo.cpp
	src/Player.cpp
	src/SelectionWindow.cpp
	src/Spell.cpp
	src/SpellBook.cpp
	src/WindowObject.cpp
	src/Configuration.cpp
)
set(HEADERS
	src/AnimationComponent.h
	src/Animator.h
	src/Battlefiled.h
	src/BattleHandler.h
	src/BattlePathFinder.h
	src/BattleUnit.h
	src/Game.h
	src/GameConstants.h
	src/Graphics.h
	src/Graphics2.h
	src/Button.h
	src/GuiHandler.h
	src/Garrnison.h
	src/InterfaceElem.h
	src/Monster.h
	src/CreatureInfo.h
	src/Player.h
	src/PCH.hpp
	src/SelectionWindow.h
	src/Spell.h
	src/SpellBook.h
	src/WindowObject.h
	src/Configuration.h
)
set(RESOURCES
	res)
                       
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# If SFML is included in the project
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1 EXCLUDE_FROM_ALL)
# If SFML is installed in the system
#find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES}
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

