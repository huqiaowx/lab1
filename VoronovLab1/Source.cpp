#include <iostream>
#include <string>

using namespace std;

struct Pipe {
	string name;
	float lenght;
	int diametr;
	bool repair;
};

struct CS {
	string name;
	int workshop;
	int w_work;
	string class_cs;
};

void Menu(Pipe t) {
	while (1)
	{
		cout << "Choose an action\n1. Add pipe\n2. Add compressor station\n3. View all objects\n4. Edit pipe\n5. Edit compressor station\n6. Save\n7. Load\n0. Exit\n";
		int option;
		cin >> option;
		switch (option)
		{
		case 1:
			cout << "Insert pipe name: ";
			cin >> t.name;
			cout << "Insert pipe lenght: ";
			cin >> t.lenght;
			cout << "Insert pipe diametr: ";
			cin >> t.diametr;
			cout << "Pipe condition: ";
			break;
		case 2:
			cout << "Insert CS name: ";
			cin >> t.name;
			cout << "Insert the number of workshops: ";
			cin >> t.lenght;
			cout << "Insert the number of workshops in operation: ";
			cin >> t.lenght;
			cout << "Insert CS class: ";
			break;
		case 3:
			cout << "Pipe name: " << t.name;
			break;

		}
	}
}

int main()
{
	Pipe truba;
	truba.name = "Uchastok 1";
	cout << truba.name;
	Menu(truba);
}