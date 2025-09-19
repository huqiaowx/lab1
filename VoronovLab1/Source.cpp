#include <iostream>
#include <string>

using namespace std;

template<typename T>
bool inputNumber(T& variable, const string& prompt, bool positiveOnly = false) {
	while (true) {
		cout << prompt;
		if (cin >> variable) {
			if (positiveOnly && variable <= 0) {
				cout << "Error, value must be positive" << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			return true;
		}
		else {
			cout << "Invalid input, please enter a valid number." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

bool inputBool(bool& variable, const string& prompt) {
	int temp;
	while (true) {
		cout << prompt;
		if (cin >> temp && (temp == 0 || temp == 1)) {
			variable = (temp == 1);
			return false;
		}
		else {
			cout << "Invalid input, please enter 0 or 1." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
	}
}


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
	float class_cs;
};

void Menu(Pipe& t,CS& k) {
	while (1)
	{
		cout << "Choose an action\n1. Add pipe\n2. Add compressor station\n3. View all objects\n4. Edit pipe\n5. Edit compressor station\n6. Save\n7. Load\n0. Exit\n";
		int option;
		cin >> option;
		switch (option)
		{
		case 1:
			cout << "Insert pipe name: ";
			cin.ignore();
			getline(cin, t.name);
			inputNumber(t.lenght, "Insert pipe lenght: ", true);
			inputNumber(t.diametr, "Insert pipe diametr: ", true);
			inputBool(t.repair, "Pipe condition(0 or 1): ");
			break;
		case 2:
			cout << "Insert CS name: ";
			cin.ignore();
			getline(cin, k.name);
			inputNumber(k.workshop, "Insert the number of workshops: ", true);
			inputNumber(k.w_work, "Insert the number of workshops in operation: ", true);
			inputNumber(k.class_cs, "Insert CS class: ", true);
			break;
		case 3:
			cout << "Pipe name: " << t.name << endl;
			cout << "Pipe lenght: " << t.lenght << endl;
			cout << "Pipe diametr: " << t.diametr << endl;
			cout << "Pipe condition: " << t.repair << endl;
			cout << "CS name: " << k.name << endl;
			cout << "Number of workshops: " << k.workshop << endl;
			cout << "Number of workshops in operation: " << k.w_work << endl;
			cout << "CS class: " << k.class_cs << endl << endl;
			break;
		

		default:
			cout << "...";

		}
	}
}

int main()
{
	Pipe truba;
	CS cstation;
	Menu(truba,cstation);
}