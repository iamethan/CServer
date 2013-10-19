#include <iostream>
using namespace std;

#include "Server.h"

int main()
{
	Server svr;

	svr.Initialize();

	svr.Run();

	svr.Finalize();

	return 0;
}