#include "MinecraftServerLauncher.h"

void write()
{
	if (!fs::exists("LauncherData"))
		fs::create_directory("LauncherData");

	OtherData Pack;
	Pack.UAR = UsingAutoRam;
	Pack.ISR = IsServerRun;
	Pack.IEE = IsEulaEdited;
	Pack.AR = Ram;
	strcpy_s(Pack.BN, sizeof(Pack.BN), BukkitName.c_str());

	FILE* fp = fopen("LauncherData\\FirstRunDate.launcherdat", "wb");
	fwrite(&FirstRunDate, sizeof(FirstRunDate), 1, fp);
	fclose(fp);
	fp = fopen("LauncherData\\LastRunDate.launcherdat", "wb");
	fwrite(&LastRunDate, sizeof(LastRunDate), 1, fp);
	fclose(fp);
	fp = fopen("LauncherData\\RunningTime.launcherdat", "wb");
	fwrite(&RunningTime, sizeof(RunningTime), 1, fp);
	fclose(fp);
	fp = fopen("LauncherData\\OtherData.launcherdat", "wb");
	fwrite(&Pack, sizeof(Pack), 1, fp);
	fclose(fp);
}

void read()
{
	if (!fs::exists("LauncherData"))
		return;

	FILE* fp = NULL;
	ifstream stream;
	OtherData Pack;

	stream.open("LauncherData\\FirstRunDate.launcherdat");
	if (stream.good())
	{
		fp = fopen("LauncherData\\FirstRunDate.launcherdat", "rb");
		fread(&FirstRunDate, sizeof(FirstRunDate), 1, fp);
		fclose(fp);
	}
	stream.close();

	stream.open("LauncherData\\LastRunDate.launcherdat");
	if (stream.good())
	{
		fp = fopen("LauncherData\\LastRunDate.launcherdat", "rb");
		fread(&LastRunDate, sizeof(LastRunDate), 1, fp);
		fclose(fp);
	}
	stream.close();

	stream.open("LauncherData\\RunningTime.launcherdat");
	if (stream.good())
	{
		fp = fopen("LauncherData\\RunningTime.launcherdat", "rb");
		fread(&RunningTime, sizeof(RunningTime), 1, fp);
		fclose(fp);
	}
	stream.close();

	stream.open("LauncherData\\OtherData.launcherdat");
	if (stream.good())
	{
		fp = fopen("LauncherData\\OtherData.launcherdat", "rb");
		fread(&Pack, sizeof(Pack), 1, fp);

		UsingAutoRam = Pack.UAR;
		IsServerRun = Pack.ISR;
		IsEulaEdited = Pack.IEE;
		Ram = Pack.AR;
		BukkitName = Pack.BN;

		fclose(fp);
	}
	stream.close();
}

void start()
{
	ifstream file;
	file.open("eula.txt");

	if (file.good() && !IsEulaEdited)
	{
		stringstream ss;
		string line;
		ss << file.rdbuf();
		file.close();

		line = ss.str();
		line.pop_back();
		line.pop_back();
		line[line.length() - 4] = 't';
		line[line.length() - 3] = 'r';
		line[line.length() - 2] = 'u';
		line[line.length() - 1] = 'e';

		ofstream file_out;
		file_out.open("eula.txt", ifstream::out);
		file_out << line;
		file_out.close();

		IsEulaEdited = true;
	}

	system("cls");
	if (BukkitName == "NULL")
	{
		cout << endl << endl;
		cout << "	[ ERROR ] : 핵심 파일의 이름을 설정해 주세요" << endl;
		cout << endl << endl;
		_getch();
		return;
	}

	string RamString;

	if (UsingAutoRam)
	{
		RamString = to_string(Ram) + "G";
	}
	else
	{
		short input;

		do {
			system("cls");

			cout << endl << endl;
			cout << "  램 할당량을 입력해 주세요 ( 단위 : GB ) : ";

			cin >> input;

			if (input <= (getmemoryinfo() / 2))
				break;
			else
			{
				system("cls");
				cout << endl << endl;
				cout << "	[ ERROR ] : 설정한 램 용량이 너무 큽니다" << endl;
				cout << endl << endl;
				_getch();
			}
		} while (1);

		RamString = to_string(input) + "G";
	}

	system("cls");

	__print_running_server();

	string command = "java -jar -Xms" + RamString + " -Xmx" + RamString + " " + BukkitName;

	time_t curr_time;
	struct tm curr_tm;
	curr_time = time(NULL);
	localtime_s(&curr_tm, &curr_time);

	if (!IsServerRun)
	{
		FirstRunDate.year = curr_tm.tm_year + 1900;
		FirstRunDate.month = curr_tm.tm_mon + 1;
		FirstRunDate.day = curr_tm.tm_mday;
	}

	LastRunDate.year = curr_tm.tm_year + 1900;
	LastRunDate.month = curr_tm.tm_mon + 1;
	LastRunDate.day = curr_tm.tm_mday;

	time_t start, end;
	int sec;
	start = time(NULL);

	system(command.c_str());

	end = time(NULL);
	sec = static_cast<int>(end - start);

	int min, hour;

	min = sec / 60;
	hour = min / 60;
	sec %= 60;
	min %= 60;

	sec += RunningTime.second;
	min += RunningTime.minute;
	hour += RunningTime.hour;

	min += sec / 60;
	hour += min / 60;
	sec %= 60;
	min %= 60;

	RunningTime.second = sec;
	RunningTime.minute = min;
	RunningTime.hour = hour;

	write();
}

void setting()
{
	while (1)
	{
		system("cls");
		write();
		
		__print_setting_menu();

		char input;

		do {
			input = _getch();
		} while (input > '6' || input < '1');

		switch (input)
		{
		case '1':
			setting_one();
			break;
		case '2':
			setting_two();
			break;
		case '3':
			setting_three();
			break;
		case '4':
			setting_four();
			break;
		case '5':
			setting_five();
			break;
		case '6':
			return;
		}
	}
}

void setting_one()
{
	system("cls");

	cout << endl << endl << endl;
	cout << "	1. 사용" << endl << endl;
	cout << "	2. 사용 안함" << endl << endl;
	cout << "	3. 돌아가기" << endl;
	cout << endl << endl;

	cout << "	원하는 항목을 선택해 주세요 : ";

	char input;

	do {
		input = _getch();
	} while (input > '3' || input < '1');

	switch (input)
	{
	case '1':
		UsingAutoRam = true;
		system("cls");
		cout << endl << endl;
		cout << "	[ INFO ] : 램 할당량 기본 설정을 \"사용\" 으로 설정하였습니다" << endl;
		cout << endl << endl;
		_getch();
		break;
	case '2':
		UsingAutoRam = false;
		system("cls");
		cout << endl << endl;
		cout << "	[ INFO ] : 램 할당량 기본 설정을 \"사용 안함\" 으로 설정하였습니다" << endl;
		cout << endl << endl;
		_getch();
		break;
	case '3':
		return;
	}

}

void setting_two()
{
	short input;

	do {
		system("cls");

		cout << endl << endl;
		cout << "  램 할당량을 입력해 주세요 ( 단위 : GB, 돌아가기 : -1 ) : ";

		cin >> input;

		if (input = -1)
			return;

		if (input <= (getmemoryinfo() / 2))
		{
			Ram = input;
			system("cls");
			cout << endl << endl;
			cout << "	[ INFO ] : 램 할당량을 \"" + to_string(input) + "GB\" 로 설정하였습니다" << endl;
			cout << endl << endl;
			_getch();
			break;
		}
		else
		{
			system("cls");
			cout << endl << endl;
			cout << "	[ ERROR ] : 설정한 램 용량이 너무 큽니다" << endl;
			cout << endl << endl;
			_getch();
		}
	} while (1);
}

void setting_three()
{
	ifstream stream;
	do
	{
		system("cls");
		string name;
		cout << endl << endl;
		cout << "	핵심 파일의 이름을 입력해 주세요 ( 한글 미지원, 돌아가기 : -1 ) : ";
		cin >> name;
		if (name == "-1")
			return;
		bool flag = false;
		char comp[5] = "raj.";
		for (int i = 4; i > 0; i--)
		{
			if (name[name.length() - i] != comp[i - 1])
				flag = true;
		}
		if (flag)
			BukkitName = (name + ".jar");
		else
			BukkitName = name;

		stream.open(BukkitName);

		if (stream.good())
		{
			stream.close();
			system("cls");
			cout << endl << endl;
			cout << "	[ INFO ] : 핵심파일을 \"" << name << "\" 파일로 설정했습니다" << endl;
			cout << endl << endl;
			_getch();
			return;
		}
		else
		{
			system("cls");
			cout << endl << endl;
			cout << "	[ ERROR ] : \"" << name << "\" 파일을 찾을 수 없습니다" << endl;
			cout << endl << endl;
			_getch();
		}
	} while (1);
}

void setting_four()
{
	string name = getjarfile();
	if (name == "NULL")
	{
		BukkitName = "NULL";
		system("cls");
		cout << endl << endl;
		cout << "	[ ERROR ] : 핵심 파일을 찾을 수 없습니다" << endl;
		cout << endl << endl;
		_getch();
	}
	else
	{
		BukkitName = name;
		system("cls");
		cout << endl << endl;
		cout << "	[ INFO ] : 핵심파일을 \"" << name << "\" 파일로 설정했습니다" << endl;
		cout << endl << endl;
		_getch();
	}
}

void setting_five()
{
	system("cls");
	cout << endl << endl;
	cout << "	정말 초기화 하시겠습니까? (Y,N) ";

	char input;

	do
	{
		input = _getch();
	} while (input != 'n' && input != 'y' && input != 'N' && input != 'Y');

	if (input == 'n' || input == 'N')
		return;

	UsingAutoRam = false;
	Ram = 1;
	BukkitName = "NULL";
	system("cls");
	cout << endl << endl;
	cout << "	[ INFO ] : 설정을 초기화 하였습니다" << endl;
	cout << endl << endl;
	_getch();
}

void info()
{
	system("cls");

	string RamString = to_string(Ram) + "GB";

	cout << endl << endl << endl << endl;
	cout << "			[ 서버 구동 정보 ]" << endl;
	cout << endl << endl;
	if (FirstRunDate.year == 0 && FirstRunDate.month == 0 && FirstRunDate.day == 0)
		cout << " 	서버를 처음 구동한 날짜 : 서버를 구동시키지 않음" << endl;
	else
		cout << " 	서버를 처음 구동한 날짜 : " << FirstRunDate.year << "년 " << FirstRunDate.month << "월 " << FirstRunDate.day << "일" << endl;
	cout << endl << endl;
	cout << " 	서버를 구동한 총 시간 : " << RunningTime.hour << "h " << RunningTime.minute << "m " << RunningTime.second << "s" << endl;
	cout << endl << endl;
	if (LastRunDate.year == 0 && LastRunDate.month == 0 && LastRunDate.day == 0)
		cout << " 	서버를 마지막으로 구동한 날짜 : 서버를 구동시키지 않음" << endl;
	else
		cout << " 	서버를 마지막으로 구동한 날짜 : " << LastRunDate.year << "년 " << LastRunDate.month << "월 " << LastRunDate.day << "일" << endl;
	cout << endl << endl;
	if (BukkitName == "NULL")
		cout << " 	핵심 파일의 이름 : 설정하지 않음" << endl;
	else
		cout << " 	핵심 파일의 이름 : " << BukkitName << endl;
	cout << endl << endl;
	cout << " 	설정된 램 할당량 : " << RamString << endl;
	cout << endl << endl << endl << endl;

	_getch();

	ifstream file;
	file.open("server.properties");

	if (file.good())
	{

		wcout.imbue(std::locale("kor"));

		system("cls");

		string motd;
		bool online_mode = true;
		bool white_list = false;
		unsigned short server_port = 25565;
		int max_player = 20;
		bool hardcore = false;
		wstring difficulty;

		string line;
		while (getline(file, line))
		{
			if (line.substr(0, 11) == "difficulty=")
			{
				string value = line.substr(11);
				if (value == "peaceful")
					difficulty = L"평화로움";
				else if (value == "easy")
					difficulty = L"쉬움";
				else if (value == "normal")
					difficulty = L"보통";
				else if (value == "hard")
					difficulty = L"어려움";
			}
			else if (line.substr(0, 9) == "hardcore=")
			{
				string value = line.substr(9);
				if (value == "true")
					hardcore = true;
				else if (value == "false")
					hardcore = false;
			}
			else if (line.substr(0, 12) == "max-player=")
				max_player = stoi(line.substr(12));
			else if (line.substr(0, 12) == "server-port=")
				server_port = static_cast<unsigned short>(stoi(line.substr(12)));
			else if (line.substr(0, 11) == "white-list=")
			{
				string value = line.substr(11);
				if (value == "true")
					white_list = true;
				else if (value == "false")
					white_list = false;
			}
			else if (line.substr(0, 12) == "online-mode=")
			{
				string value = line.substr(11);
				if (value == "true")
					online_mode = true;
				else if (value == "false")
					online_mode = false;
			}
			else if (line.substr(0, 5) == "motd=")
				motd = line.substr(5);
		}

		cout << endl << endl << endl << endl;
		cout << "			[ 서버 properties 정보 ]" << endl;
		cout << endl << endl;
		cout << "	난이도 : ";
		wcout << difficulty;
		cout << endl << endl << endl;
		if (hardcore)
			cout << "	하드코어 : 사용" << endl;
		else
			cout << "	하드코어 : 사용 안함" << endl;
		cout << endl << endl;
		cout << "	접속 가능 플레이어 수 : " << max_player << "명" << endl;
		cout << endl << endl;
		cout << "	서버 포트 : " << server_port << endl;
		cout << endl << endl;
		if (white_list)
			cout << "	화이트 리스트 : 사용" << endl;
		else
			cout << "	화이트 리스트 : 사용 안함" << endl;
		cout << endl << endl;
		if (online_mode)
			cout << "	정품 유저만 허용 : 사용" << endl;
		else
			cout << "	정품 유저만 허용 : 사용 안함" << endl;
		cout << endl << endl;
		cout << "	서버 설명 : " << motd << endl;
		cout << endl << endl << endl << endl;

		_getch();
	}
	else
		file.close();
}