#include <iostream>
#include <boost/asio.hpp>

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 55555;

int main()
{
    // io_service는 커널에서 발생한 i/o이벤트를 디스패치 해주는 클래스로
    // 커널에서 발생한 네트워크상의 접속, 데이터 송수신 등의 이벤트를 알 수 있다.
    boost::asio::io_service io_service;
    // ipv4 엔드포인트 설정
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER);
    // endpoint로부터 클라이언트의 접속 요청을 받아들이는 역할을 함
    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
    // TCP 소켓 생성
    boost::asio::ip::tcp::socket socket(io_service);
    // 소켓과 acceptor 연결 
    acceptor.accept(socket);
    return 0;
}