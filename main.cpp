#include <limits>
#include <cstdio>
#include <fstream>
#include "Menu.h"

int Error(int dd);
int Error_point(Menu *pointer, int dd);
bool Empty_submenu(Menu *pointer); ///Checks if submenu has pointers
void write1(Menu &m);
void write2(Menu &m);

using namespace std;

int main()
{
    fstream file;
	file.open("test.txt", ios::out);

	///function archive
	Function fun[20];
    string c = "function nr: ";
	for (int i = 0; i < 10; i++)
	{
		char ch = i + '0';
		fun[i] = c + ch;
		fun[i+10] = c + "1" + ch;
	}

	Menu menu("      Menu", NULL, true);
	Menu *m_pointer;            ///the pointer that currently identifies this menu
	Menu *prev = NULL;       ///pointer which helps to go back to submenu
	Function *f_pointer;         ///pointer on d
	Base *pointer;            ///the pointer which identifies this (current) element
	m_pointer = &menu;
	pointer = &menu;

	cout << "        Creating menu" << endl;
	int d = 1;
	write1(menu);
	while (d != 0)
	{
        cin >> d;
        switch (d)
        {
        case 1:
            cout << "Give the name of submenu"<<endl;
            cin >> c;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            file << "To '" <<m_pointer->Text() << "' add: " << m_pointer->add_submenu(m_pointer, c) << endl;
            write1(menu);
            break;
        case 2:
            cout << "Which function do you want to add? (0-19)\n";
            cin >> d;
            while (!(d >= 0 && d <= 19) || !cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error\nGive number of fuction (0-19)\n";
                cin >> d;
            }
            file << "To '" << m_pointer->Text() << "' add: "<<m_pointer->add_function(fun[d])<<endl;
            write1(menu);
            break;
        case 3:
            if (Empty_submenu(m_pointer)) break;
            cout << "Which point do you want to delete?" << endl;
            cin >> d;
            d = Error(d);
            d = Error_point(m_pointer,d);
            file << "From '" << m_pointer->Text() << "' deleted: " << m_pointer->delete_submenu(d) << endl;
            write1(menu);
            break;
        case 4:
            if (Empty_submenu(m_pointer)) break;
            cout << "Which point of function do you want to delete?" << endl;
            cin >> d;
            d = Error(d);
            d = Error_point(m_pointer,d);
            file << "From '" << m_pointer->Text() << "' deleted: " << m_pointer->delete_function(d) << endl;
            write1(menu);
            break;
        case 5:
            if (Empty_submenu(m_pointer)) break;
            cout << "Which point do you want to open?" << endl;
            cin >> d;
            d = Error(d);
            d = Error_point(m_pointer,d);
            pointer = m_pointer->Pointer(d);
            pointer = dynamic_cast<Menu*>(m_pointer->Pointer(d));
            if(pointer)
            {
                pointer = dynamic_cast<Menu*>(m_pointer->Pointer(d));
                prev = m_pointer;                ///helps to go back to submenu
                m_pointer = (Menu*)pointer;
                m_pointer->are_open();
                write1(menu);
            }
            else
            {
                cout << "\nIt is not a function!" << endl;
//                cin.sync();
//                cin.get(); // with iostream
            }
            break;
        case 6:
            if (prev != NULL)
            {
                m_pointer->are_open();
                m_pointer = prev;
                prev = m_pointer->Prev();
            }
            write1(menu);
            break;
        case 7:
            d = 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        default:
            cout << "Incorrect\nType 1-7\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            d = 1;
            break;
        }
	}
	///Collapses the submenu to the initial form
	while(prev != NULL)
    {
        m_pointer->are_open();
        m_pointer = prev;
        prev = m_pointer->Prev();
    }
    if (Empty_submenu(m_pointer))
    {
        file << "The submenu was empty\n" << endl;
        d = 0;
    }
	else
    {
        d = 1;
        cout << "        Testing menu" << endl << endl;
        write2(menu);
    }
	while (d != 0)
    {
        cin >> d;
        switch (d)
        {
        case 1:
            if (Empty_submenu(m_pointer)) break;
            cout << "Which point do you want to enter?" << endl;
            cin >> d;
            d = Error(d);
            d = Error_point(m_pointer,d);
            pointer = m_pointer->Pointer(d);
            pointer = dynamic_cast<Menu*>(m_pointer->Pointer(d));
            if(pointer)
            {
                pointer = dynamic_cast<Menu*>(m_pointer->Pointer(d));
                prev = m_pointer;               ///helps to back to submenu
                m_pointer = (Menu*)pointer;
                m_pointer->are_open();
                write2(menu);
            }
            else
            {
                cout << "\nThis is not a function!" << endl;
            }
        break;
        case 2:
            if (prev != NULL)
            {
                m_pointer->are_open();
                m_pointer = prev;
                prev = m_pointer->Prev();
            }
            write2(menu);
            break;
        case 3:
            if (Empty_submenu(m_pointer)) break;
            cout << "Which function do you want to use?" << endl;
            cin >> d;
            d = Error(d);
            d = Error_point(m_pointer,d);
            pointer = m_pointer->Pointer(d);
            pointer = dynamic_cast<Function*>(m_pointer->Pointer(d));
            if (pointer)
            {
                f_pointer = (Function*)pointer;
                f_pointer->start_function();
                file << "In '" << m_pointer->Text() << "' use: " << f_pointer->Text()  << endl;
                write2(menu);
            }
            else
            {
                cout << "\nThis is not a function!\n" << endl;
            }
            break;
        case 4:
            d = 0;
            break;
        default:
            cout << "Choose 1-4!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            d = 1;
            break;
        }
    }
	file << "END" << endl;
	file.close();
}

int Error(int dd)
{
    while (!dd)
    {
        cout << "Incorrect data\nGive a number\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> dd;
    }
    return dd;
}
int Error_point(Menu *pointer, int dd)
{
    while (pointer->Menu_length() < dd)
    {
        cout << dd << " not exist!\nGive another number" << endl;
        cin >> dd;
        dd = Error(dd);
    }
    return dd;
}
///Is submenu empty?
bool Empty_submenu(Menu *pointer)
{
    if((pointer->Menu_length()) ==0)
    {
        cout << "\nThe submenu is empty!\n" << endl;
        return true;
    }
    return false;
}
void write1(Menu &m)
{
        cout << endl << " ............ \n" << m << " ............ " <<endl<<endl;
        cout << "   Choose:" << endl;
        cout << "1. Add the submenu" << endl;
        cout << "2. Add the functiom" << endl;
        cout << "3. Delete the submenu" << endl;
        cout << "4. Delete the function" << endl;
        cout << "5. Enter submenu" << endl;
        cout << "6. Leave submenu" << endl;
        cout << "7. Stop creating a menu" << endl;
}
void write2(Menu &m)
{
        cout << endl << " ............ \n" << m << " ............ " <<endl<<endl;
        cout << "   Choose:" << endl;
        cout << "1. Enter submenu" << endl;
        cout << "2. Leave submenu" << endl;
        cout << "3. Start function" << endl;
        cout << "4. Close the program" << endl;
}
