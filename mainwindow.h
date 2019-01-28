#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkDiskCache>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QWebHistory>
#include <QWebView>
#include <QWebFrame>
#include <QStandardPaths>
#include <QSettings>


#include <QStringListModel>
#include <QStandardItemModel>
#include <QFile>
#include <QTimer>
#include <QDir>
#include <QProgressBar>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QFileDialog>

#include <QWebFrame>
#include <QSizePolicy>

#include <QDesktopServices>
#include <QStandardPaths>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMovie>

#include <QWidget>
#include <QNetworkDiskCache>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QWebHistory>
#include <QWebView>
#include <QWebFrame>
#include <QContextMenuEvent>
#include <QWebHitTestResult>
#include <QMenu>
#include <QWebElement>
#include <QWebView>
#include <QProcess>
#include <QMouseEvent>
#include <QClipboard>
#include <QListWidgetItem>
#include <QSettings>
#include <QMediaPlayer>
#include <QBuffer>
#include <QDateTime>
#include "ui_track.h"
#include "store.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Q_INVOKABLE void resultLoaded();
    Q_INVOKABLE void addToQueue(QString id, QString title, QString artist, QString album, QString base64, QString dominantColor, QString songId, QString albumId, QString artistId);
    Q_INVOKABLE QString getTerm();

protected slots:
    void resizeEvent(QResizeEvent *resizeEvent);
private slots:
    void init_app();
    void init_webview();
    void on_left_list_currentRowChanged(int currentRow);

    void browse();
    void search(QString offset);
    void webViewLoaded(bool loaded);
    void getAudioStream(QString id, QString songId);
    void on_search_returnPressed();
    void youtubeDlFinished(int code, QProcess::ExitStatus exitStatus);
    void ytdlReadyRead();




    //MEDIAPLAYER
    void tryStopMediaPlayer();
    void initMediaPlayer();

    void init_offline_storage();
    void setPlayerPosition(qint64 position);
    void tryToPlay(int pos);
    QString getMediaStatusString(QMediaPlayer::MediaStatus);
    QString getPlayerStateString(QMediaPlayer::State);
    void on_volumeSlider_valueChanged(int value);
    void on_stop_clicked();
    void on_seekSlider_sliderReleased();
    void on_seekSlider_sliderMoved(int position);

    //NETWORK
    void getStreamSize(const QUrl);
    void stream(const QUrl);
    void initNetworkManager();
    void contentSizeMetaChanged();
    void networkReadyRead();
    void on_play_pause_clicked();
    void on_bufferSlider_valueChanged(int value);
    void on_cache_slider_sliderMoved(int position);




    void on_right_list_itemDoubleClicked(QListWidgetItem *item);


    void on_menu_clicked();

    void on_right_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void showTrackOption();


    void saveTrack(QString format);
    void getNowPlayingTrackId();


    void loadPlayerQueue();
    void keyPressEvent(QKeyEvent *event);
    void show_top();
private:
    Ui::MainWindow *ui;
    Ui::track track_ui;

    QSettings *settings;
    QString pageType;
    int currentResultPage;
    bool isLoadingResults;
    QString offsetstr;


    QMediaPlayer *mediaPlayer; //mediplayer pointer
    QBuffer *buffer = nullptr;
    QByteArray *byteArray= nullptr;
    QNetworkAccessManager *nm = nullptr;
    QNetworkReply *reply = nullptr;
    QNetworkReply *content_size = nullptr;
    QTimer* playBackTimer = nullptr; // C++ 11 nullptr
    bool userStoppedPlayback = false;
    qint64 lastBufferSize;
    qint64 PLAYER_CACHE_SIZE = 100000 ;// 500Kb
    bool bufferFull=false;
    bool tried = false;
    int bytesPerSecond = 0;
    int secondsAvailable = 0;
    bool positionChnagedConnected;
    store *store_manager = nullptr;
    QString nowPlayingSongId;


};

#endif // MAINWINDOW_H