#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

using namespace boost::placeholders;

const int PORT_NUMBER = 55555;

class Session
{

};


class Server
{
    public:
        Server(boost::asio::io_service& io_service,
                boost::asio::io_service::strand& strand,
                boost::asio::ip::tcp::endpoint& endpoint)
            : io_service_(io_service), strand_(strand), acceptor_(io_service, endpoint)
        {}

    private:
        boost::asio::io_service& io_service_;
        boost::asio::io_service::strand& strand_;
        boost::asio::ip::tcp::acceptor acceptor_;
};


int main(int argc, char* argv[])
{
    std::shared_ptr<boost::asio::io_service> io_service = std::make_shared<boost::asio::io_service>();
    std::shared_ptr<boost::asio::io_service::work> work = std::make_shared<boost::asio::io_service::work>(*io_service);
    std::shared_ptr<boost::asio::io_service::strand> strand = std::make_shared<boost::asio::io_service::strand>(*io_service);

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER);

    std::shared_ptr<Server> server = std::make_shared<Server>(*io_service, *strand, endpoint);

    return 0;
}