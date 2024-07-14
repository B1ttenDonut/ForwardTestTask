#include "Stands.h"
/*
=====“ест дл€ определени€ времени перегрева двигател€=====
*/
int HeatTest(Engine engine) {
    int t = 0;
    bool brk = false;

    for (t = 0; t < engine.SimTime; t++)
        if (engine.Tarr[t] >= engine.Toh) {
            brk = true;
            break;
        }
    if (!brk) t = -1; //функци€ не прервалась -> двигатель не перегрелс€ -> нет времени перегрева

    return t;
};

/*
=====“ест дл€ определени€ максимальной мощности двигател€=====
*/
PowerTestResults PowerTest(Engine engine) {
    int maxN_N = -1, maxN_V = -1;   //максимальные значени€
    float N, M, V;                  //текущие значени€

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