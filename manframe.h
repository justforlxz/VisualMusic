#ifndef MANFRAME_H
#define MANFRAME_H

#include "mpris/dbusinterface.h"
#include "mpris/dbusmpris.h"
#include "mpris/dmprismonitor.h"

#include <QWidget>
#include <DBlurEffectWidget>
#include <dmpriscontrol.h>

DWIDGET_USE_NAMESPACE

class QRoundProgressBar;
class QLabel;
class ManFrame : public DBlurEffectWidget
{
    Q_OBJECT

public:
    ManFrame(QWidget *parent = 0);
    ~ManFrame();

private:
    void mprisAcquired(const QString &path);
    void mprisLost(const QString &path);
    void metadataChanged();

private:
    QLabel *m_coverLbl;
    QLabel *m_songLbl;
    QLabel *m_authorLbl;
    QRoundProgressBar *m_roundBar;
    DMPRISMonitor *m_mprisMonitor;
    DBusMPRIS *m_mprisInter = nullptr;
    QString m_lastPath;
    QStringList m_mprisPaths;
//    Player *m_dbusInter;
};

#endif // MANFRAME_H
