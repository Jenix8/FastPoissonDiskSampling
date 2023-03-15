#include <glm/glm.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <random>
#include <climits>
#include <cmath>
using namespace glm;

constexpr int W = 512;
constexpr int H = 512;
constexpr int k = 30;
constexpr float PI = 3.1415926535;
constexpr float r = 16;
constexpr float cellSize = r / 1.41421356f;

std::vector<vec2> renderPos;
std::vector<vec2> renderActive;
std::vector<vec2> pos;
std::vector<vec2> active;
std::vector<std::vector<vec2>> grid(W / cellSize + 1, std::vector<vec2>(H / cellSize + 1, vec2(-1)));

std::vector<vec2>& getPos()
{
	return renderPos;
}

std::vector<vec2>& getActive()
{
	return renderActive;
}

inline void print2v(vec2 v)
{
	printf("(%.2f, %.2f)\n", v.x, v.y);
}

inline vec2 getCell(vec2 p)
{
	return vec2((int)(p.x / cellSize), (int)(p.y / cellSize));
}

inline int RNDi(int l = 0, int r = INT_MAX)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(l, r);

	return dist(gen);
}

inline float RNDf(float low = 0, float high = 1)
{
	return low + RNDi() * (high - low) / static_cast<float>(INT_MAX);
}

bool noSampleinR(vec2 c)
{
	vec2 cellN = getCell(c);
	for (int xx = -2; xx <= 2; xx++)
		for (int yy = -2; yy <= 2; yy++)
		{
			if (abs(xx) == 2 && abs(yy) == 2) continue;

			int x = cellN.x + xx;
			int y = cellN.y + yy;

			if (x < 0 || x >= grid.size()) continue;
			if (y < 0 || y >= grid.size()) continue;

			if (grid[x][y] != vec2(-1))
				if (glm::length(grid[x][y] - c) < r)
					return false;
		}

	return true;
}

vec2 fitting(vec2& p)
{
	vec2 r;
	r[0] = 2 * p[0] / W - 1;
	r[1] = 2 * p[1] / H - 1;
    return r;
}

void init()
{
	// take a first pixel randomly
	float rx = RNDi(0, grid.size()-1) * cellSize + RNDf(0, cellSize);
	float ry = RNDi(0, grid.size()-1) * cellSize + RNDf(0, cellSize);
	vec2 initialPoint(rx, ry); 
	vec2 cellN = getCell(initialPoint);

	active.push_back(initialPoint);
	pos.push_back(initialPoint);
	grid[cellN.x][cellN.y] = initialPoint;
	renderPos.push_back(fitting(initialPoint));	
}

void run()
{
	int pointNum = 0;
	while (!active.empty())
	{
		int rIdx = RNDi(0, active.size() - 1);
		vec2 center = active[rIdx];
		vec2 centerCell = getCell(center);
	
		int count = 0;
		for (int iter = 0; iter < k; iter++)
		{
			if (count == 8) break;

			float radius = RNDf(r, 2 * r);
			float angle = RNDf(0, 2 * PI);
	
			float px = center.x + radius * cos(angle);
			float py = center.y + radius * sin(angle);
	
			if (px < 0 || px > W) continue;
			if (py < 0 || py > H) continue;

			vec2 cand(px, py);
			vec2 candCell = getCell(cand);

			if (noSampleinR(cand)) // NeighborSearch
			{
				count++;
				pointNum++;
				active.push_back(cand);
				pos.push_back(cand);
				grid[candCell.x][candCell.y] = cand;
				renderPos.push_back(fitting(cand));
			}
		}

		active.erase(active.begin() + rIdx);
	}
	printf("Number of points: %d\n", pointNum);

	return;
}