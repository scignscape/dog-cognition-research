

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-video-annotation-set.h"

#include "ntxh-parser/ntxh-document.h"

//?
#include <poppler/qt5/poppler-qt5.h>

#include <QtWidgets>
#include <qabstractvideosurface.h>
#include <qvideosurfaceformat.h>

#include "textio.h"

USING_KANS(TextIO)


DHAX_Video_Annotation_Set::DHAX_Video_Annotation_Set()
  :
     circled_text_default_font_size_(12), reffed_annotation_count_(0),
     circled_text_default_width_(0), circled_text_default_border_(2),
     sizes_ratio_x_(0), sizes_ratio_y_(0),
     sizes_ratio_x_adjustment_(0), sizes_ratio_y_adjustment_(0),
     current_pause_annotation_(nullptr),
     template_file_(nullptr)
{
}


void DHAX_Video_Annotation_Set::parse_annotation_settings_hypernode(NTXH_Graph& g, hypernode_type* h)
{
 g.get_sfsr(h, {{1, 6}}, [this](QVector<QPair<QString, void*>>& prs)
 {
  sizes_ratio_x_adjustment_ = prs[0].first.toDouble();
  sizes_ratio_y_adjustment_ = prs[1].first.toDouble();

  smaller_size_x_translation_ = prs[2].first.toShort();
  smaller_size_y_translation_ = prs[3].first.toShort();

  larger_size_x_translation_ = prs[4].first.toShort();
  larger_size_y_translation_ = prs[5].first.toShort();
 });
}


void DHAX_Video_Annotation_Set::check_lighter_darker(QString& text)
{
 static QMap<QString, QString> options {{"~>", "lighter"}, {"=>", "darker"}};

 QMapIterator<QString, QString> it(options);

 QString replacement;
 while(it.hasNext())
 {
  it.next();

  int index = text.indexOf(it.key());
  if(index == -1)
    continue;

  int pre = text.lastIndexOf(':', index);
  int start, end = index + 5;

  if(pre == -1)
    start = index;
  else
  {
   start = pre + 1;
   QColor color;

   QString color_text = text.mid(start, index - 1 - pre);
   QStringList tokens = color_text.split(' ', Qt::SkipEmptyParts);

   if(tokens.size() == 1)
     color = QColor(tokens.first());
   else
   {
    // //  todo: use these for reading the color ...
    if(tokens.value(0) == "float")
      tokens.takeFirst();
    if(tokens.value(0) == "percent")
      tokens.takeFirst();

    if(tokens.size() == 1)
      tokens.push_back(tokens.first());
    if(tokens.size() == 2)
     tokens.push_back(tokens.last());

    color.setRed(tokens.value(0).toUInt());
    color.setGreen(tokens.value(1).toUInt());
    color.setBlue(tokens.value(2).toUInt());
    if(tokens.size() > 3)
      color.setAlpha(tokens.value(3).toUInt());
   }

   index += 2;
   while(text.at(index).isSpace())
   {
    ++index;
    ++end;
   }
   QString post = text.mid(index, 3);

   qDebug() << "color = " << color.name(QColor::HexArgb);

   if(it.value() == "lighter")
     color = color.lighter(post.toUInt());
   else if(it.value() == "darker")
     color = color.darker(post.toUInt());

   replacement = color.name(QColor::HexArgb);
   qDebug() << "replacement = " << replacement;
  }

  text.replace(start, end - start, replacement);
  break;
 }

 if(!replacement.isEmpty())
   check_lighter_darker(text);
}


void DHAX_Video_Annotation_Set::check_text_macro(QString& text, int start)
{
 if(text.midRef(start).startsWith("($"))
   parse_text_macro(text, start);

 // //  these leaves open the possibility
  //    that the ($...) form could return
  //    a [$...] form, which is probably
  //    reasonable ...
 if(text.midRef(start).startsWith("[$"))
   fetch_text_macro(text, start);
}

void DHAX_Video_Annotation_Set::parse_text_macro(QString& text, int start)
{
 int index = text.indexOf(')', 2 + start);
 if(index != -1)
 {
  QString key = text.mid((2 + start), index - (2 + start));
  text_macros_[key] = text.mid(index + 1);
  text = text.mid(0, start) + text.mid(index + 1);
 }
}

void DHAX_Video_Annotation_Set::fetch_text_macro(QString& text, int start)
{
 int index = text.indexOf(']', 2 + start);
 if(index != -1)
 {
  QString key = text.mid(2 + start, index - (2 + start));
  text = text.mid(0, start) + text_macros_[key];
 }
}



void DHAX_Video_Annotation_Set::parse_latex_annotation(DHAX_Video_Annotation& dva, QString text)
{
 int index = text.indexOf(';', 2);
 if(index == -1)
   return;

 QString subfolder_name = text.mid(2, index - 2);
 text = text.mid(index + 1);

 qDebug() << "sn = " << subfolder_name;

 QDir qd(source_folder_);

 QString target_folder = qd.absoluteFilePath("tex-pdf");

 QString path = "%1/%2-%3"_qt.arg(subfolder_name).arg(dva.starting_frame_number()).arg(dva.ending_frame_number());
 qd.mkpath(path);

 QString path1 = path;
 path1.replace('/', '_');

 QString tex_template = qd.absoluteFilePath("tex-template.tex");
 QString sh_template = qd.absoluteFilePath("run-pdflatex-template.sh");

 qd.cd("./" + path);


 QString tex_text, sh_text;
 load_file(tex_template, tex_text);
 load_file(sh_template, sh_text);

 tex_text.replace("%$text$%", text);
 sh_text.replace("%cmd%", PDFLATEX_EXE);
 sh_text.replace("%src%", qd.absoluteFilePath(path1));
 sh_text.replace("%dir%", target_folder);


// path1 += ".tex";

 QString bash_file = qd.absoluteFilePath("run-pdflatex.sh");

 //pdflatex_shell_ =

 save_file(qd.absoluteFilePath(path1 + ".tex"), tex_text);
 save_file(bash_file, sh_text);

 QFile(bash_file).setPermissions(QFileDevice::ReadOwner
   | QFileDevice::WriteOwner | QFileDevice::ExeOwner);

 bash_file.prepend("/bin/sh -x ");

 dva.set_pdflatex_shell(bash_file);

 qd.cd(target_folder);
 dva.set_pdflatex_pdf( qd.absoluteFilePath(path1 + ".pdf") );
 qd.cdUp();
 qd.cd("tex-png");
 dva.set_pdflatex_png( qd.absoluteFilePath(path1 + ".png") );
}


void DHAX_Video_Annotation_Set::compile_latex(QSizeF sz) //QPair<u4, u4> dpis)
{
 for(DHAX_Video_Annotation* dva : latex_annotation_group_)
 {
  QString cmd = dva->get_pdflatex_shell();

  if(QProcess::execute(cmd) < 0)
  {
   qDebug() << "Commmand failed: " << cmd;
   continue;
  }

  QString pdf_path = dva->get_pdflatex_pdf();
  QString png_path = dva->get_pdflatex_png();

  qDebug() << "pdf path = " << pdf_path;

  Poppler::Document* doc = Poppler::Document::load(pdf_path);
  Poppler::Page* page = doc->page(0);

  if(!page)
  {
   qDebug() << "No page ...";
  }
  else
  {
   qDebug() << "Using size: " << sz;

  }

  QString back = dva->inner_style_sheet();

  qDebug() << "back = " << back;

  QColor clr = QColor(back);

  QRgb clr_rgb = clr.rgb();

  QString dpi = dva->element_name();
  QStringList dpis = dpi.split("/");

  qDebug() << "dpis = " << dpis;

  r4 dpi_array[4] = {dpis.value(0).toFloat(),
    dpis.value(1).toFloat(), dpis.value(2).toFloat(), dpis.value(3).toFloat() };

  for(u1 a = 1; a < 4; ++a)
    if(dpi_array[a] == 0)
      dpi_array[a] = dpi_array[a - 1];

  QImage image = page->renderToImage(dpi_array[0], dpi_array[1], 0, 0, sz.width(), sz.height());

  //image = image.createMaskFromColor(clr.rgb(), Qt::MaskInColor);

  QImage image1(image.width(), image.height(), QImage::Format_ARGB32);
  image1.fill(Qt::transparent);

  for(int j = 0; j < image.height(); ++j)
  {
   QRgb* scanline = (QRgb*) image.scanLine(j);
   QRgb* scanline1 = (QRgb*) image1.scanLine(j);
   for(int i = 0; i < image.width(); ++i)
   {
    QRgb pixel = scanline[i];
    if(pixel != clr_rgb)
      scanline1[i] = pixel;
   }
  }


  image1.save(png_path);
  image.save(png_path + "x.png");

 }
}



//void DHAX_Video_Annotation_Set::parse_text_annotation_hypernode(NTXH_Graph& g, hypernode_type* h)
//{
// g.get_sfsr(h, {{1, 7}}, [this](QVector<QPair<QString, void*>>& prs)
// {

//  DHAX_Video_Annotation dva;
//  dva.set_kind("text");

//  QString en = prs[2].first;
//  check_text_macro(en);

//  int index = en.indexOf('+');
//  {
//   if(index != -1)
//   {
//    QString ien = en.mid(index + 1).trimmed();
//    en = en.mid(0, index).trimmed();
//    index = ien.indexOf('|');
//    if(index != -1)
//    {
//     QString inner_bkg = ien.mid(index + 1).trimmed();
//     ien = ien.mid(0, index).simplified();
//     inner_bkg.replace(' ', "");
//     check_text_macro(inner_bkg, 0, 1);
//     dva.set_inner_element_background_color(inner_bkg);
//    }
//    dva.set_inner_element_name(ien);
//   }
//  }

//  index = en.indexOf('@');
//  if(index != -1)
//  {
//   dva.set_font_size(en.mid(index + 1).trimmed());
//   en = en.mid(0, index).trimmed();
//  }
//  dva.set_element_name(en);

//  dva.set_text(prs[3].first);

//  QString iss = prs[4].first;
//  check_text_macro(iss);

//  dva.set_inner_style_sheet(iss);

//  dva.set_corner_position(QPointF{prs[5].first.toFloat(), prs[6].first.toFloat()});
//  dva.finalize_html_text();

//  QString s = prs[0].first;
//  QString e = prs[1].first;
//  if(s.startsWith('!'))
//  {
//   dva.set_ref_id(s.mid(1));

//   // //  convert 10ths of a second to milliseconds
//   dva.set_ref_time_offset(prs[1].first.toUInt() * 100);
//  }
//  else
//  {
//   u4 start = s.toInt();
//   u4 end = e == "*"? INT_MAX : e.toInt();
//   if(e.startsWith('+'))
//     end += start;

//   dva.set_starting_frame_number(start);
//   dva.set_ending_frame_number(end);
//  }

//  load_annotation(dva);

////  QString name_description = prs[0].first;
// });

//}



void DHAX_Video_Annotation_Set::parse_text_annotation_hypernode(NTXH_Graph& g, hypernode_type* h)
{
 g.get_sfsr(h, {{1, 7}}, [this](QVector<QPair<QString, void*>>& prs)
 {
  DHAX_Video_Annotation dva;
  dva.set_kind("text");

  QString en = prs[2].first;
  check_text_macro(en);

  int index = en.indexOf('+');
  {
   if(index != -1)
   {
    QString ien = en.mid(index + 1).trimmed();
    en = en.mid(0, index).trimmed();
    index = ien.indexOf('|');
    if(index != -1)
    {
     QString inner_bkg = ien.mid(index + 1).trimmed();
     ien = ien.mid(0, index).simplified();
     inner_bkg.replace(' ', "");
     check_text_macro(inner_bkg, 0, 1);
     dva.set_inner_element_background_color(inner_bkg);
    }
    dva.set_inner_element_name(ien);
   }
  }

  index = en.indexOf('@');
  if(index != -1)
  {
   dva.set_font_size(en.mid(index + 1).trimmed());
   en = en.mid(0, index).trimmed();
  }
  dva.set_element_name(en);

  QString text = prs[3].first;

  QVector<DHAX_Video_Annotation*>* group = nullptr;

  if(text.startsWith("@@"))
  {
   parse_latex_annotation(dva, text);
   group = &latex_annotation_group_;
  }
  else
    dva.set_text(text);

  QString iss = prs[4].first;
  check_lighter_darker(iss);
  check_text_macro(iss);

  dva.set_inner_style_sheet(iss);

  dva.set_corner_position(QPointF{prs[5].first.toFloat(), prs[6].first.toFloat()});
  dva.finalize_html_text();

  QString s = prs[0].first;
  QString e = prs[1].first;
  if(s.startsWith('!'))
  {
   dva.set_ref_id(s.mid(1));

   // //  convert 10ths of a second to milliseconds
   dva.set_ref_time_offset(prs[1].first.toUInt() * 100);
  }
  else
  {
   u4 start = s.toInt();
   u4 end = e == "*"? INT_MAX : e.toInt();
   if(e.startsWith('+'))
     end += start;

   dva.set_starting_frame_number(start);
   dva.set_ending_frame_number(end);
  }


//  if(group)
    load_annotation(dva, group);

//  else
//    load_annotation(dva);

//  QString name_description = prs[0].first;
 });

}


void DHAX_Video_Annotation_Set::parse_pause_annotation_hypernode(NTXH_Graph& g, hypernode_type* h)
{
 g.get_sfsr(h, {{1, 3}}, [this](QVector<QPair<QString, void*>>& prs)
 {
  DHAX_Video_Annotation dva;
  dva.set_starting_frame_number(prs[0].first.toInt());

  QString id = prs[1].first;

  if(id.startsWith("+"))
  {
   QString key = id.mid(1);
   u4 val = ++auto_ids_[key];
   id += QString::number(val);
  }

  dva.set_id(prs[1].first);
  dva.set_pause_time(prs[2].first.toInt() * 100);
  dva.set_kind("pause");
  load_annotation(dva);

//  QString name_description = prs[0].first;
 });

}

void DHAX_Video_Annotation_Set::parse_circled_text_default_hypernode(NTXH_Graph& g, hypernode_type* h)
{
 g.get_sfsr(h, {{1, 15}}, [this](QVector<QPair<QString, void*>>& prs)
 {
  circled_text_default_font_size_ = prs[13].first.toFloat();
  circled_text_default_border_ = prs[14].first.toInt();
  circled_text_default_width_ = prs[0].first.toInt();

#define _PRS_(x)     prs[x].first.toUInt()
  circled_text_default_background_color_ = QColor(
    _PRS_(1), _PRS_(2), _PRS_(3), _PRS_(4));
  circled_text_default_foreground_color_ = QColor(
    _PRS_(5), _PRS_(6), _PRS_(7), _PRS_(8));
  circled_text_default_outline_color_ = QColor(
    _PRS_(9), _PRS_(10), _PRS_(11), _PRS_(12));
 });
}

void DHAX_Video_Annotation_Set::parse_circled_text_annotation_hypernode(NTXH_Graph& g, hypernode_type* h)
{
 g.get_sfsr(h, {{1, 6}}, [this](QVector<QPair<QString, void*>>& prs)
 {
  u4 start = prs[0].first.toUInt();
  u4 end = prs[1].first.toUInt();
  if(prs[1].first.startsWith('+'))
    end += start;

  DHAX_Video_Annotation dva;
  dva.set_kind("circled");

  dva.set_text(prs[2].first);
  dva.set_starting_frame_number(start);
  dva.set_ending_frame_number(end);
  dva.set_corner_position(QPointF{prs[3].first.toFloat(), prs[4].first.toFloat()});

  if(!prs[5].first.isEmpty())
    dva.set_pause_time(prs[5].first.toUInt());

  load_annotation(dva);
 });
}

void DHAX_Video_Annotation_Set::parse_graphic_annotation_hypernode(NTXH_Graph& g, hypernode_type* h)
{

}

void DHAX_Video_Annotation_Set::parse_shape_annotation_hypernode(NTXH_Graph& g, hypernode_type* h)
{
 g.get_sfsr(h, {{1, 5}}, [this](QVector<QPair<QString, void*>>& prs)
 {
  u4 start = prs[1].first.toUInt();
  u4 end = prs[2].first.toUInt();
  if(prs[2].first.startsWith('+'))
    end += start;

//?  QString data64 = prs[5].first;

  DHAX_Video_Annotation dva;
  dva.set_kind(prs[0].first);
  dva.set_starting_frame_number(start);
  dva.set_ending_frame_number(end);
  dva.set_kv_text(prs[3].first);
  dva.set_data64(prs[4].first);
  load_annotation(dva);

//  QString name_description = prs[0].first;
 });

}

DHAX_Video_Annotation_Set* DHAX_Video_Annotation_Set::reinit_and_delete()
{
 DHAX_Video_Annotation_Set* result = new DHAX_Video_Annotation_Set();
 result->template_file_ = template_file_;
 result->sizes_ratio_x_ = sizes_ratio_x_;
 result->sizes_ratio_y_ = sizes_ratio_y_;
 // //  note we're copying the forward to the backward ...
 result->carried_items_backward_ = carried_items_forward_;
 delete this;
 return result;
}


void DHAX_Video_Annotation_Set::read_ntxh_hypernode(NTXH_Graph& g, hypernode_type* h)
{
 QString ty = h->type_descriptor().first;

// typedef void (DHAX_Video_Annotation_Set::*fn_type)();
// fn_type fn = &DHAX_Video_Annotation_Set::parse_text_annotation_hypernode;

 static QMap<QString, void (DHAX_Video_Annotation_Set::*)
   (NTXH_Graph&, hypernode_type*)> static_map
 {
#define TEMP_MACRO(x, y) {#x, &DHAX_Video_Annotation_Set::y},
  TEMP_MACRO(Text_Annotation, parse_text_annotation_hypernode)
  TEMP_MACRO(Pause_Annotation, parse_pause_annotation_hypernode)
  TEMP_MACRO(Shape_Annotation, parse_shape_annotation_hypernode)
  TEMP_MACRO(Graphic_Annotation, parse_graphic_annotation_hypernode)

  TEMP_MACRO(Circled_Text_Default,  parse_circled_text_default_hypernode)
  TEMP_MACRO(Circled_Text_Annotation,  parse_circled_text_annotation_hypernode)
  TEMP_MACRO(Annotation_Settings,  parse_annotation_settings_hypernode)
#undef TEMP_MACRO
 };

 auto it = static_map.find(ty);
 if(it != static_map.end())
   (this->**it)(g, h);

// if(ty == "Text_Annotation")
//   parse_text_annotation_hypernode(g, h);

// else if(ty == "Shape_Annotation")
//   parse_shape_annotation_hypernode(g, h);

// else if(ty == "Circled_Text_Default")
//   parse_circled_text_default_hypernode(g, h);

// else if(ty == "Circled_Text_Annotation")
//   parse_circled_text_annotation_hypernode(g, h);

// else if(ty == "Annotation_Settings")
//   parse_annotation_settings_hypernode(g, h);

}

void DHAX_Video_Annotation_Set::clear_end_frame_data()
{
 end_frame_data_.clear();
}

void DHAX_Video_Annotation_Set::clear_scene_and_end_frame_data()
{
 clear_scene_data();
 clear_end_frame_data();
}

void DHAX_Video_Annotation_Set::clear_scene_data()
{
 QMutableMapIterator<s4, DHAX_Video_Annotation> it(*this);

 while(it.hasNext())
 {
  it.next();
  DHAX_Video_Annotation& dva = it.value();
  dva.set_scene_data(nullptr);
 }
}


void DHAX_Video_Annotation_Set::prepare_template_text()
{
 QMutableMapIterator<s4, DHAX_Video_Annotation> it(*this);

 while(it.hasNext())
 {
  it.next();
  DHAX_Video_Annotation& dva = it.value();
  dva.prepare_template_text();
 }
}

void DHAX_Video_Annotation_Set::update_template_text(const QVector<QPair<QString, QString>>& substitutions)
{
 QMutableMapIterator<s4, DHAX_Video_Annotation> it(*this);

 while(it.hasNext())
 {
  it.next();
  DHAX_Video_Annotation& dva = it.value();
  for(auto pr : substitutions)
  {
   dva.check_substitution("%%1%"_qt.arg(pr.first), pr.second);
  }

 }
}

void DHAX_Video_Annotation_Set::load_annotation_template_file()
{
 load_annotation_file(*template_file_);
 prepare_template_text();
}

void DHAX_Video_Annotation_Set::update_template_text(QString file_path)
{
 if(file_path.startsWith("*"))
 {
  update_template_text({{"file", file_path.mid(1)}});
  return;
 }
}

void DHAX_Video_Annotation_Set::load_annotation_file(QString file_path)
{
 source_file_ = file_path;

 QFileInfo qfi(source_file_);
 source_folder_ = qfi.absolutePath();

 NTXH_Document doc(file_path);

 doc.parse();

 typedef NTXH_Graph::hypernode_type hypernode_type;

 NTXH_Graph& g = *doc.graph();
 const QVector<hypernode_type*>& v = g.hypernodes();

 for(hypernode_type* h : v)
 {
  read_ntxh_hypernode(g, h);
 }


}

void DHAX_Video_Annotation_Set::load_annotation(const DHAX_Video_Annotation& dva,
  QVector<DHAX_Video_Annotation*>* group)
{
 if(dva.ref_id().isEmpty())
 {
  (*this)[dva.starting_frame_number()] = dva;

  DHAX_Video_Annotation* copied_dva = &(*this)[dva.starting_frame_number()];

  if(!dva.id().isEmpty())
    annotations_by_id_[dva.id()] = copied_dva;

  if(group)
    group->push_back(copied_dva);

 }
 else
 {
  --reffed_annotation_count_;
  (*this)[reffed_annotation_count_] = dva;
  DHAX_Video_Annotation* copied_dva = &(*this)[reffed_annotation_count_];
  if(DHAX_Video_Annotation* ref = annotations_by_id_.value(dva.ref_id()))
  {
   copied_dva->set_ref_annotation(ref);
   anchored_ref_annotations_[ref].insert(copied_dva);
  }
 }
}


void DHAX_Video_Annotation_Set::load_sample_annotations()
{
 DHAX_Video_Annotation dva;
 dva.set_text("TEST");
 dva.set_inner_style_sheet("color:red");
 dva.set_starting_frame_number(100);
 dva.set_ending_frame_number(300);
 dva.set_corner_position(QPointF{100, 100});
 dva.finalize_html_text();
 load_annotation(dva);
}

QPair<void*, void*> DHAX_Video_Annotation_Set::get_data_by_end_frame(u4 key)
{
 auto it = end_frame_data_.find(key);
 if(it == end_frame_data_.end())
   return {nullptr, nullptr};
 return it->value(0);
}

void DHAX_Video_Annotation_Set::set_end_frame_data(u4 key, void* data1, void* data2)
{
 end_frame_data_[key].push_back({data1, data2});
}

void DHAX_Video_Annotation_Set::set_end_frame_data(u4 key, DHAX_Video_Annotation& dva)
{
 set_end_frame_data(key, dva.scene_type_data(), dva.scene_data());
}


DHAX_Video_Annotation* DHAX_Video_Annotation_Set::get_annotation_by_start_frame(u4 key)
{
 auto it = find(key);
 if(it == end())
   return nullptr;
 return &it.value();
}
