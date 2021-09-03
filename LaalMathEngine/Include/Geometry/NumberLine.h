#ifndef LAAL_NUMBER_LINE_HPP
#define LAAL_NUMBER_LINE_HPP

#include "Shape/Text.h"
#include "Geometry/Polygon.h"

namespace laal
{
	enum TICK_TYPE
	{
		DOT_TICK = 0,
		LINE_TICK = 1
	};

	//! ============================================
	//! [NumberLine]
	//! ============================================
	class NumberLine : public Shape
	{
	protected:

		Line m_XAxis;

		Shape m_Ticks;

		Shape m_Labels;

		std::vector<Line> m_LineTicks;

		std::vector<Circle> m_DotTicks;
		
		std::vector<Text> m_LabelsText;

		std::vector<Line> m_LineSubTicks;

		std::vector<Circle> m_DotSubTicks;

		double m_dXRangeStart;

		double m_dXRangeEnd;

		double m_dInterval;

		unsigned int m_nDecimalPrecision;

		double m_dAxisStrokeWidth;

		double m_dTickStrokeWidth;

		double m_dTickLength;

		unsigned int m_nLabelFontSize;

		Color m_AxisColor;

		Color m_TickColor;

		Color m_LabelColor;

		TICK_TYPE m_nTickType;

	public:

		NumberLine();

		NumberLine(double xRangeStart, double xRangeEnd, double interval, unsigned int precision, TICK_TYPE tickType);

		virtual ~NumberLine();

		void InitAxis();

		void InitTicks();

		void InitLabels();

		std::string LabelText(double tickPos);

		void SubDivide(int n);

		Line* XAxis();

		Shape* Ticks();

		Shape* Labels();

		void ShowXAxis();

		void ShowTicks();

		void ShowLabels();

		void HideTicks();

		void HideLabels();

		void AxisStrokeWidth(double axisStrokeWdith);

		void TickStrokeWidth(double tickStrokeWidth);

		double AxisStrokeWidth() const;

		double TickStrokeWidth() const;

		void TickLength(double tickLength);

		double TickLength() const;

		void AxisColor(const Color& axisColor);
		
		void TickColor(const Color& tickColor);

		void LabelColor(const Color& labelColor);

		Color AxisColor() const;

		Color TickColor() const;

		Color LabelColor() const;

		TICK_TYPE TickType() const;
	};

	//! ============================================
	//! [NaturalNumberLine]
	//! ============================================
	class NaturalNumberLine : public NumberLine
	{
	public:

		NaturalNumberLine();

		NaturalNumberLine(int start, int end);

		virtual ~NaturalNumberLine();
	};
}

#endif // !LAAL_NUMBER_LINE_HPP
