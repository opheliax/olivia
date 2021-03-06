#include "paginator.h"
#include <QDateTime>
#include <QWebView>
#include <QWebFrame>
#include <QWebPage>

paginator::paginator(QObject *parent) : QObject(parent)
{
    QString setting_path =  QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QDir paginator(setting_path+"/paginator");
    if(!paginator.exists()){
        if(paginator.mkdir(paginator.path())){
            qDebug()<<"created paginator dir";
        }
    }
    paginator_path = paginator.absolutePath();
}

//used to save data returned from function dataType of page pageType for query query
void paginator::save(QString pageType,QString dataType,QString query,QString data){
    QString path = createDir(pageType.trimmed()+"/"+dataType.trimmed());
    QFile file(path+query.trimmed());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
              return;
    QTextStream out(&file);
    QString loadOnlineBtn;
    if(pageType=="album_view"){
        loadOnlineBtn  = "<a  class='ui-shadow-icon ui-btn ui-shadow ui-corner-all ui-icon-clock ui-btn-icon-left' href='#' onclick='paginator.deleteCache(\""+pageType+"\",\""+dataType+"\",\""+query+"\")'> showing old snapshot("+QDateTime::currentDateTime().toLocalTime().toString()+") Refresh</a>";
    }else{
        loadOnlineBtn  = "<a  class='ui-shadow-icon ui-btn ui-shadow ui-corner-all ui-icon-clock ui-btn-icon-left' href='#' onclick='paginator.deleteCache(\""+pageType+"\",\""+dataType+"\",\""+query+"\")'> showing old snapshot("+QDateTime::currentDateTime().toLocalTime().toString()+") Refresh</a>";
    }
    out <<loadOnlineBtn<< data.trimmed();
}

//used to load data from offline page pageType for funcction dataType for query query
QString paginator::load(QString pageType,QString dataType,QString query){
    QFile file(getPath(pageType,dataType,query));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"unable to open file";
    }
    QTextStream in(&file);
    return in.readAll();
}

//used to check if data is present in offline storage
bool paginator::isOffline(QString pageType,QString dataType,QString query){
   return QFileInfo(QFile(getPath(pageType,dataType,query))).exists();
}


//core
//used to create base path where query file will be saved
QString paginator::createDir(QString name){  // name without slashes
    QDir dir(paginator_path+"/"+name.trimmed());
    dir.mkpath(dir.path());
    return dir.path()+"/";
}

//used to get full path of query file
QString paginator::getPath(QString pageType,QString dataType,QString query){
    QDir file(paginator_path+"/"+pageType.trimmed()+"/"+dataType.trimmed()+"/"+query.trimmed());
    //qDebug()<<file.path();
    return file.path();
}

//load new data online
void paginator::deleteCache(QString pageType,QString dataType,QString query){
    qDebug()<<pageType<<dataType<<query;
    QString path = createDir(pageType.trimmed()+"/"+dataType.trimmed());
    QFile file(path+query.trimmed());
    file.remove();
    emit reloadRequested(dataType,query);
}
