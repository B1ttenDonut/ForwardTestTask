#pragma once
#include "Engine.h"
class PowerTestResults {
public:
    float N;//���� ��������
    float V;//�����. �������� ���������
};

int HeatTest(Engine engine);
PowerTestResults PowerTest(Engine engine);