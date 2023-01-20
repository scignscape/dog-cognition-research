
#undef DOMINION_NAMESPACED
#undef DOMINION_NAMESPACE_DECLARE


#ifdef DOMINION_NODE_NAMESPACE
 #define DOMINION_NODE_NAMESPACED(type) \
  DOMINION_NODE_NAMESPACE::type
#else
#define DOMINION_NODE_NAMESPACED(type) \
 type
#endif


#if defined(DOMINION_OUTER_NAMESPACE)
 #ifdef DOMINION_INNER_NAMESPACE
  #define DOMINION_NAMESPACED(type) \
   DOMINION_OUTER_NAMESPACE::DOMINION_INNER_NAMESPACE::type
  #define DOMINION_NAMESPACE_DECLARE(type) \
   namespace DOMINION_OUTER_NAMESPACE { \
    namespace DOMINION_INNER_NAMESPACE { class type; }}
 #else
  #define DOMINION_NAMESPACED(type) \
   DOMINION_OUTER_NAMESPACE::type
  #define DOMINION_NAMESPACE_DECLARE(type) \
   namespace DOMINION_OUTER_NAMESPACE { class type; }
 #endif
#elif defined(DOMINION_NAMESPACE)
 #define DOMINION_NAMESPACED(type) \
  DOMINION_NAMESPACE::type
 #define DOMINION_NAMESPACE_DECLARE(type) \
  namespace DOMINION_NAMESPACE { class type; }
#else
 #define DOMINION_NAMESPACED(type) \
  type
 #define DOMINION_NAMESPACE_DECLARE(type) \
  class type;
#endif


#ifndef DOMINION_TYPE_DECLARE
#define DOMINION_TYPE_DECLARE(node_method_name, cpp_type_name, type_code_name) \
  DOMINION_NAMESPACE_DECLARE(cpp_type_name)
#endif


#ifndef DOMINION_TYPE_ENUM
#define DOMINION_TYPE_ENUM(node_method_name, cpp_type_name, type_code_name) \
   type_code_name,
#endif


#ifndef DOMINION_TYPE_METHOD
#ifdef NO_CAON
#define DOMINION_TYPE_METHOD(node_method_name, cpp_type_name, type_code_name) \
   caon_ptr<DOMINION_NAMESPACED(cpp_type_name)> node_method_name() const { \
    if(type_code_ == Type_Codes_type::type_code_name) \
     return reinterpret_cast<DOMINION_NAMESPACED(cpp_type_name)*>(vertex_); \
    return caon_ptr<DOMINION_NAMESPACED(cpp_type_name)>();}
#else //NO_CAON
#define DOMINION_TYPE_METHOD(node_method_name, cpp_type_name, type_code_name) \
   caon_ptr<DOMINION_NAMESPACED(cpp_type_name)> node_method_name() const { \
    if(type_code_ == Type_Codes_type::type_code_name) \
     return vertex_.ptr_cast<DOMINION_NAMESPACED(cpp_type_name)>(); \
    return caon_ptr<DOMINION_NAMESPACED(cpp_type_name)>();}
#endif
#endif


#ifndef DOMINION_NODE_ONE_WAY_CONSTRUCTOR
#define DOMINION_NODE_ONE_WAY_CONSTRUCTOR( \
   node_method_name, cpp_type_name, type_code_name) \
 DOMINION_NODE_ONE_WAY_CONSTRUCTOR_ \
  (DOMINION_NODE_TYPE, node_method_name, cpp_type_name, type_code_name)
#endif


#ifdef NO_CAON
#ifndef DOMINION_NODE_ONE_WAY_CONSTRUCTOR_
#define DOMINION_NODE_ONE_WAY_CONSTRUCTOR_( \
   node_type, node_method_name, cpp_type_name, type_code_name) \
  node_type(caon_ptr<DOMINION_NAMESPACED(cpp_type_name)> v) \
   : node_type::node_ptr_base_type(v) {}
#endif
#else
#ifndef DOMINION_NODE_ONE_WAY_CONSTRUCTOR_
#define DOMINION_NODE_ONE_WAY_CONSTRUCTOR_( \
   node_type, node_method_name, cpp_type_name, type_code_name) \
  node_type(caon_ptr<DOMINION_NAMESPACED(cpp_type_name)> v) \
   : node_type::node_ptr_base_type(v) {}
#endif
#endif //NO_CAON


#ifndef DOMINION_NODE_CONSTRUCTOR
#define DOMINION_NODE_CONSTRUCTOR(node_method_name, cpp_type_name, type_code_name) \
   DOMINION_NODE_ONE_WAY_CONSTRUCTOR(node_method_name, cpp_type_name, type_code_name); \
   DOMINION_TYPE_METHOD(node_method_name, cpp_type_name, type_code_name);
#endif

#ifndef DOMINION_RETRIEVE_TYPE_CODE
#define DOMINION_RETRIEVE_TYPE_CODE(node_method_name, \
  cpp_type_name, type_code_name) \
 DOMINION_RETRIEVE_TYPE_CODE_(DOMINION_NODE_NAMESPACED(DOMINION_NODE_TYPE), \
  node_method_name, cpp_type_name, type_code_name)
#endif

#ifndef DOMINION_RETRIEVE_TYPE_CODE_
#define DOMINION_RETRIEVE_TYPE_CODE_(node_type, \
  node_method_name, cpp_type_name, type_code_name) \
template<> \
typename node_type::Galaxy_type::Type_Codes_type \
 dominion_get_type_code<node_type::Dominion_type, \
   DOMINION_NAMESPACED(cpp_type_name)>() { \
 return node_type::Galaxy_type::Type_Codes_type::type_code_name; \
}
#endif



