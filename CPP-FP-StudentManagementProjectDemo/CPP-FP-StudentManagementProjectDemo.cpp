#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>

using namespace std;

struct Student
{

	int admno;
	char name[20];
	char gender;
	int std;
	float marks;
	float percentage;


};

void addData()
{
	Student s;
	ofstream fout;
	fout.open("Students.dat", ios::binary | ios::out|ios::app);
	cout << "\n\nEnter Student Details......\n";
	cout << "Enter Admission No.     : "; 
	cin >> s.admno;
	cout << "Enter Full Name         : "; 
	cin.ignore(); 
	cin.getline(s.name, 20);
	cout << "Enter Gender (M/F)      : "; 
	cin >> s.gender;
	cout << "Enter Standard          : "; 
	cin >> s.std;
	cout << "Enter Marks (out of 500): "; 
	cin >> s.marks;
	cout << endl;
	s.percentage = s.marks * 100.0 / 500.00;
	fout.write((char*)&s, sizeof(s));
	fout.close();
	cout << "\n\nData Successfully Saved to File....\n";
}

void displayData()
{
	Student s;
	ifstream fin;
	fin.open("Students.dat", ios::in | ios::binary);
	while (fin.read((char*)&s, sizeof(s)))
	{
	
		cout << "\n\n.......Student Details......\n";
		cout << "Admission No.     : " << s.admno << endl;
		cout << "Full Name         : " << s.name << endl;
		cout << "Gender            : " << s.gender << endl;
		cout << "Standard          : " << s.std << endl;
		cout << "Marks (out of 500): " << s.marks << endl;
		cout << "Percentage        : " << s.percentage << endl;
		cout << endl;
	}
	fin.close();
	cout << "\n\nData Reading from File Successfully Done....\n";
}

void searchData()
{
	Student s;
	int n, flag = 0;
	ifstream fin;
	fin.open("Students.dat", ios::in | ios::binary);
	cout << "Enter Admission Number you want to search : ";
	cin >> n;

	while (fin.read((char*)&s, sizeof(s)))
	{
		if (n == s.admno)
		{
			cout << "The Details of Admission No. " << n << " shown herewith:\n";
			cout << "\n\n.......Student Details......\n";
			cout << "Admission No.     : " << s.admno << endl;
			cout << "Full Name         : " << s.name << endl;
			cout << "Gender            : " << s.gender << endl;
			cout << "Standard          : " << s.std << endl;
			cout << "Marks (out of 500): " << s.marks << endl;
			cout << "Percentage        : " << s.percentage << endl;
			cout << endl;
			flag++;
		}
	}
	fin.close();
	if (flag == 0)
		cout << "The Admission No. " << n << " not found....\n\n";
	cout << "\n\nData Reading from File Successfully Done....\n";
}

void deleteData()
{
	Student s;
	int n, flag = 0;
	ifstream fin;
	ofstream fout, tout;

	fin.open("Students.dat", ios::in | ios::binary);
	fout.open("TempStud.dat", ios::out | ios::app | ios::binary);
	tout.open("TrashStud.dat", ios::out | ios::app | ios::binary);

	cout << "Enter Admission Number you want to move to Trash : ";
	cin >> n;

	while (fin.read((char*)&s, sizeof(s)))
	{
		if (n == s.admno)
		{
			cout << "The Following Admission No. " << n << " has been moved to Trash:\n";
			cout << "The Details of Admission No. " << n << " shown herewith:\n";
			cout << "\n\n.......Student Details......\n";
			cout << "Admission No.     : " << s.admno << endl;
			cout << "Full Name         : " << s.name << endl;
			cout << "Gender            : " << s.gender << endl;
			cout << "Standard          : " << s.std << endl;
			cout << "Marks (out of 500): " << s.marks << endl;
			cout << "Percentage        : " << s.percentage << endl;
			cout << endl;
			tout.write((char*)&s, sizeof(s));
			flag++;
		}
		else
		{
			fout.write((char*)&s, sizeof(s));
		}
	}
	fout.close();
	tout.close();
	fin.close();
	if (flag == 0)
		cout << "The Admission No. " << n << " not found....\n\n";
	remove("Students.dat");
	rename("tempStud.dat", "Students.dat");
}

void getTrash()
{
	Student s;
	int n;
	ifstream fin;
	fin.open("TrashStud.dat", ios::in | ios::binary);
	while (fin.read((char*)&s, sizeof(s)))
	{
		cout << "\n\n.......Student Details......\n";
		cout << "Admission No.     : " << s.admno << endl;
		cout << "Full Name         : " << s.name << endl;
		cout << "Gender            : " << s.gender << endl;
		cout << "Standard          : " << s.std << endl;
		cout << "Marks (out of 500): " << s.marks << endl;
		cout << "Percentage        : " << s.percentage << endl;
		cout << endl;
	}
	fin.close();
	cout << "\n\nData Reading from Trash File Successfully Done....\n";
}

void modifyData()
{
	Student s;
	
	int n, flag = 0, pos;
	fstream fio;

	fio.open("Students.dat", ios::in | ios::out | ios::binary);

	cout << "Enter Admission Number you want to Modify : ";
	cin >> n;

	while (fio.read((char*)&s, sizeof(s)))
	{
		pos = fio.tellg();
		if (n == s.admno)
		{
			cout << "\n\n.......Student Details......\n";
			cout << "Admission No.     : " << s.admno << endl;
			cout << "Full Name         : " << s.name << endl;
			cout << "Gender            : " << s.gender << endl;
			cout << "Standard          : " << s.std << endl;
			cout << "Marks (out of 500): " << s.marks << endl;
			cout << "Percentage        : " << s.percentage << endl;
			cout << endl;
			cout << "\n\nNow Enter the New Details....\n";
			
			//input
			cout << "\n\nEnter Student Details......\n";
			cout << "Enter Admission No.     : ";
			cin >> s.admno;
			cout << "Enter Full Name         : ";
			cin.ignore();
			cin.getline(s.name, 20);
			cout << "Enter Gender (M/F)      : ";
			cin >> s.gender;
			cout << "Enter Standard          : ";
			cin >> s.std;
			cout << "Enter Marks (out of 500): ";
			cin >> s.marks;
			cout << endl;
			fio.seekg(pos - sizeof(s));
			fio.write((char*)&s, sizeof(s));
			flag++;
		}
	}
	fio.close();

	if (flag == 0)
		cout << "The Admission No. " << n << " not found....\n\n";
}


int main()
{
	int ch;
	do
	{
		system("cls");
		cout << "...............STUDENT MANAGEMENT SYSTEM..............\n";
		cout << "======================================================\n";

		cout << "1. Add Student Data\n";
		cout << "2. Display Student Data\n";
		cout << "3. Search Student Data\n";
		cout << "4. Delete Student Data\n";
		cout << "5. Trash Student Data \n";
		cout << "6. Modify Student Data\n";
		cout << "0. Exit from Program\n";
		cout << "Enter your choice  : ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case 1: addData(); break;
		case 2: displayData(); break;
		case 3: searchData(); break;
		case 4: deleteData(); break;
		case 5: getTrash(); break;
		case 6: modifyData(); break;
		}
		system("pause");
	} while (ch);

	return 0;
}