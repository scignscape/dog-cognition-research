
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PHAONG__H
#define PHAONG__H

#include <functional>

#include <QVector>

#include "accessors.h"

#define PASTE_EXPRESSION(...) __VA_ARGS__

template<typename T, typename Numeric_Index_type = signed short>
struct phaong_galaxy
{
 typedef T hyponode_value_type;
 typedef T index_type;
 typedef T type_descriptor_type;
 typedef Numeric_Index_type numeric_index_type;
};

template<typename GALAXY_Type>
class phaong
{
public:

 typedef typename GALAXY_Type::hyponode_value_type hyponode_value_type;
 typedef typename GALAXY_Type::index_type index_type;
 typedef typename GALAXY_Type::numeric_index_type numeric_index_type;
 typedef typename GALAXY_Type::type_descriptor_type type_descriptor_type;

 struct Hyponode
 {
  hyponode_value_type hypoval;
  type_descriptor_type type_descriptor;
 };

 struct Hypocell
 {
  Hyponode* hyponodes;
 };

 struct Hypocell_Block
 {
  Hypocell* hypocells;
  Hypocell_Block* next;
 };

 struct Hypocell_Array_Package
 {
  Hypocell hypocell;
  numeric_index_type size;
  numeric_index_type min_index;
 };

 struct Hypocell_Block_Package
 {
  Hypocell_Block* first_block_;
  numeric_index_type min_index_;
  numeric_index_type max_index_;
  numeric_index_type cell_size_;
 };

 class Hypernode
 {
  friend class phaong;
  union {
   Hypocell_Block_Package* block_package_;
   Hypocell_Array_Package* array_package_;
   Hypocell cell_;
  };
  numeric_index_type size_;
  type_descriptor_type type_descriptor_;

 public:

  Hypernode(Hypocell_Block_Package* block_package, numeric_index_type size,
    type_descriptor_type type_descriptor)
   :  block_package_(block_package), size_(size),
      type_descriptor_(type_descriptor)
  {
  }

  Hypernode(Hypocell_Array_Package* array_package,
    type_descriptor_type type_descriptor)
   :  array_package_(array_package), size_(0),
      type_descriptor_(type_descriptor)
  {
  }



  Hypernode(Hypocell cell, numeric_index_type size,
    type_descriptor_type type_descriptor)
   :  cell_(cell), size_(size),
      type_descriptor_(type_descriptor)
  {
  }

  Hypernode()
   :  block_package_(nullptr), size_(0)
  {
  }

  ACCESSORS__RGET(type_descriptor_type ,type_descriptor)

  numeric_index_type cell_size()
  {
   if(size_ < 0)
     return -size_;
   if(size_ == 0)
     return array_package_->size;
   return size_;
  }

  Hypocell* cell_ptr()
  {
   if(size_ == 0)
     return &array_package_->hypocell;
   return &cell_;
  }

  bool fixed_size()
  {
   return size_ >= 0;
  }

  void check_max_index(numeric_index_type ind)
  {
   if(size_ < 0)
   {
    if(block_package_->max_index_ < ind)
      block_package_->max_index_ = ind;
   }
  }

  numeric_index_type get_minimum_array_index()
  {
   if(size_ < 0)
     return block_package_->min_index_;
   if(size_ == 0)
     return array_package_->min_index;
   return 0;
  }

  void set_maximum_array_index(numeric_index_type ind)
  {
   if(size_ < 0)
     block_package_->max_index_ = ind;
//   if(size_ == 0)
//     return 0; // array_package_->max_index;
//   return 0;
  }

  numeric_index_type get_maximum_array_index()
  {
   if(size_ < 0)
     return block_package_->max_index_;
   if(size_ == 0)
     return 0; // array_package_->max_index;
   return 0;
  }

  numeric_index_type normalized_array_index(numeric_index_type ind)
  {
   if(size_ < 0)
   {
    numeric_index_type minin = block_package_->min_index_;
    numeric_index_type maxin = block_package_->max_index_;

    ind += minin;
    maxin += minin;
    if(ind > maxin)
      ind = minin;
   }
   else if(size_ == 0)
   {
    numeric_index_type minin = array_package_->min_index;
    ind += minin;
    ind %= array_package_->size;
   }
   return ind;
  }

 };

 struct Hyperedge
 {
  Hypernode* head;
  Hypernode* tail;
  Hypernode* extra;
 };

private:

 std::function<void(phaong&, Hypernode*)> node_add_function_;
 std::function<void(phaong&, Hyperedge*)> edge_add_function_;
 void* user_data_;

 Hyponode* get_hyponode(Hypernode* hn, numeric_index_type ind)
 {
  int cell_index = ind % hn->cell_size();

  int cell_order = hn->fixed_size()? 0 :
    ind / hn->cell_size();

  Hypocell* hc = nullptr;

  if(hn->fixed_size())
    hc = hn->cell_ptr();
  else
  {
   Hypocell_Block_Package* hbp = hn->block_package_;
   Hypocell_Block* hb = hbp->first_block_;
   numeric_index_type csize = hbp->cell_size_;
   int block_cell_index = cell_order % csize;
   int block_cell_order = cell_order / csize;
   int cc = 0;
   while(cc < block_cell_order)
   {
    if(!hb->next)
    {
     Hypocell* hcs = new Hypocell[csize];
     for(int i = 0; i < csize; ++i)
      hcs[i] = {nullptr};
     Hypocell_Block* nhb = new  Hypocell_Block{hcs, nullptr};
     hb->next = nhb;
    }
    hb = hb->next;
    ++cc;
   }
   hc = &(hb->hypocells)[block_cell_index];
   if(hc->hyponodes == nullptr)
   {
    Hyponode* hns = new Hyponode[hn->cell_size()];
    hc->hyponodes = hns;
   }
  }
  return &(hc->hyponodes)[cell_index];
 }

 void _set_data(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type& val, type_descriptor_type* type_descriptor)
 {
  Hyponode* ho = get_hyponode(hn, ind);

  ho->hypoval = val;
  if(type_descriptor)
    ho->type_descriptor = *type_descriptor;
 }

 Hypernode* _new_hypernode(numeric_index_type size,
   type_descriptor_type& type_descriptor,
   numeric_index_type minin, numeric_index_type csize,
   Hypernode** hn = nullptr)
 {
  numeric_index_type sz = size;
  if(sz < 0) sz = -sz;

  Hyponode* hns = new Hyponode[sz];
  Hypocell hc{hns};

  Hypocell_Array_Package* hap;

  if( (size > 0) && (minin != -1) )
  {
   hap = new Hypocell_Array_Package{hc, size, minin};
  }
  else
    hap = nullptr;

  if(csize == -1)
  {
   csize = sz;
   if(minin == -1)
     minin = 1;
  }
  else if(minin == -1)
    minin = 0;


  Hypocell_Block_Package* hbp;

  if(size < 0)
  {
   Hypocell* hcs = new Hypocell[csize];
   hcs[0] = hc;
   for(int i = 1; i < csize; ++i)
   {
    hcs[i] = {nullptr};
   }
   Hypocell_Block* hb = new Hypocell_Block{hcs, nullptr};
   hbp = new Hypocell_Block_Package{hb, minin, 0, csize};
  }
  else
    hbp = nullptr;

  Hypernode* result;

  if(hn)
  {
   result = *hn;
   if(hbp)
   {
    result->block_package_ = hbp;
    result->size_ = size;
   }
   else if(hap)
   {
    result->array_package_ = hap;
    result->size_ = 0;
   }
   else
   {
    result->cell_ = hc;
    result->size_ = size;
   }
   result->type_descriptor_ = type_descriptor;
  }
  else if(hbp)
    result = new Hypernode(hbp, size, type_descriptor);
  else if(hap)
    result = new Hypernode(hap, type_descriptor);
  else
    result = new Hypernode(hc, size, type_descriptor);

  if(node_add_function_)
  {
   node_add_function_(*this, result);
  }
  return result;
 }

public:

 phaong() : node_add_function_(nullptr), edge_add_function_(nullptr),
   user_data_(nullptr)
 {}

 ACCESSORS(PASTE_EXPRESSION(std::function<void(phaong&, Hypernode*)>) ,node_add_function)
 ACCESSORS(PASTE_EXPRESSION(std::function<void(phaong&, Hyperedge*)>) ,edge_add_function)
 ACCESSORS(void* ,user_data)

 template<typename T>
 T* user_data_as()
 {
  return (T*) user_data_;
 }

 void new_hypernode(Hypernode* hn, numeric_index_type size,
   type_descriptor_type type_descriptor = type_descriptor_type(),
   numeric_index_type minin = -1,
   numeric_index_type csize = -1)
 {
  _new_hypernode(size, type_descriptor, minin, csize, &hn);
 }

 void new_hypernode(Hypernode* hn, numeric_index_type size,
   type_descriptor_type& type_descriptor,
   numeric_index_type minin = -1,
   numeric_index_type csize = -1)
 {
  _new_hypernode(size, type_descriptor, minin, csize, &hn);
 }

 Hypernode* new_hypernode(numeric_index_type size,
   numeric_index_type minin, numeric_index_type csize = -1)
 {
  type_descriptor_type type_descriptor;
  return _new_hypernode(size, type_descriptor, minin, csize);
 }

 Hypernode* new_hypernode(numeric_index_type size,
   type_descriptor_type type_descriptor = type_descriptor_type(),
   numeric_index_type minin = -1, numeric_index_type csize = -1)
 {
  return _new_hypernode(size, type_descriptor, minin, csize);
 }

 Hypernode* new_hypernode(numeric_index_type size,
   type_descriptor_type& type_descriptor,
   numeric_index_type minin = -1, numeric_index_type csize = -1)
 {
  return _new_hypernode(size, type_descriptor, minin, csize);
 }

 void set_data(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type val, type_descriptor_type type_descriptor)
 {
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_data(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type val, type_descriptor_type& type_descriptor)
 {
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_data(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type& val, type_descriptor_type type_descriptor)
 {
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_data(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type& val, type_descriptor_type& type_descriptor)
 {
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_data(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type val)
 {
  _set_data(hn, ind, val, nullptr);
 }

 void set_data(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type& val)
 {
  _set_data(hn, ind, val, nullptr);
 }


 void set_sf(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type val, type_descriptor_type type_descriptor)
 {
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_sf(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type val, type_descriptor_type& type_descriptor)
 {
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_sf(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type& val, type_descriptor_type type_descriptor)
 {
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_sf(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type& val, type_descriptor_type& type_descriptor)
 {
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_sf(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type val)
 {
  _set_data(hn, ind, val, nullptr);
 }

 void set_sf(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type& val)
 {
  _set_data(hn, ind, val, nullptr);
 }


 void set_af(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type val, type_descriptor_type type_descriptor)
 {
  ind += hn->get_minimum_array_index();
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_af(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type val, type_descriptor_type& type_descriptor)
 {
  ind += hn->get_minimum_array_index();
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_af(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type& val, type_descriptor_type type_descriptor)
 {
  ind += hn->get_minimum_array_index();
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_af(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type& val, type_descriptor_type& type_descriptor)
 {
  ind += hn->get_minimum_array_index();
  _set_data(hn, ind, val, &type_descriptor);
 }

 void set_af(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type val)
 {
  ind += hn->get_minimum_array_index();
  _set_data(hn, ind, val, nullptr);
 }

 void set_af(Hypernode* hn, numeric_index_type ind,
   hyponode_value_type& val)
 {
  ind += hn->get_minimum_array_index();
  _set_data(hn, ind, val, nullptr);
 }

 void append_af(Hypernode* hn,
   hyponode_value_type& val, type_descriptor_type& type_descriptor)
 {
  numeric_index_type ind = hn->get_maximum_array_index() + 1;
  _set_data(hn, ind, val, &type_descriptor);
 }

 void append_af(Hypernode* hn,
   hyponode_value_type val, type_descriptor_type& type_descriptor)
 {
  numeric_index_type ind = hn->get_maximum_array_index() + 1;
  _set_data(hn, ind, val, &type_descriptor);
 }

 void append_af(Hypernode* hn,
   hyponode_value_type& val, type_descriptor_type type_descriptor)
 {
  numeric_index_type ind = hn->get_maximum_array_index() + 1;
  _set_af(hn, ind, val, &type_descriptor);
 }

 void all_afs(Hypernode* hn,
   std::function<void(hyponode_value_type&)> fn)
 {
//  numeric_index_type min = hn->get_minimum_array_index();
  numeric_index_type max = hn->get_maximum_array_index();
  for(auto i = 1; i <= max; ++i)
    get_af(hn, i, fn);
 }

 void append_af(Hypernode* hn,
   hyponode_value_type val, type_descriptor_type type_descriptor)
 {
  numeric_index_type ind = hn->get_maximum_array_index() + 1;
  hn->set_maximum_array_index(ind);
  ind += hn->get_minimum_array_index();
  _set_data(hn, ind, val, &type_descriptor);
 }

 void get_data(Hypernode* hn, numeric_index_type ind,
   std::function<void(hyponode_value_type&)> fn)
 {
  Hyponode* ho = get_hyponode(hn, ind);
  fn(ho->hypoval);
 }

 void get_af(Hypernode* hn, numeric_index_type ind,
   std::function<void(hyponode_value_type&)> fn)
 {
  numeric_index_type nind = hn->normalized_array_index(ind);
  Hyponode* ho = get_hyponode(hn, nind);
  fn(ho->hypoval);
 }

 void get_sf(Hypernode* hn, numeric_index_type ind,
   std::function<void(hyponode_value_type&)> fn)
 {
  Hyponode* ho = get_hyponode(hn, ind);
  fn(ho->hypoval);
 }

 void get_sfs(Hypernode* hn, QVector<numeric_index_type>& ind,
   std::function<void(QVector<hyponode_value_type>&)> fn)
 {
  QVector<hyponode_value_type> args;
  args.resize(ind.size());
  std::transform(ind.begin(), ind.end(), args.begin(), [this, hn](const numeric_index_type& ind)
  {
   Hyponode* ho = get_hyponode(hn, ind);
   return ho->hypoval;
  });
  fn(args);
 }

 void get_sfsr(Hypernode* hn, QVector<QPair<numeric_index_type, numeric_index_type>>&& ind,
   std::function<void(QVector<hyponode_value_type>&)> fn)
 {
  for(QPair<numeric_index_type, numeric_index_type>& pr : ind)
  {
   QVector<numeric_index_type> v;
   v.resize(pr.second - pr.first + 1);
   for(int i = pr.first; i <= pr.second; ++i)
     v[i - pr.first] = i;
   get_sfs(hn, v, fn);
  }
 }


 void get_sfs(Hypernode* hn, QVector<numeric_index_type>&& ind,
   std::function<void(QVector<hyponode_value_type>&)> fn)
 {
  get_sfs(hn, ind, fn);
 }

 Hyperedge* new_hyperedge(Hypernode* hnh, Hypernode* hnt, Hypernode* hne = nullptr)
 {
  Hyperedge* result = new Hyperedge{hnh, hnt, hne};
  if(edge_add_function_)
  {
   edge_add_function_(*this, result);
  }
  return result;
 }


};

#endif //  PHAONG__H
