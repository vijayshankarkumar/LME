#ifndef LAAL_CONSTANTS_HPP
#define LAAL_CONSTANTS_HPP

#include <gmtl/gmtl.h>
#include "Color.h"

typedef gmtl::Point3d Point;
typedef gmtl::Vec3d Vector;

namespace laal {

#define DEFAULT_ANIMATION_RUN_TIME   1
#define DEFAULT_ANIMATION_LAG_RATIO  0.0

#define ORIGIN Point(0.0, 0.0, 0.0)

#define LEFT   Vector(-1.0f, 0.0f, 0.0f)
#define RIGHT  Vector(1.0f, 0.0f, 0.0f)
#define UP     Vector(0.0f, 1.0f, 0.0f)
#define DOWN   Vector(0.0f, -1.0f, 0.0f)
#define OUT    Vector(0.0f, 0.0f, 1.0f)
#define IN     Vector(0.0f, 0.0f, -1.0f)

#define X_AXIS Vector(1.0f, 0.0f, 0.0f)
#define Y_AXIS Vector(0.0f, 1.0f, 0.0f)
#define Z_AXIS Vector(0.0f, 0.0f, 1.0f)

#define ASPECT_RATIO   gmtl::Vec2f(16.0f, 9.0f)
#define FRAME_WIDTH    16.0
#define FRAME_HEIGHT   9.0

#define DEFAULT_PIXEL_WIDTH  960
#define DEFAULT_PIXEL_HEIGHT 540
#define DEFAULT_FRAME_RATE   30

#define DEFAULT_STROKE_WIDTH 4

		const Color WHITE     (0xffffff);
		const Color BLACK     (0x000000);

		const Color RED       (0xff0000);
		const Color RED_A     (0xff3636);
		const Color RED_B     (0xff6363);
		const Color RED_C     (0xff8787);
		const Color RED_D     (0xffc4c4);

		const Color GREEN     (0x00ff00);
		const Color GREEN_A   (0x2eff2e);
		const Color GREEN_B   (0x63ff63);
		const Color GREEN_C   (0x91ff91);
		const Color GREEN_D   (0xb5ffb5);

		const Color BLUE      (0x0000ff);
		const Color BLUE_A    (0x2929ff);
		const Color BLUE_B    (0x5c5cff);
		const Color BLUE_C    (0x8c8cff);
		const Color BLUE_D    (0xbdbdff);

		const Color LIGHT_SALMON   (0xFFA07A);
		const Color SALMON         (0xFA8072);
		const Color DARK_SALMON    (0xE9967A);
		const Color LIGHT_CORAL    (0xF08080);
		const Color INDIAN_RED     (0xCD5C5C);
		const Color CRIMSON        (0xDC143C);
		const Color FIRE_BRICK     (0xB22222);
		const Color DARK_RED       (0x8B0000);

		const Color CORAL	      (0xFF7F50);
		const Color TOMATO	      (0xFF6347);
		const Color ORANGE_RED	  (0xFF4500);
		const Color GOLD	      (0xFFD700);
		const Color ORANGE	      (0xFFA500);
		const Color DARK_ORANGE	  (0xFF8C00);

		const Color YELLOW        (0xFFFF00);

		const Color BLUE_VIOLET	   (0x8A2BE2);
		const Color	DARK_VIOLET	   (0x9400D3);
		const Color	DARK_ORCHID	   (0x9932CC);
		const Color	DARK_MAGENTA   (0x8B008B);
		const Color	PURPLE	       (0x800080);
		const Color	INDIGO	       (0x4B0082);

		const Color     GRAINS_BORO	     (0xDCDCDC);
		const Color 	LIGHT_GRAY	     (0xD3D3D3);
		const Color 	SILVER	         (0xC0C0C0);
		const Color 	DARK_GRAY	     (0xA9A9A9);
		const Color 	GRAY	         (0x808080);
		const Color 	DIM_GRAY	     (0x696969);
		const Color 	LIGHT_SLATE_GRAY (0x778899);
		const Color 	SLATE_GRAY	     (0x708090);
		const Color 	DARK_SLATE_GRAY  (0x2F4F4F);

		const Color     ROSY_BROWN	(0xBC8F8F);
		const Color 	SANDY_BROWN	(0xF4A460);
		const Color 	GOLDEN_ROD	(0xDAA520);
		const Color 	PERU	    (0xCD853F);
		const Color 	CHOCOLATE	(0xD2691E);
		const Color 	SADDLE_BROWM(0x8B4513);
		const Color 	SIENNA	    (0xA0522D);
		const Color 	BROWN	    (0xA52A2A);
		const Color 	MAROON      (0x800000);

		const Color     POWDER_BLUE	      (0xB0E0E6);
		const Color 	LIGHT_BLUE	      (0xADD8E6);
		const Color 	LIGHT_SKY_BLUE	  (0x87CEFA);
		const Color 	SKY_BLUE	      (0x87CEEB);
		const Color 	DEEP_SKY_BLUE	  (0x00BFFF);
		const Color 	LIGHT_STEEL_BLUE  (0xB0C4DE);
		const Color 	DODGER_BLUE	      (0x1E90FF);
		const Color 	CORN_FLOWER_BLUE  (0x6495ED);
		const Color 	STEEL_BLUE	      (0x4682B4);
		const Color 	ROYAL_BLUE	      (0x4169E1);
		const Color 	MEDIUM_BLUE	      (0x0000CD);
		const Color 	DARK_BLUE	      (0x00008B);
		const Color 	NAVY	          (0x000080);
		const Color 	MID_NIGHT_BLUE	  (0x191970);
		const Color 	MEDIUM_SLATE_BLUE (0x7B68EE);
		const Color 	SLATE_BLUE	      (0x6A5ACD);
		const Color 	DARK_SLATE_BLUE	  (0x483D8B);

#define TOLERANCE_FOR_POINT_EQUILITY   0.0000000000001
}

#endif // !CONSTANTS_H
