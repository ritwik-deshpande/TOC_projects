#include <iostream>
#include<bits/stdc++.h>

using namespace std;

void print(vector< vector<string> > t) 
{
	int row=t.size();
	int col=t[0].size();
	cout<<"States ";
	for (int i = 0; i < col; ++i)
	{
		/* code */
		cout<<i<<" ";
	}
	cout<<endl;
	for (int i = 0; i < row; ++i)
	{
		/* code */
		for (int j = 0; j < col; ++j)
		{
			/* code */
			cout<<t[i][j]<<" ";
		}
		cout<<endl;
	}
}

void printid(map<string,int> m)
{
	map<string,int> ::iterator i;
	for ( i=m.begin();i!=m.end(); ++i)
	{
		/* code */
		cout<<i->first<<" "<<i->second<<endl;
	}
	cout<<endl;
}

void printV(vector<string> v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		/* code */
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

bool check(vector<string> v,string s)
{
	for (int i = 0; i < v.size(); ++i)
	{
		/* code */
		if(s.compare(v[i])==0)
			return true;
	}
	return false;
}
void removeUnreachable(vector< vector<string> >& t,vector<string> &states,map<string,int> & id)
{
	vector<string> :: iterator it=states.begin();
	vector< vector<string> >:: iterator it2=t.begin();
	int flag=0;
	for(int i=1;i<states.size();i++)
	{
		flag=0;
		for(int j=0;j<t.size();j++)
		{
			if(i!=j)
			{
				if(check(t[j],states[i]))
					flag=1;
			}
		}
		if(flag==0)
		{
			//cout<<"Erasing the element:"<<states[i]<<endl;
			id.erase(states[i]);
			states.erase(it+i);
			t.erase(it2+i);
		}
	}
}
int main()
{
	int s,inp,c,grp=2,stop=0;
	string word,line;
	ifstream fin;
	cout<<"Constructing transition table:"<<endl;
	cout<<"Enter the number of states and number of input symbols respectively:"<<endl;
	cin>>s;
	cin>>inp;
	map<string,int>  id;
	vector< vector<string> > t;
	vector<string> states;
	// map containg id for each state.
	cout<<"Fill up the transition table:"<<endl;
	cout<<"Assuming 'n' input symbols then they are 0 1 2 3 .....n-1"<<endl;
	fin.open("/home/ritwik/Desktop/dfa");

	for (int i = 0; i < s; ++i)
	{
		/* code */
		getline(fin,line);
		stringstream ss(line);
		c=0;
		vector<string> tr;
		while(ss >> word)
		{
			if(c==0)
			{
				if(word[word.size()-1]=='f')
				{
					id.insert(make_pair(word,1));
				}
				else
				{
					id.insert(make_pair(word,0));
				}
				states.push_back(word);
			}
			else
				tr.push_back(word);
			c++;
		}
		t.push_back(tr);
	}
	//print(t);
	removeUnreachable(t,states,id);
	// print(t);
	// printV(states);
	// printid(id);
	int epoch=s-1;
	while(epoch--)
	{
		//Iterating through each transition
		for(int i=0;i<t[0].size();i++)
		{
			for(int j=0;j<states.size();j++)
			{
				//cout<<states[j]<<" "<<t[j][i]<<endl;
				if(id[states[j]]!=id[t[j][i]])
				{
					id[states[j]]=id[t[j][i]]+1;
				}
			}
			//printid(id);
		}
	}
	//printid(id);
	map<int,vector<string> > ans;
	map<string,int> ::iterator it;
	map<int,vector<string> > ::iterator it2;
	for (it=id.begin();it!=id.end(); ++it)
	{
		/* code */
		ans[it->second].push_back(it->first);
		//cout<<it->second<<" "<<it->first<<endl;
	}

	for(it2=ans.begin();it2!=ans.end();it2++)
	{
		printV(it2->second);
	}
	return 0;
}