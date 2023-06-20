
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef CASE_MAP_GIS_SERVICE__H
#define CASE_MAP_GIS_SERVICE__H

#include <QObject>

#include <QMetaType>

#include <QList>

#include <QPoint>

#include <QDialog>
#include <QTableWidget>

#include <functional>

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTabWidget;
class QTextEdit;
class QFrame;
class QHBoxLayout;
class QVBoxLayout;
class QSlider;
class QPlainTextEdit;
class QBoxLayout;
class QButtonGroup;
class QGroupBox;
class QScrollArea;
class QGridLayout;
class QMediaPlayer;
class QProcess;
class QTcpServer;
class QGridLayout;

class ScignStage_Clickable_Label;

class XPDF_Bridge;

class QFormLayout;

class QComboBox;

#include "global-types.h"

class Case_Map_GIS_Service
{
 QString provider_;


public:

 Case_Map_GIS_Service(QString provider);

 QPair<r8, r8> get_city_latitude_and_longitude(QString city, QString state);

};

//_QSNS(ScignStage)


#endif //  CASE_MAP_ENTRY_DIALOG__H



