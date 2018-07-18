#include <wlan.h>

using boost::asio::ip::tcp;

WLAN::WLAN()
    : socket(io), acceptor(io, tcp::endpoint(tcp::v4(), 13)), resolver(io)
{
    
}

WLAN::WLAN(DeviceType type, std::string ipAddress, int port)
    : socket(io), acceptor(io, tcp::endpoint(tcp::v4(), port)), resolver(io)
{
    start(type, ipAddress, port);
}

void WLAN::start(DeviceType type, std::string ipAddress, int port)
{
    switch (type)
    {
        case DeviceType::CLIENT:
            deviceType = DeviceType::CLIENT;
            startClient(ipAddress, port);
            break;
        case DeviceType::HOST:
            deviceType = DeviceType::HOST;
            startHost();
            break;
        default:
            break;
    }
}

void WLAN::startHost()
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

void WLAN::startClient(std::string ipAddress, int port)
{
    try
    {
        tcp::resolver::results_type endpoints = resolver.resolve(ipAddress, std::to_string(port));
        for (auto endpoint : endpoints)
        {
            std::cout << endpoint.host_name() << ":" << endpoint.service_name() << std::endl;
        }
        boost::asio::connect(socket, endpoints);
        std::cout << "Connected" << std::endl;

        std::array<char, MAX_BUFFER_SIZE> buf;
        boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);
        if (error == boost::asio::error::eof)
        {
            std::cout << "Server closed connection" << std::endl;
        }
        else if (error)
            throw boost::system::system_error(error);

        std::cout.write(buf.data(), len);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void WLAN::write(std::array<char, MAX_BUFFER_SIZE>& msg)
{
    try
    {
        boost::system::error_code error;
        boost::asio::write(socket, boost::asio::buffer(msg), error);
        if (error == boost::asio::error::eof)
        {
            std::cout << "Server closed connection" << std::endl;
        }
        else if (error)
            throw boost::system::system_error(error);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void WLAN::read()
{
    try
    {
        socket.async_read_some(boost::asio::buffer(cachedMessage), 
        [this](boost::system::error_code ec, std::size_t size)
        {
            if (!ec)
            {
                receiveCallback(size);
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

void WLAN::setCallback(std::function<void(std::size_t)> callback)
{
    receiveCallback = callback;
    callbackSet = true;
}

void WLAN::checkBuffer()
{
    io.poll();
}