#pragma once
class ILayer
{
public:

	virtual void draw() = 0;
	virtual void update() = 0;

	virtual ~ILayer() = default;

};

