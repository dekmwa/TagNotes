#include "customapppanel.h"

CustomAppPanel::CustomAppPanel(QWidget *parent)
    : QWidget{parent},
    m_lay(new QHBoxLayout(this))
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("CustomAppPanel");

    initUi();
}

void CustomAppPanel::initUi() {
    QLabel *title = new QLabel();
    title->setText("Заметки тегами");
    m_lay->addWidget(title);

    m_lay->addStretch();

    QWidget *buttonsCont = new QWidget();
    QHBoxLayout *buttonsLay = new QHBoxLayout();
    buttonsCont->setLayout(buttonsLay);
    buttonsCont->setContentsMargins(0, 0, 0, 0);
    buttonsLay->setContentsMargins(0, 0, 0, 0);
    buttonsLay->setSpacing(3);

    QPushButton *minimize = new QPushButton();
    minimize->setIcon(QIcon(":/icons/minimize.svg"));
    minimize->setIconSize(QSize(20, 20));
    minimize->setFixedSize(25, 25);
    buttonsLay->addWidget(minimize);

    QPushButton *close = new QPushButton();
    close->setIcon(QIcon(":/icons/close.svg"));
    close->setIconSize(QSize(20, 20));
    close->setFixedSize(25, 25);
    buttonsLay->addWidget(close);

    m_lay->addWidget(buttonsCont);

    connect(minimize, &QPushButton::clicked, this, &CustomAppPanel::minimizeRequested);
    connect(close, &QPushButton::clicked, this, &CustomAppPanel::closeRequested);

    setFixedHeight(30);
    m_lay->setContentsMargins(10, 0, 10, 0);
    m_lay->setSpacing(0);
}

void CustomAppPanel::mousePressEvent(QMouseEvent *event)
{
    if (parentWidget()) {
        QApplication::sendEvent(parentWidget(), event);
    }
    event->accept();
}

void CustomAppPanel::mouseMoveEvent(QMouseEvent *event)
{
    if (parentWidget()) {
        QApplication::sendEvent(parentWidget(), event);
    }
    event->accept();
}

void CustomAppPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if (parentWidget()) {
        QApplication::sendEvent(parentWidget(), event);
    }
    event->accept();
}
