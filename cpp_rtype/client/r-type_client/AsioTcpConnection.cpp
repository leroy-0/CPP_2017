#include <chrono>
#include "AsioTcpConnection.h"

AsioTcpConnection::AsioTcpConnection(const std::string & host, const std::string & port)
	: stopped_(false),
	socket_(io_service),
	resolv(io_service)
{
	this->ready = false;
	this->start(resolv.resolve(tcp::resolver::query(host, port)));
	service_thread = std::thread([&] { io_service.run(); });
}

AsioTcpConnection::~AsioTcpConnection()
{
	io_service.stop();
	service_thread.join();
}

void AsioTcpConnection::Send(const std::string& message)
{
	/*std::string secure_message;

	secure_message = secure_code;
	secure_message += " ";
	std::chrono::seconds s = std::chrono::duration_cast< std::chrono::seconds >(
		std::chrono::system_clock::now().time_since_epoch()
		);
	secure_message += std::to_string(s.count());
	secure_message += " ";
	secure_message += message;*/
	start_write(message);
}

bool AsioTcpConnection::HasMessages()
{
	return (!incomingMessages.empty());
}

std::string AsioTcpConnection::GetOneMessage()
{
	if (incomingMessages.empty())
		return (std::string());
	return incomingMessages.pop();
}

bool AsioTcpConnection::isReady() const
{
	return (this->ready);
}

void AsioTcpConnection::start(tcp::resolver::iterator endpoint_iter)
{
	start_connect(endpoint_iter);
}

void AsioTcpConnection::stop()
{
	stopped_ = true;
	socket_.close();
}

void AsioTcpConnection::start_connect(tcp::resolver::iterator endpoint_iter)
{
	if (endpoint_iter != tcp::resolver::iterator())
	{
		std::cout << "Trying " << endpoint_iter->endpoint() << "...\n";

		socket_.async_connect(endpoint_iter->endpoint(),
			boost::bind(&AsioTcpConnection::handle_connect,
				this, _1, endpoint_iter));
	}
	else
	{
		stop();
	}
}

void AsioTcpConnection::handle_connect(const boost::system::error_code& ec,
	tcp::resolver::iterator endpoint_iter)
{
	if (stopped_)
		return;

	if (!socket_.is_open())
	{
		std::cout << "Connect timed out\n";

		start_connect(++endpoint_iter);
	}
	else if (ec)
	{
		std::cout << "Connect error: " << ec.message() << "\n";

		socket_.close();

		start_connect(++endpoint_iter);
	}
	else
	{
		std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";
		this->ready = true;
		start_read();
	}
}

void AsioTcpConnection::start_read()
{
	boost::asio::async_read_until(socket_, input_buffer_, '\n',
		boost::bind(&AsioTcpConnection::handle_read, this, _1));
}

void AsioTcpConnection::handle_read(const boost::system::error_code& ec)
{
	if (stopped_)
		return;

	if (!ec)
	{
		std::string line;
		std::istream is(&input_buffer_);
		std::getline(is, line);

		if (!line.empty())
		{
			incomingMessages.push(line);
		}

		start_read();
	}
	else
	{
		std::cout << "Error on receive: " << ec.message() << "\n";

		stop();
	}
}

void AsioTcpConnection::start_write(const std::string & to_write)
{
	if (stopped_)
		return;

	boost::asio::async_write(socket_, boost::asio::buffer(to_write, to_write.size()),
		boost::bind(&AsioTcpConnection::handle_write, this, _1));
}

void AsioTcpConnection::handle_write(const boost::system::error_code& ec)
{
	if (stopped_)
		return;

	if (!ec)
	{

	}
	else
	{
		std::cout << "Error on heartbeat: " << ec.message() << "\n";

		stop();
	}
}