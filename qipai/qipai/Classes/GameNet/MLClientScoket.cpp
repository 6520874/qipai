/****************************************************************************
Copyright (c) 2014 Lijunlin - Jason lee

Created by Lijunlin - Jason lee on 2014

jason.lee.c@foxmail.com
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "MLClientScoket.h"
//#include "Game/FV/NetLog.h"

NS_CC_BEGIN

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
static bool bStartup = false;
#endif

MLClientScoket::MLClientScoket()
: m_uSocket(INVALID_SOCKET)
{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
if( !bStartup ) 
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	bStartup = true;
}
#endif
}

MLClientScoket::~MLClientScoket()
{
	ccClose();
}


void MLClientScoket::setPort(int port)
{
    m_port = port;
}

void MLClientScoket::setUrl(const char *url)
{
    m_url = url;
}

// TODO:兼容ipv4和IPV6网络环境...
bool MLClientScoket::connectTcpServer(const char *pServerIP,unsigned short ServerPort)
{
    struct addrinfo * result = NULL;
    struct addrinfo * res = NULL;
    int error;
    cocos2d::log("TcpClientSocket::function [%s] line [%d] ....传入的参数：pServerIP=%s, ServerPort=%d, ------ ", __FUNCTION__, __LINE__, pServerIP, ServerPort );
    
    error = getaddrinfo(pServerIP, NULL, NULL, &result);
    if(error != 0)
    {
        // 域名解析失败，直接返回 .....
         cocos2d::log("域名解析失败，直接返回 .....TcpClientSocket::function [%s] line [%d] error in pServerIP[%s], port[%d], getaddrinfo:%d, strErr=%s", __FUNCTION__, __LINE__, pServerIP, ServerPort, error, gai_strerror(error));
        return false;
    }
    
    for(res = result; res!=NULL; res = res->ai_next)
    {
        {
            
            switch (res->ai_addr->sa_family)
            {
                case AF_INET:
                {
                    char ip[16] = { 0 };
                    struct hostent* h = gethostbyname(pServerIP);
                    if (h != NULL)
                    {
                        unsigned char* p = (unsigned char *)(h->h_addr_list)[0];
                        if (p != NULL)
                        {
                            sprintf(ip, "%u.%u.%u.%u", p[0], p[1], p[2], p[3]);
                        }
                    }
                    
                    if(subConnectServerIPV4(ip, ServerPort))
                    {
                        // IPV4 连接成功
                        cocos2d::log("TcpClientSocket::IPV4,连接成功了. IP:%s, port:%d", ip, ServerPort);
                        freeaddrinfo(result);
                        return true;
                    }
                    else
                    {
                        ccClose();
                        // IPV4 连接失败
                        cocos2d::log("TcpClientSocket::IPV4,连接失败，继续查找... IP:%s, port:%d", ip, ServerPort);
                    }
                }
                    break;
                    
                case AF_INET6:
                {
                    char hostname[1025] = "";
                    error = getnameinfo(res->ai_addr, res->ai_addrlen, hostname, 1025, NULL, 0, 0);
                    if (error != 0)
                    {
                        cocos2d::log("获取主机信息失败????：TcpClientSocket::function [%s] line [%d] error in  pServerIP[%s], port[%d], getnameifno: %s", __FUNCTION__, __LINE__, pServerIP, ServerPort, gai_strerror(error));
                        continue;
                    }
                    std::string ip = hostname;
                    if(subConnectServerIPV6(ip.c_str(), ServerPort))
                    {
                        // IPV6 连接成功
                        cocos2d::log("TcpClientSocket::IPV6,连接成功了. IP:%s, port:%d", ip.c_str(), ServerPort);
                        freeaddrinfo(result);
                        return true;
                    }
                    else
                    {
                        ccClose();
                        // IPV6 连接失败
                        cocos2d::log("TcpClientSocket::IPV6,连接失败，继续查找... IP:%s, port:%d", ip.c_str(), ServerPort);
                    }
                }
                    break;
                    
                default:
                    cocos2d::log("TcpClientSocket::switch (res->ai_addr->sa_family)=======   这是一条异常的log  ");
                    break;
            }// end switch
        }
    }// end for
    
    freeaddrinfo(result);
    cocos2d::log("TcpClientSocket::Ipv6,Ipv4连接均失败！！！ function [%s] line [%d] pServerIP:%s, port:%d ", __FUNCTION__, __LINE__, pServerIP, ServerPort);
    return false;
}

bool MLClientScoket::subConnectServerIPV4(const char *pServerIP, unsigned short ServerPort)
{
    cocos2d::log("TcpClientSocket::function [%s] line [%d] ip [%s] port [%d]", __FUNCTION__, __LINE__, pServerIP, ServerPort);
    struct sockaddr_in     addrServer;
    
   // NetLog::Log("MLClientScoket::ccInit");
    
    m_uSocket = INVALID_SOCKET;
    
    if( m_uSocket != INVALID_SOCKET )
    {
        ccClose();
    }
    
    memset(&addrServer, 0, sizeof(addrServer));
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(ServerPort);
    addrServer.sin_addr.s_addr = inet_addr(pServerIP);
    #if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    addrServer.sin_len = sizeof(struct sockaddr_in);
    #endif
    memset(addrServer.sin_zero, 0, 8);
    
    m_uSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( m_uSocket == INVALID_SOCKET )
    {
        CCLOGERROR("create socket failed");
        return false;
    }
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
    unsigned int ul = 1;
    int nRet = ioctlsocket(m_uSocket, FIONBIO, (u_long*)&ul);
    if( nRet == SOCKET_ERROR )
    {
        CCLOGERROR("set unblocking failed");
        ccClose();
        return false;
    }
#endif
    
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    int nFlags = fcntl(m_uSocket, F_GETFL, 0);
    int nRet = fcntl(m_uSocket, F_SETFL, nFlags | O_NONBLOCK);
    if( nRet == SOCKET_ERROR )
    {
        CCLOGERROR("set unblocking failed");
        ccClose();
        return false;
    }
#endif
    
    int nNoDelay = 1;
    if( setsockopt(m_uSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&nNoDelay, sizeof(nNoDelay)) == SOCKET_ERROR )
    {
        CCLOGERROR("set nodelay failed");
        ccClose();
        return false;
    }
    
    
    nRet = ::connect(m_uSocket, (struct sockaddr*)&addrServer, sizeof(addrServer));
    
    if( nRet == 0 )
    {
        cocos2d::log("nRetspf0%d",nRet);
        return true;
    }
    else
    {
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
        int nError = WSAGetLastError();
        if( nError ==  WSAEWOULDBLOCK )
        {
            return true;
        }
        else
        {
            return false;
        }
#endif
        
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
        if( nRet == SOCKET_ERROR && errno == EINPROGRESS )
        {
            cocos2d::log("nRetspf1%d",nRet);
            return true;
        }
        else
        {
            cocos2d::log("nRetspf4%d %d",nRet,errno);
            return false;
        }
        
        
        cocos2d::log("nRetspf2%d",nRet);
#endif
    }
  
    return true;
}

bool MLClientScoket::subConnectServerIPV6(const char *pServerIP, unsigned short ServerPort)
{
    //NetLog::Log("MLClientScoket::ccInit");
    
    m_uSocket  = INVALID_SOCKET;
    
    struct sockaddr_in6     addrServer;
    
    memset(&addrServer, 0, sizeof(addrServer));
    addrServer.sin6_family = AF_INET6;
    addrServer.sin6_port = htons(ServerPort);
 #if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    addrServer.sin6_len = sizeof(struct sockaddr_in6);
#endif
    
    inet_pton(AF_INET6, pServerIP, &addrServer.sin6_addr);
    
    
    m_uSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if( m_uSocket == INVALID_SOCKET )
    {
        CCLOGERROR("create socket failed");
        return false;
    }
    
    
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
    unsigned int ul = 1;
    int nRet = ioctlsocket(m_uSocket, FIONBIO, (u_long*)&ul);
    if( nRet == SOCKET_ERROR )
    {
        CCLOGERROR("set unblocking failed");
        ccClose();
        return false;
    }
#endif
    
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    int nFlags = fcntl(m_uSocket, F_GETFL, 0);
    int nRet = fcntl(m_uSocket, F_SETFL, nFlags | O_NONBLOCK);
    if( nRet == SOCKET_ERROR )
    {
        CCLOGERROR("set unblocking failed");
        ccClose();
        return false;
    }
#endif
    
    int nNoDelay = 1;
    if( setsockopt(m_uSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&nNoDelay, sizeof(nNoDelay)) == SOCKET_ERROR )
    {
        CCLOGERROR("set nodelay failed");
        ccClose();
        return false;
    }
    

     nRet = ::connect(m_uSocket, (struct sockaddr*)&addrServer, sizeof(addrServer));
        
        if( nRet == 0 )
        {
            cocos2d::log("nRetspf0%d",nRet);
            return true;
        }
        else
        {
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
            int nError = WSAGetLastError();
            if( nError ==  WSAEWOULDBLOCK )
            {
                return true;
            }
            else
            {
                return false;
            }
#endif
            
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
            if( nRet == SOCKET_ERROR && errno == EINPROGRESS )
            {
                cocos2d::log("nRetspf1%d",nRet);
                return true;
            }
            else
            {
                cocos2d::log("nRetspf4%d %d",nRet,errno);
                return false;
            }
            
            cocos2d::log("nRetspf2%d",nRet);
#endif
        }
    return true;
}

bool MLClientScoket::ccInit()
{

    
   
    return true;
}



void MLClientScoket::ccClose()
{
	if( m_uSocket != INVALID_SOCKET )
	{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		closesocket(m_uSocket);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		close(m_uSocket);        
#endif
		m_uSocket = INVALID_SOCKET;
	}
}



bool MLClientScoket::ccConnect()
{
	//NetLog::Log("MLClientScoket::ccConnect");
#if 1 // runtime error on ios
    //&& m_oInetAddress.getPort() != 0
	CCAssert(strlen("2001:19f0:8001:d5:5400:ff:fe36:7246") , "_connect");
#endif
    //ncmj.qs5918.com
    return connectTcpServer(m_url, m_port);

    
	/*if( m_uSocket == INVALID_SOCKET )
	{
		if(!ccInit())
		{
			return false;
		}
	}
    
     
	int nRet = ::connect(m_uSocket,(struct sockaddr*)&m_oInetAddress, sizeof(m_oInetAddress));
    
    cocos2d::log("nRet=%d",nRet);
    
	if( nRet == 0 )
	{
         cocos2d::log("nRetspf0%d",nRet);
		return true;
	}
	else
	{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		int nError = WSAGetLastError();
		if( nError ==  WSAEWOULDBLOCK )
		{
			return true;
		}
		else
		{
			return false;
		}
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		if( nRet == SOCKET_ERROR && errno == EINPROGRESS )
		{
           cocos2d::log("nRetspf1%d",nRet);
			return true;
		}
		else
		{
            cocos2d::log("nRetspf4%d %d",nRet,errno);
			return false;
        }
        
          cocos2d::log("nRetspf2%d",nRet);
#endif
	}
      cocos2d::log("nRetspf3%d",nRet);*/
    
}

void MLClientScoket::ccDisconnect()
{
	//NetLog::Log("MLClientScoket::ccDisconnect");
	if( m_uSocket != INVALID_SOCKET )
	{
#if 0
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		shutdown(m_uSocket, SD_BOTH);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
        shutdown(m_uSocket, SHUT_RDWR);
#endif
#endif
		ccClose();
	}
}

void MLClientScoket::setInetAddress(const MLClientInetAddress& oInetAddress)
{
	//m_oInetAddress = oInetAddress;
}

int MLClientScoket::ccRead(char* _buff, int _len)
{
	if( m_uSocket == INVALID_SOCKET )
		return eSocketIoError;

	return ::recv(m_uSocket, _buff, _len, 0);
}

int MLClientScoket::ccWrite(char* _buff, int _len)
{
	if( m_uSocket == INVALID_SOCKET )
		return eSocketIoError;

#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	return ::send(m_uSocket, _buff, _len, 0);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    return ::send(m_uSocket, _buff, _len, SO_NOSIGPIPE);
#endif
}

bool MLClientScoket::ccIsSocketVaild(bool bRecive)
{
	return isSocketVaild(m_uSocket,bRecive);
}

int MLClientScoket::ccIsConnected()
{
	if (m_uSocket == INVALID_SOCKET)
	{
		return false;
	}
	fd_set	fd;
	struct timeval tv;

	FD_ZERO(&fd);
	FD_SET(m_uSocket, &fd);

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if( select((int)(m_uSocket + 1), NULL, &fd, NULL, &tv) > 0 )
	{
		if( FD_ISSET(m_uSocket, &fd) )
		{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

			return eSocketConnected;

#elif( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

			int nError;
			socklen_t len = sizeof(nError);
			if( getsockopt(m_uSocket, SOL_SOCKET, SO_ERROR, &nError, &len) < 0 )
			{
				return eSocketConnectFailed;
			}
			if( nError == ECONNREFUSED || nError == ETIMEDOUT )
			{
				return eSocketConnectFailed;
			}
			return eSocketConnected;

#endif
		}
	}
	return eSocketConnecting;
}

NS_CC_END