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

    // 동기 서버이므로 지속적인 통신을 하기 위한 반복문
    while(true)
    {
        // 클라이언트가 보낸 문자를 담을 버퍼
        //std::array<char, 128> buf{};
        char ch;
        
        // 에러 코드
        boost::system::error_code ec;

        // 클라이언트와 연결된 소켓으로부터 데이터를 읽고, 에러가 발생했으면 에러 코드를 받아옴
        //size_t len = socket.read_some(boost::asio::buffer(buf), ec);
        size_t len = socket.read_some(boost::asio::buffer(&ch, 1), ec);

        // 에러 발생!
        if (ec)
        {
            // 클라이언트와 연결이 끊길 경우 end of file 에러
            if (ec == boost::asio::error::eof)
            {
                std::cout << "Disconnected from client..." << std::endl;
            }
            // 다른 에러일 경우 에러의 정보 표시
            else
            {
                std::cout << "error No: " << ec.value() << " error Message: " << ec.message() << std::endl;
            }
            break;
        }

        std::cout << "클라이언트에서 받은 메세지: " << ch << std::endl;

        // 데이터를 클라이언트로 보낼 경우 에러가 발생할 수 있지만 무시
		boost::system::error_code ignored_error;
        // 클라이언트에서 받은 문자를 버퍼에 담아 전송
		socket.write_some(boost::asio::buffer(&ch, 1), ignored_error);
    }

    return 0;
}