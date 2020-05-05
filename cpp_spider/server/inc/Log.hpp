//
// Created by longle_h on 06/10/2017.
//

#ifndef PROJECT_LOG_HPP
#define PROJECT_LOG_HPP
#define LOG_DIR "./Log/"

#include <iostream>
#include <ctime>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
#include "IDBManager.hpp"

namespace spider
{
    class Log
    {
    public:
        Log();
        virtual         ~Log();
        void            init(const std::string & filename);
        void            changeDate();
        void            parseBuffer();
        void            addData(const std::string & read);
        std::string     flush();

    private:
        std::string                 m_filename;
        std::string                 m_client_id;
        std::string                 path;
        std::string                 buffer;
        std::fstream                log;
        boost::posix_time::ptime    timeLocal;
        unsigned long               random;
    };
}

#endif //PROJECT_LOG_HPP
