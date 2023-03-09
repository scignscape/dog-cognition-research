

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef GH_BLOCK_STANDARD_8BIT__H
#define GH_BLOCK_STANDARD_8BIT__H

#include "gh-block-base.h"

#include "global-types.h"

#include <QVector>

class GH_Glyphdeck_Standard_8bit;
class GH_Block_Parse_Mode;

class GH_Block_Standard_8bit : public GH_Block_Base
{
 QVector<u1> chars_;

 u4 current_index_;

 GH_Glyphdeck_Standard_8bit* glyphdeck_;

 GH_Block_Parse_Mode* parse_mode_;




public:

 GH_Block_Standard_8bit();


 n8 get_default_null() Q_DECL_OVERRIDE;

 u4 clear_to_sentence_start(u4 pre, u4 start) Q_DECL_OVERRIDE;

 void swap_codes(u4 i, n8 oldc, n8 newc) Q_DECL_OVERRIDE;

 n8 get_glyph_point_at_index(u4 i) Q_DECL_OVERRIDE;
 SDI_Interpretation_Codes get_sdi_interpretation_code_at_index(u4 i) Q_DECL_OVERRIDE;
 QPair<u4, u4> get_effective_start_and_end_indices() Q_DECL_OVERRIDE;

 u4 check_confirm_sentence_end(u4 i, u4 e) Q_DECL_OVERRIDE;
 u4 get_declared_sentence_end_space(u4 i, u4 e) Q_DECL_OVERRIDE;

 u4 find_sentence_start_resume(u4 i, u4 e) Q_DECL_OVERRIDE;

 u4 check_declared(u1 gp) Q_DECL_OVERRIDE;

 void flag_as_sentence_end(u4 se, u4 sse,
   QPair<QPair<n8, n8>, QPair<n8, n8>>& r) Q_DECL_OVERRIDE;

 void write(QString text, QString block_ws, QPair<u4, u4>& result,
   QVector<u4>* special_flag_marks = nullptr) Q_DECL_OVERRIDE;

 void write(QByteArray& text, QString block_ws, QPair<u4, u4>& result,
   QVector<u4>* special_flag_marks = nullptr);

 void write_boundary_whitespace(QString bws) Q_DECL_OVERRIDE;


 QString get_latex_out(const QPair<u4, u4>& indices) Q_DECL_OVERRIDE;

 QString get_latex_representation(u4 index) Q_DECL_OVERRIDE;
 QString get_xml_representation(u4 index) Q_DECL_OVERRIDE;
 QChar get_qchar_representation(u4 index, QString& alternate) Q_DECL_OVERRIDE;
 QString get_qstring_representation(u4 index) Q_DECL_OVERRIDE;

 QString get_latex_supplement(u4 index);

 void write_to_file(QString path) Q_DECL_OVERRIDE;


};


#endif // GH_BLOCK_STANDARD_8BIT__H


