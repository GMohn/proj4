#include "XMLReader.h"

CXMLReader::CXMLReader(std::istream& is) : DInput(is) {
	DParser = XML_ParserCreate(NULL);
}

CXMLReader::~CXMLReader() {
	XML_ParserFree(DParser);
}

bool CXMLReader::End() {

}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata) {
	char Buffer[1024];
	DInput.read(Buffer, sizeof(Buffer));
	

}