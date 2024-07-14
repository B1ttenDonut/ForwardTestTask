#include "Stands.h"
/*
=====���� ��� ����������� ������� ��������� ���������=====
*/
int HeatTest(Engine engine) {
    int t = 0;
    bool brk = false;

    for (t = 0; t < engine.SimTime; t++)
        if (engine.Tarr[t] >= engine.Toh) {
            brk = true;
            break;
        }
    if (!brk) t = -1; //������� �� ���������� -> ��������� �� ���������� -> ��� ������� ���������

    return t;
};

/*
=====���� ��� ����������� ������������ �������� ���������=====
*/
PowerTestResults PowerTest(Engine engine) {
    int maxN_N = -1, maxN_V = -1;   //������������ ��������
    float N, M, V;                  //������� ��������

    for (int i = 0; i < engine.SimTime; i++) {
        M = engine.Marr[i];
        V = engine.Varr[i];

        N = M * V / 1000.0;

        if (N > maxN_N) {
            maxN_N = N;
            maxN_V = V;
        }
    }

    PowerTestResults res;        
    res.N = maxN_N;             
    res.V = maxN_V;             

    return res;
};