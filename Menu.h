#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Base
{
private:
    string text;
    int indentation;
public:
    Base():text(""),indentation(2){};
    Base(const string &b_text, int b_indentation = 2):text(b_text), indentation(b_indentation) {};
    virtual ~Base(){};

    void set_text(string b_text);
    string Text() const;
    void set_indentation(int b_indentation);
    int Indentation() const;

    friend ostream& operator<<(ostream &out,const Base &arg);
};

class Function : public Base
{
public:
	Function(string f_text = "Function"):Base(f_text){};
	~Function(){};
	void start_function();

	friend ostream& operator<<(ostream &out,const Function &arg);
};

class Menu : public Base
{
private:
    vector<Base*> elem;
    Menu *prev;
    bool to_open;
public:
  Menu(string m_text = "", Menu* p = NULL, bool open = false, int m_indentation = 2):
    Base(m_text, m_indentation), elem(), prev(p), to_open(to_open){};
  Menu(const Menu &arg):
    elem(arg.elem), prev(arg.prev), to_open(arg.to_open){};
  ~Menu(){};

    Base* Pointer(unsigned i) const;
    void write_elem() const;
    int Menu_length() const;
    void are_open();
    Menu* Prev() const;
    void set_pointer(Menu* p);
    string add_submenu(Menu* p, string m_text);
    string add_function(Function&);
    string delete_submenu(unsigned int nr);
    string delete_function(unsigned int which);

    friend ostream& operator<<(ostream &out,const Menu &arg);
};
