
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "ngml-sdi-page.h"

#include "ngml-sdi-mark-base.h"

#include <QTextStream>

#include "global-types.h"

//typedef NTXH_Graph::hypernode_type hypernode_type;

NGML_SDI_Page::NGML_SDI_Page(u4 number)
  :  number_(number)
{
}

void NGML_SDI_Page::add_page_element(NGML_SDI_Mark_Base* mark)
{
 NGML_SDI_Page_Element npe(mark);
 page_elements_.insert(npe);
 //page_elements_.push_back(npe);
}

void NGML_SDI_Page::read_page_element_from_strings(QStringList& strings)
{
 qDebug() << strings;
 NGML_SDI_Mark_Base* mark = new NGML_SDI_Mark_Base;
 NGML_SDI_Page_Element el = NGML_SDI_Page_Element(mark);
 el.read_from_strings(strings);
 page_elements_.insert(el);
 //page_elements_.push_back(el);
 //qDebug() << "SX: " << el.mark()->start_x();
}


void NGML_SDI_Page::check_add_file_id(QString jn, u4 file_id)
{
 for(QPair<QString, QPair<u4, u4>>& pr : job_names_)
 {
  if(pr.first == jn)
  {
   if(pr.second.first == 0)
     pr.second.first = file_id;
   ++pr.second.second;
   continue;
  }
 }
}


void NGML_SDI_Page::check_add_job_name(QString jn)
{
 if(job_names_.isEmpty())
   add_job_name(jn);
 else if(job_names_.last().first != jn)
   add_job_name(jn);
}


void NGML_SDI_Page::add_job_name(QString jn, u4 file_id)
{
 job_names_.push_back({jn, {file_id, 0}});
}


QString NGML_SDI_Page::last_job_name(u4& fid)
{
 if(job_names_.isEmpty())
   return {};
 fid = job_names_.last().second.first;
 return job_names_.last().first;
}


void NGML_SDI_Page::write(QString& contents)
{
 QTextStream qts(&contents);

 for(const QPair<QString, QPair<u4, u4>>& pr : job_names_)
 {
  qts << "= " << pr.first << ' ' << pr.second.first << ' ' << pr.second.second << '\n';
 }

 int c = 0;
 for(const NGML_SDI_Page_Element& el : page_elements_)
 {
  ++c;
  NGML_SDI_Mark_Base& mark = *el.mark();
  
  qts << mark.file_id() << ' ' << mark.id() << ' '
    << mark.get_kind_string() << ' ' << mark.start_index() << ' ' 
    << mark.end_index() << ' ' << mark.start_x() 
    << ' ' << mark.start_y() << ' ' << mark.end_x() 
    << ' ' << mark.end_y() << '\n'; 
 }

 // qDebug() << "Contents " << contents;
}

