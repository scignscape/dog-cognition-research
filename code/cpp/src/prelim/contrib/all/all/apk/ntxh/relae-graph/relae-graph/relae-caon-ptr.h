
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RELAE_CAON_PTR__H
#define RELAE_CAON_PTR__H


#include <memory>

#undef NO_CAON

#ifdef NO_CAON

#include <QSharedPointer>

#define CAON_PTR_DEBUG(type ,ptr)
#define CAON_EVALUATE_DEBUG(type, name ,ptr)
#define CAON_PTR_B_DEBUG(type ,ptr)
#define CAON_PTR_BUNDLE_DEBUG(type ,ptr)
#define CAON_DEBUG_NOOP


template<typename T>
struct get_pointer
{
 typedef T* type;
};

template<typename T>
using caon_ptr = typename get_pointer<T>::type;


#else // NO_CAON

#ifdef CAON_DEBUG
#define CAON_EVALUATE_DEBUG(type, name ,ptr) \
 const type& name = *ptr;
#define CAON_PTR_DEBUG(type ,ptr) \
 CAON_EVALUATE_DEBUG(type, _##ptr, ptr)
#define CAON_PTR_B_DEBUG(type ,ptr) \
 CAON_EVALUATE_DEBUG(type, _##ptr, b.ptr)
#define CAON_PTR_BUNDLE_DEBUG(type ,ptr) \
 CAON_EVALUATE_DEBUG(type, _##ptr, b.ptr)
#define CAON_DEBUG_NOOP int _CAON_DEBUG_NOOP_ = 0;
#else
#define CAON_PTR_DEBUG(type ,ptr)
#define CAON_EVALUATE_DEBUG(type, name ,ptr)
#define CAON_PTR_B_DEBUG(type ,ptr)
#define CAON_PTR_BUNDLE_DEBUG(type ,ptr)
#define CAON_DEBUG_NOOP
#endif

template<typename T>
class caon_ptr;

template<typename T>
struct caon_wrapper_type
{
 typedef caon_ptr<T> type;
};

template<typename T>
struct caon_wrapper_type<caon_ptr<T>>
{
 typedef caon_ptr<T> type;
};

template<typename TO_Type, typename FROM_Type>
static caon_ptr<TO_Type> caon_reinterpret_cast(FROM_Type* ptr);

template<typename T>
class caon_ptr
{
 template<typename FROM_Type, typename TO_Type>
 static TO_Type static_caon_cast(caon_ptr<FROM_Type> rhs)
 {
  return (TO_Type)(rhs.value_);
 }

// template<typename TO_Type, typename FROM_Type>
// static TO_Type caon_static_cast(caon_ptr<FROM_Type> rhs)
// {
//  return static_cast<TO_Type>(rhs.raw_pointer());
// }

 enum Value_Classification
 {
  // //  The following are tags used by Clasp:
  //  Raw_Ptr, Special_Value, Value_Frame, Fixnum
  Raw_Ptr = 0, Checked_Ptr = 1, Array_Ptr = 2, Fixnum = 3
 };

 static constexpr size_t classifying_mask = 3; //0b11

 static constexpr size_t tagged_null = 9;

 size_t value_;


public:

 typedef T raw_pointer_type;

 void do_delete()
 {
  delete raw_pointer();
 }

 template<typename TO_Type>
 caon_ptr<TO_Type> caon_reinterpret_cast()
 {
  return ::caon_reinterpret_cast<TO_Type, T>(raw_pointer());
 }

 template<typename TO_Type>
 caon_ptr<TO_Type> caon_static_cast()
 {
  // //  Will cast from TO_Type*
  return (TO_Type*) raw_pointer();
 }

 caon_ptr(const caon_ptr& rhs) : value_(rhs.value_) {}

 caon_ptr(size_t v)
  : value_(v)
 {

 }

 caon_ptr()
  : value_(tagged_null)
 {

 }

 caon_ptr(std::nullptr_t)
  : value_(tagged_null)
 {

 }

 size_t raw_direct_value() const
 {
  return value_;
 }

 void* raw_value_as_pointer() const
 {
  return (void*) value_;
 }

 template<typename U>
 caon_ptr<U> ptr_cast() const
 {
  return (caon_ptr<U>)(value_);
 }

 template<typename TO_Type>
 typename caon_wrapper_type<TO_Type>::type caon_cast()
 {
  return static_caon_cast<T, typename caon_wrapper_type<TO_Type>::type>(*this);
 }

 template<typename GALAXY_Type>
 static typename GALAXY_Type::Root_Vertex_type root_cast(T* t)
 {
  return caon_ptr<T>(t).template caon_cast<typename GALAXY_Type::Root_Void>();
 }

 caon_ptr(T* t)
 {
  if(t == nullptr)
  {
   value_ = tagged_null;
  }
  else
  {
   value_ = (size_t) t;
   // //  If it is desired to always use a checked flag
   //     (but can lead to performance degradation)
   //     set_checked();
  }
 }

 caon_ptr(const T* t)
 {
  if(t == nullptr)
  {
   value_ = tagged_null;
  }
  else
  {
   value_ = (size_t) t;
   //set_checked();
  }
 }

 void set_direct()
 {
  value_ |= Fixnum;
 }

 void set_checked()
 {
  value_ |= Checked_Ptr;
 }

 void set_array()
 {
  value_ |= Array_Ptr;
 }

 operator bool() const
 {
  if(value_ == 0)
   return false;
  if(is_checked())
  {
   return value_ != tagged_null;
  }
  else
  {
   return raw_pointer() != nullptr;
  }
 }

 bool is_raw() const
 {
  return (value_ & classifying_mask) == Raw_Ptr;
 }

 bool is_checked() const
 {
  return (value_ & classifying_mask) == Checked_Ptr;
 }

 bool is_array() const
 {
  return (value_ & classifying_mask) == Array_Ptr;
 }

 bool is_fixnum() const
 {
  return (value_ & classifying_mask) == Fixnum;
 }

 inline T* operator->()
 {
  return raw_pointer();
 }

 inline const T* operator->() const
 {
  return raw_pointer();
 }

 inline T& operator*()
 {
  return *raw_pointer();
 }

 inline const T& operator*() const
 {
  return *raw_pointer();
 }

 T* raw_pointer()
 {
  if(is_checked())
  {
   if(value_ == tagged_null)
     return nullptr;
  }
  return (T*) (value_ & (~classifying_mask));
 }

 const T* raw_pointer() const
 {
  return (T*) (value_ & (~classifying_mask));
 }

 size_t get_fixnum()
 {
  return value_ >> 2;
 }

 void set_fixnum(size_t v)
 {
  set_raw_value(v << 2);
  value_ |= Fixnum;
 }

 friend bool operator <(caon_ptr lhs, caon_ptr rhs)
 {
  return lhs.raw_pointer() < rhs.raw_pointer();
 }

 friend bool operator >(caon_ptr lhs, caon_ptr rhs)
 {
  return lhs.raw_pointer() > rhs.raw_pointer();
 }

 friend bool operator ==(caon_ptr lhs, caon_ptr rhs)
 {
  return lhs.raw_pointer() == rhs.raw_pointer();
 }

 friend bool operator !=(caon_ptr lhs, caon_ptr rhs)
 {
  return lhs.raw_pointer() != rhs.raw_pointer();
 }


 friend bool operator |=(caon_ptr lhs, size_t rhs)
 {
  return lhs.value_ |= rhs;
 }

 template<typename U>
 void set_direct_value(U t)
 {
  value_ = t << 2;
  set_direct();
 }

 template<typename U>
 void set_raw_value(U t)
 {
  value_ = t;
 }
};

template<typename GALAXY_Type, typename T>
typename GALAXY_Type::Root_Vertex_type
 caon_root_cast(T* t)
{
 return caon_ptr<T>::template root_cast<GALAXY_Type>(t);
}

template<typename TO_Type, typename FROM_Type>
static caon_ptr<TO_Type> caon_reinterpret_cast(FROM_Type* ptr)
{
 return caon_ptr<TO_Type>(reinterpret_cast<TO_Type*>(ptr));
}

#endif


#endif //RELAE_CAON_PTR__H
