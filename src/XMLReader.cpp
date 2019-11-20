#include "XMLReader.h"

CXMLReader::CXMLReader(std::istream& is) : DInput(is) {
	DParser = XML_ParserCreate(NULL);
	XML_SetUserData(DParser, this);
	XML_SetElementHandler(DParser, StartOfElements, EndOfElements);
	XML_SetCharacterDataHandler(DParser, CharOfElements);
}

CXMLReader::~CXMLReader() {
	XML_ParserFree(DParser);
}

void CXMLReader::StartOfElements(void* data, const char* el, const char* attr[]) {
	auto Reader = static_cast<CXMLReader*>(data);
	SXMLEntity XMLElement;
	XMLElement.DType = SXMLEntity::EType::StartElement;
	XMLElement.DNameData = std::string(el);
	for (int i = 0; attr[i]; i += 2) {
		XMLElement.SetAttribute(std::string(attr[i]), std::string(attr[i + 1]));
	}
	Reader->DBuffered.push_back(XMLElement);
}
void CXMLReader::EndOfElements(void* data, const char* el) {

}
void CXMLReader::CharOfElements(void* data, const char* el, int len) {

}

bool CXMLReader::End() {
	
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata) {
	char Buffer[1024];
	while (!DInput.eof()) {
		DInput.read(Buffer, sizeof(Buffer));
		XML_Parse(DParser, Buffer, DInput.gcount(), DInput.eof());
	}
	

}