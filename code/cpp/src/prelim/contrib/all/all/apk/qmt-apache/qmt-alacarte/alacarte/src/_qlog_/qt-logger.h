
#ifndef QT_LOGGER__H
#define QT_LOGGER__H

#include <QString>

#include <string>


inline QString q_from_std(const std::string ss)
{
 return QString::fromStdString(ss);
 //return qs.toStdString().c_str();
}

//inline QString operator ""_qt(const char* cs, size_t size)
//{
// std::string ss(cs, size);
// return q_from_std(ss);
//}

extern void qlog(QString msg);


#endif
