# project name, and type
PROJECT(OpenApoc_GameUI CXX C)

# check cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

set (GAMEUI_SOURCE_FILES
	battle/battlebriefing.cpp
	battle/battledebriefing.cpp
	battle/battleprestart.cpp
	battle/battleview.cpp
	base/basegraphics.cpp
	base/basescreen.cpp
	base/basestage.cpp
	base/researchscreen.cpp
	base/researchselect.cpp
	base/vequipscreen.cpp
	base/aequipscreen.cpp
	city/basebuyscreen.cpp
	city/baseselectscreen.cpp
	city/buildingscreen.cpp
	city/infiltrationscreen.cpp
	city/scorescreen.cpp
	city/cityview.cpp
	debugtools/debugmenu.cpp
	debugtools/formpreview.cpp
	debugtools/imagepreview.cpp
	general/mapselector.cpp
	general/difficultymenu.cpp
	general/ingameoptions.cpp
	general/loadingscreen.cpp
	general/mainmenu.cpp
	general/messagebox.cpp
	general/optionsmenu.cpp
	general/savemenu.cpp
	general/videoscreen.cpp
	general/messagelogscreen.cpp
	general/notificationscreen.cpp
	tileview/battletileview.cpp
	tileview/citytileview.cpp
	tileview/tileview.cpp
	ufopaedia/ufopaediacategoryview.cpp
	ufopaedia/ufopaediaview.cpp
	boot.cpp)
source_group(gamestate\\sources FILES ${GAMEUI_SOURCE_FILES})
set (GAMEUI_HEADER_FILES
	battle/battlebriefing.h
	battle/battledebriefing.h
	battle/battleprestart.h
	battle/battleview.h
	base/basegraphics.h
	base/basescreen.h
	base/basestage.h
	base/researchscreen.h
	base/researchselect.h
	base/vequipscreen.h
	base/aequipscreen.h
	city/basebuyscreen.h
	city/baseselectscreen.h
	city/buildingscreen.h
	city/infiltrationscreen.h
	city/scorescreen.h
	city/cityview.h
	debugtools/debugmenu.h
	debugtools/formpreview.h
	debugtools/imagepreview.h
	general/mapselector.h
	general/difficultymenu.h
	general/ingameoptions.h
	general/loadingscreen.h
	general/mainmenu.h
	general/messagebox.h
	general/optionsmenu.h
	general/savemenu.h
	general/videoscreen.h
	general/messagelogscreen.h
	general/notificationscreen.h
	tileview/battletileview.h
	tileview/citytileview.h
	tileview/tileview.h
	ufopaedia/ufopaediacategoryview.h
	ufopaedia/ufopaediaview.h
	boot.h)
source_group(gamestate\\headers FILES ${GAMEUI_HEADER_FILES})

list(APPEND ALL_SOURCE_FILES ${GAMEUI_SOURCE_FILES})
list(APPEND ALL_HEADER_FILES ${GAMEUI_HEADER_FILES})

add_library(OpenApoc_GameUI STATIC ${GAMEUI_SOURCE_FILES}
		${GAMEUI_HEADER_FILES})

target_link_libraries(OpenApoc_GameUI PUBLIC OpenApoc_Library)
target_link_libraries(OpenApoc_GameUI PUBLIC OpenApoc_Framework)
target_link_libraries(OpenApoc_GameUI PUBLIC OpenApoc_GameState)
target_link_libraries(OpenApoc_GameUI PUBLIC OpenApoc_Forms)

# version.h is used in the main menu, and that's generated in the bin dir
target_include_directories(OpenApoc_GameUI PRIVATE ${CMAKE_BINARY_DIR})

set_property(TARGET OpenApoc_GameUI PROPERTY CXX_STANDARD 11)
set_property(TARGET OpenApoc_GameUI PROPERTY CXX_STANDARD_REQUIRED ON)
