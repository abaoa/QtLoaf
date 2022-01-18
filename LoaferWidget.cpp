#include "LoaferWidget.h"
#include <QQmlApplicationEngine>
#include <QtCore>
#include <QtGui>
#pragma execution_character_set("utf-8")

LoaferWidget::LoaferWidget(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    mWinLoadingWidget = NULL;

    QEventLoop *loop = new QEventLoop(this);

    QQmlApplicationEngine *engine = new QQmlApplicationEngine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
        this, [url,loop,this](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
            {
                loop->quit();
                QCoreApplication::exit(-1);
            }
            else
            {
                QWindow *window = static_cast<QWindow*>(obj);
                if(window)
                {
                    mWinLoadingWidget = QWidget::createWindowContainer(window,this);
                    mWinLoadingWidget->setWindowFlags(Qt::FramelessWindowHint);
                    mWinLoadingWidget->setFixedSize(250,250);
                }

                loop->quit();
            }
        }, Qt::QueuedConnection);
    engine->load(url);

    loop->exec();

    auto time = QRandomGenerator::global()->bounded(300, 1000);
    mTimerID = this->startTimer(time,Qt::PreciseTimer);

    mValue = 1;
    start();

}
LoaferWidget::~LoaferWidget()
{

}

void LoaferWidget::start()
{
    mValue += QRandomGenerator::global()->bounded(1, 10);
    if(mValue >= 100)
    {
        mValue = QRandomGenerator::global()->bounded(20, 50);
    }

    this->update();
}

void LoaferWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform |
                           QPainter::Qt4CompatiblePainting);

    painter.setPen(Qt::SolidLine);

    auto rect = this->rect();
    auto center = rect.center();

    auto pen = painter.pen();
    pen.setColor(Qt::white);

    auto font = painter.font();
    font.setFamily("Lantinghei SC");//Lantinghei SC//Microsoft YaHei Ui
    auto fm = painter.fontMetrics();

    painter.fillRect(rect,Qt::black);

    painter.save();
    font.setPointSize(23);
    painter.setFont(font);
    painter.setPen(pen);
    fm = painter.fontMetrics();
    auto textRect1 = QRect(0,center.y(),rect.width(),fm.height()*2);
    painter.drawText(textRect1,Qt::AlignCenter,tr("正在进行更新%1%").arg(mValue));
    painter.restore();

    if(mWinLoadingWidget)
    mWinLoadingWidget->move(textRect1.center() - QPoint(mWinLoadingWidget->width()/2,mWinLoadingWidget->height()+fm.height()));

    painter.save();
    font.setPointSize(23);
    painter.setFont(font);
    painter.setPen(pen);
    fm = painter.fontMetrics();
    auto textRect2 = QRect(0,textRect1.bottomLeft().y(),rect.width(),fm.height()*2);
    painter.drawText(textRect2,Qt::AlignHCenter|Qt::AlignTop,tr("请保持计算机打开状态。"));
    painter.restore();

    painter.save();
    font.setPointSize(23);
    painter.setFont(font);
    painter.setPen(pen);
    fm = painter.fontMetrics();
    auto textRect3 = QRect(0,rect.height()-100,rect.width(),fm.height()*2);
    painter.drawText(textRect3,Qt::AlignCenter,tr("计算机可能会重启几次"));
    painter.restore();

}


void LoaferWidget::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == mTimerID)
    {
        this->start();
    }
}


void LoaferWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    if(this->isFullScreen())
        this->showNormal();
    else
        this->showFullScreen();
}


void LoaferWidget::showEvent(QShowEvent *)
{
    if(mWinLoadingWidget)
    {
        mWinLoadingWidget->show();
    }
}


void LoaferWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        this->close();
    }
}
