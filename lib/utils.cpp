#include "../include/utils.h"

#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dist(0.0, 1.0);

double random() { return dist(gen); }

int opposing_turn(int turn) { return turn == 1 ? 2 : 1; }