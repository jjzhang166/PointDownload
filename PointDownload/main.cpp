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

#include <QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <qquickitem.h>
#include <QQuickWindow>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include "Controler/middlesender.h"
#include "Controler/peventfilter.h"
#include "Controler/settingcontroler.h"
#include "Controler/topcontrl.h"

#include "Controler/monitorClipBoard.h"
#include "Controler/downloaddatasender.h"
#include "qtsinglecoreapplication.h"

#include "Download/unifiedinterface.h"

int main(int argc, char *argv[])
{
    QtSingleCoreApplication app(argc, argv);
    if (app.isRunning())
    {
        return 0;
    }

//    QApplication app(argc,argv);
    QString local = QLocale::system().name();
    QTranslator translator;
    translator.load(QString(":/languages/:/languages/resources/LANG/PointDownload_") + local);
    app.installTranslator(&translator);

    //这样能保证系统托盘类的初始化在qml初始化之前完成，避免造 成gtk的一些错误
    TopContrl::getInstance()->initTrayIcon();
    DownloadDataSender::getInstance();
    PEventFilter::getInstance();

    //注册的参数格式：import dataControler 1.0
    qmlRegisterType<SettingControler>("settingControler", 1, 0, "SettingControler");
    qmlRegisterType<MiddleSender>("middleSender", 1, 0, "MiddleSender");

    MonitorClipBoard * clipBoard  ;
    clipBoard = new MonitorClipBoard;

    QQmlApplicationEngine engin(QUrl("qrc:/qml/qml/PointDownload/main.qml"));

    //    //添加全局事件过滤
//    PEventFilter tmpFilter;
//    app.installEventFilter(&tmpFilter);
   app.installEventFilter(PEventFilter::getInstance());


    return app.exec();
}

