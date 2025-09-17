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

void Menu(Pipe t,CS k) {
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
			cin >> t.repair;
			break;
		case 2:
			cout << "Insert CS name: ";
			cin >> k.name;
			cout << "Insert the number of workshops: ";
			cin >> k.workshop;
			cout << "Insert the number of workshops in operation: ";
			cin >> k.w_work;
			cout << "Insert CS class: ";
			cin >> k.class_cs;
			break;
		case 3:
			cout << "Pipe name: " << t.name << endl;
			cout << "Pipe lenght: " << t.lenght << endl;
			cout << "Pipe diametr: " << t.diametr << endl;
			cout << "Pipe condition: " << t.repair << endl;
			cout << "CS name: " << k.name << endl;
			cout << "Number of workshops: " << k.workshop << endl;
			cout << "Number of workshops in operation: " << k.w_work << endl;
			cout << "CS class: " << k.class_cs << endl;
			break;


		}
	}
}

int main()
{
	Pipe truba;
	CS cstation;
	Menu(truba,cstation);
}