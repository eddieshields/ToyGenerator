#include "coefficient.h"

using namespace DalitzModel;

std::vector<Coefficient*> Coefficient::m_coefficients = std::vector<Coefficient*>();

Coordinates Coefficient::CoefficientCoordinates::Type = Coordinates::Rectangular;

Coefficient::CoefficientCoordinates Coefficient::CoordinatesSystem = Coefficient::CoefficientCoordinates();