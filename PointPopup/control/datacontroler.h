/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Match <2696627729@qq.com>
* Maintainer: Match <2696627729@qq.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#ifndef DATACONTROLER_H
#define DATACONTROLER_H

#include <QObject>
#include <QQmlEngine>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QLocalSocket>
#include <QTimer>
#include <QProcess>
#include <sys/vfs.h>
#include "xmloperations.h"

const QString MAIN_PROGRAM_PATH = "/opt/Point/PointDownload/PointDownload";
//const QString MAIN_PROGRAM_PATH =
//        "/home/Match/桌面/build-PointDownload-Desktop_Qt_5_3_0_GCC_64bit-Release/PointDownload";

class DataControler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileNameList READ getFileNameList WRITE setFileNameList NOTIFY sFileNameListChange)
    Q_PROPERTY(QString fileURL READ getFileURL WRITE setFileURL NOTIFY sFileURLChange)
    Q_PROPERTY(QString fileSavePath READ getFileSavePath WRITE setFileSavePath NOTIFY sFileSavePathChange)
    Q_PROPERTY(QString maxSpeed READ getMaxSpeed WRITE setMaxSpeed NOTIFY sMaxSpeedChange)
    Q_PROPERTY(QString maxThread READ getMaxThread WRITE setMaxThread NOTIFY sMaxThreadChange)
    Q_PROPERTY(QString freeSpace READ getFreeSpace WRITE setFreeSpace NOTIFY sFreeSpaceChange)

public:
    static DataControler * getInstance();

    //qml中能直接调用此方法,将数据发送到服务端
    Q_INVOKABLE void selectSavePath(QString buttonName);
    Q_INVOKABLE void sendToMainServer(QString threads, QString speed, QString savePath);

    //从浏览器（谷歌、火狐），或者从主程序取得下载URL和下载类型的值
    void getURLFromBrowser(QString URLInfo);

    QString getFileURL();
    QString getFileNameList();
    QString getFileSavePath();
    QString getMaxThread();
    QString getMaxSpeed();
    QString getFreeSpace();

    void setFileURL(QString URL);
    void setFileNameList(QString nameList);
    void setFileSavePath(QString path);
    void setMaxThread(QString count);
    void setMaxSpeed(QString speed);
    void setFreeSpace(QString space);

signals:
    void sFileURLChange();
    void sFileNameListChange();
    void sFileSavePathChange();
    void sMaxThreadChange();
    void sMaxSpeedChange();
    void sFreeSpaceChange();

    void sFnishGetAllInfo();
public slots:

private slots:
    void getURLInfoFromYouget();                //使用youget获取文件名，文件大小，文件类型信息
    void getURLInfo();                          //分类获取文件名，文件大小，文件类型信息

    void getYougetFeedBack();
    void getYougetError();

    void mainProgramStarted();                  //主程序启动后，连接主程序
private:
    explicit DataControler(QObject *parent = 0);

    QString getLinuxFreeSpace(QString path);


    QString getHttpFileTypeSize(QString URL);  //从http链接中获取文件大小和类型type@size
    QString getFtpFileTypeSize(QString URL);  //从ftp链接中获取文件大小和类型type@size
    QString getIconName();                      //

    QString getHttpFtpFileName(QString URL);    //

    void startMainProgram();                    //尝试启动主程序
    void connectToMainProgram();                //主程序启动后连接到主程序

    bool checkIsInDownloading(QString URL);     //查看URL是否已经在正在下载列表
    bool checkIsInDownloaded(QString URL);      //查看URL是否已经在已完成下载列表
    bool checkIsInDownloadTrash(QString URL);   //查看URL是否已经在垃圾桶列表
private:
    static DataControler * dataControler;

    XMLOperations gXMLOpera;

    //将要发送到qml界面上的数据
    QString fileURL;
    QString fileNameList;   //BT文件中可能包含多个文件,split by ?:?: type@size@name?:?type@size...
    QString fileSavePath;   //默认从系统文件读取，但是也可以从文件选择框选择
    QString maxThread;
    QString maxSpeed;
    QString freeSpace;      //对应路径的剩余空间

    //需要传递到主程序但无需显示到qml的数据
    QString toolsType;
    QString fileType;
    QString redirectURL;

    QProcess * yougetProcess;

    QLocalSocket *localSocket;
};

//将单例对象注册到qml中使用的回调函数
static QObject * dataObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return DataControler::getInstance();
}

#endif // DATACONTROLER_H
