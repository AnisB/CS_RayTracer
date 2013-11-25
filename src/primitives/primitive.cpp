#include "primitive.h"

Primitive::Primitive()
{}

Primitive::~Primitive()
{}

void Primitive::AddCoeff(double coeff)
{
    m_coeffs.push_back(coeff);
}

std::vector<double> Primitive::getCoeffList()
{
    return m_coeffs;
}
