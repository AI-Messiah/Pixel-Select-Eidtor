#include "FillPat.h"

FillPat::FillPat()
{
}

FillPat::~FillPat()
{
	delete data;
}

void FillPat::init(int w, int h)
{
	width = w;
	height = h;
	data = new bool[w * h];
	for (int i = 0; i < w * h; i++) data[i] = true;
}

void FillPat::setBounds(std::vector<glm::ivec2> ibounds)
{
	bounds = ibounds;
}

void FillPat::seed(int x, int y)
{
	fillLocs.push_back(glm::ivec2(x, y));
	bool canset;
	while (fillLocs.size() > 0) {
		int fx = fillLocs.at(0).x;
		int fy = fillLocs.at(0).y;
		canset = data[fx + fy * width];
		for (int i = 0; i < bounds.size(); i++) {
			int bx = bounds.at(i).x;
			int by = bounds.at(i).y;
			if (fx == bx && fy == by) canset = false;
		}
		fillLocs.erase(fillLocs.begin());
		if (canset) {
			data[fx + fy * width] = false;
			push(fx - 1, fy);
			push(fx + 1, fy);
			push(fx, fy - 1);
			push(fx, fy + 1);
		}
	}
	for (int i = 0; i < bounds.size(); i++) {
		int bx = bounds.at(i).x;
		int by = bounds.at(i).y;
		data[bx + by * width] = false;
	}
}

void FillPat::push(int x, int y)
{
	bool insert = true;
	if (x >= 0 && x < width && y >= 0 && y < height) {
		for (int i = 0; i < fillLocs.size(); i++) if (fillLocs.at(i) == glm::ivec2(x, y)) insert = false;
		if (insert) fillLocs.push_back(glm::ivec2(x, y));
	}
}

bool FillPat::sample(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height) {
		return !data[x + y * width];
	}
	return false;
}
