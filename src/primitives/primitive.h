#ifndef PRIMITIVE
#define PRIMITIVE

#include <vector>

class Primitive
{
 public:
    Primitive();
    ~Primitive();
    std::vector<double> getCoeffList();
    void AddCoeff(double coeff);
 private:
    std::vector<double> m_coeffs;    
};

#endif //PRIMITIVE
