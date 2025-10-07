#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "Pipe.h"

using namespace std;

template<typename T>
bool inputNumber(T& variable, const string& prompt, bool positiveOnly = false) {
	while (true) {
		cout << prompt;
		if (cin >> variable) {
            if (cin.peek() != '\n') {
                cout << "Error, please enter only numbers without extra characters." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
			if (positiveOnly && variable <= 0) {
				cout << "Error, value must be positive" << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            if (cin.peek() != '\n') {
                cout << "Error, please enter only 0 or 1 without extra characters." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
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
        string input;
        getline(cin, input); 

        if (input.empty()) {
            continue;
        }

        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            cout << "Error, please enter only numbers (0-7)." << endl;
            continue;
        }

        int option = stoi(input);
		switch (option)
		{
        case 1: {
            cout << "Insert pipe name: ";
            string tempName;
            getline(cin, tempName);
            while (tempName.empty()) {
                cout << "Error, insert pipe name: ";
                getline(cin, tempName);
            }
            t.setName(tempName);

            float tempLenght;
            inputNumber(tempLenght, "Insert pipe lenght: ", true);
            t.setLength(tempLenght);

            int tempDiametr;
            inputNumber(tempDiametr, "Insert pipe diametr: ", true);
            t.setDiametr(tempDiametr);

            bool tempRepair;
            inputBool(tempRepair, "Pipe condition(0 or 1): ");
            t.setRepair(tempRepair);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

		case 2:
			cout << "Insert CS name: ";
			getline(cin, k.name);
            while (k.name.empty()) {
                cout << "Error, insert cs name: ";
                getline(cin, k.name);
            }
			inputNumber(k.workshop, "Insert the number of workshops: ", true);
			while (true) {
				inputNumber(k.w_work, "Insert the number of workshops in operation: ");
				if (k.w_work < 0) {
					cout << "Error, number cannot be negative. Try again." << endl;
					continue;
				}
				if (k.w_work >= 0 && k.w_work <= k.workshop) {
					break;
				}
				if (k.w_work > k.workshop) {
					cout << "Error. There can be no more operating stations than there are total stations.("
						<< k.workshop << "). Try again." << endl;
				}
			}
			inputNumber(k.class_cs, "Insert CS class: ", true);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;

        case 3: {
            if (t.isEmpty() && k.name.empty()) {
                cout << "No data available, please add objects first." << endl;
            }
            else {
                if (!t.isEmpty()) {
                    cout << "\nPIPE" << endl;
                    cout << "Pipe name: " << t.getName() << endl;
                    cout << "Pipe lenght: " << t.getLenght() << endl;
                    cout << "Pipe diametr: " << t.getDiametr() << endl;
                    cout << "Pipe condition: " << (t.getRepair() ? "1" : "0") << endl << endl;
                }
                if (!k.name.empty()) {
                    cout << "\nCOMPRESSOR STATION" << endl;
                    cout << "CS name: " << k.name << endl;
                    cout << "Number of workshops: " << k.workshop << endl;
                    cout << "Number of workshops in operation: " << k.w_work << endl;
                    cout << "Number of idle workshops: " << (k.workshop - k.w_work) << endl;
                    cout << "CS class: " << k.class_cs << endl << endl;
                }
            }
            break;
        }

        case 4: {
            if (t.isEmpty()) {
                cout << "No pipe to edit, please add a pipe first." << endl;
                break;
            }

            while (true) {
                cout << "\EDIT PIPE" << endl;
                cout << "1. Change name" << endl;
                cout << "2. Change length" << endl;
                cout << "3. Change diameter" << endl;
                cout << "4. Change repair status" << endl;
                cout << "5. Back to main menu" << endl;
                cout << "Choose parameter to edit: ";

                int pipeChoice;
                cin >> pipeChoice;

                switch (pipeChoice) {
                case 1: {
                    cout << "Current name: " << t.getName() << endl;
                    cout << "Enter new name: ";
                    cin.ignore();
                    string tempName;
                    getline(cin, tempName);
                    t.setName(tempName);
                    cout << "Name updated!" << endl;
                }
                case 2: {
                    cout << "Current length: " << t.getLenght() << endl;
                    float tempLenght;
                    inputNumber(tempLenght, "Enter new length: ", true);
                    t.setLength(tempLenght);
                    cout << "Length updated!" << endl;
                    break;
                }
                case 3: {
                    cout << "Current diameter: " << t.getDiametr() << endl;
                    int tempDiametr;
                    inputNumber(tempDiametr, "Enter new diameter: ", true);
                    t.setDiametr(tempDiametr);
                    cout << "Diameter updated!" << endl;
                    break;
                }
                case 4: {
                    cout << "Current repair status: " << (t.getRepair() ? "1" : "0") << endl;
                    bool tempRepair;
                    inputBool(tempRepair, "Enter new status (0 or 1): ");
                    t.setRepair(tempRepair);
                    cout << "Repair status updated!" << endl;
                    break;
                }
                case 5: {
                    cout << "Returning to main menu..." << endl << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                default:
                    cout << "Invalid option!" << endl;
                    continue;
                }
                if (pipeChoice == 5) break;
            }
            break;
        }

        case 5: {
            if (k.name.empty()) {
                cout << "No compressor station to edit, please add a compressor station first." << endl;
                break;
            }

            while (true) {
                cout << "\nEDIT COMPRESSOR STATION" << endl;
                cout << "1. Change name" << endl;
                cout << "2. Change total workshops" << endl;
                cout << "3. Change working workshops" << endl;
                cout << "4. Change class" << endl;
                cout << "5. Start workshop" << endl;
                cout << "6. Stop workshop" << endl;
                cout << "7. Back to main menu" << endl;
                cout << "Choose parameter to edit: ";

                int csChoice;
                cin >> csChoice;

                switch (csChoice) {
                case 1:
                    cout << "Current name: " << k.name << endl;
                    cout << "Enter new name: ";
                    cin.ignore();
                    getline(cin, k.name);
                    cout << "Name updated!" << endl;
                    break;
                case 2:
                    cout << "Current total workshops: " << k.workshop << endl;
                    inputNumber(k.workshop, "Enter new total workshops: ", true);
                    if (k.w_work > k.workshop) {
                        k.w_work = k.workshop;
                        cout << "Working workshops adjusted to " << k.w_work << endl;
                    }
                    cout << "Total workshops updated!" << endl;
                    break;
                case 3:
                    cout << "Current working workshops: " << k.w_work << endl;
                    cout << "Total workshops: " << k.workshop << endl;
                    while (true) {
                        inputNumber(k.w_work, "Enter new working workshops: ");
                        if (k.w_work < 0) {
                            cout << "Error, cannot be negative. Try again." << endl;
                            continue;
                        }
                        if (k.w_work > k.workshop) {
                            cout << "Error, cannot exceed total workshops (" << k.workshop << "). Try again." << endl;
                            continue;
                        }
                        break;
                    }
                    cout << "Working workshops updated!" << endl;
                    break;
                case 4:
                    cout << "Current class: " << k.class_cs << endl;
                    inputNumber(k.class_cs, "Enter new class: ", true);
                    cout << "Class updated!" << endl;
                    break;
                case 5:
                    if (k.w_work < k.workshop) {
                        k.w_work++;
                        cout << "Workshop started, now working: " << k.w_work << " of " << k.workshop << endl;
                    }
                    else {
                        cout << "All workshops are already working!" << endl;
                    }
                    break;
                case 6:
                    if (k.w_work > 0) {
                        k.w_work--;
                        cout << "Workshop stopped, now working: " << k.w_work << " of " << k.workshop << endl;
                    }
                    else {
                        cout << "No workshops are working!" << endl;
                    }
                    break;
                case 7:
                    cout << "Returning to main menu..." << endl << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                default:
                    cout << "Invalid option!" << endl;
                    continue;
                }
                if (csChoice == 7) break;
            }
            break;
        }

        case 6:
        {
            string filename;
            cout << "Enter filename to save: ";
            cin.ignore();
            getline(cin, filename);

            ofstream file(filename);
            if (!file) {
                cout << "Error opening file for writing!" << endl;
                break;
            }

            if (!t.isEmpty()) {
                file << "PIPE" << endl;
                file << t.getName() << endl;
                file << t.getLenght() << endl;
                file << t.getDiametr() << endl;
                file << t.getRepair() << endl;
            }

            if (!k.name.empty()) { 
                file << "CS" << endl;
                file << k.name << endl;
                file << k.workshop << endl;
                file << k.w_work << endl;
                file << k.class_cs << endl;
            }

            file.close();

            if (t.isEmpty() && k.name.empty()) {
                cout << "No data to save!" << endl;
            }
            else {
                cout << "Data saved successfully to " << filename << endl;
                if (!t.isEmpty()) cout << "- Pipe data saved" << endl;
                if (!k.name.empty()) cout << "- Compressor station data saved" << endl;
            }
            break;
        }

        case 7:
        {
            string filename;
            cout << "Enter filename to load: ";
            cin.ignore();
            getline(cin, filename);

            ifstream file(filename);
            if (!file) {
                cout << "Error opening file for reading!" << endl;
                break;
            }

            Pipe tempPipe;
            CS tempCS;
            bool pipeLoaded = false;
            bool csLoaded = false;

            string line;
            while (getline(file, line)) {
                if (line == "PIPE") {
                    string name;
                    float lenght;
                    int diametr;
                    bool repair;

                    getline(file, name);
                    file >> lenght >> diametr >> repair;
                    file.ignore();

                    if (!name.empty()) {
                        tempPipe.setName(name);
                        tempPipe.setLength(lenght);
                        tempPipe.setDiametr(diametr);
                        tempPipe.setRepair(repair);
                        pipeLoaded = true;
                    }
                }
                else if (line == "CS") {
                    getline(file, tempCS.name);
                    file >> tempCS.workshop >> tempCS.w_work >> tempCS.class_cs;
                    file.ignore();

                    if (!tempCS.name.empty()) {
                        csLoaded = true;
                    }
                }
            }

            file.close();

            if (pipeLoaded) {
                t = tempPipe;
                cout << "Pipe data loaded successfully!" << endl;
                cout << "Name: " << t.getName() << ", Length: " << t.getLenght() << ", Diameter: " << t.getDiametr() << endl;
            }
            else {
                cout << "No valid pipe data found in file." << endl;
            }

            if (csLoaded) {
                k = tempCS;
                cout << "Compressor station data loaded successfully!" << endl;
                cout << "Name: " << k.name << ", Workshops: " << k.workshop << "/" << k.w_work << endl;
            }
            else {
                cout << "No valid compressor station data found in file." << endl;
            }

            if (!pipeLoaded && !csLoaded) {
                cout << "File is empty or contains invalid data!" << endl;
            }
            break;
        }

        case 0:
            return;

		default:
			cout << "Invalid option!" << endl;

		}
	}
}

int main()
{
	Pipe truba;
	CS cstation;
	Menu(truba,cstation);
}