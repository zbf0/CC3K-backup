#include "coorddiff.h"

std::vector<int> getCoordDiff(int direction) {
	std::vector<int> v = {0, 0};
	if (direction == 1) v = {-1, 1};
	if (direction == 2) v = {0, 1};
	if (direction == 3) v = {1, 1};
	if (direction == 4) v = {-1, 0};
	if (direction == 5) v = {0, 0};
	if (direction == 6) v = {1, 0};
	if (direction == 7) v = {-1, -1};
	if (direction == 8) v = {0, -1};
	if (direction == 9) v = {1, -1};
	return v;
}

