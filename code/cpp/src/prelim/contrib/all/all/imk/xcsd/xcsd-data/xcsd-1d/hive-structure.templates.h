
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef HIVE_STRUCTURE__TEMPLATES__H
#define HIVE_STRUCTURE__TEMPLATES__H


#include "xcns.h"
#include "hive-structure.h"

XCNS_(XCSD)


//template<typename GALAXY_Type>
//typename GALAXY_Type::element_type&

template<typename INDEX_Types>
typename Hive_Structure<INDEX_Types>::Hive_Layer* Hive_Structure<INDEX_Types>
  ::get_layer_for_indexed_location(nnx block_number, nnx layer_order)
{
 Hive_Layer* result = get_layer_by_layer_order(block_number, layer_order);
 check_init_layer(result);
 return result;
}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>
  ::get_location(typename INDEX_Types::Numeric_Index_type nix)
{
 nnx inner_index = fixed_size()? nix : get_inner_index(nix);
 nnx layer_order = fixed_size()? 0 :
   get_layer_order(nix);
 nnx block_number = fixed_size()? 0 : get_block_number(nix);

 Hive_Layer* hl = nullptr;

 if(fixed_size())
   hl = layer_ptr();
 else
 {
  hl = get_layer_for_indexed_location(block_number, layer_order);
 }
 return &((u1*)hl->elements_)[value_size_ * inner_index];
}

template<typename INDEX_Types>
void Hive_Structure<INDEX_Types>
  ::resize(nx nix)
{
 set_total_size(nix);
 if(layer_size_ < 0)
 {
  pre_iterator pre = parse_location(nix - 1);
  Hive_Layer* hl = get_layer_by_layer_order(pre.block_number, pre.layer_order);
  check_init_layer(hl);
 }
}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>
  ::rebound(nx nix)
{
 if(layer_size_ < 0)
 {
  if(total_size() <= nix)
  {
   resize(nix + 1);
   return get_location(nix);
  }
  return nullptr;
 }
 // // any other cases?
 return nullptr;
}

//VAL_Type* result =

//template<typename INDEX_Types>
//void* Hive_Structure<INDEX_Types>
//  ::fetch_at(nx nix, nx fallback, u1* val)
//{
// void* result = fetch(nix, fallback);
// if(!result)
// {
//  result = get_indexed_location_unchecked(fallback);
//  memcpy(result, val, value_size_);
//  rebound_to(fallback);
// }
// return result;
//// if(nix >= total_size())
////   return get(fallback);
//// return get_indexed_location(nix);
//}


template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>
  ::fetch_at(nx nix, Out_of_Bounds_Resolution_Flags oob)
{
 if(nix < total_size())
   return get_raw_indexed_location(nix);

 void* result_after_rebound = nullptr;
 void* result_without_rebound = nullptr;
 void* default_value_ptr = nullptr;

 if(oob & Out_of_Bounds_Resolution_Flags::Automatic_Rebound)
 {
  result_after_rebound = rebound(nix);
 }

 if(oob & Out_of_Bounds_Resolution_Flags::Accept_Initialize_to_Zero)
 {
  default_value_ptr = get_zeroed_location();
 }

 if(default_value_ptr)
 {
  if(result_after_rebound)
    memcpy(result_after_rebound, default_value_ptr, value_size_);

  else
    result_without_rebound = default_value_ptr;
 }

 if(result_after_rebound)
   return result_after_rebound;

 return result_without_rebound;
}

// if( (oob & Out_of_Bounds_Resolution_Flags::Alternate_Fallback_Index_Options)
//    == (u1) Out_of_Bounds_Resolution_Flags::Defer_to_Alternate_Fallback_Index)
// {
//  return fetch_at(fallback, oob);
// }

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>
  ::fetch_out_of_bounds(nx nix, Out_of_Bounds_Resolution_Flags oob)
{
 void* result_after_rebound = nullptr;
 void* result_without_rebound = nullptr;
 void* default_value_ptr = nullptr;

 if(oob & Out_of_Bounds_Resolution_Flags::Automatic_Rebound)
 {
  result_after_rebound = rebound(nix);

  if(!result_after_rebound)
    // // maybe some memory allocation problem; anyhow, not much we can do
    return nullptr;
 }


 if(oob & Out_of_Bounds_Resolution_Flags::Accept_Initialize_to_Zero)
 {
  default_value_ptr = get_zeroed_location();
 }
 else if(oob & Out_of_Bounds_Resolution_Flags::Use_Exceptions)
  throw ; // throw what?

 if(default_value_ptr)
 {
  if(result_after_rebound)
    memcpy(result_after_rebound, default_value_ptr, value_size_);

  else
    result_without_rebound = default_value_ptr;
 }

 if(result_after_rebound)
 {
  // //  possible opportunity to log resizing ...
  return result_after_rebound;
 }

 return result_without_rebound;

 //return get_indexed_location(nix);
}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>
  ::fetch(nx nix, Out_of_Bounds_Resolution_Flags oob)
{
 if(nix < total_size())
   return get_raw_indexed_location(nix);
 return fetch_out_of_bounds(nix, oob);
}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>
  ::get(nx nix)
{
 if(nix >= total_size())
   return nullptr;
 return get_indexed_location(nix);
}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>
  ::get_indexed_location(nnx block_number, nnx layer_order, nnx inner_index)
{
 Hive_Layer* hl = get_layer_for_indexed_location(block_number, layer_order);
 return &((u1*)hl->elements_)[value_size_ * inner_index];
}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>
  ::get_raw_indexed_location(nnx block_number, nnx layer_order, nnx inner_index)
{
 Hive_Layer* hl = get_layer_by_layer_order(block_number, layer_order);
 return &((u1*)hl->elements_)[value_size_ * inner_index];
}

//void* get_raw_indexed_location(nx nix);
//void* get_raw_indexed_location(nnx block_number, nnx layer_order, nnx inner_index);



template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>::contiguous(nx nix1, nx nix2, QVector<QPair<void*, nx>>* breakdown)
{
 void* result = contiguous(nix1, nix2);
 if(result)
   return result;

 if(fixed_size())
   return nullptr;

// pre_iterator pre1 = parse_location(nix1);
// pre_iterator pre2 = parse_location(nix2);
// nx

 nx layer_start = get_layer_rank(nix1);
 nx layer_end = get_layer_rank(nix2);

 nnx ls = layer_size();
 Hive_Layer* hl1 = get_layer_by_layer_rank(layer_start);
 nnx ii = get_inner_index(nix1);
 breakdown->push_back({&((u1*)hl1->elements_)[ii * value_size_], ls - ii});

 nnx offset = 1;
 while(layer_start + offset < layer_end)
 {
  Hive_Layer* hl = get_layer_by_layer_rank(layer_start + offset);
  breakdown->push_back({&((u1*)hl->elements_)[0], ls});
  ++offset;
 }

 Hive_Layer* hl2 = get_layer_by_layer_rank(layer_end);
 breakdown->push_back({&((u1*)hl2->elements_)[0], get_inner_index(nix2) + 1});

 return nullptr;
}


template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>::contiguous(nx nix1, nx nix2)
{
 if(layer_size_ > 0)
   return &((u1*)(single_layer_.elements_))[nix1 * value_size_];

 if(layer_size_ == 0)
 {
  // // is this all?
  return &((u1*)(array_package_->layer_.elements_))[nix1 * value_size_];
 }

 pre_iterator pre1 = parse_location(nix1);
 pre_iterator pre2 = parse_location(nix2);

 if( (pre1.block_number == pre2.block_number)
    && (pre1.layer_order == pre2.layer_order) )
 {
  return &((u1*)(get_layer_by_layer_order(pre1.block_number, pre1.layer_order)->elements_))
    [pre1.inner_index * value_size_];
 }

 return nullptr;
}


//block_package_->first_block_;
//nx lcount = block_package_->block_size_;

//nx block_index = layer_order % lcount;
//nx block_number = layer_order / lcount;
//nx order = 0;
//while(order < block_number)
//{
// if(!hlb->next_)
// {
//  Hive_Layer* new_hl = new_hive_layers();
//  Hive_Layer_Block* new_hb = new Hive_Layer_Block{new_hl, nullptr};
//  hlb->next_ = new_hb;
// }
// hlb = hlb->next_;
// ++order;
//}


template<typename INDEX_Types>
typename Hive_Structure<INDEX_Types>::Hive_Layer_Block*
Hive_Structure<INDEX_Types>::get_block_by_number(nnx desired_block_number)
{
 if(fixed_size())
   return nullptr;

 return check_init_blocks(desired_block_number);
}

template<typename INDEX_Types>
typename Hive_Structure<INDEX_Types>::Hive_Layer_Block*
Hive_Structure<INDEX_Types>::check_init_blocks(nnx max)
{
 Hive_Layer_Block** current_block = &block_package_->first_block_;
 Hive_Layer_Block* result = nullptr;
 for(nnx block_number = 0; block_number <= max; ++block_number)
 {
  if(*current_block)
  {
   result = *current_block;
   current_block = &(*current_block)->next_;
   continue;
  }
  Hive_Layer* nhl = new_hive_layers();
  (*current_block) = new Hive_Layer_Block{nhl, nullptr};
  if(result)
    result->next_ = *current_block;
  result = *current_block;
 }
 return result;
}

template<typename INDEX_Types>
void Hive_Structure<INDEX_Types>::pop_first_block()
{
 if(fixed_size())
   return;

 if(Hive_Layer_Block* hb = block_package_->first_block_)
 {
  if(Hive_Layer_Block* nhb = hb->next_)
  {
   block_package_->first_block_ = nhb;
   delete_block(hb);
  }
  else
  {
   delete_block(hb);
   block_package_->first_block_ = nullptr;
  }
 }
}

template<typename INDEX_Types>
void Hive_Structure<INDEX_Types>::pop_back()
{
 if(total_size_ == 0)
   return;

 --total_size_;

 // //  total_size_ is now also index of the prior last position
 nnx blkp = get_block_position(total_size_);

 if(blkp == 0)
 {
  nnx blkn = get_block_number(total_size_);
  Hive_Layer_Block* hlb = check_init_blocks(blkn);
  if(hlb)
  {
   if(hlb->next_)
   {
    delete_block(hlb->next_);
    hlb->next_ = nullptr;
   }
  }
 }
}

template<typename INDEX_Types>
typename Hive_Structure<INDEX_Types>::Hive_Layer*
Hive_Structure<INDEX_Types>::new_hive_layers()
{
 Hive_Layer* result = new Hive_Layer[block_size()];
 for(int i = 0; i < block_size(); ++i)
   result[i] = {nullptr};
 return result;
}

template<typename INDEX_Types>
void Hive_Structure<INDEX_Types>::push_first_block()
{
 Hive_Layer* new_hl = new_hive_layers();
 Hive_Layer_Block* new_hlb = new Hive_Layer_Block{new_hl, block_package_->first_block_};
 block_package_->first_block_ = new_hlb;
//?
// void* mem = malloc(block_size() * value_size_);
// first_block_ = new Hive_Block{mem, first_block_};
// total_size_ += block_size_;
}


template<typename INDEX_Types>
void Hive_Structure<INDEX_Types>::increment_iterator(iterator& hit)
{
 if(++hit.total_index == total_size_)
   hit.total_index = the_invalid_index();
 if(++hit.inner_index == layer_size())
 {
  hit.inner_index = 0;
  ++hit.layer_order;
  if(hit.layer_order == block_size())
  {
   hit.layer_order = 0;
   ++hit.block_number;
  }
 }
}


template<typename INDEX_Types>
void Hive_Structure<INDEX_Types>::decrement_iterator(iterator& hit)
{
 if(hit.total_index == 0)
 {
  hit.total_index = the_invalid_index();
  return;
 }
 --hit.total_index;


 if(hit.inner_index == 0)
 {
  hit.inner_index = layer_size() - 1;
  if(hit.layer_order == 0)
  {
   hit.layer_order = block_size() - 1;
   --hit.block_number;
  }
  else
    --hit.layer_order;
 }
 else
   --hit.inner_index;
}

template<typename INDEX_Types>
typename Hive_Structure<INDEX_Types>::pre_iterator
Hive_Structure<INDEX_Types>::parse_location(nx nix)
{
 return{
   get_block_number(nix),
   get_layer_order(nix),
   get_inner_index(nix)
 };
}

template<typename INDEX_Types>
void Hive_Structure<INDEX_Types>::position_iterator(iterator& hit, Numeric_Index_type nix)
{
 if(nix >= total_size_)
 {
  hit.total_index = the_invalid_index();
  return;
 }
 hit.total_index = nix;
 pre_iterator pre = parse_location(nix);
 hit.block_number = pre.block_number; // (nnx)(nix / ((nx) block_size() * layer_size()));
 hit.layer_order = pre.layer_order; //(nnx)(nix / layer_size()) % block_size();
 hit.inner_index = pre.inner_index; // nix % layer_size();
}



template<typename INDEX_Types>
void Hive_Structure<INDEX_Types>::reverse_iterator(iterator& hit)
{
 if(total_size_ == 0)
 {
  hit.total_index = the_invalid_index();
  return;
 }
 position_iterator(hit, total_size_);
}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>::get_back_location()
{
 if(total_size_ == 0)
   return nullptr;
 return get_indexed_location(total_size_ - 1);
}

template<typename INDEX_Types>
void Hive_Structure<INDEX_Types>::check_start_iterator(iterator& hit)
{
 if(total_size_ == 0)
 {
  hit.total_index = the_invalid_index();
  return;
 }
}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>::get_iterator_location(iterator& hit)
{
 return get_indexed_location(hit.block_number, hit.layer_order, hit.inner_index);
}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>
  ::get_push_back_location()
{
 return get_indexed_location_unchecked(total_size_);
}

//void* get_back_location();

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>
  ::get_indexed_location(typename INDEX_Types::Numeric_Index_type nix)
{
 if(nix >= total_size_)
   return nullptr;

 return get_indexed_location_unchecked(nix);
}

template<typename INDEX_Types>
typename Hive_Structure<INDEX_Types>::Hive_Layer*
Hive_Structure<INDEX_Types>
  ::get_layer_by_layer_order(nnx block_number, nnx layer_order)
{
 Hive_Layer_Block* hlb = get_block_by_number(block_number);
 return &hlb->layers_[layer_order];
}

// if(fixed_size())
//  return layer_ptr();
// Hive_Layer* result = nullptr;
// Hive_Layer_Block* hlb = block_package_->first_block_;
// nx lcount = block_package_->block_size_;
// nx block_index = layer_order % lcount;
// nx block_order = layer_order / lcount;
// nx order = 0;
// while(order < block_order)
// {
//  if(!hlb->next_)
//  {
//   Hive_Layer* new_hl = new Hive_Layer[lcount];
//   for(int i = 0; i < lcount; ++i)
//    new_hl[i] = {nullptr};
//   Hive_Layer_Block* new_hb = new Hive_Layer_Block{new_hl, nullptr};
//   hlb->next_ = new_hb;
//  }
//  hlb = hlb->next_;
//  ++order;
// }
// result = &(hlb->layers_)[block_index];
// if(result->elements_ == nullptr)
// {
//  result->elements_ = malloc(value_size_ * layer_size());
// }
// return result;
//}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>::get_indexed_location_unchecked(typename INDEX_Types::Numeric_Index_type nix)
{
 if(fixed_size())
   return &((u1*)get_fixed_size_layer()->elements_)[nix * value_size_];

 pre_iterator pre = parse_location(nix);

// nnx inner_index = get_inner_index(nix);
// nnx layer_order = get_layer_order(nix);
// nnx block_number = get_block_number(nix);

 return get_indexed_location(pre.block_number, pre.layer_order, pre.inner_index);
}

template<typename INDEX_Types>
void* Hive_Structure<INDEX_Types>::get_raw_indexed_location(typename INDEX_Types::Numeric_Index_type nix)
{
  if(fixed_size())
    return &((u1*)get_fixed_size_layer()->elements_)[nix * value_size_];

 pre_iterator pre = parse_location(nix);

// nnx inner_index = get_inner_index(nix);
// nnx layer_order = get_layer_order(nix);
// nnx block_number = get_block_number(nix);

 return get_raw_indexed_location(pre.block_number, pre.layer_order, pre.inner_index);
}

template<typename INDEX_Types>
void Hive_Structure<INDEX_Types>::increment_total_size()
{
 ++total_size_;
}



_XCNS(XCSD)


#endif // HIVE_STRUCTURE__TEMPLATES__H
