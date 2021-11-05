cmake_minimum_required(VERSION 3.10.7)

project(BattlefieldH3Engine)

set(SRCS 
	BattlefieldH3/BattlefieldH3.cpp
	BattlefieldH3/AnimationComponent.cpp
	BattlefieldH3/Game.cpp
	BattlefieldH3/Battlefiled.cpp
	BattlefieldH3/BattleHandler.cpp
	BattlefieldH3/BattlePathFinder.cpp
	BattlefieldH3/BattleUnit.cpp
	BattlefieldH3/Button.cpp
	BattlefieldH3/GameConstants.cpp
	BattlefieldH3/Graphics.cpp
	BattlefieldH3/GuiHandler.cpp
	BattlefieldH3/Garrnison.cpp
	BattlefieldH3/InterfaceElem.cpp
	BattlefieldH3/Monser.cpp
	BattlefieldH3/pch.cpp
	BattlefieldH3/SelectionWindow.cpp
	BattlefieldH3/Spell.cpp
	BattlefieldH3/SpellBook.cpp
	BattlefieldH3/WindowObject.cpp
)
set(HEADERS
	BattlefieldH3/AnimationComponent.h
	BattlefieldH3/Battlefiled.h
	BattlefieldH3/BattleHandler.h
	BattlefieldH3/BattlePathFinder.h
	BattlefieldH3/BattleUnit.h
	BattlefieldH3/Game.h
	BattlefieldH3/GameConstants.h
	BattlefieldH3/Graphics.h
	BattlefieldH3/Button.h
	BattlefieldH3/GuiHandler.h
	BattlefieldH3/Garrnison.h
	BattlefieldH3/InterfaceElem.h
	BattlefieldH3/Monser.h
	BattlefieldH3/pch.h
	BattlefieldH3/SelectionWindow.h
	BattlefieldH3/Spell.h
	BattlefieldH3/SpellBook.h
	BattlefieldH3/WindowObject.h
)
set(RESOURCES
	BattlefieldH3/startMap.txt
	
	)
#target_link_libraries(${PROJECT_NAME} Extension/SFML/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/BattlefieldH3)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Extensions/SFML/lib/cmake/SFML")

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system)

