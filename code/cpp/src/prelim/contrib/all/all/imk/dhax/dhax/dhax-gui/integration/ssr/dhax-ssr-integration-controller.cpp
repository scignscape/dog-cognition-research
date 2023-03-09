
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dhax-ssr-integration-controller.h"

#include "application/dhax-application-controller.h"

#include "dhax-ssr-integration-data.h"

#include <QDebug>


DHAX_SSR_Integration_Controller::DHAX_SSR_Integration_Controller()
  :  integration_data_(nullptr), application_controller_(nullptr)
{

}

void DHAX_SSR_Integration_Controller::read_datagram(QString text)
{
 integration_data_->ssr_file_path_ = text;
 application_controller_->offer_to_play_video(
    "Play back the screen-recorded video now?", text);
}

