/*
Author :Aadil Chasmawala
CPE assignment 1 
Civil engineering Case study

*/

#include <iostream>
#include <fstream>

using namespace std;
int main() {
	//Assumptions I made:
	// 1. Program reruns until user exits with option 3
	// 2. Program does not allow user to select option 2 if option 1 hasnt been selected
	// 3. The test files have a similar format to the one given in the Example .

	
	//while True is to repeat the program until user exits
	bool option_1_select = false;//To check whether option 1 has been selected
	double m(0), b(0);//used in both Case 1 and Case 2
	while (true) {
		char option;
		//Display the menu
		cout << "You have the following options :" << endl;
		cout << "(1) Calculate the linear regression model using the data stored in a given file ." << endl;
		cout << "(2) Calculate a freezing temperature given the water salinity using the linear model developed in option(1)." << endl;
		cout << "(3) Exit the program" << endl;
		cout << "Enter 1 , 2 or 3 to select one of the three options :";
		cin >> option;
		while (option != '1' && option != '2' && option != '3') {

			cout << "Invalid choice entered, please enter a valid choice:" << endl;
			cin >> option;
		}//ask user for options until valid value is entered
		switch (option) {
		case '1': { //brackets are needed to ensure filename is a variable only for this block
			option_1_select = true;
			string filename;
			ifstream inFile;
			cout << "Enter the filename of the file that stores the data:" << endl;
			cin >> filename;
			inFile.open(filename, ios::in);
			//Make sure file can be opened, if not displays error and exits whole program with code -1
			if (inFile.fail()) {
				cerr << "Error: The file could not be opened/found, please try running again " << endl;
				exit(-1);
			}
			double f_temp(0), w_salinity(0);
			double sum_f_temp(0), sum_w_salinity(0), sum_w_salinity_squared(0), sum_w_salinity_f_temp(0);
			string firstline;
			char c='a';
			while (c != '\n') {
				inFile.get(c);
				firstline+=c;
				//append character to a string so that the first line is stored in one variable
			}
			int n(0);// number of entries in table
			while (!inFile.eof())//Read until end of file is reached
			{
				inFile >> w_salinity >> f_temp;
				sum_f_temp += f_temp;
				sum_w_salinity += w_salinity;
				sum_w_salinity_f_temp += f_temp * w_salinity;
				sum_w_salinity_squared += w_salinity*w_salinity;
				n += 1;
			}
			inFile.close();
			//calculate m and b 
			m = (sum_w_salinity * sum_f_temp - n * sum_w_salinity_f_temp) 
				/ (pow(sum_w_salinity,2) - n * sum_w_salinity_squared);
			b= (sum_w_salinity * sum_w_salinity_f_temp - sum_w_salinity_squared*sum_f_temp)
				/ (pow(sum_w_salinity, 2) - n * sum_w_salinity_squared);
			cout << "The model parameters are: \n m = " << m << " \n b = " << b << endl;
			cout << "Hence, the linear interpolation function is : \n" << " T=" << m << "*S +" << b << endl;
			cout << "where T is the Freezing temperature,S is the water salinity and m and b are the model parameters" << endl;



			break; }
		case '2': {
			//To Check If option one has been selected before
			if (option_1_select == true) {
				double salinity(0);
				double temperature(0);
				cout << "Enter a salinity value (greater than or equal to 0)" << endl;
				cin >> salinity;
				//Ensure salinity value is valid
				while (salinity < 0) {
					cout << "The value you entered is not greater than or equal to 0" << endl;
					cout<<"Enter a Valid value of Salinity: " <<endl;
					cin >> salinity;

				}
				//Since this runs only if option 1 is selected before , we can use the same variables m and b
				temperature = m * salinity + b;
				cout << "The temperature at the given salinity value is : " << temperature << endl;
				
				break;
			}
			else {
				cout << "Please select option 1 before selecting option 2" << endl;
				continue; // the switch statement is exited and program will prompt again for the options.
			}
               }
		case '3': {
			cout << "----------------------------------------------" << endl;
			return 0; } //Ends program without any errors(as intended)
		}
		cout << "----------------------------------------------" << endl;
		//Indicates successful execution of one loop of the program.
	}
	//A return 0 here will never be reached because the intended execution of the program is to stop when 
	//option 3 is entered in the menu and keep running until then.
}