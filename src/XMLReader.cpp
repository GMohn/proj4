#include "XMLReader.h"

CXMLReader::CXMLReader(std::istream& is) : DInput(is) {
	DParser = XML_ParserCreate(NULL);
	XML_SetUserData(Dparser, this);
	XML_SetElementHandler(DParser, StartOfTags, EndOfTags);
	XML_SetCharacterDataHandler(Dparser, DText);
}

CXMLReader::~CXMLReader() {
	XML_ParserFree(DParser);
}

void CXMLReader::StartOfElements(void* data, const char* el, const char* attr[]) {
	auto Reader = static_cast<CXMLReader*>(reader);
	SXMLEntity XMLElement;
	XMLElement.DType = SXMLEntity::EType::StartElement;
	XMLElement.DNameData = std::string(el);
	for (int i = 0; attr[i]; i += 2) {
		XMLElement.SetAttribute(std::string(attr[i]), std::string(attr[i + 1]));
	}
	Reader->DBuffered.push_back(XMLElement);
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