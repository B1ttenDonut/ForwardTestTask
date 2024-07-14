#pragma once
#include "Engine.h"
class PowerTestResults {
public:
    float N;//макс мощность
    float V;//соотв. скорость коленвала
};

int HeatTest(Engine engine);
PowerTestResults PowerTest(Engine engine);