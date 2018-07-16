#include <stream.h>

#include <array>
#include <ctime>

#define MAXDATASIZE 500 // max number of bytes we can get at once 

using boost::asio::ip::tcp;

Stream::Stream()
    : socket(io), acceptor(io, tcp::endpoint(tcp::v4(), 5000)), resolver(io)
{
    
}

void Stream::startHost()
{
    try
    {
        std::cout << "Waiting for client..." << std::endl;
        acceptor.accept(socket);

        std::cout << "Client connected: " << socket.remote_endpoint().address().to_string() << std::endl;
        std::string msg = "Hello from Controller\n";
        boost::system::error_code err;
        boost::asio::write(socket, boost::asio::buffer(msg), err);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Stream::write(std::string& msg)
{
    try
    {
        boost::system::error_code err;
        std::cout << "Writing: " << msg << std::endl;
        boost::asio::write(socket, boost::asio::buffer(msg), err);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Stream::read(std::function<void(std::size_t)> callback)
{
    try
    {
        socket.async_read_some(boost::asio::buffer(currentMessage), 
        [callback](boost::system::error_code ec, std::size_t size)
        {
            if (!ec)
            {
                callback(size);
            }
            else
                throw boost::system::system_error(ec);
        });
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Stream::checkBuffer()
{
    io.poll();
}