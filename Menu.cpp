#include "Menu.h"

using namespace std;

void Base :: set_text(string m_text)
{
    text = m_text;
}
string Base :: Text() const
{
    return text;
}
void Base :: set_indentation(int m_indentation)
{
    indentation = m_indentation;
}
int Base :: Indentation()const
{
    return indentation;
}

/******************************************************/
string Menu :: add_submenu(Menu* p, string m_text)
{
    Menu* e_p = new Menu;
    e_p->prev = p;
    e_p->set_text(m_text);
    e_p->set_indentation(p->Indentation()+2);
    elem.push_back(e_p);
    return (m_text);
}
string Menu :: delete_submenu(unsigned int which)
{
string result = "Error with removing the submenu";
    Menu* temp;
    temp = dynamic_cast<Menu*>(elem[which-1]);
    if (temp)
    {
        result = elem[which-1]->Text();
        delete elem[which-1];//dealocation of memory for submenu
        elem.erase(elem.begin() + which - 1);
    }
    else
        cout << "There is no submenu" << endl;
	return result;
}//Delete the number which is at "nr"
string Menu::add_function(Function &f)
{
    Function *fun;
    fun = &f;
    elem.push_back(fun);
    return (fun->Text());
}
string Menu::delete_function(unsigned int which)
{

		string result = "";
		Function* temp;
		temp = dynamic_cast<Function*>(elem[which-1]);
		if (temp)
		{
			result = elem[which - 1]->Text();
			elem.erase(elem.begin() + which - 1);
		}
		else
			cout << "There is no function in the indicated space\n" << endl;
	return result;
}///delete the element which is at "nr"
void Menu::set_pointer(Menu* arg)
{
	prev = arg;
}
void Menu::are_open()
{
	to_open = !(to_open);
}
Menu* Menu::Prev() const
{
	return prev;
}
Base* Menu::Pointer(unsigned i) const
{
	return elem[i-1];
}
int Menu::Menu_length() const
{
	return elem.size();
}

/******************************************************/
void Function::start_function()
{
	cout << "\nWorks: " << Text() << endl;
}

/*******************************************************/
ostream& operator<<(ostream& out,const Base &arg)
{
	out << arg.text << endl;
	return out;
}
ostream& operator<<(ostream& out, const Menu &arg)
{
	Base* p;
	const Menu* p_arg;
	p_arg = &arg;
	out << (Base&)arg;
	if (arg.to_open)
		for (size_t i = 0; i < arg.elem.size(); ++i)
		{
			p = dynamic_cast<Function*>(arg.elem[i]);
				if (p)
				{
				    out.width(p_arg->Indentation());
					out << i+1 << ". " << *(arg.elem[i]);
				}
				else
				{
					p = dynamic_cast<Menu*>(arg.elem[i]);
					out.width(p_arg->Indentation());
					out << i+1 << ". " << *((Menu*)p);
				}
		}
	return out;
}//write submenu, when write function
ostream& operator<<(ostream& out, const Function &arg)
{
	out << (Base&)arg;
	return out;
}
