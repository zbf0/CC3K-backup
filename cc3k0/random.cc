#include "random.h"

void randomSort (std::vector<int>& v) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng{seed};
        std::shuffle( v.begin(), v.end(), rng );
}

std::vector<int>* randomIntGenerator_withoutReplacement (int lowerBound, int upperBound, int n = 1, bool sort = false) {
	// create vector of int
	std::vector<int> v;
	for (int i = lowerBound; i <= upperBound; ++i) {
		v.push_back(i);
	}
	// randomly change order
	randomSort(v);
	// store result in a vector
	std::vector<int>* result = new std::vector<int>;
	for (int i = 0; i < n && i < upperBound - lowerBound + 1; ++i) {
		result->push_back(v.at(i));
	}
	if (sort) {
		std::sort(result->begin(), result->end());
	}
	return result;
}

std::vector<int>* randomIntGenerator_withReplacement (int lowerBound, int upperBound, int n = 1, bool sort = false) {
	std::vector<int>* result = new std::vector<int>;
	std::vector<int>* v;
	if (lowerBound > upperBound) {
		return result;
	}
	for (int i = 0; i < n; ++i) {
		v = randomIntGenerator_withoutReplacement(lowerBound, upperBound);
		result->push_back(v->at(0));
		delete v;
	}
	if (sort) {
		std::sort(result->begin(), result->end());
	}
	return result;
}

std::vector<int>* randomIntGenerator (int lowerBound, int upperBound, int n, bool replacement, bool sort) {
	if (replacement) {
		return randomIntGenerator_withReplacement (lowerBound, upperBound, n, sort);
	} else {
		return randomIntGenerator_withoutReplacement (lowerBound, upperBound, n, sort);
	}
}
