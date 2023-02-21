
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "ses-configuration-dialog.h"

//?#include "styles.h"




#include <QApplication>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QButtonGroup>
#include <QScrollArea>
#include <QFileDialog>
#include <QTabWidget>
#include <QSplitter>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>

#include <QPlainTextEdit>
#include <QTextStream>

#include <QtMultimedia/QMediaPlayer>

#include <QPainter>
#include <QPushButton>
#include <QLabel>

//#include <QNetworkAccessManager>
//#include <QNetworkReply>

#include <QTableWidget>
#include <QGraphicsPixmapItem>

#include <QMessageBox>
#include <QDebug>
#include <QClipboard>

#include <QProcess>

#include <QGraphicsView>
#include <QScrollArea>

//#include <QTcpServer>
//#include <QNetworkAccessManager>

#include <QHeaderView>

#include <QMenu>
#include <QAction>

#include <QListWidget>

#include <QComboBox>

#include <QPainter>
#include <QPixmap>



SES_Configuration_Dialog::SES_Configuration_Dialog(QWidget* parent)
  : QDialog(parent)
{
 // // setup RZW

 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("OK");
 button_proceed_ = new QPushButton("Edit");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_proceed_->setDefault(false);
 button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setEnabled(false);

 // // unless this is being embedded ...
 button_proceed_->setEnabled(false);
 button_cancel_->setText("Close");

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
 button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

// button_ok_->setStyleSheet(basic_button_style_sheet_());
// button_proceed_->setStyleSheet(basic_button_style_sheet_());
// button_cancel_->setStyleSheet(basic_button_style_sheet_());

 connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(cancel()));

 main_layout_ = new QVBoxLayout;

 checkboxes_layout_ = new QGridLayout;

 QStringList temp_checkboxes_labels
  {

  "Energy-Conserving Architecture/Design", "Energy-Conserving Equipment/Installation",
  "Sustainable/Ecosensitive Materials/Sourcing", "Parks, Green Spaces, Public Areas",
  "Carbon-Neutral and/or Carbon Offsets", "Waterfront Zoning/Coastal Zone",
  "E-Designation", "FRESH (Food Retail Expansion)",
  "Environmental Rehabilitation", "Sustainable Infrastructure (transit, walkability)",


//  "Energy-Conserving Architecture/Design", "Apartment Building", "Parks/Recreation Area",
//     "Transit Stop/Center",
//     "Port/Airport/Railroad Track", "Commercial/Retail", "Factory/Warehouse",
//     "School/Religious Institution", "Farm/Agricultural Site", "Other"
 };

 QMap<QString, QCheckBox*> checkboxes_map_;

 for(QString label : temp_checkboxes_labels)
 {
  QString llabel = label.toLower();
  llabel.replace(' ', '-');
  llabel.replace(',', "");
  llabel.replace('(', "");
  llabel.replace(')', "");

  checkboxes_labels_.push_back(llabel);

  QCheckBox* qcb = new QCheckBox(label, this);
  checkboxes_map_[llabel] = qcb;
 }

 checkboxes_layout_->addWidget(checkboxes_map_["energy-conserving-architecture/design"], 0, 0);

// "Energy-Conserving Architecture/Design", "Energy-Conserving Equipment/Installation",
// "sustainable-ecosensitive-materials-sourcing", "parks-green-spaces-public-areas"
// "carbon-neutral-and/or-carbon-offsets", "waterfront-zoning/coastal-zone",
// "e-designation", "fresh-food-retail-expansion",
// "environmental-rehabilitation", "sustainable-infrastructure-transit-walkability",


 checkboxes_layout_->addWidget(checkboxes_map_["energy-conserving-equipment/installation"], 0, 1);
 checkboxes_layout_->addWidget(checkboxes_map_["sustainable/ecosensitive-materials/sourcing"], 0, 2);

 checkboxes_layout_->addWidget(checkboxes_map_["parks-green-spaces-public-areas"], 1, 0);
 checkboxes_layout_->addWidget(checkboxes_map_["carbon-neutral-and/or-carbon-offsets"], 1, 1);
 checkboxes_layout_->addWidget(checkboxes_map_["waterfront-zoning/coastal-zone"], 1, 2);

 checkboxes_layout_->addWidget(checkboxes_map_["e-designation"], 2, 0);
 checkboxes_layout_->addWidget(checkboxes_map_["fresh-food-retail-expansion"], 2, 1);
 checkboxes_layout_->addWidget(checkboxes_map_["environmental-rehabilitation"], 2, 2);

 checkboxes_layout_->addWidget(checkboxes_map_["sustainable-infrastructure-transit-walkability"], 3, 0);
 checkboxes_layout_->addWidget(checkboxes_map_["other"], 3, 1, 2, 1);
// checkboxes_layout_->addWidget(checkboxes_map_["other"], 3, 0);
 checkboxes_layout_->setRowStretch(4, 1);

 checkboxes_group_box_ = new QGroupBox("Location Classification (checked locations are shown on the map)", this);
 checkboxes_group_box_->setLayout(checkboxes_layout_);

 main_layout_->addWidget(checkboxes_group_box_);

 colors_layout_ = new QVBoxLayout;

 auto adj_button = [](QPushButton* b, QColor color) -> QPushButton*
 {
  QString qss = QString("background-color: %1").arg(color.name());
  b->setStyleSheet(qss);
  b->setMaximumWidth(30);
  b->setMaximumHeight(20);
  return b;
 };

 inner_colors_layouts_.push_back(new QHBoxLayout);
 inner_colors_layouts_.push_back(new QHBoxLayout);
 colors_group_box_ = new QGroupBox("Colors (click on a color patch to modify)");

 colors_buttons_.push_back(new QPushButton);
 colors_buttons_.push_back(new QPushButton);
 colors_buttons_.push_back(new QPushButton);

 colors_buttons_.push_back(new QPushButton);
 colors_buttons_.push_back(new QPushButton);


 inner_colors_layouts_[0]->addWidget(new QLabel("Waterfront Zoning/Coastal Zone (House)"));
 inner_colors_layouts_[0]->addWidget(adj_button(colors_buttons_[0], QColor(5, 190, 210, 255)));
 inner_colors_layouts_[0]->addStretch();

 inner_colors_layouts_[0]->addWidget(new QLabel("E-Designation"));
 inner_colors_layouts_[0]->addWidget(adj_button(colors_buttons_[1], QColor(155, 90, 10, 255)));
 inner_colors_layouts_[0]->addStretch();

 inner_colors_layouts_[1]->addWidget(new QLabel("FRESH (Food Retail Expansion)"));
 inner_colors_layouts_[1]->addWidget(adj_button(colors_buttons_[2], QColor(155, 0, 220, 220)));
 inner_colors_layouts_[1]->addStretch();

 inner_colors_layouts_[0]->addWidget(new QLabel("POPS (Privately Owned Public Space)"));
 inner_colors_layouts_[0]->addWidget(adj_button(colors_buttons_[3], QColor(55, 90, 110, 255)));

 inner_colors_layouts_[1]->addWidget(new QLabel("Current Selected Map Item/Location (if applicable)"));
 inner_colors_layouts_[1]->addWidget(adj_button(colors_buttons_[4], QColor(201, 159, 34)));
 inner_colors_layouts_[1]->addStretch();

// "Waterfront Zoning/Coastal Zone",
//   "E-Designation", "FRESH (Food Retail Expansion)"

 for(auto* layout : inner_colors_layouts_)
 colors_layout_->addLayout(layout);

 colors_group_box_->setLayout(colors_layout_);

 main_layout_->addWidget(colors_group_box_);




 shapes_layout_ = new QVBoxLayout;


 qreal chevron_scale = 2;
 QPointF chevron_adj{0, 42};
 QPolygonF* chevron = new QPolygonF;
 (*chevron) << QPointF(-80, -180)/chevron_scale + chevron_adj;
 (*chevron) << QPointF(0, -150)/chevron_scale + chevron_adj;
 (*chevron) << QPointF(80, -180)/chevron_scale + chevron_adj;
 (*chevron) << QPointF(0, 0)/chevron_scale + chevron_adj;


 qreal bow_tie_scale = 3;
 QPointF bow_tie_adj{0, -2};

 QPolygonF* bow_tie = new QPolygonF;
 (*bow_tie) << QPointF(-110, -110)/bow_tie_scale + bow_tie_adj;
 (*bow_tie) << QPointF(-110, 110)/bow_tie_scale + bow_tie_adj;
 (*bow_tie) << QPointF(110, -110)/bow_tie_scale + bow_tie_adj;
 (*bow_tie) << QPointF(110, 110)/bow_tie_scale + bow_tie_adj;


 qreal diamond_scale = 4;
 QPointF diamond_adj{0, -2};

 QPolygonF* diamond = new QPolygonF;
 (*diamond) << QPointF(-20, 110)/diamond_scale + diamond_adj;
 (*diamond) << QPointF(20, 110)/diamond_scale + diamond_adj;
 (*diamond) << QPointF(110, 20)/diamond_scale + diamond_adj;
 (*diamond) << QPointF(110, -20)/diamond_scale + diamond_adj;
 (*diamond) << QPointF(20, -110)/diamond_scale + diamond_adj;
 (*diamond) << QPointF(-20, -110)/diamond_scale + diamond_adj;
 (*diamond) << QPointF(-110, -20)/diamond_scale + diamond_adj;
 (*diamond) << QPointF(-110, 20)/diamond_scale + diamond_adj;



 auto sadj_button = [](QPushButton* b, QPolygonF* qpf) -> QPushButton*
 {
  QPixmap* qpm = new QPixmap(100, 100);
  qpm->fill();
  QPainter painter(qpm);

  QPointF center {((qreal)qpm->width())/2, ((qreal)qpm->height())/2};
  //painter.begin(qpm);

  //painter.scale(0.35, 0.35);
  painter.setBrush(QColor(80,50,50,255));

  if(qpf)
    painter.drawPolygon(qpf->translated(center));

  else
  {
   painter.drawEllipse(center, 40, 17);
   painter.drawEllipse(center, 17, 40);
  }
  b->setIcon(QIcon(*qpm));

  b->setMaximumWidth(30);
  b->setMaximumHeight(20);
  return b;
 };

 inner_shapes_layouts_.push_back(new QHBoxLayout);
 inner_shapes_layouts_.push_back(new QHBoxLayout);
 shapes_group_box_ = new QGroupBox("Shapes (click on a shape to modify or reassign)");

 shapes_buttons_.push_back(new QPushButton);
 shapes_buttons_.push_back(new QPushButton);
 shapes_buttons_.push_back(new QPushButton);

 shapes_buttons_.push_back(new QPushButton);
 shapes_buttons_.push_back(new QPushButton);

 inner_shapes_layouts_[0]->addWidget(new QLabel("Bow-Tie"));
 inner_shapes_layouts_[0]->addWidget(sadj_button(shapes_buttons_[1], bow_tie));
 inner_shapes_layouts_[0]->addWidget(new QLabel("(Assigned to Transportation)"));
 inner_shapes_layouts_[0]->addStretch();

 inner_shapes_layouts_[0]->addWidget(new QLabel("Double-Oval"));
 inner_shapes_layouts_[0]->addWidget(sadj_button(shapes_buttons_[3], nullptr));
 inner_shapes_layouts_[0]->addWidget(new QLabel("(Assigned to ports/airports)"));
 inner_shapes_layouts_[0]->addStretch();

 inner_shapes_layouts_[1]->addWidget(new QLabel("Diamond"));
 inner_shapes_layouts_[1]->addWidget(sadj_button(shapes_buttons_[0], diamond));
 inner_shapes_layouts_[1]->addWidget(new QLabel("(Assigned to current location)"));
 inner_shapes_layouts_[1]->addStretch();

 inner_shapes_layouts_[1]->addWidget(new QLabel("Chevron"));
 inner_shapes_layouts_[1]->addWidget(sadj_button(shapes_buttons_[2], chevron));
 inner_shapes_layouts_[1]->addWidget(new QLabel("(Assigned to Parks)"));
 inner_shapes_layouts_[1]->addStretch();

 for(auto* layout : inner_shapes_layouts_)
 shapes_layout_->addLayout(layout);

 shapes_group_box_->setLayout(shapes_layout_);

 main_layout_->addWidget(shapes_group_box_);


 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 setWindowTitle("Configuration Dialog");

}

//top_buttons_layout_ = new QHBoxLayout;

//take_screenshot_button_ = new QPushButton("Screenshot", this);

//activate_tcp_button_ = new QPushButton("Activate TCP", this);

//take_screenshot_button_->setStyleSheet(colorful_button_style_sheet_());
//activate_tcp_button_->setStyleSheet(colorful_button_style_sheet_());

//connect(take_screenshot_button_, SIGNAL(clicked()),
//  this, SLOT(handle_take_screenshot_requested()));

//connect(activate_tcp_button_, SIGNAL(clicked()),
//  this, SLOT(activate_tcp_requested()));

//top_buttons_layout_->addStretch();

//top_buttons_layout_->addWidget(activate_tcp_button_);

//top_buttons_layout_->addWidget(take_screenshot_button_);


SES_Configuration_Dialog::~SES_Configuration_Dialog()
{

}

void SES_Configuration_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void SES_Configuration_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
