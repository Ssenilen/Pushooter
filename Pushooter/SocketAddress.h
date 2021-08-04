#pragma once

using SocketAddressPtr = std::shared_ptr<class SocketAddress>;

class SocketAddress
{
public:
	SocketAddress(uint32_t inAddress, uint16_t inPort);
	SocketAddress(const sockaddr& inSockAddr);
	SocketAddress(PCWSTR IpName, uint16_t inPort);

	size_t GetSize() const { return sizeof(sockaddr); }

	static SocketAddressPtr CreateIPv4FromString(const std::string& inString);

private:
	sockaddr_in SockAddr;
};

