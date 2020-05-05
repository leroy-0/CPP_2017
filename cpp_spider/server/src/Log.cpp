//
// Created by Yan on 9/29/2017.
//

#include "Tools.hpp"
#include "Log.hpp"

spider::Log::Log()
{
    random = 0;
}

spider::Log::~Log(){}

void                spider::Log::changeDate()
{
    std::stringstream     dir;

    log.close();
    timeLocal = boost::posix_time::second_clock::local_time();
    dir << "./Log/" << timeLocal.date().year() << "-" << timeLocal.date().month() << "-" << timeLocal.date().day();
    Tools::checkDir(dir.str());
    dir << this->m_filename;
    this->log.open(dir.str(), std::fstream::in | std::fstream::out | std::fstream::app);
}

void                spider::Log::init(const std::string & filename)
{
    std::stringstream   dir;

    this->m_filename = "";
    this->m_client_id = filename;
    timeLocal = boost::posix_time::second_clock::local_time();
    dir << "./Log/" << this->m_client_id << "/";
    Tools::checkDir(dir.str());
    this->path = dir.str();
}

void                spider::Log::parseBuffer()
{
    this->log << this->buffer << std::endl;
}

void                            spider::Log::addData(const std::string & read)
{
    this->buffer.append(read);
}

std::string spider::Log::flush()
{
    std::string fullPath;
    std::string filename;
    std::stringstream ss;
    std::fstream file;
    std::time_t result = std::time(nullptr);

    fullPath.append(this->path);
    ss << timeLocal.date().year() << "-" << timeLocal.date().month() << "-" + timeLocal.date().day()
          << "-" << timeLocal.time_of_day().hours() << "-" << timeLocal.time_of_day().minutes()
          << "-" << timeLocal.time_of_day().seconds() << "-" << static_cast<long>(result) << this->random << ".spider";
    this->random++;
    filename = ss.str();
    fullPath.append(filename);
    file.open(fullPath.c_str(),std::fstream::in | std::fstream::out | std::fstream::app);
    file << this->buffer;
    file.close();
    return (fullPath);
}