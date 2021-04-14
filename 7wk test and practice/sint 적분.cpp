#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
float ff(float t);
float intF(float t);
float F(float t, float );

int main() {
	ofstream integral("integral(T=100, dt=0.01).txt");
	float rmse = 0;
	int N;
	float T = 100.0, dt = 0.01, FF, iFF;
	
	N = T / dt;
	for (int n = 0; n < N; n++) {
		FF = F(n * dt, dt);
		iFF = intF(n * dt);
		rmse += (FF - iFF) * (FF - iFF);
		integral << n * dt << "    " << FF << "    " << iFF << endl;
		
	}
	integral.close();
	cout << "    rmse    " << sqrt(rmse) << endl;

	return 0;
}

float ff(float t) {

	return sin(t);
}

float intF(float t) {

	return 1.0 - cos(t);
} //F(t)-F(0)

float F(float t, float dt) {
	float FF = 0.0;
	for (float tau = 0.0; tau < t; tau += dt) {
		FF += ff(tau) * dt;
	}
	return FF;
}