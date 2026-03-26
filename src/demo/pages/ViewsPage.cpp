#include "ViewsPage.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QCalendarWidget>
#include <QFrame>

static QLabel* sectionLabel(const QString& text)
{
    QLabel* lbl = new QLabel(text);
    lbl->setStyleSheet("font-weight: 600; font-size: 12px;");
    return lbl;
}

ViewsPage::ViewsPage(QWidget* parent)
    : QWidget(parent)
{
    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget* content = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(content);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(16);

    // ── QListWidget ──────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QListWidget");
        QHBoxLayout* hl = new QHBoxLayout(gb);
        hl->setSpacing(12);

        // Normal list
        QVBoxLayout* vl1 = new QVBoxLayout();
        vl1->addWidget(sectionLabel("Normal (multi-select):"));
        QListWidget* lw1 = new QListWidget();
        lw1->setSelectionMode(QAbstractItemView::ExtendedSelection);
        lw1->setAlternatingRowColors(true);
        const QStringList items = {
            "Dashboard", "Analytics", "Reports", "Users",
            "Settings", "Notifications", "Billing", "Support"
        };
        for (const QString& s : items) lw1->addItem(s);
        lw1->setCurrentRow(2);
        lw1->setMinimumHeight(160);
        vl1->addWidget(lw1);
        hl->addLayout(vl1);

        // Disabled list
        QVBoxLayout* vl2 = new QVBoxLayout();
        vl2->addWidget(sectionLabel("Disabled:"));
        QListWidget* lw2 = new QListWidget();
        lw2->addItems({"Item A", "Item B", "Item C"});
        lw2->setEnabled(false);
        lw2->setMaximumHeight(180);
        vl2->addWidget(lw2);
        hl->addLayout(vl2);

        mainLayout->addWidget(gb);
    }

    // ── QTreeWidget ──────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QTreeWidget");
        QVBoxLayout* vl = new QVBoxLayout(gb);

        QTreeWidget* tw = new QTreeWidget();
        tw->setHeaderLabels({"Name", "Type", "Size"});
        tw->setAlternatingRowColors(true);
        tw->setMinimumHeight(200);
        tw->header()->setStretchLastSection(true);

        // Root items
        QTreeWidgetItem* src = new QTreeWidgetItem(tw, {"src/", "Directory", ""});
        QTreeWidgetItem* theme = new QTreeWidgetItem(src, {"theme/", "Directory", ""});
        new QTreeWidgetItem(theme, {"ThemeManager.h", "Header", "4.2 KB"});
        new QTreeWidgetItem(theme, {"ThemeManager.cpp", "Source", "8.1 KB"});
        new QTreeWidgetItem(theme, {"ThemeRegistry.h", "Header", "2.0 KB"});
        QTreeWidgetItem* themes = new QTreeWidgetItem(theme, {"themes/", "Directory", ""});
        new QTreeWidgetItem(themes, {"dark_pro.qss", "QSS", "12.4 KB"});
        new QTreeWidgetItem(themes, {"light_minimal.qss", "QSS", "11.8 KB"});

        QTreeWidgetItem* demo = new QTreeWidgetItem(src, {"demo/", "Directory", ""});
        new QTreeWidgetItem(demo, {"main.cpp", "Source", "1.2 KB"});
        new QTreeWidgetItem(demo, {"MainWindow.cpp", "Source", "5.6 KB"});

        new QTreeWidgetItem(tw, {"CMakeLists.txt", "CMake", "2.1 KB"});
        new QTreeWidgetItem(tw, {"README.md", "Markdown", "6.8 KB"});

        tw->expandAll();
        tw->resizeColumnToContents(0);
        tw->resizeColumnToContents(1);

        vl->addWidget(tw);
        mainLayout->addWidget(gb);
    }

    // ── QTableWidget ─────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QTableWidget");
        QVBoxLayout* vl = new QVBoxLayout(gb);

        QTableWidget* table = new QTableWidget(8, 5);
        table->setHorizontalHeaderLabels({"ID", "Name", "Status", "Score", "Updated"});
        table->setAlternatingRowColors(true);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setMinimumHeight(260);
        table->horizontalHeader()->setStretchLastSection(true);
        table->verticalHeader()->setDefaultSectionSize(28);

        const QStringList names = {
            "Alice Johnson", "Bob Smith", "Carol White", "David Brown",
            "Eve Davis", "Frank Miller", "Grace Wilson", "Henry Moore"
        };
        const QStringList statuses = {
            "Active", "Inactive", "Active", "Pending",
            "Active", "Disabled", "Active", "Pending"
        };
        const QList<int> scores = {95, 72, 88, 61, 99, 45, 83, 70};

        for (int r = 0; r < 8; ++r) {
            table->setItem(r, 0, new QTableWidgetItem(QString::number(1000 + r)));
            table->setItem(r, 1, new QTableWidgetItem(names[r]));
            table->setItem(r, 2, new QTableWidgetItem(statuses[r]));
            table->setItem(r, 3, new QTableWidgetItem(QString::number(scores[r])));
            table->setItem(r, 4, new QTableWidgetItem("2026-03-" + QString::number(10 + r)));
        }

        // Pre-select row 2
        table->selectRow(2);

        vl->addWidget(table);
        mainLayout->addWidget(gb);
    }

    // ── QCalendarWidget ──────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QCalendarWidget");
        QHBoxLayout* hl = new QHBoxLayout(gb);

        QCalendarWidget* cal = new QCalendarWidget();
        cal->setGridVisible(true);
        cal->setMaximumWidth(340);
        hl->addWidget(cal);
        hl->addStretch();

        mainLayout->addWidget(gb);
    }

    mainLayout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scroll);
}
