#include "标头.h"
#include <iostream>

using namespace std;

//初始化函数

int main() {
	bankAlgorithm demo = bankAlgorithm();
	demo.disp();

	while (true) {
		demo.sendRequest();
		demo.disp();
	}


	return 0;
}
