
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)



RENAME_TAG(discourse-markup, discourseMarkup)
RENAME_TAG(discourse-markup-inline, discourseMarkupInline)

GTAGML_CALLBACK_NOACTION(hold-ref)

GTAGML_CALLBACK_NOACTION(noxml_)
GTAGML_CALLBACK_NOACTION(_noxml)

GTAGML_CALLBACK_SUPPRESS(xml-save_)
GTAGML_CALLBACK_NOACTION(_xml-save)
GTAGML_CALLBACK_SUPPRESS(saved-xml)

GTAGML_CALLBACK_NOACTION(copy)
GTAGML_CALLBACK_NOACTION(document-title)
GTAGML_CALLBACK_NOACTION(local-title)


GTAGML_CALLBACK_(main-block-text-commands)
 WHEN_(around)
 {
  parse_main_block_text_commands(node);
 }
 _WHEN
_GTagML_CALLBACK



GTAGML_CALLBACK_(cite)
 WHEN_(pre)
 {
  mark_citation(qts, node, prior_node, parent_of_siblings);
  cb->flags.pre_fallthrough = true;
 }
 _WHEN
_GTagML_CALLBACK


