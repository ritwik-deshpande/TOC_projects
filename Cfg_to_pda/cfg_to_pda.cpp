#include <iostream>
#include<bits/stdc++.h>

#define ep ε

using namespace std;

void printV1(vector<string> v)
{
	cout<<"d(";
	for (int i = 0; i < v.size(); ++i)
	{
		/* code */
		if(i<v.size()-1)
			cout<<v[i]<<",";
		else
			cout<<v[i];
	}
	cout<<")";
}
void printV(vector<pair<string,string> > v)
{
	cout<<"{";
	//cout<<"The size:"<<v.size()<<endl;
	for (int i = 0; i < v.size(); ++i)
	{
		/* code */
		if(i<v.size()-1)
			cout<<"("<<v[i].first<<","<<v[i].second<<"),";
		else
			cout<<"("<<v[i].first<<","<<v[i].second<<")";
	}
	cout<<"}"<<endl;
}
void print(map<vector<string> ,vector<pair<string,string> > > m)
{
	map<vector<string> ,vector<pair<string,string> > >:: iterator it;
	for(it=m.begin();it!=m.end();++it)
	{
		printV1(it->first);
		cout<<"->";
		printV(it->second);
		cout<<endl;
	}
}
int main(int argc, char const *argv[])
{
	ifstream fin;
	int n,c=0,i;
	fin.open("/home/ritwik/Desktop/cfg_to_pda");
	map<vector<string> ,vector<pair<string,string> > > m;
	string line,word;
	cout<<"Enter the number of productions:"<<endl;
	cin>>n;
	string t;
	pair<string,string>final;
	vector<string> terminals;
	vector<string> transition;
	for(int j=0;j<n;j++)
	{
		getline(fin,line);
		i=0;
		word="";
		//cout<<"The string enterd is:"<<line<<endl;
		while(line[i]!='-')
		{
			word=word+line[i];
			i++;
		}
		transition.push_back("q");
		transition.push_back("e");
		transition.push_back(word);
		i=i+2;
		while(i<line.size())
		{
			word="";
			while(i<line.size() && line[i]!='|')
			{
				if(line[i]< 'A' || line[i] > 'Z')
				{
					t=line[i];
					terminals.push_back(t);
				}
				word=word+line[i];
				i++;
			}
			i++;
			final.first="q";
			final.second=word;
			//cout<<"The word is:"<<word<<endl;
			m[transition].push_back(final);
			// Storing each transition in map
		}
		
		//print(m);
		transition.clear();
	}
	sort(terminals.begin(),terminals.end());
	terminals.erase(unique(terminals.begin(),terminals.end()),terminals.end());
	// Add transitions for terminal symbols
	for (int j = 0; j < terminals.size(); ++j)
	{
		/* code */
		if(terminals[j].compare("e")!=0)
		{
			transition.push_back("q");
			transition.push_back(terminals[j]);
			transition.push_back(terminals[j]);
			final.first="q";
			final.second="e";
			m[transition].push_back(final);
			transition.clear();
		}
	}
	print(m);
	return 0;
}