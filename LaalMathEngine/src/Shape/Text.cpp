#include "Shape/Text.h"

namespace laal
{
	Text::Text()
	{
		m_sText = "Text";
		m_bHasText = true;
	}

	Text::Text(const Point& position, const std::string& text)
	{
		m_sText = text;
		m_bHasText = true;
		m_Position = position;
	}

	Text::~Text()
	{

	}

	void Text::SetText(const std::string& text)
	{
		m_sText = text;
		m_bHasText = true;
	}

	void Text::SetFontSize(unsigned int fontSize)
	{
		m_nFontSize = fontSize;
	}
}