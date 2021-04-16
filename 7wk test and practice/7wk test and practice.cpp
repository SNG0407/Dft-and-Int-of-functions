#include <iostream>
#include <fstream>
#include <cmath>  
#include <string>

using namespace std;
const float Pi = 3.141592;

float functions(float t, int funNum);
float difOfFunctions(float t, int funNum);
float intOfFunctions(float t, int funNum);

float integral(float t, float dt, int funNum);
float dft(float t, float dt, int funNum);

int printFunction(float T, float dt, float N, string a, int num);
enum functionName
{
	FUNCTION_SIN = 1,
	FUNCTION_COS,
	FUNCTION_1,
	FUNCTION_2,
	EXIT
};
enum WhatToDo
{
	STANDARD,
	DIFFERENTIAL,
	INTEGRAL
};

int main() {


	string a;
	int N;


	while (true) {
		system("cls");
		cout << "*************************** 함수 그래프 그리기 ***************************" << endl;
		cout << "1. sin" << endl;
		cout << "2. cos" << endl;
		cout << "3. function_1" << endl;
		cout << "4. function_2" << endl;
		cout << "5. 종료" << endl;

		cout << "원하는 함수를 선택하세요 : " << endl;
		int iWhatFunction;
		cin >> iWhatFunction;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		if (iWhatFunction == EXIT) { break; }

		/*int TNum;  //n개의 주기
		int dtNum; // 주기당 n번 sampling
		cout << "몇개의 주기를 그리고 싶습니까? " << endl;
		cin >> TNum;
		cout << "한 주기에 몇개의 샘플을 그리고 싶습니까? " << endl;
		cin >> dtNum;
		float T = (float)TNum * 2 * Pi;
		float dt = 1.*2*Pi / (float)dtNum / (float)TNum; */
		float T, dt;
		cout << "float T를 입력하십시오 " << endl;
		cin >> T;
		cout << "float dt를 입력하십시오 " << endl;
		cin >> dt;
		N = T / dt;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		switch (iWhatFunction)
		{
		case FUNCTION_SIN:
			a = "sin";
			printFunction(T, dt, N, a, iWhatFunction);

			break;
		case FUNCTION_COS:
			a = "cos";
			printFunction(T, dt, N, a, iWhatFunction);
			break;
		case FUNCTION_1:
			a = "function_1";
			printFunction(T, dt, N, a, iWhatFunction);

			break;
		case FUNCTION_2:
			a = "function_2";
			printFunction(T, dt, N, a, iWhatFunction);

			break;
		default:
			break;
		}
		system("pause");
	}


	return 0;
}
float dft(float t, float dt, int funNum) {
	float result = (functions(t + dt, funNum) - functions(t, funNum)) / dt;
	return result;
} //미분 함수

float integral(float t, float dt, int funNum) {
	float FF = 0.0;
	for (float tau = 0.0; tau < t; tau += dt) {
		FF += functions(tau, funNum) * dt;
	}
	return FF;
} //적분 함수

float functions(float t, int funNum) {
	float function[4];
	function[0] = sin(t);
	function[1] = cos(t);
	function[2] = 3 * sin(2 * Pi * t) * cos(200 * Pi * t);
	function[3] = 3 * exp((-2) * t) * sin(2 * Pi * t);
	float result = function[funNum];
	return result;
}

float difOfFunctions(float t, int funNum) { //Differential
	float function[4];
	function[0] = cos(t);
	function[1] = -sin(t);
	function[2] = 6 * Pi * (cos(200 * Pi * t) * cos(2 * Pi * t) - 100 * sin(200 * Pi * t) * sin(2 * Pi * t));
	function[3] = 6 * exp((-2) * t) * (Pi * cos(2 * Pi * t) - sin(2 * Pi * t));
	float result = function[funNum];
	return result;
}
float intOfFunctions(float t, int funNum) { //t== n*dt
	float function[4];
	function[0] = -cos(t);
	function[1] = sin(t);
	function[2] = 3 / 200 / Pi * sin(2 * Pi * t) * sin(200 * Pi * t) + 3 / 10000 * cos(200 * Pi * t) * cos(2 * Pi * t);
	function[3] = (-3 / 2) / (1 + Pi * Pi) * (exp((-2) * t) * ((sin(2 * Pi * t) + Pi * cos(2 * Pi * t)) - Pi));
	float result = function[funNum];
	return result;
}


int printFunction(float T, float dt, float N, string a, int iWhatFunction) {
	ofstream Differential;
	ofstream Integral;
	float rmse = 0;
	float rmse_dB = 0;


	float result; // 기존 standard 함수 값
	float FF, iFF; //F는 적분
	float g, ig; //g는 미분

	int option;

	string  b, c, d;
	string resultDif, resultInt;

	resultDif = (a + "-dif(T=" + to_string(T) + ", dt=" + to_string(dt) + ").txt");

	Differential.open(resultDif);
	cout << resultDif << endl;
	for (int n = 0.0; n < N; n++) {
		result = functions(n * dt, iWhatFunction - 1);
		ig = difOfFunctions(n * dt, iWhatFunction - 1);   //function1Dft(n * dt); //arr[n][1]
		g = dft(n * dt, dt, iWhatFunction - 1); //arr[n][2]
		rmse += (g - ig) * (g - ig);
		rmse_dB = 20 * log10(sqrt(rmse));
		cout << "ext_f'(" << n * dt << ") = " << ig << "      f'(" << n * dt << ") = " << g << endl;
		Differential << n * dt << "    " << ig << "    " << g << endl;
	}
	cout << "미분의 rmse : " << rmse << endl;
	cout << "미분의 rmse(dB) : " << rmse_dB << endl;
	Differential.close();
	rmse = 0;
	rmse_dB = 0;

	//적분 구하기
	resultInt = (a + "-int(T=" + to_string(T) + ", dt=" + to_string(dt) + ").txt");
	Integral.open(resultInt);
	cout << resultInt << endl;
	for (int n = 0; n < N; n++) {
		result = functions(n * dt, iWhatFunction - 1); // 원 함수
		iFF = intOfFunctions(n * dt, iWhatFunction - 1); //프로그밍 값
		FF = integral(n * dt, dt, iWhatFunction - 1); //내가 손으로 푼
		rmse += (FF - iFF) * (FF - iFF);
		rmse_dB = 20 * log10(sqrt(rmse));
		cout << "ext_F(" << n * dt << ") = " << FF << "      F(" << n * dt << ") = " << iFF << endl;
		Integral << n * dt << "    " << FF << "    " << iFF << endl;
	}
	cout << "적분의 rmse : " << rmse << endl;
	cout << "적분의 rmse(dB) : " << rmse_dB << endl;
	Integral.close();

	return 2;
}