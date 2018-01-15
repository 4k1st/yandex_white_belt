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
5 ������� �� ����������������: ���������� ����� ��������
� stdin ���� ��� ����������� �����. ����� �� ���������� ����� ��������.
������
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
6 ������� �� ����������������: �������� �����
�� ���� ���� ����� ������������� ����� N. �������� ��� � �������� ������� ��������� ��� ������� �����.
������
stdin	stdout
5	101
32	100000
1	1
���������
�	����� N ����� ��������� � ���������� ���� int
�	� ���� ������ ��� ����� ����������� ��������� vector; ����������, ��� ���������� �������� x � ����� ������� v �������� ���: v.push_back(x);

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
/*7 ������� �� ����������������: ���������
�������� �������, �������
�	���������� Factorial
�	���������� int
�	��������� int � ���������� ��������� ������ ���������. �������������, ��� �������� ������� �� ������ �� ��������� 10. ��� ������������� ���������� ������� ������ ���������� 1.
�������� �������	���������
1	1
-2	1
4	24
���������
� ���� ������ �� �������� ��� ���� �������� ���� � ����������� ������� Factorial. ���� ���� �� ������ ��������� ������� main. ���� � �� ����� ������� main, �� �������� ������ ����������
*/
	if(a<=0)
		return 1;
	return a*Factorial(a-1);
}

/*ex10*/
bool IsPalindrom(string str)
{
	/*
8 ������������� ������� �� ����������������: ���������
�������� �������, �������
�	���������� IsPalindrom
�	���������� bool
�	��������� �������� ���� string � ����������, �������� �� ���������� ������ �����������
��������� - ��� ����� ��� �����, ������� ��������� �������� ����� ������� � ������ ������.
�������� �������	���������
madam	true
gentleman	false
���������
� ���� ������ �� �������� ��� ���� �������� ���� � ����������� ������� IsPalindrom. ���� ���� �� ������ ��������� ������� main. ���� � �� ����� ������� main, �� �������� ������ ����������.

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
9 ������� �� ����������������: ����� �����������
�������� �������, �������
�	���������� PalindromFilter
�	���������� vector<string>
�	��������� vector<string> words � int minLength � ���������� ��� ������ �� ������� words, ������� �������� ������������ � ����� ����� �� ������ minLength
������� ������ �������� �� ����� 100 �����, ����� ������ ������ �� ������ 100 ��������.
�������
words	minLength	���������
abacaba, aba	5	abacaba
abacaba, aba	2	abacaba, aba
weew, bro, code	4	weew
���������
� ���� ������ ��� ���� �������� �� �������� ���� � ����������� ������� PalindromFilter, � ����� ������ �������, ���� ��� ���������� (��������, ������� �������� �� ���������). ���� ���� �� ������ ��������� ������� main. ���� � �� ����� ������� main, �� �������� ������ ����������.
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
	10 ������������� ������� �� ����������������: ������������
�������� ������� UpdateIfGreater, ������� ��������� ��� ������������� ���������: first � second. ���� first �������� ������ second, ���� ������� ������ ���������� � second �������� ��������� first. ��� ���� ��������� ��������� second ������ ���� ����� �� ���������� �������.
������
���������
� ���� ������ �� �������� ��� ���� �������� ���� � ����������� ������� UpdateIfGreater. ���� ���� �� ������ ��������� ������� main. ���� � �� ����� ������� main, �� �������� ������ ����������.

	*/
	if(a>b)
		b=a;
}

/*ex13*/
void MoveString(vector<string> &source,vector<string> &destination)
{
	/*
	11 ������� �� ����������������: ����������� �����
�������� ������� MoveStrings, ������� ��������� ��� ������� �����, source � destination, � ���������� ��� ������ �� ������� ������� � ����� �������. ����� ���������� ������� ������ source ������ ��������� ������.
����� �������� ���������� �������, ���� ������� � ���� ����� clear:
������
���������
� ���� ������ �� �������� ��� ���� �������� ���� � ����������� ������� MoveStrings. ���� ���� �� ������ ��������� ������� main. ���� � �� ����� ������� main, �� �������� ������ ����������.

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
	12 ������� �� ����������������: �������� ������������������
���������� ������� void Reverse(vector<int>& v), ������� ������������ �������� ������� � �������� �������.
������
���������
� ���� ������ �� �������� ��� ���� �������� ���� � ����������� ������� Reverse. ���� ���� �� ������ ��������� ������� main. ���� � �� ����� ������� main, �� �������� ������ ����������.

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
	13 ������������� ������� �� ����������������: �������� ������������������ � 2
���������� ������� vector<int> Reversed(const vector<int>& v), ������������ ����� ������� v, � ������� ����� ������������ � �������� �������.
������
������ v		��������� �������
1, 5, 3, 4, 2  	2, 4, 3, 5, 1
	
���������
� ���� ������ �� �������� ��� ���� �������� ���� � ����������� ������� Reversed. ���� ���� �� ������ ��������� ������� main. ���� � �� ����� ������� main, �� �������� ������ ����������.
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
	14 ������������� ������� �� ����������������: ������� �����������
���� �������� �����������, ������������� � ������� N ������ ������ ����. ������� ������ ���� (� ��������� � ����) �� ��������� ����������� ���� �������� ��������������� �� ��� N ����.
�������������, ��� ������� �������������� �������� ����������� �������� ����� ������.
������ �����
�������� ����� N, ����� N ��������������� ����� ����� � �������� ����������� � 0-�, 1-�, ... (N?1)-� ����.
������ ������
������ ����� K � ���������� ����, �������� ����������� � ������� ���� �������� ���������������. ����� K ����� ����� � ������ ���� ����.
������
����
5
7 6 3 0 9
�����
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
	15 ������� �� ����������������: �������
���� ����� � �������, �� ������� �� ������ �� � ������, ���� ����� ��������� � ����� � ������� ������. ����� ����, ������ ��������� ���� ����� ���������� � �������� ������������ ��-�� ����, ��� ������� �� ������������.
���������� ��������� ��������� �������� ��� ��������:
�	WORRY i: �������� i-�� �������� � ������ ������� (� ��������� � 0) ��� ��������������;
�	QUIET i: �������� i-�� �������� ��� ��������������;
�	COME k: �������� k ��������� ������� � ����� �������;
�	COME -k: ������ k ������� �� ����� �������;
�	WORRY_COUNT: ������ ���������� ������������� ����� � �������.
���������� ������� �����.
������ �����
���������� �������� Q, ����� �������� ��������.
��� ������ �������� WORRY i � QUIET i �������������, ��� ������� � ������� i ���������� � ������� �� ������ ��������.
��� ������ �������� COME -k �������������, ��� k �� ������ �������� ������� �������.
������ ������
��� ������ �������� WORRY_COUNT �������� ���� ����� ����� � ���������� ������������� ����� � �������.
������
����
8
COME 5
WORRY 1
WORRY 4
COME -2
WORRY_COUNT
COME 3
WORRY 3
WORRY_COUNT

�����
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
	16 ������� �� ����������������: ����������� ����
� ������� �� ��� ���� ����������� ����, ������ �� ������� ����� ��������� � ���������� ���� ������� ������: ������ ������ �� �������������, ����������� ����� �� ����� � ��. ��� ����� ����������� ������ �� ������� ����� ���, � ������, ��������� ��������� ��������:
ADD i s
�������� ���� � ��������� s � ���� i.
NEXT
��������� ������� ����� � ������ �����. ���� ����� ����� ����� ������ ����, ��� �������, ����������� ��� ���������� �� ����� ��������� ���. ���� �� � ����� ������ ������ ����, ���� �� ���� ��������� ���� ���������� ����� ����������� �� ��������� ���� ������ ������.
�������� ��������, ��� ���������� ������ ����� ���� ����� ��������� 11.
DUMP i
������� ��� ���� � ���� i.
���������� ������� ������� ��������� ������. ���������� ���� � ������� ������������� �������������� ��������� � ��� ���� ��������, ��� � ������� ������ 28 ����.
��������
��� ����������� ���� ��������� ������� v2 � ����� ������� v1 ������ ������������ ����� insert:
������ �����
������� ����� �������� Q, ����� �������� ��������.
�������� ��� s ��������� � ������� ������ �� ��������� ����, ���� � �������� �������������. ������ ���� i �������� ������ ������� � ���������� �� 1 �� ������� �������� ������.
������ ������
��� ������ �������� ���� DUMP � ��������� ������ �������� ���������� ��� � ��������������� ����, � ����� �� ��������, �������� �� ��������. ������� ������ ��� � ������ ������ �������� �������� �� �����.
������
����
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
�����
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
17 ������������� ������� �� ����������������: ���������
����� ���������� ����������� ���� �����, ���� ���� �� ��� ����� �������� ������������� ���� � ������. ��������, ����� �eat� ����� �������� ������������� ���� ����� �tea�, ������� ��� ����� �������� ����������� ���� �����. ���� ���� ����, ��������� ��� ������ �� ���, �������� �� ����� ���� ���� ����������� ���� �����.
��������
���� �� �������� �������� ����, �������� �� ����� ����������� ���� �����, ����������� � ���������. ��� ������� ����� � ������� ������� ����������, ������� ��� � �� ����������� ������ �����. ���� ��� ����� ���� ��� ������� ����� (� ��� ����������� � ������� �������� ��������� ==), �� ����� �������� ����������� ���� �����, � ��������� ������ �� ��������.
��� ���� ���������� ������ ������� �� ����� ������ ������� � ��������� ������� BuildCharCounters.
������ �����
������� ���� ����� ��� ���� N, ����� � N ������� ���������� ���� ����, ������� ���������� ���������. �������������, ��� ��� ����� ������� ���� �� �������� ��������� ����.
������ ������
�������� N �����: ��� ������ �������� ���� ���� YES, ���� ��� ����� �������� �����������, � NO � ��������� ������.
������
����
3
eat tea
find search
master stream
�����
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
		18 ������������� ������� �� ����������������: ���������� ������
		���������� ���������� ������ �����.
		�� ���� ��������� ��������� ��������� �������:
		�	CHANGE_CAPITAL country new_capital � ��������� ������� ������ country �� new_capital, ���� ���������� ����� ������ � ����� ��������, ���� ������ � �� ����.
		�	RENAME old_country_name new_country_name � �������������� ������ �� old_country_name � new_country_name.
		�	ABOUT country � ����� ������� ������ country.
		�	DUMP � ����� ������ ���� �����.
		������ �����
		� ������ ������ ���������� ���������� �������� Q, � ��������� Q ������� � �������� ��������. ��� �������� ����� � ������ ������� ���� �� ��������� ����, ���� � �������� �������������.
		������ ������
		�������� ��������� ��������� ������� �������:
		� ����� �� ������ CHANGE_CAPITAL country new_capital ��������
		�	Introduce new country country with capital new_capital, ���� ������ country ������ �� ������������;
		�	Country country hasn't changed its capital, ���� ������ country �� �������� ������� ����� ������� new_capital;
		�	Country country has changed its capital from old_capital to new_capital, ���� ������ country �� �������� ������� ����� ������� old_capital, �������� ������� �� ��������� � ��������� new_capital.
		� ����� �� ������ RENAME old_country_name new_country_name ��������
		�	Incorrect rename, skip, ���� ����� �������� ������ ��������� �� ������, ������ old_country_name �� ���������� ��� ������ new_country_name ��� ����������;
		�	Country old_country_name with capital capital has been renamed to new_country_name, ���� ������ ��������� � ������ ����� ������� capital.
		� ����� �� ������ ABOUT country ��������
		�	Country country doesn't exist, ���� ������ � ��������� country �� ����������;
		�	Country country has capital capital, ���� ������ country ���������� � ����� ������� capital.
		� ����� �� ������ DUMP ��������
		�	There are no countries in the world, ���� ���� �� ���� ��������� �� ����� ������;
		�	���������� ��������� ���� country/capital, ����������� ������� ���� ����� � ������������� �� �������� ������, ���� � ���� ��� ���� ���� �� ���� ������.
		������ 1
		����
		6
		CHANGE_CAPITAL RussianEmpire Petrograd
		RENAME RussianEmpire RussianRepublic
		ABOUT RussianRepublic
		RENAME RussianRepublic USSR
		CHANGE_CAPITAL USSR Moscow
		DUMP
		�����
		Introduce new country RussianEmpire with capital Petrograd
		Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
		Country RussianRepublic has capital Petrograd
		Country RussianRepublic with capital Petrograd has been renamed to USSR
		Country USSR has changed its capital from Petrograd to Moscow
		USSR/Moscow
		������ 2
		����
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
		�����
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
					/*	���� ����� �������� ������ ��������� �� ������,
						 ������ 
						 old_country_name �� ���������� ��� ������ 
						 new_country_name ��� ����������;*/
   						
					   }else{
					   		 out.push_back("Country "+old_country_name+" with capital capital has been renamed to "+new_country_name+"\n");
							/*, ���� ������ ��������� � ������ ����� ������� capital.*/
					   }

			}else if(command=="ABOUT")
			{
				cin>>country;
				out.push_back("Country "+country+" doesn't exist\n");
				 /*, ���� ������ � ��������� country �� ����������;*/
				out.push_back("Country "+country+" has capital "+capital+"\n");
				  /*, ���� ������ country ���������� � ����� ������� capital.*/
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

	/*, ���� ���� �� ���� ��������� �� ����� ������;*/
   /* ���������� ��������� ���� country/capital, �����������
    ������� ���� ����� � ������������� �� �������� ������, 
	���� � ���� ��� ���� ���� �� ���� ������./*/

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



/*���������� ������� �������� ���������� ���������. ��� ����� ������������ ��������� �������:

    NEW_BUS bus stop_count stop1 stop2 ... � �������� ������� �������� � ��������� bus � stop_count ����������� � ���������� stop1, stop2, ...
    BUSES_FOR_STOP stop � ������� �������� ���� ��������� ��������, ���������� ����� ��������� stop.
    STOPS_FOR_BUS bus � ������� �������� ���� ��������� �������� bus �� ������� ���������, �� ������� ����� ��������� �� ������ �� ���������.
    ALL_BUSES � ������� ������ ���� ��������� � �����������.

������ �����

� ������ ������ ����� ���������� ���������� �������� Q, ����� � Q ������� ������� �������� ��������.

�������������, ��� ��� �������� ��������� � ��������� ������� ���� �� ��������� ����, ���� � ������ �������������.

��� ������� ������� NEW_BUS bus stop_count stop1 stop2 ... �������������, ��� ������� bus �����������, ���������� ��������� ������ 0, � ����� ����� stop_count ������� ������ ����� ���������� �������� ���������, ������ ��� �������� � ������ ������ ��������.
������ ������

��� ������� �������, ����� NEW_BUS, �������� ��������������� ����� �� ����:

    �� ������ BUSES_FOR_STOP stop �������� ����� ������ ������ ���������, ����������� ����� ��� ���������, � ��� �������, � ������� ��� ����������� ��������� NEW_BUS. ���� ��������� stop �� ����������, �������� No stop.
    �� ������ STOPS_FOR_BUS bus �������� �������� ��������� �������� bus � ��������� ������� � ��� �������, � ������� ��� ���� ������ � ��������������� ������� NEW_BUS. �������� ������ ��������� stop ������ ����� ��� Stop stop: bus1 bus2 ..., ��� bus1 bus2 ... � ������ ���������, ����������� ����� ��������� stop, � �������, � ������� ��� ����������� ��������� NEW_BUS, �� ����������� ��������� �������� bus. ���� ����� ��������� stop �� ��������� �� ���� �������, ����� bus, ������ ������ ��������� ��� �� �������� no interchange. ���� ������� bus �� ����������, �������� No bus.
    �� ������ ALL_BUSES �������� �������� ���� ��������� � ���������� �������. �������� ������� �������� bus ������ ����� ��� Bus bus: stop1 stop2 ..., ��� stop1 stop2 ... � ������ ��������� �������� bus � �������, � ������� ��� ���� ������ � ��������������� ������� NEW_BUS. ���� �������� �����������, �������� No buses.

��������������

������� ������ ���� �������� ����� ������ �������. ���� �� �� ������� � ���, ��� �� �������� �� �����, ����������� ������� ��� ���.
������
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
	 * � ���� ������ ��� ����� ����������� ������ ���������� ���������.

� ������, ��� ������� ��������, ��������� ������� �������� ���������, ����� ���� ������ ����� ����� (������� �������� � 1, ������� � 2 � �. �.), ���� ������� ����� ������������� ��������, �������� ������������� ����� ����� ���������.

������ ���������, ���������� ���� �� ����� ������������� ���������, ��������� ���������� (��. ������).
��������

� C++ ������ ������� ����� ���� �� ������ ����� ��� ������, �� � ������ ���������, ��������, vector.
������ �����

������� �������� ���������� �������� Q, ����� Q �������� ��������.

������ ������ ������������ ����� ������������� ���������� ��������� N, �� ������� ������� ���������� �������� N ��������� �������� ��������� ���������������� ��������. �������� ��������� ������� ���� �� ��������� ���� � �������� �������������.
������ ������

�������� ����� �� ������ ������ � ��������� ������.

���� ������� � ������ ������� ��������� ��� ����������, � ����� �� ��������������� ������ �������� Already exists for i, ��� i � ����� �������� � ����� ������� ���������. � ��������� ������ ����� �������� ��������� ������ ��������� ����� ����� i � ������� ��� � ������� New bus i.
������
����.


4
2 Marushkino Kokoshkino
1 Kokoshkino
2 Marushkino Kokoshkino
2 Kokoshkino Marushkino
	 *
	 * ���������

������ ����������� ��� ���������� �������: ���� ������������ � ����� ��������� ��������� ������ ������� � ��������� � ���� ����� �������, ��������� ����� ���������� �� ���������� �� �������. ����� ����� ��������, ����������� ��������� ����������.

��������, ������ ����

map<string, int> m;
// ...
m["two"] = m.size();
// ��� ����� ������� ������: ��������� size ��� �������� ����� ����?

����� �������� ����� ���:

map<string, int> m;
// ...
int new_value = m.size();
m["two"] = new_value;
// ������ �� ����������: ����� ������ �� ���������� ��������
 * */
}


void ex23()
{
/*
21 ������������� ������� �� ����������������: ���������� ���������� �����
��� ����� �����. ������� ���������� ���������� ����� � ���� ������.
������ �����
������� �������� ���������� ����� N, ����� � ���� N �����, ���������� ��������. ��� ������ ������� ���� �� ��������� ����, ���� � �������� �������������.
������ ������
�������� ������������ ����� ����� � ���������� ���������� ����� � ������ ������.
������
����
6
first
second
first
third
second
second

�����
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
