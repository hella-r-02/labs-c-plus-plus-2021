#ifndef TASKS_HPP
#define TASKS_HPP

#include <functional>

void taskOne(std::function<bool(const int&, const int&)> cmp);
void taskTwo(const char *fileName);
void taskThree();
void taskFour(std::function<bool(const double&, const double&)> cmp,  size_t size);
void fillRandom(double *array, int size);
#endif
