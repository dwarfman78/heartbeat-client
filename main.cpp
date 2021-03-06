/*Copyright (C) <2015> <Fabien LE CORRE (dwarf@dwarfman.fr)>

This software is provided 'as-is', without any express or implied
        warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
        including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
        in a product, an acknowledgment in the product documentation would be
        appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
        misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.*/
#include <sstream>
#include <iostream>
#include <ctime>
#include <SFML/Network.hpp>
#include "sha256.h"

using namespace std;
string timestamp()
{
    	time_t now;
        time(&now);
        struct tm* ptm;

        ptm = gmtime(&now);
        std::ostringstream ss;
        ss << ptm->tm_yday;

        return ss.str();
}
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

        SHA256 sha256;

        sf::Packet packet;

	std::string publicAddress;

	std::string timestampStr;

	std::string hash;

	std::cout << "Hello, launching heartbeat-client (1.1)" << std::endl;

        while(true)
        {
		
	    publicAddress = sf::IpAddress::getPublicAddress(sf::milliseconds(1000)).toString();

	    timestampStr = timestamp();

	    std::cout << "Sending heartbeat with : \n\t Subdomain : " << subDomain << "\n\t Sender : " << publicAddress << "\n\t Timestamp : " << timestampStr << std::endl;
            
	    hash = sha256(subDomain+publicAddress+password+timestampStr);

            packet << subDomain << hash;

            udpSocket.send(packet, {serverIp}, (unsigned short)std::atol(serverPort.c_str()));

	    packet.clear();
	    
  	    std::cout << "Going to sleep for : " + sleepTime + " milliseconds." << std::endl;

            sf::sleep(sf::milliseconds(atoi(sleepTime.c_str())));
        }
    }
    else
    {
        std::cout << "Invalid arguments, expecting SERVER_ADDRESS SERVER_PORT SUBDOMAIN PASSWORD SLEEP_TIME" << std::endl;
    }

    return 0;
}
