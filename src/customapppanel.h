#ifndef CUSTOMAPPPANEL_H
#define CUSTOMAPPPANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>


class CustomAppPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CustomAppPanel(QWidget *parent = nullptr);

private:
    QHBoxLayout *m_lay;

    void initUi();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void minimizeRequested();
    void closeRequested();
};

#endif // CUSTOMAPPPANEL_H
