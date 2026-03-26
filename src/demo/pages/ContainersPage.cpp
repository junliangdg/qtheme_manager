#include "ContainersPage.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTabWidget>
#include <QToolBox>
#include <QStackedWidget>
#include <QFrame>
#include <QSplitter>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>

static QLabel* sectionLabel(const QString& text)
{
    QLabel* lbl = new QLabel(text);
    lbl->setStyleSheet("font-weight: 600; font-size: 12px;");
    return lbl;
}

ContainersPage::ContainersPage(QWidget* parent)
    : QWidget(parent)
{
    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget* content = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(content);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(16);

    // ── QGroupBox ────────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QGroupBox Variants");
        QHBoxLayout* hl = new QHBoxLayout(gb);
        hl->setSpacing(12);

        QGroupBox* gb1 = new QGroupBox("Standard Group");
        QVBoxLayout* vl1 = new QVBoxLayout(gb1);
        vl1->addWidget(new QLabel("Content inside group box"));
        vl1->addWidget(new QPushButton("Action"));
        hl->addWidget(gb1);

        QGroupBox* gb2 = new QGroupBox("Checkable Group");
        gb2->setCheckable(true);
        gb2->setChecked(true);
        QVBoxLayout* vl2 = new QVBoxLayout(gb2);
        vl2->addWidget(new QLabel("Enabled when checked"));
        vl2->addWidget(new QPushButton("Button"));
        hl->addWidget(gb2);

        QGroupBox* gb3 = new QGroupBox("Disabled Group");
        gb3->setEnabled(false);
        QVBoxLayout* vl3 = new QVBoxLayout(gb3);
        vl3->addWidget(new QLabel("Disabled content"));
        vl3->addWidget(new QPushButton("Disabled"));
        hl->addWidget(gb3);

        mainLayout->addWidget(gb);
    }

    // ── QTabWidget ───────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QTabWidget");
        QVBoxLayout* vl = new QVBoxLayout(gb);

        QTabWidget* tw = new QTabWidget();
        tw->setMinimumHeight(160);

        QWidget* p1 = new QWidget();
        QVBoxLayout* pl1 = new QVBoxLayout(p1);
        pl1->addWidget(new QLabel("Content of Tab 1"));
        pl1->addWidget(new QPushButton("Tab 1 Button"));
        pl1->addStretch();
        tw->addTab(p1, "Tab One");

        QWidget* p2 = new QWidget();
        QVBoxLayout* pl2 = new QVBoxLayout(p2);
        pl2->addWidget(new QLabel("Content of Tab 2"));
        pl2->addWidget(new QLabel("More content here"));
        pl2->addStretch();
        tw->addTab(p2, "Tab Two");

        QWidget* p3 = new QWidget();
        QVBoxLayout* pl3 = new QVBoxLayout(p3);
        pl3->addWidget(new QLabel("Content of Tab 3"));
        pl3->addStretch();
        tw->addTab(p3, "Tab Three");

        tw->addTab(new QWidget(), "Disabled Tab");
        tw->setTabEnabled(3, false);

        vl->addWidget(tw);
        mainLayout->addWidget(gb);
    }

    // ── QToolBox ─────────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QToolBox");
        QVBoxLayout* vl = new QVBoxLayout(gb);

        QToolBox* toolBox = new QToolBox();
        toolBox->setMaximumHeight(200);

        QWidget* tb1 = new QWidget();
        QVBoxLayout* tbl1 = new QVBoxLayout(tb1);
        tbl1->addWidget(new QLabel("General settings content"));
        tbl1->addWidget(new QPushButton("Apply"));
        toolBox->addItem(tb1, "General Settings");

        QWidget* tb2 = new QWidget();
        QVBoxLayout* tbl2 = new QVBoxLayout(tb2);
        tbl2->addWidget(new QLabel("Appearance options"));
        tbl2->addWidget(new QPushButton("Reset"));
        toolBox->addItem(tb2, "Appearance");

        QWidget* tb3 = new QWidget();
        QVBoxLayout* tbl3 = new QVBoxLayout(tb3);
        tbl3->addWidget(new QLabel("Advanced configuration"));
        toolBox->addItem(tb3, "Advanced");

        vl->addWidget(toolBox);
        mainLayout->addWidget(gb);
    }

    // ── QSplitter ────────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QSplitter");
        QVBoxLayout* vl = new QVBoxLayout(gb);

        QSplitter* splitter = new QSplitter(Qt::Horizontal);
        splitter->setMaximumHeight(140);

        QListWidget* leftList = new QListWidget();
        leftList->addItems({"Item 1", "Item 2", "Item 3", "Item 4", "Item 5"});
        leftList->setCurrentRow(0);
        splitter->addWidget(leftList);

        QTextEdit* rightText = new QTextEdit();
        rightText->setPlainText("Right panel content.\n\nDrag the splitter handle to resize panels.");
        splitter->addWidget(rightText);

        splitter->setSizes({200, 400});
        vl->addWidget(splitter);
        mainLayout->addWidget(gb);
    }

    // ── QFrame ───────────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QFrame Shapes");
        QHBoxLayout* hl = new QHBoxLayout(gb);
        hl->setSpacing(16);

        auto makeFrame = [](QFrame::Shape shape, QFrame::Shadow shadow, const QString& label) -> QWidget* {
            QWidget* w = new QWidget();
            QVBoxLayout* vl = new QVBoxLayout(w);
            QFrame* f = new QFrame();
            f->setFrameShape(shape);
            f->setFrameShadow(shadow);
            f->setFixedSize(80, 60);
            vl->addWidget(f, 0, Qt::AlignCenter);
            QLabel* lbl = new QLabel(label);
            lbl->setAlignment(Qt::AlignCenter);
            lbl->setStyleSheet("font-size: 11px;");
            vl->addWidget(lbl);
            return w;
        };

        hl->addWidget(makeFrame(QFrame::Box,     QFrame::Plain,  "Box Plain"));
        hl->addWidget(makeFrame(QFrame::Box,     QFrame::Raised, "Box Raised"));
        hl->addWidget(makeFrame(QFrame::Box,     QFrame::Sunken, "Box Sunken"));
        hl->addWidget(makeFrame(QFrame::Panel,   QFrame::Raised, "Panel Raised"));
        hl->addWidget(makeFrame(QFrame::StyledPanel, QFrame::Sunken, "Styled Sunken"));
        hl->addStretch();

        mainLayout->addWidget(gb);
    }

    // ── QScrollArea ──────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QScrollArea");
        QVBoxLayout* vl = new QVBoxLayout(gb);

        QScrollArea* sa = new QScrollArea();
        sa->setMaximumHeight(120);
        sa->setWidgetResizable(true);

        QWidget* saContent = new QWidget();
        QVBoxLayout* saLayout = new QVBoxLayout(saContent);
        for (int i = 1; i <= 12; ++i) {
            saLayout->addWidget(new QLabel(QString("Scrollable item #%1 — long content to trigger scroll").arg(i)));
        }
        sa->setWidget(saContent);
        vl->addWidget(sa);
        mainLayout->addWidget(gb);
    }

    mainLayout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scroll);
}
