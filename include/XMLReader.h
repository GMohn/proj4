#ifndef XMLREADER_H 	  			 	 
#define XMLREADER_H

#include "XMLEntity.h"
#include <istream>
#include <expat.h>
#include <list>

class CXMLReader{
    private:
		std::istream& DInput;
		XML_Parser DParser;
		std::list<SXMLEntity> DBuffered;
		static void StartOfElements(void* data, const char* el, const char** attr);
		static void EndOfElements(void* data, const char* el);
		static void CharOfElements(void* data, const char* el, size_t len);
    public:
        CXMLReader(std::istream &is);
        ~CXMLReader();
        
        bool End();
        bool ReadEntity(SXMLEntity &entity, bool skipcdata = false);
};

#endif
