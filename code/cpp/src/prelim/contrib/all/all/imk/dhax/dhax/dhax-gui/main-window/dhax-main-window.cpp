
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dhax-main-window.h"

#include "dhax-main-window-menus.h"
#include "dhax-signal-generator.h"

#include "dhax-main-window-data.h"

#include "integration/meshlab/dhax-meshlab-integration-data.h"
#include "integration/freecad/dhax-freecad-integration-data.h"

#include <QSpacerItem>
#include <QGridLayout>


DHAX_Main_Window::DHAX_Main_Window()
  :  QMainWindow(), main_window_data_(nullptr),
     import_info_message_box_(nullptr)
{

}


void DHAX_Main_Window::init_signal_generator()
{
 signal_generator_ = new DHAX_Signal_Generator;
}


void DHAX_Main_Window::show_freecad_import_info()
{
 DHAX_FreeCAD_Integration_Data& fid = *main_window_data_->freecad_integration();

 QString dt = QString(R"(Temp File Path: %1
Camera Position: %2, %3, %4
Camera Rotation: %5, %6, %7; %8)")
   .arg(fid.freecad_file_path())
   .arg(fid.freecad_position_data().value(0))
   .arg(fid.freecad_position_data().value(1))
   .arg(fid.freecad_position_data().value(2))
   .arg(fid.freecad_position_data().value(3))
   .arg(fid.freecad_position_data().value(4))
   .arg(fid.freecad_position_data().value(5))
   .arg(fid.freecad_position_data().value(6))
   ;

 dt += QString(R"(
Aspect Ratio: %1
Near Distance: %2
Far Distance: %3
Focal Distance: %4)")
   .arg(fid.freecad_position_data().value(7))
   .arg(fid.freecad_position_data().value(8))
   .arg(fid.freecad_position_data().value(9))
   .arg(fid.freecad_position_data().value(10));


 if(import_info_message_box_)
   delete import_info_message_box_;

 import_info_message_box_ = new QMessageBox(this);
 import_info_message_box_->setText("FreeCAD Import");
 import_info_message_box_->setInformativeText(R"(Hit "Show Details" for information about the FreeCAD snapshot recently imported)");
 import_info_message_box_->setDetailedText(dt);
 QSpacerItem* horizontalSpacer = new QSpacerItem(600, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
 QGridLayout* layout = (QGridLayout*)import_info_message_box_->layout();
 layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

 import_info_message_box_->show();

}


void DHAX_Main_Window::show_meshlab_import_info()
{
 DHAX_Meshlab_Integration_Data& mid = *main_window_data_->meshlab_integration();
 QString ti = QString("%1; %2, %3, %4").arg(mid.meshlab_track_info().scalar())
   .arg(mid.meshlab_track_info().x()).arg(mid.meshlab_track_info().y())
   .arg(mid.meshlab_track_info().z());

 QString dt = QString(R"(Temp File Path: %1
Mesh File: %2
Track (Rotation) Position: %3
Center Position: %4, %5, %6
Scale (Zoom) Level: %7)")
   .arg(mid.mesh_file_path())
   .arg(mid.meshlab_file_path())
   .arg(ti)
   .arg(mid.meshlab_center_position().x()).
    arg(mid.meshlab_center_position().y()).
    arg(mid.meshlab_center_position().z())
   .arg(mid.meshlab_scale_info());

 if(import_info_message_box_)
   delete import_info_message_box_;

 import_info_message_box_ = new QMessageBox(this);
 import_info_message_box_->setText("Meshlab Export");
 import_info_message_box_->setInformativeText(R"(Hit "Show Details" for information about the Meshlab snapshot recently imported)");
 import_info_message_box_->setDetailedText(dt);
 QSpacerItem* horizontalSpacer = new QSpacerItem(600, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
 QGridLayout* layout = (QGridLayout*)import_info_message_box_->layout();
 layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

 import_info_message_box_->show();

}
