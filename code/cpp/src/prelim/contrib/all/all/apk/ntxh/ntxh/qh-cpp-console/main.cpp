
#include <QUrl>

#include "qh-cpp-parser/qh-cpp-document.h"

USING_KANS(Qh)

#include <QApplication>

#include "pdf-viewer/pdf-document-controller.h"

#include "textio.h"

USING_KANS(TextIO)

#include "json/qh-json-file-reader.h"
#include "json/pseudo-jpath.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>
#include <QJsonObject>

USING_KANS(RdSC)

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




 QJsonArray sentences_array = jp.evaluate("$:sentences;").value<QJsonArray>();
// Pseudo_JPath jpa((QJsonDocument(sentences_array)));
// jpa.evaluate("$|0");


 QVector<QPair<QPair<u4, u4>, QPair<u4, u4>>> ses;

 for(QJsonValue v : sentences_array)
 {
  if(!v.isObject())
    continue;

  QJsonObject o = v.toObject();
  QJsonArray a_s = o.value("start").toArray();
  QJsonArray a_e = o.value("end").toArray();

  ses.push_back({{a_s[0].toInt(), a_s[1].toInt()},
    {a_e[0].toInt(), a_e[1].toInt()}});
//  v.toObject(
//  Pseudo_JPath jpa((QJsonDocument(v.toObject())));
//  ses.push_back({{jpa.evaluate("$:start|0").toUInt(), jpa.evaluate("$:start|1").toUInt()},
//                 {jpa.evaluate("$:end|0").toUInt(), jpa.evaluate("$:end|1").toUInt()}}
//                 );
 }

 r8 width = pw.toDouble();
 r8 height = ph.toDouble();

 u2 w_px = pt_to_px(width);
 u2 h_px = pt_to_px(height);

 qDebug() << "w_px = " << w_px;
 qDebug() << "h_px = " << h_px;


// u4 x1u = jp.evaluate("$:x1;").value<u4>();
// u4 y1u = jp.evaluate("$:y1;").value<u4>();

// u4 x2u = jp.evaluate("$:x2;").value<u4>();
// u4 y2u = jp.evaluate("$:y2;").value<u4>();

 static u4 rescale = 0x10000;

 QString circles;

 u1 count = 0;
 for(QPair<QPair<u4, u4>, QPair<u4, u4>> se : ses)
 {
  r8 x1 = (double) se.first.first / rescale;
  r8 y1 = (double) se.first.second / rescale;

  r8 x2 = (double) se.second.first / rescale;
  r8 y2 = (double) se.second.second / rescale;

  u2 x1_px = pt_to_px(x1);
  u2 y1_px = pt_to_px(y1);

  u2 x2_px = pt_to_px(x2);
  u2 y2_px = pt_to_px(y2);

  u2 lh = pt_to_px(default_letter_height);

  circles += R"_(
             <g id="south-move-text-group" transform="translate(%1, %2)">
              <a class='sentence-start_base sentence-start_display-select' id='token-s0'>
              <circle cx='0' cy='0' r='3' />
              </a>
             </g>

               <g id="south-move-text-group" transform="translate(%3, %4)">
                <a class='sentence-start_base sentence-start_display-select' id='token-s0'>
                <circle cx='0' cy='0' r='3' />
                </a>
               </g>

             )_"_qt.arg(x1_px).arg(h_px - y1_px)
    .arg(x2_px).arg(h_px - y2_px);

  ++count;

  if(count == 3)
  {

   u2 start_x = x1_px;
   u2 start_y_baseline = h_px - y1_px;
   u2 start_y_topline = start_y_baseline - lh;

   u2 endline_x = w_px + 10;
   u2 endline_y_top = start_y_topline;
   u2 endline_y_bottom = start_y_baseline + 3;

   u2 end_x = x2_px;
   u2 end_y_baseline = h_px - y2_px;
   u2 end_y_topline = end_y_baseline - lh;

   u2 startline_x = 10;
   u2 startline_y_top = end_y_topline - 3;
   u2 startline_y = end_y_baseline;

   QString point1 = "%1,%2"_qt.arg(start_x).arg(start_y_baseline);
   QString point2 = "%1,%2"_qt.arg(start_x).arg(start_y_topline);
   QString point3 = "%1,%2"_qt.arg(endline_x).arg(endline_y_top);
   QString point4 = "%1,%2"_qt.arg(endline_x).arg(endline_y_bottom);

   QString point5 = "%1,%2"_qt.arg(end_x).arg(end_y_topline);
   QString point6 = "%1,%2"_qt.arg(end_x).arg(end_y_baseline);
   QString point7 = "%1,%2"_qt.arg(startline_x).arg(startline_y);
   QString point8 = "%1,%2"_qt.arg(startline_x).arg(startline_y_top);


   circles += R"_(
              <g id="south-move-text-group" transform="translate(0, 0)">
   <a class='sentence-start_base sentence-start_display-select' id='discourse-s0'>
    <polygon points="%1 %2 %3 %4 %5 %6 %7 %8" />
   </a>
    </g>
     )_"_qt.arg(point1).arg(point2).arg(point3).arg(point4)
   .arg(point5).arg(point6).arg(point7).arg(point8);

  }


  // r8 x2 = (double) x2u / rescale;
  // r8 y2 = (double) y2u / rescale;
 }

// r8 x1 = (double)  / rescale;
// r8 y1 = (double) y1u / rescale;

// r8 x2 = (double) x2u / rescale;
// r8 y2 = (double) y2u / rescale;


 QString path = folder + "/tex/out/nj.pdf";
 pdfc.load_document(path);

 QImage image(1, 1, QImage::Format_RGB32);

 QPair<u4, u4> pr {image.physicalDpiX(), image.physicalDpiY()};
 pdfc.load_page(0, 1, pr);

 image = pdfc.pixmap().toImage();



 image.save(folder + "/t1.png");

 QString svg = R"_(
<svg width="%1" height="%2" xmlns="http://www.w3.org/2000/svg"
  xmlns:xhtml="http://www.w3.org/1999/xhtml"
  xmlns:xlink="http://www.w3.org/1999/xlink">
 <defs>

  <linearGradient id="sentence-start-gradient" gradientTransform="rotate(299)">
   <stop offset="0%" stop-color="rgb(127, 29, 43)" />
   <stop offset="35%" stop-color="white" />
   <stop offset="100%" stop-color="white" />
  </linearGradient>

  <style>
   .sentence-start_base {fill:url(#sentence-start-gradient);
     fill-opacity:0.3;stroke-opacity:0.5;
     stroke:url(#sentence-start-gradient); stroke-width:1;}

   .sentence-start_display-select {}

   .sentence-start_base:hover  { fill:rgb(250,130,130) }
  </style>

 </defs>

 <image xlink:href="t1.png"  width="%1" height="%2" />
 %3
</svg>
)_"_qt.arg(image.width()).arg(image.height()).arg(circles)
  ;

 save_file(folder + "/t1.svg", svg);


 return 0;
}



int main1()
{
 Qh_CPP_Document qhd(ROOT_FOLDER "/../qh/test.qh");
 qhd.parse();

 return 0;

}
