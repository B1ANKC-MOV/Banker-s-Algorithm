#include "��ͷ.h"
#include <iostream>

using namespace std;

//��ʼ������

int main() {
	bankAlgorithm demo = bankAlgorithm();
	demo.disp();

	while (true) {
		demo.sendRequest();
		demo.disp();
	}


	return 0;
}
