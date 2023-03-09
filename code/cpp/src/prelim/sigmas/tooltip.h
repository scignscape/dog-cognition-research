//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



SIGMA_ADAPTER(set_multiline_tooltip, (QString ,a1), (QString ,a2))
SIGMA_ADAPTER_PAIR(share_tooltip)

/* these macros should be akin to:
 *

void set_multiline_tooltip(QString a1, QString a2)
{
 sigmans(set_multiline_tooltip)(oself, a1, a2);
}

void share_tooltip()
{
 sigmans(share_tooltip)(oself->first, oself->second);
 oself_done();
}

 *
 */
