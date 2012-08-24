#ifndef SCRIBE_SINAFILTER_H
#define SCRIBE_SINAFILTER_H

#include "common.h"
#include "env_default.h"
class Filter{
    public:
        Filter();
        bool listFilter(std::string& message,std::string& filename,bool listflag);
		bool removePrefix(std::string& message);
        bool filter(std::string& message,const std::string& regex);
		bool readConfig(const std::string& filename);	
		~Filter();
	private:
	    static std::string trimString(const std::string& str);
		/*暂存用户配置的配置文件*/
		std::string filename;
		std::vector<std::string> list_name;
		std::map<std::string,int> list_map;
		time_t now;
		time_t m_now;
		bool first;
		
		
    
    
};

#endif
