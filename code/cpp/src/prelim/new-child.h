
#ifndef NEW_CHILD__H
#define NEW_CHILD__H

template<typename PARENT_Type, typename CHILD_Type>
struct _new_child
{
 PARENT_Type* _this;

 template<typename ARG1_Type>
 CHILD_Type* operator()(ARG1_Type a1)
 {
  return new CHILD_Type(a1, _this);
 }

 CHILD_Type* operator()()
 {
  return new CHILD_Type(_this);
 }

 operator CHILD_Type*()
 {
  return operator()();
 }

};

#define new_child(ty) \
  (_new_child<std::remove_pointer<decltype(this)>::type, ty>{this})


#endif
