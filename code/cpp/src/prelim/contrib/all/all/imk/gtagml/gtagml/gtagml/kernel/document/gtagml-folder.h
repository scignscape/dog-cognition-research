
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GTAGML_FOLDER__H
#define GTAGML_FOLDER__H

#include <QString>
#include <QStringList>

#include <QMap>

#include <functional>

#include "accessors.h"
#include "flags.h"

#include "relae-graph/relae-caon-ptr.h"

#include "kans.h"

KANS_(GTagML)

class GTagML_Graph;
class GTagML_Parser;
class GTagML_Graph_Build;
class GTagML_Grammar;
class GTagML_Annotation_Tile;
class GTagML_Project_Info;


class GTagML_Folder
{
 QString first_file_path_;
 QString man_path_;

 QString local_path_;
 QString output_path_;
 QString input_path_;

 QString latex_path_;
 QString latex_code_;

 QMap<QString, int> user_highlights_;
 QMap<QString, caon_ptr<GTagML_Annotation_Tile>> annotations_;

 QMap<QString, QString> file_list_output_;
 QMap<QString, QString> partials_codes_;
 QMap<QString, QString> non_partials_codes_;

 GTagML_Project_Info* project_info_;

public:

 GTagML_Folder(QString local_path = QString());
 GTagML_Folder(QString local_path, QString first_file_path, 
   QString man_path);


 ACCESSORS(QString ,local_path)
 ACCESSORS(QString ,first_file_path)
 ACCESSORS(QString ,man_path)
 ACCESSORS(GTagML_Project_Info* ,project_info)

 void convert_all_files();
 void convert_all_files(QString output_path, QString khif_path = QString());

 void convert_all_files(void(*fn)(QString,
   GTagML_Project_Info*, GTagML_Folder*));


 void read_output_path(QString document_file);
 void display_user_highlights();

 void get_gtagml_files(QStringList& result, QString first_file);

 void convert_to_latex(std::function<void(QString)> fn);

 void convert_to_latex();

// void convert_all_khif_files(QString khif_dir, QString html_dir);

 void output_file_list(QString& result, const QMap<QString, QString>& file_kind);

 QString partials_codes_to_lisp();
 QString output_file_list();

};

_KANS(GTagML)

#endif
