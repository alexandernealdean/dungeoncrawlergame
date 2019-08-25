#include <iostream>
#include "IFDParser.h"

using namespace std;

int main(){
	IFDParser parser;
	parser.tokenIt();
	parser.printStrings();

	return 0;
}
