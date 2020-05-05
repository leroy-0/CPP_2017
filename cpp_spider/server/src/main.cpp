#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
#include "Tools.hpp"
#include "AServer.hpp"
#include "Communication.hpp"

using boost::asio::ip::tcp;

int                             main(int argc, char* argv[])
{
    boost::asio::io_service     io_service;

    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << "<port>\n";
            return 1;
        }
        Tools::checkDir(std::string("./Log/"));
        spider::AServer serv(io_service, std::atoi(argv[1]));
        serv.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return (0);
}