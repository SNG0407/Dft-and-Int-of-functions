#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
const float Pi = 3.141592;
float integral(float t, float dt, float (*fx)(float));
float dft(float t, float dt, float (*fx)(float));

float sint(float t);
float sinDft(float t);
float sinInt(float t);

float cost(float t);
float cosDft(float t);

float expt(float t);
float expDft(float t);


float function1(float t);
float function1Dft(float t);
float function1Int(float t);

float function2(float t);
float function2Dft(float t);
float function2Int(float t);

int main() {
	float rmse = 0;
	int N;
	float T = 20.0, dt = 0.1;
	float FF, iFF; //F는 적분
	float g, ig; //g는 미분
	N = T / dt;

	ofstream Differential("function1-dif(T=20, dt=0.1).txt");
	

	//미분 작성
	for (int n = 0; n < N; n++) {
		ig = function1Dft(n * dt);
		g = dft(n * dt, dt, function1);
		rmse += (g - ig) * (g - ig);
		//cout << "ext_f'(" << n * dt << ") = " << ig << "      f'(" << n * dt << ") = " << g << endl;
		Differential << n * dt << "    " << ig << "    " << g << endl;
	}
	Differential.close();
	cout << "  dif  rmse    " << sqrt(rmse) << endl;
	rmse = 0; //초기화

	//적분 작성
	T = 20.0, dt = 0.01;
	N = T / dt;
	ofstream Integral("function1-int(T=20, dt=0.01.txt");
	for (int n = 0; n < N; n++) {
		FF = integral(n * dt, dt, function1);
		iFF = function1Int(n * dt);
		rmse += (FF - iFF) * (FF - iFF);
		cout << "ext_F(" << n * dt << ") = " << iFF << "      F(" << n * dt << ") = " << FF << endl;
		Integral << n * dt << "    " << iFF << "    " << FF << endl;

	}
	cout << " int   rmse    " << sqrt(rmse) << endl;

	Integral.close();
	return 0;
}
float dft(float t, float dt, float (*fx)(float)) {

	return ((*fx)(t + dt) - (*fx)(t)) / dt;
} //미분 함수

float integral(float t, float dt, float (*fx)(float)) {
	float FF = 0.0;
	for (float tau = 0.0; tau < t; tau += dt) {
		FF += (*fx)(tau) * dt;
	}
	return FF;
} //적분 함수

float sint(float t) { return sin(t);}
float sinDft(float t) { return cos(t); } //f(t) = sin(t), f'(t) = cos(t)
float sinInt(float t) { return 1.0 -cos(t); }

float cost(float t) { return cos(t); }
float cosDft(float t) { return -sin(t); } 

float expt(float t) { return exp(t); }
float expDft(float t) { return exp(t); }


float function1(float t) { return 3*sin(2*Pi*t)*cos(200*Pi*t); }
float function1Dft(float t){ return 6*Pi*(cos(200*Pi*t)*cos(2 * Pi * t)-100*sin(200 * Pi * t)*sin(2 * Pi * t)); }
float function1Int(float t){ return 3/200/Pi*sin(2*Pi*t)* sin(200 * Pi * t) +3/10000*cos(200*Pi*t)* cos(2 * Pi * t); }

float function2(float t){
	return 3 * exp((-2) * t) * sin(2 * Pi * t);
}
float function2Dft(float t){
	return 6 * exp((-2) * t) * (Pi * cos(2 * Pi * t) - sin(2 * Pi * t));
}
float function2Int(float t){ 
	return (-3 / 2) / (1 + Pi * Pi) * (exp((-2) * t) * ((sin(2 * Pi * t) + Pi*cos(2 * Pi * t))-Pi)) ;
}//F(t)-F(0)