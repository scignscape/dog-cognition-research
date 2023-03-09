
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_MENU_SYSTEM__H
#define DHAX_MENU_SYSTEM__H

#include <QMenu>
#include <QMap>

#include "accessors.h"


class DHAX_Main_Window;
class DHAX_Main_Window_Menus;
class DHAX_Menu;

class DHAX_Menu_System
{
 DHAX_Main_Window* main_window_;
 DHAX_Main_Window_Menus* menus_;

// QMenu* help_menu_;
// QMenu* tools_menu_;

 QMap<QPair<DHAX_Menu*, QString>, QAction*> deferred_actions_;
 QMap<QPair<DHAX_Menu*, QString>, QAction*> action_ref_map_;



public:

 DHAX_Menu_System();

 ACCESSORS(DHAX_Main_Window* ,main_window)

 void init_menus();

 DHAX_Menu* menu(QString label);

//? void add_deferred_action(QString key, QAction* a);
 QAction* add_deferred_action_ref(QString ref, DHAX_Menu& menu, QString key);
 QAction* add_action_ref(QString ref, DHAX_Menu& menu, QString key);
 QAction* get_action_by_ref_name(QString ref, DHAX_Menu& menu);

};


#endif //  DHAX_MENU_SYSTEM__H


