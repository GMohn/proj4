#ifndef XMLREADER_H 	  			 	 
#define XMLREADER_H

#include "XMLEntity.h"
#include <istream>
#include <expat.h>

class CXMLReader{
    private:
		std::istream& DInput;
		XML_Parser DParser;
    public:
        CXMLReader::CXMLReader(std::istream &is);
        CXMLReader::~CXMLReader();
        
        bool CXMLReader::End();
        bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata = false);
};

#endif
