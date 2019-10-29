//#include <Windows.h>
#include <iostream>
//#include <queue>
//#include <stack>
#include "PTL.h" //PTL stack+queue
#include <time.h>

using namespace std;

enum CAR_STATUS
{
	NOTARRIVED,
	INLOT,
	WAITING,
	MOVING,
	GONE
};

//void gotoxy(int x, int y)
//{
//	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD c = { x, y };
//	SetConsoleCursorPosition(hOut, c);
//}

string RandomPlate()
{
	static string plateHead[] = { "��A", "��C", "��E", "��F", "��H", "��G", "��B", "��A", "��B", "��C", "��E", "��A", "��B", "��D", "��C", "��A", "��B", "��C", "��G", "��H", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��R", "��T", "ԥA", "ԥB", "ԥC", "ԥD", "ԥE", "ԥF", "ԥG", "ԥH", "ԥJ", "ԥK", "ԥL", "ԥM", "ԥN", "ԥP", "ԥQ", "ԥR", "ԥS", "ԥU", "��A", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��P", "��Q", "��R ", "��S", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��P", "��V", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��P", "��R", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��U", "��S", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��P", "��Q", "��R", "��S", "³A", "³B", "³C", "³D", "³E", "³F", "³G", "³H", "³J", "³K", "³L", "³M", "³N", "³P", "³Q", "³R", "³S", "³U", "³V", "³Y", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��P", "��Q", "��R", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��P", "��Q", "��R", "��S", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��P", "��R", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��P", "��A", "��B", "��C", "��D", "��E", "��F", "��H", "��J", "��K", "��L", "��M", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��U", "��V", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��K", "��L", "��M", "��N", "��P", "��Q", "��R", "��S", "��T", "��U", "��V", "��W", "��X", "��Y", "��Z", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��A", "��B", "��C", "��D", "��E", "��F", "��G", "��H", "��J", "��A", "��B", "��C", "��D", "��E", "��F", "��H", "��J", "��K", "��L", "��M", "��Q", "��R", "��S", "��T", "��U", "��V", "��W", "��X", "��Y", "��Z", "��A", "��B", "��C", "��D", "��A", "��B", "��C", "��D", "��E" };
	static int plateHead_Length = (sizeof(plateHead) / sizeof(plateHead[0]));
	static string plateLetter = "ABCDEFGHJKLMNPQRSTUVWXYZ";
	static string plateNum = "0123456789";

	string result = "\0", tempPlate = "\0";
	result += plateHead[rand() % plateHead_Length];
	int letterNum = rand() % 3;
	for (int i = 0; i < letterNum; i++)
		tempPlate += plateLetter[rand() % 24];
	for (int i = 0; i < 5 - letterNum; i++)
		tempPlate += plateNum[rand() % 10];
	for (int i = 0; i < 5; i++)
		swap(tempPlate[i], tempPlate[rand() % 5]);

	result += tempPlate;
	return result;
}

struct Car {
	unsigned int arrival_time = 0, leaving_time = 0;
	int minute_time() { return (leaving_time - arrival_time) / 60; }
	string plate = "\0";
	enum CAR_STATUS status = NOTARRIVED;
};

class Info {
private:
	stack<Car>parkingLot, tmpPath;
	queue<Car>waitingPath;
	int maxLength = 0;
	double price = 0;

public:
	int Enter(Car arrival);
	int Leave(string plate);
	void Init(int length);
	void setPrice(double _price) { price = _price; };
	double Price(Car car);
	void Display(stack<Car> *content);
	void Display(queue<Car> *content);
	void showLot() { cout << "��ͣ����:" << endl; Display(&parkingLot); }
	void showPavement() { cout << "�Ŷӳ���:" << endl; Display(&waitingPath); }
};

int Info::Enter(Car arrival)
{
	arrival.arrival_time = (unsigned)time(NULL);
	if (parkingLot.size() < maxLength) {
		arrival.status = INLOT;
		parkingLot.push(arrival);

		cout << parkingLot.top().plate << "����ͣ������" << "ͣ��" << parkingLot.size() << "��λ" << endl;
	}
	else
	{
		arrival.status = WAITING;
		waitingPath.push(arrival);
		cout << waitingPath.back().plate << "���ڵȴ�..." << endl;
	}
	return 0;
}

int Info::Leave(string plate)
{
	while (parkingLot.top().plate != plate)
	{
		parkingLot.top().status = MOVING;
		tmpPath.push(parkingLot.top());
		parkingLot.pop();
		if (parkingLot.empty())
		{
			break;
		}
	}
	if (!parkingLot.empty())
	{
		parkingLot.top().leaving_time = (unsigned)time(NULL);
		cout << parkingLot.top().plate << "�뿪�ˣ�" << "��ͣ��" << parkingLot.top().minute_time() << "���ӣ�" << "�շ�" << price * parkingLot.top().minute_time() << "Ԫ" << endl;
		parkingLot.pop();
		while (!tmpPath.empty())
		{
			tmpPath.top().status = INLOT;
			parkingLot.push(tmpPath.top());
			tmpPath.pop();
		}
		if (!waitingPath.empty()) {
			Enter(waitingPath.front());
			waitingPath.pop();
		}
	}
	else
	{
		cout << "���޴˳���" << endl;
		while (!tmpPath.empty())
		{
			tmpPath.top().status = INLOT;
			parkingLot.push(tmpPath.top());
			tmpPath.pop();
		}
	}
	
	return 0;
}

void Info::Init(int length)
{
	maxLength = length;
	while (!waitingPath.empty())
		waitingPath.pop();
	while (!tmpPath.empty())
		tmpPath.pop();
	while (!parkingLot.empty())
		parkingLot.pop();
}

double Info::Price(Car car)
{
	double totalprice = (car.arrival_time - car.leaving_time) * price;
	return totalprice;
}

void Info::Display(stack<Car> *content)
{
	stack<Car> buf = *content;
	int No = 1;
	cout << "No" << "\t" << "���ƺ�" << "\t\t" << "��ͣʱ��" << endl;
	while (!buf.empty())
	{
		buf.top().leaving_time = (unsigned)time(NULL);
		cout << No << "\t" << buf.top().plate << "\t" << buf.top().minute_time() << endl;
		buf.pop();
		No++;
	}
}

void Info::Display(queue<Car> *content)
{
	queue<Car> buf = *content;
	int No = 1;
	cout << "No" << "\t" << "���ƺ�" << "\t\t" << "�ȴ�ʱ��" << endl;
	while (!buf.empty())
	{
		buf.front().leaving_time = (unsigned)time(NULL);
		cout << No << "\t" << buf.front().plate << "\t" << buf.front().minute_time() << endl;
		buf.pop();
		No++;
	}
}

void main()
{
	Info lotInfo;
	int maxLength;
	cout << "ͣ��λ����:";
	cin >> maxLength;
	lotInfo.Init(maxLength);
	Car tmpcar;
	while (true)
	{
		int select = 0;
		double _price = 0;
		cout << endl << "��ӭʹ��ͣ��������ϵͳ��" << "��" << maxLength << "����λ" << endl
			<< "(1) ����ÿ���ӵ���" << endl
			<< "(2) ��ʾͣ����Ϣ" << endl
			<< "(3) ��ʾ�ȴ��б�" << endl
			<< "(4) ��������" << endl
			<< "(5) �����뿪" << endl
			<< "(6) ����" << endl
			<< "(7) �˳�" << endl
			<< "��ѡ��";

		cin >> select;
		system("cls");
		switch (select)
		{
		case 1: cout << "���ۣ�"; cin >> _price; lotInfo.setPrice(_price); break;
		case 2: lotInfo.showLot(); break;
		case 3: lotInfo.showPavement(); break;
		case 4: cout << "���ƺţ�"; cin >> tmpcar.plate; lotInfo.Enter(tmpcar); break;
		case 5: cout << "���ƺţ�"; cin >> tmpcar.plate; lotInfo.Leave(tmpcar.plate); break;
		case 6: for (int i = 0; i < 60; i++) { tmpcar.plate = RandomPlate(); lotInfo.Enter(tmpcar); }; break;
		case 7: exit(0);
		}
	}
}
