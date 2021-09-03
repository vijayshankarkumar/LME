#ifndef LAAL_TEXT_HPP
#define LAAL_TEXT_HPP

#include "Shape/Shape.h"

namespace laal
{
	class Text : public Shape
	{

	public:

		Text();
		
		Text(const Point& position, const std::string& text);

		virtual ~Text();

		void SetText(const std::string& text);

		void SetFontSize(unsigned int fontSize);
	};
}

#endif // !LAAL_TEXT_HPP
