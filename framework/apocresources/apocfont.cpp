#include "framework/apocresources/apocfont.h"
#include "framework/data.h"
#include "framework/font.h"
#include "framework/framework.h"
#include "framework/logger.h"
#include "library/sp.h"

// Disable automatic #pragma linking for boost - only enabled in msvc and that should provide boost
// symbols as part of the module that uses it
#define BOOST_ALL_NO_LIB
#include <boost/locale.hpp>
#include <tinyxml2.h>

namespace OpenApoc
{

sp<BitmapFont> ApocalypseFont::loadFont(tinyxml2::XMLElement *fontElement)
{
	int spacewidth = 0;
	int height = 0;
	UString fontName;

	std::map<UniChar, UString> charMap;

	const char *attr = fontElement->Attribute("name");
	if (!attr)
	{
		LogError("apocfont element with no \"name\" attribute");
		return nullptr;
	}
	fontName = attr;

	auto err = fontElement->QueryIntAttribute("height", &height);
	if (err != tinyxml2::XML_SUCCESS || height <= 0)
	{
		LogError("apocfont \"%s\" with invalid \"height\" attribute", fontName.cStr());
		return nullptr;
	}
	err = fontElement->QueryIntAttribute("spacewidth", &spacewidth);
	if (err != tinyxml2::XML_SUCCESS || spacewidth <= 0)
	{
		LogError("apocfont \"%s\" with invalid \"spacewidth\" attribute", fontName.cStr());
		return nullptr;
	}

	for (auto *glyphNode = fontElement->FirstChildElement(); glyphNode;
	     glyphNode = glyphNode->NextSiblingElement())
	{
		UString nodeName = glyphNode->Name();
		if (nodeName != "glyph")
		{
			LogError("apocfont \"%s\" has unexpected child node \"%s\", skipping", fontName.cStr(),
			         nodeName.cStr());
			continue;
		}
		auto *glyphPath = glyphNode->Attribute("glyph");
		if (!glyphPath)
		{
			LogError("Font \"%s\" has glyph with missing string attribute - skipping glyph",
			         fontName.cStr());
			continue;
		}
		auto *glyphString = glyphNode->Attribute("string");
		if (!glyphString)
		{
			LogError("apocfont \"%s\" has glyph with missing string attribute - skipping glyph",
			         fontName.cStr());
			continue;
		}

		auto pointString = boost::locale::conv::utf_to_utf<UniChar>(glyphString);

		if (pointString.length() != 1)
		{
			LogError("apocfont \"%s\" glyph \"%s\" has %lu codepoints, expected one - skipping "
			         "glyph",
			         fontName.cStr(), glyphString, pointString.length());
			continue;
		}
		UniChar c = pointString[0];

		if (charMap.find(c) != charMap.end())
		{
			LogError("Font \"%s\" has multiple glyphs for string \"%s\" - skipping glyph",
			         fontName.cStr(), glyphString);
			continue;
		}

		charMap[c] = glyphPath;
	}

	auto font = BitmapFont::loadFont(charMap, spacewidth, height, fontName,
	                                 fw().data->loadPalette(fontElement->Attribute("palette")));
	return font;
}
}; // namespace OpenApoc
