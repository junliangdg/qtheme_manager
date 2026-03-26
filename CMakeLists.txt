cmake_minimum_required(VERSION 3.16)

project(QThemeManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ─── Options ──────────────────────────────────────────────────────────────────
# Set to OFF when this project is used as a Git submodule and you only want
# the QThemeLib shared library without building the demo application.
option(QTHEME_BUILD_DEMO "Build the QThemeDemo application" ON)

# ─── Qt detection ─────────────────────────────────────────────────────────────
find_package(Qt6 QUIET COMPONENTS Core Widgets)
if(Qt6_FOUND)
    message(STATUS "Using Qt6")
    set(QT_VERSION_MAJOR 6)
    set(QT_LIBS Qt6::Core Qt6::Widgets)
else()
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
    message(STATUS "Using Qt5")
    set(QT_VERSION_MAJOR 5)
    set(QT_LIBS Qt5::Core Qt5::Widgets)
endif()

# ─── QThemeLib — shared library (DLL / .so / .dylib) ─────────────────────────
set(THEME_SOURCES
    src/theme/ThemeManager.cpp
    src/theme/ThemeRegistry.cpp
)

set(THEME_HEADERS
    src/theme/qthemelib_global.h
    src/theme/ThemeManager.h
    src/theme/ThemeRegistry.h
)

set(THEME_RESOURCES
    src/theme/qthemelib_resources.qrc
)

add_library(QThemeLib SHARED
    ${THEME_SOURCES}
    ${THEME_HEADERS}
    ${THEME_RESOURCES}
)

# Tell the compiler we are building the DLL (enables Q_DECL_EXPORT)
target_compile_definitions(QThemeLib PRIVATE QTHEMELIB_LIBRARY)

target_include_directories(QThemeLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/theme>
    $<INSTALL_INTERFACE:include/qthemelib>
)

target_link_libraries(QThemeLib PUBLIC ${QT_LIBS})

# On Windows, place the import library (.lib) alongside the DLL
set_target_properties(QThemeLib PROPERTIES
    VERSION   ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# ─── Demo Application (optional) ──────────────────────────────────────────────
if(QTHEME_BUILD_DEMO)
    set(DEMO_SOURCES
        src/demo/main.cpp
        src/demo/MainWindow.cpp
        src/demo/pages/ButtonsPage.cpp
        src/demo/pages/InputsPage.cpp
        src/demo/pages/ViewsPage.cpp
        src/demo/pages/ContainersPage.cpp
        src/demo/pages/NavigationPage.cpp
        src/demo/pages/FeedbackPage.cpp
    )

    set(DEMO_HEADERS
        src/demo/MainWindow.h
        src/demo/pages/ButtonsPage.h
        src/demo/pages/InputsPage.h
        src/demo/pages/ViewsPage.h
        src/demo/pages/ContainersPage.h
        src/demo/pages/NavigationPage.h
        src/demo/pages/FeedbackPage.h
    )

    add_executable(QThemeDemo
        ${DEMO_SOURCES}
        ${DEMO_HEADERS}
    )

    target_include_directories(QThemeDemo PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/demo
        ${CMAKE_CURRENT_SOURCE_DIR}/src/theme
    )

    # Link against the shared library — QTHEMELIB_EXPORT becomes Q_DECL_IMPORT
    target_link_libraries(QThemeDemo PRIVATE QThemeLib)

    # Qt6 specific settings
    if(Qt6_FOUND)
        qt_standard_project_setup()
    endif()

    # Windows: hide console window in release builds
    if(WIN32)
        set_target_properties(QThemeDemo PROPERTIES
            WIN32_EXECUTABLE $<CONFIG:Release>
        )
    endif()

    # Windows: copy QThemeLib.dll next to the demo executable after each build
    if(WIN32)
        add_custom_command(TARGET QThemeDemo POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:QThemeLib>
                $<TARGET_FILE_DIR:QThemeDemo>
            COMMENT "Copying QThemeLib.dll to demo output directory"
        )
    endif()

    message(STATUS "QThemeDemo will be built")
else()
    message(STATUS "QThemeDemo skipped (QTHEME_BUILD_DEMO=OFF)")
endif()

# ─── Install rules (optional, useful when consumed via find_package) ──────────
include(GNUInstallDirs)

install(TARGETS QThemeLib
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}   # .dll on Windows
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}   # .so / .dylib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}   # .lib import lib on Windows
)

install(FILES ${THEME_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qthemelib
)
