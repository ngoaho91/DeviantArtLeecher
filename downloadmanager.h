#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>

class DownloadManager : public QObject
{
    Q_OBJECT
    QNetworkAccessManager manager;
    QString saveFolder;
public:
    explicit DownloadManager(QObject *parent = 0);
    void doDownload(QUrl url);
    void setSaveFolder(QString path);

private:
    bool fileExists(QUrl url);
    QString saveFileName(QUrl url);
    bool saveToDisk(const QString filename, QIODevice *data);
signals:
    void downloadCompleted(QString filename);
public slots:
    void downloadFinished(QNetworkReply *reply);
};

#endif // DOWNLOADMANAGER_H
