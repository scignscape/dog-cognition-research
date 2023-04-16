
#include <QUrl>

#include "qh-cpp-parser/qh-cpp-document.h"

USING_KANS(Qh)

#include <QApplication>

#include "pdf-viewer/pdf-document-controller.h"

#include "textio.h"

USING_KANS(TextIO)

#include "json/qh-json-file-reader.h"
#include "json/pseudo-jpath.h"

#include "sdi/sdi-block-element.h"

#include "sdi/sdi-block-element-collection.h"


#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>
#include <QJsonObject>

USING_KANS(RdSC)


#include "dlfcn.h"

//#include <QXmlStreamReader>


/*

<! <x>[retval] <\ [proc](pr)  [lambda](<*>[retval] <\ [proc](add) [lambda](5 7) ) !>

.,
load-pst $ /test ;.
,.

,x int

.<x>[r] [p](pr)  [l](<*>[r] [p](add) [l](5 7) )

.[p](unless) [l]($1 $2) = .[p](if) [l](<*>[r] [l](;1) ;2)


[p] = %
[r] = @
[l] = \
[m] = &
[s] =
[e] =
[c] = @.

.<x>@ %(pr) \(<*>@ %(add) \(5 7) )


.&(unless) \($1 $2) = .%(if) \(<*>@ \(;1) ;2)


.<x>@. %(test) \+(this)


.<x>[c]

 */

u2 pt_to_px(r8 pt)
{
 return pt * (96./72);
}


int main(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 PDF_Document_Controller pdfc;

 QString folder = ROOT_FOLDER "/../qh/work";


 Qh_Json_File_Reader qjfr(folder + "/tex/out");

 QJsonDocument jsond;
 qjfr.json_document(jsond, "nj.json");



 Pseudo_JPath jp(jsond);
 QString pw = jp.evaluate("$:page-size>pdfpagewidth;").value<QString>();
 if(pw.endsWith("pt"))
   pw.chop(2);

 QString ph = jp.evaluate("$:page-size>pdfpageheight;").value<QString>();
 if(ph.endsWith("pt"))
   ph.chop(2);

 QString dlh = jp.evaluate("$:default-letter-height;").value<QString>();
 if(dlh.endsWith("pt"))
   dlh.chop(2);
 r8 default_letter_height = dlh.toDouble();


 //QVector<SDI_Block_Element*> sentences;
 SDI_Block_Element_Collection element_collection;


 QJsonArray elements_array = jp.evaluate("$:elements;").value<QJsonArray>();
// Pseudo_JPath jpa((QJsonDocument(sentences_array)));
// jpa.evaluate("$|0");

// QVector<QPair<QPair<u4, u4>, QPair<u4, u4>>> element_start_and_ends;

 r8 width = pw.toDouble();
 r8 height = ph.toDouble();

 u2 w_px = pt_to_px(width);
 u2 h_px = pt_to_px(height);

 qDebug() << "w_px = " << w_px;
 qDebug() << "h_px = " << h_px;

 static u4 rescale = 0x10000;


 for(QJsonValue v : elements_array)
 {
  if(!v.isObject())
    continue;

  QJsonObject qjo = v.toObject();
  //u4 id = o.value("id").toInt();
  auto it = qjo.find("isa");
  if(it == qjo.end())
  {
   it = qjo.find("end-of");
   if(it == qjo.end())
     // any other options?
     continue;
   QString end_of = it.value().toString();
   if(SDI_Block_Element* sbe = element_collection.read_json_end_object(end_of, qjo))
   {    
    r8 top_letter_height = default_letter_height + 4; // allow and extra 4 pts on top
    r8 bottom_letter_height = default_letter_height;

    //r8 first_line_height_adjustment = (count == 1)? default_letter_height : 0;

    r8 line_spacing_factor = default_letter_height + 3; //? what exactly?

    sbe->init_coordinates(height, width - 10, 10,
      top_letter_height, bottom_letter_height, line_spacing_factor, default_letter_height);
   }

   //sbe->read_json_start_object(kind, o);
  }
  else
  {
   QString kind = it.value().toString();
   SDI_Block_Element* sbe = new SDI_Block_Element();
   sbe->read_json_start_object(kind, element_collection, qjo);
  }
 }

 QString sdi_block_elements;

 for(SDI_Block_Element* sentence : element_collection.sentences())
 {
//  ++count;
  QString points;
//  if(count == 3)
//  {
   sentence->svg_coordinates_string(points);
   sdi_block_elements += R"_(
              <g id="sentence-%1" transform="translate(0, 0)">
   <a class='sentence-start_base sentence-start_display-select' id='discourse-s%1'>
    <polygon points="%2" />
   </a>
    </g>
     )_"_qt.arg(sentence->sentence_id()).arg(points);
//  }
 }

 QString base_title = "multi-media";

 QString path = "%1/tex/out/%2.pdf"_qt.arg(folder).arg(base_title);
 pdfc.load_document(path);

 QImage image(1, 1, QImage::Format_RGB32);

 QPair<u4, u4> pr {image.physicalDpiX(), image.physicalDpiY()};
 pdfc.load_page(0, 1, pr);

 image = pdfc.pixmap().toImage();

 QString page_file = "%1/%2.png"_qt.arg(folder).arg(base_title);

 image.save(page_file);

 QString svg = load_file(folder + "/template.svg");

 svg.replace("%WIDTH%", QString::number(image.width()));
 svg.replace("%HEIGHT%", QString::number(image.height()));
 svg.replace("%PAGE%", page_file);
 svg.replace("%BLOCK-ELEMENTS%", sdi_block_elements);

 save_file("%1/%2.svg"_qt.arg(folder).arg(base_title), svg);

 return 0;
}


int main1()
{
 Qh_CPP_Document qhd(ROOT_FOLDER "/../qh/test.qh");
 qhd.parse();

 return 0;

}

#ifdef HIDE


//QString svg = R"_(
//<svg width="%1" height="%2" xmlns="http://www.w3.org/2000/svg"
// xmlns:xhtml="http://www.w3.org/1999/xhtml"
// xmlns:xlink="http://www.w3.org/1999/xlink">
//<defs>

// <style>
//  .sentence-start_base {fill:none;
//    fill-opacity:0.3;stroke-opacity:0.5;
//    stroke:none; stroke-width:1;}

//  .sentence-start_display-select {}

//  .sentence-start_base:hover { fill:rgb(250,130,130);
//     stroke: rgb(250,130,130); }
// </style>

//</defs>

//<image xlink:href="t1.png"  width="%1" height="%2" />
//%3
//</svg>
//)_"_qt.arg(image.width()).arg(image.height()).arg(circles)
// ;



// r8 x1 = (double)  / rescale;
// r8 y1 = (double) y1u / rescale;

// r8 x2 = (double) x2u / rescale;
// r8 y2 = (double) y2u / rescale;


//  QJsonArray a_s = o.value("start").toArray();
//  QJsonArray a_e = o.value("end").toArray();

//  element_start_and_ends.push_back({{a_s[0].toInt(), a_s[1].toInt()},
//    {a_e[0].toInt(), a_e[1].toInt()}});
//  v.toObject(
//  Pseudo_JPath jpa((QJsonDocument(v.toObject())));
//  ses.push_back({{jpa.evaluate("$:start|0").toUInt(), jpa.evaluate("$:start|1").toUInt()},
//                 {jpa.evaluate("$:end|0").toUInt(), jpa.evaluate("$:end|1").toUInt()}}
//                 );

// u4 x1u = jp.evaluate("$:x1;").value<u4>();
// u4 y1u = jp.evaluate("$:y1;").value<u4>();

// u4 x2u = jp.evaluate("$:x2;").value<u4>();
// u4 y2u = jp.evaluate("$:y2;").value<u4>();


u2 paragraph_id = 1;
u2 count = 0;
for(QPair<QPair<u4, u4>, QPair<u4, u4>> se : element_start_and_ends)
{
 ++count;

 SDI_Block_Element* sentence = new SDI_Block_Element(paragraph_id, count);


 r8 top_letter_height = default_letter_height + 4; // allow and extra 4 pts on top
 r8 bottom_letter_height = default_letter_height;

 r8 first_line_height_adjustment = (count == 1)? default_letter_height : 0;

 r8 line_spacing_factor = default_letter_height + 3; //? what exactly?



 sentence->init_coordinates(se, height, width - 10, 10,
   top_letter_height, bottom_letter_height, line_spacing_factor, first_line_height_adjustment);

//  sentences.push_back(sentence);
}

//  circles += R"_(
//             <g id="south-move-text-group" transform="translate(%1, %2)">
//              <a class='sentence-start_base sentence-start_display-select' id='token-s0'>
//              <circle cx='0' cy='0' r='3' />
//              </a>
//             </g>

//               <g id="south-move-text-group" transform="translate(%3, %4)">
//                <a class='sentence-start_base sentence-start_display-select' id='token-s0'>
//                <circle cx='0' cy='0' r='3' />
//                </a>
//               </g>

//             )_"_qt.arg(x1_px).arg(h_px - y1_px)
//    .arg(x2_px).arg(h_px - y2_px);

//  ++count;

//  if(count == 3)
//  {

//   u2 start_x = x1_px;
//   u2 start_y_baseline = h_px - y1_px;
//   u2 start_y_topline = start_y_baseline - lh;

//   u2 endline_x = w_px + 10;
//   u2 endline_y_top = start_y_topline;
//   u2 endline_y_bottom = start_y_baseline + 3;

//   u2 end_x = x2_px;
//   u2 end_y_baseline = h_px - y2_px;
//   u2 end_y_topline = end_y_baseline - lh;

//   u2 startline_x = 10;
//   u2 startline_y_top = end_y_topline - 3;
//   u2 startline_y = end_y_baseline;

// count = 0;


class test_test
{
 r4 val;

public:

 test_test() : val(111.111) {};

 void debug(u2 x);

};

void test_test::debug(u2 x)
{
 qDebug() << (x + val);
}


void tdebug()
{
 qDebug() << 44;

}


int main(int argc, char *argv[])
{
 test_test tt;

 tt.debug(2);

 std::string ss =  typeid(&test_test::debug).name();

 qDebug() << QString::fromStdString(ss);

 QString fn = QString::fromStdString(ss).mid(1);
 fn.prepend("_ZN");

 void *hndl = dlopen (NULL, RTLD_NOW);

 //auto ty = typeid(tdebug).;
 std::string ss1 =  typeid(tdebug).name();

 void* fptr = dlsym (hndl, fn.toStdString().c_str());
 typedef void (test_test::*ttt)(u2);

 union ttt_cast { void* pv; ttt fn; };
 ttt_cast tc;
 tc.pv = dlsym (hndl, "_ZN9test_test5debugEt");

 ttt tfn = tc.fn;

 (tt.*tfn)(13);

 return 0;
}

#endif
