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

#ifndef REQUEST_MANAGER_HPP
#define REQUEST_MANAGER_HPP


#include <chrono>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "server/job.hpp"

#include "settings.hpp"

class Configuration;
class Cache;
class Renderer;
class Geodata;
class StylesheetManager;
class HttpRequest;
class TileIdentifier;
class RenderCanvasFactory;

#ifdef QT_HOOK
class Job_Context;
class Single_Job_Context;
#endif //def QT_HOOK

class RequestManager : public boost::enable_shared_from_this<RequestManager>
{
public:

 RequestManager(void* offline_context,
   const shared_ptr<Configuration>& config,
   const shared_ptr<Geodata>& data,
   const shared_ptr<Renderer>& renderer,
   const shared_ptr<Cache>& cache,
   const shared_ptr<StylesheetManager>& ssm);


 RequestManager(const shared_ptr<Configuration>& config, const shared_ptr<Geodata>& data, const shared_ptr<Renderer>& renderer, const shared_ptr<Cache>& cache, const shared_ptr<StylesheetManager>& ssm);

	~RequestManager();

	void stop();

 void push_factory();
 void pop_factory();

 void create_and_run_job(QMT_Tile_Object_Coordinates* coordinates_save_info, //int zoom, int x, int y,
   const string& format, const string& stylesheet_folder_path,
   const string& stylesheet_path_name, bool pop_factory = false);

	TESTABLE void enqueue(const shared_ptr<HttpRequest>& r);
	TESTABLE void enqueue(const shared_ptr<MetaIdentifier>& ti);
	TESTABLE shared_ptr<Geodata> getGeodata() const;
	TESTABLE shared_ptr<StylesheetManager> getStylesheetManager() const;
	TESTABLE shared_ptr<Cache> getCache() const;
	TESTABLE shared_ptr<Renderer> getRenderer() const;

private:
	void processNextRequest();
	bool nextUserRequest();
	bool nextPreRenderRequest();

private:
	shared_ptr<Geodata> data;
	shared_ptr<Renderer> renderer;
	shared_ptr<Cache> cache;
	shared_ptr<StylesheetManager> ssm;
	shared_ptr<Configuration> config;


#ifdef QT_HOOK
 Job_Context* job_context_;
 void* offline_context_;
#endif

 // // qmt: make these pointers so we can "not use them" for offline ...
 boost::asio::io_service* jobPool;
 boost::asio::io_service::work* preventStop;

	std::vector< shared_ptr<boost::thread> > workers;

	std::queue<shared_ptr<RenderCanvasFactory>> factories;
	boost::mutex factoriesMutex;

	boost::mutex userRJMutex;
	boost::mutex preRJMutex;
	std::queue< shared_ptr<HttpRequest> > userRequests;
	std::queue< shared_ptr<MetaIdentifier> > preRenderRequests;

	//! thread-safe queue of running jobs
	class RunningQueue;
	scoped_ptr<RunningQueue> running;

	unsigned int currentPrerenderingThreads;

	std::chrono::system_clock::time_point prerender_start, prerender_stop;
};


#endif
