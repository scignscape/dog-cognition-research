

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gh-block-standard-8bit.h"

#include "gh-block-parse-mode.h"

#include "glyphdeck/gh-glyphdeck-standard-8bit.h"

#include <QTextStream>
#include <QFile>


GH_Block_Standard_8bit::GH_Block_Standard_8bit()
 :  current_index_(1), glyphdeck_(new GH_Glyphdeck_Standard_8bit)
    //parse_mode_(new GH_Block_Parse_Mode(247))
{
 parse_mode_ = new GH_Block_Parse_Mode(glyphdeck_->get_default_null());
 chars_.push_back(glyphdeck_->get_default_void_separator());
 chars_.push_back(glyphdeck_->get_default_void_separator());
}


void GH_Block_Standard_8bit::write_to_file(QString path)
{
 QFile outfile(path);
 if (!outfile.open(QIODevice::WriteOnly))
   return;

 QTextStream qts(&outfile);

 QString multichar;
 for(u1 ch : chars_)
 {
  char c = glyphdeck_->get_simple_encoding(ch, multichar);
  if(c)
    qts << QChar::fromLatin1(c);
  else
  {
   qts << multichar;
   multichar.clear();
  }
 }

}


n8 GH_Block_Standard_8bit::get_glyph_point_at_index(u4 i)
{
 if(i > chars_.size())
   return chars_.value(0, glyphdeck_->get_default_null());
 return chars_.at(i);
}


u4 GH_Block_Standard_8bit::check_declared(u1 gp)
{
 return glyphdeck_->check_declared(gp);
}


u4 GH_Block_Standard_8bit::find_sentence_start_resume(u4 i, u4 e)
{
 if(e == 0)
   e = chars_.size() - 1;

 for(u4 u = i; u <= e; ++u)
 {
  n8 uu = get_glyph_point_at_index(u);
  GH_Block_Base::Evaluation_Codes ec = glyphdeck_->check_confirm_sentence_resume(uu);
  if(ec == GH_Block_Base::Evaluation_Codes::Confirm)
    return i;
 }
 return 0;
}

u4 GH_Block_Standard_8bit::get_declared_sentence_end_space(u4 i, u4 e)
{
 for(u4 u = i; u <= e; ++u)
 {
  n8 uu = get_glyph_point_at_index(u);
  GH_Block_Base::Evaluation_Codes ec = glyphdeck_->check_confirm_sentence_end(uu, false);
  if(ec == GH_Block_Base::Evaluation_Codes::Confirm_Via_Declared
   // // ok?
     || ec == GH_Block_Base::Evaluation_Codes::Confirm_Via_Declared_Suspend
     )
    return i;
 }
 return 0;
}

u4 GH_Block_Standard_8bit::check_confirm_sentence_end(u4 i, u4 e)
{
 bool have_space = false;
 u4 neutral_count = 0;
 for(u4 u = i; u <= e; ++u)
 {
  n8 uu = get_glyph_point_at_index(u);
  GH_Block_Base::Evaluation_Codes ec = glyphdeck_->check_confirm_sentence_end(uu, have_space);
  if(ec == GH_Block_Base::Evaluation_Codes::Space)
  {
   have_space = true;
   continue;
  }
  if(ec == GH_Block_Base::Evaluation_Codes::Neutral)
  {
   ++neutral_count;
   continue;
  }
  if(ec == GH_Block_Base::Evaluation_Codes::Confirm
    //?
    || ec == GH_Block_Base::Evaluation_Codes::Confirm_Via_Declared
    )
    return i + neutral_count;
  if(ec == GH_Block_Base::Evaluation_Codes::Refute)
    return 0;
  if(ec == GH_Block_Base::Evaluation_Codes::Confirm_Via_Declared_Suspend)
    return i + neutral_count;
 }
 return 0;
}

n8 GH_Block_Standard_8bit::get_default_null()
{
 return (n8) glyphdeck_->get_default_null();
}

void GH_Block_Standard_8bit::swap_codes(u4 i, n8 oldc, n8 newc)
{
 // // a swap back can occur even if the swap doesn't actually
  //   change the glyph code (e.g. for a declared se space ...)
 if(oldc == newc)
   return;

 if(chars_[i] == (u1) oldc)
   chars_[i] = (u1) newc;
}

u4 GH_Block_Standard_8bit::clear_to_sentence_start(u4 pre, u4 start)
{
 // // stats at pre and checks that nothing but whitespace
  //   goes until the start ...

 u4 result = 0;
 for(u4 u = pre; u < start; ++u)
 {
  ++result;
  n8 uu = get_glyph_point_at_index(u);
  GH_Block_Base::Evaluation_Codes ec =
    glyphdeck_->check_confirm_clear_inter_sentence_gap(uu);
  if(ec == GH_Block_Base::Evaluation_Codes::Refute)
    return 0;
 }
 return result;
}


//bool GH_Block_Standard_8bit::check_declared(u1 cue)
//{
// return
//}

void GH_Block_Standard_8bit::flag_as_sentence_end(u4 se, u4 sse,
  QPair<QPair<n8, n8>, QPair<n8, n8>>& r)
{
 // // the first pair holds the old value for the sentence end
  //   and then the new value (if it changes otherwide default null).
  //   The second pair holds the old value for the sentence
  //   end space (or default null if there is none)
  //   and the new value (or default null if there is no change).

 u1 dn = get_default_null();
 u1 c1 = chars_[se];
 u4 swap = glyphdeck_->get_sentence_end_swap(c1);
 if(swap == dn)
 {
  r = {{(n8) c1, (n8) dn}, {(n8) dn, (n8)dn}};
  return;
 }
 chars_[se] = swap;
 if(sse == 0)
 {
  r = {{(n8) c1, (n8) swap}, {(n8) dn, (n8)dn}};
  return;
 }
 u1 c2 = chars_[sse];
 u4 sswap = glyphdeck_->get_sentence_end_space_swap(c2);
 if(sswap == dn)
 {
  r = {{(n8) c1, (n8) swap}, {(n8) c2, (n8)dn}};
  return;
 }
 chars_[sse] = sswap;
 r = {{(n8) c1, (n8) swap}, {(n8) c2, (n8)sswap}};
}

GH_Block_Base::SDI_Interpretation_Codes GH_Block_Standard_8bit::get_sdi_interpretation_code_at_index(u4 i)
{
 n8 u = get_glyph_point_at_index(i);
 return glyphdeck_->get_sdi_interpretation_code((u1) u);
}

void GH_Block_Standard_8bit::write(QString text, QString block_ws,
  QPair<u4, u4>& result, QVector<u4>* special_flag_marks)
{
 QByteArray qba = text.toLatin1();
 write(qba, block_ws, result, special_flag_marks);
}

QPair<u4, u4> GH_Block_Standard_8bit::get_effective_start_and_end_indices()
{
 return {2, chars_.size() - 1};
}

QString GH_Block_Standard_8bit::get_latex_supplement(u4 index)
{
 u1 code = chars_[index];
 return glyphdeck_->get_latex_supplement(code, divert_mode_);
}

QString GH_Block_Standard_8bit::get_latex_out(const QPair<u4, u4>& indices)
{
 QString result;
 QTextStream qts(&result);
 for(u4 u = indices.first; u <= indices.second; ++u)
 {
  // first, inserts ...
  QList<QString*> pres = get_pre_insert_as<QString>(u);
  for(QString* pre : pres)
    qts << *pre;

  qts << get_latex_representation(u);
  QString supl = get_latex_supplement(u);
  if(!supl.isEmpty())
    qts << supl; // " " << supl << " ";

  QList<QString*> posts = get_insert_as<QString>(u);
  for(QString* post : posts)
    qts << *post;

 }
 return result;
}

void GH_Block_Standard_8bit::write(QByteArray& text, QString block_ws,
  QPair<u4, u4>& result, QVector<u4>* special_flag_marks)
{
 if(text.isEmpty())
 {
  result.first = current_index_;
  result.second = current_index_ - 1;
  return;
 }
 result.first = current_index_ + 1;
 for(u1 u : text)
 {
  u1 check = parse_mode_->check_hold(u);
  if(check)
  {
   // // todo fewer raw numbers ...
   if(check == 200)
     continue;
   if(check == 80)
     continue;
   if(check > 200)
   {
    check -= 200;
    for(u1 uu = 0; uu < check; ++uu)
    {
     ++current_index_;
     chars_.push_back((u1) parse_mode_->release_glyph_point());
    }
   }
   if(check > 100)
   {
    check -= 100;
    for(u1 uu = 0; uu < check; ++uu)
    {
     ++current_index_;
     QPair<u1, u1> pr;
     parse_mode_->release_cancel_or_alt_char(pr);
     chars_.push_back(glyphdeck_->encode_alt_pair(pr));
    }
   }
   if(check == 100)
     continue;
   if(check > 90)
   {
    if(special_flag_marks)
    {
     // //  we want the *next* index unless mode is 9 ...
     u1 offset = (u1)(check != 99);

     if(special_flag_marks->isEmpty())
     {
      special_flag_marks->push_back((current_index_ + offset)| 0x80000000);
      special_flag_marks->push_back(check - 90);
     }
     else
     {
      u4 sf_index = 0;
      // find sf which is a position
      u4 index_from_end = special_flag_marks->size();
      while(index_from_end > 0)
      {
       --index_from_end;
       u4 sf = special_flag_marks->at(index_from_end);
       if( (sf & 0x80000000) > 0 )
       {
        sf_index = sf & 0x7FFFFFFF;
        break;
       }
      }
      if(sf_index)
      {
       // we've found an index.  Is it current?
       if(sf_index == (current_index_ + offset))//? (current_index_ + 1) )
         special_flag_marks->push_back(check - 90);
       else
       {
        if(check == 99)
          special_flag_marks->push_back( (current_index_ + offset) | 0x80000000);
        else
          special_flag_marks->push_back( (current_index_ + offset) | 0x80000000);
        special_flag_marks->push_back(check - 90);
       }
      }
     }
    }
   }
   if(check == 89)
   {
    ++current_index_;
    u1 uu = glyphdeck_->encode_latin1('^');
    chars_.push_back(uu);
    goto skip_continue;
   }
   continue;
  }
//  parse_mode_->
skip_continue:

  //  switch(parse_mode_)
//  {

//  }
  ++current_index_;
  u1 uu = glyphdeck_->encode_latin1(u);
  chars_.push_back(uu);
 }

 if(!block_ws.isEmpty())
 {
  write_boundary_whitespace(block_ws);
 }

 result.second = current_index_;
}

void GH_Block_Standard_8bit::write_boundary_whitespace(QString bws)
{
 u1 uu = glyphdeck_->get_boundary_whitespace_code(bws);
 if(uu != glyphdeck_->get_default_null())
 {
  ++current_index_;
  chars_.push_back(uu);
 }
}


QString GH_Block_Standard_8bit::get_latex_representation(u4 index)
{
 if(index >= chars_.size())
   return {}; 
 
 u1 code = chars_[index];

 QString result = glyphdeck_->get_latex_representation(code);
 return result;
}

QString GH_Block_Standard_8bit::get_xml_representation(u4 index)
{
 if(index >= chars_.size())
   return {}; 

 u1 code = chars_[index];

 QString result;// = glyphdeck_->get_xml_representation(code);
 return result;
}

QChar GH_Block_Standard_8bit::get_qchar_representation(u4 index, QString& alternate)
{
 if(index >= chars_.size())
   return {}; 

 u1 code = chars_[index];

 QChar result;// = glyphdeck_->get_latex_representation(code);//, alternate);
 return result;
}

QString GH_Block_Standard_8bit::get_qstring_representation(u4 index)
{
 if(index >= chars_.size())
   return {}; 

 u1 code = chars_[index];

 QString result;// = glyphdeck_->get_latex_representation(code);
 return result;
}


