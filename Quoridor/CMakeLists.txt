cmake_minimum_required(VERSION 3.19)
project(Quoridor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Quoridor
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    src/game.cpp
    src/game.h
    src/gameEngine.cpp 
    src/gameEngine.h
)

target_link_libraries(Quoridor
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Quoridor
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Quoridor
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
