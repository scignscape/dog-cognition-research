
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DGVM_RUNTIME__TEMPLATES__H
#define DGVM_RUNTIME__TEMPLATES__H

#include <QVariant>


USING_KANS(DGVM)



//namespace std {
// template<class T, std::size_t N>
// struct tuple_size<DGVM_Runtime_Environment::One_Byte_Deque::_binder<T, N>>
//    : std::integral_constant<std::size_t, N> { };

//    template<std::size_t I, std::size_t N, class T>
//    struct tuple_element<I, DGVM_Runtime_Environment::One_Byte_Deque::_binder<T, N>> { using type = T; };
//}



//template <std::size_t N, typename T>
//auto DGVM_Runtime_Environment::One_Byte_Deque::binding_rhs(const std::vector<T>& vec) {
//  return _binder<T, N>{vec};
//}


template<typename VALUE_Type>
u1 DGVM_Runtime::get_ptr_tag(n8 raw_value)
{
 mz::tagged_ptr<VALUE_Type> tptr;
 tptr.set_raw_value(raw_value);
 return tptr.tag();
}


template<typename VALUE_Type>
VALUE_Type*  DGVM_Runtime::detag_ptr(n8 raw_value)
{
 mz::tagged_ptr<VALUE_Type> tptr;
 tptr.set_raw_value(raw_value);
 return tptr.ptr();
}


template<typename VALUE_Type, size_t ALIGN_Size>
mz::tagged_ptr<VALUE_Type, ALIGN_Size> DGVM_Runtime::_tag_ptr_value(VALUE_Type* pVal,
  u1 tag_value, u1 tag_size)
{
 //return nullptr;

 mz::tagged_ptr<VALUE_Type, ALIGN_Size> result(pVal, tag_value);
 //result.set_ptr(pull_ptr_value<typename std::remove_pointer<VALUE_Type>::type>());
 return result;

}


template<typename VALUE_Type>
mz::tagged_ptr<VALUE_Type> DGVM_Runtime::_tag_ptr_value(VALUE_Type* pVal, u1 tag_size,
  u1 tag_value)
{
// using REM_VALUE_Type = typename std::remove_pointer<VALUE_Type>::type;

 mz::tagged_ptr<VALUE_Type> result(pVal, tag_value);

 //? result.set_tag(tag_size, tag_value);

 //result.set_ptr(pull_ptr_value<typename std::remove_pointer<VALUE_Type>::type>());
 return result;
}


template<typename VALUE_Type>
mz::tagged_ptr<VALUE_Type> DGVM_Runtime::tag_ptr_value(VALUE_Type* pVal,
  u1 tag_size, u1 tag_value, size_t align_size)
{
 //auto [tag_value, tag_size] = one_byte_deque_._pull<2>();
 //u1 align_size = one_byte_deque_.pull_opt(255);


////  u1 align_size = one_byte_deque_.pull_opt(255);
////  u1 test = one_byte_deque_.pull_opt(255);

// qDebug() << "tag_size = " << tag_size;
// qDebug() << "tag_value = " << tag_value;

//   qDebug() << "align_size = " << align_size;
//   qDebug() << "test = " << test;

 switch (align_size)
 {
  case 255:
   {
//    return 0;
    mz::tagged_ptr<VALUE_Type> result = _tag_ptr_value<VALUE_Type>(pVal, tag_size, tag_value);
    return result;// (n8) result.ptr();
   }
   break;
  default:
   break;
 }

// mz::tagged_ptr<VALUE_Type, Align_size> _tag_ptr_value() = _tag_ptr_value()

 return nullptr;
}



#endif //  DGVM_RUNTIME__TEMPLATES__H
