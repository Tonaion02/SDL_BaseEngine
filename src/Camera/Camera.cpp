#include "Camera.h"





//------------------------------------------------------------------------------------
//Camera Class
//------------------------------------------------------------------------------------
void Camera::init(const Vector2i& tileDimension, const Vector2i& levelDimension)
{
	s_tileDimension = tileDimension;
	s_levelDimension = levelDimension;

	//Init RenderAdj 
	if (s_levelDimension.x * s_tileDimension.x < Options::get().getScreenDimension().x)
	{

	}
	else
	{
		s_renderAdj.x = 0;
	}

	if (s_levelDimension.y * s_tileDimension.y < Options::get().getScreenDimension().y)
	{

	}
	else
	{
		s_renderAdj.y = 0;
	}
	//Init RenderAdj
}



void Camera::updatePos(const Vector2i pos)
{
	this->s_pos = {pos.x + (s_tileDimension.x/2), pos.y + (s_tileDimension.y/2)};
	//Aggiornare anche RectRendering

	s_intTilePos = { s_pos.x / s_levelDimension.x, s_pos.y / s_levelDimension.y };

	s_nTileToRender = { (((Options::get().getScreenDimension().x / s_levelDimension.x) - 1) / 2), (((Options::get().getScreenDimension().y / s_levelDimension.y) - 1) / 2) };
	s_backToRender = { s_intTilePos.x - s_nTileToRender.x - 2,s_intTilePos.y - s_nTileToRender.y - 2 };
	s_frontToRender = { s_intTilePos.x + s_nTileToRender.x + 2,s_intTilePos.y + s_nTileToRender.y + 2 };
	s_startRectRendering = s_pos - Vector2i(Options::get().getScreenDimension().x / 2, Options::get().getScreenDimension().y / 2);
	s_endRectRendering = s_pos + Vector2i(Options::get().getScreenDimension().x / 2, Options::get().getScreenDimension().y / 2);

	//Controll value rendering
	if (s_startRectRendering.x <= 0)
	{
		s_startRectRendering.x = 0;
		s_endRectRendering.x = Options::get().getScreenDimension().x;
	}
	else if (s_endRectRendering.x >= (s_levelDimension.x * s_tileDimension.x))
	{
		s_startRectRendering.x = (s_levelDimension.x * s_tileDimension.x) - Options::get().getScreenDimension().x;
		s_endRectRendering.x = (s_levelDimension.x * s_tileDimension.x);
	}
	if (s_startRectRendering.y <= 0)
	{
		s_startRectRendering.y = 0;
		s_endRectRendering.y = Options::get().getScreenDimension().y;
	}
	else if (s_endRectRendering.y >= (s_levelDimension.y * s_tileDimension.y))
	{
		s_startRectRendering.y = (s_levelDimension.y * s_tileDimension.y) - Options::get().getScreenDimension().y;
		s_endRectRendering.y = (s_levelDimension.y * s_tileDimension.y);
	}
	//Controll value rendering

	//Controll value
	if (s_backToRender.x < 0)
	{
		s_backToRender.x = 0;
		s_frontToRender.x = Options::get().getScreenDimension().x / s_tileDimension.x;
	}

	if (s_backToRender.y < 0)
	{
		s_backToRender.y = 0;
		s_frontToRender.y = Options::get().getScreenDimension().y / s_tileDimension.y;
	}

	if (s_frontToRender.x > s_levelDimension.x)
	{
		s_frontToRender.x = s_levelDimension.x;
		s_backToRender.x = s_levelDimension.x - Options::get().getScreenDimension().x / s_tileDimension.x;
	}

	if (s_frontToRender.y > s_levelDimension.y)
	{
		s_frontToRender.y = s_levelDimension.y;
		s_backToRender.y = s_levelDimension.y - Options::get().getScreenDimension().y / s_tileDimension.y;
	}
	//Controll value

	if (s_levelDimension.x * s_tileDimension.x < Options::get().getScreenDimension().x)
	{

	}
	else
	{

	}

	if (s_levelDimension.y * s_tileDimension.y < Options::get().getScreenDimension().y)
	{

	}
	else
	{

	}
}



Vector2i Camera::getPlayerPos(const Vector2i startRendering) const
{
	return {s_pos.x - (s_tileDimension.x/2) - startRendering.x + s_renderAdj.x, s_pos.y - (s_tileDimension.y/2) - startRendering.y + s_renderAdj.y };
}



Vector2i Camera::getStartRectRendering() const
{
	return s_startRectRendering;
}



Vector2i Camera::getFrontToRender() const
{
	return s_frontToRender;
}



Vector2i Camera::getBackToRender() const
{
	return s_backToRender;
}
//------------------------------------------------------------------------------------
//Camera Class
//------------------------------------------------------------------------------------