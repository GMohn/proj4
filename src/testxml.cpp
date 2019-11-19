#include <gtest/gtest.h>
#include "XMLReader.h"
#include <sstream>

TEST(CXMLReader, EmptyTest) {
	std::stringstream Input;
	CXMLReader Reader(Input);

	EXPECT_TRUE(Reader.End());
}