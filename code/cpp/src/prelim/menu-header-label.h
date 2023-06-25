#ifndef MENU_HEADER_LABEL__H
#define MENU_HEADER_LABEL__H

#include <QWidgetAction>
#include <QLabel>

inline QColor lighter_yellow()
{
 static QColor result;
 if(!result.isValid())
 {
  result = Qt::yellow;
  result = result.lighter(170);
 }
 return result;
}

class Menu_Header_Label : public QWidgetAction
{
public:

 Menu_Header_Label(QString text = "[text needed]", QColor color = lighter_yellow(), QWidget* parent = nullptr) : QWidgetAction(parent)
 {
 // "Five cases in this area"
  QLabel* lbl = new QLabel(text, parent);
  setDefaultWidget(lbl);

  lbl->setStyleSheet("padding-left:3;background:%1;"_qt.arg(color.name()));

 }

 Menu_Header_Label(QString text, QWidget* parent, QColor color = lighter_yellow()) :
   Menu_Header_Label(text, color, parent)
 {

 }

 Menu_Header_Label(QWidget* parent, QString text = "[text needed]", QColor color = Qt::yellow) :
   Menu_Header_Label(text, color, parent)
 {

 }


//protected:
// QWidget* createWidget()
// {
//  return new QLabel("OK");
// }
};




#endif
