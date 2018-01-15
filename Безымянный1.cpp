#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
	vector<int> nums={1,2,2,3,4,5};
	string str="abcdefg";
	for(int a:nums)
	{
		cout<<a<<"; ";
	}
	cout<<endl;
	for(char c:str)
	{
		cout<<c<<',';
	
	}
	return 0;
}
