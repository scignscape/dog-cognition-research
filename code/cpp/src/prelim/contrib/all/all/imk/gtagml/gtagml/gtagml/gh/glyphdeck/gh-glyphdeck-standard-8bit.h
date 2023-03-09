

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef GH_GLYPHDECK_STANDARD_8BIT__H
#define GH_GLYPHDECK_STANDARD_8BIT__H

#include "gh/gh-block-base.h"

class GH_Glyphdeck_Standard_8bit // : GH_Block_Base 
{

public:

 GH_Glyphdeck_Standard_8bit();

 GH_Block_Base::SDI_Interpretation_Codes get_sdi_interpretation_code(u1 gp);
 GH_Block_Base::Evaluation_Codes check_confirm_sentence_end(u1 gp, bool have_space);
 GH_Block_Base::Evaluation_Codes check_confirm_clear_inter_sentence_gap(u1 gp);
 GH_Block_Base::Evaluation_Codes check_confirm_sentence_resume(u1 gp);

 u4 check_declared(u1 gp);

 u1 get_basic_char(u1 gp);
 u1 get_char_with_diacritic(u1 gp);
 u1 get_non_alphanumeric_char(u1 gp);

 u1 get_sentence_end_swap(u1 gp);
 u1 get_sentence_end_space_swap(u1 gp);

 u1 encode_latin1(u1 cue);
 u1 encode_alt_pair(const QPair<u4, u4>& pr);

 u1 get_default_void_separator();
 u1 get_default_null();

 u1 get_boundary_whitespace_code(QString bws);

 QString get_latex_representation(u1 gp);
 QString get_latex_supplement(u1 gp, GH_Block_Base::Divert_Mode dm);

 QString get_xml_representation(u1 gp);
 QChar get_qchar_representation(u1 gp, QString& alternate);
 QString get_qstring_representation(u1 gp);

 char get_simple_encoding(u1 gp, QString& alternate);


};


#endif // GH_GLYPHDECK_STANDARD_8BIT__H


