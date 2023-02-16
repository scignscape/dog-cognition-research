
#include <QDebug>

#include <QString>
#include <QFileInfo>

#include <QtMath>

#include "qmt-global-types.h"
#include "qt-logger.h"

#include <QImage>
#include <QPainter>

#include <QGuiApplication>

#include <QVector2D>


QLine make_vline(const QPoint& center, u2 half_height)
{
 //QLine result(center.x(), center.y() - height, )
 return QLine(center - QPoint{0, half_height}, center + QPoint{0, half_height});
}

QLine make_hline(const QPoint& center, u2 half_width)
{
 //QLine result(center.x(), center.y() - height, )
 return QLine(center - QPoint{half_width, 0}, center + QPoint{half_width, 0});
}

QRect make_rectangle_from_center(const QPoint& center, u2 width, u2 height)
{
 QRect result(center, QSize{0, 0});
 result.adjust(-width, -height, width, height);
 return result;
}

QRect make_square_from_center(const QPoint& center, u2 half_side)
{
 QRect result(center, QSize{0, 0});
 result.adjust(-half_side, -half_side, half_side, half_side);
 return result;
}

void center_transpose(QRect& rect)
{
 rect = make_rectangle_from_center(rect.center(), (u2) rect.height() / 2, (u2) rect.width() / 2);
}

static constexpr u2 mr_factor = 4;

u2 operator ""_mr(n8 value)
{
 return value * mr_factor;
}

void draw_gappy_rectangle(QPainter& painter, const QRect& rect, u2 gap)
{
 painter.drawLine(rect.topLeft() + QPoint(gap, 0), rect.topRight() - QPoint(gap, 0));
 painter.drawLine(rect.bottomLeft() + QPoint(gap, 0), rect.bottomRight() - QPoint(gap, 0));

 painter.drawLine(rect.topLeft() + QPoint(0, gap), rect.bottomLeft() - QPoint(0, gap));
 painter.drawLine(rect.topRight() + QPoint(0, gap), rect.bottomRight() - QPoint(0, gap));

}

void draw_gappy_rectangle_as_hexagon(QPainter& painter, const QRect& rect, u2 gap)
{
 draw_gappy_rectangle(painter, rect, gap);

 painter.drawLine(rect.topLeft() + QPoint(gap, 0), rect.topLeft() + QPoint(0, gap));

 painter.drawLine(rect.topRight() - QPoint(gap, 0), rect.topRight() + QPoint(0, gap));

 painter.drawLine(rect.bottomLeft() + QPoint(gap, 0), rect.bottomLeft() - QPoint(0, gap));

 painter.drawLine(rect.bottomRight() - QPoint(gap, 0), rect.bottomRight() - QPoint(0, gap));

}

void draw_image(QImage& image)
{
 QPainter painter(&image);

 QPoint focus = image.rect().center();

 painter.drawRect(image.rect());

 painter.setPen(Qt::darkRed);
 QRect c_rect = make_rectangle_from_center(focus, 44_mr, 78_mr);
 painter.drawRect(c_rect);
 center_transpose(c_rect);
 painter.drawRect(c_rect);

 painter.setPen(Qt::black);


 QRect d_rect = make_rectangle_from_center(focus, 33_mr, 44_mr);

 //painter.drawRect(d_rect);
 painter.drawLine(d_rect.topLeft(), d_rect.bottomLeft());
 painter.drawLine(d_rect.topRight(), d_rect.bottomRight());


 center_transpose(d_rect);
// painter.drawRect(d_rect);

 painter.drawLine(d_rect.topLeft(), d_rect.topRight());
 painter.drawLine(d_rect.bottomLeft(), d_rect.bottomRight());

// QRect b_rect = make_rectangle_from_center(focus, 55_mr, 77_mr);

// painter.drawRect(b_square);

// QRect b_rect1 = make_rectangle_from_center(focus, 55_mr, 33_mr);
// painter.drawRect(b_rect1);
// center_transpose(b_rect1);
// painter.drawRect(b_rect1);


 QPoint aline_center = focus - QPoint(66_mr, 0);
 QLine l1 = make_vline(aline_center, 44_mr);
 painter.drawLine(l1);

 aline_center = focus + QPoint(66_mr, 0);
 l1 = make_vline(aline_center, 44_mr);
 painter.drawLine(l1);

 aline_center = focus - QPoint(0, 66_mr);
 l1 = make_hline(aline_center, 44_mr);
 painter.drawLine(l1);

 aline_center = focus + QPoint(0, 66_mr);
 l1 = make_hline(aline_center, 44_mr);
 painter.drawLine(l1);

 QRect z_rect = make_rectangle_from_center(focus, 92_mr, 55_mr);

 QRect b_square = make_square_from_center(focus, 55_mr);

 painter.setPen(Qt::red);
 painter.drawLine(z_rect.topLeft(), b_square.topLeft());
 painter.drawLine(z_rect.bottomLeft(), b_square.bottomLeft());
 painter.drawLine(z_rect.topRight(), b_square.topRight());
 painter.drawLine(z_rect.bottomRight(), b_square.bottomRight());


 painter.setPen(Qt::darkCyan);

//? painter.drawRect(z_rect);
 QLine zline(z_rect.topLeft(), z_rect.bottomLeft());
 painter.drawLine(zline);
 zline.translate(14_mr, 0);
 painter.drawLine(zline);

 zline = QLine(z_rect.topRight(), z_rect.bottomRight());
 painter.drawLine(zline);
 zline.translate(-14_mr, 0);
 painter.drawLine(zline);


 center_transpose(z_rect);

 painter.setPen(Qt::red);
 painter.drawLine(z_rect.topLeft(), b_square.topLeft());
 painter.drawLine(z_rect.bottomLeft(), b_square.bottomLeft());
 painter.drawLine(z_rect.topRight(), b_square.topRight());
 painter.drawLine(z_rect.bottomRight(), b_square.bottomRight());

 draw_gappy_rectangle(painter, b_square, 11_mr);

 painter.setPen(Qt::darkCyan);



// painter.drawRect(z_rect);
// painter.drawLine(z_rect.topLeft(), z_rect.topRight());
// painter.drawLine(z_rect.bottomLeft(), z_rect.bottomRight());

 zline = QLine(z_rect.topLeft(), z_rect.topRight());
 painter.drawLine(zline);
 zline.translate(0, 14_mr);
 painter.drawLine(zline);

 zline = QLine(z_rect.bottomLeft(), z_rect.bottomRight());
 painter.drawLine(zline);
 zline.translate(0, -14_mr);
 painter.drawLine(zline);

 painter.setPen(Qt::NoPen);
 painter.setBrush(QColor("orange"));
 //QRect goal_rect = make_rectangle_from_side_centers(focus.x() - 90_mr)

 //painter.drawLine(focus.x() - 88_mr, focus.y(), focus.x() - 33_mr, focus.y());
 painter.drawRect(focus.x() - 92_mr, focus.y() - 10_mr, 4_mr, 20_mr);
 painter.drawRect(focus.x() + 92_mr, focus.y() - 10_mr, -4_mr, 20_mr);

 painter.drawRect(focus.x() - 10_mr, focus.y() - 92_mr, 20_mr, 4_mr);
 painter.drawRect(focus.x() - 10_mr, focus.y() + 92_mr, 20_mr, -4_mr);

 painter.setPen(Qt::darkGreen);

 painter.drawLine(focus.x() - 82_mr, focus.y() - 8_mr, focus.x() - 33_mr, focus.y() - 8_mr);
 painter.drawLine(focus.x() - 88_mr, focus.y(), focus.x() - 33_mr, focus.y());

 painter.drawLine(focus.x() - 82_mr, focus.y() + 8_mr, focus.x() - 33_mr, focus.y() + 8_mr);
 painter.drawLine(focus.x() - 82_mr, focus.y() - 8_mr, focus.x() - 82_mr, focus.y() + 8_mr);

 painter.drawLine(focus.x() + 82_mr, focus.y() - 8_mr, focus.x() + 33_mr, focus.y() - 8_mr);
 painter.drawLine(focus.x() + 88_mr, focus.y(), focus.x() + 33_mr, focus.y());
 painter.drawLine(focus.x() + 82_mr, focus.y() + 8_mr, focus.x() + 33_mr, focus.y() + 8_mr);
 painter.drawLine(focus.x() + 82_mr, focus.y() - 8_mr, focus.x() + 82_mr, focus.y() + 8_mr);


 painter.drawLine(focus.x() - 8_mr, focus.y() - 82_mr, focus.x() - 8_mr, focus.y() - 33_mr);
 painter.drawLine(focus.x(), focus.y() - 88_mr, focus.x(), focus.y() - 33_mr);
 painter.drawLine(focus.x() + 8_mr, focus.y() - 82_mr, focus.x() + 8_mr, focus.y() - 33_mr);
 painter.drawLine(focus.x() - 8_mr, focus.y() - 82_mr, focus.x() + 8_mr, focus.y() - 82_mr);

 painter.drawLine(focus.x() - 8_mr, focus.y() + 82_mr, focus.x() - 8_mr, focus.y() + 33_mr);
 painter.drawLine(focus.x(), focus.y() + 88_mr, focus.x(), focus.y() + 33_mr);
 painter.drawLine(focus.x() + 8_mr, focus.y() + 82_mr, focus.x() + 8_mr, focus.y() + 33_mr);
 painter.drawLine(focus.x() - 8_mr, focus.y() + 82_mr, focus.x() + 8_mr, focus.y() + 82_mr);

 painter.setPen(Qt::darkMagenta);

 u2 gap = 17_mr;
 QRect hex = make_square_from_center(focus, 22_mr);
 draw_gappy_rectangle_as_hexagon(painter, hex, gap);

 painter.setPen(Qt::darkYellow);
 QPen new_pen(Qt::darkYellow);
 new_pen.setWidth(2);
 painter.setPen(new_pen);
 QRect d_square = make_square_from_center(focus, 33_mr);
// painter.drawRect(d_square);

 QPoint home_bl = d_square.bottomLeft();

 QPoint stumps_bl = home_bl + QPoint(-5_mr * M_SQRT1_2, 5_mr * M_SQRT1_2);

 QPoint base_bl_1 = home_bl + QPoint(28_mr, 0);
 QPoint base_bl_6 = home_bl + QPoint(0, -28_mr);

// QPoint base_b1_2 = base_b1_1 + QPoint(28_mr * M_SQRT1_2, -28_mr * M_SQRT1_2);
// QPoint base_b1_5 = base_b1_6 + QPoint(28_mr * M_SQRT1_2, -28_mr * M_SQRT1_2);

 QPoint base_bl_2 = base_bl_1 + QPoint(27_mr, -10_mr);
 QPoint base_bl_5 = base_bl_6 + QPoint(10_mr, -27_mr);

 QPoint base_bl_3 = base_bl_2 + QPoint(0, -28_mr);

 QPoint mid_bl_3 = base_bl_3 + QPoint(6_mr, 0_mr);


 QPoint base_bl_4 = base_bl_5 + QPoint(28_mr, 0);


 //QLine l_start(d_square.bottomLeft(), d_square.bottomLeft() + QPoint(28_mr, 0));

 u2 base_radius = 4;

 painter.setBrush(Qt::yellow);

 painter.drawLine(stumps_bl + QPoint(5, 5), stumps_bl + QPoint(-5, -5));

 painter.drawEllipse(home_bl, base_radius, base_radius);
 painter.drawEllipse(base_bl_1, base_radius, base_radius);
// painter.drawEllipse(base_b1_2, base_radius, base_radius);
 painter.drawEllipse(base_bl_3, base_radius, base_radius);

 painter.drawEllipse(mid_bl_3, base_radius, base_radius);



 painter.drawEllipse(base_bl_4, base_radius, base_radius);
// painter.drawEllipse(base_b1_5, base_radius, base_radius);
 painter.drawEllipse(base_bl_6, base_radius, base_radius);

// painter.drawText(base_b1_1, "1");
// painter.drawText(base_b1_2, "2");
// painter.drawText(base_b1_3, "3");
// painter.drawText(base_b1_4, "4");
// painter.drawText(base_b1_5, "5");
// painter.drawText(base_b1_6, "6");



 QPoint home_br = d_square.bottomRight();

 QPoint stumps_br = home_br + QPoint(5_mr * M_SQRT1_2, 5_mr * M_SQRT1_2);


 QPoint base_br_6 = home_br + QPoint(-28_mr, 0);
 QPoint base_br_1 = home_br + QPoint(0, -28_mr);

 QPoint base_br_5 = base_br_6 + QPoint(-27_mr, -10_mr);
 QPoint base_br_2 = base_br_1 + QPoint(-10_mr, -27_mr);

 QPoint base_br_4 = base_br_5 + QPoint(0, -28_mr);
 QPoint base_br_3 = base_br_2 + QPoint(-28_mr, 0);

 new_pen.setColor(Qt::blue);
 painter.setPen(new_pen);
 painter.setBrush(QColor(Qt::cyan));

// new_pen.setColor(Qt::red);
// painter.setPen(new_pen);
// painter.setBrush(QColor("pink"));

 painter.drawLine(stumps_br + QPoint(-5, 5), stumps_br + QPoint(5, -5));
// painter.drawText(base_br_1, "1");
// painter.drawText(base_br_2, "2");
// painter.drawText(base_br_3, "3");
// painter.drawText(base_br_4, "4");
// painter.drawText(base_br_5, "5");
// painter.drawText(base_br_6, "6");

 painter.drawEllipse(home_br, base_radius, base_radius);

 painter.drawEllipse(base_br_1, base_radius, base_radius);
// painter.drawEllipse(base_br_2, base_radius, base_radius);
 painter.drawEllipse(base_br_3, base_radius, base_radius);
 painter.drawEllipse(base_br_4, base_radius, base_radius);
// painter.drawEllipse(base_br_5, base_radius, base_radius);
 painter.drawEllipse(base_br_6, base_radius, base_radius);


 QPoint home_tr = d_square.topRight();

 QPoint stumps_tr = home_tr + QPoint(5_mr * M_SQRT1_2, -5_mr * M_SQRT1_2);


 QPoint base_tr_1 = home_tr + QPoint(-28_mr, 0);
 QPoint base_tr_6 = home_tr + QPoint(0, 28_mr);


 QPoint base_tr_2 = base_tr_1 + QPoint(-27_mr, 10_mr);
 QPoint base_tr_5 = base_tr_6 + QPoint(-10_mr, 27_mr);

 QPoint base_tr_3 = base_tr_2 + QPoint(0, 28_mr);
 QPoint base_tr_4 = base_tr_5 + QPoint(-28_mr, 0);

 new_pen.setColor(Qt::darkYellow);
 painter.setPen(new_pen);
 painter.setBrush(Qt::yellow);

 painter.drawLine(stumps_tr + QPoint(-5, -5), stumps_tr + QPoint(5, 5));

// painter.drawText(base_tr_1, "1");
// painter.drawText(base_tr_2, "2");
// painter.drawText(base_tr_3, "3");
// painter.drawText(base_tr_4, "4");
// painter.drawText(base_tr_5, "5");
// painter.drawText(base_tr_6, "6");

 painter.drawEllipse(home_tr, base_radius, base_radius);

 painter.drawEllipse(base_tr_1, base_radius, base_radius);
// painter.drawEllipse(base_tr_2, base_radius, base_radius);
 painter.drawEllipse(base_tr_3, base_radius, base_radius);
 painter.drawEllipse(base_tr_4, base_radius, base_radius);
// painter.drawEllipse(base_tr_5, base_radius, base_radius);
 painter.drawEllipse(base_tr_6, base_radius, base_radius);

 QPoint mid_bl_5_tr_2 ((base_bl_5 + base_tr_2) / 2);
 mid_bl_5_tr_2 -= QPoint(2_mr, 2_mr);
 painter.drawEllipse(mid_bl_5_tr_2, base_radius, base_radius);

// painter.drawEllipse( (base_bl_5 + base_tr_2) / 2, base_radius, base_radius);

// painter.drawEllipse( (base_bl_2 + base_tr_5) / 2, base_radius, base_radius);

 QPoint mid_bl_2_tr_5 ((base_bl_2 + base_tr_5) / 2);
 mid_bl_2_tr_5 -= QPoint(2_mr, 2_mr);
 painter.drawEllipse(mid_bl_2_tr_5, base_radius, base_radius);



 QPoint home_tl = d_square.topLeft();
 QPoint stumps_tl = home_tl + QPoint(-5_mr * M_SQRT1_2, -5_mr * M_SQRT1_2);

 QPoint base_tl_6 = home_tl + QPoint(28_mr, 0);
 QPoint base_tl_1 = home_tl + QPoint(0, 28_mr);

 QPoint base_tl_5 = base_tl_6 + QPoint(27_mr, 10_mr);
 QPoint base_tl_2 = base_tl_1 + QPoint(10_mr, 27_mr);

 QPoint base_tl_4 = base_tl_5 + QPoint(0, 28_mr);
 QPoint base_tl_3 = base_tl_2 + QPoint(28_mr, 0);

 new_pen.setColor(Qt::blue);
 painter.setPen(new_pen);
 painter.setBrush(Qt::cyan);

 painter.drawLine(stumps_tl + QPoint(5, -5), stumps_tl + QPoint(-5, 5));

 painter.drawEllipse(home_tl, base_radius, base_radius);
// painter.drawText(base_tl_1, "1");
// painter.drawText(base_tl_2, "2");
// painter.drawText(base_tl_3, "3");
// painter.drawText(base_tl_4, "4");
// painter.drawText(base_tl_5, "5");
// painter.drawText(base_tl_6, "6");

 painter.drawEllipse(base_tl_1, base_radius, base_radius);
// painter.drawEllipse(base_tl_2, base_radius, base_radius);
 painter.drawEllipse(base_tl_3, base_radius, base_radius);
 painter.drawEllipse(base_tl_4, base_radius, base_radius);
// painter.drawEllipse(base_tl_5, base_radius, base_radius);
 painter.drawEllipse(base_tl_6, base_radius, base_radius);

 QPoint mid_tl_5_br_2 ((base_tl_5 + base_br_2) / 2);
 mid_tl_5_br_2 -= QPoint(2_mr, 2_mr);

 painter.drawEllipse(mid_tl_5_br_2, base_radius, base_radius);
 painter.drawEllipse( (base_tl_2 + base_br_5) / 2, base_radius, base_radius);




// painter.drawLine(home, base_b1_1);
// painter.drawLine(home, base_b1_6);
// painter.drawLine(base_b1_1, base_b1_2);
// painter.drawLine(base_b1_6, base_b1_5);
// painter.drawLine(base_b1_2, base_b1_3);
// painter.drawLine(base_b1_5, base_b1_4);

 painter.setBrush(Qt::NoBrush);


 painter.drawEllipse(mid_bl_2_tr_5, base_radius * 2, base_radius * 2);

 QLine dist_line(home_br, mid_bl_2_tr_5);

 QVector2D dist_vec(dist_line.dx(), dist_line.dy());

 qDebug() << "dist_vec = " << dist_vec << " l = " << dist_vec.length() / mr_factor;

 QLine dist_line1(base_bl_1, mid_bl_2_tr_5);
 QVector2D dist_vec1(dist_line1.dx(), dist_line1.dy());
 qDebug() << "dist_vec1 = " << dist_vec1 << " l = " << dist_vec1.length() / mr_factor;

 QLine dist_line2(mid_bl_2_tr_5, mid_bl_3);
 QVector2D dist_vec2(dist_line2.dx(), dist_line2.dy());
 qDebug() << "dist_vec2 = " << dist_vec2 << " l = " << dist_vec2.length() / mr_factor;

 QLine dist_line3(mid_bl_3, base_bl_4);
 QVector2D dist_vec3(dist_line3.dx(), dist_line3.dy());
 qDebug() << "dist_vec3 = " << dist_vec3 << " l = " << dist_vec3.length() / mr_factor;


 QPoint mid34 = (base_bl_3 + base_tl_4) / 2;
 QPoint mid43 = (base_bl_4 + base_br_3) / 2;

 painter.drawEllipse(mid34, base_radius * 2, base_radius * 2);
 painter.drawEllipse(mid43, base_radius * 2, base_radius * 2);


 QLine dist_line23(base_bl_2, mid34);
 QVector2D dist_vec23(dist_line23.dx(), dist_line23.dy());
 qDebug() << "dist_vec23 = " << dist_vec23 << " l = " << dist_vec23.length() / mr_factor;

 QLine dist_line3443(mid34, mid43);
 QVector2D dist_vec3443(dist_line3443.dx(), dist_line3443.dy());
 qDebug() << "dist_vec3443 = " << dist_vec3443 << " l = " << dist_vec3443.length() / mr_factor;

 QLine dist_line34(mid34, base_bl_4);
 QVector2D dist_vec34(dist_line34.dx(), dist_line34.dy());
 qDebug() << "dist_vec34 = " << dist_vec34 << " l = " << dist_vec34.length() / mr_factor;



 //u2 dist = home_bl

}


int main(int argc, char* argv[])
{
 QGuiApplication app(argc, argv);


 QString image_path = ALACARTE_QLOG_FOLDER "/img.png"_qt;

 QFileInfo qfi(image_path);

 qDebug() << "image = " << qfi.absoluteFilePath();

 QImage image(188_mr, 188_mr, QImage::Format_RGB32);


 image.fill(Qt::white);

 draw_image(image);

 image.save(qfi.absoluteFilePath());

 return 0;

}
