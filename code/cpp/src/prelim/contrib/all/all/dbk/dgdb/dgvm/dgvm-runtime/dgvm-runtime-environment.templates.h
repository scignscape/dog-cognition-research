
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DGVM_RUNTIME_ENVIRONMENT__TEMPLATES__H
#define DGVM_RUNTIME_ENVIRONMENT__TEMPLATES__H

#include <QVariant>


USING_KANS(DGVM)



namespace std {
 template<class T, std::size_t N>
 struct tuple_size<DGVM_Runtime_Environment::One_Byte_Deque::_binder<T, N>>
    : std::integral_constant<std::size_t, N> { };

    template<std::size_t I, std::size_t N, class T>
    struct tuple_element<I, DGVM_Runtime_Environment::One_Byte_Deque::_binder<T, N>> { using type = T; };
}



template <std::size_t N, typename T>
auto DGVM_Runtime_Environment::One_Byte_Deque::binding_rhs(const std::vector<T>& vec) {
  return _binder<T, N>{vec};
}

template<typename VALUE_Type = void**>
void DGVM_Runtime_Environment::get_ptr_tag()
{
 n8 raw_value = pull_raw_value<n8>();
 u1 tag_value = dgr_->template get_ptr_tag<VALUE_Type>(raw_value);
 push_byte_value(tag_value);
}

template<typename VALUE_Type = void**>
void DGVM_Runtime_Environment::detag_ptr()
{
 n8 raw_value = pull_raw_value<n8>();
 VALUE_Type* ptr = dgr_->template detag_ptr<VALUE_Type>(raw_value);

 push_ptr_value(ptr);
}





template<typename VALUE_Type>
void DGVM_Runtime_Environment::tag_ptr_value()
{
 VALUE_Type* pVal = pull_ptr_value<VALUE_Type>();
 auto [tag_value, tag_size] = one_byte_deque_._pull<2>();
 u1 align_size = one_byte_deque_.pull_opt(255);

// n8 result = reinterpret_cast<uintptr_t>( dgr_->tag_ptr_value(pVal, tag_value, tag_size, align_size) );
 n8 result = (n8) dgr_->tag_ptr_value(pVal, tag_size, tag_value, align_size).raw_value();

 push_raw_value(result);
}



template<typename VALUE_Type>
void DGVM_Runtime_Environment::push_ptr_value(VALUE_Type* pVal)
{
 QVariant qv;
 qv.setValue(pVal);
 qvariant_deque_.push_back(qv);
}


template<typename VALUE_Type>
void DGVM_Runtime_Environment::push_raw_value(VALUE_Type val)
{
 QVariant qv;
 qv.setValue(val);
 qvariant_deque_.push_back(qv);
}


template<typename VALUE_Type>
VALUE_Type DGVM_Runtime_Environment::yield()
{
 VALUE_Type result = preyield<VALUE_Type>();
 qvariant_deque_.pop_back();
 return result;
}


template<typename VALUE_Type>
VALUE_Type DGVM_Runtime_Environment::preyield()
{
 QVariant qvar = qvariant_deque_.back();
 return qvar.value<VALUE_Type>();
}



#endif //  DGVM_RUNTIME_ENVIRONMENT__TEMPLATES__H
