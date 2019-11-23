#include "XMLReader.h"
#include <iostream>


CXMLReader::CXMLReader(std::istream& is) : DInput(is) {
	DParser = XML_ParserCreate(NULL);
	XML_SetUserData(DParser, this);
	XML_SetElementHandler(DParser, StartOfElements, EndOfElements);
	XML_SetCharacterDataHandler(DParser, CharOfElements);
}

CXMLReader::~CXMLReader() {
	XML_ParserFree(DParser);
}

void CXMLReader::StartOfElements(void* data, const char* el, const char** attr) {
	std::cout << "@ " << __LINE__ << std::endl;
	auto Reader = static_cast<CXMLReader*>(data);
	SXMLEntity XMLElement;
	XMLElement.DType = SXMLEntity::EType::StartElement;
	XMLElement.DNameData = std::string(el);
	int i = 0;
	//loop through attributes and load them in entity
	for (i = 0; attr[0] && attr[i + 2]; i += 2) {
		XMLElement.SetAttribute(std::string(attr[i]), std::string(attr[i + 1]));
	}
	Reader->DBuffered.push_back(XMLElement);
}
void CXMLReader::EndOfElements(void* data, const char* el) {
	std::cout << "@ " << __LINE__ << std::endl;
	auto Reader = static_cast<CXMLReader*>(data);
	SXMLEntity XMLElement;
	XMLElement.DType = SXMLEntity::EType::EndElement;
	XMLElement.DNameData = std::string(el);
	Reader->DBuffered.push_back(XMLElement);
}
void CXMLReader::CharOfElements(void* data, const char* el, int len) {
	std::cout << "@ " << __LINE__ << std::endl;
	auto Reader = static_cast<CXMLReader*>(data);
	SXMLEntity XMLElement;
	XMLElement.DType = SXMLEntity::EType::CharData;
	XMLElement.DNameData = std::string(el, len);
	Reader->DBuffered.push_back(XMLElement);
}


bool CXMLReader::End() {
	if(!DInput.eof()){
		DInput.peek();
	}
	return DBuffered.empty() and DInput.eof();
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata) {
	std::cout << "@ " << __LINE__ << std::endl;
	char Buffer[1024];
	while (!DInput.eof()) {
		DInput.read(Buffer, sizeof(Buffer));
		XML_Parse(DParser, Buffer, DInput.gcount(), DInput.eof());
		std::cout << "@ " << __LINE__ << std::endl;
	}
	if (!DBuffered.empty()) {
		//pop data
		if (skipcdata) {
			while (DBuffered.front().DType == SXMLEntity::EType::CharData) {
				DBuffered.pop_front();
			}
		}
		entity = DBuffered.front();
		DBuffered.pop_front();
		return true;
	}

}
