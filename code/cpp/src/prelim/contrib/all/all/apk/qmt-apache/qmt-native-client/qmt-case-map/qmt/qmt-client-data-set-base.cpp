
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qmt-client-data-set-base.h"

//#include "MapGraphicsView.h"

#include "global-types.h"

#include <QMessageBox>

#include <QDebug>

#include <QFile>

#include <QVector2D>



QMT_Client_Data_Set_Base::QMT_Client_Data_Set_Base()
  :  current_bind_object_(nullptr), current_bind_vector_(nullptr)
{

}


void QMT_Client_Data_Set_Base::load_ntxh_file(QString file_path)
{
 NTXH_Document doc(file_path);

 prepare_ntxh_document(doc, file_path);

 doc.parse();

 typedef NTXH_Graph::hypernode_type hypernode_type;

 NTXH_Graph& g = *doc.graph();
 const QVector<hypernode_type*>& v = g.hypernodes();

 for(hypernode_type* h : v)
 {
  read_ntxh_hypernode(g, h);
 }

 conclude_ntxh_document(doc, file_path);
}


u4 QMT_Client_Data_Set_Base::match_locations_in_text_file(QString file_path,
  r8 query_latitude, r8 query_longitude,
  u4 number_of_results, u1 latitude_column,
  u1 longitude_column, u1 column_separator,
  s4 allow_duplicates,
  u1 number_of_header_lines, QVector<u1> other_location_columns)
{
 QFile infile(file_path);
 if(!infile.open(QIODevice::ReadOnly))
  return 0;

 for(u1 i = 0; i < number_of_header_lines; ++i)
 {
  if(!infile.atEnd())
    // // header
    infile.readLine();
 }

 u1 larger_column_plus_one = qMax(latitude_column, longitude_column) + 1;

 QVector<QList<QByteArray>> matches(number_of_results);
 QVector<double> deltas(number_of_results);

 QVector<QPair<r8, r8>> llpair;

 u4 abs_allow_duplicates = qAbs(allow_duplicates);
 if(abs_allow_duplicates == 1)
   abs_allow_duplicates = (u4) -1;

 if(abs_allow_duplicates)
   llpair.resize(number_of_results);

 QMap<QPair<r8, r8>, QPair<u4, u4>> llcounts;

 double max_delta = 0;
 u4 max_delta_index = 0;
 u4 matches_active_size = 0;

// //u1 count = 0;
// if(!infile.atEnd())
//  // //  read the header line
//  infile.readLine();
// while(!infile.atEnd())
// {
//  QByteArray qba = infile.readLine();
//  QList<QByteArray> fields = qba.split(',');
//  // //  stop_id,stop_code,stop_name,stop_desc,stop_lat,stop_lon,zone_id
//  r8 lat = fields[4].toDouble();
//  r8 lon = fields[5].toDouble();


 while(!infile.atEnd())
 {
  QByteArray line = infile.readLine().simplified();

  if(line.isEmpty())
    continue;

  // //  this is a hack to strip commas inside quotes, which for
   //    demo purposes could be assumed always to precede spaces

  line.replace(", ", "$");

  QList<QByteArray> qbas = line.split(column_separator);
  if(qbas.size() < larger_column_plus_one)
    continue;

  r8 latitude = qbas[latitude_column].toDouble();
  r8 longitude = qbas[longitude_column].toDouble();

  if(abs_allow_duplicates)
  {
   auto it = llcounts.find({latitude, longitude});
   if(it != llcounts.end())
   {
    if((*it).first < abs_allow_duplicates)
    {
     ++(*it).first;
     if(allow_duplicates > 0)
       matches[it->second] = qbas;
    }
    continue;
   }
  }

  r8 dlat = latitude - query_latitude;
  r8 dlon = longitude - query_longitude;

  QVector2D v2d(dlat, dlon);
  double len = v2d.length();
  if(matches_active_size < number_of_results)
  {
   // // there's room for any candidate no matter how distant
   matches[matches_active_size] = qbas;
   deltas[matches_active_size] = len;

   if(abs_allow_duplicates)
   {
    llcounts.insert({latitude, longitude}, {1, matches_active_size});
    llpair[matches_active_size] = {latitude, longitude};
   }

   if(len > max_delta)
   {
    max_delta_index = matches_active_size;
    max_delta = len;
   }
   ++matches_active_size;
  }
  else if(len < max_delta)
  {
   // //  replace the most distant match
   //    don't bother sorting, we'll just calculate the new largest distance

   if(abs_allow_duplicates)
   {
    QPair<r8, r8> old_pair = llpair[max_delta_index];
    llcounts.remove(old_pair);
    llcounts.insert({latitude, longitude}, {1, max_delta_index});
    llpair[max_delta_index] = {latitude, longitude};
   }

   matches[max_delta_index] = qbas;
   deltas[max_delta_index] = len;
   auto it = std::max_element(deltas.begin(), deltas.end());
   max_delta_index = std::distance(deltas.begin(), it);
   max_delta = *it;
  }
 }
 infile.close();

 for(u4 excess = matches_active_size; excess < number_of_results; ++excess)
 {
  matches.removeLast();
 }

 u1 number_of_location_columns = 2 + other_location_columns.size();

 // //  for the distance
 u1 number_of_added_location_columns = 1;

 if(abs_allow_duplicates)
   // //  An extra column for duplicate counts
    //
   ++number_of_added_location_columns;

 QSet<u1> location_column_set(other_location_columns.begin(),
   other_location_columns.end());

 location_column_set.insert(latitude_column);
 location_column_set.insert(longitude_column);

 // //  this is to leave an extra column for item-specific
  //    data that may be added later, like graphics item style ...
 u1 number_of_extra_info_columns = 1;

 u1 index = 0;
 QVector<Match_Info> info(matches.length());
 std::transform(matches.begin(), matches.end(), info.begin(),
   [&deltas, &index, &llpair, &llcounts, number_of_extra_info_columns,
    &location_column_set, &other_location_columns, number_of_location_columns,
    number_of_added_location_columns, allow_duplicates,
    abs_allow_duplicates, latitude_column, longitude_column]
   (const QList<QByteArray> qbas) -> decltype (info.value(0))
 {
  u1 number_of_non_location_columns = qbas.size() - number_of_location_columns;

  number_of_non_location_columns += number_of_extra_info_columns;

  QVector<_r8_or_ptr> location_fields(number_of_location_columns + number_of_added_location_columns);

  u1 f = 0;

  if(abs_allow_duplicates)
  {
   location_fields[f]._r8 = llpair[index].first;
   location_fields[++f]._r8 = llpair[index].second;
   location_fields[++f]._r8 = deltas[index];
   if(allow_duplicates < 0)
     // // have to do the double conversion first!
     location_fields[++f]._r8 = -(r8)llcounts[llpair[index]].first;
   else
     location_fields[++f]._r8 = llcounts[llpair[index]].first;
  }
  else
  {
   // //  recalculating the lat/lon but this seems more
    //    efficient than storing then overwriting the lat/lon
    //    for all temporary values unless we need them for
    //    duplicate counts.  Plus I suppose it's not
    //    impossible that some variation on the algorithm
    //    might allow a hook where the lat/lon registered
    //    in the result set might differ somehow than
    //    the one involved in calculating distances
    //    (maybe different levels of precision?)
   location_fields[f]._r8 = qbas[latitude_column].toDouble();
   location_fields[++f]._r8 = qbas[longitude_column].toDouble();
   location_fields[++f]._r8 = deltas[index];
  }

  ++index;
  for(u1 oc : other_location_columns)
    location_fields[++f]._r8 = qbas[oc].toDouble();

  // //  this could be more efficient if we know all matches
   //    have the same number of columns, they we would
   //    could form a list of non-location columns ahead of
   //    time.  But I'm not sure that would be a noticeable
   //    optimization and anyways it might be better to
   //    support different-length matches
  QVector<QString> svec(number_of_non_location_columns);
  for(u1 c = 0, sc = number_of_extra_info_columns; sc < number_of_non_location_columns; ++c)
  {
   if(location_column_set.contains(c))
     continue;

   svec[sc] = QString::fromLatin1(qbas[c]);

   // //  again, due to the hack to deal with commas-in-quotes
   svec[sc].replace("$", ", ");
   ++sc;
  }

  return {location_fields, svec.toList()};
 });

 current_matches_.clear();
 current_matches_.resize(info.size());

 // //  an alternative would be to filter out results
  //    that exceed some threshold distance ...
 std::partial_sort_copy(info.begin(), info.end(),
   current_matches_.begin(), current_matches_.end(),
   [](const Match_Info& lhs, const Match_Info& rhs)
 {
  return lhs.location_fields[2]._r8 < rhs.location_fields[2]._r8;
 });

 return matches_active_size;
}

