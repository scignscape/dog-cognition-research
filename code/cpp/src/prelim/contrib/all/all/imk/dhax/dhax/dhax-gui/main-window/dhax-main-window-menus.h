
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DHAX_MAIN_WINDOW_MENUS__H
#define DHAX_MAIN_WINDOW_MENUS__H

#include <QMenu>
#include <QMap>

#include "accessors.h"

class DHAX_Main_Window;

class DHAX_Menu : public QMenu
{
 struct _add_action_package {
  DHAX_Menu* _this;
  QString label;

  template<typename FN_Type>
  void operator <<(FN_Type fn)
  {
    _this->add_action(label, fn);
  }
 };


public:

 DHAX_Menu();


 _add_action_package add_action(QString label)
 {
  return {this, label};
 }

 template<typename FN_Type>
 void add_action(QString label, FN_Type fn)
 {
  addAction(label, fn);
 }

 DHAX_Menu* add_nested_menu(QString label)
 {
  return static_cast<DHAX_Menu*>(addMenu(label));
 }

};

class DHAX_Main_Window_Menus
{
 DHAX_Main_Window* parent_;

 QMap<QString, DHAX_Menu*> menus_;

// QMenu* help_menu_;
// QMenu* tools_menu_;

public:

 DHAX_Main_Window_Menus();

 ACCESSORS(DHAX_Main_Window* ,parent)

 void init_menu(QString label);
 DHAX_Menu* menu(QString label);

};


#endif //  DHAX_MAIN_WINDOW_MENUS__H


