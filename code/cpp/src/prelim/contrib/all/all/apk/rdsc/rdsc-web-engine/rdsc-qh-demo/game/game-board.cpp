
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "game-board.h"

#include "game-driver.h"
#include "game-token.h"

#include "textio.h"
USING_KANS(TextIO)

#include "rdsc-2d/mat2d.templates.h"
#include "rdsc-1d/vec1d.h"

#include "rdsc-qh/qh-web-view-dialog.h"



Game_Board::Game_Board(Game_Driver* driver)
  :  driver_(driver), slot_positions_(16, 16, decltype(slot_positions_) ::Fixed_Preinit),
     non_slot_positions_(15, 15, decltype(slot_positions_) ::Fixed_Preinit),
     next_token_number_(0)
{
 for(u1 r = 1, _r = 1; r <= 16; ++r, _r += 2)
  for(u1 c = 0, _c = 1; c < 16; ++c, _c += 2)
  {
   void* pv = slot_positions_.fetch_raw(r, c);
   Game_Position* gp = new (pv) Game_Position(_r, _c);
   game_positions_by_coords_[{_r, _c}] = gp;
   game_positions_by_label_code_[gp->label_code()] = gp;
  }

 for(u1 r = 1, _r = 2; r <= 15; ++r, _r += 2)
  for(u1 c = 1, _c = 2; c <= 15; ++c, _c += 2)
  {
   void* pv = non_slot_positions_.fetch_raw(r, c);
   Game_Position* gp = new (pv) Game_Position(_r, _c);
   game_positions_by_coords_[{_r, _c}] = gp;
   game_positions_by_label_code_[gp->label_code()] = gp;
  }

 // //  init the adjacents

 for(Game_Position* gp : game_positions_by_label_code_.values())
 {
  u1 r = gp->position_row();
  u1 c = gp->position_column();

  gp->set_adjacent_positions(0, game_positions_by_coords_.value({r-1, c-1}));
  gp->set_adjacent_positions(1, game_positions_by_coords_.value({r+1, c-1}));
  gp->set_adjacent_positions(2, game_positions_by_coords_.value({r+1, c+1}));
  gp->set_adjacent_positions(3, game_positions_by_coords_.value({r-1, c+1}));
 }

}


Game_Position* Game_Board::get_game_position_by_label_code(QString lc)
{
 return game_positions_by_label_code_.value(lc);
}

void Game_Board::handle_token_placement(QH_Web_View_Dialog* dlg, Game_Token* token, QString pos_id)
{
 Game_Position* gp = get_game_position_by_label_code(pos_id);

 if(gp)
 {
//   u2 r = gp->position_row();
//   u2 c = gp->position_column();

//  s2 tn = next_token_number();
  QString token_id = token->svg_id();
  QString hide_group;
  QString show_group;
  if(token->south())
  {
   hide_group = "south-adding-text-group";
   show_group = "north-adding-text-group";
  }
  else
  {
   hide_group = "north-adding-text-group";
   show_group = "south-adding-text-group";
  }

  s2 token_mid_offset_x = 25, token_mid_offset_y = 25;

  s2 x = gp->svg_x() + token_mid_offset_x, y = gp->svg_y() + token_mid_offset_y;

  //c * 100, y = r * 100;
  //runJavaScript("position_token('%1', %2, %3);"_qt.arg(id).arg(x).arg(y));

  dlg->run_js_in_current_web_page("show_token_at_position('%1', %2, %3);"_qt.arg(token_id).arg(x).arg(y));
  dlg->run_js_in_current_web_page("hide_svg_element('%1');"_qt.arg(hide_group));
  dlg->run_js_in_current_web_page("show_svg_element('%1');"_qt.arg(show_group));

  increment_next_token_number();
 }
}



void Game_Board::to_svg(QString in_folder, QString out_file)
{
 QDir qd(in_folder);
 QString board_start = load_file(qd.absoluteFilePath("board-start.txt"));
 QString board_end = load_file(qd.absoluteFilePath("board-end.txt"));

// QString svg_text;
 QString main_text;

 u1 slot_width = 50;

 auto squares = [&main_text, slot_width, this]()
 {
  main_text += "\n\n<!-- squares -->\n\n";
  // //  draw squares
  static QString square_css_classes [2] {"dark-square", "light-square"};

  static s1 slot_position_x_offsets[2]{1, 0};
  static s1 slot_position_y_offsets[2]{1, 0};
  s1 slot_width_offset = -1;

  for(u1 r = 0, _r = 31; r < 16; ++r, _r -= 2)
   for(u1 c = 0, _c = 1; c < 16; ++c, _c += 2)
   {
    u1 r_2 = r / 2, c_2 = c / 2, rc_2 = (r_2 % 2) == (c_2 % 2);

    s1 slot_position_x_offset = slot_position_x_offsets[c % 2];
    s1 slot_position_y_offset = slot_position_y_offsets[r % 2];


    Game_Position* gp = game_positions_by_coords_[{_r, _c}];

    s2 svg_x = c * slot_width + slot_position_x_offset;
    s2 svg_y = r * slot_width + slot_position_y_offset;

    gp->set_svg_x(svg_x); gp->set_svg_y(svg_y);


    main_text += R"_(
 <a class="%1" id="%2" onclick="position_clicked(event)">
  <rect x="%3" y="%4" width="%5" height="%5"/>
 </a>
 )_"_qt.arg(square_css_classes[rc_2]).arg(gp->label_code())
     .arg(svg_x)
     .arg(svg_y).arg(slot_width + slot_width_offset);

   }
 };

 auto h_line = [&main_text](QString css_class, u2 x1, u2 x2, u2 y)
 {
  main_text += R"(
<g class='%1'>
 <line x1="%2" y1="%4" x2="%3" y2="%4"/>
</g>)"_qt.arg(css_class).arg(x1).arg(x2).arg(y);
 };

 auto v_line = [&main_text](QString css_class, u2 x, u2 y1, u2 y2)
 {
  main_text += R"(
<g class='%1'>
 <line x1="%2" y1="%3" x2="%2" y2="%4"/>
</g>)"_qt.arg(css_class).arg(x).arg(y1).arg(y2);
 };

 auto slot_borders = [&main_text, slot_width, h_line, v_line]()
 {
  // //  draw slot borders
  main_text += "\n\n<!-- slot borders -->\n\n";

  s1 draw_outer_offset = -9;
  s1 draw_inner_offset = 14;
  s2 draw_width = slot_width + draw_outer_offset;

  for(u2 r = 50; r < 850; r += 100)
  {
   for(u2 c = 50; c < 850; c += 100)
   {
    h_line("slot-border", c - draw_width, c - draw_inner_offset, r);
    h_line("slot-border", c + draw_inner_offset, c + draw_width, r);

    v_line("slot-border", c, r - draw_width, r - draw_inner_offset);
    v_line("slot-border", c, r + draw_inner_offset, r + draw_width);
   }
  }
 };

 auto polygon = [&main_text](QString element_id, QString css_class, u2 x, u2 y, QVector<QPair<s2, s2>> points)
 {
  QVector<QString> points_str(8);

  std::transform(points.begin(), points.end(), points_str.begin(), [x, y](auto pr)
  {
   return "%1,%2"_qt.arg(x + pr.first).arg(y + pr.second);
  });

  main_text += R"(
<a class="%1" id="%2"><g>
 <polygon points="%3"/>
</g></a>)"_qt.arg(css_class).arg(element_id).arg(points_str.toList().join(" "));

 };

 auto init_diamond_octagon_points_vector = [](QVector<QPair<s2, s2>>& vec, s1 ortho_x,
   s1 diag_x, s1 ortho_y = 0, s1 diag_y = 0)
 {
  if(diag_y == 0)
    diag_y = diag_x;
  if(ortho_y == 0)
    ortho_y = ortho_x;

  vec.resize(8);
  vec[0] = {0, -ortho_y};
  vec[2] = {ortho_x, 0};
  vec[4] = {0, +ortho_y};
  vec[6] = {-ortho_x, 0};
  vec[1] = {diag_x, -diag_y};
  vec[3] = {diag_x, diag_y};
  vec[5] = {-diag_x, diag_y};
  vec[7] = {-diag_x, -diag_y};
 };


 auto centers = [&main_text, this, polygon, init_diamond_octagon_points_vector]()
 {
  // //  draw centers
  main_text += "\n\n<!-- centers -->\n\n";

  static s1 visible_ortho_point = 12;
  static s1 visible_diag_point = 5;

  static s1 hidden_ortho_point = 24;
  static s1 hidden_diag_point = 20;

  static QVector<QPair<s2, s2>> visible_points;
  if(visible_points.isEmpty())
  {
   init_diamond_octagon_points_vector(visible_points, visible_ortho_point, visible_diag_point);
  }

  static QVector<QPair<s2, s2>> hidden_points;
  if(hidden_points.isEmpty())
  {
   init_diamond_octagon_points_vector(hidden_points, hidden_ortho_point, hidden_diag_point);
  }

  for(u2 r = 50, _r = 30; r < 850; r += 100, _r -= 4)
  {
   for(u2 c = 50, _c = 2; c < 850; c += 100, _c += 4)
   {
    Game_Position* gp = game_positions_by_coords_[{_r, _c}];

    polygon(gp->label_code() + "-v", "visible-center-polygon", c, r, visible_points);
    polygon(gp->label_code(), "hidden-center-polygon", c, r, hidden_points);
   }
  }
 };

 auto intersections = [&main_text, this, polygon, init_diamond_octagon_points_vector]()
 {
  // //  draw intersections
  main_text += "\n\n<!-- intersections -->\n\n";

  s1 base_x_offset = 0, base_y_offset = 0;
  s1 area_line_offset = -1;


  static s1 visible_ortho_point = 8;
  static s1 visible_diag_point = 4;

  static s1 hidden_ortho_point = 22;
  static s1 hidden_diag_point = 16;

  static QVector<QPair<s2, s2>> visible_points;
  if(visible_points.isEmpty())
  {
   init_diamond_octagon_points_vector(visible_points, visible_ortho_point, visible_diag_point);
  }

  static QVector<QPair<s2, s2>> hidden_points;
  if(hidden_points.isEmpty())
  {
   init_diamond_octagon_points_vector(hidden_points, hidden_ortho_point, hidden_diag_point);
  }

  for(u2 r = 100, _r = 28; r < 800; r += 100, _r -= 4)
  {
   for(u2 c = 100, _c = 4; c < 800; c += 100, _c += 4)
   {
    s1 x_offset = base_x_offset + area_line_offset*(c == 300 || c == 500),
      y_offset = base_y_offset + area_line_offset*(r == 300 || r == 500);

    Game_Position* gp = game_positions_by_coords_[{_r, _c}];

    polygon(gp->label_code() + "-v", "visible-intersection-polygon", c + x_offset, r + y_offset, visible_points);
    polygon(gp->label_code(), "hidden-intersection-polygon", c + x_offset, r + y_offset, hidden_points);
   }
  }
 };

 auto edges = [&main_text, this, polygon, init_diamond_octagon_points_vector]()
 {
  // //  draw edges
  main_text += "\n\n<!-- edges -->\n\n";

  s1 base_x_offset = 0, base_y_offset = 0;
  s1 area_line_offset = -1;


  static s1 visible_ortho_point_y = 1;
  static s1 visible_ortho_point_x = 13;
  static s1 visible_diag_point_x = 15;
  static s1 visible_diag_point_y = 2;

  static s1 hidden_ortho_point_y = 10;
  static s1 hidden_ortho_point_x = 23;
  static s1 hidden_diag_point_x = 25;
  static s1 hidden_diag_point_y = 8;


  static QVector<QPair<s2, s2>> visible_points;
  if(visible_points.isEmpty())
  {
   init_diamond_octagon_points_vector(visible_points, visible_ortho_point_x,
     visible_diag_point_x, visible_ortho_point_y, visible_diag_point_y);
  }

  static QVector<QPair<s2, s2>> hidden_points;
  if(hidden_points.isEmpty())
  {
   init_diamond_octagon_points_vector(hidden_points, hidden_ortho_point_x,
     hidden_diag_point_x, hidden_ortho_point_y,
     hidden_diag_point_y);
  }

  for(u2 r = 100, _r = 28; r < 800; r += 100, _r -= 4)
  {
   for(u2 c = 50, _c = 2; c < 850; c += 100, _c += 4)
   {
    s1 x_offset = base_x_offset,
      y_offset = base_y_offset + area_line_offset*(r == 300 || r == 500);

    Game_Position* gp = game_positions_by_coords_[{_r, _c}];

    polygon(gp->label_code() + "-v", "visible-edge-polygon", c + x_offset, r + y_offset, visible_points);
    polygon(gp->label_code(), "hidden-edge-polygon", c + x_offset, r + y_offset, hidden_points);
   }
  }
 };


 auto sides = [&main_text, this, polygon,
   init_diamond_octagon_points_vector]()
 {
  // //  draw sides
  main_text += "\n\n<!-- sides -->\n\n";

  s1 base_x_offset = 0, base_y_offset = 0;
  s1 area_line_offset = -1;

  static s1 visible_ortho_point_y = 13;
  static s1 visible_ortho_point_x = 1;
  static s1 visible_diag_point_x = 2;
  static s1 visible_diag_point_y = 15;

  static s1 hidden_ortho_point_y = 23;
  static s1 hidden_ortho_point_x = 10;
  static s1 hidden_diag_point_x = 8;
  static s1 hidden_diag_point_y = 25;


  static QVector<QPair<s2, s2>> visible_points;
  if(visible_points.isEmpty())
  {
   init_diamond_octagon_points_vector(visible_points, visible_ortho_point_x,
     visible_diag_point_x, visible_ortho_point_y, visible_diag_point_y);
  }

  static QVector<QPair<s2, s2>> hidden_points;
  if(hidden_points.isEmpty())
  {
   init_diamond_octagon_points_vector(hidden_points, hidden_ortho_point_x,
     hidden_diag_point_x, hidden_ortho_point_y,
     hidden_diag_point_y);
  }

  for(u2 r = 50, _r = 30; r < 850; r += 100, _r -= 4)
  {
   for(u2 c = 100, _c = 4; c < 800; c += 100, _c += 4)
   {
    s1 x_offset = base_x_offset + area_line_offset*(c == 300 || c == 500),
      y_offset = base_y_offset;

    Game_Position* gp = game_positions_by_coords_[{_r, _c}];

    polygon(gp->label_code() + "-v", "visible-side-polygon", c + x_offset, r + y_offset, visible_points);
    polygon(gp->label_code(), "hidden-side-polygon", c + x_offset, r + y_offset, hidden_points);
   }
  }
 };



 u2 board_left_offset = 0;
 u2 total_board_width = 800;

 u2 board_top_offset = 0;
 u2 total_board_height = 800;

 auto gridlines = [&main_text, total_board_width, board_left_offset,
   total_board_height, board_top_offset,
   h_line, v_line]()
 {
  main_text += "\n\n<!-- gridlines -->\n\n";
  // //  draw gridlines
  static QString gridline_css_classes [3] {"", "gridline", "area-gridline"};

  for(u2 r = 100; r < 800; r += 100)
  {
   s1 offset = 1 + ((r == 300) | (r == 500));

//   //Game_Position* gp = game_positions_by_coords_[{_r, _c}];
//    main_text += R"(
//  <g class='%1'>
//   <line x1="0" y1="%2" x2="800" y2="%2"/>
//  </g>)"_qt.arg(gridline_css_classes[offset]).arg(r - offset);

   h_line(gridline_css_classes[offset], board_left_offset,
     board_left_offset + total_board_width, r - offset + 1);

  }

  for(u2 c = 100; c < 800; c += 100)
  {
   s1 offset = 1 + (c == 300 | c == 500);


//    //Game_Position* gp = game_positions_by_coords_[{_r, _c}];
//    main_text += R"(
//  <g class='%1'>
//   <line x1="%2" y1="0" x2="%2" y2="800"/>
//  </g>)"_qt.arg(gridline_css_classes[offset]).arg(c - offset);

    v_line(gridline_css_classes[offset], c - offset + 1,
      board_top_offset, board_top_offset + total_board_height);

  }
 };
  // for(u1 r = 1, _r = 1; r <= 16; ++r, _r += 2)
  //  for(u1 c = 0, _c = 1; c < 16; ++c, _c += 2)
  //  {
  //   Game_Position* gp = game_positions_by_coords_[{_r, _c}];

  //  }

 gridlines(); squares(); slot_borders(); centers(); intersections(); edges(); sides();

 QString tokens_text;
 auto tokens = [&tokens_text, this]()
 {
  for(u1 i = 0; i < 30; ++i)
  {
   QString s_id = "token-s"_qt + QString::number(i);
   QString n_id = "token-n"_qt + QString::number(i);

   driver_->register_new_token(1, s_id);
   driver_->register_new_token(2, n_id);

   tokens_text += R"(
<a class='south-token' id='%1'>
 <circle cx='0' cy='0' r='12' />
</a>

<a class='north-token' id='%2'>
 <circle cx='0' cy='0' r='12' />
</a>
)"_qt.arg(s_id).arg(n_id);
  }
 };

 tokens();

 board_end.replace("%TOKENS%", tokens_text);

 QString svg_text = board_start + main_text + board_end;

 save_file(out_file, svg_text);

}


void Game_Board::debug_board(QString file)
{
 QString summary;

 for(auto [key, gp] : game_positions_by_label_code_.toStdMap())
 //for(Game_Position* gp : game_positions_by_label_code_.values())
 {
  if(key != gp->label_code())
    qDebug() << "Unexpected problem in label code";
  summary += "\n==== "_qt + gp->label_code() + "\n" + gp->summary() + "-----\n";
 }

 save_file(file, summary);

}

