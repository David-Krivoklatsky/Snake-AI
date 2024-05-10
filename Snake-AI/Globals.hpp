#pragma once

//#include <vector>

constexpr int WINDOW_SIZE = 800;
constexpr int PIXEL_SIZE = 20;
constexpr int BLOCK_SIZE = WINDOW_SIZE / PIXEL_SIZE;
constexpr int FPS_LIMIT = 60;
constexpr float SNAKE_SPEED = 7.f;

enum Direction {
	Up = 0,
	Left = 1,
	Down = 2,
	Right = 3,

	Unknown = 4
};

//extern bool isError = false;
//extern std::vector<std::string> Errors;
