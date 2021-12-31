cmake_minimum_required(VERSION 3.10.7)

project(BattlefieldH3Engine)

set(SRCS 
	src/BattlefieldH3.cpp
	src/AnimationComponent.cpp
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
	src/Monser.cpp
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
	src/Monser.h
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
	res/startMap.txt
	res/config.txt
	res/Textures
	res/Fonts
	)
	
                       
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1 EXCLUDE_FROM_ALL)

find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCES}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system)

