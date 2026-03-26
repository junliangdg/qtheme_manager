#include "ButtonsPage.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QToolButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QButtonGroup>
#include <QFrame>
#include <QMenu>

// Helper: create a section label
static QLabel* sectionLabel(const QString& text)
{
    QLabel* lbl = new QLabel(text);
    lbl->setStyleSheet("font-weight: 600; font-size: 12px; color: palette(mid);");
    return lbl;
}

// Helper: horizontal separator
static QFrame* hLine()
{
    QFrame* f = new QFrame();
    f->setFrameShape(QFrame::HLine);
    f->setFrameShadow(QFrame::Sunken);
    return f;
}

ButtonsPage::ButtonsPage(QWidget* parent)
    : QWidget(parent)
{
    // Outer scroll area
    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget* content = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(content);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(16);

    // ── QPushButton ──────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QPushButton");
        QVBoxLayout* vl = new QVBoxLayout(gb);

        vl->addWidget(sectionLabel("Standard States"));
        QHBoxLayout* row1 = new QHBoxLayout();
        row1->setSpacing(8);
        row1->addWidget(new QPushButton("Primary"));
        QPushButton* hoverHint = new QPushButton("Hover Me");
        hoverHint->setToolTip("Hover to see effect");
        row1->addWidget(hoverHint);
        QPushButton* pressBtn = new QPushButton("Press Me");
        row1->addWidget(pressBtn);
        QPushButton* disabledBtn = new QPushButton("Disabled");
        disabledBtn->setEnabled(false);
        row1->addWidget(disabledBtn);
        QPushButton* checkedBtn = new QPushButton("Checked");
        checkedBtn->setCheckable(true);
        checkedBtn->setChecked(true);
        row1->addWidget(checkedBtn);
        row1->addStretch();
        vl->addLayout(row1);

        vl->addWidget(sectionLabel("Flat / Text Buttons"));
        QHBoxLayout* row2 = new QHBoxLayout();
        row2->setSpacing(8);
        QPushButton* flatBtn = new QPushButton("Flat Button");
        flatBtn->setFlat(true);
        row2->addWidget(flatBtn);
        QPushButton* flatDisabled = new QPushButton("Flat Disabled");
        flatDisabled->setFlat(true);
        flatDisabled->setEnabled(false);
        row2->addWidget(flatDisabled);
        row2->addStretch();
        vl->addLayout(row2);

        vl->addWidget(sectionLabel("Semantic Variants (via property)"));
        QHBoxLayout* row3 = new QHBoxLayout();
        row3->setSpacing(8);
        QPushButton* secBtn = new QPushButton("Secondary");
        secBtn->setProperty("class", "secondary");
        row3->addWidget(secBtn);
        QPushButton* dangerBtn = new QPushButton("Danger");
        dangerBtn->setProperty("class", "danger");
        row3->addWidget(dangerBtn);
        QPushButton* dangerDisabled = new QPushButton("Danger Disabled");
        dangerDisabled->setProperty("class", "danger");
        dangerDisabled->setEnabled(false);
        row3->addWidget(dangerDisabled);
        row3->addStretch();
        vl->addLayout(row3);

        vl->addWidget(sectionLabel("Sizes"));
        QHBoxLayout* row4 = new QHBoxLayout();
        row4->setSpacing(8);
        QPushButton* small = new QPushButton("Small");
        small->setFixedHeight(24);
        small->setStyleSheet("font-size: 11px; padding: 2px 10px;");
        row4->addWidget(small);
        row4->addWidget(new QPushButton("Normal"));
        QPushButton* large = new QPushButton("Large");
        large->setFixedHeight(44);
        large->setStyleSheet("font-size: 15px; padding: 8px 24px;");
        row4->addWidget(large);
        row4->addStretch();
        vl->addLayout(row4);

        mainLayout->addWidget(gb);
    }

    // ── QToolButton ──────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QToolButton");
        QHBoxLayout* hl = new QHBoxLayout(gb);
        hl->setSpacing(8);

        QToolButton* tb1 = new QToolButton();
        tb1->setText("Tool");
        hl->addWidget(tb1);

        QToolButton* tb2 = new QToolButton();
        tb2->setText("Checkable");
        tb2->setCheckable(true);
        tb2->setChecked(true);
        hl->addWidget(tb2);

        QToolButton* tb3 = new QToolButton();
        tb3->setText("Disabled");
        tb3->setEnabled(false);
        hl->addWidget(tb3);

        QToolButton* tb4 = new QToolButton();
        tb4->setText("With Menu ▾");
        QMenu* tbMenu = new QMenu(tb4);
        tbMenu->addAction("Action 1");
        tbMenu->addAction("Action 2");
        tbMenu->addSeparator();
        tbMenu->addAction("Action 3");
        tb4->setMenu(tbMenu);
        tb4->setPopupMode(QToolButton::MenuButtonPopup);
        hl->addWidget(tb4);

        hl->addStretch();
        mainLayout->addWidget(gb);
    }

    // ── QCheckBox ────────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QCheckBox");
        QHBoxLayout* hl = new QHBoxLayout(gb);
        hl->setSpacing(16);

        QCheckBox* cb1 = new QCheckBox("Unchecked");
        hl->addWidget(cb1);

        QCheckBox* cb2 = new QCheckBox("Checked");
        cb2->setChecked(true);
        hl->addWidget(cb2);

        QCheckBox* cb3 = new QCheckBox("Tristate");
        cb3->setTristate(true);
        cb3->setCheckState(Qt::PartiallyChecked);
        hl->addWidget(cb3);

        QCheckBox* cb4 = new QCheckBox("Disabled Unchecked");
        cb4->setEnabled(false);
        hl->addWidget(cb4);

        QCheckBox* cb5 = new QCheckBox("Disabled Checked");
        cb5->setChecked(true);
        cb5->setEnabled(false);
        hl->addWidget(cb5);

        hl->addStretch();
        mainLayout->addWidget(gb);
    }

    // ── QRadioButton ─────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QRadioButton");
        QHBoxLayout* hl = new QHBoxLayout(gb);
        hl->setSpacing(16);

        QButtonGroup* bg = new QButtonGroup(gb);

        QRadioButton* rb1 = new QRadioButton("Option A");
        rb1->setChecked(true);
        bg->addButton(rb1);
        hl->addWidget(rb1);

        QRadioButton* rb2 = new QRadioButton("Option B");
        bg->addButton(rb2);
        hl->addWidget(rb2);

        QRadioButton* rb3 = new QRadioButton("Option C");
        bg->addButton(rb3);
        hl->addWidget(rb3);

        QRadioButton* rb4 = new QRadioButton("Disabled");
        rb4->setEnabled(false);
        hl->addWidget(rb4);

        QRadioButton* rb5 = new QRadioButton("Disabled Checked");
        rb5->setChecked(true);
        rb5->setEnabled(false);
        hl->addWidget(rb5);

        hl->addStretch();
        mainLayout->addWidget(gb);
    }

    mainLayout->addStretch();

    scroll->setWidget(content);

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scroll);
}
