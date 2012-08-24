#include "common.h"
#include "Filter.h"

Filter::Filter(){
   now = time(NULL);
   first = true;
}

Filter::~Filter(){
    
}

/*
* 处理字符串读取的逻辑
*/

//去掉前后空格的函数
std::string Filter::trimString(const std::string& str){
        std::string whitespace = " \t";
        size_t start      =str.find_first_not_of(whitespace);
        size_t end        =str.find_last_not_of(whitespace);

        if(start != std::string::npos) {
        return str.substr(start, end - start + 1);
        }else{
        return "";
        }
}

/*
 * 根据用户使用的配置文件中黑白名单进行过滤，
 * filename 用户配置的黑白名单
 * listflag 黑白名单   #为注释字符
 */

bool Filter::readConfig(const std::string& filename){
		std::string line;
        std::ifstream config_file;

        config_file.open(filename.c_str());

        if (!config_file.good()) {
			return false;
        }
        while (getline(config_file, line)) {
			line = trimString(line);
			size_t comment = line.find_first_of('#');
			if (comment != std::string::npos) {
      			line.erase(comment);
    		}
			int length = line.size();
    		if (0 >= length) {
      			continue;
    		}
        	list_name.push_back(line);
        }
		
        config_file.close();
	
	std::vector<std::string>::iterator it;
    std::string t_regex;
	int i=0;
    
	for (it = list_name.begin();it!=list_name.end();it++){
        t_regex = (*it);
		list_map.insert(std::pair<std::string,int>(t_regex,i));
		i++;
	}
        return true;	
}

/*bool Filter::listFilter(std::string& message,std::string& filename,bool listflag){
	time_t m_now;
	m_now = time(NULL);
	//间隔一定时间重读配置文件
	
	if(((m_now-now)>30*60)||first){
		first = false;
		now = m_now;
		list_name.clear();
		if(!readConfig(filename)){
			LOG_OPER("read filter config failed");
		}else {
			LOG_OPER("reload the config file");
		}
	}

	std::vector<std::string>::iterator it;
	std::string t_regex;
	std::string t_mess;
	const char* regexPattern;

	for (it = list_name.begin();it!=list_name.end();it++){
		t_regex = (*it);
    	t_mess = message;

    	regexPattern = t_regex.c_str();

    	boost::regex reg(regexPattern);
    	bool ismatch;
    	ismatch = boost::regex_search(t_mess.c_str(),reg);
    	if (ismatch){
			if(!listflag){
				return true;
			}
    	} 
    	    	
	}
	// 如果是黑名单返回true 白名单返回 false 
	if(listflag){
		return true;
	}else {
		return false;
	}
	return false;
}*/


bool Filter::listFilter(std::string& message,std::string& filename,bool listflag){
	m_now = time(NULL);                                                                                                                                                 
    //间隔一定时间重读配置文件
    std::string t_msg;    
    std::string domain;
	if(((m_now-now)>30*60)||first){
        first = false;
        now = m_now;
        list_name.clear();
        if(!readConfig(filename)){
            LOG_OPER("read filter config failed  [%s]",filename.c_str());
        }else {
            LOG_OPER("reload the config file  [%s]",filename.c_str());
        }   
    }

	t_msg=message;
	size_t size;
	size=t_msg.rfind("&_data=");
	if(size!=std::string::npos){
		t_msg=t_msg.substr(size);
		size=t_msg.find(" ");
		if(size!=std::string::npos){
			domain=t_msg.substr(0,size);
			if(list_map.find(domain)!=list_map.end()&&!listflag){
				return true;
			}else if(list_map.find(domain)==list_map.end()&&listflag){
				return true;
			}
		}	
	}
	return false;	
}


/*bool Filter::listFilter(std::string& message,std::string& filename,bool listflag){
	m_now = time(NULL);
	//间隔一定时间重读配置文件
	
	if(((m_now-now)>30*60)||first){
		first = false;
		now = m_now;
		list_name.clear();
		if(!readConfig(filename)){
			LOG_OPER("read filter config failed  [%s]",filename.c_str());
		}else {
			LOG_OPER("reload the config file  [%s]",filename.c_str());
		}
	}

	std::vector<std::string>::iterator it;
	std::string t_regex;

	for (it = list_name.begin();it!=list_name.end();it++){
		t_regex = (*it);
    	
		if (message.find(t_regex)!=std::string::npos){
			if(!listflag){
				return true;
			}
    	} 
	}
	// 如果是黑名单返回true 白名单返回 false 
	if(listflag){
		return true;
	}else {
		return false;
	}
	return false;
}*/


bool Filter::removePrefix(std::string& message){

    std::string temp=message;
    size_t found;
    found = temp.find("&_data=");
        
    if(found!=std::string::npos){
        temp=temp.substr(found+7);
        message = temp;
        return true;
    }
    
    return false;
}

bool Filter::filter( std::string& message,const std::string& regex ){
    
    std::string t_regex = regex;
    std::string t_mess = message;

    const char* regexPattern = t_regex.c_str();

    boost::regex reg(regexPattern);
    bool ismatch;
    ismatch = boost::regex_search(t_mess.c_str(),reg);

    if (ismatch){
        return true;
    }
	
    return false;    
}

