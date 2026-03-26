#include "ThemeRegistry.h"

// ─────────────────────────────────────────────────────────────────────────────
ThemeRegistry& ThemeRegistry::instance()
{
    static ThemeRegistry s_instance;
    return s_instance;
}

// ─────────────────────────────────────────────────────────────────────────────
void ThemeRegistry::registerInfo(const ThemeInfo& info)
{
    m_registry[info.key] = info;
}

// ─────────────────────────────────────────────────────────────────────────────
ThemeInfo ThemeRegistry::info(const QString& key) const
{
    return m_registry.value(key);
}

// ─────────────────────────────────────────────────────────────────────────────
QStringList ThemeRegistry::keys() const
{
    return m_registry.keys();
}

// ─────────────────────────────────────────────────────────────────────────────
QList<ThemeInfo> ThemeRegistry::allThemes() const
{
    return m_registry.values();
}

// ─────────────────────────────────────────────────────────────────────────────
QList<ThemeInfo> ThemeRegistry::byCategory(const QString& category) const
{
    QList<ThemeInfo> result;
    for (const ThemeInfo& t : m_registry) {
        if (t.category == category) {
            result.append(t);
        }
    }
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
void ThemeRegistry::registerBuiltinThemes()
{
    ThemeRegistry& reg = instance();

    reg.registerInfo({
        "light_minimal",
        "Light Minimal",
        "Clean, airy light theme inspired by modern SaaS dashboards",
        "light",
        "#4F8EF7",
        "#F5F7FA",
        "#1A1A2E"
    });

    reg.registerInfo({
        "dark_pro",
        "Dark Pro",
        "Professional dark theme for developer tools and AI products",
        "dark",
        "#4A90D9",
        "#1E1E2E",
        "#CDD6F4"
    });

    reg.registerInfo({
        "glass_futuristic",
        "Glass Futuristic",
        "Sci-fi inspired theme with gradient accents and translucent feel",
        "special",
        "#00D4FF",
        "#0A0E1A",
        "#E0F0FF"
    });

    reg.registerInfo({
        "soft_rounded",
        "Soft Rounded",
        "Gentle, rounded design with muted tones for desktop productivity",
        "light",
        "#7C6FCD",
        "#F0EEF8",
        "#2D2B3D"
    });

    reg.registerInfo({
        "high_contrast",
        "High Contrast",
        "Maximum readability and accessibility with bold contrast",
        "special",
        "#FFFF00",
        "#000000",
        "#FFFFFF"
    });

    reg.registerInfo({
        "blue_business",
        "Blue Business",
        "Corporate blue theme suitable for enterprise applications",
        "light",
        "#0066CC",
        "#EEF4FB",
        "#1A2B4A"
    });

    reg.registerInfo({
        "green_eye",
        "Green Eye Care",
        "Low-fatigue green-tinted theme for long working sessions",
        "dark",
        "#4CAF50",
        "#1A2318",
        "#D4EDDA"
    });
}
