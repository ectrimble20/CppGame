/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	imgLib(ImageLibrary()),
	bgSurface(imgLib.SeekImage("charcoal64")),
	testImgHideShow(imgLib.SeekImage("man1_front_idle")),
	testButton(Button(Rect(128.0f, 32.0f, Vector2(200.0f, 150.0f)), Surface(imgLib.SeekImage("button_exit"))))
{
	GameLogger::Log("Game Object Initialized");
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.mouse.LeftIsPressed())
	{
		Vector2 clickSpot(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
		if (testButton.Clicked(clickSpot))
		{
			GameLogger::Log("Click at " + std::to_string(wnd.mouse.GetPosX()) + "," + std::to_string(wnd.mouse.GetPosY()) + " was on the button");
			if (showText) {
				showText = false;
			}
			else {
				showText = true;
			}
		}
		else
		{
			GameLogger::Log("Click at " + std::to_string(wnd.mouse.GetPosX()) + "," + std::to_string(wnd.mouse.GetPosY()) + " was NOT on the button");
		}
	}
}

void Game::ComposeFrame()
{
	/*
	//Test code to see if my stupid image lib is working
	holder = Surface(imageLib.SeekImage("man1_front_idle"));
	gfx.DrawSurface(32, 32, holder, Colors::Magenta, false);
	holder = Surface(imageLib.SeekImage("man2_front_idle"));
	gfx.DrawSurface(64, 32, holder, Colors::Magenta, false);
	holder = Surface(imageLib.SeekImage("man_front_idle"));
	gfx.DrawSurface(96, 32, holder, Colors::Magenta, false);
	//okay so lets try to write something to the screen with our broke ass font class.
	//okay so we're going to test out Font import method now since we're using our existing sprite sheet method to import it
	holder = Surface(imageLib.SeekImage("Lucida_33")); //should draw an A
	gfx.DrawSurface(32, 128, holder, Colors::Magenta, false);
	holder = Surface(imageLib.SeekImage("Lucida_34")); //should draw an B
	gfx.DrawSurface(64, 128, holder, Colors::Magenta, false);
	holder = Surface(imageLib.SeekImage("Lucida_35")); //should draw an C
	gfx.DrawSurface(96, 128, holder, Colors::Magenta, false);
	holder = Surface(imageLib.SeekImage("Lucida_36")); //should draw an D
	gfx.DrawSurface(128, 128, holder, Colors::Magenta, false);
	*/
	//std::string t = "Test String";
	//expect this to be 384 X 32 with 12,288 pixels.
	//Surface tS = font.GetTextSurface(t, "Lucida", 32);
	//gfx.DrawSurface(32, 32, holder, Colors::Magenta, false);

	//Should draw a background with our 64x64 image
	for (int y = 0; y < gfx.ScreenHeight; y += 63)
	{
		for (int x = 0; x < gfx.ScreenWidth; x += 63)
		{
			gfx.DrawSurface(x, y, bgSurface, Colors::Magenta, false);
		}
	}
	gfx.DrawSurface(136.0f, 134.0f, testButton.GetSurface(), Colors::Magenta, false);
	if (showText)
	{
		gfx.DrawSurface(400.0f, 150.0f, testImgHideShow, Colors::Magenta, false);
	}

}
