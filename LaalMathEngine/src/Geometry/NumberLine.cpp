#include "Geometry/NumberLine.h"

namespace laal
{
	NumberLine::NumberLine() :
		m_dXRangeStart(-5.0),
		m_dXRangeEnd(5.0),
		m_dInterval(0.5),
		m_nDecimalPrecision(1),
		m_dAxisStrokeWidth(5),
		m_dTickStrokeWidth(5),
		m_dTickLength(0.05),
		m_nLabelFontSize(12),
		m_AxisColor(0x214580),
		m_TickColor(0x214580),
		m_LabelColor(WHITE),
		m_nTickType(LINE_TICK)
	{
		InitAxis();
		InitTicks();
		InitLabels();

		ShowXAxis();
		ShowTicks();
		ShowLabels();
	}

	NumberLine::NumberLine(double xRangeStart, double xRangeEnd, double interval, unsigned int precision, TICK_TYPE ticktType) :
		m_dXRangeStart(xRangeStart),
		m_dXRangeEnd(xRangeEnd),
		m_dInterval(interval),
		m_nDecimalPrecision(precision),
		m_dAxisStrokeWidth(5),
		m_dTickStrokeWidth(5),
		m_dTickLength(0.05),
		m_nLabelFontSize(12),
		m_AxisColor(0x214580),
		m_TickColor(0x214580),
		m_LabelColor(WHITE),
		m_nTickType(ticktType)
	{
		InitAxis();
		InitTicks();
		InitLabels();

		ShowXAxis();
		ShowTicks();
		ShowLabels();
	}

	NumberLine::~NumberLine()
	{

	}

	void NumberLine::InitAxis()
	{
		m_XAxis = Line(Point(-1.0, 0.0, 0.0), Point(1.0, 0.0, 0.0));
		m_XAxis.StrokeColor(m_AxisColor);
		m_XAxis.StrokeWidth(m_dAxisStrokeWidth);
	}

	void NumberLine::InitTicks()
	{

		std::vector<double> tickPos;
		double shift = (m_dXRangeEnd + m_dXRangeStart) / 2.0;
		double scale = 1.0 / (m_dXRangeEnd - shift);
		double start = m_dXRangeStart;
		while (start <= m_dXRangeEnd)
		{
			tickPos.push_back(start);
			start += m_dInterval;
		}

		for (double tp : tickPos)
		{
			switch (m_nTickType)
			{
			case DOT_TICK:
			{
				Circle tick(m_dTickLength / 2.0);
				tick.MoveTo((tp - shift) * scale, 0.0, 0.0);
				tick.FillColor(m_TickColor);
				tick.StrokeWidth(0.0);
				m_DotTicks.push_back(tick);
				break; 
			}

			case LINE_TICK:
			{
				Line tick(Point((tp - shift) * scale, m_dTickLength / 2.0, 0.0), Point((tp - shift) * scale, -1.0 * m_dTickLength / 2.0, 0.0));
				tick.StrokeColor(m_TickColor);
				tick.StrokeWidth(m_dTickStrokeWidth);
				m_LineTicks.push_back(tick);
				break; 
			}

			default:
				break;
			}
		}
		
		switch (m_nTickType)
		{
		case DOT_TICK:
			for (Circle& tick : m_DotTicks)
			{
				m_Ticks.Add(&tick);
			}
			break;

		case LINE_TICK:
			for (Line& tick : m_LineTicks)
			{
				m_Ticks.Add(&tick);
			}
			break;

		default:
			break;
		}
	}

	void NumberLine::InitLabels()
	{
		std::vector<double> tickPos;
		double shift = (m_dXRangeEnd + m_dXRangeStart) / 2.0;
		double scale = 1.0 / (m_dXRangeEnd - shift);
		double start = m_dXRangeStart;
		while (start <= m_dXRangeEnd)
		{
			tickPos.push_back(start);
			start += m_dInterval;
		}

		for (double tp : tickPos)
		{
			Text label(Point((tp - shift) * scale, -1.0 * m_dTickLength - 0.02, 0.0), LabelText(tp));
			label.FillColor(m_LabelColor);
			label.SetFontSize(m_nLabelFontSize);
			m_LabelsText.push_back(label);
		}

		for (Text& label : m_LabelsText)
		{
			m_Labels.Add(&label);
		}
	}

	std::string NumberLine::LabelText(double tickPos)
	{
		std::string label = std::to_string(tickPos);
		size_t i = 0, j;
		while (i < label.length())
		{
			if (label[i] == '.')
			{
				j = i + 1;
				unsigned int cnt = 0;
				while (j < label.length() && cnt < m_nDecimalPrecision)
				{
					j++;
					cnt++;
				}
				label.resize(j);
				break;
			}
			i++;
		}
		if (m_nDecimalPrecision == 0)
		{
			label.pop_back();
		}
		return label;
	}

	void NumberLine::SubDivide(int n)
	{
		if (m_Ticks.ChildShapes().empty())
		{
			return;
		}

		std::vector<Shape*> childShapes = m_Ticks.ChildShapes();
		for (size_t i = 0; i < childShapes.size() - 1; i++)
		{
			std::vector<Point> tickPos = Linspace(childShapes[i]->Position(), childShapes[i + 1]->Position(), n + 1); 
			for (size_t j = 1; j < n; j++)
			{
				switch (m_nTickType)
				{
				case DOT_TICK:
				{
					Circle subTick(m_dTickLength / 4.0);
					subTick.MoveTo(tickPos[j]);
					subTick.FillColor(m_TickColor);
					subTick.StrokeWidth(0.0);
					m_DotSubTicks.push_back(subTick);
					break; 
				}

				case LINE_TICK:
				{
					Line subTick(Point(tickPos[j][0], tickPos[j][1] + m_dTickLength / 4.0, 0.0), Point(tickPos[j][0], tickPos[j][1] - m_dTickLength / 4.0, 0.0));
					subTick.StrokeColor(m_TickColor);
					subTick.StrokeWidth(m_dTickStrokeWidth / 2.0);
					m_LineSubTicks.push_back(subTick);
					break; 
				}

				default:
					break;
				}
			}
		}

		switch (m_nTickType)
		{
		case DOT_TICK:
			for (Circle& subTick : m_DotSubTicks)
			{
				m_Ticks.Add(&subTick);
			}
			break;

		case LINE_TICK:
			for (Line& subTick : m_LineSubTicks)
			{
				m_Ticks.Add(&subTick);
			}
			break;

		default:
			break;
		}
	}

	Line* NumberLine::XAxis()
	{
		return &m_XAxis;
	}

	Shape* NumberLine::Ticks()
	{
		return &m_Ticks;
	}

	Shape* NumberLine::Labels()
	{
		return &m_Labels;
	}

	void NumberLine::ShowXAxis()
	{
		Add(&m_XAxis);
	}

	void NumberLine::ShowTicks()
	{
		Add(&m_Ticks);
	}

	void NumberLine::ShowLabels()
	{
		Add(&m_Labels);
	}

	void NumberLine::HideTicks()
	{
		Remove(&m_Ticks);
	}

	void NumberLine::HideLabels()
	{
		Remove(&m_Labels);
	}

	void NumberLine::AxisStrokeWidth(double axisStrokeWidth)
	{
		m_dAxisStrokeWidth = axisStrokeWidth;
		m_XAxis.StrokeWidth(axisStrokeWidth);
	}

	void NumberLine::TickStrokeWidth(double tickStrokeWidth)
	{
		m_dTickStrokeWidth = tickStrokeWidth;
		m_Ticks.StrokeWidth(tickStrokeWidth);
	}

	double NumberLine::AxisStrokeWidth() const
	{
		return m_dAxisStrokeWidth;
	}

	double NumberLine::TickStrokeWidth() const
	{
		return m_dTickStrokeWidth;
	}

	void NumberLine::TickLength(double tickLength)
	{
		for (Shape* tick : m_Ticks.ChildShapes())
		{
			tick->Scale(m_dTickLength / tickLength);
		}
		m_dTickLength = tickLength;
	}

	double NumberLine::TickLength() const
	{
		return m_dTickLength;
	}

	void NumberLine::AxisColor(const Color& axisColor)
	{
		m_AxisColor = axisColor;
		m_XAxis.StrokeColor(axisColor);
	}

	void NumberLine::TickColor(const Color& tickColor)
	{
		m_TickColor = tickColor;
		m_Ticks.StrokeColor(tickColor);
	}

	void NumberLine::LabelColor(const Color& labelColor)
	{
		m_LabelColor = labelColor;
		m_Labels.FillColor(labelColor);
	}

	Color NumberLine::AxisColor() const
	{
		return m_AxisColor;
	}

	Color NumberLine::TickColor() const
	{
		return m_TickColor;
	}

	Color NumberLine::LabelColor() const
	{
		return m_LabelColor;
	}

	TICK_TYPE NumberLine::TickType() const
	{
		return m_nTickType;
	}

	NaturalNumberLine::NaturalNumberLine() :
		NumberLine(-5.0, 5.0, 1.0, 0, LINE_TICK)
	{
		SubDivide(2);
	}

	NaturalNumberLine::NaturalNumberLine(int start, int end) :
		NumberLine((double)start, (double)end, 1.0, 0, LINE_TICK)
	{
		SubDivide(2);
	}

	NaturalNumberLine::~NaturalNumberLine()
	{

	}
}