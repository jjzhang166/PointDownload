#/***********************************************************************
#*PointDownload
#*Copyright (C) 2014  PointTeam
#*
#*
#* This program is free software: you can redistribute it and/or modify
#* it under the terms of the GNU General Public License as published by
#* the Free Software Foundation, either version 3 of the License, or
#* any later version.
#*
#* This program is distributed in the hope that it will be useful,
#* but WITHOUT ANY WARRANTY; without even the implied warranty of
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#* GNU General Public License for more details.
#*
#* You should have received a copy of the GNU General Public License
#* along with this program.  If not, see <http://www.gnu.org/licenses/>.
# ***********************************************************************/

TEMPLATE = app
QT += xml
QT += widgets
QT += qml quick

SOURCES += main.cpp \
    control/getsavepathdialog.cpp \
    control/peventfilter.cpp \
    control/xmloperations.cpp \
    control/datacontroler.cpp

RESOURCES += qml.qrc \
    resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

OTHER_FILES +=

HEADERS += \
    control/getsavepathdialog.h \
    control/peventfilter.h \
    control/xmloperations.h \
    control/datacontroler.h

lupdate_only{
SOURCES = main.qml \
          FileNameListPanel.qml\
          SavePathPanel.qml\
            SettingSpinBox.qml\
    control/datacontroler.cpp\
    control/getsavepathdialog.cpp
}

TRANSLATIONS = PointPopup_zh_CN.ts
