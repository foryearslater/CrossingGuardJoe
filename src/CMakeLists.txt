set(SOURCES
    button.cpp
    car.cpp
    game.cpp
    kid.cpp
    loadimage.cpp
    player.cpp
    application.cpp
)
add_library(CROSSING_GUARD_JOE_LIB STATIC ${SOURCES} )

target_include_directories(CROSSING_GUARD_JOE_LIB PUBLIC ${CMAKE_SOURCE_DIR}/include)