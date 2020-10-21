#include "rng.h"

// variables for rng
std::random_device rd;
std::mt19937 kRng(rd());
