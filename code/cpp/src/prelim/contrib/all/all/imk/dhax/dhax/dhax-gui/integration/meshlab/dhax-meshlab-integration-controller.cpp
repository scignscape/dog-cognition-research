
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dhax-meshlab-integration-controller.h"

#include "application/dhax-application-controller.h"

#include "dhax-meshlab-integration-data.h"

#include <QDebug>


DHAX_Meshlab_Integration_Controller::DHAX_Meshlab_Integration_Controller()
  :  integration_data_(nullptr), application_controller_(nullptr)
{

}

void DHAX_Meshlab_Integration_Controller::read_datagram(QString text)
{
 //qDebug() << "text = " << text;
 QStringList qsl = text.split('*');

 integration_data_->mesh_file_path_ = qsl.takeFirst();

 QString file_path = qsl.takeFirst();
 integration_data_->meshlab_file_path_ = file_path;
// meshlab_file_path_ = file_path;

 if(!qsl.isEmpty())
 {
  QStringList qsl1 = qsl.takeFirst().simplified().split(' ');
  integration_data_->meshlab_track_info_.setScalar(qsl1.value(0).toFloat());
  integration_data_->meshlab_track_info_.setX(qsl1.value(1).toFloat());
  integration_data_->meshlab_track_info_.setY(qsl1.value(2).toFloat());
  integration_data_->meshlab_track_info_.setZ(qsl1.value(3).toFloat());
 }

 if(!qsl.isEmpty())
 {
  QString scale_and_center = qsl.takeFirst().simplified();
  QStringList qsl1 = scale_and_center.split(' ');
  integration_data_->meshlab_scale_info_ = qsl1.value(0).toFloat();

  integration_data_->meshlab_center_position_.setX(qsl1.value(1).toFloat());
  integration_data_->meshlab_center_position_.setY(qsl1.value(2).toFloat());
  integration_data_->meshlab_center_position_.setZ(qsl1.value(3).toFloat());
 }

 ++*integration_data_->meshlab_import_count_;

 //showNormal();
 application_controller_->load_image(file_path);

}

