#ifndef QTDEVIANTLEECHER_H
#define QTDEVIANTLEECHER_H
#include "downloadmanager.h"
#include <QStringList>
class QtDeviantLeecher : public QObject
{
    Q_OBJECT
    DownloadManager* galleryDownloader;
    DownloadManager* artDownloader;
    DownloadManager* imageDownloader;
    QStringList artList;
    QString username;
    int offset;
public:
    explicit QtDeviantLeecher();
    void setSaveFolder(QString path);
    void leech(QString name);
private:
    void nextArt();
    void nextGallery();
signals:
    void galleryDetected(int size);
    void artDetected(QString url);
    void imageDetected(QString url);
    void imageDownloaded(QString filename);
    void leechFinished();
public slots:
    void getArtFromGallery(QString filename);
    void getImageFromArt(QString filename);
    void emitImageDownloaded(QString filename);
};

#endif // QTDEVIANTLEECHER_H
