#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	int paso = 1;
	cout<<"paso-- :";
	if (paso--==1)
	{
		cout<<"primero se decremento\n";
	}else{
		cout<<"primero se evaluo\n";
	}

	cout<<"--paso :";
	if (--paso==1)
	{
		cout<<"primero se decremento\n";
	}else{
		cout<<"primero se evaluo\n";
	}
}