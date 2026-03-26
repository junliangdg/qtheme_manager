#include "MainWindow.h"

#include "ThemeManager.h"
#include "ThemeRegistry.h"

#include "pages/ButtonsPage.h"
#include "pages/InputsPage.h"
#include "pages/ViewsPage.h"
#include "pages/ContainersPage.h"
#include "pages/NavigationPage.h"
#include "pages/FeedbackPage.h"

#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QFrame>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("QTheme Manager — Modern QSS Theme Demo");
    setMinimumSize(1100, 720);
    resize(1280, 800);

    setupMenuBar();
    setupToolBar();
    setupCentralWidget();
    setupDockWidget();
    setupStatusBar();

    // Connect ThemeManager signal
    connect(&ThemeManager::instance(), &ThemeManager::themeChanged,
            this, &MainWindow::onThemeChanged);
}

// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::setupMenuBar()
{
    QMenuBar* mb = menuBar();

    // File menu
    QMenu* fileMenu = mb->addMenu("&File");
    fileMenu->addAction("&New",  [](){}, QKeySequence::New);
    fileMenu->addAction("&Open", [](){}, QKeySequence::Open);
    fileMenu->addAction("&Save", [](){}, QKeySequence::Save);
    fileMenu->addSeparator();
    QAction* quitAct = fileMenu->addAction("&Quit", qApp, &QApplication::quit, QKeySequence::Quit);
    Q_UNUSED(quitAct)

    // View menu
    QMenu* viewMenu = mb->addMenu("&View");
    viewMenu->addAction("Toggle &Dock", this, [this](){
        if (m_dockWidget) m_dockWidget->setVisible(!m_dockWidget->isVisible());
    });
    viewMenu->addSeparator();

    // Theme submenu
    QMenu* themeMenu = viewMenu->addMenu("&Theme");
    const QStringList themes = ThemeManager::instance().availableThemes();
    for (const QString& t : themes) {
        QAction* act = themeMenu->addAction(ThemeManager::displayName(t), this, [this, t](){
            ThemeManager::instance().applyTheme(qApp, t);
        });
        Q_UNUSED(act)
    }

    // Help menu
    QMenu* helpMenu = mb->addMenu("&Help");
    helpMenu->addAction("&About Qt", qApp, &QApplication::aboutQt);
    helpMenu->addAction("&About", this, [this](){
        // Simple about message via status bar
        statusBar()->showMessage("QTheme Manager v1.0 — Modern QSS Theme Library for Qt Widgets", 4000);
    });
}

// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::setupToolBar()
{
    QToolBar* tb = addToolBar("Main Toolbar");
    tb->setObjectName("mainToolBar");
    tb->setMovable(true);

    tb->addAction("New");
    tb->addAction("Open");
    tb->addAction("Save");
    tb->addSeparator();
    tb->addAction("Undo");
    tb->addAction("Redo");
    tb->addSeparator();

    // Theme selector in toolbar
    QLabel* themeLabel = new QLabel("  Theme: ");
    tb->addWidget(themeLabel);

    m_themeCombo = new QComboBox();
    m_themeCombo->setMinimumWidth(160);
    m_themeCombo->setToolTip("Switch application theme");
    populateThemeCombo();
    tb->addWidget(m_themeCombo);

    connect(m_themeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onThemeComboChanged);

    tb->addSeparator();
    tb->addAction("Settings");
    tb->addAction("Help");
}

// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::setupStatusBar()
{
    m_statusLabel = new QLabel("Ready");
    m_themeLabel  = new QLabel();

    statusBar()->addWidget(m_statusLabel, 1);
    statusBar()->addPermanentWidget(m_themeLabel);

    // Update theme label
    const QString cur = ThemeManager::instance().currentTheme();
    if (!cur.isEmpty()) {
        m_themeLabel->setText("Theme: " + ThemeManager::displayName(cur) + "  ");
    }
}

// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::setupCentralWidget()
{
    m_tabWidget = new QTabWidget();
    m_tabWidget->setDocumentMode(false);
    m_tabWidget->setTabPosition(QTabWidget::North);

    m_tabWidget->addTab(new ButtonsPage(),    "🔘 Buttons");
    m_tabWidget->addTab(new InputsPage(),     "✏️ Inputs");
    m_tabWidget->addTab(new ViewsPage(),      "📋 Views");
    m_tabWidget->addTab(new ContainersPage(), "📦 Containers");
    m_tabWidget->addTab(new NavigationPage(), "🧭 Navigation");
    m_tabWidget->addTab(new FeedbackPage(),   "📊 Feedback");

    setCentralWidget(m_tabWidget);
}

// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::setupDockWidget()
{
    m_dockWidget = new QDockWidget("Theme Info", this);
    m_dockWidget->setObjectName("themeInfoDock");
    m_dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QWidget* dockContent = new QWidget();
    QVBoxLayout* layout  = new QVBoxLayout(dockContent);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(6);

    QLabel* titleLabel = new QLabel("<b>Available Themes</b>");
    layout->addWidget(titleLabel);

    QListWidget* themeList = new QListWidget();
    themeList->setObjectName("dockThemeList");

    const QList<ThemeInfo> themes = ThemeRegistry::instance().allThemes();
    for (const ThemeInfo& info : themes) {
        themeList->addItem(info.displayName);
    }

    connect(themeList, &QListWidget::itemClicked, this, [this](QListWidgetItem* item){
        // Find key by display name
        const QList<ThemeInfo> all = ThemeRegistry::instance().allThemes();
        for (const ThemeInfo& info : all) {
            if (info.displayName == item->text()) {
                ThemeManager::instance().applyTheme(qApp, info.key);
                break;
            }
        }
    });

    layout->addWidget(themeList);

    QLabel* hintLabel = new QLabel("<small><i>Click a theme to apply it</i></small>");
    hintLabel->setWordWrap(true);
    layout->addWidget(hintLabel);
    layout->addStretch();

    m_dockWidget->setWidget(dockContent);
    addDockWidget(Qt::RightDockWidgetArea, m_dockWidget);
}

// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::populateThemeCombo()
{
    if (!m_themeCombo) return;

    m_themeCombo->blockSignals(true);
    m_themeCombo->clear();

    const QStringList keys = ThemeManager::instance().availableThemes();
    for (const QString& key : keys) {
        m_themeCombo->addItem(ThemeManager::displayName(key), key);
    }

    // Select current theme
    const QString cur = ThemeManager::instance().currentTheme();
    if (!cur.isEmpty()) {
        int idx = m_themeCombo->findData(cur);
        if (idx >= 0) m_themeCombo->setCurrentIndex(idx);
    }

    m_themeCombo->blockSignals(false);
}

// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::onThemeComboChanged(int index)
{
    const QString key = m_themeCombo->itemData(index).toString();
    if (!key.isEmpty()) {
        ThemeManager::instance().applyTheme(qApp, key);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
void MainWindow::onThemeChanged(const QString& themeName)
{
    if (m_statusLabel) {
        m_statusLabel->setText("Theme applied: " + ThemeManager::displayName(themeName));
    }
    if (m_themeLabel) {
        m_themeLabel->setText("Theme: " + ThemeManager::displayName(themeName) + "  ");
    }

    // Sync combo without triggering signal
    if (m_themeCombo) {
        m_themeCombo->blockSignals(true);
        int idx = m_themeCombo->findData(themeName);
        if (idx >= 0) m_themeCombo->setCurrentIndex(idx);
        m_themeCombo->blockSignals(false);
    }
}
