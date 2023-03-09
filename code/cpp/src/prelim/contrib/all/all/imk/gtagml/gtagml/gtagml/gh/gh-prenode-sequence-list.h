

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef GH_PRENODE_SEQUENCE_LIST__H
#define GH_PRENODE_SEQUENCE_LIST__H


#include <QList>
#include <QPair>
#include <QString>


class GH_Prenode_Sequence;

class GH_Prenode_Sequence_List : public QList<QPair<QString, GH_Prenode_Sequence*>>
{
public:

 GH_Prenode_Sequence_List();

 void add_prenode();


};


#endif // GH_PRENODE_SEQUENCE_LIST__H


