#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

float realdft(float t);
float ff(float t);
float dft(float t, float dt);

int main() {
	float rmse = 0;
	int N;
	float T = 20.0, dt = 0.010;
	float g, ig; //g´Â ¹ÌºÐ
	N = T / dt;

	ofstream differential("differential(dt=0.01, rmse = 0.).txt");
	
	
	for (int n = 0; n < N; n++) {
		ig = realdft(n * dt);
		g = dft(n * dt, dt);
		rmse += (g - ig) * (g - ig);
		cout << "cos(t) f'(" << n * dt << ") = " << ig << "      f'(" << n * dt << ") = " << g << endl;
		differential << n * dt << "    " << g << "    " << ig << endl;
	}
	cout << "    rmse    " << sqrt(rmse) << endl;

	differential.close();
	return 0;
}

float ff(float t) {
	return sin(t);
}

float realdft(float t) {

	return cos(t);
} //f(t) = sin(t), f'(t) = cos(t)



float dft(float t, float dt) {

	return (ff(t + dt) - ff(t)) / dt;
}