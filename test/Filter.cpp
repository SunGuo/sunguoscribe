
#include <iostream>
#include "Filter.h"

using namespace std;

Filter::Filter(){
		
}

Filter::~Filter(){
	
}

void Filter::HandleFilter(boost::shared_ptr<string_message_t> messages){
		string_message_t::iterator it;
		for (it=messages->begin();it!=messages->end();++it){
			std::string temp=(*it);
			size_t found;
			found = temp.find("&_data=");
			if(found!=std::string::npos){
				temp=temp.substr(found+7);
				(*it)=temp;
			}
		}
}

void Filter::filterLog_grep(boost::shared_ptr<string_message_t> messages,const std::string& regexp){
	
	std::string t_regex = regexp;
	const char* regexPattern = t_regex.c_str();
	boost::regex reg(regexPattern);
	string_message_t::iterator it;
	bool ismatch;
	for (it=messages->begin();it!=messages->end();++it){
		std::string temp=(*it);
		ismatch = boost::regex_search(temp.c_str(),reg);
		if (!ismatch){
			messages->erase(it);
		}
	}
	
	for (it=messages->begin();it!=messages->end();++it){
		std::cout<<"message    :"<<(*it)<<std::endl;
	}
	
}

/*
*
* $1

void Filter::filterLog_awk(boost::shared_ptr<string_message_t>,const std::string& sp,const std::string& logic){

}
*/

int main (){
	boost::shared_ptr<string_message_t> p_v;
	
	p_v = boost::shared_ptr<string_message_t> (new string_message_t);
	p_v->push_back("_accesskey=spoollxrsaansnq8tjw0&_ip=61.135.153.210&_port=80&_an=D11113905&_data=www.sinaimg.cn 122.159.242.201 0.000047922 hit [30/Mar/2012:14:17:05 +0800] \"GET /dy/slidenews/40_img/2012_13/29253_833534_888302.jpg HTTP/1.1\" 200 72499 \"http://slide.hlj.sina.com.cn/news/slide_40_29253_52537.html\" \"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\"");
	
	p_v->push_back("_accesskey=spoollxrsaansnq8tjw0&_ip=61.135.153.53&_port=80&_an=D11113899&_data=d3.sina.com.cn 124.65.183.14 0.000034094 hit [30/Mar/2012:14:17:27 +0800] \"GET /shh/lechan/20120222taobao/img_295/12.jpg HTTP/1.1\" 200 5779 \"http://pfp.sina.com.cn/2012taobaonew/shipin/taobao_video.html\" \"Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0; 360SE)\"");
	
	Filter fi;
	std::string regex = "&_ip=61.135.153.53";
	fi.filterLog_grep(p_v,regex);
	
	return 0;
}

