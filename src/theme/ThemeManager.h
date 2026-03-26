#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QApplication>

/**
 * @brief ThemeManager - Singleton for managing and applying QSS themes.
 *
 * Usage:
 *   ThemeManager::instance().loadThemesFromDir(":/themes");
 *   ThemeManager::instance().applyTheme(qApp, "dark_pro");
 *
 * Integration in other projects:
 *   1. Add ThemeManager.h/cpp + ThemeRegistry.h/cpp to your project.
 *   2. Copy the themes/ directory (or embed via .qrc).
 *   3. Call ThemeManager::instance().initialize(...) at startup.
 */
class ThemeManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Returns the singleton instance.
     */
    static ThemeManager& instance();

    /**
     * @brief Initialize with a directory containing .qss files.
     *        Each .qss filename (without extension) becomes a theme name.
     * @param themesDir  Path to directory, e.g. ":/themes" or "./themes"
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
     * @brief Load all .qss files from a directory and register them.
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
