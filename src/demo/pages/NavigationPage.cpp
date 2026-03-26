#include "NavigationPage.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QToolButton>
#include <QPushButton>
#include <QFrame>
#include <QListWidget>
#include <QStackedWidget>

static QLabel* sectionLabel(const QString& text)
{
    QLabel* lbl = new QLabel(text);
    lbl->setStyleSheet("font-weight: 600; font-size: 12px;");
    return lbl;
}

NavigationPage::NavigationPage(QWidget* parent)
    : QWidget(parent)
{
    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget* content = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(content);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(16);

    // ── Embedded QMenuBar ────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QMenuBar (embedded demo)");
        QVBoxLayout* vl = new QVBoxLayout(gb);
        vl->addWidget(sectionLabel("Note: The main window's menu bar is the primary example. "
                                   "Below is a standalone embedded QMenuBar for style preview:"));

        QMenuBar* mb = new QMenuBar();
        mb->setNativeMenuBar(false); // Force Qt rendering

        QMenu* fileMenu = mb->addMenu("&File");
        fileMenu->addAction("New");
        fileMenu->addAction("Open");
        fileMenu->addSeparator();
        fileMenu->addAction("Exit");

        QMenu* editMenu = mb->addMenu("&Edit");
        editMenu->addAction("Undo");
        editMenu->addAction("Redo");
        editMenu->addSeparator();
        editMenu->addAction("Cut");
        editMenu->addAction("Copy");
        editMenu->addAction("Paste");

        QMenu* viewMenu = mb->addMenu("&View");
        QMenu* themeSubMenu = viewMenu->addMenu("Theme");
        themeSubMenu->addAction("Light Minimal");
        themeSubMenu->addAction("Dark Pro");
        themeSubMenu->addAction("Glass Futuristic");
        viewMenu->addSeparator();
        viewMenu->addAction("Full Screen");

        QMenu* helpMenu = mb->addMenu("&Help");
        helpMenu->addAction("Documentation");
        helpMenu->addAction("About");

        vl->addWidget(mb);
        mainLayout->addWidget(gb);
    }

    // ── Embedded QToolBar ────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QToolBar (embedded demo)");
        QVBoxLayout* vl = new QVBoxLayout(gb);
        vl->addWidget(sectionLabel("Standalone toolbar for style preview:"));

        QToolBar* tb = new QToolBar();
        tb->setMovable(false);

        QToolButton* newBtn = new QToolButton();
        newBtn->setText("New");
        tb->addWidget(newBtn);

        QToolButton* openBtn = new QToolButton();
        openBtn->setText("Open");
        tb->addWidget(openBtn);

        QToolButton* saveBtn = new QToolButton();
        saveBtn->setText("Save");
        tb->addWidget(saveBtn);

        tb->addSeparator();

        QToolButton* undoBtn = new QToolButton();
        undoBtn->setText("Undo");
        tb->addWidget(undoBtn);

        QToolButton* redoBtn = new QToolButton();
        redoBtn->setText("Redo");
        tb->addWidget(redoBtn);

        tb->addSeparator();

        QToolButton* checkedBtn = new QToolButton();
        checkedBtn->setText("Bold");
        checkedBtn->setCheckable(true);
        checkedBtn->setChecked(true);
        tb->addWidget(checkedBtn);

        QToolButton* disabledBtn = new QToolButton();
        disabledBtn->setText("Disabled");
        disabledBtn->setEnabled(false);
        tb->addWidget(disabledBtn);

        vl->addWidget(tb);
        mainLayout->addWidget(gb);
    }

    // ── Sidebar Navigation Pattern ───────────────────────────
    {
        QGroupBox* gb = new QGroupBox("Sidebar Navigation Pattern");
        QHBoxLayout* hl = new QHBoxLayout(gb);
        hl->setSpacing(0);

        // Sidebar
        QListWidget* sidebar = new QListWidget();
        sidebar->setFixedWidth(160);
        sidebar->setFrameShape(QFrame::NoFrame);
        sidebar->addItems({
            "Dashboard",
            "Analytics",
            "Reports",
            "Users",
            "Settings",
            "Help"
        });
        sidebar->setCurrentRow(0);

        // Content area
        QStackedWidget* stack = new QStackedWidget();
        stack->setFrameShape(QFrame::StyledPanel);

        const QStringList pages = {
            "Dashboard content area",
            "Analytics charts and graphs",
            "Reports and exports",
            "User management",
            "Application settings",
            "Help and documentation"
        };

        for (const QString& pageText : pages) {
            QWidget* page = new QWidget();
            QVBoxLayout* pl = new QVBoxLayout(page);
            pl->setContentsMargins(16, 16, 16, 16);
            QLabel* lbl = new QLabel(pageText);
            lbl->setStyleSheet("font-size: 16px; font-weight: 600;");
            pl->addWidget(lbl);
            pl->addWidget(new QLabel("Click sidebar items to navigate between pages."));
            pl->addStretch();
            stack->addWidget(page);
        }

        connect(sidebar, &QListWidget::currentRowChanged, stack, &QStackedWidget::setCurrentIndex);

        hl->addWidget(sidebar);

        // Vertical separator
        QFrame* sep = new QFrame();
        sep->setFrameShape(QFrame::VLine);
        sep->setFrameShadow(QFrame::Sunken);
        hl->addWidget(sep);

        hl->addWidget(stack, 1);

        gb->setMinimumHeight(200);
        mainLayout->addWidget(gb);
    }

    // ── QStatusBar demo ──────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QStatusBar (see main window bottom)");
        QVBoxLayout* vl = new QVBoxLayout(gb);
        vl->addWidget(new QLabel(
            "The main window's status bar at the bottom shows:\n"
            "  • Left: current status message\n"
            "  • Right: active theme name\n\n"
            "Switch themes using the toolbar combo box to see it update."
        ));
        mainLayout->addWidget(gb);
    }

    mainLayout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scroll);
}
