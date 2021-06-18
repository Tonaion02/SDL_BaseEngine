#pragma once

#include "PrecompiledHeaders.h"

#include "Math/Vector.h"

#include "General/Options.h"





class Camera
{
public:
	static Camera& get()
	{
		static Camera instance;
		return instance;
	}

	void init(const Vector2i& tileDimension, const Vector2i& levelDimension);

	void updatePos(const Vector2i pos);

	Vector2i getPlayerPos(const Vector2i startRendering) const;
	Vector2i getStartRectRendering() const;
	Vector2i getFrontToRender() const;
	Vector2i getBackToRender() const;

protected:
	Camera() :s_tileDimension({ 32, 32 }) {}

protected:
	Vector2i s_pos;

	//Base info
	Vector2i s_tileDimension;
	Vector2i s_levelDimension;

	Vector2i s_startRectRendering, s_endRectRendering;
	Vector2i s_backToRender, s_frontToRender;
	Vector2i s_intTilePos;
	Vector2i s_nTileToRender;

	Vector2i s_renderAdj;
};