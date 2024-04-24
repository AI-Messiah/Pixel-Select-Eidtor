#pragma once
#include "glm/glm.hpp"
#include <vector>

class FillPat
{
public:
	FillPat();
	~FillPat();
	void init(int w, int h);
	void setBounds(std::vector<glm::ivec2> ibounds);
	void seed(int x, int y);
	
	bool sample(int x, int y);
private:
	void push(int x, int y);
	int width, height;
	bool* data;
	std::vector<glm::ivec2> bounds;
	std::vector<glm::ivec2> fillLocs;
};

