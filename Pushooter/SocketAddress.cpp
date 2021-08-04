#include "stdafx.h"
#include "SocketAddress.h"

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)
{
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.S_un.S_addr = htonl(inAddress);
	SockAddr.sin_port = htons(inPort);
	memset(&SockAddr.sin_zero, 0, sizeof(SockAddr.sin_zero));
}

SocketAddress::SocketAddress(const sockaddr& inSockAddr)
{
	memcpy(&SockAddr, &inSockAddr, sizeof(sockaddr));
}

SocketAddress::SocketAddress(PCWSTR IpName, uint16_t inPort)
{
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_port = htons(inPort);
	memset(&SockAddr.sin_zero, 0, sizeof(SockAddr.sin_zero));
	InetPton(AF_INET, IpName, &SockAddr.sin_addr);
}

SocketAddressPtr SocketAddress::CreateIPv4FromString(const std::string& inString)
{
	auto pos = inString.find_last_of(":");
	std::string host, service;

	if (pos != std::string::npos)
	{
		host = inString.substr(0, pos);
		service = inString.substr(pos + 1);
	}
	else
	{
		host = inString;
		service = "0";
	}

	addrinfo hint;
	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;

	addrinfo* result = nullptr;
	int error = getaddrinfo(host.c_str(), service.c_str(), &hint, &result);
	addrinfo* initResult = result;

	if (error > 0 && result == nullptr)
	{
		return nullptr;
	}

	if (error != 0 && result != nullptr)
	{
		freeaddrinfo(initResult);
		return nullptr;
	}

	while (result->ai_addr == nullptr && result->ai_next != nullptr)
	{
		result = result->ai_next;
	}

	if (result->ai_addr == nullptr)
	{
		freeaddrinfo(initResult);
		return nullptr;
	}

	auto toRet = std::make_shared<SocketAddress>(*result->ai_addr);
	return toRet;
}
