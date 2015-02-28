#include <iostream>
#include <SFML/Network.hpp>
#include "sha256.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 6)
    {
        std::string serverIp = argv[1];

        std::string serverPort = argv[2];

        std::string subDomain = argv[3];

        std::string password = argv[4];

        std::string sleepTime = argv[5];

        sf::UdpSocket udpSocket;

        sf::Packet packet;

        SHA256 sha256;

        std::string publicAddress = sf::IpAddress::getPublicAddress(sf::milliseconds(1000)).toString(); //"127.0.0.1";

        std::string hash = sha256(subDomain+publicAddress+password);

        packet << subDomain << hash;

        while(true)
        {
            sf::sleep(sf::milliseconds(atoi(sleepTime.c_str())));

            udpSocket.send(packet, {serverIp}, (unsigned short)std::atol(serverPort.c_str()));
        }
    }
    else
    {
        std::cout << "invalid arguments, expecting SERVER_ADDRESS SERVER_PORT SUBDOMAIN PASSWORD SLEEP_TIME" << std::endl;
    }


    return 0;
}
