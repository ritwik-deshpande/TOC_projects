#include <iostream>
#include<bits/stdc++.h>

using namespace std;

void print(string start,vector<string> end)
{
	cout<<start<<"->";
	for (int i = 0; i < end.size(); ++i)
	{
		/* code */
		cout<<end[i];
	}
	cout<<endl;
}
void printS(vector<string> v)
{
	for(int i=0;i<v.size();i++)
	{
		cout<<v[i];
	}
}
void printV(vector< vector <string> > v)
{
	for(int i=0;i<v.size();i++)
	{
		if(i<v.size()-1)
		{
			printS(v[i]);
			cout<<"|";
		}
		else
			printS(v[i]);
	}
}
void recur(string start,vector<string> end,map<string,vector<vector<string> > >& m,int count,vector<char> states)
{
	if(count<end.size()-1)
	{
		for(int i=0;i<states.size();i++)
		{
			if(count==0)
			{
				start[3]=states[i];
				end[end.size()-1][3]=states[i];
			}
			else
			{
				end[count][3]=states[i];
				end[count+1][1]=states[i];
			}
			recur(start,end,m,count+1,states);
		}
	}
	else
	{
		m[start].push_back(end);
	}
}

void recur2(string start,vector<string> end,map<string,vector<vector<string> > >& m,vector<char> states)
{
	for(int i=0;i<states.size();i++)
	{
		start[3]=states[i];
		m[start].push_back(end);
	}
}

void printM(map<string,vector<vector<string> > >  m)
{
	map<string,vector<vector<string> > > :: iterator it;
	for(it=m.begin();it!=m.end();it++)
	{
		cout<<it->first<<"->";
		printV(it->second);
		cout<<endl;
	}
}

void init(string start,vector<string> end,map<string,vector<vector<string> > >& m,vector<char> states)
{
	string temp="";
	temp+='[';
	temp+='a';
	temp+='Z';
	temp+=' ';
	temp+=']';
	for(int i=0;i<states.size();i++)
	{
		temp[3]=states[i];
		end.push_back(temp);
		m[start].push_back(end);
		end.clear();
	}
}
int main()
{
	ifstream fin;
	int n,c=0,j;
	string word,line;
	string start="";
	string temp="";
	fin.open("/home/ritwik/Desktop/pda_to_cfg");

	map<string,vector<vector<string> > > m;
	cout<<"Enter the number of states:"<<endl;
	cin>>n;
	vector<char> states;
	vector<string> end;
	char t;
	for (int i = 0; i < n; ++i)
	{
		/* code */
		t='a'+i;
		states.push_back(t);
	}
	start="S";
	init(start,end,m,states);
	cout<<"Enter the number of transitions:"<<endl;
	cin>>n;
	for (int i = 0; i < n; ++i)
	{
		/* code */
		getline(fin,line);
		j=1;
		word="";
		start="";
		temp="";
		while(j<line.size() && line[j]!='-')
		{
			if(line[j]=='(')
				j++;
			else if(line[j]==')')
				j++;
			else{
				if(line[j]!=',')
					word=word+line[j];
				j++;
			}
		}
		j=j+2;
		start+='[';
		start+=word[0];
		start+=word[2];
		start+=' ';
		start+=']';
		string a="";
		a+=word[1];
		end.push_back(a);
		word="";
		j++;
		while(j<line.size())
		{
			if(line[j]=='(')
				j++;
			else if(line[j]==')')
				j++;
			else{
				if(line[j]!=',')
				{
					word=word+line[j];
				}
			}
			j++;
		}
		c=0;
		//cout<<"THe value of word is:"<<word[1]<<endl;
		if(word[1]!='e' && word[0]!='e')
		{
			for (int k = 1; k < word.size(); ++k)
			{
				/* code */
				temp="";
				if(c==0)
				{
					temp+='[';
					temp+=word[0];
					temp+=word[k];
					temp+=' ';
					temp+=']';
				}
				else
				{
					temp+='[';
					temp+=' ';
					temp+=word[k];
					temp+=' ';
					temp+=']';
				}
				end.push_back(temp);
				c++;
			}
			recur(start,end,m,0,states);
		}
		else
		{
			recur2(start,end,m,states);
		}
		//print(start,5,end);
		//printM(m);
	    //cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
		end.clear();
	}
	printM(m);
	return 0;
}