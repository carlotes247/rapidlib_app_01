// rapidlib_app_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "regression.h"
#define SDL_MAIN_HANDLED
#include "SDL.h"

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

#pragma endregion

#pragma region Methods Declaration

void addTrainingExamples();

void trainRegressionModel();

void initAndCreateWindow();

void initRectangle(int height, int width);

void mainUpdateLoop();

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

	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
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

	// Create sdl window
	mainWindow = SDL_CreateWindow
	("Rapidlib test", // window's title
		10, 25, // coordinates on the screen, in pixels, of the window's upper left corner
		640, 480, // window's length and height in pixels  
		SDL_WINDOW_OPENGL);

	renderer = SDL_CreateRenderer(mainWindow, -1, 0);

}

void initRectangle(int height, int width)
{
	// Paint rectangle	
	rect.h = height;
	rect.w = width;

}

void mainUpdateLoop()
{
	bool exitCondition = false;
	while (!exitCondition)
	{

		if (SDL_PollEvent(&eventSDL) != 0)
		{
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

		std::cout << "MIDI note " << newNote << " is " << freqHz << " Hertz" << std::endl;

	}

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
