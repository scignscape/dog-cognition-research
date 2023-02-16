/**
 *  This file is part of alaCarte.
 *
 *  alaCarte is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  alaCarte is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with alaCarte. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright alaCarte 2012-2013 Simon Dreher, Florian Jacob, Tobias Kahlert, Patrick Niklaus, Bernhard Scheirle, Lisa Winter
 *  Maintainer: Bernhard Scheirle
 */



#include "server/job.hpp"
#include "server/request_manager.hpp"
#include "server/cache.hpp"
#include "server/tile.hpp"
#include "server/tile_identifier.hpp"
#include "server/stylesheet_manager.hpp"
#include "server/stylesheet.hpp"
#include "server/renderer/renderer.hpp"
#include "server/meta_identifier.hpp"
#include "server/http_request.hpp"
#include "general/geodata.hpp"
#include "general/configuration.hpp"
#include "server/render_attributes.hpp"
#include "utils/rect.hpp"
#include "utils/transform.hpp"
#include "utils/statistic.hpp"


#include "qt-logger.h"
#include <QImage>
#include <QPainter>

#include <QBuffer>

#include "_qmt_/job-context.h"
#include "_qmt_/single-job-context.h"

#include "_qmt_/qmt-tile-object.h"


#define STAT_START(_X) 			Statistic::Get()->start(measurement, _X)
#define STAT_STOP(_X) 			Statistic::Get()->stop(measurement, _X)
#define STAT_STATS(_X, _Y, _Z) 	Statistic::Get()->setStats(measurement, _X, _Y, _Z)
#define STAT_WRITE() 			Statistic::Get()->finished(measurement)

/**
 * @brief Creates a new Job and sets the RequestManager.
 *
 * @param config The Configuration, e.g. for the prerender_level.
 * @param manager The RequestManager which holds all important components.
 **/
Job::Job(const shared_ptr<MetaIdentifier>& mid,
		 const shared_ptr<Configuration>& config,
		 const shared_ptr<RequestManager>& manager,
		 const shared_ptr<RenderCanvas>& canvas)
	: manager(manager)
	, config(config)
	, mid(mid)
	, canvas(canvas)
	, measurement(Statistic::Get()->startNewMeasurement(mid->getStylesheetPath(), mid->getZoom()))
{
#ifdef QT_HOOK
 coordinates_save_info_ = nullptr;
 //single_job_context_ = new Single_Job_Context (Job_Context::the_instance()); //(nullptr);
 single_job_context_ = new Single_Job_Context;// (nullptr); //(nullptr);
#endif
 }

/**
 * @brief Computes an rectangle for the given TileIdentifier.
 *
 * @param ti The TileIdentifier.
 **/
FixedRect Job::computeRect(const shared_ptr<TileIdentifier>& ti)
{
	int zoom = ti->getZoom();
	coord_t x0, x1, y0, y1;
	tileToMercator(ti->getX(), ti->getY(), zoom, x0, y0);
	tileToMercator(ti->getX() + 1, ti->getY() + 1, zoom, x1, y1);

	coord_t minX = std::min(x0, x1);
	coord_t minY = std::min(y0, y1);
	coord_t maxX = std::max(x0, x1);
	coord_t maxY = std::max(y0, y1);

 // // qmt
 int xch, ych;
 mercatorToTile(x0, y0, zoom, xch, ych);
 qlog("mercatorToTile: x0 = %1, y0 = %2, x = %3, y = %4, xch = %5, ych = %6\n"_qt
   .arg(x0).arg(y0).arg(ti->getX()).arg(ti->getY()).arg(xch).arg(ych) );

	FixedRect tile(minX, minY, maxX, maxY);
	return tile.grow(tile.getWidth()  * TILE_OVERLAP,
					 tile.getHeight() * TILE_OVERLAP);
}

/**
 * @brief Computes an rectangle for the given MetaIdentifier.
 *
 * @param ti The MetaIdentifier.
 **/
FixedRect Job::computeRect(const shared_ptr<MetaIdentifier>& ti)
{
	int zoom = ti->getIdentifiers()[0]->getZoom();
	coord_t x0, x1, y0, y1;
	tileToMercator(ti->getX(), ti->getY(), zoom, x0, y0);
	tileToMercator(ti->getX() + ti->getWidth(),
				   ti->getY() + ti->getHeight(),
				   zoom, x1, y1);


 // // qmt
 int xch, ych;
 mercatorToTile(x0, y0, zoom, xch, ych);
 qlog("mercatorToTile: x0 = %1, y0 = %2, x = %3, y = %4, xch = %5, ych = %6\n"_qt
   .arg(x0).arg(y0).arg(ti->getX()).arg(ti->getY()).arg(xch).arg(ych) );



	coord_t minX = std::min(x0, x1);
	coord_t minY = std::min(y0, y1);
	coord_t maxX = std::max(x0, x1);
	coord_t maxY = std::max(y0, y1);



	FixedRect tile(minX, minY, maxX, maxY);
	return tile.grow(tile.getWidth()  * TILE_OVERLAP,
					 tile.getHeight() * TILE_OVERLAP);
}

/**
 * @brief Computes an empty Tile.
 *
 **/
shared_ptr<Tile> Job::computeEmpty()
{
	const string& path = mid->getStylesheetPath();
	const TileIdentifier::Format format = mid->getImageFormat();
	shared_ptr<Stylesheet> stylesheet = manager->getStylesheetManager()->getStylesheet(mid->getStylesheetPath());
	shared_ptr<TileIdentifier> emptyID = TileIdentifier::CreateEmptyTID(path, format);
	shared_ptr<Tile> tile = manager->getCache()->getTile(emptyID);

	if(!tile->isRendered()) {
		shared_ptr<std::vector<NodeId>> nodeIDs 	= boost::make_shared< std::vector<NodeId>>();
		shared_ptr<std::vector<WayId>> 	wayIDs 		= boost::make_shared< std::vector<WayId>>();
		shared_ptr<std::vector<RelId>> 	relationIDs = boost::make_shared< std::vector<RelId>>();

		RenderAttributes renderAttributes;

		stylesheet->match(nodeIDs, wayIDs, relationIDs, mid, &renderAttributes);
		manager->getRenderer()->renderEmptyTile(renderAttributes, canvas, tile);
	}

	return tile;
}

/**
 * @brief Inits the internal list of tiles that are part of the MetaTile.
 * @return true if all contained tiles are in cache
 */
bool Job::initTiles()
{
	bool rendered = true;
	for (auto& id : mid->getIdentifiers())
	{
		shared_ptr<Tile> tile = manager->getCache()->getTile(id);
		rendered = rendered && tile->isRendered();
		tiles.push_back(tile);
	}

	return rendered;
}

/**
 * @brief Computes a all tiles contained in the MetaIdentifier.
 *
 **/
void Job::process()
{
	shared_ptr<Geodata> geodata = manager->getGeodata();

 qlog("job process: x = %1, y = %2, z = %3\n"_qt
   .arg(mid->getX()).arg(mid->getY()).arg(mid->getZoom()) );

	FixedRect rect = computeRect(mid);

 qlog("rect: min_x = %1, min_y = %2, max_x = %3, max_y = %4\n"_qt
   .arg(rect.minX).arg(rect.minY).arg(rect.maxX).arg(rect.maxY) );

	STAT_START(Statistic::GeoContainsData);
		empty = !geodata->containsData(rect);
	STAT_STOP(Statistic::GeoContainsData);

	if(empty) {
		STAT_WRITE();
		return;
	}

	cached = initTiles();
	if (cached) {
		STAT_WRITE();
		return;
	}

	STAT_START(Statistic::GeoNodes);
		auto nodeIDs = geodata->getNodeIDs(rect);
	STAT_STOP(Statistic::GeoNodes);

	STAT_START(Statistic::GeoWays);
		auto wayIDs = geodata->getWayIDs(rect);
	STAT_STOP(Statistic::GeoWays);

	STAT_START(Statistic::GeoRelation);
		auto relationIDs = geodata->getRelationIDs(rect);
	STAT_STOP(Statistic::GeoRelation);

	STAT_STATS(nodeIDs->size(), wayIDs->size(), relationIDs->size());

	shared_ptr<Stylesheet> stylesheet = manager->getStylesheetManager()->getStylesheet(mid->getStylesheetPath());
	RenderAttributes renderAttributes;
	STAT_START(Statistic::StylesheetMatch);
		stylesheet->match(nodeIDs, wayIDs, relationIDs, mid, &renderAttributes);
	STAT_STOP(Statistic::StylesheetMatch);

	const shared_ptr<Renderer>& renderer = manager->getRenderer();
	STAT_START(Statistic::Renderer);

#ifdef QT_HOOK
  auto [w, h] =
#endif
  renderer->renderMetaTile(renderAttributes, canvas, mid);

 #ifdef QT_HOOK
  single_job_context_->set_held_width(w);
  single_job_context_->set_held_height(h);
 #endif

	STAT_STOP(Statistic::Renderer);
}

/*
 * @brief answers the requets for the computed tiles. Called by RequestManager
 */
void Job::deliver()
{
	if (empty)
	{
		shared_ptr<Tile> tile = computeEmpty();
		for (auto& id : mid->getIdentifiers())
		{
			for (auto& req : requests[*id])
				req->answer(tile);
		}
	} else {
		const shared_ptr<Renderer>& renderer = manager->getRenderer();
		STAT_START(Statistic::Slicing);
  for (auto& tile : tiles)
  {
			if (!tile->isRendered())
				renderer->sliceTile(canvas, mid, tile);

  #ifdef QT_HOOK
   Tile::ImageType ti = tile->getImage();

   //?int count = single_job_context_->job_context()->get_inc_current_image_count();
   //?int count = single_job_context_->static_job_context()->image_count;
   int count = single_job_context_->job_context()->get_inc_current_image_count();


   shared_ptr<TileIdentifier> tile_id = tile->getIdentifier();

   QMT_Tile_Object tobj(tile_id->getZoom(), tile_id->getX(),
     tile_id->getY()//?, mid->getWidth(), mid->getHeight()
                        );


   QString file_path = ALACARTE_IMAGES_FOLDER "/behind-the-scenes/i-%1.png"_qt.arg(count);

   QImage image;
   image.loadFromData(ti->data(), ti->size()); //, single_job_context_->get_held_width_times_height(), "png");

    //QImage image(held_width_, held_height_, QImage::Format_RGB32); //tile->getIdentifier()->getWidth(), tile->getIdentifier()->getHeight());
   QPainter painter(&image);

   static s1 text_outline_adjust_factor = 3;

   if(painter.isActive())
   {
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::darkCyan);

    QFont font = painter.font();
    font.setPixelSize(11);
    painter.setFont(font);

//?    painter.drawRect(10, 10, 30, 30);

    QString text1 = "%1 %2"_qt
      .arg(tobj.mercator_x())
      .arg(tobj.mercator_y());

    QString text2 = "%1 \u2022 %2 %3"_qt
      .arg(tobj.zoom())
      .arg(tobj.x())
      .arg(tobj.y())
      //?.arg(tobj.mercator_width())
      ;

    QString text3 = "%1 %2"_qt
      .arg(tobj.top_left_latitude())
      .arg(tobj.top_left_longitude());

    QString text4 = "%1 %2"_qt
      .arg(tobj.get_latitude_span())
      .arg(tobj.get_longitude_span());

//    QString text5 = "%1 %2"_qt
//      .arg(tobj.mercator_width())
//      .arg(tobj.mercator_height());


    QString text = "%1\n%2\n%3\n%4"_qt.arg(text1).arg(text2)
      .arg(text3).arg(text4); //.arg(text5);


    QRectF zero; //{0.,0.,0,};
    QRectF bound = painter.boundingRect(zero, Qt::AlignLeft, text);
    bound.moveTopLeft({10, 10});

    painter.drawText(bound, Qt::AlignLeft, text);

    bound.adjust(-text_outline_adjust_factor, -text_outline_adjust_factor,
      text_outline_adjust_factor, text_outline_adjust_factor);

    //bound += QPointF{10, 10};

//    painter.drawText(10, 20, text1);
//    painter.drawText(10, 40, text2);
//    painter.drawText(10, 60, text3);
//    painter.drawText(10, 80, text3);

    QPen pen;
    pen.setColor(QColor("Pink"));
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawRect(bound);

    QRect rect = image.rect();
    pen.setColor(QColor("SkyBlue"));
    pen.setWidth(1);
    pen.setStyle(Qt::DashDotLine);
    painter.setPen(pen);
    painter.drawRect(rect);

    rect.moveTopLeft({-1, -1});

    pen.setColor(QColor("Orange"));
    pen.setWidth(1);
    pen.setStyle(Qt::DashDotDotLine);
    painter.setPen(pen);
    painter.drawRect(rect);

    rect.adjust(1, 1, 0, 0);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::yellow);

//    painter.drawRect(QRect{rect.center() - QPoint{2, 5}, QSize{4, 10}});
//    painter.drawRect(QRect{rect.center() - QPoint{5, 2}, QSize{10, 4}});


    u4 x10 = (10 * (tobj.mercator_x() / 10)) + 1;
    u4 y10 = (10 * (tobj.mercator_y() / 10)) + 1;

    r8 x10r = ((r8)(x10 - tobj.mercator_x())) / tobj.mercator_width();
    r8 y10r = ((r8)(y10 - tobj.mercator_y())) / tobj.mercator_height();

    x10r *= image.width();
    y10r *= image.height();

    qlog("x10r = %1 y10r = %2\n"_qt.arg(x10r).arg(y10r));

    QPointF spot{x10r, y10r};
    painter.drawRect(QRectF{spot - QPoint{2, 5}, QSize{4, 10}});
    painter.drawRect(QRectF{spot - QPoint{5, 2}, QSize{10, 4}});

    //    painter.drawEllipse(rect.center(), 4, 6);




//    painter.drawText(10, 10, QString::number());
//    painter.drawText(10, 30, QString::number(tobj.mercator_y()));
//    painter.drawText(10, 50, "%1, %2"_qt.arg(image.width()).arg(image.height()));

   }

   image.save(file_path);
   qlog("Rendering count: %1\n"_qt.arg(count));

   QByteArray byteArray;
   QBuffer buffer(&byteArray);

   //buffer.m

   //?buffer.open(QBuffer::ReadWrite);
   image.save(&buffer, "PNG");

   Tile::ImageType new_image = boost::make_shared<Tile::ImageType::element_type>();
   new_image->resize(byteArray.size() - 3);
   std::copy(byteArray.begin(), byteArray.end() - 3, new_image->begin());
   tile->setImage(new_image);


//   qlog("Sizes: %1 %2\n"_qt.arg(byteArray.length()).arg(ti->size()));

//   std::copy(byteArray.begin(), byteArray.end() - 3, ti->begin());

//   FixedRect rect = computeRect(mid);

//   double lat, lon;
//   QMT_Tile_Object::mercator_to_latitude_and_longitude(rect.minX, rect.minY, //mid->getX(), mid->getY(),
//     tile_id->getZoom(), lat, lon);
//   //inverseMercator(fp, lat, lon);

//   qlog("Lat: %1, Lon: %2, BR Lat: %3, "
//        "BR Lon: %4, mx: %5, my: %6, mW: %7, mH: %8\n"_qt
//      .arg(tobj.top_left_latitude()).arg(tobj.top_left_longitude())
//      .arg(tobj.bottom_right_latitude()).arg(tobj.bottom_right_longitude())
//      .arg(tobj.mercator_x()).arg(tobj.mercator_y())
//        .arg(tobj.mercator_width()).arg(tobj.mercator_height())

//        //.arg(lat).arg(lon)

//        );

//   qlog("MX: %1, MY: %2, TX: %3, TY: %4"_qt
//      .arg(mid->getX()).arg(mid->getY())
//      .arg(tile_id->getX()).arg(tile_id->getY())
//        );

#endif

#ifdef QT_HOOK

 if(coordinates_save_info_)
  if(void* const* save_info = tobj.matches(*coordinates_save_info_))
   if(QString* offline_target_file_path_ = (QString*) *save_info)
    if(!offline_target_file_path_->isEmpty())
    {
     image.save(*offline_target_file_path_);
    }

#endif

			for (auto& req : requests[*tile->getIdentifier()])
     req->answer(tile);
		}
		if (!cached)
			STAT_STOP(Statistic::Slicing);
	}

	STAT_WRITE();
}

