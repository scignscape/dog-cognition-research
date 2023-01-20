
#ifdef _DH_INCLUDE_ONLY_

template<DH_Stage_Code::Query_Typecode>
void _acc_conv(DH_Stage_Code sc, char* mem, QDataStream& qds, u4 len);


//template<>
//void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_INTTYPE>(DH_Stage_Code sc,
//  char* mem, QDataStream& qds, u4 len)
//{
//}

#define _lenmin(x) qMin(len, (u4) x)

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_User_Data>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_Hypernode>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{
// QString* qs = (QString*) sv.data();
// result = qs->toStdString().c_str();//qs->toUtf8().data();
 //xdata = nullptr;
}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_qvar>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_NULLTYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_RECTYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}


template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_INTTYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{
 //u4 len = sc.get_byte_length();
 QByteArray qba;
 if(sc.check_signed())
 {
  switch (len)
  {
  case 1: s1 s_1; qds >> s_1; qba = u1_to_qba(s_1); break;
  case 2: s2 s_2; qds >> s_2; qba = u2_to_qba(s_2); break;
  case 4: s4 s_4; qds >> s_4; qba = u4_to_qba(s_4); break;
  case 8: n8 n_8; qds >> n_8; qba = n8_to_qba(n_8); break;
  }
 }
 else
 {
  switch (len)
  {
  case 1: u1 u_1; qds >> u_1; qba = u1_to_qba(u_1); break;
  case 2: u2 u_2; qds >> u_2; qba = u2_to_qba(u_2); break;
  case 4: u4 u_4; qds >> u_4; qba = u4_to_qba(u_4); break;
  case 8: n8 n_8; qds >> n_8; qba = n8_to_qba(n_8); break;
  }
 }
 memcpy(mem, qba.data(), len);
}



template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_DOUBLETYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_STRTYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_XMLLITERALTYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_URITYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_BLOBTYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_CHARTYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_FIXPOINTTYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_DATETYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{
 QDate qd;
 qds >> qd;
 QByteArray qba = n8_to_qba(qd.toJulianDay());
 memcpy(mem, qba.data(), _lenmin(8));
}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_TIMETYPE>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{
 QTime qtm;
 qds >> qtm;
 QByteArray qba = u4_to_qba((u4)qtm.msecsSinceStartOfDay());
 memcpy(mem, qba.data(), _lenmin(4));
}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_QDateTime>(DH_Stage_Code sc,
  char* mem, QDataStream& qds, u4 len)
{
 QDateTime qdt;
 qds >> qdt;
 QByteArray qba = n8_to_qba((n8)qdt.toMSecsSinceEpoch());
 memcpy(mem, qba.data(), _lenmin(8));
}




void _acc_conv(DH_Stage_Code sc, char* mem, QDataStream& qds, u4 len)
{
 DH_Stage_Code::Query_Typecode qtc = sc.get_qtc_code();
 switch (qtc)
 {
#define TEMP_MACRO(x ,y) \
  case DH_Stage_Code::Query_Typecode::qtc_##x: \
   _acc_conv<DH_Stage_Code::Query_Typecode::qtc_##x>(sc, mem, qds, len); break;
 _TYPECODE_QUERY_MACROS(TEMP_MACRO)
 #undef TEMP_MACRO
 }
}












template<DH_Stage_Code::Query_Typecode>
void _acc_conv(DH_Stage_Code sc, const QByteArray& source, QDataStream& target, u4 len);


//template<>
//void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_INTTYPE>(DH_Stage_Code sc,
//  const QByteArray& source, QDataStream& target, u4 len)
//{
//}

//#define _lenmin(x) qMin(len, (u4) x)

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_User_Data>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_Hypernode>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{
// QString* qs = (QString*) sv.data();
// result = qs->toStdString().c_str();//qs->toUtf8().data();
 //xdata = nullptr;
}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_qvar>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_NULLTYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_RECTYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}


template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_INTTYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{
 //u4 len = sc.get_byte_length();
 QByteArray qba;
 if(sc.check_signed())
 {
  switch (len)
  {
  case 1: target << qba_to_s1(source); break;
  case 2: target << qba_to_s2(source); break;
  case 4: target << qba_to_s4(source); break;
  case 8: target << qba_to_n8(source); break;
  }
 }
 else
 {
  switch (len)
  {
  case 1: target << qba_to_u1(source); break;
  case 2: target << qba_to_u2(source); break;
  case 4: target << qba_to_u4(source); break;
  case 8: target << qba_to_n8(source); break;
  }
 }
}



template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_DOUBLETYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_STRTYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_XMLLITERALTYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_URITYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_BLOBTYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_CHARTYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_FIXPOINTTYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{

}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_DATETYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{
 target << QDate::fromJulianDay(qba_to_n8(source));
// QDate qd;
// qds >> qd;
// QByteArray qba = n8_to_qba(qd.toJulianDay());
// memcpy(mem, qba.data(), _lenmin(8));
}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_WG_TIMETYPE>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{
 target << QTime::fromMSecsSinceStartOfDay(qba_to_u4(source));
}

template<>
void _acc_conv<DH_Stage_Code::Query_Typecode::qtc_QDateTime>(DH_Stage_Code sc,
  const QByteArray& source, QDataStream& target, u4 len)
{
 target << QDateTime::fromMSecsSinceEpoch(qba_to_n8(source));
}




void _acc_conv(DH_Stage_Code sc, const QByteArray& source, QDataStream& target, u4 len)
{
 DH_Stage_Code::Query_Typecode qtc = sc.get_qtc_code();
 switch (qtc)
 {
#define TEMP_MACRO(x ,y) \
  case DH_Stage_Code::Query_Typecode::qtc_##x: \
   _acc_conv<DH_Stage_Code::Query_Typecode::qtc_##x>(sc, source, target, len); break;
 _TYPECODE_QUERY_MACROS(TEMP_MACRO)
 #undef TEMP_MACRO
 }
}

#endif // _DH_INCLUDE_ONLY_
