#include <bits/stdc++.h>
using namespace std;

static int ccc=0;
const int d_size = 25;
  
struct team {
    string team_name;
	tuple <string, int, int> team_info;
    team* next;
    team* prev;
};

class match {
public: 
    team **winning_team, **losing_team;

    match()
    {
        winning_team = new team*[d_size];
        losing_team = new team*[d_size];
        for (int i = 0; i < d_size; i++) {
            winning_team[i] = NULL;
            losing_team[i] = NULL;
        }
    }

int findvalue(string team_name,map<string,int> m)
    {
        auto itr=m.find(team_name);
		return itr->second;
    }
    
bool tfind(string team_name,map<string,int> m)
    {
		if(m.find(team_name)!= m.end())
    	{
			return 1;
		}
		else
		{
			return 0;
		}
	}

void add(string team_name, tuple <string, int, int> value, map<string,int> m)
    {
        int hh_val = findvalue(team_name,m);
        team* entry = winning_team[hh_val];
  
        if (entry == NULL) {
            entry = new team;
            entry->team_info= value;
            entry->team_name = team_name;
            entry->next = NULL;
            entry->prev = NULL;
            winning_team[hh_val] = entry;
            losing_team[hh_val] = entry;
        }
        else {
            while (entry != NULL)
                entry = entry->next;
  
            entry = new team;
            entry->team_info= value;
            entry->team_name = team_name;
            entry->next = NULL;
            entry->prev = losing_team[hh_val];
            losing_team[hh_val]->next = entry;
            losing_team[hh_val] = entry;
        }
    }

void disp(string team_name,map<string,int> m)
{
    int hh_val = findvalue(team_name,m);
    team* entry = winning_team[hh_val];
    while (entry != NULL)
    {
    	cout<<get<0>(entry->team_info)<<" of "<<entry->team_name<<" scored "<<get<1>(entry->team_info)<<" runs and took "<<get<2>(entry->team_info)<<" wickets"<<endl;
		entry = entry->next;
	}
}



};
int main()
	{
		match m1;
		map<string,int> m;
		static int count=0;
		//goto or while loop for returning
		int tt1;
		cout<<"Enter the number of fixtures played :";
		cin>>tt1;
		while(tt1--)
		{
		string s1,s2;
		int matchr1=0,matchr2=0,matchr3,matchr4;//match1 and match3, match2 and match4 are the runs scored by the winning and losing teams(scored and extras)
		cout<<"Enter the names of the winning team :"; 
		cin>>s1;
		cout<<"Enter the names of the losing team :"; 
		cin>>s2;// function in the next line takes input as string
			if(m1.tfind(s1,m)==0)
			{
			ccc++;
			m.insert({s1,count});
	        count++;
	        }
	        if(m1.tfind(s2,m)==0)
			{
			ccc++;
			m.insert({s2,count});
	        count++;
	        }
		for(int i=0;i<2;i++)
		{
			string ss;
			int matchrr=0;
			if(i==0)
			{
				ss=s1;
				cout<<"Enter the number of players of the winning team who either scored runs or took wickets(or both) :";
			}
			else
			{
				ss=s2;
				cout<<"Enter the number of players of the losing team who either scored runs or took wickets(or both) :";
			}
			int kk;
			cin>>kk;
			while(kk--)
			{
				string a1;
				repeat1:
				cout<<"Enter the name, runs and wickets taken respectively :";
				int a2, a3;
				cin>>a1>>a2>>a3;
				if(a2==0 && a3==0)
				{
					cout<<endl<<"As per the data "<<a1<<" scored 0 runs and took 0 wickets "<<endl;
					cout<<"To change the entry enter 1 and to register the player with the data provided enter 0 :";
					bool dc;
					cin>>dc;
					if(dc==1)
					{
						cout<<endl;
						goto repeat1;
					}
				}
				matchrr+=a2;
				tuple <string, int, int> tt;
				tt = make_tuple(a1,a2,a3);
			}
			if(i==0)
			{
				matchr1+=matchrr;
			}
			else
			{
				matchr2+=matchrr;
			}
		}
		cout<<"Enter the extra runs scored by the winning team :";
		cin>>matchr3;
		cout<<"Enter the extra runs scored by the losing team :";
		cin>>matchr4;
		cout<<"MATCH SUMMARY :"<<endl;
		cout<<"In this match between "<<s1<<" and "<<s2<<endl<<s1<<" won by "<<(matchr1+matchr3)-(matchr2+matchr4)<<" runs"<<endl<<endl;
	}
		int tt2;
		cout<<"Enter the number of teams whose player stats you want to view :";
		cin>>tt2;
		while(tt2--)
		{
			cout<<"Team name :";
			string sk;
			cin>>sk;
			cout<<sk<<":"<<endl;
			m1.disp(sk,m);
			cout<<endl;
		}
		int ch,chh;
		maxx:
        cout<<"enter 1 to find highest run scorer "<<"\n"<<"enter 2 to find highest wicket taker"<<endl;
        cin>>ch;
	return 0;
}