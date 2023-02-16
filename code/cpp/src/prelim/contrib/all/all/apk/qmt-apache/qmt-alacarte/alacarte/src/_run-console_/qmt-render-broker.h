
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QMT_RENDER_BROKER__H
#define QMT_RENDER_BROKER__H

#include <QString>
#include <QMap>

#include <string>

#include "accessors.h"

#include "global-types.h"

#include <boost/smart_ptr/shared_ptr.hpp>

//#include "../server/http/re

class RequestManager;


class QMT_Render_Broker
{
 QString geodata_file_;

 QString out_file_pattern_;

 QString stylesheet_path_name_;
 QString stylesheet_folder_path_;

 u4 zoom_min_;
 u4 zoom_max_;

 QVector<u4> x_min_;
 QVector<u4> x_max_;

 QVector<u4> y_min_;
 QVector<u4> y_max_;

 boost::shared_ptr<RequestManager> request_manager_;

 QMap<QString, QString> configuration_qmap_;

 void init();

 void re_init();

public:

 QMT_Render_Broker(QString geodata_file, RequestManager* request_manager = nullptr);

 ACCESSORS(QString ,geodata_file)

 ACCESSORS(QString ,out_file_pattern)

 ACCESSORS(QString ,stylesheet_path_name)
 ACCESSORS(QString ,stylesheet_folder_path)

 ACCESSORS(u4 ,zoom_min)
 ACCESSORS(u4 ,zoom_max)

 ACCESSORS(QVector<u4> ,x_min)
 ACCESSORS(QVector<u4> ,x_max)

 ACCESSORS(QVector<u4> ,y_min)
 ACCESSORS(QVector<u4> ,y_max)

 void generate_png();


};


#endif // QMT_RENDER_BROKER__H
