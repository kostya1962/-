#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Windows.h"

using namespace std;

byte fun(int k) { if (k % 50 == 0)return 0; else return 1; }

void cur_date(short& day, short& month, short& year) {//возвращает текущую дату
	SYSTEMTIME t;
	GetLocalTime(&t);
	day = t.wDay;
	month = t.wMonth;
	year = t.wYear;
}

int my_stoi(string str) {//функция преобразования строки цифр в число типа int 
	int k = 0,  f = 0;
	string sh = "0123456789";
	if (str.empty()) return k;
	while (str[0] == '0') {//удаляет все незначащие нули
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

bool dig(string str) {//функция, прверяющая, состоит ли строка только из цифр
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

bool dig_price(string str) {//функция, прверяющая, состоит ли строка только из цифр и точки (для цены)
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
	for (int i = 0, k = 0; i < str.length(); i++) {//возвращает ложь, если в строке больше одной точки
		if (str[i] == '.') k++;
		if (k > 1) return false;
	}
	return true;
}

bool only_let_cap(string str) {//Определяет, есть ли в строке символы, кроме букв русского и латинского алфавитов и только первая буква должна и может быть прописной
	while (str.find(' ') != string::npos)//удаляет пробелы
		str.erase(str.find(' '), 1);

	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ", a = "abcdefghikjlmnopqrstuvwxyzабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
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

bool only_let(string str) {//Определяет, есть ли в строке символы, кроме букв русского и латинского алфавитов
	while (str.find(' ') != string::npos)//удаляет пробелы
		str.erase(str.find(' '), 1);

	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯabcdefghikjlmnopqrstuvwxyzабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
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

string lowercase(string str) {//возвращает строку из стрчных букв, если в ней есть прописные буквы, иначе строка не изменяется
	int f = 0;
	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ", a = "abcdefghikjlmnopqrstuvwxyzабвгдеёжзийклмнопрстуфхцчшщъыьэюя", rez = "";
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

struct hall {//стуктура определения зала
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

hall hall :: operator=(hall& ob) {//присваивание залов
	row = ob.row;
	seat_row = ob.seat_row;
	return *this;
}

struct Time {//структура времени
	string hour;
	string min;

	Time operator=(Time); // используйте const time& вместо time
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

struct Date {//стркутура даты
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

struct play {//постановки
	string name;//название постановки
	struct Date date;//дата постановки
	struct Time time;//время постановки
	string ganre;//жанр постановки
	string price;//цена одного билета
	int num_hall = 0;//номер зала
	hall play_h;//информация о зале
	vector<vector<bool>> seats;//данные о свободноси/занятости конкретного места зала
	
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

play& play::operator=(play& ob) {//перенрузка оператора присваивания для постановки
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

int play :: free_place() {//считает количество свободных мест
	unsigned int k = 0;
	for (int i = 0; i < play_h.row; i++) 
		for (int j = 0; j < play_h.seat_row; j++) 
			if (seats[i][j]) k++;
		
	return k;
}

ostream& operator<<(ostream& stream, play& ob) {//оператор вывода для постановки
	cout << "\"" << ob.name << "\"" << endl << string(50,'-') << endl;
	cout << "\tЖанр: " << ob.ganre << endl;
	cout << "\tДата: ";
	cout.fill('0');
	cout.width(2);
	cout << ob.date.day << '.';
	cout.width(2);
	cout << ob.date.month << '.';
	//cout.fill(' ');
	cout.fill(' ');
	cout.width(0);
	cout << ob.date.year << endl;
	cout << "\tВремя: ";
	cout.fill('0');
	cout.width(2);
	cout << ob.time.hour << ':';
	cout.width(2);
	cout << ob.time.min << endl;
	cout.fill(' ');
	cout.width(0);
	cout << "\tЗал: " << ob.num_hall << endl;
	cout << "\tЦена билета: " << ob.price << endl;
	cout << "\tКоличество свободных мест: " << ob.free_place() << endl;
	cout << string(50, '-');
	return stream;
}

void vivod(string name, Date date, Time time, string num_hall, string ganre, string price) {//по форме напониманет вывод постановки, но нужен дла печати ошибочных записей до создания самой записи
	cout << string(40, '-') << endl << "   \"" << name << "\"" << endl;
	cout << "      Жанр: " << ganre << endl;
	cout << "      Дата: ";
	cout.fill('0');
	cout.width(2);
	cout << date.day << '.';
	cout.width(2);
	cout << date.month << '.';
	//cout.fill(' ');
	cout.fill(' ');
	cout.width(0);
	cout << date.year << endl;
	cout << "      Время: ";
	cout.fill('0');
	cout.width(2);
	cout << time.hour << ':';
	cout.width(2);
	cout << time.min << endl;
	cout << "      Цена билета: " << price << endl;
	cout << "      Зал: " << num_hall << endl;
	cout << string(40, '-') << endl ;
}

class theater {

	string name;//название театра 
	vector <struct play> play_t;//вектор (список) постановок
	int count_halls = 0;//количество залов
	hall* halls = NULL;//определение количества рдов и мест в каждом из залов

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

theater::theater() {//конструктор по умолчанию
	halls = NULL;
	count_halls = 0;
	name = "";
}

theater::theater(string n, int h, hall hs[]) {//констурктор с заданными наванием театра и количеством залов, с определением каждого из залов в массиве hs
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
		std::cout << "Предложенный массив залов меньше указанного количесвта залов!\n";
	}
	catch (...) {
		name = "";
		count_halls = 0;
		delete[] halls;
		std::cout << "Неизвестное исключесние!\n";
	}
}
//1
theater::theater(string file) {//Конструктор создания объекта класса с помощью данных из файла
	ifstream in(file);
	string c, count;
	int k = 0;
	if (!(in.is_open())) { cout << "Файл " << file << " не может быть открыт!\n"; throw 1; }
	getline(in, name);
	getline(in, count);
	while (my_stoi(count) < 1) {
		cout << "\aБыло считано невозможное количество залов!";
		throw 1;
	}
	count_halls = my_stoi(count);
	getline(in, count);
	if (count_halls == 0 && count.empty()) { halls = NULL;  }
	else {
		halls = new hall[count_halls];

		if (count.find(' ') == string::npos && !(count.empty())) { cout << "В файле " << file << " нет необходимых разделителей!"; throw 1; }
		while (count[0] == ' ') { 
			count.erase(0, 1); 
			if (count.empty()) { cout << "Строка состоит только из пробелов" << endl; in.close(); throw 1; }
		}
		while (count[count.size() - 1] == ' ') { 
			count.erase(count.size() - 1, 1); 
			if (count.empty()) { cout << "Строка состоит только из пробелов" << endl; in.close(); throw 1; }
		}
		for (int i = 0; i < count.size(); i++) {
			if (count[i] == ' ') k++;
		}
		if (k != (count_halls * 2) - 1) { cout << "В файле" << file << " предоставлена недостаточная или избыточная информация о местах в залах." << endl; throw 1; }
		for (int i = 0, j = 0; i < count_halls && j < count.length(); i++) {
			c = "";
			while (count[j] != ' ' && j < count.size()) {
				c += count[j];
				j++;
			}
			j++;
			while (!(dig(c))) {
				cout << "\aБыло считано невозможное количество рядов для зала" << (i + 1) << "! Повторите попытку ввода : \n";
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
				cout << "\aБыло считано невозможное количество мест в ряде для зала" << (i + 1) << "! Повторите попытку ввода : \n";
				getline(cin, c);
			}
			halls[i].seat_row = my_stoi(c);
		}
	}
	in.close();
}

theater::theater(string n, int count, hall h) {//конструктор театра, создающий count одинаковых залов с определением h(для коструктора нужна предварительная проверка данных)
	name = n;
	count_halls = count;
	halls = new hall[count_halls];
	for (int i = 0; i < count_halls; i++) 
		halls[i] = h;
}

theater::theater(theater& copy) {//констуктор копирования
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

		for (int i = 0; i < (play_t.size() - k); i++) { //ищем max-запись

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

	if (count_halls == 0) { std::cout << "Не существует залов для прведения постановки! Добавьте зал!\n"; return; }
	string c;
	short day, month, year;
	string mon_let[12] = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сеньтябрь", "Октябрь", "Ноябрь", "Декабрь" };
	string num[12] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
	cur_date(day, month, year);
	if (only_let(d.month)) {
		for (int i = 0; i < 12; i++)
			if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
	}
	while (true) //Проверяем дату на корректность
		if (dig(d.day) && dig(d.month) && dig(d.year)) {
			if (my_stoi(d.day) > 31 || my_stoi(d.day) < 1 || (my_stoi(d.year) == year && my_stoi(d.month) == month && my_stoi(d.day) < day)) {
				std::cout << "\aЗначение дня даты находится вне пределов допустимого! \n";
				vivod(n, d, t, h, g, p);
				cout << "Повторите попытку ввода даты!" << endl;
			}
			else {
				if (my_stoi(d.month) < 1 || my_stoi(d.month) > 12 || (my_stoi(d.year) == year && my_stoi(d.month) < month)) {
					std::cout << "\aЗначение месяца даты находится вне пределов допустимого! \n";
					vivod(n, d, t, h, g, p);
					cout << "Повторите попытку ввода даты!" << endl;
				}
				else {
					if (my_stoi(d.year) < year) {
						std::cout << "\aЗначение года даты находится вне пределов допустимого! \n";
						vivod(n, d, t, h, g, p);
						cout << "Повторите попытку ввода даты!" << endl;
					}
					else  break;
				}
			}
			


			std::cout << "Год проведения постановки: ";
			getline(cin, d.year);
			std::cout << "Месяц проведения постановки: ";
			getline(cin, d.month);
			if (only_let(d.month)) {
				
				for (int i = 0; i < 12; i++)
					if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
			}
			std::cout << "День проведения постановки: ";
			getline(cin, d.day);


		}
		else {
			std::cout << "\aЗначения даты невозможно пердставить в числовом виде! Повторите попытку ввода!\n";
			vivod(n, d, t, h, g, p);
			cout << "Год проведения постановки: ";
			getline(cin, d.year);
			std::cout << "Месяц проведения постановки: ";
			getline(cin, d.month);
			if (only_let(d.month)) {
				
				for (int i = 0; i < 12; i++)
					if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
			}
			std::cout << "День проведения постановки: ";
			getline(cin, d.day);
		}
	while (d.day[0] == '0' && d.day.length() > 1) d.day.erase(0, 1);//удаляет незначащие нули
	while (d.month[0] == '0' && d.month.length() > 1) d.month.erase(0, 1);
	while (d.year[0] == '0') d.year.erase(0, 1);

	while (true)//Проверяем час на корректность
		if (dig(t.hour)) {
			if (my_stoi(t.hour) > 23 || my_stoi(t.hour) < 0) {
				std::cout << "\aЗначение часа находится вне пределов допустимого!"<<endl;
				vivod(n, d, t, h, g, p);
				cout << "Повторите попытку ввода даты! \nЧас начала проведения постановки: " << endl;
				getline(cin, t.hour);
			}
			else break;	
		}
		else {

			std::cout << "\aЗначение часа невозможно пердставить в числовом виде!"<<endl;
			vivod(n, d, t, h, g, p);
			cout << "Повторите попытку ввода даты! \nЧас начала проведения постановки: " << endl;
			getline(cin, t.hour);
		}
	while (t.hour[0] == '0' && t.hour.length() > 1) t.hour.erase(0, 1);//удаляет незначащие нули
	
	while (true)//Проверяем минуты на корректность
		if (dig(t.min)) {
			if (my_stoi(t.min) > 59 || my_stoi(t.min) < 0) {
				std::cout << "\aЗначение минуты находится вне пределов допустимого!"<<endl;
				vivod(n, d, t, h, g, p);
				cout << "Повторите попытку ввода даты! \nМинута начала проведения постановки: ";
				getline(cin, t.min);
			}
			else break;
		}
		else {
			std::cout << "\aЗначение минуты невозможно пердставить в числовом виде!"<<endl;
			vivod(n, d, t, h, g, p);
			cout << "Повторите попытку ввода даты! \nМинута начала проведения постановки: ";
			getline(cin, t.min);
		}
	while (t.min[0] == '0' && t.min.length() > 1) t.min.erase(0, 1);//удаляет незначащие нули

	while (true)//Проверяем жанр на корректность
		if (only_let_cap(g)) break;
		else {
			std::cout << "\aЖанр постановки содержит недопустимые символы!"<<endl;
			vivod(n, d, t, h, g, p);
			cout << "Повторите попытку ввода!\n Жанр постановки (жанр имеет только одну ПРОПИСНУЮ букву, которая явлется ПЕРВУЮ): ";
			getline(cin, g);
		}


	while (true) //Проверка на корректность цены билета
		if (dig_price(p)) break;
		else {
			std::cout << "\aЦена билета на постановку имеет недопустимое значение!" << endl;
			vivod(n, d, t, h, g, p);
			cout << " Повторите попытку ввода!\nЦена билета на постановку: ";
			getline(cin, p);
		}

	while (true)//проверка корректности введённого номера зала
		if (dig(h)) {
			if (my_stoi(h) < 1 || my_stoi(h) > count_halls) {
				std::cout << "\aНекорректное занчение номера зала!" << endl;
				vivod(n, d, t, h, g, p);
				cout << "Повторите ввод!\nНомер зала, где будет ставиться постановка: ";
				getline(cin, h);
			}
			else break;
		}
		else {
			std::cout << "\aВведённый номер зала содержит недопустимые символы!" << endl;
			vivod(n, d, t, h, g, p);
			cout << "Повторите ввод!\nНомер зала, где будет ставиться постановка: ";
			getline(cin, h);
		}

	for (int i = 0; i < play_t.size(); i++)
		if (play_t[i].date == d && play_t[i].time == t && play_t[i].num_hall == my_stoi(h)) {
			std::cout << "\aВ указанном зале уже запланирована постановка в это время!\n";//добавить функции изменения параметров времени и места
			return;
		}
	
	vector<vector<bool>> seats(halls[my_stoi(h) - 1].row, vector<bool>(halls[my_stoi(h) - 1].seat_row, true));
	if (!(s.empty())) {
		while (s[0] == ' ') { s.erase(0, 1); if (s.empty()) return; }
		while (s[s.size() - 1] == ' ') { s.erase(s.size() - 1, 1); if (s.empty()) return;}
		if (!(s.empty())) {
			if (s.find('.') == string::npos) { cout << "\aВ файле, с которого считываются данные, нет необходимых разделителей в списке забронированных мест!"; throw 3; }
			for (int i = 0, row, st; i < s.length();) {
				c = "";
				while (s[i] != '.') {
					c += s[i];
					i++;
				}
				i++;
				if (my_stoi(c) <= 0 || my_stoi(c) > halls[my_stoi(h) - 1].row) { cout << "\aЗначения забронированных мест в ряде не является допустимым!\n"; throw 3; }
				row = my_stoi(c);
				c = "";
				while (i < s.length() && s[i] != ' ') {
					c += s[i];
					i++;
				}
				i++;
				if (my_stoi(c) <= 0 || my_stoi(c) > halls[my_stoi(h) - 1].seat_row) { cout << "Значения забронированных мест не является допустимым!\n"; throw 3; }
				st = my_stoi(c);
				seats[row - 1][st - 1] = false;
			}
		}
	}
	play perf(n, d, t, g, p, my_stoi(h), halls[my_stoi(h) - 1]);//создаём запись о постановке
	perf.seats = seats;
	play_t.push_back(perf);//добавляем запись о постанове в список постановок
	sort_time();//сортируем список постановок по веремени (и по залам)
}

ostream& operator<<(ostream& stream, theater& ob) {
	cout << string(70, '~') << endl;
	cout << "Название театра: \"" << ob.name << '\"' << endl;
	cout << string(18, ' ') << "Количество записей о постановках: " << ob.play_t.size() << endl;
	for (int i = 0; i < ob.count_halls; i++) {
		cout << string(18, ' ') << "Зал " << (i + 1) << ":" << endl;
		cout << string(26, ' ') << "Количество рядов: " << ob.halls[i].row << endl;
		cout << string(26, ' ') << "Количество мест в одном ряде: " << ob.halls[i].seat_row << endl;
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
void theater::fread(string filename) {//считывает список постановок
	ifstream in(filename);
	string n, g, h, p, let, s;
	Date d;
	Time t;
	int i = 0, k;

	if (!(in.is_open())) { cout << "\aФайл " << filename << " не может быть открыт!\n"; throw 2; }
	while (!(in.eof())) {
		k = 0;
		getline(in, n);
		getline(in, let);
		if (let.find('.') == string::npos) { cout << "\aВ файле " << filename << " имеется недопустимое для даты значаение!\n"; in.close(); return; }
		for (int j = 0; j < let.length(); j++) 
			if (let[j] == '.') k++;
		if(k != 2) { cout << "\aВ файле " << filename << " имеется недопустимое для даты значаение!\n"; in.close(); return; }
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
		if (let.find(':') == string::npos) { cout << "\aВ файле " << filename << " имеется недопустимое для времени значаение!\n"; in.close();  throw 4; }
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
		catch (int i) { cout << "Вы вернулись в основное меню с кодом ошибки " << i << endl; in.close(); return; }
		n = "";
		d.day = ""; d.month = ""; d.year = "";
		t.hour = ""; t.min = "";
		g = ""; p = ""; let = ""; h = ""; s = "";
	}
	in.close();
}

void theater::fwrite(string filename_t, string filename_p) {//записывает данные о театре и список постановок
	ofstream out_t(filename_t);
	if (!(out_t.is_open())) { cout << "\aОшибка открытия файла " << filename_t << " !\n"; return;}
	ofstream out_p(filename_p);
	if (!(out_p.is_open())) { cout << "\aОшибка открытия файла " << filename_p << " !\n"; return; }

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

void theater :: print_play() {//выводит список всех постановок театра
	if (play_t.empty()) { cout << "Ничего не найдено." << endl; return; }
	cout << "Список постановок: " << endl;
	cout << string(50, '-') << endl;
	for (int i = 0; i < play_t.size(); i++)
		cout << ' ' << (i + 1) << ". " << play_t[i] << endl;
}

void theater :: print_play(vector<play>& play_list, vector<int>& index) {//выводит какой-то определённый подсписок театра
	if (play_list.empty()) { cout << "Ничего не найдено." << endl; return; }
	cout << "Список постановок: " << endl;
	cout << string(50, '-') << endl;
	for (int i = 0; i < play_list.size(); i++)
		cout << ' ' << index[i] << ". " << play_list[i] << endl;
}

vector<play> theater::find_name(string str, vector<int>& index) {//создает подсписок из записей постановок, имеющих похожее имя
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++) 
		if (lowercase(play_t[i].name).find(lowercase(str)) != string::npos) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

vector<play> theater::find_ganre(string str, vector<int>& index) {//создает подсписок из записей постановок, имеющих похожий по написанию жанр
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++)
		if (lowercase(play_t[i].ganre).find(lowercase(str)) != string::npos) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

vector<play> theater::find_day(string day, vector<int>& index) {////создает подсписок из записей постановок, имеющих сохжее значение дня даты проведения
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++) 
		if (play_t[i].date.day.find(day) != string::npos) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

vector<play> theater::find_month(string month, vector<int>& index) {//создает подсписок из записей постановок, имеющих значение месяца
	vector<play> p;
	if (!(index.empty())) index.clear();
	if (only_let(month)) {
		string mon_let[12] = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сеньтябрь", "Октябрь", "Ноябрь", "Декабрь" };
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

vector<play> theater::find_year(string year, vector<int>& index) {//создает подсписок из записей постановок, имеющих похожее значение года
	vector<play> p;
	if (!(index.empty())) index.clear();
	for (int i = 0; i < play_t.size(); i++)
		if (play_t[i].date.year.find(year) != string::npos) {
			p.push_back(play_t[i]);
			index.push_back(i + 1);
		}
	return p;
}

vector<play> theater::find_hour(string hour, vector<int>& index) {//создает подсписок из записей постановок, имеющих похожее значение часа
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

void theater::print_hall(int index) {//печатает зал для указанной по индексу постановки
	string m;
	int f = 0;
	while (true) {
		cout << "Каким способом вы хотите напечатать зал?" << endl << "  1 - Графическим" << endl << "  2 - Текстовым" << endl << "  0 - Выйти  из метода" << endl << "Введите значение: ";
		getline(cin, m);
		if (m == "1") {
			if (play_t[index-1].play_h.seat_row <= 999) {
				cout << endl << "Условные обозначения:\n";
				cout.width(42);
				cout << "* - свободное место\n";
				cout.width(47);
				cout << "# - забронированное место" << endl << endl;
				for (int k = 0; k < (play_t[index-1].play_h.seat_row / 50) + fun(play_t[index-1].play_h.seat_row); k++) {//графический местод вывода зала
					if (play_t[index-1].play_h.seat_row > 50) cout << (k + 1) << "-ая часть зала: " << endl;
					cout << "№места";
					for (int i = k * 50, n = 1; (i < (play_t[index-1].play_h.seat_row)) && ((i + n) % 50 != 0); i++, n = 0) {
						cout.width(4);
						cout << i + 1;
					}
					cout << endl;
					cout << "ряда " << endl;
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
			else { cout << "Зал слишком большой, поэтому не может быть выведен графически. Попробуйте ткстовый метод.\n"; }
		}
		else if (m == "2") {
			while (true) {//текстовый метода вывода зала
				f = 0;
				cout << "Введите номер ряда от " << 1 << " до " << play_t[index-1].play_h.row << ", чтобы узнать, какие места в нём свободны (или \'0\', чтобы выйти из метода): ";
				getline(cin, m);
				if (m == "0") break;
				if (my_stoi(m) > 0 && my_stoi(m) <= play_t[index-1].play_h.row) {
					cout << "Свободные места ряда " << m << ": ";
					for (int i = 0, s = 0; i < play_t[index-1].play_h.seat_row; i++) 
						if (play_t[index-1].seats[my_stoi(m) - 1][i]) {
							cout << (i + 1);
							if (i != (play_t[index-1].play_h.seat_row - 1)) cout << ", ";
							else cout << ". " << endl;
							if (s == 35) { cout << endl; s = 0; }
							f = 1;
							s++;
						}
					
					if (f == 0) cout << "Все места забронированы. Попробуйте ввести другой ряд." << endl;
				}
				else cout << "Искомый ряд не существует. Повторите попытку ввода.\n";
			}
		}
		else if (m == "0") break;
		else { cout << "Вы ввели значение, не предполагаемое пунктом меню. Повторите попытку ввода.\n"; }
	}
}

void theater::book_place(int index) {//бронирование места на постановку(получает порядковый номер)
	string row, seat, f;
	cout << string(50, '-') << endl << play_t[index-1] << endl;
	while (true) {
		cout << "Выберете следующий шаг.\n  1 - Забронировать место\n  2 - Вывести зал постановки\n  0 - Выйти из метода" << endl << "Выберете соотвествуюий пункт меню: ";
		getline(cin, f);
		if (f == "1") {
			while (true) {
				cout << "Выберете ряд, в котором хотите занять место: ";
				getline(cin, row);
				if (my_stoi(row) > 0 && my_stoi(row) <= play_t[index-1].play_h.row) break;
				else cout << "Введены некорректные данные. Повторите попытку ввода.\n";
			}
			while (true) {
				cout << "Выберете место в ряде " << row << " которое хотите забронировать: ";
				getline(cin, seat);
				if (my_stoi(seat) > 0 && my_stoi(seat) <= play_t[index-1].play_h.seat_row) break;
				else cout << "Введены некорректные данные. Повторите попытку ввода.\n";
			}
			if (play_t[index-1].seats[my_stoi(row) - 1][my_stoi(seat) - 1]) {
				play_t[index-1].seats[my_stoi(row) - 1][my_stoi(seat) - 1] = false;
				cout << "Место успешно забронировано!\n";
			}
			else { cout << "Место уже забронировано.\n"; }
		}
		else if (f == "2") print_hall(index);
		else if (f == "0") break;
		else cout << "Нет подходящего пункта меню." << endl;
	}
}

void theater::del_play(string index) {//удаляет запись о постановке
	if (play_t.size() == 0 || my_stoi(index) < 1 || my_stoi(index) > play_t.size()) { cout << "\aВ театре нет ни одной постановки!\n"; return; }
	vector<play> double_play;
	string s;
	int k = my_stoi(index) - 1;
	cout << string(50, '-') << endl << play_t[k] << "\n" << "Вы уверены что хотите удалить запись о постановке?\n";
	cout << string(66, ' ') << "1 - Да\n";
	cout << string(44,' ') << "{Любое другое значение} - Нет\nВведите соотвествующий пункт меню: ";
	getline(cin, s);
	if (my_stoi(s) == 1) {
		for (int i = 0; i < k; i++) double_play.push_back(play_t[i]);
		for (int i = (k + 1); i < play_t.size(); i++) double_play.push_back(play_t[i]);
		play_t = double_play;
	}
	else  return; 
}

void theater::del_hall(int num) {//удаляет зал с номером num (счёт от 1)
	int f = 0;
	string h;
	for (int i = 0; i < play_t.size(); i++)
		if ((play_t[i].num_hall == num) && ((play_t[i].play_h.row * play_t[i].play_h.seat_row) != (play_t[i].free_place()))) {
			f = 1;
			break;
		}
	if (f == 1) { cout << "В удаляемом зале уже забронированы места на определённые постановки. До проведения постановок невозможно удалить зал.\n"; return; }
	if ((count_halls - 1) != 0) {
		for (int i = 0; i < play_t.size(); i++) {
			if (play_t[i].num_hall == num) {
				cout << "Постановка планируется проводиться в удаляемом зале.\n" << string(50, '-') << endl << play_t[i] << endl << "Выберете для данной постановки оставшиеся залы: ";
				getline(cin, h);
				while (my_stoi(h) < 1 || my_stoi(h) == num || my_stoi(h) > count_halls) {
					cout << "Зал для данной постановки не может быть заменён указанным залом. Повторите попытку ввода." << endl;
					cout << "Выберете для данной постановки оставшиеся залы: ";
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
	else { cout << "Невозможно удалить единственный зал, так как нет возможности перенести постановки в другое место\n"; return; }
}

void theater::add_hall(hall h) {//добавляет постановку
	count_halls++;
	hall* new_hall = new hall[count_halls];
	for (int i = 0; i < (count_halls - 1); i++) 
		new_hall[i] = halls[i];
	new_hall[(count_halls - 1)] = h;
	delete[] halls;
	halls = new_hall;
}

void theater::sort_name() {//сортирует по имени постаноки (по алфавиту)
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

theater operator+(theater ob1, theater ob2) {//создаёт новый объект класса theater, который включает в себя как данные левтого, так и данные правого операнда
	theater ob;
	cout << "Введите наименование театра, который получится в результате сложения: ";
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

void theater::rename() {//Заменяет название театра
	cout << "Введите новое имя театра: ";
	getline(cin, name);
}

void menu1() {//вывод начального меню
	cout << endl << string(120, '*') << endl << "Начальное меню." << endl;
	cout << string(8, ' ') << "Создание объекта класса ob theater.\n";
	cout << string(8, ' ') << "1 - Конструктор по умолчанию\n";
	cout << string(8, ' ') << "2 - Конструктор с заданием и определением определённого числа залов\n";
	cout << string(8, ' ') << "3 - Конструктор, создающий определённое число одинаковых залов\n";
	cout << string(8, ' ') << "4 - Конструктор, считывающий данные с файла\n";
	cout << string(8, ' ') << "0 - Выйти\n" << string(120, '*') << "\n\n";
}

void menu_ob1() {//вывод меню создания воторого объекта
	cout << endl << string(120, '*') << endl;
	cout << string(8, ' ') << "Создание объекта ob1 класса theater.\n";
	cout << string(8, ' ') << "1 - Конструктор по умолчанию\n";
	cout << string(8, ' ') << "2 - Конструктор с заданием и определением определённого числа залов\n";
	cout << string(8, ' ') << "3 - Конструктор, создающий определённое число одинаковых залов\n";
	cout << string(8, ' ') << "4 - Конструктор, считывающий данные с файла\n";
	cout << string(8, ' ') << "0 - Выйти\n" << string(120, '*') << "\n\n";
}

void menu2() {//вывод основного меню
	cout << endl << string(120, '*') << endl << "Основное меню." << endl;
	cout << "Работа с объектом (ob) класса theater.\n";
	cout << string(8, ' ') << "1 - Вывести данные о театре\n";
	cout << string(8, ' ') << "2 - Вывести список постановок\n";
	cout << string(8, ' ') << "3 - Добавить постановку\n";
	cout << string(8, ' ') << "4 - Удалить постановку по порядковому номеру\n";
	cout << string(8, ' ') << "5 - Считать данные о постановках с файла\n";
	cout << string(8, ' ') << "6 - Записать данные о театре и постановках в файлы\n";
	cout << string(8, ' ') << "7 - Найти постановки по названию\n";
	cout << string(8, ' ') << "8 - Найти постановки по жанру\n";
	cout << string(8, ' ') << "9 - Найти постановки по дню в месяце проведения\n";
	cout << string(8, ' ') << "10 - Найти постановки по месяцу проведения\n";
	cout << string(8, ' ') << "11 - Найти постановки по году проведения\n";
	cout << string(8, ' ') << "12 - Найти постановки по часу начала проведения\n";
	cout << string(8, ' ') << "13 - Найти постановки по дате проведения\n";
	cout << string(8, ' ') << "14 - Найти постановки по времени проведения\n";
	cout << string(8, ' ') << "15 - Найти постановки по залу\n";
	cout << string(8, ' ') << "16 - Забронировать место на постановку\n";
	cout << string(8, ' ') << "17 - Отсортировать список постановок по времени (состояние по умолчанию)\n";
	cout << string(8, ' ') << "18 - Отсортировать список постановок по названию\n";
	cout << string(8, ' ') << "19 - Изменить название театра\n";
	cout << string(8, ' ') << "20 - Добавить зал\n";
	cout << string(8, ' ') << "21 - Удалить зал по поярдковому номеру\n";
	cout << string(8, ' ') << "22 - Проверка перегрузки индекса массива. Вывести данные о постановке по индексу\n";
	cout << string(8, ' ') << "23 - Получить количесвто записей о постановках\n";
	cout << string(8, ' ') << "24 - Проверить перегрузку операторов. Создание второго объекта класса theater (ob1).\n";
	cout << string(8, ' ') << "0 - Вернуться в начальное меню\n" << string(120, '*') << "\n\n";
}

void menu3() {//меню операторов
	cout << endl << string(120, '*') << "\nМеню операоторов \'+\' и \'=\'.\n";
	cout << string(8,' ') << "1 - Вывести данные объекта ob\n";
	cout << string(8, ' ') << "2 - Вывести список постановок ob\n";
	cout << string(8, ' ') << "3 - Вывести данные объекта ob1\n";
	cout << string(8, ' ') << "4 - Вывести список постановок ob1\n";
	cout << string(8, ' ') << "5 - Добавить постановку для ob1\n";
	cout << string(8, ' ') << "6 - Считать данные о постановках с файла для ob1\n";
	cout << string(8, ' ') << "7 - Вывести данные объекта ob2\n";
	cout << string(8, ' ') << "8 - Вывести список постановок ob2\n";
	cout << string(8, ' ') << "9 - Присвоить объекту ob2 объект ob\n";
	cout << string(8, ' ') << "10 - Сложить объекты ob и ob1 и присвоить результат объекту ob2\n";
	cout << string(8, ' ') << "0 - Вернуться в основное меню\n" << string(120, '*') << "\n\n";
}

void constr1(theater& ob) {
	string n, count, k;
	cout << "Введите наименование театра: ";
	getline(cin, n);
	cout << "Введите количество залов создаваемого театра: ";
	getline(cin, count);
	while (my_stoi(count) < 1) {
		cout << "Введено невозможное количество залов. Повторите попытку ввода.\nВведите количество залов создаваемого театра: ";
		getline(cin, count);
	}
	hall* halls = new hall[my_stoi(count)];
	for (int i = 0; i < my_stoi(count); i++) {
		std::cout << "Количество рядов в зале " << i + 1 << ": ";
		getline(cin, k);
		while (my_stoi(k) < 1) {
			std::cout << "Вы ввели невозможное количество рядов! Повторите попытку ввода!\n" << "Количество рядов в зале " << (i + 1) << ": ";
			getline(cin, k);
		}
		halls[i].row = my_stoi(k);
		std::cout << "Количество мест в одном ряде зала " << i + 1 << ": ";
		getline(cin, k);
		while (my_stoi(k) < 1) {
			std::cout << "Вы ввели невозможное количество мест ряда! Повторите попытку ввода!\n" << "Количество мест в одном ряде зала " << (i + 1) << ": ";
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
	cout << "Введите наименование театра: ";
	getline(cin, n);
	cout << "Введите количество залов с одинаковыми характеристиками для создаваемого театра: ";
	getline(cin, count);
	while (my_stoi(count) < 1) {
		cout << "Введено невозможное количество залов. Повторите попытку ввода.\nВведите количество залов с одинаковыми характеристиками для создаваемого театра: ";
		getline(cin, count);
	}
	cout << "Определение характристик залов. \tВведите количество рядов: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "\tВведено невозможное число рядов в зале. Повторите попытку ввода\n\tВведите количество рядов: ";
		getline(cin, k);
	}
	h.row = my_stoi(k);
	cout << "\tВведите количество мест в одном ряде: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "\tВведено невозможное число мест в ряде. Повторите попытку ввода\n\tВведите количество мест в ряде: ";
		getline(cin, k);
	}
	h.seat_row = my_stoi(k);
	theater ob1(n, my_stoi(count), h);
	ob = ob1;
}

void add_p(theater& ob) {
	if (ob.count_h() == 0) { cout << "Нет залов для проведения постановок. Добавьте зал.\n"; return; }
	string n, g, p, h;
	Date d;
	Time t;
	short day, month, year;
	cur_date(day, month, year);
	string mon_let[12] = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сеньтябрь", "Октябрь", "Ноябрь", "Декабрь" };
	string num[12] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
	cout << "Введите наименование добавляемой постановки: ";
	getline(cin, n);
	cout << "Введите жанр добавляемой постановки: ";
	getline(cin, g);
	while (true)//Проверяем жанр на корректность
		if (only_let_cap(g)) break;
		else {
			std::cout << "\aЖанр постановки содержит недопустимые символы!" << endl;
			vivod(n, d, t, h, g, p);
			cout << "Повторите попытку ввода!\n Жанр постановки (жанр имеет только одну ПРОПИСНУЮ букву, которая явлется ПЕРВУЮ): ";
			getline(cin, g);
		}
	cout << "Введите год проведения добавляемой постановки: ";
	getline(cin, d.year);
	cout << "Введите месяц проведения добавляемой постановки: ";
	getline(cin, d.month);
	if (only_let(d.month)) {
		for (int i = 0; i < 12; i++) 
			if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
	}
	cout << "Введите день проведения добавляемой постановки: ";
	getline(cin, d.day);
	while (true) //Проверяем дату на корректность
		if (dig(d.day) && dig(d.month) && dig(d.year)) {
			if (my_stoi(d.day) > 31 || my_stoi(d.day) < 1 || (my_stoi(d.year) == year && my_stoi(d.month) == month && my_stoi(d.day) < day)) {
				std::cout << "\aЗначение дня даты находится вне пределов допустимого! \n";
				vivod(n, d, t, h, g, p);
				cout << "Повторите попытку ввода даты!" << endl;
			}
			else {
				if (my_stoi(d.month) < 1 || my_stoi(d.month) > 12 || (my_stoi(d.year) == year && my_stoi(d.month) < month)) {
					std::cout << "\aЗначение месяца даты находится вне пределов допустимого! \n";
					vivod(n, d, t, h, g, p);
					cout << "Повторите попытку ввода даты!" << endl;
				}
				else {
					if (my_stoi(d.year) < year) {
						std::cout << "\aЗначение года даты находится вне пределов допустимого! \n";
						vivod(n, d, t, h, g, p);
						cout << "Повторите попытку ввода даты!" << endl;
					}
					else  break;
				}
			}
			std::cout << "Год проведения постановки: ";
			getline(cin, d.year);
			std::cout << "Месяц проведения постановки: ";
			getline(cin, d.month);
			if (only_let(d.month)) {
				for (int i = 0; i < 12; i++)
					if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
			}
			std::cout << "День проведения постановки: ";
			getline(cin, d.day);
		}
		else {
			std::cout << "\aЗначения даты невозможно пердставить в числовом виде! Повторите попытку ввода!\n";
			vivod(n, d, t, h, g, p);
			cout << "Год проведения постановки: ";
			getline(cin, d.year);
			std::cout << "Месяц проведения постановки: ";
			getline(cin, d.month);
			if (only_let(d.month)) {

				for (int i = 0; i < 12; i++)
					if (lowercase(d.month) == lowercase(mon_let[i])) { d.month = num[i]; break; }
			}
			std::cout << "День проведения постановки: ";
			getline(cin, d.day);
		}

	cout << "Введите час начала проведения добавляемой постановки: ";
	getline(cin, t.hour);
	while (true)//Проверяем час на корректность
		if (dig(t.hour)) {
			if (my_stoi(t.hour) > 23 || my_stoi(t.hour) < 0) {
				std::cout << "\aЗначение часа находится вне пределов допустимого!" << endl;
				vivod(n, d, t, h, g, p);
				cout << "Повторите попытку ввода даты! \nЧас начала проведения постановки: " << endl;
				getline(cin, t.hour);
			}
			else break;
		}
		else {

			std::cout << "\aЗначение часа невозможно пердставить в числовом виде!" << endl;
			vivod(n, d, t, h, g, p);
			cout << "Повторите попытку ввода даты! \nЧас начала проведения постановки: " << endl;
			getline(cin, t.hour);
		}
	
	cout << "Введите минуты начала проведения добавляемой постановки: ";
	getline(cin, t.min);
	while (true)//Проверяем минуты на корректность
		if (dig(t.min)) {
			if (my_stoi(t.min) > 59 || my_stoi(t.min) < 0) {
				std::cout << "\aЗначение минуты находится вне пределов допустимого!" << endl;
				vivod(n, d, t, h, g, p);
				cout << "Повторите попытку ввода даты! \nМинута начала проведения постановки: ";
				getline(cin, t.min);
			}
			else break;
		}
		else {
			std::cout << "\aЗначение минуты невозможно пердставить в числовом виде!" << endl;
			vivod(n, d, t, h, g, p);
			cout << "Повторите попытку ввода даты! \nМинута начала проведения постановки: ";
			getline(cin, t.min);
		}

	cout << "Введите номер зала, где будет проходить добавляемая постановка: ";
	getline(cin, h);
	while (true)//проверка корректности введённого номера зала
		if (dig(h)) {
			if (my_stoi(h) < 1 || my_stoi(h) > ob.count_h()) {
				std::cout << "\aНекорректное занчение номера зала!" << endl;
				vivod(n, d, t, h, g, p);
				cout << "Повторите ввод!\nНомер зала, где будет ставиться постановка: ";
				getline(cin, h);
			}
			else break;
		}
		else {
			std::cout << "\aВведённый номер зала содержит недопустимые символы!" << endl;
			vivod(n, d, t, h, g, p);
			cout << "Повторите ввод!\nНомер зала, где будет ставиться постановка: ";
			getline(cin, h);
		}

	cout << "Введите цену на билет для добавляемой постановки: ";
	getline(cin, p);
	while (true) //Проверка на корректность цены билета
		if (dig_price(p)) break;
		else {
			std::cout << "\aЦена билета на постановку имеет недопустимое значение!" << endl;
			vivod(n, d, t, h, g, p);
			cout << " Повторите попытку ввода!\nЦена билета на постановку: ";
			getline(cin, p);
		}
	ob.add_play(n, d, t, g, p, h, "");
}

void del_p(theater& ob) {
	string index;
	cout << "Введите порядковый номер удаляемой постановки: ";
	getline(cin, index);
	ob.del_play(index);
}

void write_t(theater& ob) {
	string filename_t, filename_p;
	cout << "Введите наименование файла, в который следует записать данные о театре: ";
	getline(cin, filename_t);
	cout << "Введите наименование файла, в который следует записать данные о постановках: ";
	getline(cin, filename_p);
	ob.fwrite(filename_t, filename_p);
}

void f_date(theater& ob) {
	vector<int> index;
	vector<play> p;
	Date d;
	cout << "Введите год проведения искомых постановок: ";
	getline(cin, d.year);
	cout << "Введите месяц проведения искомых постановок: ";
	getline(cin, d.month);
	cout << "Введите день проведения искомых постановок: ";
	getline(cin, d.day);
	p = ob.find_date(d, index);
	ob.print_play(p, index);
}

void f_time(theater& ob) {
	vector<int> index;
	vector<play> p;
	Time t;
	cout << "Введите час начала проведения искомых постановок: ";
	getline(cin, t.hour);
	cout << "Введите минуты начала прведения искомых постановок: ";
	getline(cin, t.min);
	p = ob.find_time(t, index);
	ob.print_play(p, index);
}

void f_hall(theater& ob) {
	string k; 
	vector<play> p;
	vector<int> index;
	cout << "Введите номер зала, по которому хотите отфильтровать список постановок: ";
	getline(cin, k);
	while (my_stoi(k) < 1 || my_stoi(k) > ob.count_h()) {
		cout << "Введено недопустимое для зала значение. Повторите ввод: ";
		getline(cin, k);
	}
	p = ob.find_hall(my_stoi(k), index);
	ob.print_play(p, index);
}

void book_p(theater& ob) {
	if (ob.size() == 0) { cout << "\aВ театре нет ни одной постановки!\n"; return; }
	string num;
	cout << "Введите порядковый номер постановки, для которой хотите забронировать места: ";
	getline(cin, num);
	while (my_stoi(num) < 1 || my_stoi(num) > ob.size()) {
		cout << "Введён некорректный порядковый номер. Повторите попытку ввода.\nВведите порядковый номер постановки, для которой хотите забронировать места: ";
		getline(cin, num);
	}
	ob.book_place(my_stoi(num));
}

void add_h(theater& ob) {
	hall h;
	string k;
	cout << "Введите количество рядов добавляемого ряда: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "Введено некорректное значение числа рядов добавляемого зала. Повторите попытку ввода.\nВведите количество рядов добавляемого зала: ";
		getline(cin, k);
	}
	h.row = my_stoi(k);
	cout << "Введите количество мест в одном ряде добавляемого зала: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "Введено некорректное значение числа мест в ряде добавляемого зала. Повторите попытку ввода.\nВведите количество мест ряда добавляемого зала: ";
		getline(cin, k);
	}
	h.seat_row = my_stoi(k);
	ob.add_hall(h);
}

void del_h(theater& ob) {
	if (ob.count_h() == 0) { cout << "\aВ театре нет ни одного зала!\n"; return;  }
	string k;
	cout << "Введите порядковый номер зала, который хотите удалить: ";
	getline(cin, k);
	while (my_stoi(k) < 1 || my_stoi(k) > ob.count_h()) {
		cout << "Введён некорректный порядковый номер удаляемого зала. Повторите попытку.\nВведите порядковый номер зала, который хотите удалить: ";
		getline(cin, k);
	}
	ob.del_hall(my_stoi(k));
}

void ind(theater& ob) {
	if (ob.size() == 0) { cout << "\aВ театре нет ни одной постановки!\n"; return; }
	string k;
	cout << "Введите индекс записи, которую надо вывести на консоль: ";
	getline(cin, k);
	while (my_stoi(k) < 0 || my_stoi(k) >= ob.size()) {
		cout << "Введённый индекс выходит за пределы массива постановок. Повторите попытку ввода: ";
		getline(cin, k);
	}
	play p = ob[my_stoi(k)];
	cout << string(50, '-')<<"\n "<<k<<". " << p << endl;
}

void fun_menu3(theater& ob) {//необходимо доработать
	string k = "5";
	int f = 0;
	theater ob1, ob2;
	while (my_stoi(k) < 0 || my_stoi(k) > 4) {
		try {
			menu_ob1();
			cout << "Введите соотвествующий пункт меню: ";
			getline(cin, k);
			switch (my_stoi(k)) {
			case 0: { break; }
			case 1: { break; }
			case 2: {theater ob3; constr1(ob3); ob1 = ob3; ob3.~theater(); break; }
			case 3: {theater ob3; constr2(ob3); ob1 = ob3; ob3.~theater(); break; }
			case 4: {cout << "Введите наименование файла, с которого хотите считать данные для театра: "; getline(cin, k);  theater ob3(k); ob1 = ob3; ob3.~theater(); k = "2"; break; }
			default: {cout << "Вы выбрали несущетвующий пункт меню.\n"; }
			}
		}
		catch (int i) { cout << "Вы вернулись в основное меню меню с кодом ошибки " << i << endl; ob1.~theater(); ob2.~theater(); f = 1; break;}
		catch (...) { cout << "Вызвано неизвестное исключение.Вы вернулись в основное меню меню.\n"; ob1.~theater(); ob2.~theater(); f = 1; break;}
	}
	if (f == 0 && k != "0") {
		menu3();
		cout << "Введите соотвествующий пункт меню: ";
		getline(cin, k);
		while (k != "0") {
			try {
				switch (my_stoi(k)) {
				case 1: {cout << ob << endl; break; }
				case 2: {ob.print_play(); break; }
				case 3: {cout << ob1 << endl; break; }
				case 4: {ob1.print_play(); break; }
				case 5: {cout << "Введите наименование файла, с которого следует считать данные о постановках: "; getline(cin, k); ob.fread(k); k = "5"; break; }
				case 6: {add_p(ob1); break; }
				case 7: { cout << ob2 << "\n"; break; }
				case 8: { ob2.print_play(); break; }
				case 9: {ob2 = ob; cout << "Значение успешно приствоено.\n"; break; }
				case 10: {ob2 = ob + ob1; cout << "Объекты были успешно сложены.\n"; break; }
				default: {cout << "Вы выбрали несущетвующий пункт меню.\n"; }
				}
				menu3();
				cout << "Введите соотвествующий пункт меню: ";
				getline(cin, k);
			}
			catch (int i) { cout << "Вы вернулись в меню оператров \'+\' и \'=\' с кодом ошибки " << i << endl; menu3(); cout << "Введите соотвествующий пункт меню: "; getline(cin, k); }
			catch (...) { cout << "Вызвано неизвестное исключение. Вы вернулись в меню оператров \'+\' и \'=\'.\n"; menu3(); cout << "Введите соотвествующий пункт меню: "; getline(cin, k); }
		}
	}
}

void fun_menu2(theater& ob) {
	string k;
	vector<int> index;
	vector<play> p;
	menu2();
	cout << "Введите соотвествующий пункт меню: ";
	getline(cin, k);
	while (my_stoi(k) != 0) {
		try {
			switch (my_stoi(k)) {
			case 1: {cout << ob << endl; break; }
			case 2: {ob.print_play(); break; }
			case 3: {add_p(ob); break; }
			case 4: {del_p(ob); break; }
			case 5: {cout << "Введите наименование файла, с которого следует считать данные о постановках: "; getline(cin, k); ob.fread(k); k = "5"; break; }
			case 6: {write_t(ob); break; }
			case 7: {cout << "Введите название постановок, которых хотите найти: "; getline(cin, k);  p = ob.find_name(k, index); ob.print_play(p, index); k = "7";  break; }
			case 8: {cout << "Введите жанр постановок, которых хотите найти: "; getline(cin, k);  p = ob.find_ganre(k, index); ob.print_play(p, index); k = "8";  break; }
			case 9: {cout << "Введите день месяца проведения постановок, которых хотите найти: "; getline(cin, k);  p = ob.find_day(k, index); ob.print_play(p, index); k = "9";  break; }
			case 10: {cout << "Введите месяц проведения постановок, которых хотите найти: "; getline(cin, k);  p = ob.find_month(k, index); ob.print_play(p, index); k = "10";  break; }
			case 11: {cout << "Введите год проведения постановок, которых хотите найти: "; getline(cin, k);  p = ob.find_year(k, index); ob.print_play(p, index); k = "11";  break; }
			case 12: {cout << "Введите час начала проведения постановок, которых хотите найти: "; getline(cin, k);  p = ob.find_hour(k, index); ob.print_play(p, index); k = "12";  break; }
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
			case 23: {cout << "Количество записей о постановках: " << ob.size() << endl;  break; }
			case 24: {fun_menu3(ob); break; }
			default: {cout << "Вы выбрали несущетвующий пункт меню.\n"; }
			}
			menu2();
			cout << "Введите соотвествующий пункт меню: ";
			getline(cin, k);
		}
		catch (int i) { cout << "Вы вернулись в основное меню с кодом ошибки " << i << endl; menu2(); cout << "Введите соотвествующий пункт меню: "; getline(cin, k); }
		catch (...) { cout << "Вызвано неизвестное исключение." << endl; menu2(); cout << "Введите соотвествующий пункт меню: "; getline(cin, k); }
	}
	ob.~theater();
}

void constr_1() {
	string n, count, k;
	cout << "Введите наименование театра: ";
	getline(cin, n);
	cout << "Введите количество залов создаваемого театра: ";
	getline(cin, count);
	while (my_stoi(count) < 1) {
		cout << "Введено невозможное количество залов. Повторите попытку ввода.\nВведите количество залов создаваемого театра: ";
		getline(cin, count);
	}
	hall* halls = new hall[my_stoi(count)];
	for (int i = 0; i < my_stoi(count); i++) {
		std::cout << "Количество рядов в зале " << i + 1 << ": ";
		getline(cin, k);
		while (my_stoi(k) < 1) {
			std::cout << "Вы ввели невозможное количество рядов! Повторите попытку ввода!\n" << "Количество рядов в зале " << (i + 1) << ": ";
			getline(cin, k);
		}
		halls[i].row = my_stoi(k);
		std::cout << "Количество мест в одном ряде зала " << i + 1 << ": ";
		getline(cin, k);
		while (my_stoi(k) < 1) {
			std::cout << "Вы ввели невозможное количество мест ряда! Повторите попытку ввода!\n" << "Количество мест в одном ряде зала " << (i + 1) << ": ";
			getline(cin, k);
		}
		halls[i].seat_row = my_stoi(k);
	}
	theater ob(n, my_stoi(count), halls);//передаёт объект следующему меню
	delete[] halls;
	fun_menu2(ob);
}

void constr_2() {
	string n, count, k;
	hall h;
	cout << "Введите наименование театра: ";
	getline(cin, n);
	cout << "Введите количество залов с одинаковыми характеристиками для создаваемого театра: ";
	getline(cin, count);
	while (my_stoi(count) < 1) {
		cout << "Введено невозможное количество залов. Повторите попытку ввода.\nВведите количество залов с одинаковыми характеристиками для создаваемого театра: ";
		getline(cin, count);
	}
	cout << "Определение характристик залов. \n\tВведите количество рядов: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "\tВведено невозможное число рядов в зале. Повторите попытку ввода\n\tВведите количество рядов: ";
		getline(cin, k);
	}
	h.row = my_stoi(k);
	cout << "\tВведите количество мест в одном ряде: ";
	getline(cin, k);
	while (my_stoi(k) < 1) {
		cout << "\tВведено невозможное число мест в ряде. Повторите попытку ввода\n\tВведите количество мест в ряде: ";
		getline(cin, k);
	}
	h.seat_row = my_stoi(k);
	theater ob(n, my_stoi(count), h);//переход к другому меню
	fun_menu2(ob);
} 

void constr_3() {
	string file;
	cout << "Введите наименование файла, с которого хотите считать данные для театра: ";
	getline(cin, file);
	theater ob(file);
	fun_menu2(ob);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string k;
	menu1();
	cout << "Введите соотвествующий пункт меню: ";
	getline(cin, k);
	while (my_stoi(k) != 0) {
		try {
			switch (my_stoi(k)) {
			case 1: {theater ob; fun_menu2(ob); break; }//передаёт объект следующему меню
			case 2: {constr_1(); break; }
			case 3: {constr_2(); break; }
			case 4: {constr_3(); break; }
			default: {cout << "Вы выбрали несущетвующий пункт меню.\n"; }
			}
			menu1();
			cout << "Введите соотвествующий пункт меню: ";
			getline(cin, k);
		}
		catch (int i) { cout << "Вы вернулись в начальное меню с кодом ошибки " << i << endl; menu1(); cout << "Введите соотвествующий пункт меню: "; getline(cin, k);}
		catch (...) { cout << "Вызвано неизвестное исключение." << endl; menu1(); cout << "Введите соотвествующий пункт меню: "; getline(cin, k);}
	}
	
	return 0;
}