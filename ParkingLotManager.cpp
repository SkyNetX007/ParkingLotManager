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
	static string plateHead[] = { "¾©A", "¾©C", "¾©E", "¾©F", "¾©H", "¾©G", "¾©B", "½òA", "½òB", "½òC", "½òE", "»¦A", "»¦B", "»¦D", "»¦C", "ÓåA", "ÓåB", "ÓåC", "ÓåG", "ÓåH", "¼½A", "¼½B", "¼½C", "¼½D", "¼½E", "¼½F", "¼½G", "¼½H", "¼½J", "¼½R", "¼½T", "Ô¥A", "Ô¥B", "Ô¥C", "Ô¥D", "Ô¥E", "Ô¥F", "Ô¥G", "Ô¥H", "Ô¥J", "Ô¥K", "Ô¥L", "Ô¥M", "Ô¥N", "Ô¥P", "Ô¥Q", "Ô¥R", "Ô¥S", "Ô¥U", "ÔÆA", "ÔÆC", "ÔÆD", "ÔÆE", "ÔÆF", "ÔÆG", "ÔÆH", "ÔÆJ", "ÔÆK", "ÔÆL", "ÔÆM", "ÔÆN", "ÔÆP", "ÔÆQ", "ÔÆR ", "ÔÆS", "ÁÉA", "ÁÉB", "ÁÉC", "ÁÉD", "ÁÉE", "ÁÉF", "ÁÉG", "ÁÉH", "ÁÉJ", "ÁÉK", "ÁÉL", "ÁÉM", "ÁÉN", "ÁÉP", "ÁÉV", "ºÚA", "ºÚB", "ºÚC", "ºÚD", "ºÚE", "ºÚF", "ºÚG", "ºÚH", "ºÚJ", "ºÚK", "ºÚL", "ºÚM", "ºÚN", "ºÚP", "ºÚR", "ÏæA", "ÏæB", "ÏæC", "ÏæD", "ÏæE", "ÏæF", "ÏæG", "ÏæH", "ÏæJ", "ÏæK", "ÏæL", "ÏæM", "ÏæN", "ÏæU", "ÏæS", "ÍîA", "ÍîB", "ÍîC", "ÍîD", "ÍîE", "ÍîF", "ÍîG", "ÍîH", "ÍîJ", "ÍîK", "ÍîL", "ÍîM", "ÍîN", "ÍîP", "ÍîQ", "ÍîR", "ÍîS", "Â³A", "Â³B", "Â³C", "Â³D", "Â³E", "Â³F", "Â³G", "Â³H", "Â³J", "Â³K", "Â³L", "Â³M", "Â³N", "Â³P", "Â³Q", "Â³R", "Â³S", "Â³U", "Â³V", "Â³Y", "ĞÂA", "ĞÂB", "ĞÂC", "ĞÂD", "ĞÂE", "ĞÂF", "ĞÂG", "ĞÂH", "ĞÂJ", "ĞÂK", "ĞÂL", "ĞÂM", "ĞÂN", "ĞÂP", "ĞÂQ", "ĞÂR", "ËÕA", "ËÕB", "ËÕC", "ËÕD", "ËÕE", "ËÕF", "ËÕG", "ËÕH", "ËÕJ", "ËÕK", "ËÕL", "ËÕM", "ËÕN", "ÕãA", "ÕãB", "ÕãC", "ÕãD", "ÕãE", "ÕãF", "ÕãG", "ÕãH", "ÕãJ", "ÕãK", "ÕãL", "¸ÓA", "¸ÓB", "¸ÓC", "¸ÓD", "¸ÓE", "¸ÓF", "¸ÓG", "¸ÓH", "¸ÓJ", "¸ÓK", "¸ÓL", "¸ÓM", "¶õA", "¶õB", "¶õC", "¶õD", "¶õE", "¶õF", "¶õG", "¶õH", "¶õJ", "¶õK", "¶õL", "¶õM", "¶õN", "¶õP", "¶õQ", "¶õR", "¶õS", "¹ğA", "¹ğB", "¹ğC", "¹ğD", "¹ğE", "¹ğF", "¹ğG", "¹ğH", "¹ğJ", "¹ğK", "¹ğL", "¹ğM", "¹ğN", "¹ğP", "¹ğR", "¸ÊA", "¸ÊB", "¸ÊC", "¸ÊD", "¸ÊE", "¸ÊF", "¸ÊG", "¸ÊH", "¸ÊJ", "¸ÊK", "¸ÊL", "¸ÊM", "¸ÊN", "¸ÊP", "½úA", "½úB", "½úC", "½úD", "½úE", "½úF", "½úH", "½úJ", "½úK", "½úL", "½úM", "ÃÉA", "ÃÉB", "ÃÉC", "ÃÉD", "ÃÉE", "ÃÉF", "ÃÉG", "ÃÉH", "ÃÉJ", "ÃÉK", "ÃÉL", "ÃÉM", "ÉÂA", "ÉÂB", "ÉÂC", "ÉÂD", "ÉÂE", "ÉÂF", "ÉÂG", "ÉÂH", "ÉÂJ", "ÉÂK", "ÉÂU", "ÉÂV", "¼ªA", "¼ªB", "¼ªC", "¼ªD", "¼ªE", "¼ªF", "¼ªG", "¼ªH", "¼ªJ", "ÃöA", "ÃöB", "ÃöC", "ÃöD", "ÃöE", "ÃöF", "ÃöG", "ÃöH", "ÃöJ", "ÃöK", "¹óA", "¹óB", "¹óC", "¹óD", "¹óE", "¹óF", "¹óG", "¹óH", "¹óJ", "ÔÁA", "ÔÁB", "ÔÁC", "ÔÁD", "ÔÁE", "ÔÁF", "ÔÁG", "ÔÁH", "ÔÁJ", "ÔÁK", "ÔÁL", "ÔÁM", "ÔÁN", "ÔÁP", "ÔÁQ", "ÔÁR", "ÔÁS", "ÔÁT", "ÔÁU", "ÔÁV", "ÔÁW", "ÔÁX", "ÔÁY", "ÔÁZ", "ÇàA", "ÇàB", "ÇàC", "ÇàD", "ÇàE", "ÇàF", "ÇàG", "ÇàH", "²ØA", "²ØB", "²ØC", "²ØD", "²ØE", "²ØF", "²ØG", "²ØH", "²ØJ", "´¨A", "´¨B", "´¨C", "´¨D", "´¨E", "´¨F", "´¨H", "´¨J", "´¨K", "´¨L", "´¨M", "´¨Q", "´¨R", "´¨S", "´¨T", "´¨U", "´¨V", "´¨W", "´¨X", "´¨Y", "´¨Z", "ÄşA", "ÄşB", "ÄşC", "ÄşD", "ÇíA", "ÇíB", "ÇíC", "ÇíD", "ÇíE" };
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
	void showLot() { cout << "ÒÑÍ£³µÁ¾:" << endl; Display(&parkingLot); }
	void showPavement() { cout << "ÅÅ¶Ó³µÁ¾:" << endl; Display(&waitingPath); }
};

int Info::Enter(Car arrival)
{
	arrival.arrival_time = (unsigned)time(NULL);
	if (parkingLot.size() < maxLength) {
		arrival.status = INLOT;
		parkingLot.push(arrival);

		cout << parkingLot.top().plate << "½øÈëÍ£³µ³¡£¬" << "Í£ÔÚ" << parkingLot.size() << "ºÅÎ»" << endl;
	}
	else
	{
		arrival.status = WAITING;
		waitingPath.push(arrival);
		cout << waitingPath.back().plate << "ÕıÔÚµÈ´ı..." << endl;
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
		cout << parkingLot.top().plate << "Àë¿ªÁË£¬" << "¹²Í£³µ" << parkingLot.top().minute_time() << "·ÖÖÓ£¬" << "ÊÕ·Ñ" << price * parkingLot.top().minute_time() << "Ôª" << endl;
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
		cout << "²éÎŞ´Ë³µ£¡" << endl;
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
	cout << "No" << "\t" << "³µÅÆºÅ" << "\t\t" << "ÒÑÍ£Ê±³¤" << endl;
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
	cout << "No" << "\t" << "³µÅÆºÅ" << "\t\t" << "µÈ´ıÊ±³¤" << endl;
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
	cout << "Í£³µÎ»ÅäÖÃ:";
	cin >> maxLength;
	lotInfo.Init(maxLength);
	Car tmpcar;
	while (true)
	{
		int select = 0;
		double _price = 0;
		cout << endl << "»¶Ó­Ê¹ÓÃÍ£³µ³¡¹ÜÀíÏµÍ³£º" << "¹²" << maxLength << "¸ö³µÎ»" << endl
			<< "(1) ÉèÖÃÃ¿·ÖÖÓµ¥¼Û" << endl
			<< "(2) ÏÔÊ¾Í£³µĞÅÏ¢" << endl
			<< "(3) ÏÔÊ¾µÈ´ıÁĞ±í" << endl
			<< "(4) ³µÁ¾½øÈë" << endl
			<< "(5) ³µÁ¾Àë¿ª" << endl
			<< "(6) ²âÊÔ" << endl
			<< "(7) ÍË³ö" << endl
			<< "ÇëÑ¡Ôñ£º";

		cin >> select;
		system("cls");
		switch (select)
		{
		case 1: cout << "µ¥¼Û£º"; cin >> _price; lotInfo.setPrice(_price); break;
		case 2: lotInfo.showLot(); break;
		case 3: lotInfo.showPavement(); break;
		case 4: cout << "³µÅÆºÅ£º"; cin >> tmpcar.plate; lotInfo.Enter(tmpcar); break;
		case 5: cout << "³µÅÆºÅ£º"; cin >> tmpcar.plate; lotInfo.Leave(tmpcar.plate); break;
		case 6: for (int i = 0; i < 60; i++) { tmpcar.plate = RandomPlate(); lotInfo.Enter(tmpcar); }; break;
		case 7: exit(0);
		}
	}
}
