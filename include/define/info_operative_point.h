#pragma once
#include "type_operative.h"
#include "xpack.h"

struct InfoPoint3D {
public:
    double x;
    double y;
    double z;
    double alpha;
    double beta;
    double gamma;

    int index;
    TypeNeedleRoutProperty property;
    XPACK(O(x, y, z, alpha, beta, gamma, index, property));
};

