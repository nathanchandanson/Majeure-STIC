#include"counter.hpp"
 
unsigned BaseCounter::getCounter() const 
{
  return counter;
}
 
unsigned BaseCounter::getMax() const 
{
  return max;
}

void BaseCounter::print()
{
  std::cout << "Compteur : " << counter << "/" << max << std::endl;
}
 
void BaseCounter::reset() 
{
  counter = 0;
}
 
void BaseCounter::set(unsigned value) 
{
  counter = (value <= max) ? value : counter;
}
 
void BaseCounter::setMax(unsigned value) 
{
   if(counter >= value)
     counter = 0;
     max = value;
}

void BaseCounter::decrement()
{
  if(counter >0){
    counter--;
  }else{
    counter = max;
  }
}

void BaseCounter::increment()
{
  counter ++;
  if(counter > max){
    counter = 0;
  }
}

void BiDiCounter::increment(unsigned value)
{
  if(counter+value <= max){
    counter += value;
  }else{
    counter = (counter+value) % max;
  }
}

void AdvCounter::increment()
{
  if(counter < max){
    counter++;
  }
}