#include<iostream>
using namespace std;

class Date
{
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:
	int GetMonthDay(int year, int month)
	{
		static int MonthDay[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if ((month == 2) && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		{
			return 29;
		}
		return MonthDay[month];
	}

	Date(int year = 0, int month = 1, int day = 1)
	{
		if (month >= 1 && month <= 12 && day >= 1 && day <= GetMonthDay(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "请输入正确的日期" << endl;
		}
	}

	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	Date& operator=(const Date& d)
	{
		//非常关键
		if (this !=&d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
	return *this;
	}

	bool operator==(const Date& d)
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}

	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}

	bool operator>(const Date& d)
	{
		if (_year > d._year)
			return true;
		else if (_year == d._year && _month > d._month)
			return true;
		else if (_year == d._year && _month == d._month && _day > d._day)
			return true;
		return false;
	}

	bool operator>=(const Date& d)
	{
		return ((*this == d) || (*this > d));
	}

	bool operator<(const Date& d)
	{
		return !(*this >= d);
	}

	bool operator<=(const Date& d)
	{
		return *this < d || *this == d;
	}

	//重载+=号
	Date& operator+=(int day)
	{
		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			++_month;
			if (_month == 13)
			{
				++_year;
				_month = 1;
			}

		}
		return *this;
	}

	Date operator+(int day)
	{
		//Date ret(*this);
		//ret._day += day;
		//while (ret._day > GetMonthDay(ret._year, ret._month))
		//{
		//	ret._day -= GetMonthDay(ret._year, ret._month);
		//	++ret._month;
		//	if (ret._month == 13)
		//	{
		//		++ret._year;
		//		ret._month = 1;
		//	}
		//}
		//return ret;

		Date ret(*this);
		ret += day;
		return ret;
	}

	void print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "-" << d._month << "-" << d._day << endl;
	return out;
 }
istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}



int main()
{
	Date d1(2022, 2, 28);
	d1.print();

	Date d2(2022,2,28);
	d2.print();
	cout << (d1 != d2) << endl;
	cout << (d1 == d2) << endl;
	cout << (d1 > d2) << endl;
	cout << (d1 >= d2) << endl;
	cout << (d1 < d2) << endl;
	cout << (d1 <= d2) << endl;

	Date d3 = d2;
	d3 += 1;
	d3.print();

	Date d4 = d3 + 33;
	d4.print();

	cout << d4;

	Date d5;
	cin >> d5;
	cout << d5;

	return 0;
}