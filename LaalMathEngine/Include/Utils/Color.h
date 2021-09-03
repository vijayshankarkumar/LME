#ifndef LAAL_COLOR_HPP
#define LAAL_COLOR_HPP

#include "Math/SimpleFunctions.h"

namespace laal 
{
	//! ===============================================
	//! [Color]
	//! ===============================================
	class Color 
	{

	private:

		double m_dRed;

		double m_dGreen;
		
		double m_dBlue;
		
		double m_dAlpha;

	public:

		Color();
		
		Color(double r, double g, double b, double a = 1.0);
		
		Color(unsigned int hexColor, double a = 1.0);

		~Color();

		unsigned int RGB();
		
		unsigned int RGBA();

		unsigned int ARGB();

		double Red() const;

		double Green() const;

		double Blue() const;

		double Alpha() const;

		void Red(double r);

		void Green(double g);
		
		void Blue(double b);
		
		void Alpha(double a);

		void Interpolate(const Color& start, const Color& end, double alpha);

	};
}

#endif // !LAAL_COLOR_HPP
