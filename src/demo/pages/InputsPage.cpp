#include "InputsPage.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QFontComboBox>
#include <QSlider>
#include <QDial>
#include <QFrame>
#include <QSizePolicy>

static QLabel* sectionLabel(const QString& text)
{
    QLabel* lbl = new QLabel(text);
    lbl->setStyleSheet("font-weight: 600; font-size: 12px; margin-top: 4px;");
    return lbl;
}

InputsPage::InputsPage(QWidget* parent)
    : QWidget(parent)
{
    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget* content = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(content);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(16);

    // ── QLineEdit ────────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QLineEdit");
        QFormLayout* form = new QFormLayout(gb);
        form->setSpacing(10);
        form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
        form->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

        QLineEdit* le1 = new QLineEdit("Normal text input");
        form->addRow("Normal:", le1);

        QLineEdit* le2 = new QLineEdit();
        le2->setPlaceholderText("Enter text here...");
        form->addRow("Placeholder:", le2);

        QLineEdit* le3 = new QLineEdit("password123");
        le3->setEchoMode(QLineEdit::Password);
        form->addRow("Password:", le3);

        QLineEdit* le4 = new QLineEdit("Read-only content");
        le4->setReadOnly(true);
        form->addRow("Read-only:", le4);

        QLineEdit* le5 = new QLineEdit("Disabled input");
        le5->setEnabled(false);
        form->addRow("Disabled:", le5);

        QLineEdit* le6 = new QLineEdit("Clear me");
        le6->setClearButtonEnabled(true);
        form->addRow("Clear button:", le6);

        mainLayout->addWidget(gb);
    }

    // ── QTextEdit / QPlainTextEdit ───────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QTextEdit / QPlainTextEdit");
        QHBoxLayout* hl = new QHBoxLayout(gb);
        hl->setSpacing(12);

        QVBoxLayout* vl1 = new QVBoxLayout();
        vl1->addWidget(sectionLabel("QTextEdit (rich text):"));
        QTextEdit* te = new QTextEdit();
        te->setHtml("<b>Bold</b>, <i>italic</i>, <u>underline</u><br>"
                    "Supports <span style='color:#4F8EF7'>rich text</span> formatting.");
        te->setMinimumHeight(90);
        te->setMaximumHeight(110);
        vl1->addWidget(te);
        hl->addLayout(vl1);

        QVBoxLayout* vl2 = new QVBoxLayout();
        vl2->addWidget(sectionLabel("QPlainTextEdit:"));
        QPlainTextEdit* pte = new QPlainTextEdit();
        pte->setPlainText("Plain text editor\nLine 2\nLine 3");
        pte->setMinimumHeight(90);
        pte->setMaximumHeight(110);
        vl2->addWidget(pte);
        hl->addLayout(vl2);

        QVBoxLayout* vl3 = new QVBoxLayout();
        vl3->addWidget(sectionLabel("Disabled:"));
        QTextEdit* teDisabled = new QTextEdit("Disabled text edit");
        teDisabled->setEnabled(false);
        teDisabled->setMinimumHeight(90);
        teDisabled->setMaximumHeight(110);
        vl3->addWidget(teDisabled);
        hl->addLayout(vl3);

        mainLayout->addWidget(gb);
    }

    // ── Spin Boxes ───────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QSpinBox / QDoubleSpinBox / Date & Time");
        QFormLayout* form = new QFormLayout(gb);
        form->setSpacing(10);
        form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
        form->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

        QSpinBox* sb = new QSpinBox();
        sb->setRange(0, 100);
        sb->setValue(42);
        sb->setMinimumWidth(120);
        form->addRow("QSpinBox:", sb);

        QSpinBox* sbDis = new QSpinBox();
        sbDis->setValue(10);
        sbDis->setEnabled(false);
        sbDis->setMinimumWidth(120);
        form->addRow("SpinBox disabled:", sbDis);

        QDoubleSpinBox* dsb = new QDoubleSpinBox();
        dsb->setRange(0.0, 100.0);
        dsb->setValue(3.14);
        dsb->setDecimals(2);
        dsb->setMinimumWidth(120);
        form->addRow("QDoubleSpinBox:", dsb);

        QDateEdit* de = new QDateEdit(QDate::currentDate());
        de->setCalendarPopup(true);
        de->setMinimumWidth(160);
        form->addRow("QDateEdit:", de);

        QTimeEdit* te = new QTimeEdit(QTime::currentTime());
        te->setMinimumWidth(160);
        form->addRow("QTimeEdit:", te);

        QDateTimeEdit* dte = new QDateTimeEdit(QDateTime::currentDateTime());
        dte->setCalendarPopup(true);
        dte->setMinimumWidth(220);
        form->addRow("QDateTimeEdit:", dte);

        mainLayout->addWidget(gb);
    }

    // ── QComboBox ────────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QComboBox / QFontComboBox");
        QFormLayout* form = new QFormLayout(gb);
        form->setSpacing(10);
        form->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
        form->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

        QComboBox* cb1 = new QComboBox();
        cb1->addItems({"Option Alpha", "Option Beta", "Option Gamma", "Option Delta"});
        form->addRow("Normal:", cb1);

        QComboBox* cb2 = new QComboBox();
        cb2->setEditable(true);
        cb2->addItems({"Editable 1", "Editable 2", "Editable 3"});
        form->addRow("Editable:", cb2);

        QComboBox* cb3 = new QComboBox();
        cb3->addItems({"Disabled Option"});
        cb3->setEnabled(false);
        form->addRow("Disabled:", cb3);

        QFontComboBox* fcb = new QFontComboBox();
        form->addRow("QFontComboBox:", fcb);

        mainLayout->addWidget(gb);
    }

    // ── QSlider / QDial ──────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QSlider / QDial");
        QVBoxLayout* vl = new QVBoxLayout(gb);
        vl->setSpacing(12);

        vl->addWidget(sectionLabel("Horizontal Sliders:"));

        QFormLayout* sliderForm = new QFormLayout();
        sliderForm->setSpacing(10);
        sliderForm->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sliderForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

        QSlider* s1 = new QSlider(Qt::Horizontal);
        s1->setRange(0, 100);
        s1->setValue(42);
        sliderForm->addRow("Normal (42):", s1);

        QSlider* s2 = new QSlider(Qt::Horizontal);
        s2->setRange(0, 100);
        s2->setValue(70);
        s2->setEnabled(false);
        sliderForm->addRow("Disabled (70):", s2);

        vl->addLayout(sliderForm);

        vl->addWidget(sectionLabel("Vertical Slider + QDial:"));
        QHBoxLayout* vRow = new QHBoxLayout();
        vRow->setSpacing(24);

        QVBoxLayout* svBox = new QVBoxLayout();
        svBox->addWidget(new QLabel("Vertical:"));
        QSlider* sv = new QSlider(Qt::Vertical);
        sv->setRange(0, 100);
        sv->setValue(60);
        sv->setFixedHeight(80);
        svBox->addWidget(sv);
        vRow->addLayout(svBox);

        QVBoxLayout* dialBox = new QVBoxLayout();
        dialBox->addWidget(new QLabel("Dial (35):"));
        QDial* dial = new QDial();
        dial->setRange(0, 100);
        dial->setValue(35);
        dial->setFixedSize(80, 80);
        dialBox->addWidget(dial);
        vRow->addLayout(dialBox);

        QVBoxLayout* dialBox2 = new QVBoxLayout();
        dialBox2->addWidget(new QLabel("Dial disabled:"));
        QDial* dialDisabled = new QDial();
        dialDisabled->setRange(0, 100);
        dialDisabled->setValue(60);
        dialDisabled->setEnabled(false);
        dialDisabled->setFixedSize(80, 80);
        dialBox2->addWidget(dialDisabled);
        vRow->addLayout(dialBox2);

        vRow->addStretch();
        vl->addLayout(vRow);

        mainLayout->addWidget(gb);
    }

    mainLayout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scroll);
}
