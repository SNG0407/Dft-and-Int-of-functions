// 7wk test and practice.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
using namespace std;

float factorial(float);
int factorial(int);
double factorial(double);
int writedata(int, short*, int);
int main()
{
	/*for(int i =0; i<10; i++){
		cout << "      "<<i<<"! = " << factorial((float)i) << endl;
	}*/

	short data[500];
	int N = 5;
	writedata(N,data, 0); //5개 씀
	cout << " \n" << endl;
	/*for (int i = 0; i < N;i++) {
		cout << data[i] << endl;
	}*/
	writedata(N + 3, data + N, N); //8개 씀 그 다음은 N + N+3
	cout << " \n" << endl;
	writedata(N, data + N+ N+5, N + N + 3);

	for (int i = 0; i < 40; i++) {
		cout << "data[" << i<< "] = " << data[i] << endl;
	}

	return 0;
}

float factorial(float n) {
	if (n < 2) return 1;
	else return n * factorial(n - 1);
} //34!까지
int factorial(int n) {
	if (n < 2) return 1;
	else return n * factorial(n - 1);
} //14!까지
double factorial(double n) {
	if (n < 2) return 1;
	else return n * factorial(n - 1);
} //170!까지

int writedata(int N, short* pArray, int iNumber) {
	for (int i = 0; i < N; i++) {
		pArray[i] = i + 10;
		cout <<"data["<<i+ iNumber <<"] = "<< pArray[i] << endl;
	}
	return N;
}