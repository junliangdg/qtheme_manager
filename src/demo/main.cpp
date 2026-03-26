#include <QApplication>
#include <QDir>

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

    // ── Locate themes directory ──────────────────────────────
    // Search order:
    //   1. Executable directory/themes  (deployed / CMake post-build copy)
    //   2. Walk up from exe to find src/theme/themes  (development build)
    QString themesPath;

    const QString exeDir = QCoreApplication::applicationDirPath();
    if (QDir(exeDir + "/themes").exists()) {
        themesPath = exeDir + "/themes";
    } else {
        QDir d(exeDir);
        for (int i = 0; i < 6; ++i) {
            if (QDir(d.absolutePath() + "/src/theme/themes").exists()) {
                themesPath = d.absolutePath() + "/src/theme/themes";
                break;
            }
            d.cdUp();
        }
    }

    if (themesPath.isEmpty()) {
        qWarning("Could not locate themes directory. Themes will not load.");
    }

    // ── Register theme metadata (ThemeRegistry) ──────────────
    ThemeRegistry::registerBuiltinThemes();

    // ── Load .qss files into ThemeManager ────────────────────
    ThemeManager& tm = ThemeManager::instance();
    if (!themesPath.isEmpty()) {
        tm.initialize(themesPath);   // scans dir, registers all .qss files
    }

    // ── Apply default theme ──────────────────────────────────
    tm.applyTheme(&app, "dark_pro");

    // ── Launch main window ───────────────────────────────────
    MainWindow window;
    window.show();

    return app.exec();
}
