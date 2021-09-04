# LME
![frame0](https://user-images.githubusercontent.com/39207277/132066669-47a8cf0b-1d87-4c33-af78-5628614dab8a.png)

Animation engine for Mathematical simulations in C++. This project is highly inspired from 3b1b's Manim.
LME is built with C++17 on Visual Studio 2019 and Windows 10 platform. It can be used for making Math videos as the animation is converted to videos on the fly. It consists of wide range of animation classes that can be used for Mathematical Simualations.\
NOTE: This project is highly under production.

# Use Cases
* It can be used as **Graphing Application** to plot mathematical functions and parametric equations.
* For **Data Visualization** as it has all tools built in or can be extended.
* For **Data Structure and Algorith** visualizer.
* It can used as svg rendering engine.

# Example
```cpp
class TestScene : public laal::Scene
{
public:

	void Construct() override
	{
		laal::Line ln(Point(-1, 0, 0), Point(1, 0, 0));
		ln.StrokeColor(laal::ORANGE_RED);
		Add(&ln);

		auto func1 = [](double t)
		{
			return t;
		};
		auto func2 = [](double t)
		{
			return (1.0 / gmtl::Math::TWO_PI) * gmtl::Math::sin(t * gmtl::Math::TWO_PI);
		};

		laal::ParametricCurve pc(func1, func2, -1, 1);
		pc.StrokeColor(laal::BLUE_VIOLET);
		Add(&pc);

		laal::Arrow ar(Point(0, 0, 0), Point(0.5, 0.0, 0.0));
		Add(&ar);

		laal::ShapeGroup sg;
		laal::Dot dt;
		dt.Translate(0.5, 0.0,  0.0);
		sg.Add(&dt);
		laal::Line ln1(Point(0.0, 0.0, 0.0), Point(0.5, 0.0, 0.0));
		ln1.StrokeColor(laal::WHITE);
		sg.Add(&ln1);
		Add(&sg);

		laal::FollowPath fp(&sg, func1, func2, -1, 1, 3.0, 0);
		fp.EaseFunction(laal::EaseInOutExpo);
		Add(&fp);
		fp.Begin();
		Play();
		Wait(0.5);
	}
};
```

# System Requirement
* C++ 17
* Visual Studio 2019 or higher with UTF-8 encoding enabled
* FFMPEG

# Dependencies
[Blend2d](https://blend2d.com/) The rendering engine of LME.\
[FFMPEG](https://www.ffmpeg.org/) Media Library used in LME for video encoding and muxing.\
[GMTL](http://ggt.sourceforge.net/html/main.html) Generic Math Template Library.\
[FreeType](https://www.freetype.org/) Text type setting library. 

# Installation
Clone the project in Visual Studio 2019 or higher with C++ 17 enabled and handle all dependencies(see **Dependencies** section for more). Build the whole visual studio solution and run the example code in **Applicaiton.cpp**.

# Contributing
Contribution to this project is always welcomed.

# License
This project falls under MIT License.
