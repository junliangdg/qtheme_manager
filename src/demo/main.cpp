#include <QApplication>

#include "ThemeManager.h"
#include "ThemeRegistry.h"
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    // High-DPI support (Qt5 only — Qt6 enables this by default)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QApplication app(argc, argv);
    app.setApplicationName("QThemeDemo");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("QThemeManager");

    // ── Register theme metadata (ThemeRegistry) ──────────────
    // Provides display names, descriptions, and color hints for the UI picker.
    ThemeRegistry::registerBuiltinThemes();

    // ── Load embedded themes from QThemeLib.dll ───────────────
    // All .qss files are compiled into the DLL as Qt resources (:/themes/).
    // No external files or post-build copies are needed.
    ThemeManager::instance().initialize();

    // ── Apply default theme ──────────────────────────────────
    ThemeManager::instance().applyTheme(&app, "dark_pro");

    // ── Launch main window ───────────────────────────────────
    MainWindow window;
    window.show();

    return app.exec();
}
