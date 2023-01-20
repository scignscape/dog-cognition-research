
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RELAE_GRAMMAR__H
#define RELAE_GRAMMAR__H

#include <functional>
#include <initializer_list>

#include <QRegularExpressionMatch>

#include "relae-regex.h"
#include "flags.h"

#ifndef RZ_MATCH_CALLBACK
#define RZ_MATCH_CALLBACK std::function<void()>
#endif

template<typename GRAPH_Type,
 typename PARSER_Type = typename GRAPH_Type::Parser_type>
class Relae_Grammar
{
 typedef GRAPH_Type tGraph;
 typedef PARSER_Type tParser;

 typedef RZ_Core_Rule tRule;

public:
 struct Context
 {
  unsigned short index;
  float weight;
  unsigned short depth_mark;
  Context(unsigned short i = 0, float w = 0):index(i),weight(w),depth_mark(0){}
  Context(const Context& lhs):index(lhs.index),weight(lhs.weight),depth_mark(lhs.depth_mark)
  {

  }

  template<typename T>
  inline bool above(const T& t = 0) const
  {
   return weight > t;
  }

  template<typename T>
  inline bool fail(const T& t) const
  {
   return weight < t;
  }

  inline bool fail() const
  {
   //? OK?
   if(index == 0)
    return false;
   //?
   return weight < 1;
  }

  inline operator bool() const
  {
   return !fail();
  }
 };

private:
 QVector<tRule*> rules_;
 QMap<QString, tRule*> rule_names_;
 QMap<QString, QString> pre_rule_strings_;

 // For special named captures syntax
 QMap<QString, int> capture_name_map_;

 QMap<QString, unsigned short> context_names_;

 QMap<tRule*, Flag_or_Depth*> condition_dependencies_;

 QMap<tRule*, Flag_or_Depth*> negated_condition_dependencies_;

 QMap<tRule*, unsigned short> context_dependencies_;

 QMap<tRule*, RZ_Flag_Test*> flag_tests_;

 void flag_test_map(tRule* r, RZ_Flag_Test* test)
 {
  flag_tests_[r] = test;
 }

 void flag_test_map(QString s, RZ_Flag_Test* test)
 {
  if( rule_names_.find(s) != rule_names_.end() )
    flag_test_map(rule_names_[s], test);
 }

 QVector<Context> context_vector_;

 QVector< QVector<unsigned short> > context_triggers_;

 unsigned short active_context_index_;
 const Context* rule_context_;

 QVector<Context*> context_ptr_vector_;

 // Casting Flag_or_Depth* pointers to this struct is merely a flag
 // to indicate that the rule using the pointer should test the
 // negation of the value; cf. negated_condition_dependencies[].
 struct Negated_Flag_or_Depth
 {
  Flag_or_Depth* negative;
  explicit Negated_Flag_or_Depth(Flag_or_Depth* fod):negative(fod){}
  Negated_Flag_or_Depth() = delete;
  Negated_Flag_or_Depth(const Negated_Flag_or_Depth& rhs) = default;
  Negated_Flag_or_Depth& operator=(const Negated_Flag_or_Depth& rhs) = default;
  Flag_or_Depth* as_Flag_or_Depth_ptr()
  {
   return negative;
  }
 };

 typedef Negated_Flag_or_Depth negated;

 void context_map(QString name, const Context& context)
 {
  context_dependencies_.insert(rule_names_[name], context.index);
 }

 void condition_map(QString name, Flag_or_Depth* flag_or_depth)
 {
  condition_dependencies_.insert(rule_names_[name], flag_or_depth);
 }

 void negated_condition_map(QString name, Flag_or_Depth* flag_or_depth)
 {
  negated_condition_dependencies_.insert(rule_names_[name], flag_or_depth);
 }

public:

 Relae_Grammar():active_context_index_(0),rule_context_(0)
 {
  add_context("<root>");
  activate_context(0);
 }


 Context add_context(QString s)
 {
  if(context_names_.find(s) != context_names_.end())
//   return context_names.at(s);
    return context_names_[s];
  Context result = Context(context_vector_.size());
  context_vector_.push_back(result);
  context_ptr_vector_.push_back(nullptr);
  context_triggers_.push_back( QVector<unsigned short>() );
// context_names.insert({s, result});
  context_names_[s] = result.index;
  return result;
 }

 void track_context(std::initializer_list<Context*> clist)
 {
  for(Context* c : clist)
  {
   context_ptr_vector_[c->index] = new Context(*c);//c;
  }
 }

 void cancel_context_ptr(unsigned short index, float w = 0)
 {
  if(Context* c = context_ptr_vector_[index] )
    c->weight = w;
 }

 Context add_context(QString s, std::initializer_list<Context> clist)
 {
  Context result = add_context(s);

  for(Context c : clist)
  {
   context_triggers_[result.index].push_back(c.index);
  }

  return result;
 }

 void activate(QString s, float weight = 1)
 {
  activate_context(s, weight);
  active_context_index_ = context_names_[s];
 }

 void activate_context(QString s, float weight = 1)
 {
  activate_context(context_names_[s], weight);
 }

 void activate_context(unsigned short s, float weight = 1, bool reset = true)
 {
  if(reset)
  {
   for(int i = 0; i < context_vector_.size(); ++i)
    context_vector_[i].weight = 0;
  }
  context_vector_[s].weight = weight;
  QVectorIterator<unsigned short> triggers(context_triggers_[s]);
  while (triggers.hasNext())
  {
   this->activate_context(triggers.next(), weight, false);
  }
 }

 void activate(Context& c, float w = 1)
 {
  c.weight = w;
  activate_context(c.index);
  active_context_index_ = c.index;
 }

 void activate(const Context& c, float w = 1)
 {
  Context* pc = context_ptr_vector_[c.index];
  if(pc)
    activate(*pc, w);
  else
  {
   activate_context(c.index);
   active_context_index_ = c.index;
  }
 }

 void check_activate_with_depth_mark(const Context& c, const Context& cc,
   unsigned short dm, float w = 1)
 {
  Context* pcc = context_ptr_vector_[cc.index];
  if(pcc)
  {
   if(pcc->depth_mark == dm)
   {
    pcc->depth_mark = 0;
    activate(c, w);
   }
  }
 }


 void activate_with_depth_mark(Context& c, unsigned short dm, float w = 1)
 {
  c.weight = w;
  c.depth_mark = dm;
  activate_context(c.index);
  active_context_index_ = c.index;
 }

 void activate_with_depth_mark(const Context& c, unsigned short dm, float w = 1)
 {
  Context* pc = context_ptr_vector_[c.index];
  if(pc)
  {
   activate_with_depth_mark(*pc, dm, w);
  }
  else
  {
   activate_context(c.index);
   active_context_index_ = c.index;
  }
 }

 void cancel_context(QString s, float w = 0)
 {
  Context(context_names_[s]).weight = w;
 }

 void cancel_context(Context& c, float w = 0)
 {
  c.weight = w;
 }

 void cancel_context(unsigned short index, float w = 0)
 {
  cancel_context(context_vector_[index], w);
 }

 void switch_to_context(QString s, float w2 = 1, float w1 = 0)
 {
  cancel_context(active_context_index_, w1);
  cancel_context_ptr(active_context_index_, w1);
  activate(s, w2);
 }

 void switch_to_context(Context& c, float w2 = 1, float w1 = 0)
 {
  cancel_context(active_context_index_, w1);
  cancel_context_ptr(active_context_index_, w1);
  activate(c, w2);
 }

 void swap_context(QString s1, QString s2, float w1 = 0, float w2 = 1)
 {
  cancel_context(s1, w1);
  activate(s2, w2);
 }

 void swap_context(Context& c1, Context& c2, float w1 = 0, float w2 = 1)
 {
  cancel_context(c1, w1);
  activate(c2, w2);
 }

 bool check_context(Context& c)
 {
  return c;
 }

 bool check_context(QString s)
 {
  return context_names_[s];
 }

 void pre_rule(QString name, QString expr)
 {
  pre_rule_strings_[name] = expr;
 }

 void add_rule(QString name, tRule* r)
 {
  r->capture_name_map = capture_name_map_;
  capture_name_map_.clear();
  rules_.push_back(r);
  rule_names_[name] = r;
 }

 // By default assume rules are compound anchored regexes: in other words,
 // a preprocessor will map .rule-name structures to (\g<rule-name>), with
 // (?<rule-name> ... ){0} in the prelim for ... replaced with the contents
 // of a previously named rule added to the grammar.
 void add_rule(QString name, QString rx, RZ_MATCH_CALLBACK block) //RZ_MATCH_CALLBACK block)
 {
  add_compound_anchored_rule(name, rx, block);// static_cast<RZ_MATCH_CALLBACK>( block ) );
 }

 void add_rule(Context& c, QString name, QString rx, RZ_MATCH_CALLBACK block) //CALLBACK_Type ct)
 {
  add_rule(name, rx, block);
  context_map(name, c);
 }

 void add_rule( RZ_Flag_Test&& flag_test, QString name, QString rx, RZ_MATCH_CALLBACK block) //CALLBACK_Type ct)
 {
  add_rule(name, rx, block);

  void* mem = malloc( sizeof(RZ_Flag_Test) );
  RZ_Flag_Test* ptr = (RZ_Flag_Test*) mem;
   *ptr = std::move(flag_test);


  flag_test_map(name, ptr );
 }

 void add_rule( RZ_Flag_Test&& flag_test, Context& c, QString name, QString rx, RZ_MATCH_CALLBACK block) //CALLBACK_Type ct)
 {
  add_rule(c, name, rx, block);

  void* mem = malloc( sizeof(RZ_Flag_Test) );
  RZ_Flag_Test* ptr = (RZ_Flag_Test*) mem;
   *ptr = std::move(flag_test);


  flag_test_map(name, ptr );
 }


 void add_rule(Flag_or_Depth* flag_or_depth, QString name, QString rx, RZ_MATCH_CALLBACK block) //CALLBACK_Type ct)
 {
  add_rule(name, rx, block);
  condition_map(name, flag_or_depth);
 }

 void add_rule(Flag_or_Depth* flag_or_depth, Context& c, QString name, QString rx, RZ_MATCH_CALLBACK block) //CALLBACK_Type ct)
 {
  add_rule(name, rx, block);
  context_map(name, c);
  condition_map(name, flag_or_depth);
 }

 void add_rule(Negated_Flag_or_Depth neg_flag_or_depth, QString name, QString rx, RZ_MATCH_CALLBACK block) //CALLBACK_Type ct)
 {
  add_rule(name, rx, block);
  negated_condition_map(name, neg_flag_or_depth.as_Flag_or_Depth_ptr());
 }

 void add_rule(Negated_Flag_or_Depth neg_flag_or_depth, Context& c, QString name, QString rx, RZ_MATCH_CALLBACK block) //CALLBACK_Type ct)
 {
  add_rule(name, rx, block);
  context_map(name, c);
  condition_map(name, neg_flag_or_depth.as_Flag_or_Depth_ptr());
 }


 void add_anchored_rule_with_prelim(QString name, QString prelim, QString rx, RZ_MATCH_CALLBACK block)
 {
  QString s = prelim + "^" + rx;
  add_regex_rule(name, s, block);
 }

 void add_rule_with_prelim(QString name, QString prelim, QString rx, RZ_MATCH_CALLBACK block)
 {
  QString s = prelim + rx;
  add_regex_rule(name, s, block);
 }

 void add_compound_anchored_rule(QString name, QString rx, RZ_MATCH_CALLBACK block)
 {

  QString prelim;
  QString main_rx;
  prepare_compound_rule(rx, prelim, main_rx);
  add_anchored_rule_with_prelim(name, prelim, main_rx, block);
 }

 void add_compound_rule(QString name, QString rx, RZ_MATCH_CALLBACK block)
 {
  QString prelim;
  QString main_rx;
  prepare_compound_rule(rx, prelim, main_rx);
  add_rule_with_prelim(name, prelim, main_rx, block);
 }

 // preprecesses the rule string for both anchors and named matches
 void prepare_compound_rule(QString rx, QString& prelim, QString& main_rx)
 {
  int capture_name_count = 0;
  //  const char* cs = rx.c_str();
  QChar* cs = rx.data();

  QString name_acc_;
  QString prelim_acc_;
  QString main_acc_;

  // begin closure for temp functions
  {
   QString& name_acc = name_acc_;
   QString& prelim_acc = prelim_acc_;
   QString& main_acc = main_acc_;

   QString name;

   bool dot_flag = false;
   bool double_dot_flag = false;
   bool name_flag = false;
   bool local_name_flag = false;
   bool add_named_capture_flag = false;

   //  one reason to use lambdas here is that these tests can be
   //  used both within and after the unroll loop of the characters
   // char c;
   QChar c;

   auto get_expr = [&](QString name) -> QString
   {
    tRule* r = rule_names_[name];
    if(r)
     return r->expr;
    else
    {
     QString expr = pre_rule_strings_[name];
     if(expr.isEmpty()) //empty()
      return name;
     return expr;
    }
   };
   auto check_name_flag = [&]() -> bool
   {
    if(name_flag)
    {
     if(c == ' ' || c == '.' || c == '\n' || c == '\r' || c == 0 )
     {
      name_flag = false;
      name = name_acc;
      name_acc = "";
      //      name = name_acc.str();
      //      name_acc.str("");
      QString expr = get_expr(name);

      prelim_acc += "(?<" //'(' + '?' + '<'
        + name + '>' + expr + ')' + '{' + '0' + '}';
      capture_name_map_[name] = ++capture_name_count;
      if(c == '.')
       add_named_capture_flag = true;
      else if(local_name_flag)
      {
       local_name_flag = false;
      }
      else
       ;
     }
     else
      name_acc += c;
     return true;
    }
    return false;
   };
   auto check_double_dot_flag = [&]() -> bool
   {
    if(double_dot_flag)
    {
     double_dot_flag = false;
     if(c == 0)
      main_acc += '.' + '.';
     else if(c == ' ' || c == '\n' || c == '\r' || c == ']')
      main_acc += '.' + '.' + c;
     else if(c == '.')
      main_acc += '.' + '.' + '.';
     else
     {
      local_name_flag = true;
      name_flag = true;
      name_acc += c;
     }
     return true;
    }
    return false;
   };
   auto check_dot_flag = [&]() -> bool
   {
    if(dot_flag)
    {
     dot_flag = false;
     if(c.isNull() ) //== 0
       main_acc += '.';
     else if(c == ',')
       main_acc += '.';
     else if(c == ' ' || c == '\n' || c == '\r' || c == ']')
       main_acc += '.' + c;
     else if(c == '.')
       double_dot_flag = true;
     else
     {
      local_name_flag = false;
      name_flag = true;
      name_acc += c;
     }
     return true;
    }
    return false;
   };
   auto check_named_capture_flag = [&]() -> bool
   {
    if(add_named_capture_flag)
    {
     bool discard_c = (c == '\n' || c == '\r' || c.isNull());// == 0);
     if( discard_c || c == ' ' || c == '(' || c == ')' )
     {
      add_named_capture_flag = false;
      if(local_name_flag)
      {
       local_name_flag = false;
       QString expr = get_expr(name);
       main_acc += "(\\g<" + name + '>' + expr + ')';
      }
      else
      {
       QString expr = get_expr(name);
       main_acc += "(" + expr + ')' + name_acc;// + ')';
       name_acc = "";
      }
      if(!discard_c)
       main_acc += c;
     }
     else
      name_acc += c;
     return true;
    }
    return false;
   };
   do
   {
    c = *cs++;
    if(c == '?' && *cs == '<' && (*(cs + 1)).isLetter() )
    {
     cs++;
     QString s;
     while(*cs != '>')
      s += *cs++;
     capture_name_map_[s] = ++capture_name_count;
     c = *++cs;
     continue;
    }
    if(check_name_flag())
     continue;
    if(check_double_dot_flag())
     continue;
    if(check_dot_flag())
     continue;
    if(check_named_capture_flag())
     continue;
    if(c == '.')
     dot_flag = true;
    else
     main_acc += c;
   }
   while (!c.isNull());
   // clean up special strings maybe left at the end of the input
   if(check_name_flag());
   else if(check_dot_flag());
   else if(check_named_capture_flag());
  }  // end closure

  //  prelim = prelim_acc_.str();
  main_rx = main_acc_.simplified().
   replace(' ', "").replace("[__", "[ ").replace(QChar('\0'), "");

  // //  For streams or string builders rather than just QString
  //  prelim = prelim_acc_.str();
  //  main_rx = main_acc_.str();
  //  prelim_acc_.str("");
  //  main_acc_.str("");
 }


 void add_anchored_rule(QString name, QString rx, RZ_MATCH_CALLBACK block)
 {
  QString s = "\\g" + rx;
  add_regex_rule(name, s, block);
 }

 // does no preprocessing on the rule string
 void add_regex_rule(QString name, QString rx, RZ_MATCH_CALLBACK block)
 {
  tRule* r = new tRule (name, rx, block);
  add_rule(name, r);
 }

 void add_char_choice_rule(QString name, QString chars, RZ_MATCH_CALLBACK block)
 {
 }

 void add_char_rule(QString name, tChar char_, RZ_MATCH_CALLBACK block)
 {
  tRule* r = new tRule (name, QString(char_), block);
  add_rule(name, r);
 }

 RZ_Match_Data_Qt* regex_try_rule(QString str, int pos, tRule& r)
 {
  QRegularExpressionMatch match = r.rexpr->match(str, pos,
   QRegularExpression::NormalMatch, r.match_options);  //QRegExp::CaretAtOffset
  if(match.hasMatch())
  {
   return new RZ_Match_Data_Qt(match.capturedEnd(), // pos + match.capturedLength(),
    match.capturedTexts(), r.capture_name_map);
  }
  return nullptr;
 }

 RZ_Match_Data_Base*
 try_rule(tRule& r, QString str, void* extra_string_data, int pos)
 {
  // The extra_string_data is used by Rule_Type::Regex, but perhaps will be used by other types also.
//  switch(r.rule_type)
//  {
//  case tRule::Rule_Type::Char_Choice:
//   {
//    char c = str[pos];
//    if(r.expr.find_first_of(c) != -1)
//     return RZ_Match_Data(c);
//   }
//    break;
//   case tRule::Rule_Type::Regex:
//   {
//  void* md = Ruby_Bridge().try_rule(extra_string_data, pos, r.rexpr);

    RZ_Match_Data_Qt* md = regex_try_rule(str, pos, r);
    if(md)
    {
     return md;
    }
  return RZ_Match_Fail();
 }

 void paste_context(tRule* r)
 {
  if(context_dependencies_.find(r) != context_dependencies_.end())
  {
   r->context_index = context_dependencies_.value(r);//at(r);
  }
 }

 void paste_condition(tRule* r)
 {
  if(condition_dependencies_.find(r) != condition_dependencies_.end())
  {
   r->condition = condition_dependencies_.value(r);//(r);
  }
  if(negated_condition_dependencies_.find(r) != negated_condition_dependencies_.end())
  {
   r->negative_condition = negated_condition_dependencies_.value(r);//at(r);
  }
 }

 void paste_flag_test(tRule* r)
 {
  if(flag_tests_.find(r) != flag_tests_.end())
  {
   r->flag_test = flag_tests_.value(r);//.at(r);
  }
 }


 const
 Context* load_context(tRule* r)
 {
  return &context_vector_.at( r->context_index );
 }


 void compile(QString str, void* extra_string_data, int& pos, tParser& parser)
 {
  for (tRule* r:rules_)
  {
   RZ_Flag_Test* test = r->flag_test;
   if(test)
   {
    void* pv = test->bitset;
    size_t st = (size_t) pv;
    if(!*test)
    {
     continue;
    }
   }
   Flag_or_Depth* flag_or_depth = r->condition;
   if(flag_or_depth)
   {
    // // the r->flag_or_depth pointer may point to a single or an array of conditions.
    if(unsigned short cl = r->condition_length)
    {
     do
     {
      if(* (Flag_or_Depth*) (flag_or_depth) ) goto main_continue;
      ++flag_or_depth;
     }
     while(cl-- > 0);
    }
    else if(!*flag_or_depth)
    {
main_continue:
     continue;
    }
   }
   Flag_or_Depth* neg_flag_or_depth = r->negative_condition;
   if(neg_flag_or_depth)
   {
    // // the r->flag_or_depth pointer may point to a single or an array of conditions.
    if(unsigned short ncl = r->negative_condition_length)
    {
     do
     {
      if(* (Flag_or_Depth*) (neg_flag_or_depth) ) goto neg_main_continue;
      ++neg_flag_or_depth;
     }
     while(ncl-- > 0);
    }
    else if(*neg_flag_or_depth)
    {
neg_main_continue:
     continue;
    }
   }

   rule_context_ = load_context(r);
   if( rule_context_->fail() )
   {
    continue;
   }
   RZ_Match_Data_Base* md = try_rule(*r, str, extra_string_data, pos);
   // // The test for md by itself is not currently necessary, since try_rule
    //   will return a valid failure object (not a null pointer).
   if(md && *md)
   {
    if(md->end_of_file())
     pos = 0;
    else
    {
     parser.set_match(md, r, pos);
     r->callback();

     if(parser.reset_cancel())
      continue;
     else if(parser.end_of_file_info())
     {
      pos = 0;
     }
     else
     {
      md->reset_position(pos);
      QString seek;
      if(parser.check_seek(seek))
      {
       // this depends on QString functions
       pos = str.indexOf(seek, pos) + seek.size();
      }
     }
    }
    return;
   }
  }
  ++pos;
 }

 void buffer()
 {
 }


 void compile_file(tGraph& g, tParser& p, QString str)
 {
  QString contents;
  Utilities_type::Load_File(str, contents);
  compile(g, p, contents);
 }

 void compile(tParser& p, tGraph& g, QString str, int start_position = 0)
 {
  for (tRule* r:rules_)
  {
   paste_context(r);
   paste_condition(r);
   paste_flag_test(r);
  }
  QString extra_string_data;
  int pos = start_position;
  int length = str.length();
  do
  {
   compile(str, &extra_string_data, pos, p);
  }
  while( (pos > 0) && (pos <= length) );
 }
};


#endif //RELAE_GRAMMAR__H
