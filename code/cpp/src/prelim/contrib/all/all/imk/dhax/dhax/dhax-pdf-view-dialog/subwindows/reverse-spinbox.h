#ifndef REVERSE_SPIN_BOX__H
#define REVERSE_SPIN_BOX__H

#include <QSpinBox>

class Reverse_Spin_Box : public QSpinBox
{
 Q_OBJECT

public:

 Reverse_Spin_Box(QWidget* parent = nullptr);

 void set_maximum(int max);

 int valueFromText(const QString &text) const;
 QString textFromValue(int value) const;

 QValidator::State validate(QString &input, int &pos) const;
 //QValidator validate()

Q_SIGNALS:

 void value_changed(int value);

public Q_SLOTS:
 void stepBy(int steps);
 void reverse_value_changed(int value);
 void set_value(int value);
};

#endif
