
#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <deque>
#include <condition_variable>
#include <thread>
#include <exception>
#include <vector>
#include <fstream>
#include <assert.h>
#include <sstream>
#include <boost/chrono/thread_clock.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/greg_month.hpp>
#include <algorithm>
#include <Windows.h>
#include "kupal.h"
//##############################################################################
const int MAX = 99;
const int MIN = 10;
std::mutex PCMU;
bool TRULSE;
std::deque<int> RVALX;
std::deque<int> CNTRX;
std::condition_variable COND;
//##############################################################################
using namespace std;
using namespace boost::algorithm;
using namespace boost::posix_time;
using boost::lexical_cast;
using boost::bad_lexical_cast;

//##############################################################################
void inline NEWL(void)
{
	cout << "\n\n";
}

//##############################################################################
void inline spacer(string stra)
{
	cout << "===================== " << stra << " =======================" << endl;
}

//##############################################################################
struct SCLUB
{
	string name;
	int age;
	int sss;
	bool likepet;
	double money;
};
//##############################################################################


//##############################################################################
int get_irandom(void);
void run_class(void);
void prod_cons(void);
void produce(void);
void consume(void);
void run_struct(void);
void run_template(void);
template<typename tt>
void test_template(const tt & idata);
void run_array(void);
void read_array(const int *aptr, const int &limit);
void count_em(int &cntx);
void do_recursive(void);
void convert_num(void);
void test_lambda(void);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
int _tmain(int argc, _TCHAR* argv[])
{
	const ptime start = microsec_clock::local_time();
	run_class();
	prod_cons();
	run_struct();
	run_template();
	run_array();
	do_recursive();
	convert_num();
	test_lambda();
	const ptime stop = microsec_clock::local_time();
	const time_duration elapsed = stop - start;
	cout << "\n\nElapsed Time = " << elapsed << std::endl;
	system("pause");
	return 0;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void run_class(void)
{
	spacer("Class and Object");
	string zname;
	kupal *PTR1 = new kupal("max", "bruce", true);
	kupal OBJ1("ray", "toby", false);
	kupal *PTRX;

	PTRX = &OBJ1;
	zname = PTRX->getname();
	cout << "Got Name : " << zname << endl;
	PTRX->setname("mork");

	zname = PTR1->getname();
	cout << "Got Name : " << zname << endl;
	PTR1->showval();

	delete PTR1;
	PTR1 = nullptr;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void prod_cons(void)
{
	NEWL();
	spacer("Produce and Consume Thread");
	std::thread prod(produce);
	std::thread cons(consume);
	Sleep(10);
	prod.join();
	cons.join();
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void produce(void)
{
	int cntr, rval;
	stringstream stm;
	string stra;
	cntr = 10;
	TRULSE = false;
	try
	{
		while (cntr > 0)
		{
			std::unique_lock<mutex> locker1(PCMU);
			rval = get_irandom();
			RVALX.push_front(rval);
			CNTRX.push_front(cntr);
			stm << "produce ---> " << "RVALX = " << rval << "   " << "CNTRX = " << cntr << endl;
			stra = stm.str();
			cout << stra;
			stm.str("");
			cntr--;
			TRULSE = true;
			locker1.unlock();
			COND.notify_one();
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}
	catch (exception& e)
	{
		cout << "Error : " << e.what() << endl;
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void consume(void)
{
	int cntr, rval;
	stringstream stm;
	string stra;
	cntr = 10;
	try
	{
		while (cntr > 1)
		{
			std::unique_lock<mutex> locker1(PCMU);
			COND.wait(locker1, []() {return TRULSE == true;  });
			TRULSE = false;
			rval = RVALX.front();
			cntr = CNTRX.front();
			RVALX.pop_front();
			CNTRX.pop_front();
			stm << "consume ---> " << "RVALX = " << rval << "   " << "CNTRX = " << cntr << endl;
			stra = stm.str();
			cout << stra;
			stm.str("");
			locker1.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}
	catch (exception& e)
	{
		cout << "Error : " << e.what() << endl;
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void run_struct(void)
{
	NEWL();
	spacer("Structure");
	int lena, iname, iage, isss, ipet, imoney;
	int iaddr;
	stringstream stm;
	SCLUB *SPTRA = new SCLUB;
	SCLUB OBJ1;
	SCLUB *SPTR1;

	SPTR1 = &OBJ1;

	SPTRA->name = "kups";
	SPTRA->age = 23;
	SPTRA->sss = 22334568;
	SPTRA->likepet = true;
	SPTRA->money = 0Xfffe;

	SPTR1->name = "max";
	SPTR1->age = 76;
	SPTR1->sss = 98765431;
	SPTR1->likepet = false;
	SPTR1->money = 1203;

	cout << "Name : " << SPTR1->name << "  Age : " << SPTR1->age << "   Likepet : " << SPTR1->likepet << endl;
	cout << "Name : " << SPTRA->name << "   Age : " << SPTRA->age << "   Likepet : " << SPTRA->likepet << endl;
	lena = sizeof(*SPTRA);
	iname = sizeof(SPTRA->name);
	iage = sizeof(SPTRA->age);
	isss = sizeof(SPTRA->sss);
	ipet = sizeof(SPTRA->likepet);
	imoney = sizeof(SPTRA->money);

	stm.str("");
	stm << (void *)(SPTR1);
	string addr = stm.str();
	cout << "\naddress of struct = " << addr << endl;
	cout << "address of struct = " << (void*)(&OBJ1) << endl;
	stm.str("");
	//===========================================================================//
	std::stringstream ss;
	ss << std::hex << addr;
	ss >> iaddr;
	cout << "\n\nusing stringstream convert string hex integer to integer" << endl;
	cout << "address of struct1 = " << iaddr << "\n\n";
	cout << "address of struct2 = 0x" << std::hex << iaddr << "\n\n";
	//==========================================================================//
	cout << "struct size = " << lena << endl;
	cout << "struct name = " << iname << endl;
	cout << "struct age = " << iage << endl;
	cout << "struct sss = " << isss << endl;
	cout << "struct pet = " << ipet << endl;
	cout << "struct money = " << imoney << endl;
	delete SPTRA;
	SPTRA = nullptr;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void run_template(void)
{
	NEWL();
	spacer("template");
	string mystr;
	int myint;

	mystr = "this sucks and full of bullshit and kupal and whiff";
	test_template<string>(mystr);
	myint = 1234;
	test_template<int>(myint);
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
template <typename tt>
void test_template(const tt & idata)
{
	int isize;
	stringstream stm;
	string stra;

	isize = sizeof(idata);
	stm << "Data : " << idata << "\ndata size = " << isize << endl;
	stra = stm.str();
	stm.str("");
	cout << stra;

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void run_array(void)
{
	NEWL();
	spacer("pointers to array");
	int arr[10];
	int *ptra;
	int *ptrb = new int[10];
	int size, cntr, rval;

	size = sizeof(arr) / sizeof(arr[0]);
	cout << "array size = " << size << endl;

	ptra = &arr[0];
	*ptra = 10;

	ptra++;
	*ptra = 11;

	ptra = &arr[2];
	*ptra = 12;

	ptra = &arr[0];
	*(ptra + 3) = 13;

	ptra = &arr[0];
	ptra[4] = 14;

	ptra = (arr + 5);
	*ptra = 15;

	ptra = &arr[0];
	read_array(ptra, 5);

	cout << "\n\nArray in heap" << endl;
	for (cntr = 0; cntr < size; cntr++)
	{
		rval = get_irandom();
		*(ptrb + cntr) = rval;
	}
	read_array(ptrb, size);

	delete []ptrb;
	ptrb = nullptr;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void read_array(const int *aptr, const int &limit)
{
	int cntr, rval, iaddr;
	stringstream stm, stx;
	string stra;
	for (cntr = 0; cntr < limit; cntr++)
	{
		rval = *(aptr + cntr);
		stm << (aptr + cntr);
		stra = stm.str();
		cout << "*(aptr + cntr) = " << rval << "    " << " Address = 0x" << stra << endl;
		stm.str("");

		cout << "\nConvert hex value to hex integer and print it" << endl;
		stx << std::hex << (aptr + cntr);
		stx >> iaddr;
		cout << "Address via string --> hex = 0x" << iaddr << "\n\n";
		stx = std::stringstream(); // need to clear value of stx
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void do_recursive(void)
{
	NEWL();
	spacer("recursive");
	int cntr = 10;
	count_em(cntr);
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void count_em(int &cntx)
{
	if (cntx > 0)
	{
		cout << "cntr = " << cntx << endl;
		cntx--;
		count_em(cntx);
	}
	else
	{
		cout << "Done Counter" << endl;
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void convert_num(void)
{
	NEWL();
	float fval;
	int ival;
	int zval;
	stringstream stx, stz, sty;
	string stra;

	string str1 = "750";
	string str2 = "2.7135678943";
	string str3 = "0x7abcde";
	spacer("convert string number to integers");
	try
	{
		sty << std::hex << str3;
		sty >> zval;
		cout << "long Val = 0x" << std::hex << zval << endl;

		stx << str2;
		stx >> fval;
		cout << "float Val = " << std::setprecision(6) << fval << endl;

		stz << str1;
		stz >> ival;
		cout << "int Val = " << std::dec << ival << endl;
	}
	catch (exception& e)
	{
		cerr << "Bad cast: " << e.what() << endl;
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void test_lambda(void)
{
	NEWL();
	spacer("lambda");
	int rval, cntr;
	auto sum = 0;

	std::deque<int> ideck;
	ideck.resize(10);
	for (cntr = 0; cntr < 10; cntr++)
	{
		rval = cntr + 1;
		ideck.at(cntr) = rval;
	}

	auto getsum = [&sum](int x)
	{
		sum += x;
		cout << "x value = " << x << endl;
	};

	std::for_each(begin(ideck), end(ideck), getsum);
	cout << "sum = " << sum << endl;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
int get_irandom(void)
{
	int rval, min, max;
	min = MIN;
	max = MAX;
	rval = min + (rand() % (int)(max - min + 1));
	return rval;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
