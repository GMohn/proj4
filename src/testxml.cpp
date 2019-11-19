#include <gtest/gtest.h>
#include "XMLReader.h"
#include <sstream>

TEST(XMLReader, EmptyTest) {
	std::stringstream Input;
	XMLReader Reader(Input);

	EXPECT_TRUE(Reader.End());
}