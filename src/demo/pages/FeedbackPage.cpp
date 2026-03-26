#include "FeedbackPage.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>
#include <QScrollBar>
#include <QPushButton>
#include <QFrame>
#include <QTimer>
#include <QSlider>

static QLabel* sectionLabel(const QString& text)
{
    QLabel* lbl = new QLabel(text);
    lbl->setStyleSheet("font-weight: 600; font-size: 12px;");
    return lbl;
}

FeedbackPage::FeedbackPage(QWidget* parent)
    : QWidget(parent)
{
    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget* content = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(content);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(16);

    // ── QProgressBar ─────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QProgressBar");
        QVBoxLayout* vl = new QVBoxLayout(gb);
        vl->setSpacing(10);

        // Various fill levels
        struct BarInfo { int value; QString label; };
        const QList<BarInfo> bars = {
            {0,   "0% — Empty"},
            {25,  "25% — Quarter"},
            {50,  "50% — Half"},
            {75,  "75% — Three quarters"},
            {100, "100% — Complete"},
        };

        for (const BarInfo& info : bars) {
            QHBoxLayout* row = new QHBoxLayout();
            QLabel* lbl = new QLabel(info.label);
            lbl->setFixedWidth(180);
            row->addWidget(lbl);
            QProgressBar* pb = new QProgressBar();
            pb->setRange(0, 100);
            pb->setValue(info.value);
            pb->setTextVisible(true);
            row->addWidget(pb);
            vl->addLayout(row);
        }

        // Indeterminate (busy) progress bar
        vl->addWidget(sectionLabel("Indeterminate (busy):"));
        QProgressBar* busyBar = new QProgressBar();
        busyBar->setRange(0, 0); // indeterminate
        busyBar->setTextVisible(false);
        vl->addWidget(busyBar);

        // Disabled
        vl->addWidget(sectionLabel("Disabled:"));
        QProgressBar* disabledBar = new QProgressBar();
        disabledBar->setRange(0, 100);
        disabledBar->setValue(60);
        disabledBar->setEnabled(false);
        vl->addWidget(disabledBar);

        // Animated progress bar
        vl->addWidget(sectionLabel("Animated (click Start/Stop):"));
        QHBoxLayout* animRow = new QHBoxLayout();
        QProgressBar* animBar = new QProgressBar();
        animBar->setRange(0, 100);
        animBar->setValue(0);
        animRow->addWidget(animBar);

        QPushButton* startBtn = new QPushButton("Start");
        startBtn->setFixedWidth(70);
        animRow->addWidget(startBtn);

        QPushButton* stopBtn = new QPushButton("Stop");
        stopBtn->setFixedWidth(70);
        animRow->addWidget(stopBtn);

        vl->addLayout(animRow);

        // Timer for animation
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [animBar](){
            int v = animBar->value() + 2;
            if (v > 100) v = 0;
            animBar->setValue(v);
        });
        connect(startBtn, &QPushButton::clicked, this, [timer](){ timer->start(50); });
        connect(stopBtn,  &QPushButton::clicked, this, [timer](){ timer->stop(); });

        mainLayout->addWidget(gb);
    }

    // ── QScrollBar ───────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QScrollBar");
        QVBoxLayout* vl = new QVBoxLayout(gb);
        vl->setSpacing(10);

        vl->addWidget(sectionLabel("Horizontal:"));
        QScrollBar* hBar = new QScrollBar(Qt::Horizontal);
        hBar->setRange(0, 100);
        hBar->setValue(40);
        hBar->setFixedHeight(16);
        vl->addWidget(hBar);

        QScrollBar* hBarDisabled = new QScrollBar(Qt::Horizontal);
        hBarDisabled->setRange(0, 100);
        hBarDisabled->setValue(60);
        hBarDisabled->setEnabled(false);
        hBarDisabled->setFixedHeight(16);
        vl->addWidget(hBarDisabled);

        vl->addWidget(sectionLabel("Vertical:"));
        QHBoxLayout* vBarRow = new QHBoxLayout();
        QScrollBar* vBar = new QScrollBar(Qt::Vertical);
        vBar->setRange(0, 100);
        vBar->setValue(30);
        vBar->setFixedWidth(16);
        vBar->setFixedHeight(80);
        vBarRow->addWidget(vBar);

        QScrollBar* vBarDisabled = new QScrollBar(Qt::Vertical);
        vBarDisabled->setRange(0, 100);
        vBarDisabled->setValue(70);
        vBarDisabled->setEnabled(false);
        vBarDisabled->setFixedWidth(16);
        vBarDisabled->setFixedHeight(80);
        vBarRow->addWidget(vBarDisabled);
        vBarRow->addStretch();
        vl->addLayout(vBarRow);

        mainLayout->addWidget(gb);
    }

    // ── QLabel Variants ──────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("QLabel Variants");
        QVBoxLayout* vl = new QVBoxLayout(gb);
        vl->setSpacing(8);

        QLabel* normal = new QLabel("Normal label text");
        vl->addWidget(normal);

        QLabel* bold = new QLabel("<b>Bold label text</b>");
        vl->addWidget(bold);

        QLabel* rich = new QLabel("<span style='font-size:16px; font-weight:700;'>Large heading</span>");
        vl->addWidget(rich);

        QLabel* colored = new QLabel("<span style='color:#4F8EF7;'>Colored label (inline style)</span>");
        vl->addWidget(colored);

        QLabel* wrapped = new QLabel(
            "This is a long label that wraps across multiple lines when the window is narrow. "
            "It demonstrates word wrap behavior in QLabel with setWordWrap(true)."
        );
        wrapped->setWordWrap(true);
        vl->addWidget(wrapped);

        QLabel* disabled = new QLabel("Disabled label");
        disabled->setEnabled(false);
        vl->addWidget(disabled);

        QLabel* linkLabel = new QLabel("<a href='https://qt.io'>Qt Official Website</a>");
        linkLabel->setOpenExternalLinks(true);
        vl->addWidget(linkLabel);

        mainLayout->addWidget(gb);
    }

    // ── Tooltip Demo ─────────────────────────────────────────
    {
        QGroupBox* gb = new QGroupBox("Tooltips");
        QHBoxLayout* hl = new QHBoxLayout(gb);
        hl->setSpacing(8);

        QPushButton* btn1 = new QPushButton("Hover for tooltip");
        btn1->setToolTip("This is a standard tooltip.\nIt supports multi-line text.");
        hl->addWidget(btn1);

        QPushButton* btn2 = new QPushButton("Rich tooltip");
        btn2->setToolTip("<b>Rich Tooltip</b><br>Supports <i>HTML</i> formatting.");
        hl->addWidget(btn2);

        QPushButton* btn3 = new QPushButton("No tooltip");
        hl->addWidget(btn3);

        hl->addStretch();
        mainLayout->addWidget(gb);
    }

    mainLayout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scroll);
}
