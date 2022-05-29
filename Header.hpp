#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define deb if(0)
#define save_deb if(0)
#define win_deb if(0)
#define mm_deb if(0)

#define FOR(i,a) for(int i = 0; i < (a); ++i)
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define EMPTY 0
#define NONE 0 
#define WHITE 1
#define BLACK 2

struct Field;
struct Board;
struct Node;

#include "Field.hpp"
#include "Board.hpp"
#include "Interface.hpp"
#include "Solver.hpp"
#include "Utils.hpp"
#include "Node.hpp"
#include "MinMax.hpp"