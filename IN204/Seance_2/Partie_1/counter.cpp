#include "counter.hpp"

unsigned MyCounter::getCounter() const
{
  return counter;
}

unsigned MyCounter::getMax() const
{
  return max;
}

void MyCounter::increment()
{
  counter++;
  if (counter > max)
    counter = 0;
}

void MyCounter::reset()
{
  counter = 0;
}

void MyCounter::set(unsigned value)
{
  counter = (value <= max) ? value : counter;
}

void MyCounter::setMax(unsigned value)
{
  if (counter >= value)
    counter = 0;
  max = value;
}

void MyBiDiCounter::decrement()
{
  if (counter > 0)
  {
    counter--;
  }
  else
  {
    counter = max;
  }
}

void MyBiDiCounter::print()
{
  std::cout << "Compteur : " << counter << "/" << max << std::endl;
}