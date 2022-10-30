#pragma once
#include "surface.h"
#include "template.h"

namespace Tmpl8 {

	class Rect2D
	{
	public:
		vec2 topLeft, topRight;
		vec2 bottomLeft, bottomRight;

		//Rect2D(vec2 tl, vec2 tr, vec2 bl, vec2 br) : topLeft(tl), topRight(tr), bottomLeft(bl), bottomRight(br) {}
		Rect2D(float width, float height){
			float w = width;
			float h = height;

			topLeft = vec2(0, 0);
			topRight = vec2(0, w);

			bottomLeft = vec2(0, h);
			bottomRight = vec2(w, h);
		}
		Rect2D(Sprite* sprite) {
			float w = sprite->GetWidth();
			float h = sprite->GetHeight();

			topLeft = vec2(0, 0);
			topRight = vec2(0, w);

			bottomLeft = vec2(0, h);
			bottomRight = vec2(w, h);
		}
		Rect2D() {};
	};
}
