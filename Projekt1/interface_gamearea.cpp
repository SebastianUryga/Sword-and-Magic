#include "pch.h"
#include "interface_gamearea.h"
#include "Tiles.h"

void Interface::GameArea::setTexturesToAllSprites()
{
	
	/*for (int x = 0; x < world.w(); x++)
		for (int y = 0; y < world.h(); y++)
		{
			Maps::Tile & tile = world.GetTiles(x, y);
			tile.setGroundTexture(*graphics.grounds[tile.GetGround()]);
		}*/
	/*for (auto &it : world.GetAllMapsObjects())
	{
		it->sprite.setTexture(*graphics.mapObjects[it->type]);
	}*/
}

void Interface::GameArea::initView()
{
	this->view.setSize(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	);
	this->view.setCenter(
		this->window->getSize().x / 2.f,
		this->window->getSize().y / 2.f
	);
}

HeroInstance * Interface::GameArea::curHero() const
{
	if (selection && selection->type == Obj::HERO)
		return static_cast<HeroInstance *>(selection);
	else
		return nullptr;
}

sf::Vector2f Interface::GameArea::getScrollOffset() const
{
	return this->scrollOffset;
}

sf::Vector2f Interface::GameArea::getScrollDirection() const
{
	return this->scrollDirection;
}

int Interface::GameArea::getMode() const
{
	return this->mode;
}

void Interface::GameArea::focusOn(sf::Vector2f pos)
{
	this->scrollTime += 2;
	this->scrollDirection = ((pos - this->scrollOffset) - sf::Vector2f(20*TILEWIDTH, 15* TILEWIDTH));
}

bool Interface::GameArea::needScroll()
{
	if (this->scrollDirection.x != 0 || this->scrollDirection.y != 0)
		if (scrollTime > 3.f)
		{
			scrollTime = 0;
			return true;
		}
	return false;
}

bool Interface::GameArea::contains(sf::Vector2i point) const
{
	return this->rectMaps.contains(point);
}

void Interface::GameArea::built(sf::RenderWindow* window,  int mode)
{
	this->window = window;
	this->mode = mode;
	this->rectMaps = sf::IntRect(0, 0, window->getSize().x, window->getSize().y);

	this->background.setSize(sf::Vector2f(
		(float)rectMaps.width, (float)rectMaps.height));

	for (int x = 0; x < world.w(); x++)
		for (int y = 0; y < world.h(); y++)
		{
			this->interactiveElem.push_back(std::shared_ptr<Maps::Tile>(&world.GetTile(x, y), [](Maps::Tile *){}));
		}

	this->initView();
	// taki tymczasowy kod
	if (world.vec_heros.size() > 0)
		selection = world.vec_heros[0];
	else
		selection = nullptr;
	float i = 0;
	
	// ustawia wszystkim obiektom textury
	// chwilowo nie potrzebne
	//this->setTexturesToAllSprites();
}

Interface::GameArea::GameArea()
	:WindowObject(0,0,0,0,this->font)
{
	this->rectMaps.top = 0.f;
	this->rectMaps.left = 0.f;
	this->scrollSpeed = 20.f;
	this->scrollTime = 10.f;
	this->scrollOffset = sf::Vector2f(0, 0);
	this->scrollDirection = sf::Vector2f(0, 0);
	this->window = nullptr;
}

Interface::GameArea::~GameArea()
{

}

void Interface::GameArea::updateView()
{
	if (this->needScroll())
	{
		this->view.move(this->getScrollDirection());
		this->scrollOffset += this->scrollDirection;
		this->scrollDirection = sf::Vector2f(0, 0);
	}
}

void Interface::GameArea::updateInput(const float dt, sf::Vector2i mousePosWindow)
{
	if (!this->active)
		return;
	this->scrollTime += dt * this->scrollSpeed;
	if (mousePosWindow.x < 2)
		this->scrollDirection.x = -TILEWIDTH;
	if (mousePosWindow.y < 2)
		this->scrollDirection.y = -TILEWIDTH;
	if (mousePosWindow.x > (int)this->window->getSize().x -10) // lol
		this->scrollDirection.x = TILEWIDTH;
	if (mousePosWindow.y > (int)this->window->getSize().y -30) // nie ograniam
		this->scrollDirection.y = TILEWIDTH;
}

void Interface::GameArea::update(const float dt, sf::Vector2i mousePosWindow)
{
	this->updateInput(dt, mousePosWindow);
	this->updateView();
	for (auto it : world.GetAllMapsObjects())
	{
		it->update(dt);
	}
}

void Interface::GameArea::render(sf::RenderTarget * target)
{
	target->setView(this->view);
	
	for (int x = 0; x < world.w(); x++)
		for (int y = 0; y < world.h(); y++)
			world.GetTile(x, y).renderGround(target);
	//
	// mapObjects render();
	for (auto it : world.GetAllMapsObjects())
	{
		target->draw(it->sprite);

		it->render(target);
	}
	if(curHero() && curHero()->currentPath)
	for (auto& moveArrow : GetHeroMoveArrows())
	{
		if (moveArrow.toDraw)
			target->draw(moveArrow.sprite);
		else
			break;
	}

	if(mode == Interface::GameMode) // jesli tworzymy swiat to nie potrzebujemy mgly wojny
	for (int x = 0; x < world.w(); x++)
		for (int y = 0; y < world.h(); y++)
			if(world.GetTile(x, y).isFog(PI->getCurrentColor()))
				world.GetTile(x, y).renderFog(target); // rysujemy mgle wojny

	target->setView(this->window->getDefaultView());
}

void Interface::MouseCursorAreaClickLeft(const sf::Vector2i mousePos)
{
}

Interface::GameArea & Interface::GetGameArea()
{
	if (!PI->gameArea)
		assert(0);
	return *PI->gameArea;
}

ButtonsArea & Interface::GetButtonsArea()
{
	return Interface::buttonsArea;
}

Interface::AdvMapArrows & Interface::GetHeroMoveArrows()
{
	return Interface::heroMoveArrows;
}

Arrow& Interface::AdvMapArrows::top()
{
	assert(topIndex > -1);
	Arrow& arrow = this->at(topIndex);
	if(arrow.toDraw)
		return arrow;
	else
	{
		if (topIndex == 0)
			return arrow;
		topIndex--;
		return top();
	}
}

void Interface::AdvMapArrows::calcuateArrows(std::shared_ptr<Path> path)
{
	static ArrowDirection dirs[9][9] = {
	{TopLeft_TopLeft		,TopLeft_Top		,TopLeft_TopRight,
	 TopLeft_Left			,None				,TopLeft_Right,
	 TopLeft_BottomLeft		,TopLeft_Bottom		,Top_TopLeft},

	{Top_TopLeft			,Top_Top			,Top_TopRight,
	 Top_Left				,None				,Top_Right,
	 Top_BottomLeft			,None				,Top_BottomRight},

	{TopRight_TopLeft		,TopRight_Top, TopRight_TopRight,
	 TopRight_Left			,None				,TopRight_Right,
	 None					, TopRight_Bottom	,TopRight_BottomRight},

	{Left_TopLeft			,Left_Top			,Left_TopRight,
	 Left_Left				,None				,None,
	 Left_BottomLeft		,Left_Bottom		,Left_BottomRight},

	{None, None, None, None, None, None, None, None, None},

	{Right_TopLeft			,Right_Top			,Right_TopRight,
	 None					,None				,Right_Right,
	 Right_BottomLeft		,Right_Bottom		,Right_BottomRight},

	{BottomLeft_TopLeft		,BottomLeft_Top		,None,
	 BottomLeft_Left		,None				,BottomLeft_Right,
	 BottomLeft_BottomLeft	,BottomLeft_Bottom	,BottomLeft_BottomRight},

	{Bottom_TopLeft			,None				,Bottom_TopRight,
	 Bottom_Left			,None				,Bottom_Right,
	 Bottom_BottomLeft		,Bottom_Bottom		,Bottom_BottomRight},

	{None					,BottomRight_Top	,BottomRight_TopRight,
	 BottomRight_Left		,None				,BottomRight_Right,
	 BottomRight_BottomLeft	,BottomRight_Bottom	,BottomRight_BottomRight}
	};

	if (!path)
		return;
	if (path->nodes.size() > this->topIndex)
	{
		this->resize(path->nodes.size());
		for (; topIndex < path->nodes.size() - 1 ; topIndex++)
			this->at(topIndex).setTexture(*graphics.heroMoveArrows);
	}
	for (auto& arrow: *this)
		arrow.toDraw = false;
	for (int i = 0; i < (int)path->nodes.size() - 1; ++i)
	{
		const sf::Vector2i &curPos = path->nodes[i].coord, &nextPos = path->nodes[i + 1].coord;

		ArrowDirection dir = None;
		if (i == 0) //last tile
		{
			int x = (int)TILEWIDTH * curPos.x,
				y = (int)TILEWIDTH * curPos.y;
			if (x < 0 || y < 0)
				continue;
			dir = EndPath;
		}
		else
		{
			const sf::Vector2i &prevPos = path->nodes[i - 1].coord;
			std::vector<PathNode> & cv = path->nodes;
			/* Vector directions
			 *  0   1   2
			 *    \ | /
			 *  3 - 4 - 5
			 *    / | \
			 *  6   7  8
			 *For example:
			 *  |
			 *  |__\
			 *     /
			 * is id1=7, id2=5 (pns[7][5])
			*/
			//bool pathContinuous = curPos.areNeighbours(nextPos) && curPos.areNeighbours(prevPos);
			int id1 = (curPos.x - nextPos.x + 1) + 3 * (curPos.y - nextPos.y + 1);   //Direction of entering vector
			int id2 = (cv[i - 1].coord.x - curPos.x + 1) + 3 * (cv[i - 1].coord.y - curPos.y + 1); //Direction of exiting vector
			dir = dirs[id1][id2];
		}
		if (path->nodes[i].turns)
			this->at(i).reachbleInOneTurn = false;
		else
			this->at(i).reachbleInOneTurn = true;
		if (dir >= 0)
		{
			int x = (int)TILEWIDTH * (curPos.x),
				y = (int)TILEWIDTH * (curPos.y);
			this->at(i).toDraw = true;
			this->at(i).setType(dir);
			this->at(i).setPosition(x, y);
		}
		topIndex = path->nodes.size() - 1;
	}
}

Interface::AdvMapArrows::AdvMapArrows()
{
	path = nullptr;
	topIndex = 0;
}

void Interface::AdvMapArrows::eraseArrow(const sf::Vector2i & heroPos)
{
	float x = this->back().sprite.getPosition().x;
	float y = this->back().sprite.getPosition().y;
	this->top().toDraw = false;
	
}
