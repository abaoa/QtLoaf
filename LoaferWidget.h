#ifndef LOAFERWIDGET_H
#define LOAFERWIDGET_H

#include <QWidget>

class LoaferWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoaferWidget(QWidget *parent = 0);
    ~LoaferWidget();
    void start();
protected:
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    int mValue;
    int mTimerID;
    QWidget *mWinLoadingWidget;
};

#endif // LOAFERWIDGET_H
