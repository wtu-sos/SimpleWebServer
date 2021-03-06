#include "Socket.h"
#include "string.h"
#include <string>
#include <errno.h>
#include <fcntl.h>

Socket::Socket() : m_sock(-1) {
	memset(&m_addr, 0, sizeof(m_addr));
	create();

}

Socket::Socket(int port) : m_sock(-1) {
	memset(&m_addr, 0, sizeof(m_addr));

	create();
	bind(port);
	listen();

}


Socket::~Socket(){
	if (is_valid())
	{
		::close(m_sock);
		std::cout << "close socket : " << m_sock << std::endl;
	}
}

bool Socket::create(){
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (!is_valid())
		return false;
	
	int on = 1;
	if(setsockopt(m_sock, SOL_SOCKET,
		SO_REUSEADDR, (const char*)&on,
		sizeof(on) == -1))
		return false;
	
	return true;
}

bool Socket::bind ( const int port ) {
	if (!is_valid())
	{
		return false;
	}

	m_addr.sin_family		= AF_INET;
	m_addr.sin_addr.s_addr	= INADDR_ANY;
	m_addr.sin_port			= htons(port);

	int bind_return = ::bind(m_sock,
		(struct sockaddr *)&m_addr,
		sizeof(m_addr));

	if (-1 == bind_return)
	{
		return false;
	}

	return true;
}

bool Socket::listen() const {
	if (!is_valid())
	{
		return false;
	}

	int listen_return = ::listen(m_sock
	, MAXCONNECTIONS);

	if (-1 == listen_return)
	{
		return false;
	}

	return true;
}

bool Socket::accept(Socket& new_socket) const
{
	int addr_length = sizeof(m_addr);
	new_socket.m_sock = ::accept(m_sock,
		(sockaddr*)&m_addr, (socklen_t*)&addr_length);
	if (new_socket.m_sock <= 0)
		return false;
	else 
		return true;
}

bool Socket::send (const std::string s) const
{
	int status = ::send(m_sock, s.c_str(), 
		s.size(), MSG_NOSIGNAL);
	if (-1 == status) 
	{
		return false;
	}
	else 
	{
		return true;
	}
}

int Socket::recv(std::string& s) const 
{
	char buf[MAXRECV + 1];
	s = "";

	memset(buf, 0, MAXRECV);
	int status = ::recv(m_sock, buf, MAXRECV, 0);
	if (-1 == status)
	{
		std::cout << "ststus == -1, errno = " << errno << "in Socke::recv \n";
		return 0;
	} 
	else if (0 == status)
	{
		return 0;
	} 
	else 
	{
		s = buf;
		return status;
	}
}

bool Socket::connect(const std::string host, const int port)
{
	if (!is_valid())
		return false;
	
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(port);

	int status = inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);
	status = ::connect(m_sock, (sockaddr *)&m_addr, sizeof(m_addr));

	if (status == 0)
		return true;
	else 
		return false;
}

void Socket::set_non_blocking(const bool b)
{
	int opts;
	opts = fcntl(m_sock, F_GETFL);
	if (0 == opts)
	{
		return ;
	}
	if (b)
		opts = (opts | O_NONBLOCK);
	else
		opts = (opts & ~O_NONBLOCK);

	fcntl(m_sock, F_SETFL, opts);
}
