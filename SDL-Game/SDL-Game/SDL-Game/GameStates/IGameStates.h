#pragma once
#include <string>
#include <iostream>

class IGameStates
{
public:
	virtual ~IGameStates() { /*std::cout << "~IIGameStates()" << std::endl; */ }
	virtual void update(double dt) = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;

};