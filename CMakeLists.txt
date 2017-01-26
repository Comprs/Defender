cmake_minimum_required(VERSION 3.7)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -std=c++1z")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s -flto -Werror")
endif()
include_directories(include)
add_executable(defender
    src/abductor.cpp
    src/alien.cpp
    src/alienprojectile.cpp
    src/audio.cpp
    src/audioregistry.cpp
    src/clock.cpp
    src/defenderutils.cpp
    src/entity.cpp
    src/fighter.cpp
    src/fontregistry.cpp
    src/gamecontrollermanager.cpp
    src/game.cpp
    src/inputmanager.cpp
    src/interceptor.cpp
    src/keyboardmanager.cpp
    src/main.cpp
    src/maingameroom.cpp
    src/mainmenu.cpp
    src/man.cpp
    src/menuroom.cpp
    src/mutant.cpp
    src/particle.cpp
    src/pauseroom.cpp
    src/player.cpp
    src/playerprojectile.cpp
    src/renderer.cpp
    src/room.cpp
    src/texture.cpp
    src/textureregistry.cpp
    src/ttffont.cpp
    src/window.cpp
)
target_link_libraries(defender SDL2 SDL2_image SDL2_mixer SDL2_ttf)
install(TARGETS defender RUNTIME DESTINATION bin)
install(FILES resources/alien1.png DESTINATION bin)
install(FILES resources/alien2.png DESTINATION bin)
install(FILES resources/alien3.png DESTINATION bin)
install(FILES resources/alien4.png DESTINATION bin)
install(FILES resources/Audiowide-Regular.ttf DESTINATION bin)
install(FILES resources/background.png DESTINATION bin)
install(FILES resources/blood.png DESTINATION bin)
install(FILES resources/enemyShot.png DESTINATION bin)
install(FILES resources/explosion.png DESTINATION bin)
install(FILES resources/explosion.wav DESTINATION bin)
install(FILES resources/man.png DESTINATION bin)
install(FILES resources/player.png DESTINATION bin)
install(FILES resources/playerShard.png DESTINATION bin)
install(FILES resources/shard.png DESTINATION bin)
install(FILES resources/shot.png DESTINATION bin)
