#ifndef SCRIBE_SINAFILTER_H
#define SCRIBE_SINAFILTER_H

#include "common.h"

typedef std::vector<std::string> string_message_t;

class Filter{
	public:
		Filter();
		void HandleFilter(boost::shared_ptr<string_message_t> messages);
		void filterLog_grep(boost::shared_ptr<string_message_t>,const std::string& regex);
		~Filter();
};

#endif
