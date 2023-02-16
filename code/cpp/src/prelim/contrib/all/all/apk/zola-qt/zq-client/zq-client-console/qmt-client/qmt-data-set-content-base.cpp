
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-data-set-content-base.h"

//#include "MapGraphicsView.h"

#include "global-types.h"

#include <QMessageBox>

#include <QDebug>

#include <QFile>

#include <QVector2D>



QMT_Data_Set_Content_Base::QMT_Data_Set_Content_Base()
{

}


//void QMT_Client_Data_Set::read_ntxh_hypernode(NTXH_Graph& g, hypernode_type* h)
//{
// if(h->type_descriptor().first == "Sighting")
// {
//  qDebug() << "Sighting";
//  g.get_sfsr(h, {{1, 4}}, [this](QVector<QPair<QString, void*>>& prs)
//  {
////   u4 id = prs[0].first.toInt();
////   QString j = prs[1].first;
////   u4 s = prs[2].first.toInt();
////   u4 e = prs[3].first.toInt();
//  });
// }
//}
