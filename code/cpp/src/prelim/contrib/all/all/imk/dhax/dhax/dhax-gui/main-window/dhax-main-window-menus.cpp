
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "dhax-main-window-menus.h"

#include "dhax-gui/main-window/dhax-main-window.h"

#include <QMenuBar>

DHAX_Main_Window_Menus::DHAX_Main_Window_Menus()
{

}


DHAX_Menu::DHAX_Menu()
{

}


void DHAX_Main_Window_Menus::init_menu(QString label)
{
 menus_[label] = static_cast<DHAX_Menu*>(parent_->menuBar()->addMenu(label)); //, parent_);
}

DHAX_Menu* DHAX_Main_Window_Menus::menu(QString label)
{
 return menus_.value(label);
}
