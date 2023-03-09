
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef NGML_SDI_DOCUMENT__H
#define NGML_SDI_DOCUMENT__H

#include "global-types.h"


#include <QDebug>

#include <QTextStream>

#include "ntxh-parser/ntxh-document.h"



#include "kans.h"

//KANS_CLASS_DECLARE(HGDMCore ,NTXH_Graph)
//USING_KANS(HGDMCore)

KANS_CLASS_DECLARE(DGH ,DGH_SDI_Paragraph)
KANS_CLASS_DECLARE(DGH ,DGH_SDI_Sentence)

USING_KANS(DGH)


#include "rzns.h"

//class hypernode_type;
class NGML_SDI_Page;

class NGML_SDI_Document
{
 QString path_;
 QString folder_;
 r8 global_base_line_skip_;// = 12
 r8 global_base_line_stretch_;

 QVector<NGML_SDI_Page*> pages_;

 QString pages_folder_;

 QMap<QPair<QString, u4>, QPair<void*, u4>> open_elements_;

 QString* unzip_folder_;

 QString prelatex_file_path_;

 QMap<QChar, QVector<u4>> prelatex_;

 QString zip_path_;
 QString copy_path_;
 QString unzip_test_path_;

 QStringList prelatex_lines_;

 QMap<QPair<u4, u4>, QPair<QPair<DGH_SDI_Paragraph*, u4>, QPair<u4, u4>>> gh_sdi_sentence_info_;

 QMap<DGH_SDI_Paragraph*, QPair<u4, u4>> gh_sdi_paragraph_info_;

 QMap<QString, QMap<u4, DGH_SDI_Paragraph*>> dgh_paragraphs_;

 QMap<u4, QString> file_job_name_by_file_id_;

 u4 carried_paragraph_id_;
 u4 carried_sentence_id_;

 QStringList prelatex_files_;

 DGH_SDI_Paragraph* current_parse_paragraph_;

 QMap<QString, u4> prelatex_file_ids_;

 QMap<DGH_SDI_Paragraph*, QVector<DGH_SDI_Sentence*>> sentences_;


public:
 
 NGML_SDI_Document(QString path, QString folder);

 ACCESSORS(QString ,zip_path)
 ACCESSORS(QString ,copy_path)
 ACCESSORS(QString ,unzip_test_path)
 ACCESSORS(QString ,pages_folder)

 u4 half_base_line_stretch();
 u4 half_base_line_stretch(n8 bls);
 static u4 half_base_line_stretch(n8 bls, r8 blt);
 static r8 ptstring_to_r8(QString str, r8 default_value = 1.);


 QMap<QChar, QVector<u4>>& review() { return prelatex_; }

 ACCESSORS(r8 ,global_base_line_skip)
 ACCESSORS(r8 ,global_base_line_stretch)

 void load_prelatex_file(QString path);

 void load_prelatex_files(QStringList path);

 void parse();

 void review_dgh();
 void merge_dgh();
 void output_dgh(QString path);

 void parse_paragraph_start_hypernode(NTXH_Graph& g, NTXH_Graph::hypernode_type* hn);
 void parse_paragraph_end_hypernode(NTXH_Graph& g, NTXH_Graph::hypernode_type* hn);

 void parse_sentence_start_hypernode(NTXH_Graph& g, NTXH_Graph::hypernode_type* hn);
 void parse_sentence_end_hypernode(NTXH_Graph& g, NTXH_Graph::hypernode_type* hn);

 void parse_element_start_hypernode(NTXH_Graph& g, NTXH_Graph::hypernode_type* hn);
 void parse_element_end_hypernode(NTXH_Graph& g, NTXH_Graph::hypernode_type* hn);


 void parse_info_hypernode(NTXH_Graph& g, NTXH_Graph::hypernode_type* hn);

 NGML_SDI_Page* get_page(u4 page);

 void output_pages(QStringList htxn_files, QStringList marks_files, QString mergefile = {});

 NGML_SDI_Page* check_read_page(QString zip_file_path, 
   QString unzip_path, QString unzip_folder_name, u4 page_number);

 void check_unzip_folder(QString zip_file_path, 
  QString unzip_path, QString unzip_folder_name);

};


#endif // NGML_SDI_DOCUMENT__H
