#include "downloadmanager.h"
DownloadManager::DownloadManager(QObject *parent)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::doDownload(QUrl url)
{
    if(fileExists(url))
    {
        QFileInfo info(url.path());
        QString basename = info.fileName();
        emit downloadCompleted(saveFolder+"/"+basename);
        return;
    }
    QNetworkRequest request(url);
    manager.get(request);
}
void DownloadManager::setSaveFolder(QString path)
{
    saveFolder = path;
}
bool DownloadManager::fileExists(QUrl url)
{
    QFileInfo info(url.path());
    QString basename = info.fileName();
    if (basename.isEmpty()) return false;
    if (QFile::exists(saveFolder+"/"+basename)) return true;
    return false;
}

QString DownloadManager::saveFileName(QUrl url)
{
    QFileInfo info(url.path());
    QString basename = info.fileName();
    if (basename.isEmpty())
        basename = "download";
    if (QFile::exists(saveFolder+"/"+basename))
    {
        // already exists, don't overwrite
        int i = 0;
        basename += '_';
        while (QFile::exists(saveFolder+"/"+basename + QString::number(i)))
            ++i;
        basename += QString::number(i);
    }
    return basename;
}

bool DownloadManager::saveToDisk(const QString filename, QIODevice *data)
{
    QFile file(saveFolder+"/"+filename);
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(filename),
                qPrintable(file.errorString()));
        return false;
    }
    file.write(data->readAll());
    file.close();
    emit downloadCompleted(saveFolder+"/"+filename);
    return true;
}

void DownloadManager::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
    }
    else
    {
        QString filename = saveFileName(url);
        if (saveToDisk(filename, reply))
            printf("Download of %s succeded (saved to %s)\n",
                   url.toEncoded().constData(), qPrintable(filename));
    }
    reply->deleteLater();
}
