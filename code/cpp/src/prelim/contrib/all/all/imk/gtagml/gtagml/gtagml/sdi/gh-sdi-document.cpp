

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gh-sdi-document.h"

#include "gh/gh-block-base.h"

#include "output/gtagml-output-sdi-infoset.h"

#include "kans.h"

#include <QFile>

#include <QDir>
#include <QDirIterator>

#include "textio.h"

USING_KANS(TextIO)

USING_KANS(SDI)


GH_SDI_Document::GH_SDI_Document()
 :  sdi_infoset_output_(nullptr)
{

}

void GH_SDI_Document::setup_folder_from_template(QString file_name, QString job_name,
  QString template_folder, QString input_folder, QString setup_folder, QString topl)
{
 QDir qd(setup_folder);

 qd.mkdir("ngml");
 qd.cd("ngml");
 QDir tqd(template_folder);
 tqd.cd("ngml");
 QDirIterator qdi(tqd);
 while(qdi.hasNext())
 {
  qdi.next();
  QString fp = qdi.filePath();
  if(fp.endsWith(".tex"))
  {
   copy_file_to_folder(fp, qd.path());
  }
 }

 tqd.cdUp();
 qd.cdUp();

 QDir iqd(input_folder);
 iqd.cdUp();

 QString pdfl = load_file(tqd.absoluteFilePath("run-pdflatex.sh"));

 pdfl.replace("%R%", ROOT_FOLDER);
 pdfl.replace("%I%", input_folder);
 pdfl.replace("%U%", iqd.absolutePath());


 if(topl.isEmpty())
 {
  if(job_name.isEmpty())
  {
   QFileInfo qfi(file_name);
   job_name = qfi.completeBaseName();
  }

  pdfl.replace("%F%", file_name);
  pdfl.replace("%J%", job_name);
 }
 else
 {
  if(job_name.isEmpty())
  {
   QFileInfo qfi(topl);
   job_name = qfi.completeBaseName();
  }

  pdfl.replace("%F%", topl);
  pdfl.replace("%J%", job_name);
 }

 save_file(qd.absoluteFilePath("run-pdflatex.sh"), pdfl);

 qd.cdUp();
 qd.cdUp();
 qd.mkdir("out");
}


void GH_SDI_Document::finalize_sentence_boundaries(GH_Block_Base& bl, QString path)
{
 sdi_infoset_output_->finalize_paragraph_boundaries(bl);
 sdi_infoset_output_->finalize_sentence_boundaries(bl);

 sdi_infoset_output_->finalize_widowed_sentence_boundaries(bl);

 QFile outfile(path);
 if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text))
   return;
 QTextStream outstream(&outfile);

 outstream << R"(
&type GH_SDI_Sentence {4}
 :i:1 :p:2 :s:3 :e:4 ;

&type GH_SDI_Paragraph {4}
 :i:1 :j:2 :s:3 :e:4 ;

&/
 )";

 sdi_infoset_output_->write_ntxh(outstream);

 outstream << R"(

/&
)";

 outfile.close();

 // QPair<u4, u4> pr = bl.get_effective_start_and_end_indices();
// u4 s = pr.first;
// u4 e = pr.second;
// for(u4 u = s; u <= e; ++u)
// {

// }
}


bool GH_SDI_Document::check_letter(GH_Block_Base& bl, u4 pos)
{
 GH_Block_Base::SDI_Interpretation_Codes sic = bl.get_sdi_interpretation_code_at_index(pos);
 return sic == GH_Block_Base::SDI_Interpretation_Codes::Letter
   || sic == GH_Block_Base::SDI_Interpretation_Codes::Declared_Fiat_Letter
   || sic == GH_Block_Base::SDI_Interpretation_Codes::Declared_Fiat_Letter_Sentence_End;
}

bool GH_SDI_Document::check_sentence_start_resume(GH_Block_Base& bl, u4 pos)
{
 GH_Block_Base::SDI_Interpretation_Codes sic = bl.get_sdi_interpretation_code_at_index(pos);
 return sic == GH_Block_Base::SDI_Interpretation_Codes::Declared_Sentence_Resume_Space;
}

bool GH_SDI_Document::check_sentence_end_suspend(GH_Block_Base& bl, u4 pos)
{
 GH_Block_Base::SDI_Interpretation_Codes sic = bl.get_sdi_interpretation_code_at_index(pos);
 return sic == GH_Block_Base::SDI_Interpretation_Codes::Declared_Sentence_End_Suspend_Space;
}

u4 GH_SDI_Document::scan_for_sentence_start_resume(GH_Block_Base& bl, u4 start, u4 end)
{
 u4 i = start;
 if(!check_sentence_end_suspend(bl, i))
   return 0;
 for(++i; i <= end; ++i)
 {
  if(check_sentence_start_resume(bl, i))
    return i;
 }
 return 1;
}

void GH_SDI_Document::clear_end_boundary_space(GH_Block_Base& bl, u4& end)
{
 while(end > 0)
 {
  GH_Block_Base::SDI_Interpretation_Codes sic = bl.get_sdi_interpretation_code_at_index(end);
  if(sic == GH_Block_Base::SDI_Interpretation_Codes::Hide_Ignore)
    --end;
  else
    return;
 }

}


u4 GH_SDI_Document::scan_for_sentence_start(GH_Block_Base& bl, u4 start, u4 end, u4& result)
{
 u1 gap = 1;
 for(u4 i = start; i <= end; ++i)
 {
  if(check_letter(bl, i))
  {
   result = i;
   return gap;
  }
  ++gap;
 }
 return false;
}

u4 GH_SDI_Document::scan_for_sentence_end(GH_Block_Base& bl,
  u4 start, u4 end, u4& result, u4& space)
{
 u4 _space = 0;
 u4 gap = 1;
 for(u4 i = start; i <= end; ++i)
 {
  GH_Block_Base::SDI_Interpretation_Codes sic = bl.get_sdi_interpretation_code_at_index(i);
  if(sic == GH_Block_Base::SDI_Interpretation_Codes::Potential_Sentence_End
   || sic == GH_Block_Base::SDI_Interpretation_Codes::Declared_Fiat_Letter_Sentence_End)
  {
   if(i == end)
   {
    result = i;
    space = 0;
    return gap;
   }
   _space = bl.check_confirm_sentence_end(i + 1, end);
   if(_space == 0)
     continue;
   else
   {
    result = i;
    space = _space;
    return gap;
   }
  }
  else if(sic == GH_Block_Base::SDI_Interpretation_Codes::Declared_Sentence_End)
  {
   result = i;
   space = bl.get_declared_sentence_end_space(i + 1, end);
   return gap;
  }
  ++gap;
 }
 result = 0;
 space = 0;
 return 0;
}

