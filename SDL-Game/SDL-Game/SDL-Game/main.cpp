#include<SDL.h>
#include "Core/CGame.h"
#include <iostream>

const int FPS = 250;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	CGame &theGame = CGame::Instance();

	Uint32 frameStart, frameTime;

	//std::cout << "\[" << typeid(theGame).name() <<"]\n";


	CGame::Instance().init("SDL Game", 100, 100, 750, 580, false);
	while (CGame::Instance().isRunning())
	{
		frameStart = SDL_GetTicks();
		//SDL_ShowCursor(SDL_DISABLE);
		CGame::Instance().render();
		CGame::Instance().update();
		CGame::Instance().handleEvents();


		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}

	return 0;
}


//
//// CPP program to illustrate
//// working of Virtual Functions
//#include <iostream>
//using namespace std;
//
//class base {
//public:
//    virtual void fun_1() { cout << "base-1\n"; }
//    virtual void fun_2() { cout << "base-2\n"; }
//    virtual void fun_3() { cout << "base-3\n"; }
//
//};
//
//class derived : public base {
//public:
//    virtual void fun_1() { cout << "derived-1\n"; }
//    virtual void fun_2() { cout << "derived-2\n"; }
//    virtual void fun_3() { cout << "derived-3\n"; }
//};
//int main()
//{
//    base* p = new derived();
//
//    // Early binding because fun1() is non-virtual
//    // in base
//    p->fun_1();
//
//    // Late binding (RTP)
//    p->fun_2();
//
//    // Late binding (RTP)
//    p->fun_3();
//
//    // Late binding (RTP)
//
//    // Early binding but this function call is
//    // illegal(produces error) because pointer
//    // is of base type and function is of
//    // derived class
//    // p->fun_4(5);
//}
