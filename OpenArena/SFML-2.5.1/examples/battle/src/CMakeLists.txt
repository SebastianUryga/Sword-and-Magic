
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/battle)

set(SRC 
	${SRCROOT}/BattlefieldH3.cpp
	${SRCROOT}/AnimationComponent.cpp
	${SRCROOT}/Game.cpp
	${SRCROOT}/Battlefiled.cpp
	${SRCROOT}/BattleHandler.cpp
	${SRCROOT}/BattlePathFinder.cpp
	${SRCROOT}/BattleUnit.cpp
	${SRCROOT}/Button.cpp
	${SRCROOT}/GameConstants.cpp
	${SRCROOT}/Graphics.cpp
	${SRCROOT}/GuiHandler.cpp
	${SRCROOT}/Garrnison.cpp
	${SRCROOT}/InterfaceElem.cpp
	${SRCROOT}/Monser.cpp
	${SRCROOT}/SelectionWindow.cpp
	${SRCROOT}/Spell.cpp
	${SRCROOT}/SpellBook.cpp
	${SRCROOT}/WindowObject.cpp
    ${SRCROOT}/AnimationComponent.h
	${SRCROOT}/Battlefiled.h
	${SRCROOT}/BattleHandler.h
	${SRCROOT}/BattlePathFinder.h
	${SRCROOT}/BattleUnit.h
	${SRCROOT}/Game.h
	${SRCROOT}/GameConstants.h
	${SRCROOT}/Graphics.h
	${SRCROOT}/Button.h
	${SRCROOT}/GuiHandler.h
	${SRCROOT}/Garrnison.h
	${SRCROOT}/InterfaceElem.h
	${SRCROOT}/Monser.h
	${SRCROOT}/PCH.hpp
	${SRCROOT}/SelectionWindow.h
	${SRCROOT}/Spell.h
	${SRCROOT}/SpellBook.h
	${SRCROOT}/WindowObject.h
)

set(RESOURCES
	${SRCROOT}/res/startMap.txt
	${SRCROOT}/res/Textures
	${SRCROOT}/res/Fonts
	)

sfml_add_example(battle GUI_APP
                 SOURCES ${SRC}
                 DEPENDS sfml-audio sfml-graphics sfml-window
                 RESOURCES_DIR res)                      

