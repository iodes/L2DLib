#pragma once
#include <windows.h>

struct Argument {
	LPCWSTR model;
	LPCWSTR* textures;
	LPCWSTR* motions;
};