// ���� 1
#include <iostream>
using namespace std;

class Box {
private:
    double length;
    double width;
    double height;
public:
    Box(int l = 0, int w = 0, int h = 0) : length(l), width(w), height(h) {  }

    bool operator<(Box& b) {
        if (this->getVolume() < b.getVolume()) return true;
        else return false;
    }

    double getVolume(void) {
        return length * width * height;
    }

    void getItem(void) {
        cout << "������ ����: " << length << endl;
        cout << "������ �ʺ�: " << width << endl;
        cout << "������ ����: " << height << endl;
        cout << "������ ����: " << getVolume() << endl << endl;
    }
};
int main(int argc, const char* argv[]) {
    Box a(10, 10, 10), b(20, 20, 20);

    cout << "���� #1" << endl;
    a.getItem();
    cout << "���� #2" << endl;
    b.getItem();

    if (a < b) cout << "true" << endl;
    else cout << "false" << endl;

    return 0;
}


//���� 2
#include <iostream>
using namespace std;

class Time {
private:
    int hours;
    int minutes;
public:
    Time() : hours(0), minutes(0) {}
    Time(int h, int m) : hours{ h }, minutes{ m } {}

    void displayTime() {
        cout << hours << ": " << minutes << endl;
    }

    const Time& operator++() {
        if (this->minutes < 59) this->minutes++;
        else if (this->minutes == 59) {
            this->hours++;
            this->minutes = 0;
        }
        return (*this);
    }
};

int main(int argc, const char* argv[]) {
    Time t(10, 59);
    t.displayTime();

    ++t;
    t.displayTime();

    ++t;
    t.displayTime();

    return 0;
}


//���� 3
#include <iostream>
#include <string>
using namespace std;

class Person {
    string name;
    int birthYear;
public:
    Person(string name, int year) {
        this->name = name;
        this->birthYear = year;
    }
    void print() {
        cout << "����: " << name << endl;
        cout << "�������: " << birthYear << endl;
    }
};

class Student :public Person {
    string university;
public:
    Student(string name, int year, string university) :Person(name, year) {
        this->university = university;
    }
    void print() {
        Person::print();
        cout << "���б�: " << university << endl;
    }
};

int main() {
    Student s("���Ͽ�", 2001, "��õ����б�");
    s.print();
    return 0;
}


//���� 4
#include <iostream>
#include <string>
using namespace std;

class Employee {
    string name;
    int salary;
public:
    Employee(string n, int s) { name = n; salary = s; }
    void setName(string n) { name = n; }
    void setSalary(int s) { salary = s; }
    string getName() { return name; }
    int getSalary() { return salary; }
    int computeSalary() { return salary; }
};

int main() {
    Employee e("��ö��", 200);
    cout << "�̸� : " << e.getName() << endl;
    cout << "���� : " << e.getSalary() << endl;
    cout << "��ü �޿� : " << e.computeSalary() << endl;
    return 0;
}


//����5
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class Sprite {
protected:
	int x, y;
	char shape;
public:
	Sprite(int x, int y, char shape) : x(x), y(y), shape(shape) {}
	virtual ~Sprite() {	}

	virtual void move(char d) = 0;
	char getShape() { return shape; }

	int getX() { return x; }
	int getY() { return y; }

	bool checkCollision(Sprite* other) {
		if (x == other->getX() && y == other->getY())
			return true;
		else
			return true;
	}
};

class Hero : public Sprite {
public:
	Hero(int x, int y) :Sprite(x, y, 'H') {	}
	void draw() { cout << 'H'; }
	void move(char d) {
		if (d == 'a') { x -= 1; }
		else if (d == 'w') { y -= 1; }
		else if (d == 's') { y += 1; }
		else if (d == 'd') { x += 1; }
	}
};

class Treasure :public Sprite {
public:
	Treasure(int x, int y) :Sprite(x, y, 'T') {}
	void move(char d) {}
};

class Enmey :public Sprite {
public:
	Enmey(int x, int y) :Sprite(x, y, 'E') {}
	void move(char d) {}
};

class Board {
	char* board;
	int width, height;
public:
	Board(int w, int h) :width(w), height(h) {
		board = new char[width * height];
		clearBoard();
	}
	~Board() {
		delete board;
	}
	void setValue(int r, int c, char shape) {
		board[r * width + c] = shape;
	}
	void printBoard() {
		for (int i = 0; i < height; i++) {
			cout << "\t";
			for (int j = 0; j < width; j++)
				cout << board[i * width + j];
			cout << endl;
		}
	}
	void clearBoard() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++)
				board[i * width + j] = '.';
		}
	}
};

void drawLine(char x) {
	cout << endl;
	for (int i = 0; i < 100; i++)
		cout << x;
	cout << endl;
}

int main() {
	vector<Sprite*> list;
	int width, height;

	cout << "������ ũ�⸦ �Է��Ͻÿ�[�ִ� 10x10]: " << endl;
	cout << "����";
	cin >> width;
	cout << "����:";
	cin >> height;

	Board board(height, width);
	list.push_back(new Hero(0, 0));
	list.push_back(new Treasure(height - 1, width - 1));
	list.push_back(new Enmey(3, 3));

	drawLine('*');
	cout << "�� ������ ��ǥ�� ����(T)�̳� ��(E)�� ������ �ʰ� ������ �����ϴ� ���̴�. ���ΰ��� a,s,w,d Ű�� �̿��Ͽ� ������ �� �ִ�." << endl;
	drawLine('*');
	cout << endl;

	while (true) {
		board.clearBoard();
		for (auto& e : list)
			board.setValue(e->getY(), e->getX(), e->getShape());
		board.printBoard();

		char direction;
		cout << "���� �����ϱ��(a,s,w,d): ";
		cin >> direction;

		for (auto& e : list)
			e->move(direction);
		drawLine('-');
	}

	for (auto& e : list)
		delete e;
	list.clear();

	return 0;
}


//����6
#include<iostream>
using namespace std;

class Weapon {
public:
	virtual void load() = 0;
};
class Bomb : public Weapon {
public:
	void load() { cout << "��ź�� �����մϴ�." << endl; }
};
class Gun : public Weapon {
public:
	void load() { cout << "���� �����մϴ�." << endl; }
};

int main() {
	Weapon* loa[3];
	loa[0] = new Gun;
	loa[1] = new Bomb;
	loa[2] = new Bomb;

	for (Weapon* w : loa)
		w->load();

	return 0;
}


//���� 7
#include<iostream>
#include<sstream>
#include<vector>
using namespace std;

class Sprite {
protected:
    int x, y;
    char shape;
public:
    Sprite(int x, int y, char shape) : x(x), y(y), shape{ shape } { }
    virtual ~Sprite() { }

    virtual void move(char d) = 0;
    char getShape() { return shape; }

    int getX() { return x; }
    int getY() { return y; }

    bool checkCollision(Sprite* other) {
        if (x == other->getX() && y == other->getY())
            return true;
        else
            return true;
    }
};

class Hero :public Sprite {
public:
    Hero(int x, int y) :Sprite(x, y, 'H') { }
    void draw() { cout << 'H'; }
    void move(char d) {
        if (d == 'a') { x -= 1; }
        else if (d == 'w') { y -= 1; }
        else if (d == 's') { y += 1; }
        else if (d == 'd') { x += 1; }
    }
};

class Treasure :public Sprite {
public:
    Treasure(int x, int y) : Sprite(x, y, 'T') { }
    void move(char d) { }
};

class Enemy :public Sprite {
public:
    Enemy(int x, int y) : Sprite(x, y, 'E') { }
    void move(char d) {   }
};

class Board {
    char* board;
    int width, height;
public:
    Board(int w, int h) : width{ w }, height{ h } {
        board = new char[width * height];
        clearBoard();
    }
    ~Board() {
        delete board;
    }
    void setValue(int r, int c, char shape) {
        board[r * width + c] = shape;
    }
    void printBoard() {
        for (int i = 0; i < height; i++) {
            cout << "\t";
            for (int j = 0; j < width; j++)
                cout << board[i * width + j];
            cout << endl;
        }
    }
    void clearBoard() {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                board[i * width + j] = '.';
    }
};

void drawLine(char x) {
    cout << endl;
    for (int i = 0; i < 100; i++)
        cout << x;
    cout << endl;
}

int main() {
    vector<Sprite*>list;
    int width, height;

    cout << "������ ũ�⸦ �Է��Ͻÿ�[�ִ� 10x10]: " << endl;
    cout << "����: ";
    cin >> width;

    cout << "����: ";
    cin >> height;

    Board board(height, width);
    list.push_back(new Hero(0, 0));
    list.push_back(new Treasure(height - 1, width - 1));
    list.push_back(new Enemy(3, 3));

    drawLine('*');
    cout << "�� ������ ��ǥ�� ����(T)�̳� ��(E)�� ������ �ʰ� ������ �����ϴ� ���̴�. ";
    cout << "���ΰ��� a, s, w, d Ű�� �̿��Ͽ� ������ �� �ִ�." << endl;
    drawLine('*');
    cout << endl;

    while (true)
    {
        board.clearBoard();
        for (auto& e : list)
            board.setValue(e->getY(), e->getX(), e->getShape());
        board.printBoard();

        char direction;
        try {
            cout << "���� �����ϱ��(a, s, w, d): ";
            cin >> direction;
            if (direction == 'a' && direction == 's' || direction == 'w' || direction == 'd') {
                for (auto& e : list)
                    e->move(direction);
                drawLine('-');
            }
            else
                throw direction;
        }
        catch (char e) {
            cout << "���� : " << e << "�� �������� �ʽ��ϴ�." << endl;
        }
    }

    for (auto& e : list)
        delete e;
    list.clear();
}


//����8
#include<iostream>
using namespace std;

template<typename T>
T getSmalleset(T arr[], int n) {
    T min = arr[0];

    for (int i = 0; i < n; i++) {
        if (min > arr[i])
            min = arr[i];
    }

    return min;
}

int main() {
    double list[] = { 1.2, 3.3, 9.0, 1.5, 8.7 };
    cout << "�ּҰ�: " << getSmalleset(list, 5) << endl;
}


//����9
#include<iostream>
using namespace std;

template<typename T>
class Circle {
private:
    T x, y;
    T radius;
public:
    Circle(T x, T y, T r) : x{ x }, y{ y }, radius{ r } {}
    T area() { return radius * radius * 3.14; }
};

int main() {

    Circle<int> circle(1, 1, 10);
    cout << "����: " << circle.area() << endl;

    return 0;
}