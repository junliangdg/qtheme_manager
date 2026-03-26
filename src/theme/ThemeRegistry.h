#pragma once

#include <QString>
#include <QStringList>
#include <QMap>

/**
 * @brief ThemeRegistry - Stores metadata about available themes.
 *
 * Provides structured information about each theme beyond just the QSS content,
 * such as display name, description, color palette, and category.
 *
 * This is optional but useful for building theme picker UIs.
 */
struct ThemeInfo
{
    QString key;          ///< Internal key, e.g. "dark_pro"
    QString displayName;  ///< Human-readable name, e.g. "Dark Pro"
    QString description;  ///< Short description
    QString category;     ///< e.g. "dark", "light", "special"
    QString primaryColor; ///< Hex color string, e.g. "#4A90D9"
    QString bgColor;      ///< Background color hint
    QString textColor;    ///< Primary text color hint
};

class ThemeRegistry
{
public:
    static ThemeRegistry& instance();

    /**
     * @brief Register metadata for a theme.
     */
    void registerInfo(const ThemeInfo& info);

    /**
     * @brief Get metadata for a theme by key.
     * @return ThemeInfo (empty if not found)
     */
    ThemeInfo info(const QString& key) const;

    /**
     * @brief Returns all registered theme keys.
     */
    QStringList keys() const;

    /**
     * @brief Returns all registered ThemeInfo entries.
     */
    QList<ThemeInfo> allThemes() const;

    /**
     * @brief Returns themes filtered by category.
     */
    QList<ThemeInfo> byCategory(const QString& category) const;

    /**
     * @brief Populate the registry with the built-in themes.
     *        Call this once at startup.
     */
    static void registerBuiltinThemes();

private:
    ThemeRegistry() = default;
    ThemeRegistry(const ThemeRegistry&) = delete;
    ThemeRegistry& operator=(const ThemeRegistry&) = delete;

    QMap<QString, ThemeInfo> m_registry;
};
