/// @file stream.h
/// @author Andrew Loomis
/// @date 5/17/2018
/// @brief Definition of WLAN class.

#ifndef WLAN_H
#define WLAN_H

#define MAX_BUFFER_SIZE 128

#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <functional>
#include <array>

/// @brief Controls a Wireless LAN (WLAN) radio, like the pDDL2450.
class WLAN
{
public:
    enum DeviceType {
        HOST = 0,
        CLIENT
    };

    /// @brief Initializes private variables.
    WLAN();
    WLAN(DeviceType type, std::string ipAddress, int port);

    void start(DeviceType type, std::string ipAddress, int port);
    void write(std::array<char, MAX_BUFFER_SIZE>& msg);
    void read();
    void setCallback(std::function<void(std::size_t)> callback);
    void checkBuffer();

    /// @brief Gives access to whether the socket is active.
    /// @return True if socket is active, false if not.
    bool isActive() const { return active; }

    void getCachedMessage(std::array<char, MAX_BUFFER_SIZE>& msg) const { msg = cachedMessage; }

private:
    void startHost();
    void startClient(std::string ipAddress, int port);

    bool active;
    DeviceType deviceType;

    boost::asio::io_context io;
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::resolver resolver;

    std::function<void(std::size_t size)> receiveCallback;
    bool callbackSet = false;

    std::array<char, MAX_BUFFER_SIZE> cachedMessage;
};

#endif