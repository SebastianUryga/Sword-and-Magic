#include "pch.h"
#include "interface_gamearea.h"
#include "Tiles.h"

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

void Interface::GameArea::initHeroList()
{
	playerListOfHero = new HeroList(1250, 0);
	for (auto& item : this->playerListOfHero->portraits)
	{
		this->interactiveElem.push_back(std::shared_ptr<HeroList::HeroItem>(item));
	}
	this->playerListOfHero->setHeroes(world.GetKingdom(PI->currentColorTurn).heroes);
}

HeroInstance * Interface::GameArea::curHero() const
{
	if (selection && selection->type == Obj::HERO)
		return static_cast<HeroInstance *>(selection);
	else
		return nullptr;
}

TownInstance * Interface::GameArea::curTown() const
{
	if (selection && selection->type == Obj::TOWN)
		return static_cast<TownInstance *>(selection);
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

sf::Vector2i Interface::GameArea::getScrollTileOffset() const
{
	return (sf::Vector2i) (this->scrollOffset / TILEWIDTH);
}

sf::View Interface::GameArea::getView() const
{
	return this->view;
}

int Interface::GameArea::getMode() const
{
	return this->mode;
}

void Interface::GameArea::focusOn(sf::Vector2f pos)
{
	this->scrollTime += 0.8;
	this->scrollDirection = ((pos - this->scrollOffset) - sf::Vector2f(20*TILEWIDTH, 15* TILEWIDTH));
}

bool Interface::GameArea::needScroll()
{
	if (this->scrollDirection.x != 0 || this->scrollDirection.y != 0)
		if (scrollTime > 1.f)
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
	this->rectMaps = sf::IntRect(0, 0, window->getSize().x-400, window->getSize().y);

	this->background.setSize(sf::Vector2f(
		(float)rectMaps.width, (float)rectMaps.height));

	this->initHeroList();

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
	if (mousePosWindow.y > (int)this->window->getSize().y -40) // nie ograniam
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
	
	for (int x = std::max(0,this->getScrollTileOffset().x - 1);
		x < std::min(world.w(), this->getScrollTileOffset().x + 51); x++)
		for (int y = std::max(0, this->getScrollTileOffset().y - 1);
			y < std::min(world.h(), this->getScrollTileOffset().y + 30); y++)
	{
		world.GetTile(x, y).renderGround(target);
		if(y > 0)
			world.GetTile(x, y-1).renderRoad(target);
	}
			
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
	this->playerListOfHero->render(target);
}

void Interface::MouseCursorAreaClickLeft(const sf::Vector2i tile)
{
	PI->tileLClicked(tile);
}

void Interface::MouseCursorAreaClickRight(const sf::Vector2i tile)
{
	PI->tileRClicked(tile);
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
	 None					,TopRight_Bottom	,TopRight_BottomRight},

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

Interface::HeroList::HeroList(float x, float y)
{
	this->selected = -1;
	this->background.setPosition(x, y);
	this->background.setSize(sf::Vector2f(50, 240));
	this->background.setFillColor(sf::Color(130, 112, 155, 255));
	for (int i = 0; i < 8; i++)
	{
		this->portraits.push_back(
			new HeroItem(i, &this->selected, x + 10, (i * 30)+ y + 10, nullptr));
	}	

}

void Interface::HeroList::addHero(HeroInstance * h)
{
	// check if there is already this hero
	for(auto item : this->portraits) if(item->h && h && item->h->id == h->id)
	{
		std::cout << "hero already is in HeroList" << std::endl;
		return;
	}
	int i = 0;
	// put in next empty slot
	while (i<8 && this->portraits[i]->h) i++; 
	if(i<8)
	{
		portraits[i]->h = h;
		this->update();
	}
}

void Interface::HeroList::setHeroes(std::vector<HeroInstance*>& playerHeroes)
{

	if (playerHeroes.size() > 8)
		std::cout << "za duzo cos tych herosow" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		if (i < playerHeroes.size())
			this->portraits[i]->h = playerHeroes[i];
		else
			this->portraits[i]->h = nullptr;
	}
	this->update();
}

void Interface::HeroList::update()
{
	for (int i = 7; i > 0; i--)
	{
		if (portraits[i]->h && portraits[i - 1]->h == nullptr)
		{
			portraits[i - 1]->h = portraits[i]->h;
			portraits[i]->h = nullptr;
			this->update();
			return;
		}
	}
	for (auto& item : this->portraits)
	{
		if (item->h)
			item->heroPortrait.setTextureRect(Graphics::selectSmallPortrait(item->h->name));

	}
	//updateing sprite
	//updating move
}

void Interface::HeroList::render(sf::RenderTarget * target)
{
	target->draw(this->background);
	for (auto& item : this->portraits)
	{
		if (item->h)
		{
			target->draw(item->heroPortrait);
			target->draw(item->movment);
		}
			
		if (selected == item->id)
			target->draw(item->selectFrame);
	}
		
}

void Interface::HeroList::HeroItem::clickLeft(bool down, bool previousState)
{
	if (down && previousState == false && this->h)
	{
		if (*this->sel == this->id)
			PI->openHeroWindow(this->h);
		else
		{
			*this->sel = this->id;
			PI->focusOn(this->h, true);
			PI->gameArea->selection = this->h;
			PI->canCalcuatePaths = true;

		}
	}
}

Interface::HeroList::HeroItem::HeroItem(int id, int* selected,float x, float y, HeroInstance * h)
{
	this->sel = selected;
	this->shape = sf::FloatRect(x, y, 34, 23);
	this->selectFrame.setPosition(x, y);
	this->selectFrame.setSize(sf::Vector2f(34, 23));
	this->selectFrame.setOutlineThickness(1);
	this->selectFrame.setFillColor(sf::Color::Transparent);
	this->selectFrame.setOutlineColor(sf::Color::Yellow);
	this->movment.setPosition(x - 2, y + 23);
	this->movment.setScale(1, -1);
	this->movment.setSize(sf::Vector2f(2, 27));
	this->heroPortrait.setPosition(x, y);
	this->heroPortrait.setTexture(*graphics.allHeroesPortraits);
	this->id = id;
	this->h = nullptr;
	
}
