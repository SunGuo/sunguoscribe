#include "Syslogmodel.h"

SyslogModel::SyslogModel(const std::string& ip,const unsigned long port)
	:serverip(ip),
	serverport(port),
	opened(false){
	
}

SyslogModel::~SyslogModel(){

}

boost::shared_ptr<SyslogModel> SyslogModel::createSyslogModel(const std::string& netprotocol,const std::string& ip, unsigned long port){
	if(0 == netprotocol.compare("UDP")){
		/*
		*初始化一个UDP网络接口
		*/
		return boost::shared_ptr<SyslogModel>(new SyslogUdpModel(ip,port));
	}else if(0 == netprotocol.compare("TCP")){
		/*
		*初始化一个TCP网络接口
		*/
		return boost::shared_ptr<SyslogModel>(new SyslogTcpModel(ip,port));
	}else{
		return boost::shared_ptr<SyslogModel>();
	}
}




/*
*
*  处理UDP网络连接的逻辑  继承syslogModel
*
*/

SyslogUdpModel::SyslogUdpModel(const std::string& ip,unsigned long port)
	:SyslogModel(ip,port)
	{

}

SyslogUdpModel::~SyslogUdpModel(){

}

bool SyslogUdpModel::open(){
	if ((server_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) { 
		return false;
	} 
	server_addr.sin_family=AF_INET; 
    server_addr.sin_port=htons(this->serverport); 
    inet_pton(AF_INET,this->serverip.c_str(),&server_addr.sin_addr);
    memset(&(server_addr.sin_zero),0,8); 
	opened = true;
	return true;
}

bool SyslogUdpModel::close_fd(){
	 close(server_sockfd); 
	 opened = false;
	 return true;
}

bool SyslogUdpModel::isOpen(){
	return opened;
}

bool SyslogUdpModel::write(const std::string& data){
	std::cout<<data<<std::endl;
	unsigned long datasize = data.length();
	addr_size=sizeof(struct sockaddr);
	if (sendto(server_sockfd,data.c_str(),datasize,0,
                          (struct sockaddr*)&server_addr,addr_size) == -1){         
        return false; 
    }
	return true;
}


/*
*
*  处理TCP网络连接的逻辑  继承syslogModel
*
*/


SyslogTcpModel::SyslogTcpModel(const std::string& ip,unsigned long port)
	:SyslogModel(ip,port)
	{
}

SyslogTcpModel::~SyslogTcpModel(){
	
}


bool SyslogTcpModel::open(){
	/*if ((server_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) { 
		return false;
	}
	server_addr.sin_family=AF_INET; 
    server_addr.sin_port=htons(serverport); 
    inet_pton(AF_INET,serverip.c_str(),&server_addr.sin_addr);
    memset(&(server_addr.sin_zero),0,8);
	if(connect(server_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1) 
    { 
		opened = false;
        return false;
    }*/

	if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {   
        //perror("socket:");
        //exit(1);
		opened = false;
		return false;
    }   

        
        
    server_addr.sin_family=AF_INET; 
    server_addr.sin_port=htons(serverport); 
    inet_pton(AF_INET,serverip.c_str(),&server_addr.sin_addr);
    memset(&(server_addr.sin_zero),0,8); 
        
        
    if(connect(server_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1) 
    {   
        //perror("connect:"); 
        //exit(1);
		opened = false;
		return false;
    }   

	opened = true;
	return true;
}

bool SyslogTcpModel::close_fd(){
	 close(server_sockfd); 
	 opened = false;
	 return true;
}

bool SyslogTcpModel::isOpen(){
	return opened;
}

bool SyslogTcpModel::write(const std::string& data){
	
	unsigned long datasize = data.length();
	std::cout<<data<<std::endl;
	if (send(server_sockfd,data.c_str(),data.length(), 0) == -1)    
    {         
       return false;
    }
	return true;
}

int main(){
	std::string ip = "10.210.213.130";
	unsigned long port = 9090;
	std::string nettype="TCP";

	boost::shared_ptr<SyslogModel> writesyslog = SyslogModel::createSyslogModel(nettype,ip,port);
	
	if(writesyslog->open()){
		
		writesyslog->write("HelloWOrld");
	}else {
		std::cout<<"Hello world Hello world Hello world"<<std::endl;
	}
	writesyslog->close_fd();
	return 0;
}
