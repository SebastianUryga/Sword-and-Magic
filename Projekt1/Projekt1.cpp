#include"pch.h"
#include"Game.h"


int main()
{
	
	std::thread main([=]() {
		Game game;
		game.run();
		PI->end = true;
	});
	
	std::thread thr([=]() {
		for (int i = 0; i < 999; i++)
		if (PI)
		{
			while (!PI->end)
			{
				if (PI->canCalcuatePaths)
					PI->calcuatePaths();
				else
					std::this_thread::yield();
			}
		}
		else
		{
			 std::this_thread::yield();
		}
	});
	thr.join();
	main.join();
	return 0;
}