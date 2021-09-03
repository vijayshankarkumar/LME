#ifndef LAAL_CAMERA_HPP
#define LAAL_CAMERA_HPP

#include <blend2d.h>
#include <gmtl/gmtl.h>
#include <algorithm>

#include "Utils/Constants.h"
#include "Shape/Shape.h"

typedef gmtl::Point3d Point;
typedef gmtl::Vec3d Vector;

namespace laal
{
	class Camera
	{

	protected:

		Point m_Position;

		const double m_dFrameWidth;

		const double m_dFrameHeight;

		const unsigned int m_nPixelWidth;

		const unsigned int m_nPixelHeight;

		BLImage* m_Img;

		BLContext* m_Ctx;

		BLContext* m_CtxText;

		Shape* m_RootShape;

		BLFontFace m_FontFace;

	public:

		Camera();

		Camera(double frameWidth, double frameHeight, unsigned int pixelWidth, unsigned int pixelHeight);

		~Camera();

		void InitImage();

		void InitContext();

		void Capture();

		void GetImage();

		uint8_t* ImageData();

		unsigned int ImageStride();

		void ClearImage();

		double FrameWidth() const;

		double FrameHeight() const;

		unsigned int PixelWidth() const;

		unsigned int PixelHeight() const;

		void RenderShape(Shape* shape);

		void SetStrokeStyle(Shape* shape, BLContext* ctx);

		void SetFillStyle(Shape* shape, BLContext* ctx);

		void SetPath(Shape* shape);

		void LoadFont();

		void RenderText(Shape* shape);

		void SetText(const std::string& str, std::vector<std::vector<char>>& out);

		void SetRootShape(Shape* root);

		Shape* GetRootShape() const;

		void SortedShapes(std::vector<Shape*>& out);

		void SortedShapes(Shape* root, std::vector<Shape*>& shapes);
	};
}
#endif // !LAAL_CAMERA_HPP