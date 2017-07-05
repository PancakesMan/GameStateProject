#include "Button.h"
#include <Font.h>

#pragma region constructors/destructor
Button::Button() : Button(0, 0, "", nullptr)
{
	//
}
Button::Button(float x, float y, std::string _text, aie::Font* _font)
{
	xPos = x;
	yPos = y;
	text = _text;
	font = _font;
	autosize = true;
	visible = true;
	enabled = true;

	SetForegroundColour({ 1.f, 1.f, 1.f, 1.f });
	SetBackgroundColour({ 1.f, 1.f, 1.f, .25f });
}
Button::~Button()
{
	delete font;
}
#pragma endregion

#pragma region public functions
void Button::SetForegroundColour(Colour c)
{
	this->foregroundColour = c;
}
void Button::SetBackgroundColour(Colour c)
{
	this->backgroundColour = c;
}
void Button::SetText(std::string _text)
{
	text = _text;
}
// Draws the button using the provided renderer
void Button::Draw(aie::Renderer2D* renderer)
{
	if (visible)
	{
		aie::Input* input = aie::Input::getInstance();

		if (autosize)
		{
			width = font->getStringWidth(text.c_str());
			height = font->getStringHeight(text.c_str());
		}

		//Draw Border
		if (enabled)
		{
			if (Collision()) // Change colour on mouseover
				renderer->setRenderColour(backgroundColour.red, backgroundColour.green, backgroundColour.blue, backgroundColour.alpha * 2.f);
			else // Use non-mouseover colour
				renderer->setRenderColour(backgroundColour.red, backgroundColour.green, backgroundColour.blue, backgroundColour.alpha);
		}
		else
			renderer->setRenderColour(backgroundColour.red, backgroundColour.green, backgroundColour.blue, backgroundColour.alpha * 0.5f);
		renderer->drawBox(xPos, yPos, width + paddingLeft + paddingRight, height + paddingTop + paddingBottom);

		//Draw Text
		if (enabled)
		{
			if (Collision()) // Change colour on mouseover
				renderer->setRenderColour(foregroundColour.red, foregroundColour.green, foregroundColour.blue, foregroundColour.alpha * 2.f);
			else // Use non-mouseover colour
				renderer->setRenderColour(foregroundColour.red, foregroundColour.green, foregroundColour.blue, foregroundColour.alpha);
		}
		else // Use disabled colour
			renderer->setRenderColour(foregroundColour.red, foregroundColour.green, foregroundColour.blue, foregroundColour.alpha * 0.5f);
		renderer->drawText(font, text.c_str(), xPos - width / 2, yPos - height / 2);
	}
}

// Returns true if mouse is inside button bounds
bool Button::Collision()
{
	// Get instance of input
	aie::Input* input = aie::Input::getInstance();

	// If the button is not enabled
	// collision is ignored
	if (!enabled)
		return false;

	return input->getMouseX() > xPos - width / 2 - paddingLeft && input->getMouseX() < xPos + width / 2 + paddingRight
		&& input->getMouseY() > yPos - height / 2 - paddingBottom && input->getMouseY() < yPos + height / 2 + paddingTop;
}

float Button::getX() {
	return xPos;
}

float Button::getY() {
	return yPos;
}
#pragma endregion