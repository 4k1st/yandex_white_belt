#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void ex6()
{
	/*
		ff
	
	*/
	string str;
	cin>>str;
	
	int i=0, c=0;
	for(auto j: str)
	{
		if(j=='f')
		{
			c++;
		}
		if(c==2)
			break;
		i++;
	}
	
	if(c==0)
	{
		cout<<-2;
	}else if(c==1)
	{
		cout<<-1;
	}else
	{
		cout<<i;
	}
}

void ex7()
{
	/*
5 Задание по программированию: Наибольший общий делитель
В stdin даны два натуральных числа. Найти их наибольший общий делитель.
Пример
stdin	stdout
25 27	1
12 16	4
13 13	13
*/
	int a,b;
	cin>>a>>b;
	while(a!=0 && b!=0)
	{
		if(a>b)
		{	
			a=a%b;
		}else{
			b=b%a;
		}
	}	
	cout<<a+b;
}

void ex8()
{
	/*
6 Задание по программированию: Двоичные числа
На вход дано целое положительное число N. Выведите его в двоичной системе счисления без ведущих нулей.
Пример
stdin	stdout
5	101
32	100000
1	1
Подсказка
•	число N можно считывать в переменную типа int
•	в этой задаче вам может пригодиться контейнер vector; напоминаем, что добавление значения x в конец вектора v делается так: v.push_back(x);

	*/
	int a,c;
	cin>>a;
	vector<int> bin;
	while(a!=1)
	{
		bin.push_back(a%2);
		a/=2;
		
	}
	bin.push_back(1);
	for(int i=bin.size()-1;i>=0;i--)
	{
		
		cout<<bin[i];
	}
}

/*ex9*/
int Factorial(int a)
{
/*7 Задание по программированию: Факториал
Напишите функцию, которая
•	называется Factorial
•	возвращает int
•	принимает int и возвращает факториал своего аргумента. Гарантируется, что аргумент функции по модулю не превышает 10. Для отрицательных аргументов функция должна возвращать 1.
Аргумент функции	Результат
1	1
-2	1
4	24
Пояснение
В этой задаче на проверку вам надо прислать файл с реализацией функции Factorial. Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции
*/
	if(a<=0)
		return 1;
	return a*Factorial(a-1);
}

/*ex10*/
bool IsPalindrom(string str)
{
	/*
8 Тренировочное задание по программированию: Палиндром
Напишите функцию, которая
•	называется IsPalindrom
•	возвращает bool
•	принимает параметр типа string и возвращает, является ли переданная строка палиндромом
Палиндром - это слово или фраза, которые одинаково читаются слева направо и справа налево.
Аргумент функции	Результат
madam	true
gentleman	false
Пояснение
В этой задаче на проверку вам надо прислать файл с реализацией функции IsPalindrom. Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции.

	*/
	bool key;
	for(int i=0, j=str.size()-1;i<=j;i++, j--)
	{
		if(str[i]==str[j]){
			//key=true;
			return true;
		}else{
			return false;
		}		
	}
	
}

/*ex11*/
vector<string> PalindromFilter(vector<string> words,int minLength)
{
	/*
9 Задание по программированию: Отбор палиндромов
Напишите функцию, которая
•	называется PalindromFilter
•	возвращает vector<string>
•	принимает vector<string> words и int minLength и возвращает все строки из вектора words, которые являются палиндромами и имеют длину не меньше minLength
Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
Примеры
words	minLength	результат
abacaba, aba	5	abacaba
abacaba, aba	2	abacaba, aba
weew, bro, code	4	weew
Пояснение
В этой задаче вам надо прислать на проверку файл с реализацией функции PalindromFilter, а также других функций, если это необходимо (например, функции проверки на палиндром). Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции.
*/
	vector<string> res;
	for(auto str: words)
	{
		if(str.size()<minLength)
			continue;	
		if(IsPalindrom(str))
		{
			res.push_back(str);
		}
	}	
	return res;
} 

/*ex12*/
void UpdateIfGreater(int a,int &b)
{
	/*
	10 Тренировочное задание по программированию: Максимизатор
Напишите функцию UpdateIfGreater, которая принимает два целочисленных аргумента: first и second. Если first оказался больше second, Ваша функция должна записывать в second значение параметра first. При этом изменение параметра second должно быть видно на вызывающей стороне.
Пример
Пояснение
В этой задаче на проверку вам надо прислать файл с реализацией функции UpdateIfGreater. Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции.

	*/
	if(a>b)
		b=a;
}

/*ex13*/
void MoveString(vector<string> &source,vector<string> &destination)
{
	/*
	11 Задание по программированию: Перемещение строк
Напишите функцию MoveStrings, которая принимает два вектора строк, source и destination, и дописывает все строки из первого вектора в конец второго. После выполнения функции вектор source должен оказаться пустым.
Чтобы очистить содержимое вектора, надо вызвать у него метод clear:
Пример
Пояснение
В этой задаче на проверку вам надо прислать файл с реализацией функции MoveStrings. Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции.

	*/
	for(auto w: source)
	{
		destination.push_back(w);
	}
	source.clear();
}

/*ex14*/
void Reverse(vector<int> &v)
{
	/*
	12 Задание по программированию: Разворот последовательности
Реализуйте функцию void Reverse(vector<int>& v), которая переставляет элементы вектора в обратном порядке.
Пример
Пояснение
В этой задаче на проверку вам надо прислать файл с реализацией функции Reverse. Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции.

	*/
	vector<int> buf;
	for(int i=v.size()-1;i>=0;i--)
	{
		buf.push_back(v[i]);
	}
	v=buf;
}

/*ex15*/
vector<int> Reversed(const vector<int> &v)
{
	/*
	13 Тренировочное задание по программированию: Разворот последовательности — 2
Реализуйте функцию vector<int> Reversed(const vector<int>& v), возвращающую копию вектора v, в которой числа переставлены в обратном порядке.
Пример
Вектор v		Результат функции
1, 5, 3, 4, 2  	2, 4, 3, 5, 1
	
Пояснение
В этой задаче на проверку вам надо прислать файл с реализацией функции Reversed. Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции.
	*/
	vector<int> buf;
	for(int i=v.size()-1;i>=0;i--)
	{
		buf.push_back(v[i]);
	}
	return buf;
}

void  ex16()
{
	/*
	14 Тренировочное задание по программированию: Средняя температура
Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.
Гарантируется, что среднее арифметическое значений температуры является целым числом.
Формат ввода
Вводится число N, затем N неотрицательных целых чисел — значения температуры в 0-й, 1-й, ... (N?1)-й день.
Формат вывода
Первое число K — количество дней, значение температуры в которых выше среднего арифметического. Затем K целых чисел — номера этих дней.
Пример
Ввод
5
7 6 3 0 9
Вывод
3
0 1 4

	*/
	int n,sar=0;
	cin>>n;
	vector<int> v(n);
	vector<int> res;
	for(auto &b: v )
	{
		cin>>b;
		sar+=b;
	}
	sar=sar/n;
	cout<<sar<<endl;
	for(int i=0;i<v.size();i++)
	{
		if(v[i]>sar)	
			res.push_back(i);
	}
	cout<<res.size()<<endl;
	for(auto x: res)
	{
		cout<<x<<" ";
	}
}

void ex17()
{
	/*
	15 Задание по программированию: Очередь
Люди стоят в очереди, но никогда не уходят из её начала, зато могут приходить в конец и уходить оттуда. Более того, иногда некоторые люди могут прекращать и начинать беспокоиться из-за того, что очередь не продвигается.
Реализуйте обработку следующих операций над очередью:
•	WORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
•	QUIET i: пометить i-го человека как успокоившегося;
•	COME k: добавить k спокойных человек в конец очереди;
•	COME -k: убрать k человек из конца очереди;
•	WORRY_COUNT: узнать количество беспокоящихся людей в очереди.
Изначально очередь пуста.
Формат ввода
Количество операций Q, затем описания операций.
Для каждой операции WORRY i и QUIET i гарантируется, что человек с номером i существует в очереди на момент операции.
Для каждой операции COME -k гарантируется, что k не больше текущего размера очереди.
Формат вывода
Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди.
Пример
Ввод
8
COME 5
WORRY 1
WORRY 4
COME -2
WORRY_COUNT
COME 3
WORRY 3
WORRY_COUNT

Вывод
1
2

	*/
	int count_commands;
	cin>>count_commands;
	vector<bool> quiet;
	vector<int> worry_count;
	string command;
	int value,wc=0;
	for(int i=0;i<count_commands;i++)
	{
		cin>>command;
		if(command=="WORRY"){
			cin>>value;
			quiet[value]=true;
		}else if(command=="QUIET"){
			cin>>value;
			quiet[value]=false;
		}else if(command=="COME"){
			cin>>value;
			if(value>0)
			{
				for(int j=0;j<value;j++)
				{
					quiet.push_back(false);
				}
			}else{
				for(int j=value;j<0;j++)
				{
					quiet.pop_back();
				}	
			}
		}else if(command=="WORRY_COUNT"){
		wc=0;
			for(auto b: quiet)
			{
				if(b)
					wc++;
			}	
				worry_count.push_back(wc);
		}
	}
	
	for(auto b:worry_count)
	{
		cout<<b<<endl;
	}
}

void ex18()
{
	/*	
	16 Задание по программированию: Ежемесячные дела
У каждого из нас есть ежемесячные дела, каждое из которых нужно выполнять в конкретный день каждого месяца: оплата счетов за электричество, абонентская плата за связь и пр. Вам нужно реализовать работу со списком таких дел, а именно, обработку следующих операций:
ADD i s
Добавить дело с названием s в день i.
NEXT
Закончить текущий месяц и начать новый. Если новый месяц имеет больше дней, чем текущий, добавленные дни изначально не будут содержать дел. Если же в новом месяце меньше дней, дела со всех удаляемых дней необходимо будет переместить на последний день нового месяца.
Обратите внимание, что количество команд этого типа может превышать 11.
DUMP i
Вывести все дела в день i.
Изначально текущим месяцем считается январь. Количества дней в месяцах соответствуют Григорианскому календарю с той лишь разницей, что в феврале всегда 28 дней.
Указание
Для дописывания всех элементов вектора v2 в конец вектора v1 удобно использовать метод insert:
Формат ввода
Сначала число операций Q, затем описания операций.
Названия дел s уникальны и состоят только из латинских букв, цифр и символов подчёркивания. Номера дней i являются целыми числами и нумеруются от 1 до размера текущего месяца.
Формат вывода
Для каждой операции типа DUMP в отдельной строке выведите количество дел в соответствующий день, а затем их названия, разделяя их пробелом. Порядок вывода дел в рамках каждой операции значения не имеет.
Пример
Ввод
12
ADD 5 Salary
ADD 31 Walk
ADD 30 WalkPreparations
NEXT
DUMP 5
DUMP 28
NEXT
DUMP 31
DUMP 30
DUMP 28
ADD 28 Payment
DUMP 28
Вывод
1 Salary
2 WalkPreparations Walk
0
0
2 WalkPreparations Walk
3 WalkPreparations Walk Payment
*/
	int count_commands;
	cin>>count_commands;
	vector<bool> quiet;
	vector<int> worry_count;
	string command;
	int value,wc=0;
	string s;
	for(int i=0;i<count_commands;i++)
	{
		cin>>command;
		if(command=="ADD"){
			cin>>value;
			cin>>s;
			quiet[value]=true;
		}else if(command=="NEXT"){
			cin>>value;
			quiet[value]=false;
		}else if(command=="DUMP"){
			cin>>value;
			if(value>0)
			{
				for(int j=0;j<value;j++)
				{
					quiet.push_back(false);
				}
			}else{
				for(int j=value;j<0;j++)
				{
					quiet.pop_back();
				}	
			}
		}
	}
	
	for(auto b:worry_count)
	{
		cout<<b<<endl;
	}
}

/*anagramm*/
void ex19()
{
/*
17 Тренировочное задание по программированию: Анаграммы
Слова называются анаграммами друг друга, если одно из них можно получить перестановкой букв в другом. Например, слово «eat» можно получить перестановкой букв слова «tea», поэтому эти слова являются анаграммами друг друга. Даны пары слов, проверьте для каждой из них, являются ли слова этой пары анаграммами друг друга.
Указание
Один из способов проверки того, являются ли слова анаграммами друг друга, заключается в следующем. Для каждого слова с помощью словаря подсчитаем, сколько раз в нём встречается каждая буква. Если для обоих слов эти словари равны (а это проверяется с помощью обычного оператора ==), то слова являются анаграммами друг друга, в противном случае не являются.
При этом построение такого словаря по слову удобно вынести в отдельную функцию BuildCharCounters.
Формат ввода
Сначала дано число пар слов N, затем в N строках содержатся пары слов, которые необходимо проверить. Гарантируется, что все слова состоят лишь из строчных латинских букв.
Формат вывода
Выведите N строк: для каждой введённой пары слов YES, если эти слова являются анаграммами, и NO в противном случае.
Пример
Ввод
3
eat tea
find search
master stream
Вывод
YES
NO
YES,
*/
	int h;
	cin>>h;
	string st1,st2;
	vector<string> result;
	map<char, int> first;
	map<char, int> second;	
	for(int i=0;i<h;i++)
	{
		cin>>st1>>st2;
	first.clear();
	second.clear();
		for(const char& ch:st1)
		{
			++first[ch];
		}
		for(const char& ch:st2)
		{
			++second[ch];
		}		
		
		if(first==second)
		{
			result.push_back("YES");	
		}else{
			result.push_back("NO");
		}
		
	}
	
	for(auto s :result)
	{
		cout<<s<<endl;
	}
}


void ex20()
{
	/*
		18 Тренировочное задание по программированию: Справочник столиц
		Реализуйте справочник столиц стран.
		На вход программе поступают следующие запросы:
		•	CHANGE_CAPITAL country new_capital — изменение столицы страны country на new_capital, либо добавление такой страны с такой столицей, если раньше её не было.
		•	RENAME old_country_name new_country_name — переименование страны из old_country_name в new_country_name.
		•	ABOUT country — вывод столицы страны country.
		•	DUMP — вывод столиц всех стран.
		Формат ввода
		В первой строке содержится количество запросов Q, в следующих Q строках — описания запросов. Все названия стран и столиц состоят лишь из латинских букв, цифр и символов подчёркивания.
		Формат вывода
		Выведите результат обработки каждого запроса:
		В ответ на запрос CHANGE_CAPITAL country new_capital выведите
		•	Introduce new country country with capital new_capital, если страны country раньше не существовало;
		•	Country country hasn't changed its capital, если страна country до текущего момента имела столицу new_capital;
		•	Country country has changed its capital from old_capital to new_capital, если страна country до текущего момента имела столицу old_capital, название которой не совпадает с названием new_capital.
		В ответ на запрос RENAME old_country_name new_country_name выведите
		•	Incorrect rename, skip, если новое название страны совпадает со старым, страна old_country_name не существует или страна new_country_name уже существует;
		•	Country old_country_name with capital capital has been renamed to new_country_name, если запрос корректен и страна имеет столицу capital.
		В ответ на запрос ABOUT country выведите
		•	Country country doesn't exist, если страны с названием country не существует;
		•	Country country has capital capital, если страна country существует и имеет столицу capital.
		В ответ на запрос DUMP выведите
		•	There are no countries in the world, если пока не было добавлено ни одной страны;
		•	разделённые пробелами пары country/capital, описывающие столицы всех стран и упорядоченные по названию страны, если в мире уже есть хотя бы одна страна.
		Пример 1
		Ввод
		6
		CHANGE_CAPITAL RussianEmpire Petrograd
		RENAME RussianEmpire RussianRepublic
		ABOUT RussianRepublic
		RENAME RussianRepublic USSR
		CHANGE_CAPITAL USSR Moscow
		DUMP
		Вывод
		Introduce new country RussianEmpire with capital Petrograd
		Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
		Country RussianRepublic has capital Petrograd
		Country RussianRepublic with capital Petrograd has been renamed to USSR
		Country USSR has changed its capital from Petrograd to Moscow
		USSR/Moscow
		Пример 2
		Ввод
		24
		RENAME FakeCountry FarFarAway
		ABOUT FarFarAway
		DUMP
		CHANGE_CAPITAL TsardomOfRussia Moscow
		CHANGE_CAPITAL TsardomOfRussia Moscow
		CHANGE_CAPITAL ColonialBrazil Salvador
		CHANGE_CAPITAL TsardomOfRussia SaintPetersburg
		RENAME TsardomOfRussia RussianEmpire
		CHANGE_CAPITAL RussianEmpire Moscow
		CHANGE_CAPITAL RussianEmpire SaintPetersburg
		CHANGE_CAPITAL ColonialBrazil RioDeJaneiro
		DUMP
		RENAME ColonialBrazil EmpireOfBrazil
		ABOUT RussianEmpire
		RENAME EmpireOfBrazil UnitedStatesOfBrazil
		CHANGE_CAPITAL RussianEmpire Petrograd
		RENAME RussianEmpire RussianRepublic
		RENAME RussianRepublic USSR
		CHANGE_CAPITAL USSR Moscow
		CHANGE_CAPITAL UnitedStatesOfBrazil Brasilia
		RENAME UnitedStatesOfBrazil FederativeRepublicOfBrazil
		ABOUT RussianEmpire
		DUMP
		RENAME USSR USSR
		Вывод
		Incorrect rename, skip
		Country FarFarAway doesn't exist
		There are no countries in the world
		Introduce new country TsardomOfRussia with capital Moscow
		Country TsardomOfRussia hasn't changed its capital
		Introduce new country ColonialBrazil with capital Salvador
		Country TsardomOfRussia has changed its capital from Moscow to SaintPetersburg
		Country TsardomOfRussia with capital SaintPetersburg has been renamed to RussianEmpire
		Country RussianEmpire has changed its capital from SaintPetersburg to Moscow
		Country RussianEmpire has changed its capital from Moscow to SaintPetersburg
		Country ColonialBrazil has changed its capital from Salvador to RioDeJaneiro
		ColonialBrazil/RioDeJaneiro RussianEmpire/SaintPetersburg
		Country ColonialBrazil with capital RioDeJaneiro has been renamed to EmpireOfBrazil
		Country RussianEmpire has capital SaintPetersburg
		Country EmpireOfBrazil with capital RioDeJaneiro has been renamed to UnitedStatesOfBrazil
		Country RussianEmpire has changed its capital from SaintPetersburg to Petrograd
		Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
		Country RussianRepublic with capital Petrograd has been renamed to USSR
		Country USSR has changed its capital from Petrograd to Moscow
		Country UnitedStatesOfBrazil has changed its capital from RioDeJaneiro to Brasilia
		Country UnitedStatesOfBrazil with capital Brasilia has been renamed to FederativeRepublicOfBrazil
		Country RussianEmpire doesn't exist
		FederativeRepublicOfBrazil/Brasilia USSR/Moscow
		Incorrect rename, skip

	*/
	int q;
	cin>>q;
	string country, capial, oldCapital,oldCountry;
	map<string,string> mCountry;
	vector<string> out;
	for(int i=0;i<q;i++)
	{
			cin>>command;
			if(command=="CHANGE_CAPITAL")
			{
				cin>>country;
				cin>>capital;
				if(mCountry[country]=="")
				{
					out.push_back("Introduce new country "+country+" with capital "+new_capital+"\n");
					mCountry[country=capital];
				}else if(mCountry[country]==capital)
				{
					out.push_back("Country "+country+" hasn't changed its capital\n");
					mCountry[country=capital];
				}else
				{
					oldCapital=mCountry[country];
					mCountry[country]=capital;
					out.push_back("Country "+country+" has changed its capital from "+oldCapital+" to "+capital+"\n");
				}
			}else if(command=="RENAME")
			{
				cin>>country;
				cin>>old_country;
   					if(){
					   	  	out.push_back( "Incorrect rename, skip\n" );
					/*	если новое название страны совпадает со старым,
						 страна 
						 old_country_name не существует или страна 
						 new_country_name уже существует;*/
   						
					   }else{
					   		 out.push_back("Country "+old_country_name+" with capital capital has been renamed to "+new_country_name+"\n");
							/*, если запрос корректен и страна имеет столицу capital.*/
					   }

			}else if(command=="ABOUT")
			{
				cin>>country;
				out.push_back("Country "+country+" doesn't exist\n");
				 /*, если страны с названием country не существует;*/
				out.push_back("Country "+country+" has capital "+capital+"\n");
				  /*, если страна country существует и имеет столицу capital.*/
			}else if(command=="DUMP")
			{
				if(mCountry.size()==0)	
				{
					out.push_back("There are no countries in the world");
				}else{
					for(auto string& str:mCountry)
					{
						out.push_back(str.first+"/"+str.second+"\n");
				
					}
					
				}

	/*, если пока не было добавлено ни одной страны;*/
   /* разделённые пробелами пары country/capital, описывающие
    столицы всех стран и упорядоченные по названию страны, 
	если в мире уже есть хотя бы одна страна./*/

			}

	}
	for(const string &str:result)
	{
		 
		
/*
 * 6
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME RussianEmpire RussianRepublic
ABOUT RussianRepublic
RENAME RussianRepublic USSR
CHANGE_CAPITAL USSR Moscow
DUMP


24
RENAME FakeCountry FarFarAway
ABOUT FarFarAway
DUMP
CHANGE_CAPITAL TsardomOfRussia Moscow
CHANGE_CAPITAL TsardomOfRussia Moscow
CHANGE_CAPITAL ColonialBrazil Salvador
CHANGE_CAPITAL TsardomOfRussia SaintPetersburg
RENAME TsardomOfRussia RussianEmpire
CHANGE_CAPITAL RussianEmpire Moscow
CHANGE_CAPITAL RussianEmpire SaintPetersburg
CHANGE_CAPITAL ColonialBrazil RioDeJaneiro
DUMP
RENAME ColonialBrazil EmpireOfBrazil
ABOUT RussianEmpire
RENAME EmpireOfBrazil UnitedStatesOfBrazil
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME RussianEmpire RussianRepublic
RENAME RussianRepublic USSR
CHANGE_CAPITAL USSR Moscow
CHANGE_CAPITAL UnitedStatesOfBrazil Brasilia
RENAME UnitedStatesOfBrazil FederativeRepublicOfBrazil
ABOUT RussianEmpire
DUMP
RENAME USSR USSR


*/

	}
}


void ex21()
{



/*Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:

    NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
    BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
    STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
    ALL_BUSES — вывести список всех маршрутов с остановками.

Формат ввода

В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.

Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.

Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что маршрут bus отсутствует, количество остановок больше 0, а после числа stop_count следует именно такое количество названий остановок, причём все названия в каждом списке различны.
Формат вывода

Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:

    На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих через эту остановку, в том порядке, в котором они создавались командами NEW_BUS. Если остановка stop не существует, выведите No stop.
    На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке, в котором они были заданы в соответствующей команде NEW_BUS. Описание каждой остановки stop должно иметь вид Stop stop: bus1 bus2 ..., где bus1 bus2 ... — список автобусов, проезжающих через остановку stop, в порядке, в котором они создавались командами NEW_BUS, за исключением исходного маршрута bus. Если через остановку stop не проезжает ни один автобус, кроме bus, вместо списка автобусов для неё выведите no interchange. Если маршрут bus не существует, выведите No bus.
    На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. Описание каждого маршрута bus должно иметь вид Bus bus: stop1 stop2 ..., где stop1 stop2 ... — список остановок автобуса bus в порядке, в котором они были заданы в соответствующей команде NEW_BUS. Если автобусы отсутствуют, выведите No buses.

Предупреждение

Условие задачи выше содержит много важных деталей. Если вы не уверены в том, что не упустили ни одной, перечитайте условие ещё раз.
Пример
10
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES
*/
}


void ex22()
{
	/*
	 * В этой задаче вам нужно присваивать номера автобусным маршрутам.

А именно, для каждого маршрута, заданного набором названий остановок, нужно либо выдать новый номер (первому маршруту — 1, второму — 2 и т. д.), либо вернуть номер существующего маршрута, которому соответствует такой набор остановок.

Наборы остановок, полученные друг из друга перестановкой остановок, считаются различными (см. пример).
Указание

В C++ ключом словаря может быть не только число или строка, но и другой контейнер, например, vector.
Формат ввода

Сначала вводится количество запросов Q, затем Q описаний запросов.

Каждый запрос представляет собой положительное количество остановок N, за которым следуют разделённые пробелом N различных названий остановок соответствующего маршрута. Названия остановок состоят лишь из латинских букв и символов подчёркивания.
Формат вывода

Выведите ответ на каждый запрос в отдельной строке.

Если маршрут с данным набором остановок уже существует, в ответ на соответствующий запрос выведите Already exists for i, где i — номер маршрута с таким набором остановок. В противном случае нужно выделить введённому набору остановок новый номер i и вывести его в формате New bus i.
Пример
Ввод.


4
2 Marushkino Kokoshkino
1 Kokoshkino
2 Marushkino Kokoshkino
2 Kokoshkino Marushkino
	 *
	 * Замечание

Будьте внимательны при обновлении словаря: если одновременно в одном выражении вычислять размер словаря и добавлять в него новый элемент, результат может отличаться от ожидаемого на единицу. Чтобы этого избежать, используйте временную переменную.

Например, вместо кода

map<string, int> m;
// ...
m["two"] = m.size();
// что нужно сделать раньше: вычислить size или добавить новый ключ?

стоит написать такой код:

map<string, int> m;
// ...
int new_value = m.size();
m["two"] = new_value;
// теперь всё однозначно: нужен размер до добавления элемента
 * */
}


void ex23()
{
/*
21 Тренировочное задание по программированию: Количество уникальных строк
Дан набор строк. Найдите количество уникальных строк в этом наборе.
Формат ввода
Сначала вводится количество строк N, затем — сами N строк, разделённые пробелом. Все строки состоят лишь из латинских букв, цифр и символов подчёркивания.
Формат вывода
Выведите единственное целое число — количество уникальных строк в данном наборе.
Пример
Ввод
6
first
second
first
third
second
second

Вывод
3
*/
	int n;
	cin>>n;
	map<string,int> str;
	string word;
	for(int i=0;i<n;i++)
	{
		cin>>word
		str['word']++;		
	}
	for(auto const &j: str)
	{
		if(j.)
		
	}

}

int main()
{
	ex19();
/*	vector<string> words={"abacaba","aba","weew","bro","code"};
//	vector<string> res={"ddf","bgf"};
	vector<int> res={1,2,23,6,9,7};
	vector<int> ret;
	ret=Reversed(res);
//	MoveString(words,res);
	for(auto w:res)
	{
		cout<<w<<" ";
	}
	cout<<endl<<"------------------------------------"<<endl;
	for(auto w:ret)
	{
		cout<<w<<" ";
	}	
/*	int x,y;
	cin>>x>>y;
	UpdateIfGreater(x,y);
	cout<<y;
	
//	string str;
//	cin>>str;
//	cin>>x;
//	cout<<IsPalindrom(str);
//ex8();*/
	return 0;
}
