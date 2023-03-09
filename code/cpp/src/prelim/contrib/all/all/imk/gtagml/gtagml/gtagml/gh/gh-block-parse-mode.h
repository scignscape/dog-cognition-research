

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



#ifndef GH_BLOCK_PARSE_MODE__H
#define GH_BLOCK_PARSE_MODE__H

#include "global-types.h"

#include <QPair>
#include <QMap>
#include <QString>
 
#include <QQueue>

class GH_Block_Parse_Mode
{
 u1 hold_state_;
 u1 length_with_hold_state_;
 u1 held_diacritic_cue_;
 u1 held_diacritic_code_;

 QQueue<n8> ready_glyph_points_;
 QQueue<QPair<u1, u1>> cancel_or_alt_chars_;

 u1 null_code_;
 u1 acc_length_;

public:

 GH_Block_Parse_Mode(u1 null_code);

 u1 check_hold(u1 cue);

 QPair<u1, u1> get_diacritic_length(u1 cue);
 u1 get_diacritic_code(u1 cue, u1 length);
 u1 finalize_glyph_points(u1 cue);
 u1 finalize_glyph_points_1(u1 cue);

 n8 release_glyph_point();
 void release_cancel_or_alt_char(QPair<u1, u1>& pr);
};


#endif // GH_BLOCK_PARSE_MODE__H


