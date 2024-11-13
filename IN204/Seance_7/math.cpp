#include "math.hpp"

double divide(double a, double b) noexcept(false)   // On prévient que la fonction peut renvoyer une exception
{
//   if(b == 0) throw division_by_zero(); // Test si b est nul ou pas
  if(b == 0) throw extended_division_by_zero(); // Test si b est nul ou pas

  return a/b;
}