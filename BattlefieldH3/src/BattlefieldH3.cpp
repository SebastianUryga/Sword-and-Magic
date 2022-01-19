#include "GuiHandler.h"
bool end = false;
int main()
{
	
	std::thread main([=]() {
		Game game;
		game.run();
		end = true;
	});
	std::thread thr([=]() {
		while (!end)
			if (BH.battlefield && BH.battleBegan)
			{
				std::vector<std::thread> threads;
				for (auto& unit : BH.battlefield->units)
				{
					
					if (unit && unit!= nullptr && !unit->thread)
					{
						auto f = [=](std::shared_ptr<BattleUnit> unit) {
							unit->thread = true;
							while (unit->getAlive() && BH.battlefield)
								if (!unit->calculatingPaths())
								{
									std::this_thread::yield;
									std::this_thread::sleep_for(std::chrono::microseconds(50));
								}
						};

						threads.emplace_back( std::thread (f, unit));
						unit->thread = true;
						threads.back().detach();
						
					}
				}/*
				for (auto& t : threads)
				{
					t.detach();
					;
				}*/
				
				BH.battleBegan = false;
				std::this_thread::yield;
				std::this_thread::sleep_for(std::chrono::microseconds(100));

			}
	});

	thr.join();
	main.join();
	return 0;
}
