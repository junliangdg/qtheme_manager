#pragma once

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QTabWidget>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void onThemeChanged(const QString& themeName);
    void onThemeComboChanged(int index);

private:
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupCentralWidget();
    void setupDockWidget();
    void populateThemeCombo();

    QTabWidget*  m_tabWidget    = nullptr;
    QComboBox*   m_themeCombo   = nullptr;
    QLabel*      m_statusLabel  = nullptr;
    QLabel*      m_themeLabel   = nullptr;
    QDockWidget* m_dockWidget   = nullptr;
};
