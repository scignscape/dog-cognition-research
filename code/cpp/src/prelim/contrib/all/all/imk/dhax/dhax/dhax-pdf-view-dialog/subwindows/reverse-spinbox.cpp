
#include "reverse-spinbox.h"

Reverse_Spin_Box::Reverse_Spin_Box(QWidget* parent)
 : QSpinBox(parent)
{
 connect(this, SIGNAL(valueChanged(int)),
   this, SLOT(reverse_value_changed(int)));
}

QValidator::State Reverse_Spin_Box::validate(QString &input, int &pos) const
{
 return QValidator::Acceptable;
}

int Reverse_Spin_Box::valueFromText(const QString& text) const
{
 int num = text.toInt();
 if(num == 0)
 {
  return 0;
 }
 else
 {
  return - (num - 1);
 }
}

QString Reverse_Spin_Box::textFromValue(int value) const
{
 return QSpinBox::textFromValue(1 - value);
}

void Reverse_Spin_Box::set_value(int value)
{
 this->QSpinBox::setValue(1 - value);
}

void Reverse_Spin_Box::reverse_value_changed(int value)
{
 Q_EMIT(value_changed(1 - value));
}

void Reverse_Spin_Box::set_maximum(int max)
{
 this->QSpinBox::setMaximum(0);
 this->QSpinBox::setMinimum(1 - max);
}


void Reverse_Spin_Box::stepBy(int steps)
{
 this->QSpinBox::stepBy(steps);
//    switch(steps) {
//        case 1 :    setValue(value()*2);
//                    break;
//        case -1 :   setValue(value()/2);
//                    break;
//        default:    QSpinBox::stepBy(steps);
//                    break;
//    }
}

