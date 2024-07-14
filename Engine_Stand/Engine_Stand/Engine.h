#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
using json = nlohmann::json;

class Engine {
private:
	int I;						//������ ������� ���������
	std::vector<int> M;			//�������� ������ ���������
	std::vector<int> V;			//�������� �������� ���������
	float Hm;					//����������� ����������� �������� ������� �� ��������� �������
	float Hv;					//����������� ����������� �������� ������� �� �������� �������� ���������
	float C;					//����������� ����������� �������� ���������� �� ����������� ��������� � ���������� �����
public:
	int Toh;					//����������� ���������
	std::vector<float> Tarr;	//
	std::vector<float> Varr;	//�������� �����������, �������� �������� ���������  � ��������� ������� ������� � ������ ������� ���������
	std::vector<float> Marr;	//
	int SimTime = 0;			//����� ����� ���������

	Engine(json data) {			//����������� ������, ����������� ������� �� JSON�
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
	int Simulation(int envTemp) {//��������� ���������
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
			currentM = M[c] + (currentV - V[c]) * MCoef;  //��������� ������� ������ ������� �� "����������" ���������� �� ������� ��� ���� �����

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

