#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    boost::asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1234));

    tcp::socket socket(io_context);
    acceptor.accept(socket);

    for (;;) {
        char data[1024];
        boost::system::error_code error;

        size_t length = socket.read_some(boost::asio::buffer(data), error);

        if (error == boost::asio::error::eof) {
            break;
        }
        else if (error) {
            throw boost::system::system_error(error);
        }

        std::cout << "Received: " << data << std::endl;

        std::string response = "Message received!";
        boost::asio::write(socket, boost::asio::buffer(response));
    }

    return 0;
}
