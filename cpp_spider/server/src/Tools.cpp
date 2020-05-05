//
// Created by Yan on 10/3/2017.
//


#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "Tools.hpp"

void                            Tools::checkDir(std::string directory)
{
    boost::filesystem::path     dir(directory.c_str());

    try {
        if (boost::filesystem::create_directory(dir))
            Tools::printServerLogGreen(std::string(directory + " directory succefully created"), "Server");
    } catch (const std::exception&){}
}


void                            Tools::printServerLogRed(const std::string &log, const std::string & ip)
{
    boost::posix_time::ptime    timeLocal;

    timeLocal = boost::posix_time::second_clock::local_time();
    std::cerr << "[" << timeLocal.date().year() << "-" << timeLocal.date().month() << "-" << timeLocal.date().day()
              << "]" << "[" << timeLocal.time_of_day().hours()
              << ":" << timeLocal.time_of_day().minutes()
              << ":" << timeLocal.time_of_day().seconds()
              << "]" << "[" << ip <<"]"
              << " " << termcolor::red << log
              << termcolor::reset << std::endl;
}

void                            Tools::printServerLogGreen(const std::string &log, const std::string & ip)
{
    boost::posix_time::ptime    timeLocal;

    timeLocal = boost::posix_time::second_clock::local_time();
    std::cerr << "[" << timeLocal.date().year() << "-" << timeLocal.date().month() << "-" << timeLocal.date().day()
              << "]" << "[" << timeLocal.time_of_day().hours()
              << ":" << timeLocal.time_of_day().minutes()
              << ":" << timeLocal.time_of_day().seconds()
              << "]" << "[" << ip <<"]"
              << " " << termcolor::green << log
              << termcolor::reset << std::endl;
}

void                            Tools::printServerLogClassic(const std::string &log, const std::string & ip)
{
    boost::posix_time::ptime    timeLocal;

    timeLocal = boost::posix_time::second_clock::local_time();
    std::cerr << "[" << timeLocal.date().year() << "-" << timeLocal.date().month() << "-" << timeLocal.date().day()
              << "]" << "[" << timeLocal.time_of_day().hours()
              << ":" << timeLocal.time_of_day().minutes()
              << ":" << timeLocal.time_of_day().seconds()
              << "]" << "[" << ip <<"]"
              << " " << log << std::endl;
}