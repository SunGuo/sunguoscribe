
#ifndef SCRIBE_SYSLOG_H
#define SCRIBE_SYSLOG_H


#include <iostream>
#include "common.h"

/*
 * SyslogInterface Of the Syslog Net 
 */

class SyslogModel{
	
	public:
		
		SyslogModel(const std::string& ip,const unsigned long port);
		static boost::shared_ptr<SyslogModel> createSyslogModel(const std::string& netprotocol,const std::string& ip, unsigned long port);
		virtual ~SyslogModel()=0;
		virtual bool open()=0;
		virtual bool close_fd()=0;
		virtual bool isOpen()=0;
		virtual bool write(const std::string& data)=0;
		
	protected:
		
		int server_sockfd, recvbytes,addr_size; 		  
		struct sockaddr_in server_addr; 
		
		std::string serverip;
		unsigned long serverport;
		bool opened;
		
		//disallow copy,assignment,and empty construction	
		SyslogModel();
		SyslogModel(SyslogModel& rhs);
		SyslogModel& operator=(SyslogModel& rhs);
	
};

/*
*处理UDP网络连接逻辑
*/

class SyslogUdpModel:public SyslogModel{
	public:
		SyslogUdpModel(const std::string& ip,const unsigned long port);
		virtual ~SyslogUdpModel();
		bool open();
		bool close_fd();
		bool isOpen();
		bool write(const std::string& data);
	
	private:
		//disallow copy,assignment,and empty construction
		SyslogUdpModel();
		SyslogUdpModel(SyslogUdpModel& rhs);
		SyslogUdpModel& operator=(SyslogUdpModel& rhs);
};

/*
*处理TCP网络连接逻辑
*/

class SyslogTcpModel:public SyslogModel{
	public:
		SyslogTcpModel(const std::string& ip,const unsigned long port);
		virtual ~SyslogTcpModel();
		bool open();
		bool close_fd();
		bool isOpen();
		bool write(const std::string& data);
	private:
		//disallow copy,assignment,and empty construction
		SyslogTcpModel();
		SyslogTcpModel(SyslogTcpModel& rhs);
		SyslogTcpModel& operator=(SyslogTcpModel& rhs);
};

#endif
