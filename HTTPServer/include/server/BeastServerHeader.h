#ifndef COMRED_BEAST_SERVER_HEADER_H
#define COMRED_BEAST_SERVER_HEADER_H

#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>

namespace server {
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
}

#endif
