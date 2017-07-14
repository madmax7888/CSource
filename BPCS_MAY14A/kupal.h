

#pragma once
#include <string>
#include <mutex>

using namespace std;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

class kupal
{
private:
	string name;
	string petname;
	bool smelly_fart;
	int sss;
	static int bilang;

public:
	kupal(const string &sname, const string &spet, const bool &tf);
	string getname(void);
	void setname(const string &sname);
	void showval(void);
	void dispose(void);
	~kupal(void);
};

