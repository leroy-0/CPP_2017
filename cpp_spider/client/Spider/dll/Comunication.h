#pragma once

#include	<string>
#include	<boost/array.hpp>
#include	<boost/asio.hpp>
#include	"Comunication.h"
#include	"AEncryption.hpp"

class Comunication
{
public:
	Comunication();
	virtual ~Comunication();

public:
	void			run();
	bool			connect();
	void			send_files(boost::asio::ip::tcp::socket &socket);
	int				get_key(size_t len);
	void			send_parts(std::string &file, boost::asio::ip::tcp::socket &socket);
	std::string		read_one_file(std::ifstream &myfile, boost::asio::ip::tcp::socket &socket);
	int				check_recv(boost::asio::ip::tcp::socket &socket);


private:
	std::string key;
	spider::AEncryption *enc;
	time_t			start;

};