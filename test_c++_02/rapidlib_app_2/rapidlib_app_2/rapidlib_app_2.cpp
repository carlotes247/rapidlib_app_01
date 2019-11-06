// rapidlib_app_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "regression.h"
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_ttf.h"

#pragma region Vars
	// Creating vector of training examples
std::vector<trainingExample> examples;
trainingExample auxExample;

// Creating regression instance
regression modelRegression;

// Defining inputs and outputs
std::vector<double> input = { 48 };
std::vector<double> output = { 130.81 };

// Mouse pos
int mousePosX;
int mousePosY;

// Rectangle to paint
SDL_Rect rect; // the rectangle

// event sdl to poll input states
SDL_Event eventSDL;

// The window to paint and modify
SDL_Window* mainWindow;

//Renderer required to paint window
SDL_Renderer* renderer;

// Font to draw text with
TTF_Font * font;

#pragma endregion

#pragma region Methods Declaration

void addTrainingExamples();

void trainRegressionModel();

void initAndCreateWindow();

void initRectangle(int height, int width);

void drawTextOnScreen(std::string textToDisplay);

void collectTrainingExamples(std::vector<double> inputs, std::vector<double> outputs);

void getTextInput();

void mainUpdateLoop();

void endProgram();

#pragma endregion


int main()
{
	// Assign inputs to training set
	addTrainingExamples();

	// Train model
	trainRegressionModel();

	// Creates window for graphics
	initAndCreateWindow();
	
	initRectangle(50, 50);
	
	// Calls update logic inside loop
	mainUpdateLoop();
	// Once update loop is finished...

	return 0;

}

#pragma region Methods Definition

void addTrainingExamples() {
	// Assign inputs to training set
	auxExample.input = input;
	auxExample.output = output;
	examples.push_back(auxExample);

	//More elements
	input = { 54 };
	output = { 185.00 };
	auxExample.input = input;
	auxExample.output = output;
	examples.push_back(auxExample);

	input = { 60 };
	output = { 261.63 };
	auxExample.input = input;
	auxExample.output = output;
	examples.push_back(auxExample);

	input = { 66 };
	output = { 369.994 };
	auxExample.input = input;
	auxExample.output = output;
	examples.push_back(auxExample);

	input = { 72 };
	output = { 523.25 };
	auxExample.input = input;
	auxExample.output = output;
	examples.push_back(auxExample);

	std::cout << "Training data: \n";
	for (int i = 0; i < examples.size(); i++)
	{
		std::cout << examples[i].input[0] << " " << examples[i].output[0] << "\n";

	}

}

void trainRegressionModel()
{
	std::cout << "Now training a regression... \n";

	bool isTrained = modelRegression.train(examples);
	//bool isTrained = false;

	if (isTrained)
	{
		std::cout << "Model trained successfully! \n";
	}
	else
	{
		std::cout << "Error when training model :( \n";
	}

}

void initAndCreateWindow()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	// Create sdl window
	mainWindow = SDL_CreateWindow
	("Rapidlib test", // window's title
		10, 25, // coordinates on the screen, in pixels, of the window's upper left corner
		640, 480, // window's length and height in pixels  
		SDL_WINDOW_OPENGL);

	// Creates renderer
	renderer = SDL_CreateRenderer(mainWindow, -1, 0);

	// Init font
	font = TTF_OpenFont("arial.ttf", 25);
}

void initRectangle(int height, int width)
{
	// Paint rectangle	
	rect.h = height;
	rect.w = width;

}

void drawTextOnScreen(std::string textToDisplay)
{	
	const char *text = textToDisplay.c_str();
	SDL_Color blackColor = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, blackColor); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect
	
	// We make sure that the width and height are not stretched
	SDL_QueryTexture(Message, NULL, NULL, &Message_rect.w, &Message_rect.h);

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	SDL_RenderPresent(renderer);
	
	//Don't forget too free your surface and texture
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
}

void collectTrainingExamples(std::vector<double> inputs, std::vector<double> outputs)
{

}

void getTextInput()
{
	//Set text color as black
	SDL_Color textColor = { 0, 0, 0, 0xFF };

	//The current input text.
	std::string inputText = "Some Text";
	
	//gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColor);
}

void mainUpdateLoop()
{
	bool exitCondition = false;
	while (!exitCondition)
	{

		if (SDL_PollEvent(&eventSDL) != 0)
		{
			switch (eventSDL.type) {
				/* Keyboard event */
				case SDL_KEYDOWN:
					switch (eventSDL.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						exitCondition = true;
					case SDLK_SPACE:
						std::cout << "space key pressed! " << std::endl;
					default:
						break;
					}

				/* SDL_QUIT event (window close) */
				case SDL_QUIT:
					//exitCondition = true;
					break;

				default:
					break;
			}

			// Get mouse event
			SDL_GetMouseState(&mousePosX, &mousePosY);

		}

		// Paint background
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer); // fill the scene with white

		// Colour for the rect (red)
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		rect.x = mousePosX;
		rect.y = mousePosY;
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer); // copy to screen

		//Get some user input
		int newNote = mousePosX;

		//Run the trained model on the user input
		std::vector<double> inputVec = { double(newNote) };
		double freqHz = modelRegression.run(inputVec)[0];


		//std::cout << "MIDI note " << newNote << " is " << freqHz << " Hertz" << std::endl;		

		drawTextOnScreen(std::to_string(freqHz));

		// Little delay to not run constantly
		SDL_Delay(10);
	}

}

void endProgram()
{
	TTF_CloseFont(font);
	SDL_DestroyWindow(mainWindow);
	TTF_Quit();
	SDL_Quit();

}

#pragma endregion


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
