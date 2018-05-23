#include "manframe.h"
#include "qroundprogressbar.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QDBusInterface>
#include <QTimer>
#include <DPlatformWindowHandle>

DWIDGET_USE_NAMESPACE

ManFrame::ManFrame(QWidget *parent)
    : DBlurEffectWidget(parent)
{
    DPlatformWindowHandle *platformWindowHandle = new DPlatformWindowHandle(this);

    platformWindowHandle->setEnableBlurWindow(true);
    platformWindowHandle->setTranslucentBackground(true);
    platformWindowHandle->setWindowRadius(0);
    platformWindowHandle->setBorderWidth(0);
    platformWindowHandle->setShadowOffset(QPoint(0, 0));
    platformWindowHandle->setShadowColor(QColor(0, 0, 0, 255 * 0.7));

    setBlendMode(InWindowBlend);
    setMaskColor(DarkColor);
    setWindowFlags(Qt::FramelessWindowHint);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);

    m_coverLbl = new QLabel;
    m_coverLbl->setFixedSize(300, 300);
    m_coverLbl->setPixmap(QPixmap("/Users/lxz/Pictures/p/1428112046634.jpg").scaled(300, 300, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    QLabel *maxCurOffLine = new QLabel;
    maxCurOffLine->setFixedSize(400, 5);
    maxCurOffLine->setStyleSheet("background: white;");

    m_songLbl = new QLabel;
    m_songLbl->setText("演示歌曲");
    m_songLbl->setStyleSheet("font-size: 20px;color:white;");

    m_authorLbl = new QLabel;
    m_authorLbl->setText("作者");
    m_authorLbl->setStyleSheet("font-size: 15px;color:white;");

    QLabel *curOffLine = new QLabel;
    curOffLine->setFixedSize(200, 2);
    curOffLine->setStyleSheet("background: white;");

    m_roundBar = new QRoundProgressBar;
//    m_roundBar->setInnerOuterRate(0.5);
    m_roundBar->setFixedSize(200, 200);

    layout->addSpacing(20);
    layout->addWidget(m_coverLbl, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(maxCurOffLine, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(m_songLbl, 0, Qt::AlignCenter);
    layout->addSpacing(10);
    layout->addWidget(m_authorLbl, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(curOffLine, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(m_roundBar, 0, Qt::AlignCenter);
    layout->addSpacing(20);

    setFixedWidth(420);

    m_mprisMonitor = new DMPRISMonitor;
    connect(m_mprisMonitor, &DMPRISMonitor::mprisAcquired, this, &ManFrame::mprisAcquired);
    connect(m_mprisMonitor, &DMPRISMonitor::mprisLost, this, &ManFrame::mprisLost);
    m_mprisMonitor->init();

    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(1000);

    connect(timer, &QTimer::timeout, this, [=] {
        if (m_mprisInter) {
            m_roundBar->setValue((double)m_mprisInter->position());
        }

        timer->start();
    });

    timer->start();
}

ManFrame::~ManFrame()
{

}

void ManFrame::mprisAcquired(const QString &path)
{
    m_lastPath = path;

    // save paths
    if (!m_mprisPaths.contains(path))
        m_mprisPaths.append(path);

    if (m_mprisInter)
        m_mprisInter->deleteLater();

    m_mprisInter = new DBusMPRIS(path, "/org/mpris/MediaPlayer2", QDBusConnection::sessionBus(), this);

    connect(m_mprisInter, &DBusMPRIS::MetadataChanged, this, &ManFrame::metadataChanged);

    metadataChanged();
}

void ManFrame::mprisLost(const QString &path)
{
    m_mprisPaths.removeOne(path);

    if (m_lastPath != path)
        return;

    if (!m_mprisInter)
        return;

    if (!m_mprisPaths.isEmpty())
        return mprisAcquired(m_mprisPaths.last());

    m_mprisInter->deleteLater();
    m_mprisInter = nullptr;
}

void ManFrame::metadataChanged()
{
    const QVariantMap &value = m_mprisInter->metadata();
    if (value.isEmpty()) return;

    m_roundBar->setMaximum(value.value("mpris:length").toDouble());
    m_authorLbl->setText(value.value("xesam:artist").toString());
    m_songLbl->setText(value.value("xesam:title").toString());
    const QUrl &pictureUrl = value.value("mpris:artUrl").toString();
    const QPixmap &picture = QPixmap(pictureUrl.toLocalFile()).scaled(QSize(300, 300), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_coverLbl->setPixmap(picture);
}
