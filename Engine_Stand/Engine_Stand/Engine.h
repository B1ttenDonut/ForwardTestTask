#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json;

class Engine {
private:
	int I;						//Момент инерции двигателя
	std::vector<int> M;			//Крутящий момент двигателя
	std::vector<int> V;			//Скорость врещения коленвала
	float Hm;					//Коэффициент зависимости скорости нагрева от крутящего момента
	float Hv;					//Коэффициент зависимости скорости нагрева от скорости вращения коленвала
	float C;					//Коэффициент зависимости скорости охлаждения от температуры двигателя и окружающей среды
public:
	int Toh;					//Температура перегрева
	std::vector<float> Tarr;	//
	std::vector<float> Varr;	//Значения температуры, скорости вращения коленвала  м крутящего момента времени в каждую секунду симуляции
	std::vector<float> Marr;	//
	int SimTime = 0;			//общая длина симуляции

	Engine(json data) {			//конструктор класса, заполняемый данными из JSONа
		I = data["I"];
		for (auto& el : data["M"].items()) {
			M.push_back(el.value());
		}
		for (auto& el : data["V"].items()) {
			V.push_back(el.value());
		}
		Toh = data["Toh"];
		Hm = data["Hm"];
		Hv = data["Hv"];
		C = data["C"];
	};
	int Simulation(int envTemp) {//Симуляция двигателя
		float currentV = V[0];
		float currentM = M[0];
		float currentTemp = envTemp;

		float MCoef = (float)(M[1] - M[0]) / (float)(V[1] - V[0]);
		float a = (float)M[0] / (float)Toh;

		int time = 0;

		float heatingV = 0;
		float coolingV = 0;

		int c = 0;
		while (currentM > 0) {
			if (currentV >= V[c + 1]) {
				c++;
				a = (float)M[c] / (float)Toh;
				MCoef = (float)(M[c + 1] - M[c]) / (float)(V[c + 1] - V[c]);
			}

			currentV += a;
			currentM = M[c] + (currentV - V[c]) * MCoef;  //поскольку функция задана кусочно мы "сбрасываем" координаты до нулевых для этой точки

			heatingV = currentM * Hm + currentV * currentV * Hv;
			coolingV = C * ((float)envTemp - currentTemp);
			currentTemp += heatingV + coolingV;

			time++;

			Tarr.push_back(currentTemp);
			Varr.push_back(currentV);
			Marr.push_back(currentM);
		}
		SimTime = time;
		return time;
	}

};

