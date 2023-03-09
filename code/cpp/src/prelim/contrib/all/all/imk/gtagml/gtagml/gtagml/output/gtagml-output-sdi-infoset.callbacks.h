
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


GTAGML_CALLBACK_(p)
 WHEN_(around)
 {
  check_sentence_boundaries(qts, node);
 }
 _WHEN
_GTagML_CALLBACK



GTAGML_CALLBACK_SUPPRESS(documentclass)
GTAGML_CALLBACK_NOACTION(include)
GTAGML_CALLBACK_NOACTION(main-block-text-commands)


GTAGML_CALLBACK_(document)
 WHEN_(pre)
 {
 }
 _WHEN_(post)
 {
 }
 _WHEN
_GTagML_CALLBACK


GTAGML_CALLBACK_(copy)
 WHEN_(around)
 {
  set_copy(qts, node);
 }
 _WHEN
_GTagML_CALLBACK

GTAGML_CALLBACK_(setup)
 WHEN_(around)
 {
  set_setup(qts, node);
 }
 _WHEN
_GTagML_CALLBACK


GTAGML_CALLBACK_(document-title)
 WHEN_(around)
 {
  set_info_param(qts, "document-title", node);
 }
 _WHEN
_GTagML_CALLBACK

GTAGML_CALLBACK_(local-title)
 WHEN_(around)
 {
  set_info_param(qts, "local-title", node);
 }
 _WHEN
_GTagML_CALLBACK





GTAGML_CALLBACK_(noxml_)
 WHEN_(around)
 {
  // suppress_node_ = node;
 }
 _WHEN
_GTagML_CALLBACK


GTAGML_CALLBACK_(_noxml)
 WHEN_(around)
 {
  // suppress_node_ = nullptr;
 }
 _WHEN
_GTagML_CALLBACK


GTAGML_CALLBACK_(dclass)
 WHEN_(pre)
 {
  // suppress_node_ = node;
 }
 _WHEN_(post)
 {
  // suppress_node_ = nullptr;
 }
 _WHEN
_GTagML_CALLBACK


GTAGML_CALLBACK_(inc)
 WHEN_(around)
 {
 }
 _WHEN
_GTagML_CALLBACK



 GTAGML_CALLBACK_(fnl)
  WHEN_(around)
  {
   qts << '\n';
  }
  _WHEN
 _GTagML_CALLBACK



//RENAME_TAG(cp, p)
RENAME_(cp, p, comment)
RENAME_(hide, span, hide)
RENAME_(ulead, u, leader)
RENAME_(iag, i, autogen)
RENAME_TAG(pdf-ref, span)
RENAME_(latex-only, span, latex-only)


GTAGML_CALLBACK_(code)
 WHEN_(pre)
  {
//   flags.code_display_mode = true;
   cb->flags.pre_fallthrough = true;
  }
  _WHEN_(post)
  {
//   flags.code_display_mode = false;
   cb->flags.post_fallthrough = true;
  }
 _WHEN
_GTagML_CALLBACK

