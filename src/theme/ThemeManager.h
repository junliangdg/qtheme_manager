#pragma once

#include "qthemelib_global.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QApplication>

/**
 * @brief ThemeManager - Singleton for managing and applying QSS themes.
 *
 * Themes are embedded inside QThemeLib.dll via Qt resources (:/themes/).
 * No external .qss files are required at runtime.
 *
 * Typical usage:
 * @code
 *   // Register metadata (optional, for UI pickers)
 *   ThemeRegistry::registerBuiltinThemes();
 *
 *   // Load embedded themes (default path ":/themes" is used automatically)
 *   ThemeManager::instance().initialize();
 *
 *   // Apply a theme
 *   ThemeManager::instance().applyTheme(qApp, "dark_pro");
 * @endcode
 *
 * When used as a Git submodule, link against QThemeLib and call the two
 * lines above — no file copying needed.
 */
class QTHEMELIB_EXPORT ThemeManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Returns the singleton instance.
     */
    static ThemeManager& instance();

    /**
     * @brief Initialize from the embedded Qt resource path.
     *
     * Loads all .qss files from ":/themes" (compiled into the DLL).
     * Call this once at application startup before applying any theme.
     */
    void initialize();

    /**
     * @brief Initialize with an explicit directory or Qt resource path.
     * @param themesDir  e.g. ":/themes" (default) or an absolute filesystem path
     */
    void initialize(const QString& themesDir);

    /**
     * @brief Register a theme manually by name and QSS content.
     */
    void registerTheme(const QString& name, const QString& qss);

    /**
     * @brief Register a theme by name and path to a .qss file.
     */
    void registerThemeFile(const QString& name, const QString& filePath);

    /**
     * @brief Load all .qss files from a directory (or Qt resource path) and register them.
     */
    void loadThemesFromDir(const QString& dirPath);

    /**
     * @brief Apply a named theme to the given QApplication.
     * @return true if theme was found and applied.
     */
    bool applyTheme(QApplication* app, const QString& themeName);

    /**
     * @brief Apply the current theme again (useful after dynamic widget creation).
     */
    void reapplyCurrentTheme(QApplication* app);

    /**
     * @brief Returns the list of registered theme names.
     */
    QStringList availableThemes() const;

    /**
     * @brief Returns the currently active theme name.
     */
    QString currentTheme() const;

    /**
     * @brief Returns the QSS string for a given theme name.
     */
    QString themeQss(const QString& themeName) const;

    /**
     * @brief Returns a human-readable display name for a theme key.
     *        e.g. "dark_pro" -> "Dark Pro"
     */
    static QString displayName(const QString& themeKey);

signals:
    /**
     * @brief Emitted after a theme has been successfully applied.
     */
    void themeChanged(const QString& themeName);

private:
    ThemeManager();
    ~ThemeManager() = default;
    ThemeManager(const ThemeManager&) = delete;
    ThemeManager& operator=(const ThemeManager&) = delete;

    QString loadQssFile(const QString& filePath) const;

    QMap<QString, QString> m_themes;   // name -> QSS content
    QString                m_current;
};
