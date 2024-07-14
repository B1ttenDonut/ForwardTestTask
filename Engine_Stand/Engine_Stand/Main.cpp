// Engine_Stand.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "Engine.h"
#include "Stands.h"
using json = nlohmann::json;


int main()
{
    setlocale(LC_ALL, "Russian");

    std::ifstream f("EngineData.json");     //импорт данных из JSON
    json data = json::parse(f);
    Engine engine(data);

    int envTemp;
    std::cout << "Пожалуйста введите температуру окружающей среды (градусы цельсия): " << std::endl;
    std::cin >> envTemp;                                                            
    engine.Simulation(envTemp);

    int heatRes = HeatTest(engine);                                           
    PowerTestResults powerRes = PowerTest(engine);

    std::cout << "Время работы двигателя до перегрева (-1 означает что двигатель не перегрелся): " << heatRes << " секунд." << std::endl;
    std::cout << "Максимальная мощность двигателя: " << powerRes.N << "кВт,\nПри скорости вращения коленвала: " << powerRes.V << " радиан/секунду." << std::endl;

    return 0;
}
