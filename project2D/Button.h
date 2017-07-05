#pragma once
#include "Renderer2D.h"
#include "Input.h"
#include <string>
#include <memory>

struct Colour
{
	float red, green, blue, alpha;
};

class Button
{
public:
	Button();
	Button(float x, float y, std::string text, aie::Font* font);
	~Button();

	void SetForegroundColour(Colour c);
	void SetBackgroundColour(Colour c);
	void SetText(std::string _text);
	void Draw(aie::Renderer2D* renderer);
	bool Collision();

	float getX();
	float getY();

	bool visible;
	bool enabled;

private:
	Colour foregroundColour, backgroundColour;
	float xPos, yPos, width, height;
	std::string text;
	aie::Font* font;
	bool autosize;

	int paddingLeft = 5;
	int paddingTop = 5;
	int paddingRight = 5;
	int paddingBottom = 5;
};