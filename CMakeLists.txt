cmake_minimum_required(VERSION 3.16)

project(QThemeManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6 first, fallback to Qt5
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

# ─── Theme Library ────────────────────────────────────────────────────────────
set(THEME_SOURCES
    src/theme/ThemeManager.cpp
    src/theme/ThemeRegistry.cpp
)

set(THEME_HEADERS
    src/theme/ThemeManager.h
    src/theme/ThemeRegistry.h
)

add_library(QThemeLib STATIC ${THEME_SOURCES} ${THEME_HEADERS})

target_include_directories(QThemeLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/theme
)

target_link_libraries(QThemeLib PUBLIC ${QT_LIBS})

# ─── Demo Application ─────────────────────────────────────────────────────────
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

set(DEMO_RESOURCES
    resources/resources.qrc
)

add_executable(QThemeDemo
    ${DEMO_SOURCES}
    ${DEMO_HEADERS}
    ${DEMO_RESOURCES}
)

target_include_directories(QThemeDemo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/demo
    ${CMAKE_CURRENT_SOURCE_DIR}/src/theme
)

target_link_libraries(QThemeDemo PRIVATE QThemeLib ${QT_LIBS})

# Qt6 specific settings
if(Qt6_FOUND)
    qt_standard_project_setup()
endif()

# Windows: hide console window in release
if(WIN32)
    set_target_properties(QThemeDemo PROPERTIES
        WIN32_EXECUTABLE $<CONFIG:Release>
    )
endif()

# Copy QSS files to build directory for development convenience
add_custom_command(TARGET QThemeDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/theme/themes
        $<TARGET_FILE_DIR:QThemeDemo>/themes
    COMMENT "Copying theme files to build directory"
)
