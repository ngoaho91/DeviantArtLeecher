#include "qtdeviantleecher.h"

QtDeviantLeecher::QtDeviantLeecher()
{
    galleryDownloader = new DownloadManager();
    artDownloader = new DownloadManager();
    imageDownloader = new DownloadManager();
    offset = 0;
}
void QtDeviantLeecher::setSaveFolder(QString path)
{
    galleryDownloader->setSaveFolder(path);
    artDownloader->setSaveFolder(path);
    imageDownloader->setSaveFolder(path);
}

void QtDeviantLeecher::leech(QString name)
{
    username = name;
    nextGallery();
}

void QtDeviantLeecher::nextGallery()
{
    QString str = "http://"+username+".deviantart.com/gallery/?offset="+QString::number(offset);
    QUrl url(str);
    galleryDownloader->doDownload(url);
    connect(galleryDownloader, SIGNAL(downloadCompleted(QString)),
            this,SLOT(getArtFromGallery(QString)));
    offset+=24;
}

void QtDeviantLeecher::nextArt()
{
    if(artList.length() == 0)
    {
        emit leechFinished();
        return;
    }
    QString art = artList.at(0);
    emit artDetected(art);
    artDownloader->doDownload(QUrl(art));
    connect(artDownloader, SIGNAL(downloadCompleted(QString)),
            this,SLOT(getImageFromArt(QString)));
    artList.removeAt(0);
}

void QtDeviantLeecher::getArtFromGallery(QString filename)
{
    QFile file(filename);
    bool found = false;
    if (file.open(QIODevice::ReadOnly)) {
        QString content(file.readAll());
        QRegExp aExp("<a class=\"thumb\"[^>]+>");
        int pos = 0;
        while ((pos = aExp.indexIn(content, pos)) != -1)
        {
            found = true;
            QString a = aExp.cap(0);
            QRegExp hrefExp("href=\"([^\"]*)\"");
            if(hrefExp.indexIn(a) != -1)
            {
                QString href = hrefExp.cap(0);
                href.remove(href.length()-1,1);
                href.remove(0,6);
                artList.append(href);
            }
            pos += aExp.matchedLength();
        }
    }
    file.close();
    file.remove();
    if(found) nextGallery(); else nextArt();
}
void QtDeviantLeecher::getImageFromArt(QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QString content(file.readAll());
        content.replace('\n',' ');
        QRegExp imgExp("<img collect_rid=\"[^>]+class=\"dev-content-full\">");
        if(imgExp.indexIn(content) != -1)
        {
            QString img = imgExp.cap(0);
            QRegExp srcExp("src=\"([^\"]*)\"");
            if(srcExp.indexIn(img) != -1)
            {
                QString src = srcExp.cap(0);
                src.remove(src.length()-1,1);
                src.remove(0,5);
                emit imageDetected(src);
                QUrl url(src);
                imageDownloader->doDownload(url);
                connect(imageDownloader, SIGNAL(downloadCompleted(QString)),
                        this,SLOT(emitImageDownloaded(QString)));
            }
        }
    }
    file.close();
    file.remove();
}
void QtDeviantLeecher::emitImageDownloaded(QString filename)
{
    emit imageDownloaded(filename);
    nextArt();
}
