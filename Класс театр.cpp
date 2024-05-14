#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Windows.h"

using namespace std;

byte fun(int k) { if (k % 50 == 0)return 0; else return 1; }

void cur_date(short& day, short& month, short& year) {//���������� ������� ����
	SYSTEMTIME t;
	GetLocalTime(&t);
	day = t.wDay;
	month = t.wMonth;
	year = t.wYear;
}

int my_stoi(string str) {//������� �������������� ������ ���� � ����� ���� int 
	int k = 0,  f = 0;
	string sh = "0123456789";
	if (str.empty()) return k;
	while (str[0] == '0') {//������� ��� ���������� ����
		str.erase(0, 1);
		if (str.empty())  return k; 
	}
	for (int i = 0; i < str.length(); i++) {
		for (int j = 0; j < sh.length(); j++)
			if (str[i] == sh[j]) {
				k = k * 10 + j;
				f = 1;
				break;
			}
		if(f == 0) return -1;
		f = 0;
	}
	return k;
}

bool dig(string str) {//�������, ����������, ������� �� ������ ������ �� ����
	string sh = "0123456789";
	int f = 0;
	for (int i = 0; i < str.length(); i++) {
		for (int j = 0; j < sh.length(); j++)
			if (str[i] == sh[j]) {
				f = 1;
				break;
			}
		if (f == 0) return false;
		f = 0;
	}
	return true;
}

bool dig_price(string str) {//�������, ����������, ������� �� ������ ������ �� ���� � ����� (��� ����)
	string sh = "0123456789.";
	int f = 0;
	for (int i = 0; i < str.length(); i++) {
		for (int j = 0; j < sh.length(); j++)
			if (str[i] == sh[j]) {
				f = 1;
				break;
			}
		if (f == 0) return false;
		f = 0;
	}
	for (int i = 0, k = 0; i < str.length(); i++) {//���������� ����, ���� � ������ ������ ����� �����
		if (str[i] == '.') k++;
		if (k > 1) return false;
	}
	return true;
}

bool only_let_cap(string str) {//����������, ���� �� � ������ �������, ����� ���� �������� � ���������� ��������� � ������ ������ ����� ������ � ����� ���� ���������
	while (str.find(' ') != string::npos)//������� �������
		str.erase(str.find(' '), 1);

	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ�����Ũ��������������������������", a = "abcdefghikjlmnopqrstuvwxyz��������������������������������";
	int f = 0, f1 = 0;
	for (int i = 0; i < A.length(); i++) {
		if (str[0] == A[i]){
			f1 = 1;
			break;
		}
	}
	for (int i = 1; i < str.length(); i++)
		for (int j = 0; j < a.length(); j++)
			if (str[i] == a[j]) {
				f++;
				break;
			}
	if (f == (str.length()-1) && f1 == 1) return true;
	else return false;
}

bool only_let(string str) {//����������, ���� �� � ������ �������, ����� ���� �������� � ���������� ���������
	while (str.find(' ') != string::npos)//������� �������
		str.erase(str.find(' '), 1);

	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ�����Ũ��������������������������abcdefghikjlmnopqrstuvwxyz��������������������������������";
	int f = 0;

	for (int i = 0; i < str.length(); i++)
		for (int j = 0; j < A.length(); j++)
			if (str[i] == A[j]) {
				f++;
				break;
			}
	if (f == str.length()) return true;
	else return false;
}

string lowercase(string str) {//���������� ������ �� ������� ����, ���� � ��� ���� ��������� �����, ����� ������ �� ����������
	int f = 0;
	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ�����Ũ��������������������������", a = "abcdefghikjlmnopqrstuvwxyz��������������������������������", rez = "";
	for (int i = 0; i < str.length(); i++) {
		f = 0;
		for (int j = 0; j < A.length(); j++) 
			if (str[i] == A[j]) {
				rez += a[j];
				f = 1;
				break;
			}
		if (f == 0) rez += str[i];
	}
	return rez;
}

struct hall {//�������� ����������� ����
	int row = 0;
	int seat_row = 0;

	hall operator=(hall&);
	hall(int, int);
	hall();
};

hall :: hall() {
	row = 0;
	seat_row = 0;
}

hall :: hall(int r, int s) {
	row = r;
	seat_row = s;
}

hall hall :: operator=(hall& ob) {//������������ �����
	row = ob.row;
	seat_row = ob.seat_row;
	return *this;
}

struct Time {//��������� �������
	string hour;
	string min;

	Time operator=(Time); // ����������� const time& ������ time
	int operator==(Time);
	Time(string, string);
	Time();
};

Time::Time() {
	hour = "";
	min = "";
}

Time::Time(string h, string m) {
	hour = h;
	min = m;
}

Time Time::operator=(Time ob) {
	hour = ob.hour;
	min = ob.min;
	return *this;
}

int Time::operator==(Time ob) {
	return hour == ob.hour && min == ob.min;
}

struct Date {//��������� ����
	string day;
	string month;
	string year;

	Date operator=(Date);
	int operator==(Date);
	Date(string, string, string);
	Date();
};

Date::Date() {
	day = "";
	month = "";
	year = "";
}

Date:: Date(string d, string m, string y){
	day = d;
	month = m;
	year = y;
}

Date Date :: operator=(Date ob) {
	day = ob.day;
	month = ob.month;
	year = ob.year;

	return *this;
}

int Date::operator==(Date ob) {
	return day == ob.day && month == ob.month && year == ob.year;
}

struct play {//����������
	string name;//�������� ����������
	struct Date date;//���� ����������
	struct Time time;//����� ����������
	string ganre;//���� ����������
	string price;//���� ������ ������
	int num_hall = 0;//����� ����
	hall play_h;//���������� � ����
	vector<vector<bool>> seats;//������ � ����������/��������� ����������� ����� ����
	
	play();
	play(string, struct Date, struct Time, string, string, int, hall);
	play& operator=(play&);
	int operator==(play ob);
	friend ostream& operator<<(ostream&, play&);
	int free_place();
};

play::play() {
	Date d;
	Time t;
	name = "";
	date = d;
	time = t;
	ganre = "";
	price = "";
}

play::play(string n, struct Date d, struct Time t, string g, string p, int num, hall h) : name(n), date(d), time(t), ganre(g), price(p), num_hall(num), play_h(h) {}

play& play::operator=(play& ob) {//���������� ��������� ������������ ��� ����������
	name = ob.name;
	date = ob.date;
	time = ob.time;
	ganre = ob.ganre;
	price = ob.price;
	num_hall = ob.num_hall;
	play_h = ob.play_h;
	seats = ob.seats;
	return *this;
}

int play::operator==(play ob){
	return name == ob.name && date == ob.date && time == ob.time && num_hall == ob.num_hall && ganre == ganre;
}

int play :: free_place() {//������� ���������� ��������� ����
	unsigned int k = 0;
	for (int i = 0; i < play_h.row; i++) 
		for (int j = 0; j < play_h.seat_row; j++) 
			if (seats[i][j]) k++;
		
	return k;
}

ostream& operator<<(ostream& stream, play& ob) {//�������� ������ ��� ����������
	cout << "\"" << ob.name << "\"" << endl << string(50,'-') << endl;
	cout << "\t����: " << ob.ganre << endl;
	cout << "\t����: ";
	cout.fill('0');
	cout.width(2);
	cout << ob.date.day << '.';
	cout.width(2);
	cout << ob.date.month << '.';
	//cout.fill(' ');
	cout.fill(' ');
	cout.width(0);
	cout << ob.date.year << endl;
	cout << "\t�����: ";
	cout.fill('0');
	cout.width(2);
	cout << ob.time.hour << ':';
	cout.width(2);
	cout << ob.time.min << endl;
	cout.fill(' ');
	cout.width(0);
	cout << "\t���: " << ob.num_hall << endl;
	cout << "\t���� ������: " << ob.price << endl;
	cout << "\t���������� ��������� ����: " << ob.free_place() << endl;
	cout << string(50, '-');
	return stream;
}

void vivod(string name, Date date, Time time, string num_hall, string ganre, string price) {//�� ����� ����������� ����� ����������, �� ����� ��� ������ ��������� ������� �� �������� ����� ������
	cout << string(40, '-') << endl << "   \"" << name << "\"" << endl;
	cout << "      ����: " << ganre << endl;
	cout << "      ����: ";
	cout.fill('0');
	cout.width(2);
	cout << date.day << '.';
	cout.width(2);
	cout << date.month << '.';
	//cout.fill(' ');
	cout.fill(' ');
	cout.width(0);
	cout << date.year << endl;
	cout << "      �����: ";
	cout.fill('0');
	cout.width(2);
	cout << time.hour << ':';
	cout.width(2);
	cout << time.min << endl;
	cout << "      ���� ������: " << price << endl;
	cout << "      ���: " << num_hall << endl;
	cout << string(40, '-') << endl ;
}

class theater {

	string name;//�������� ������ 
	vector <struct play> play_t;//������ (������) ����������
	int count_halls = 0;//���������� �����
	hall* halls = NULL;//����������� ���������� ���� � ���� � ������ �� �����

public:
	theater();
	theater(string, int, hall[]);
	theater(string, int, hall);
	theater(string);
	theater(theater&);
	~theater() { delete[] halls; halls = nullptr; play_t.clear(); }
	void add_play(string, struct Date, struct Time, string, string, string, string);
	void del_play(string);
	void add_hall(hall);
	void del_hall(int);
	void print_play();
	void print_play(vector<play>&, vector<int>&);
	void print_hall(int);
	void fread(string);
	void fwrite(string, string);
	vector<play> find_name(string, vector<int>&);
	vector<play> find_ganre(string, vector<int>&);
	vector<play> find_day(string, vector<int>&);
	vector<play> find_month(string, vector<int>&);
	vector<play> find_year(string, vector<int>&);
	vector<play> find_hour(string, vector<int>&);
	vector<play> find_date(Date, vector<int>&);
	vector<play> find_time(Time, vector<int>&);
	vector<play> find_hall(int, vector<int>&);
	void book_place(int);
	void sort_time();
	void sort_name();
	void rename();
	auto size() { return play_t.size(); }
	int count_h() { return count_halls; }
	friend theater operator+(theater, theater);
	play operator[](int i) { return play_t[i]; }
	friend ostream& operator<<(ostream&, theater&);
	theater& operator=(const theater&);
};

theater::theater() {//����������� �� ���������
	halls = NULL;
	count_halls = 0;
	name = "";
}

theater::theater(string n, int h, hall hs[]) {//����������� � ��������� �������� ������ � ����������� �����, � ������������ ������� �� ����� � ������� hs
	name = n;
	count_halls = h;
	halls = new hall[count_halls];
	try {
		for (int i = 0; i < count_halls; i++)
			halls[i] = hs[i];
	}
	catch (out_of_range) {
		name = "";
		count_halls = 0;
		delete[] halls;
		std::cout << "������������ ������ ����� ������ ���������� ���������� �����!\n";
	}
	catch (...) {
		name = "";
		count_halls = 0;
		delete[] halls;
		std::cout << "����������� �����������!\n";
	}
}
//1
theater::theater(string file) {//����������� �������� ������� ������ � ������� ������ �� �����
	ifstream in(file);
	string c, count;
	int k = 0;
	if (!(in.is_open())) { cout << "���� " << file << " �� ����� ���� ������!\n"; throw 1; }
	getline(in, name);
	getline(in, count);
	while (my_stoi(count) < 1) {
		cout << "\a���� ������� ����������� ���������� �����!";
		throw 1;
	}
	count_halls = my_stoi(count);
	getline(in, count);
	if (count_halls == 0 && count.empty()) { halls = NULL;  }
	else {
		halls = new hall[count_halls];

		if (count.find(' ') == string::npos && !(count.empty())) { cout << "� ����� " << file << " ��� ����������� ������������!"; throw 1; }
		while (count[0] == ' ') { 
			count.erase(0, 1); 
			if (count.empty()) { cout << "������ ������� ������ �� ��������" << endl; in.close(); throw 1; }
		}
		while (count[count.size() - 1] == ' ') { 
			count.erase(count.size() - 1, 1); 
			if (count.empty()) { cout << "������ ������� ������ �� ��������" << endl; in.close(); throw 1; }
		}
		for (int i = 0; i < count.size(); i++) {
			if (count[i] == ' ') k++;
		}
		if (k != (count_halls * 2) - 1) { cout << "� �����" << file << " ������������� ������������� ��� ���������� ���������� � ������ � �����." << endl; throw 1; }
		for (int i = 0, j = 0; i < count_halls && j < count.length(); i++) {
			c = "";
			while (count[j] != ' ' && j < count.size()) {
				c += count[j];
				j++;
			}
			j++;
			while (!(dig(c))) {
				cout << "\a���� ������� ����������� ���������� ����� ��� ����" << (i + 1) << "! ��������� ������� ����� : \n";
				getline(cin, c);
			}
			halls[i].row = my_stoi(c);
			c = "";
			while (count[j] != ' ' && j < count.size()) {
				c += count[j];
				j++;
			}
			j++;
			while (!(dig(c))) {
				cout << "\a���� ������� ����������� ���������� ���� � ���� ��� ����" << (i + 1) << "! ��������� ������� ����� : \n";
				getline(cin, c);
			}
			halls[i].seat_row = my_stoi(c);
		}
	}
	in.close();
}

theater::theater(string n, int count, hall h) {//����������� ������, ��������� count ���������� ����� � ������������ h(��� ����������� ����� ��������������� �������� ������)
	name = n;
	count_halls = count;
	halls = new hall[count_halls];
	for (int i = 0; i < count_halls; i++) 
		halls[i] = h;
}

theater::theater(theater& copy) {//���������� �����������
	name = copy.name;
	count_halls = copy.count_halls;
	halls = new hall[count_halls];
	play_t = copy.play_t;
	for (int i = 0; i < count_halls; i++)
		halls[i] = copy.halls[i];
}

void theater::sort_time() {
	if (play_t.size() == 0) return;
	play  pr, max;
	
	for (int k = 0; k < (play_t.size() - 1); k++) {

		max = play_t[0];

		for (int i = 0; i < (play_t.size() - k); i++) { //���� max-������

			if (my_stoi(play_t[i].date.year) > my_stoi(max.date.year))
				max = play_t[i];

			else {
				if (my_stoi(play_t[i].date.year) == my_stoi(max.date.year))
					if (my_stoi(play_t[i].date.month) > my_stoi(max.date.month))
						max = play_t[i];

					else {
						if (my_stoi(play_t[i].date.month) == my_stoi(max.date.month))
							if (my_stoi(play_t[i].date.day) > my_stoi(max.date.day))
								max = play_t[i];

							else {
								if (my_stoi(play_t[i].date.day) == my_stoi(max.date.day))
									if (my_stoi(play_t[i].time.hour) > my_stoi(max.time.hour))
										max = play_t[i];

									else {
										if (my_stoi(play_t[i].time.hour) == my_stoi(max.time.hour))
											if (my_stoi(play_t[i].time.min) > my_stoi(max.time.min))
												max = play_t[i];

											else {
												if (my_stoi(play_t[i].time.min) == my_stoi(max.time.min))
													if (play_t[i].num_hall > max.num_hall)
														max = play_t[i];
											}
									}
							}
					}
			}
		}
		
		for (int i = 0; i < play_t.size(); i++) 
			if (max == play_t[i]) {
				pr = play_t[play_t.size() - (static_cast<unsigned long long>(k) + 1)];
				play_t[play_t.size() - (static_cast<unsigned long long>(k) + 1)] = max;
				play_t[i] = pr;
				break;
			}
	}
}
//3
void theater::add_play(string n, struct Date d, struct Time t, string g, string p, string h, string s) {

	if (count_halls == 0) { std::cout << "�� ���������� ����� ��� ��������� ����������! �������� ���!\n"; return; }
	string c;
	short day, month, year;
	string mon_let[12] = { "������", "�������", "����", "������", "���", "����", "����", "������", "���������", "�������", "������", "�������" };
	string num[12] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
	cur_date(day, month, year);
	if (only_let(d.month)) {
		for (int i = 0; i < 12; i++)
			if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
	}
	while (true) //��������� ���� �� ������������
		if (dig(d.day) && dig(d.month) && dig(d.year)) {
			if (my_stoi(d.day) > 31 || my_stoi(d.day) < 1 || (my_stoi(d.year) == year && my_stoi(d.month) == month && my_stoi(d.day) < day)) {
				std::cout << "\a�������� ��� ���� ��������� ��� �������� �����������! \n";
				vivod(n, d, t, h, g, p);
				cout << "��������� ������� ����� ����!" << endl;
			}
			else {
				if (my_stoi(d.month) < 1 || my_stoi(d.month) > 12 || (my_stoi(d.year) == year && my_stoi(d.month) < month)) {
					std::cout << "\a�������� ������ ���� ��������� ��� �������� �����������! \n";
					vivod(n, d, t, h, g, p);
					cout << "��������� ������� ����� ����!" << endl;
				}
				else {
					if (my_stoi(d.year) < year) {
						std::cout << "\a�������� ���� ���� ��������� ��� �������� �����������! \n";
						vivod(n, d, t, h, g, p);
						cout << "��������� ������� ����� ����!" << endl;
					}
					else  break;
				}
			}
			


			std::cout << "��� ���������� ����������: ";
			getline(cin, d.year);
			std::cout << "����� ���������� ����������: ";
			getline(cin, d.month);
			if (only_let(d.month)) {
				
				for (int i = 0; i < 12; i++)
					if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
			}
			std::cout << "���� ���������� ����������: ";
			getline(cin, d.day);


		}
		else {
			std::cout << "\a�������� ���� ���������� ����������� � �������� ����! ��������� ������� �����!\n";
			vivod(n, d, t, h, g, p);
			cout << "��� ���������� ����������: ";
			getline(cin, d.year);
			std::cout << "����� ���������� ����������: ";
			getline(cin, d.month);
			if (only_let(d.month)) {
				
				for (int i = 0; i < 12; i++)
					if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
			}
			std::cout << "���� ���������� ����������: ";
			getline(cin, d.day);
		}
	while (d.day[0] == '0' && d.day.length() > 1) d.day.erase(0, 1);//������� ���������� ����
	while (d.month[0] == '0' && d.month.length() > 1) d.month.erase(0, 1);
	while (d.year[0] == '0') d.year.erase(0, 1);

	while (true)//��������� ��� �� ������������
		if (dig(t.hour)) {
			if (my_stoi(t.hour) > 23 || my_stoi(t.hour) < 0) {
				std::cout << "\a�������� ���� ��������� ��� �������� �����������!"<<endl;
				vivod(n, d, t, h, g, p);
				cout << "��������� ������� ����� ����! \n��� ������ ���������� ����������: " << endl;
				getline(cin, t.hour);
			}
			else break;	
		}
		else {

			std::cout << "\a�������� ���� ���������� ����������� � �������� ����!"<<endl;
			vivod(n, d, t, h, g, p);
			cout << "��������� ������� ����� ����! \n��� ������ ���������� ����������: " << endl;
			getline(cin, t.hour);
		}
	while (t.hour[0] == '0' && t.hour.length() > 1) t.hour.erase(0, 1);//������� ���������� ����
	
	while (true)//��������� ������ �� ������������
		if (dig(t.min)) {
			if (my_stoi(t.min) > 59 || my_stoi(t.min) < 0) {
				std::cout << "\a�������� ������ ��������� ��� �������� �����������!"<<endl;
				vivod(n, d, t, h, g, p);
				cout << "��������� ������� ����� ����! \n������ ������ ���������� ����������: ";
				getline(cin, t.min);
			}
			else break;
		}
		else {
			std::cout << "\a�������� ������ ���������� ����������� � �������� ����!"<<endl;
			vivod(n, d, t, h, g, p);
			cout << "��������� ������� ����� ����! \n������ ������ ���������� ����������: ";
			getline(cin, t.min);
		}
	while (t.min[0] == '0' && t.min.length() > 1) t.min.erase(0, 1);//������� ���������� ����

	while (true)//��������� ���� �� ������������
		if (only_let_cap(g)) break;
		else {
			std::cout << "\a���� ���������� �������� ������������ �������!"<<endl;
			vivod(n, d, t, h, g, p);
			cout << "��������� ������� �����!\n ���� ���������� (���� ����� ������ ���� ��������� �����, ������� ������� ������): ";
			getline(cin, g);
		}


	while (true) //�������� �� ������������ ���� ������
		if (dig_price(p)) break;
		else {
			std::cout << "\a���� ������ �� ���������� ����� ������������ ��������!" << endl;
			vivod(n, d, t, h, g, p);
			cout << " ��������� ������� �����!\n���� ������ �� ����������: ";
			getline(cin, p);
		}

	while (true)//�������� ������������ ��������� ������ ����
		if (dig(h)) {
			if (my_stoi(h) < 1 || my_stoi(h) > count_halls) {
				std::cout << "\a������������ �������� ������ ����!" << endl;
				vivod(n, d, t, h, g, p);
				cout << "��������� ����!\n����� ����, ��� ����� ��������� ����������: ";
				getline(cin, h);
			}
			else break;
		}
		else {
			std::cout << "\a�������� ����� ���� �������� ������������ �������!" << endl;
			vivod(n, d, t, h, g, p);
			cout << "��������� ����!\n����� ����, ��� ����� ��������� ����������: ";
			getline(cin, h);
		}

	for (int i = 0; i < play_t.size(); i++)
		if (play_t[i].date == d && play_t[i].time == t && play_t[i].num_hall == my_stoi(h)) {
			std::cout << "\a� ��������� ���� ��� ������������� ���������� � ��� �����!\n";//�������� ������� ��������� ���������� ������� � �����
			return;
		}
	
	vector<vector<bool>> seats(halls[my_stoi(h) - 1].row, vector<bool>(halls[my_stoi(h) - 1].seat_row, true));
	if (!(s.empty())) {
		while (s[0] == ' ') { s.erase(0, 1); if (s.empty()) return; }
		while (s[s.size() - 1] == ' ') { s.erase(s.size() - 1, 1); if (s.empty()) return;}
		if (!(s.empty())) {
			if (s.find('.') == string::npos) { cout << "\a� �����, � �������� ����������� ������, ��� ����������� ������������ � ������ ��������������� ����!"; throw 3; }
			for (int i = 0, row, st; i < s.length();) {
				c = "";
				while (s[i] != '.') {
					c += s[i];
					i++;
				}
				i++;
				if (my_stoi(c) <= 0 || my_stoi(c) > halls[my_stoi(h) - 1].row) { cout << "\a�������� ��������������� ���� � ���� �� �������� ����������!\n"; throw 3; }
				row = my_stoi(c);
				c = "";
				while (i < s.length() && s[i] != ' ') {
					c += s[i];
					i++;
				}
				i++;
				if (my_stoi(c) <= 0 || my_stoi(c) > halls[my_stoi(h) - 1].seat_row) { cout << "�������� ��������������� ���� �� �������� ����������!\n"; throw 3; }
				st = my_stoi(c);
				seats[row - 1][st - 1] = false;
			}
		}
	}
	play perf(n, d, t, g, p, my_stoi(h), halls[my_stoi(h) - 1]);//������ ������ � ����������
	perf.seats = seats;
	play_t.push_back(perf);//��������� ������ � ��������� � ������ ����������
	sort_time();//��������� ������ ���������� �� �������� (� �� �����)
}

ostream& operator<<(ostream& stream, theater& ob) {
	cout << string(70, '~') << endl;
	cout << "�������� ������: \"" << ob.name << '\"' << endl;
	cout << string(18, ' ') << "���������� ������� � �����������: " << ob.play_t.size() << endl;
	for (int i = 0; i < ob.count_halls; i++) {
		cout << string(18, ' ') << "��� " << (i + 1) << ":" << endl;
		cout << string(26, ' ') << "���������� �����: " << ob.halls[i].row << endl;
		cout << string(26, ' ') << "���������� ���� � ����� ����: " << ob.halls[i].seat_row << endl;
	}
	cout << string(70, '~') << endl << endl;
	return stream;
}

theater& theater::operator=(const theater& ob) {
	if (this != &ob) {
		delete[] halls;
		name = ob.name;
		count_halls = ob.count_halls;
		halls = new hall[count_halls];
		for (int i = 0; i < count_halls; i++) {
			halls[i] = ob.halls[i];
		}
		play_t = ob.play_t;
	}
	return *this;
}
//2
void theater::fread(string filename) {//��������� ������ ����������
	ifstream in(filename);
	string n, g, h, p, let, s;
	Date d;
	Time t;
	int i = 0, k;

	if (!(in.is_open())) { cout << "\a���� " << filename << " �� ����� ���� ������!\n"; throw 2; }
	while (!(in.eof())) {
		k = 0;
		getline(in, n);
		getline(in, let);
		if (let.find('.') == string::npos) { cout << "\a� ����� " << filename << " ������� ������������ ��� ���� ���������!\n"; in.close(); return; }
		for (int j = 0; j < let.length(); j++) 
			if (let[j] == '.') k++;
		if(k != 2) { cout << "\a� ����� " << filename << " ������� ������������ ��� ���� ���������!\n"; in.close(); return; }
		while (let[i] != '.') {
			d.day += let[i];
			i++;
		}
		i++;
		while (let[i] != '.') {
			d.month += let[i];
			i++;
		}
		i++;
		while (i != let.size()) {
			d.year += let[i];
			i++;
		}
		i = 0;
		getline(in, let);
		if (let.find(':') == string::npos) { cout << "\a� ����� " << filename << " ������� ������������ ��� ������� ���������!\n"; in.close();  throw 4; }
		while (let[i] != ':') {
			t.hour += let[i];
			i++;
		}
		i++;
		while (i != let.size()) {
			t.min += let[i];
			i++;
		}
		i = 0;
		getline(in, g);
		getline(in, p);
		getline(in, h);
		getline(in, s);
		getline(in, let);
		try { add_play(n, d, t, g, p, h, s); }
		catch (int i) { cout << "�� ��������� � �������� ���� � ����� ������ " << i << endl; in.close(); return; }
		n = "";
		d.day = ""; d.month = ""; d.year = "";
		t.hour = ""; t.min = "";
		g = ""; p = ""; let = ""; h = ""; s = "";
	}
	in.close();
}

void theater::fwrite(string filename_t, string filename_p) {//���������� ������ � ������ � ������ ����������
	ofstream out_t(filename_t);
	if (!(out_t.is_open())) { cout << "\a������ �������� ����� " << filename_t << " !\n"; return;}
	ofstream out_p(filename_p);
	if (!(out_p.is_open())) { cout << "\a������ �������� ����� " << filename_p << " !\n"; return; }

	out_t << name << endl;
	out_t << count_halls << endl;
	for (int i = 0; i < count_halls; i++) 
		out_t << halls[i].row << ' ' << halls[i].seat_row << ' ';
	out_t.close();

	for (int i = 0; i < play_t.size(); i++) {
		out_p << play_t[i].name << endl;
		out_p << play_t[i].date.day << '.' << play_t[i].date.month << '.' << play_t[i].date.year << endl;
		out_p << play_t[i].time.hour << ':' << play_t[i].time.min << endl;
		out_p << play_t[i].ganre << endl;
		out_p << play_t[i].price << endl;
		out_p << play_t[i].num_hall << endl;
		for (int j = 0; j < play_t[i].play_h.row; j++) 
			for (int k = 0; k < play_t[i].play_h.seat_row; k++) 
				if (!(play_t[i].seats[j][k])) 
					out_p << (j + 1) << '.' << (k + 1) << ' '; 
		out_p << endl;
		out_p << endl;
	}
	out_p.close();
}

void theater :: print_play() {//������� ������ ���� ���������� ������
	if (play_t.empty()) { cout << "������ �� �������." << endl; return; }
	cout << "������ ����������: " << endl;
	cout << string(50, '-') << endl;
	for (int i = 0; i < play_t.size(); i++)
		cout << ' ' << (i + 1) << ". " << play_t[i] << endl;
}

void theater :: print_play(vector<play>& play_list, vector<int>& index) {//������� �����-�� ����������� ��������� ������
	if (play_list.empty()) { cout << "������ �� �������." << endl; return; }
	cout << "������ ����������: " << endl;
	cout << string(50, '-') << endl;
	for (int i = 0; i < play_list.size(); i++)
		cout << ' ' << index[i] << ". " << play_list[i] << endl;
}

vector<play> theater::find_name(string str, vector<int>& index) {//������� ��������� �� ������� ����������, ������� ������� ���
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++) 
		if (lowercase(play_t[i].name).find(lowercase(str)) != string::npos) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

vector<play> theater::find_ganre(string str, vector<int>& index) {//������� ��������� �� ������� ����������, ������� ������� �� ��������� ����
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++)
		if (lowercase(play_t[i].ganre).find(lowercase(str)) != string::npos) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

vector<play> theater::find_day(string day, vector<int>& index) {////������� ��������� �� ������� ����������, ������� ������ �������� ��� ���� ����������
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++) 
		if (play_t[i].date.day.find(day) != string::npos) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

vector<play> theater::find_month(string month, vector<int>& index) {//������� ��������� �� ������� ����������, ������� �������� ������
	vector<play> p;
	if (!(index.empty())) index.clear();
	if (only_let(month)) {
		string mon_let[12] = { "������", "�������", "����", "������", "���", "����", "����", "������", "���������", "�������", "������", "�������" };
		int k[12] = {}, j = 0;
		for (int i = 0; i < 12; i++) 
			if (lowercase(mon_let[i]).find(lowercase(month)) != string::npos) {
				k[j] = i + 1;
				j++;
			}
		for (int i = 0; i < play_t.size(); i++) 
			for (int z = 0; z < j; z++) 
				if (my_stoi(play_t[i].date.month) == k[z]) {
					p.push_back(play_t[i]);
					index.push_back(i + 1);
				}
	}
	else {
		for (int i = 0; i < play_t.size(); i++)
			if (play_t[i].date.month.find(month) != string::npos) {
				p.push_back(play_t[i]);
				index.push_back(i + 1);
			}
	}
	return p;
}

vector<play> theater::find_year(string year, vector<int>& index) {//������� ��������� �� ������� ����������, ������� ������� �������� ����
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++)
		if (play_t[i].date.year.find(year) != string::npos) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

vector<play> theater::find_hour(string hour, vector<int>& index) {//������� ��������� �� ������� ����������, ������� ������� �������� ����
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++)
		if (play_t[i].time.hour.find(hour) != string::npos) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

vector<play> theater::find_date(Date date, vector<int>& index) {
	vector<play> p, play_d, play_m, play_y;
	play_d = find_day(date.day,index);
	play_m = find_month(date.month,index);
	play_y = find_year(date.year,index);
	index.clear();
	for (int i = 0, df = 0, mf = 0, yf = 0; i < play_t.size(); i++, df = 0, mf = 0, yf = 0) {
		for (int j = 0; j < play_d.size(); j++) 
			if (play_t[i] == play_d[j]) {
				df = 1; 
				break;
			}
		for (int j = 0; j < play_m.size(); j++) 
			if (play_t[i] == play_m[j]) {
				mf = 1;
				break;
			}
		for (int j = 0; j < play_y.size(); j++) 
			if (play_t[i] == play_y[j]) {
				yf = 1;
				break;
			}
		if (df == 1 && mf == 1 && yf == 1) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	}
	return p;
}

vector<play> theater::find_time(Time time, vector<int>& index) {
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++) 
		if (play_t[i].time.hour.find(time.hour) != string::npos && play_t[i].time.min.find(time.min) != string::npos) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

vector<play> theater::find_hall(int num, vector<int>& index) {
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++) 
		if (play_t[i].num_hall == num) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

void theater::print_hall(int index) {//�������� ��� ��� ��������� �� ������� ����������
	string m;
	int f = 0;
	while (true) {
		cout << "����� �������� �� ������ ���������� ���?" << endl << "  1 - �����������" << endl << "  2 - ���������" << endl << "  0 - �����  �� ������" << endl << "������� ��������: ";
		getline(cin, m);
		if (m == "1") {
			if (play_t[index-1].play_h.seat_row <= 999) {
				cout << endl << "�������� �����������:\n";
				cout.width(42);
				cout << "* - ��������� �����\n";
				cout.width(47);
				cout << "# - ��������������� �����" << endl << endl;
				for (int k = 0; k < (play_t[index-1].play_h.seat_row / 50) + fun(play_t[index-1].play_h.seat_row); k++) {//����������� ������ ������ ����
					if (play_t[index-1].play_h.seat_row > 50) cout << (k + 1) << "-�� ����� ����: " << endl;
					cout << "������";
					for (int i = k * 50, n = 1; (i < (play_t[index-1].play_h.seat_row)) && ((i + n) % 50 != 0); i++, n = 0) {
						cout.width(4);
						cout << i + 1;
					}
					cout << endl;
					cout << "���� " << endl;
					for (int i = 0; i < play_t[index-1].play_h.row; i++) {
						cout.width(7);
						cout << (i + 1) << "  ";
						for (int j = k * 50, n = 1; (j < play_t[index-1].play_h.seat_row) && ((j + n) % 50 != 0); j++, n = 0) {
							if (play_t[index-1].seats[i][j] == true)
								cout << "*   ";
							else
								cout << "#   ";
						}
						cout << endl;
					}
					cout << endl;
				}
			}
			else { cout << "��� ������� �������, ������� �� ����� ���� ������� ����������. ���������� �������� �����.\n"; }
		}
		else if (m == "2") {
			while (true) {//��������� ������ ������ ����
				f = 0;
				cout << "������� ����� ���� �� " << 1 << " �� " << play_t[index-1].play_h.row << ", ����� ������, ����� ����� � �� �������� (��� \'0\', ����� ����� �� ������): ";
				getline(cin, m);
				if (m == "0") break;
				if (my_stoi(m) > 0 && my_stoi(m) <= play_t[index-1].play_h.row) {
					cout << "��������� ����� ���� " << m << ": ";
					for (int i = 0, s = 0; i < play_t[index-1].play_h.seat_row; i++) 
						if (play_t[index-1].seats[my_stoi(m) - 1][i]) {
							cout << (i + 1);
							if (i != (play_t[index-1].play_h.seat_row - 1)) cout << ", ";
							else cout << ". " << endl;
							if (s == 35) { cout << endl; s = 0; }
							f = 1;
							s++;
						}
					
					if (f == 0) cout << "��� ����� �������������. ���������� ������ ������ ���." << endl;
				}
				else cout << "������� ��� �� ����������. ��������� ������� �����.\n";
			}
		}
		else if (m == "0") break;
		else { cout << "�� ����� ��������, �� �������������� ������� ����. ��������� ������� �����.\n"; }
	}
}

void theater::book_place(int index) {//������������ ����� �� ����������(�������� ���������� �����)
	string row, seat, f;
	cout << string(50, '-') << endl << play_t[index-1] << endl;
	while (true) {
		cout << "�������� ��������� ���.\n  1 - ������������� �����\n  2 - ������� ��� ����������\n  0 - ����� �� ������" << endl << "�������� ������������� ����� ����: ";
		getline(cin, f);
		if (f == "1") {
			while (true) {
				cout << "�������� ���, � ������� ������ ������ �����: ";
				getline(cin, row);
				if (my_stoi(row) > 0 && my_stoi(row) <= play_t[index-1].play_h.row) break;
				else cout << "������� ������������ ������. ��������� ������� �����.\n";
			}
			while (true) {
				cout << "�������� ����� � ���� " << row << " ������� ������ �������������: ";
				getline(cin, seat);
				if (my_stoi(seat) > 0 && my_stoi(seat) <= play_t[index-1].play_h.seat_row) break;
				else cout << "������� ������������ ������. ��������� ������� �����.\n";
			}
			if (play_t[index-1].seats[my_stoi(row) - 1][my_stoi(seat) - 1]) {
				play_t[index-1].seats[my_stoi(row) - 1][my_stoi(seat) - 1] = false;
				cout << "����� ������� �������������!\n";
			}
			else { cout << "����� ��� �������������.\n"; }
		}
		else if (f == "2") print_hall(index);
		else if (f == "0") break;
		else cout << "��� ����������� ������ ����." << endl;
	}
}

void theater::del_play(string index) {//������� ������ � ����������
	if (play_t.size() == 0 || my_stoi(index) < 1 || my_stoi(index) > play_t.size()) { cout << "\a� ������ ��� �� ����� ����������!\n"; return; }
	vector<play> double_play;
	string s;
	int k = my_stoi(index) - 1;
	cout << string(50, '-') << endl << play_t[k] << "\n" << "�� ������� ��� ������ ������� ������ � ����������?\n";
	cout << string(66, ' ') << "1 - ��\n";
	cout << string(44,' ') << "{����� ������ ��������} - ���\n������� �������������� ����� ����: ";
	getline(cin, s);
	if (my_stoi(s) == 1) {
		for (int i = 0; i < k; i++) double_play.push_back(play_t[i]);
		for (int i = (k + 1); i < play_t.size(); i++) double_play.push_back(play_t[i]);
		play_t = double_play;
	}
	else  return; 
}

void theater::del_hall(int num) {//������� ��� � ������� num (���� �� 1)
	int f = 0;
	string h;
	for (int i = 0; i < play_t.size(); i++)
		if ((play_t[i].num_hall == num) && ((play_t[i].play_h.row * play_t[i].play_h.seat_row) != (play_t[i].free_place()))) {
			f = 1;
			break;
		}
	if (f == 1) { cout << "� ��������� ���� ��� ������������� ����� �� ����������� ����������. �� ���������� ���������� ���������� ������� ���.\n"; return; }
	if ((count_halls - 1) != 0) {
		for (int i = 0; i < play_t.size(); i++) {
			if (play_t[i].num_hall == num) {
				cout << "���������� ����������� ����������� � ��������� ����.\n" << string(50, '-') << endl << play_t[i] << endl << "�������� ��� ������ ���������� ���������� ����: ";
				getline(cin, h);
				while (my_stoi(h) < 1 || my_stoi(h) == num || my_stoi(h) > count_halls) {
					cout << "��� ��� ������ ���������� �� ����� ���� ������ ��������� �����. ��������� ������� �����." << endl;
					cout << "�������� ��� ������ ���������� ���������� ����: ";
					getline(cin, h);
				}
				play_t[i].num_hall = my_stoi(h);
				play_t[i].play_h = halls[my_stoi(h) - 1];
				vector<vector<bool>> s(play_t[i].play_h.row, vector<bool>(play_t[i].play_h.seat_row, true));
				play_t[i].seats = s;
			}
		}
		hall* new_hall = new hall[(count_halls - 1)];
		for (int i = 0; i < (num - 1); i++)
			new_hall[i] = halls[i];
		for (int i = num; i < count_halls; i++)
			new_hall[i-1] = halls[i];
		delete[] halls;
		halls = new_hall;
		count_halls--;
	}
	else if (play_t.empty()) { delete[] halls; halls = NULL; }
	else { cout << "���������� ������� ������������ ���, ��� ��� ��� ����������� ��������� ���������� � ������ �����\n"; return; }
}

void theater::add_hall(hall h) {//��������� ����������
	count_halls++;
	hall* new_hall = new hall[count_halls];
	for (int i = 0; i < (count_halls - 1); i++) 
		new_hall[i] = halls[i];
	new_hall[(count_halls - 1)] = h;
	delete[] halls;
	halls = new_hall;
}

void theater::sort_name() {//��������� �� ����� ��������� (�� ��������)
	if (play_t.size() == 0) return;
	string max;
	play pr;
	for (int k = 0; k < (play_t.size()-1); k++) {
		max = play_t[0].name;
		for (int i = 0; i < (play_t.size() - k); i++) 
			if (play_t[i].name > max) max = play_t[i].name;
		for (int i = 0; i < (play_t.size() - k); i++) 
			if (play_t[i].name == max) {
				pr = play_t[play_t.size() - (k + 1)];
				play_t[play_t.size() - (k + 1)] = play_t[i];
				play_t[i] = pr;
				break;
			}
	}
}

theater operator+(theater ob1, theater ob2) {//������ ����� ������ ������ theater, ������� �������� � ���� ��� ������ �������, ��� � ������ ������� ��������
	theater ob;
	cout << "������� ������������ ������, ������� ��������� � ���������� ��������: ";
	getline(cin, ob.name);
	ob.count_halls = ob1.count_halls + ob2.count_halls;
	ob.halls = new hall[ob.count_halls];
	for (int i = 0; i < ob1.count_halls; i++) 
		ob.halls[i] = ob1.halls[i];
	for (int i = 0, j = ob1.count_halls; i < ob2.count_halls; i++, j++)
		ob.halls[j] = ob2.halls[i];
	for (int i = 0; i < ob2.play_t.size(); i++) 
		ob2.play_t[i].num_hall += ob1.count_halls;
	vector<play> pr(ob1.play_t);
	for (int i = 0; i < ob2.play_t.size(); i++)
		pr.push_back(ob2.play_t[i]);
	ob.play_t = pr;
	ob.sort_time();
	return ob;
}

void theater::rename() {//�������� �������� ������
	cout << "������� ����� ��� ������: ";
	getline(cin, name);
}

void menu1() {//����� ���������� ����
	cout << endl << string(120, '*') << endl << "��������� ����." << endl;
	cout << string(8, ' ') << "�������� ������� ������ ob theater.\n";
	cout << string(8, ' ') << "1 - ����������� �� ���������\n";
	cout << string(8, ' ') << "2 - ����������� � �������� � ������������ ������������ ����� �����\n";
	cout << string(8, ' ') << "3 - �����������, ��������� ����������� ����� ���������� �����\n";
	cout << string(8, ' ') << "4 - �����������, ����������� ������ � �����\n";
	cout << string(8, ' ') << "0 - �����\n" << string(120, '*') << "\n\n";
}

void menu_ob1() {//����� ���� �������� �������� �������
	cout << endl << string(120, '*') << endl;
	cout << string(8, ' ') << "�������� ������� ob1 ������ theater.\n";
	cout << string(8, ' ') << "1 - ����������� �� ���������\n";
	cout << string(8, ' ') << "2 - ����������� � �������� � ������������ ������������ ����� �����\n";
	cout << string(8, ' ') << "3 - �����������, ��������� ����������� ����� ���������� �����\n";
	cout << string(8, ' ') << "4 - �����������, ����������� ������ � �����\n";
	cout << string(8, ' ') << "0 - �����\n" << string(120, '*') << "\n\n";
}

void menu2() {//����� ��������� ����
	cout << endl << string(120, '*') << endl << "�������� ����." << endl;
	cout << "������ � �������� (ob) ������ theater.\n";
	cout << string(8, ' ') << "1 - ������� ������ � ������\n";
	cout << string(8, ' ') << "2 - ������� ������ ����������\n";
	cout << string(8, ' ') << "3 - �������� ����������\n";
	cout << string(8, ' ') << "4 - ������� ���������� �� ����������� ������\n";
	cout << string(8, ' ') << "5 - ������� ������ � ����������� � �����\n";
	cout << string(8, ' ') << "6 - �������� ������ � ������ � ����������� � �����\n";
	cout << string(8, ' ') << "7 - ����� ���������� �� ��������\n";
	cout << string(8, ' ') << "8 - ����� ���������� �� �����\n";
	cout << string(8, ' ') << "9 - ����� ���������� �� ��� � ������ ����������\n";
	cout << string(8, ' ') << "10 - ����� ���������� �� ������ ����������\n";
	cout << string(8, ' ') << "11 - ����� ���������� �� ���� ����������\n";
	cout << string(8, ' ') << "12 - ����� ���������� �� ���� ������ ����������\n";
	cout << string(8, ' ') << "13 - ����� ���������� �� ���� ����������\n";
	cout << string(8, ' ') << "14 - ����� ���������� �� ������� ����������\n";
	cout << string(8, ' ') << "15 - ����� ���������� �� ����\n";
	cout << string(8, ' ') << "16 - ������������� ����� �� ����������\n";
	cout << string(8, ' ') << "17 - ������������� ������ ���������� �� ������� (��������� �� ���������)\n";
	cout << string(8, ' ') << "18 - ������������� ������ ���������� �� ��������\n";
	cout << string(8, ' ') << "19 - �������� �������� ������\n";
	cout << string(8, ' ') << "20 - �������� ���\n";
	cout << string(8, ' ') << "21 - ������� ��� �� ����������� ������\n";
	cout << string(8, ' ') << "22 - �������� ���������� ������� �������. ������� ������ � ���������� �� �������\n";
	cout << string(8, ' ') << "23 - �������� ���������� ������� � �����������\n";
	cout << string(8, ' ') << "24 - ��������� ���������� ����������. �������� ������� ������� ������ theater (ob1).\n";
	cout << string(8, ' ') << "0 - ��������� � ��������� ����\n" << string(120, '*') << "\n\n";
}

void menu3() {//���� ����������
	cout << endl << string(120, '*') << "\n���� ����������� \'+\' � \'=\'.\n";
	cout << string(8,' ') << "1 - ������� ������ ������� ob\n";
	cout << string(8, ' ') << "2 - ������� ������ ���������� ob\n";
	cout << string(8, ' ') << "3 - ������� ������ ������� ob1\n";
	cout << string(8, ' ') << "4 - ������� ������ ���������� ob1\n";
	cout << string(8, ' ') << "5 - �������� ���������� ��� ob1\n";
	cout << string(8, ' ') << "6 - ������� ������ � ����������� � ����� ��� ob1\n";
	cout << string(8, ' ') << "7 - ������� ������ ������� ob2\n";
	cout << string(8, ' ') << "8 - ������� ������ ���������� ob2\n";
	cout << string(8, ' ') << "9 - ��������� ������� ob2 ������ ob\n";
	cout << string(8, ' ') << "10 - ������� ������� ob � ob1 � ��������� ��������� ������� ob2\n";
	cout << string(8, ' ') << "0 - ��������� � �������� ����\n" << string(120, '*') << "\n\n";
}

void constr1(theater& ob) {
	string n, count, k;
	cout << "������� ������������ ������: ";
	getline(cin, n);
	cout << "������� ���������� ����� ������������ ������: ";
	getline(cin, count);
	while (my_stoi(count) < 1) {
		cout << "������� ����������� ���������� �����. ��������� ������� �����.\n������� ���������� ����� ������������ ������: ";
		getline(cin, count);
	}
	hall* halls = new hall[my_stoi(count)];
	for (int i = 0; i < my_stoi(count); i++) {
		std::cout << "���������� ����� � ���� " << i + 1 << ": ";
		getline(cin, k);
		while (my_stoi(k) < 1) {
			std::cout << "�� ����� ����������� ���������� �����! ��������� ������� �����!\n" << "���������� ����� � ���� " << (i + 1) << ": ";
			getline(cin, k);
		}
		halls[i].row = my_stoi(k);
		std::cout << "���������� ���� � ����� ���� ���� " << i + 1 << ": ";
		getline(cin, k);
		while (my_stoi(k) < 1) {
			std::cout << "�� ����� ����������� ���������� ���� ����! ��������� ������� �����!\n" << "���������� ���� � ����� ���� ���� " << (i + 1) << ": ";
			getline(cin, k);
		}
		halls[i].seat_row = my_stoi(k);
	}
	theater ob1(n, my_stoi(count), halls);
	delete[] halls;
	ob = ob1;
}

void constr2(theater& ob) {
	string n, count, k;
	hall h;
	cout << "������� ������������ ������: ";
	getline(cin, n);
	cout << "������� ���������� ����� � ����������� ���������������� ��� ������������ ������: ";
	getline(cin, count);
	while (my_stoi(count) < 1) {
		cout << "������� ����������� ���������� �����. ��������� ������� �����.\n������� ���������� ����� � ����������� ���������������� ��� ������������ ������: ";
		getline(cin, count);
	}
	cout << "����������� ������������ �����. \t������� ���������� �����: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "\t������� ����������� ����� ����� � ����. ��������� ������� �����\n\t������� ���������� �����: ";
		getline(cin, k);
	}
	h.row = my_stoi(k);
	cout << "\t������� ���������� ���� � ����� ����: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "\t������� ����������� ����� ���� � ����. ��������� ������� �����\n\t������� ���������� ���� � ����: ";
		getline(cin, k);
	}
	h.seat_row = my_stoi(k);
	theater ob1(n, my_stoi(count), h);
	ob = ob1;
}

void add_p(theater& ob) {
	if (ob.count_h() == 0) { cout << "��� ����� ��� ���������� ����������. �������� ���.\n"; return; }
	string n, g, p, h;
	Date d;
	Time t;
	short day, month, year;
	cur_date(day, month, year);
	string mon_let[12] = { "������", "�������", "����", "������", "���", "����", "����", "������", "���������", "�������", "������", "�������" };
	string num[12] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
	cout << "������� ������������ ����������� ����������: ";
	getline(cin, n);
	cout << "������� ���� ����������� ����������: ";
	getline(cin, g);
	while (true)//��������� ���� �� ������������
		if (only_let_cap(g)) break;
		else {
			std::cout << "\a���� ���������� �������� ������������ �������!" << endl;
			vivod(n, d, t, h, g, p);
			cout << "��������� ������� �����!\n ���� ���������� (���� ����� ������ ���� ��������� �����, ������� ������� ������): ";
			getline(cin, g);
		}
	cout << "������� ��� ���������� ����������� ����������: ";
	getline(cin, d.year);
	cout << "������� ����� ���������� ����������� ����������: ";
	getline(cin, d.month);
	if (only_let(d.month)) {
		for (int i = 0; i < 12; i++) 
			if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
	}
	cout << "������� ���� ���������� ����������� ����������: ";
	getline(cin, d.day);
	while (true) //��������� ���� �� ������������
		if (dig(d.day) && dig(d.month) && dig(d.year)) {
			if (my_stoi(d.day) > 31 || my_stoi(d.day) < 1 || (my_stoi(d.year) == year && my_stoi(d.month) == month && my_stoi(d.day) < day)) {
				std::cout << "\a�������� ��� ���� ��������� ��� �������� �����������! \n";
				vivod(n, d, t, h, g, p);
				cout << "��������� ������� ����� ����!" << endl;
			}
			else {
				if (my_stoi(d.month) < 1 || my_stoi(d.month) > 12 || (my_stoi(d.year) == year && my_stoi(d.month) < month)) {
					std::cout << "\a�������� ������ ���� ��������� ��� �������� �����������! \n";
					vivod(n, d, t, h, g, p);
					cout << "��������� ������� ����� ����!" << endl;
				}
				else {
					if (my_stoi(d.year) < year) {
						std::cout << "\a�������� ���� ���� ��������� ��� �������� �����������! \n";
						vivod(n, d, t, h, g, p);
						cout << "��������� ������� ����� ����!" << endl;
					}
					else  break;
				}
			}
			std::cout << "��� ���������� ����������: ";
			getline(cin, d.year);
			std::cout << "����� ���������� ����������: ";
			getline(cin, d.month);
			if (only_let(d.month)) {
				for (int i = 0; i < 12; i++)
					if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
			}
			std::cout << "���� ���������� ����������: ";
			getline(cin, d.day);
		}
		else {
			std::cout << "\a�������� ���� ���������� ����������� � �������� ����! ��������� ������� �����!\n";
			vivod(n, d, t, h, g, p);
			cout << "��� ���������� ����������: ";
			getline(cin, d.year);
			std::cout << "����� ���������� ����������: ";
			getline(cin, d.month);
			if (only_let(d.month)) {

				for (int i = 0; i < 12; i++)
					if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
			}
			std::cout << "���� ���������� ����������: ";
			getline(cin, d.day);
		}

	cout << "������� ��� ������ ���������� ����������� ����������: ";
	getline(cin, t.hour);
	while (true)//��������� ��� �� ������������
		if (dig(t.hour)) {
			if (my_stoi(t.hour) > 23 || my_stoi(t.hour) < 0) {
				std::cout << "\a�������� ���� ��������� ��� �������� �����������!" << endl;
				vivod(n, d, t, h, g, p);
				cout << "��������� ������� ����� ����! \n��� ������ ���������� ����������: " << endl;
				getline(cin, t.hour);
			}
			else break;
		}
		else {

			std::cout << "\a�������� ���� ���������� ����������� � �������� ����!" << endl;
			vivod(n, d, t, h, g, p);
			cout << "��������� ������� ����� ����! \n��� ������ ���������� ����������: " << endl;
			getline(cin, t.hour);
		}
	
	cout << "������� ������ ������ ���������� ����������� ����������: ";
	getline(cin, t.min);
	while (true)//��������� ������ �� ������������
		if (dig(t.min)) {
			if (my_stoi(t.min) > 59 || my_stoi(t.min) < 0) {
				std::cout << "\a�������� ������ ��������� ��� �������� �����������!" << endl;
				vivod(n, d, t, h, g, p);
				cout << "��������� ������� ����� ����! \n������ ������ ���������� ����������: ";
				getline(cin, t.min);
			}
			else break;
		}
		else {
			std::cout << "\a�������� ������ ���������� ����������� � �������� ����!" << endl;
			vivod(n, d, t, h, g, p);
			cout << "��������� ������� ����� ����! \n������ ������ ���������� ����������: ";
			getline(cin, t.min);
		}

	cout << "������� ����� ����, ��� ����� ��������� ����������� ����������: ";
	getline(cin, h);
	while (true)//�������� ������������ ��������� ������ ����
		if (dig(h)) {
			if (my_stoi(h) < 1 || my_stoi(h) > ob.count_h()) {
				std::cout << "\a������������ �������� ������ ����!" << endl;
				vivod(n, d, t, h, g, p);
				cout << "��������� ����!\n����� ����, ��� ����� ��������� ����������: ";
				getline(cin, h);
			}
			else break;
		}
		else {
			std::cout << "\a�������� ����� ���� �������� ������������ �������!" << endl;
			vivod(n, d, t, h, g, p);
			cout << "��������� ����!\n����� ����, ��� ����� ��������� ����������: ";
			getline(cin, h);
		}

	cout << "������� ���� �� ����� ��� ����������� ����������: ";
	getline(cin, p);
	while (true) //�������� �� ������������ ���� ������
		if (dig_price(p)) break;
		else {
			std::cout << "\a���� ������ �� ���������� ����� ������������ ��������!" << endl;
			vivod(n, d, t, h, g, p);
			cout << " ��������� ������� �����!\n���� ������ �� ����������: ";
			getline(cin, p);
		}
	ob.add_play(n, d, t, g, p, h, "");
}

void del_p(theater& ob) {
	string index;
	cout << "������� ���������� ����� ��������� ����������: ";
	getline(cin, index);
	ob.del_play(index);
}

void write_t(theater& ob) {
	string filename_t, filename_p;
	cout << "������� ������������ �����, � ������� ������� �������� ������ � ������: ";
	getline(cin, filename_t);
	cout << "������� ������������ �����, � ������� ������� �������� ������ � �����������: ";
	getline(cin, filename_p);
	ob.fwrite(filename_t, filename_p);
}

void f_date(theater& ob) {
	vector<int> index;
	vector<play> p;
	Date d;
	cout << "������� ��� ���������� ������� ����������: ";
	getline(cin, d.year);
	cout << "������� ����� ���������� ������� ����������: ";
	getline(cin, d.month);
	cout << "������� ���� ���������� ������� ����������: ";
	getline(cin, d.day);
	p = ob.find_date(d, index);
	ob.print_play(p, index);
}

void f_time(theater& ob) {
	vector<int> index;
	vector<play> p;
	Time t;
	cout << "������� ��� ������ ���������� ������� ����������: ";
	getline(cin, t.hour);
	cout << "������� ������ ������ ��������� ������� ����������: ";
	getline(cin, t.min);
	p = ob.find_time(t, index);
	ob.print_play(p, index);
}

void f_hall(theater& ob) {
	string k; 
	vector<play> p;
	vector<int> index;
	cout << "������� ����� ����, �� �������� ������ ������������� ������ ����������: ";
	getline(cin, k);
	while (my_stoi(k) < 1 || my_stoi(k) > ob.count_h()) {
		cout << "������� ������������ ��� ���� ��������. ��������� ����: ";
		getline(cin, k);
	}
	p = ob.find_hall(my_stoi(k), index);
	ob.print_play(p, index);
}

void book_p(theater& ob) {
	if (ob.size() == 0) { cout << "\a� ������ ��� �� ����� ����������!\n"; return; }
	string num;
	cout << "������� ���������� ����� ����������, ��� ������� ������ ������������� �����: ";
	getline(cin, num);
	while (my_stoi(num) < 1 || my_stoi(num) > ob.size()) {
		cout << "����� ������������ ���������� �����. ��������� ������� �����.\n������� ���������� ����� ����������, ��� ������� ������ ������������� �����: ";
		getline(cin, num);
	}
	ob.book_place(my_stoi(num));
}

void add_h(theater& ob) {
	hall h;
	string k;
	cout << "������� ���������� ����� ������������ ����: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "������� ������������ �������� ����� ����� ������������ ����. ��������� ������� �����.\n������� ���������� ����� ������������ ����: ";
		getline(cin, k);
	}
	h.row = my_stoi(k);
	cout << "������� ���������� ���� � ����� ���� ������������ ����: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "������� ������������ �������� ����� ���� � ���� ������������ ����. ��������� ������� �����.\n������� ���������� ���� ���� ������������ ����: ";
		getline(cin, k);
	}
	h.seat_row = my_stoi(k);
	ob.add_hall(h);
}

void del_h(theater& ob) {
	if (ob.count_h() == 0) { cout << "\a� ������ ��� �� ������ ����!\n"; return;  }
	string k;
	cout << "������� ���������� ����� ����, ������� ������ �������: ";
	getline(cin, k);
	while (my_stoi(k) < 1 || my_stoi(k) > ob.count_h()) {
		cout << "����� ������������ ���������� ����� ���������� ����. ��������� �������.\n������� ���������� ����� ����, ������� ������ �������: ";
		getline(cin, k);
	}
	ob.del_hall(my_stoi(k));
}

void ind(theater& ob) {
	if (ob.size() == 0) { cout << "\a� ������ ��� �� ����� ����������!\n"; return; }
	string k;
	cout << "������� ������ ������, ������� ���� ������� �� �������: ";
	getline(cin, k);
	while (my_stoi(k) < 0 || my_stoi(k) >= ob.size()) {
		cout << "�������� ������ ������� �� ������� ������� ����������. ��������� ������� �����: ";
		getline(cin, k);
	}
	play p = ob[my_stoi(k)];
	cout << string(50, '-')<<"\n "<<k<<". " << p << endl;
}

void fun_menu3(theater& ob) {//���������� ����������
	string k = "5";
	int f = 0;
	theater ob1, ob2;
	while (my_stoi(k) < 0 || my_stoi(k) > 4) {
		try {
			menu_ob1();
			cout << "������� �������������� ����� ����: ";
			getline(cin, k);
			switch (my_stoi(k)) {
			case 0: { break; }
			case 1: { break; }
			case 2: {theater ob3; constr1(ob3); ob1 = ob3; ob3.~theater(); break; }
			case 3: {theater ob3; constr2(ob3); ob1 = ob3; ob3.~theater(); break; }
			case 4: {cout << "������� ������������ �����, � �������� ������ ������� ������ ��� ������: "; getline(cin, k);  theater ob3(k); ob1 = ob3; ob3.~theater(); k = "2"; break; }
			default: {cout << "�� ������� ������������� ����� ����.\n"; }
			}
		}
		catch (int i) { cout << "�� ��������� � �������� ���� ���� � ����� ������ " << i << endl; ob1.~theater(); ob2.~theater(); f = 1; break;}
		catch (...) { cout << "������� ����������� ����������.�� ��������� � �������� ���� ����.\n"; ob1.~theater(); ob2.~theater(); f = 1; break;}
	}
	if (f == 0 && k != "0") {
		menu3();
		cout << "������� �������������� ����� ����: ";
		getline(cin, k);
		while (k != "0") {
			try {
				switch (my_stoi(k)) {
				case 1: {cout << ob << endl; break; }
				case 2: {ob.print_play(); break; }
				case 3: {cout << ob1 << endl; break; }
				case 4: {ob1.print_play(); break; }
				case 5: {cout << "������� ������������ �����, � �������� ������� ������� ������ � �����������: "; getline(cin, k); ob.fread(k); k = "5"; break; }
				case 6: {add_p(ob1); break; }
				case 7: { cout << ob2 << "\n"; break; }
				case 8: { ob2.print_play(); break; }
				case 9: {ob2 = ob; cout << "�������� ������� ����������.\n"; break; }
				case 10: {ob2 = ob + ob1; cout << "������� ���� ������� �������.\n"; break; }
				default: {cout << "�� ������� ������������� ����� ����.\n"; }
				}
				menu3();
				cout << "������� �������������� ����� ����: ";
				getline(cin, k);
			}
			catch (int i) { cout << "�� ��������� � ���� ��������� \'+\' � \'=\' � ����� ������ " << i << endl; menu3(); cout << "������� �������������� ����� ����: "; getline(cin, k); }
			catch (...) { cout << "������� ����������� ����������. �� ��������� � ���� ��������� \'+\' � \'=\'.\n"; menu3(); cout << "������� �������������� ����� ����: "; getline(cin, k); }
		}
	}
}

void fun_menu2(theater& ob) {
	string k;
	vector<int> index;
	vector<play> p;
	menu2();
	cout << "������� �������������� ����� ����: ";
	getline(cin, k);
	while (my_stoi(k) != 0) {
		try {
			switch (my_stoi(k)) {
			case 1: {cout << ob << endl; break; }
			case 2: {ob.print_play(); break; }
			case 3: {add_p(ob); break; }
			case 4: {del_p(ob); break; }
			case 5: {cout << "������� ������������ �����, � �������� ������� ������� ������ � �����������: "; getline(cin, k); ob.fread(k); k = "5"; break; }
			case 6: {write_t(ob); break; }
			case 7: {cout << "������� �������� ����������, ������� ������ �����: "; getline(cin, k);  p = ob.find_name(k, index); ob.print_play(p, index); k = "7";  break; }
			case 8: {cout << "������� ���� ����������, ������� ������ �����: "; getline(cin, k);  p = ob.find_ganre(k, index); ob.print_play(p, index); k = "8";  break; }
			case 9: {cout << "������� ���� ������ ���������� ����������, ������� ������ �����: "; getline(cin, k);  p = ob.find_day(k, index); ob.print_play(p, index); k = "9";  break; }
			case 10: {cout << "������� ����� ���������� ����������, ������� ������ �����: "; getline(cin, k);  p = ob.find_month(k, index); ob.print_play(p, index); k = "10";  break; }
			case 11: {cout << "������� ��� ���������� ����������, ������� ������ �����: "; getline(cin, k);  p = ob.find_year(k, index); ob.print_play(p, index); k = "11";  break; }
			case 12: {cout << "������� ��� ������ ���������� ����������, ������� ������ �����: "; getline(cin, k);  p = ob.find_hour(k, index); ob.print_play(p, index); k = "12";  break; }
			case 13: {f_date(ob); break; }
			case 14: {f_time(ob); break; }
			case 15: { f_hall(ob); break; }
			case 16: {book_p(ob); break; }
			case 17: {ob.sort_time(); break; }
			case 18: {ob.sort_name(); break; }
			case 19: {ob.rename(); break; }
			case 20: {add_h(ob); break; }
			case 21: {del_h(ob); break; }
			case 22: {ind(ob); break; }
			case 23: {cout << "���������� ������� � �����������: " << ob.size() << endl;  break; }
			case 24: {fun_menu3(ob); break; }
			default: {cout << "�� ������� ������������� ����� ����.\n"; }
			}
			menu2();
			cout << "������� �������������� ����� ����: ";
			getline(cin, k);
		}
		catch (int i) { cout << "�� ��������� � �������� ���� � ����� ������ " << i << endl; menu2(); cout << "������� �������������� ����� ����: "; getline(cin, k); }
		catch (...) { cout << "������� ����������� ����������." << endl; menu2(); cout << "������� �������������� ����� ����: "; getline(cin, k); }
	}
	ob.~theater();
}

void constr_1() {
	string n, count, k;
	cout << "������� ������������ ������: ";
	getline(cin, n);
	cout << "������� ���������� ����� ������������ ������: ";
	getline(cin, count);
	while (my_stoi(count) < 1) {
		cout << "������� ����������� ���������� �����. ��������� ������� �����.\n������� ���������� ����� ������������ ������: ";
		getline(cin, count);
	}
	hall* halls = new hall[my_stoi(count)];
	for (int i = 0; i < my_stoi(count); i++) {
		std::cout << "���������� ����� � ���� " << i + 1 << ": ";
		getline(cin, k);
		while (my_stoi(k) < 1) {
			std::cout << "�� ����� ����������� ���������� �����! ��������� ������� �����!\n" << "���������� ����� � ���� " << (i + 1) << ": ";
			getline(cin, k);
		}
		halls[i].row = my_stoi(k);
		std::cout << "���������� ���� � ����� ���� ���� " << i + 1 << ": ";
		getline(cin, k);
		while (my_stoi(k) < 1) {
			std::cout << "�� ����� ����������� ���������� ���� ����! ��������� ������� �����!\n" << "���������� ���� � ����� ���� ���� " << (i + 1) << ": ";
			getline(cin, k);
		}
		halls[i].seat_row = my_stoi(k);
	}
	theater ob(n, my_stoi(count), halls);//������� ������ ���������� ����
	delete[] halls;
	fun_menu2(ob);
}

void constr_2() {
	string n, count, k;
	hall h;
	cout << "������� ������������ ������: ";
	getline(cin, n);
	cout << "������� ���������� ����� � ����������� ���������������� ��� ������������ ������: ";
	getline(cin, count);
	while (my_stoi(count) < 1) {
		cout << "������� ����������� ���������� �����. ��������� ������� �����.\n������� ���������� ����� � ����������� ���������������� ��� ������������ ������: ";
		getline(cin, count);
	}
	cout << "����������� ������������ �����. \n\t������� ���������� �����: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "\t������� ����������� ����� ����� � ����. ��������� ������� �����\n\t������� ���������� �����: ";
		getline(cin, k);
	}
	h.row = my_stoi(k);
	cout << "\t������� ���������� ���� � ����� ����: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "\t������� ����������� ����� ���� � ����. ��������� ������� �����\n\t������� ���������� ���� � ����: ";
		getline(cin, k);
	}
	h.seat_row = my_stoi(k);
	theater ob(n, my_stoi(count), h);//������� � ������� ����
	fun_menu2(ob);
} 

void constr_3() {
	string file;
	cout << "������� ������������ �����, � �������� ������ ������� ������ ��� ������: ";
	getline(cin, file);
	theater ob(file);
	fun_menu2(ob);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string k;
	menu1();
	cout << "������� �������������� ����� ����: ";
	getline(cin, k);
	while (my_stoi(k) != 0) {
		try {
			switch (my_stoi(k)) {
			case 1: {theater ob; fun_menu2(ob); break; }//������� ������ ���������� ����
			case 2: {constr_1(); break; }
			case 3: {constr_2(); break; }
			case 4: {constr_3(); break; }
			default: {cout << "�� ������� ������������� ����� ����.\n"; }
			}
			menu1();
			cout << "������� �������������� ����� ����: ";
			getline(cin, k);
		}
		catch (int i) { cout << "�� ��������� � ��������� ���� � ����� ������ " << i << endl; menu1(); cout << "������� �������������� ����� ����: "; getline(cin, k);}
		catch (...) { cout << "������� ����������� ����������." << endl; menu1(); cout << "������� �������������� ����� ����: "; getline(cin, k);}
	}
	
	return 0;
}