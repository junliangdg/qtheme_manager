#include "ThemeManager.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

// Ensure the DLL's Qt resources (:/themes, :/icons) are registered when the
// library is loaded.  This is only needed when the library is built as a
// shared library; for static builds Qt links the resources automatically.
#if !defined(QTHEMELIB_STATIC)
static void initQThemeResources()
{
    Q_INIT_RESOURCE(qthemelib_resources);
}

namespace {
struct ResourceInitializer {
    ResourceInitializer() { initQThemeResources(); }
} s_resourceInit;
} // namespace
#endif

// ─────────────────────────────────────────────────────────────────────────────
ThemeManager::ThemeManager() = default;

ThemeManager& ThemeManager::instance()
{
    static ThemeManager s_instance;
    return s_instance;
}

// ─────────────────────────────────────────────────────────────────────────────
void ThemeManager::initialize()
{
    // Default: load themes embedded in the DLL's Qt resources
    loadThemesFromDir(QStringLiteral(":/themes"));
}

void ThemeManager::initialize(const QString& themesDir)
{
    loadThemesFromDir(themesDir);
}

// ─────────────────────────────────────────────────────────────────────────────
void ThemeManager::registerTheme(const QString& name, const QString& qss)
{
    if (name.isEmpty()) {
        qWarning() << "[ThemeManager] Cannot register theme with empty name.";
        return;
    }
    m_themes[name] = qss;
    qDebug() << "[ThemeManager] Registered theme:" << name;
}

// ─────────────────────────────────────────────────────────────────────────────
void ThemeManager::registerThemeFile(const QString& name, const QString& filePath)
{
    const QString qss = loadQssFile(filePath);
    if (qss.isEmpty()) {
        qWarning() << "[ThemeManager] Failed to load QSS file:" << filePath;
        return;
    }
    registerTheme(name, qss);
}

// ─────────────────────────────────────────────────────────────────────────────
void ThemeManager::loadThemesFromDir(const QString& dirPath)
{
    QDir dir(dirPath);
    if (!dir.exists()) {
        qWarning() << "[ThemeManager] Theme directory not found:" << dirPath;
        return;
    }

    const QStringList filters = { "*.qss" };
    const QFileInfoList files = dir.entryInfoList(filters, QDir::Files, QDir::Name);

    for (const QFileInfo& fi : files) {
        const QString name = fi.baseName();   // filename without extension
        const QString qss  = loadQssFile(fi.absoluteFilePath());
        if (!qss.isEmpty()) {
            registerTheme(name, qss);
        }
    }

    qDebug() << "[ThemeManager] Loaded" << m_themes.size() << "theme(s) from" << dirPath;
}

// ─────────────────────────────────────────────────────────────────────────────
bool ThemeManager::applyTheme(QApplication* app, const QString& themeName)
{
    if (!app) {
        qWarning() << "[ThemeManager] applyTheme: null QApplication pointer.";
        return false;
    }

    if (!m_themes.contains(themeName)) {
        qWarning() << "[ThemeManager] Theme not found:" << themeName
                   << "| Available:" << availableThemes();
        return false;
    }

    app->setStyleSheet(m_themes.value(themeName));
    m_current = themeName;
    emit themeChanged(themeName);
    qDebug() << "[ThemeManager] Applied theme:" << themeName;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
void ThemeManager::reapplyCurrentTheme(QApplication* app)
{
    if (!m_current.isEmpty()) {
        applyTheme(app, m_current);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
QStringList ThemeManager::availableThemes() const
{
    return m_themes.keys();
}

// ─────────────────────────────────────────────────────────────────────────────
QString ThemeManager::currentTheme() const
{
    return m_current;
}

// ─────────────────────────────────────────────────────────────────────────────
QString ThemeManager::themeQss(const QString& themeName) const
{
    return m_themes.value(themeName);
}

// ─────────────────────────────────────────────────────────────────────────────
QString ThemeManager::displayName(const QString& themeKey)
{
    // Convert snake_case to Title Case: "dark_pro" -> "Dark Pro"
    QString result = themeKey;
    result.replace('_', ' ');
    QStringList words = result.split(' ');
    for (QString& word : words) {
        if (!word.isEmpty()) {
            word[0] = word[0].toUpper();
        }
    }
    return words.join(' ');
}

// ─────────────────────────────────────────────────────────────────────────────
QString ThemeManager::loadQssFile(const QString& filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "[ThemeManager] Cannot open file:" << filePath;
        return {};
    }
    QTextStream stream(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    stream.setCodec("UTF-8");
#else
    stream.setEncoding(QStringConverter::Utf8);
#endif
    return stream.readAll();
}
