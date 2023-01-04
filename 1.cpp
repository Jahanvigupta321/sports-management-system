#include <bits/stdc++.h>
using namespace std;

static int ccc=0;
const int tablesize = 25;
  
struct h_node {
    string key;
	tuple <string, int, int> val;
    h_node* next;
    h_node* prev;
};

class HMap {
public: 
    h_node **hhtable, **top;

HMap()
    {
        hhtable = new h_node*[tablesize];
        top = new h_node*[tablesize];
        for (int i = 0; i < tablesize; i++) {
            hhtable[i] = NULL;
            top[i] = NULL;
        }
    }

int HFunc(string key,map<string,int> m)
    {
        auto itr=m.find(key);
		return itr->second;
    }
    
bool tfind(string key,map<string,int> m)
    {
		if(m.find(key)!= m.end())
    	{
			return 1;
		}
		else
		{
			return 0;
		}
	}

void add(string key, tuple <string, int, int> value, map<string,int> m)
    {
        int hh_val = HFunc(key,m);
        h_node* entry = hhtable[hh_val];
  
        if (entry == NULL) {
            entry = new h_node;
            entry->val= value;
            entry->key = key;
            entry->next = NULL;
            entry->prev = NULL;
            hhtable[hh_val] = entry;
            top[hh_val] = entry;
        }
        else {
            while (entry != NULL)
                entry = entry->next;
  
            entry = new h_node;
            entry->val= value;
            entry->key = key;
            entry->next = NULL;
            entry->prev = top[hh_val];
            top[hh_val]->next = entry;
            top[hh_val] = entry;
        }
    }

void ssearchup(string key, tuple <string, int, int> value, map<string,int> m)
     {
     	int hh_val = HFunc(key,m);
     	h_node* entry = hhtable[hh_val];
     	while(entry!=NULL)
     	{
     		if(get<0>(entry->val)==get<0>(value))
     		{
     			get<1>(entry->val)=get<1>(entry->val)+get<1>(value);
     			get<2>(entry->val)=get<2>(entry->val)+get<2>(value);
     			return;
			 }
			entry = entry->next;
		 }
		 add(key,value,m);
     	
	 }

void disp(string key,map<string,int> m)
{
    int hh_val = HFunc(key,m);
    h_node* entry = hhtable[hh_val];
    while (entry != NULL)
    {
    	cout<<get<0>(entry->val)<<" of "<<entry->key<<" scored "<<get<1>(entry->val)<<" runs and took "<<get<2>(entry->val)<<" wickets"<<endl;
		entry = entry->next;
	}
}
void maxrun()
{
	int dd,maxr=0;
	string maxn;
	dd=ccc;
	while(dd!=0)
	{
        h_node* entry = hhtable[dd-1];
        while (entry != NULL)
        {
        	if(get<1>(entry->val) > maxr)
        	{
        		maxr=get<1>(entry->val);
        		maxn=get<0>(entry->val);
			}
			entry = entry->next;
		}
		dd--;
	}
	cout<<"The highest run scorer is "<<maxn<<" with "<<maxr<<" runs"<<endl;
	cout<<endl;
}
void maxwicket()
{
	int dd,maxwi=0;
	string maxn;
	dd=ccc;
	while(dd!=0)
	{
        h_node* entry = hhtable[dd-1];
        while (entry != NULL)
        {
        	if(get<2>(entry->val) > maxwi)
        	{
        		maxwi=get<2>(entry->val);
        		maxn=get<0>(entry->val);
			}
			entry = entry->next;
		}
		dd--;
	}
	cout<<"The highest wicket-taker is "<<maxn<<" with "<<maxwi<<" wickets"<<endl;
	cout<<endl;
}


};
	int main()
	{
		HMap hash;
		map<string,int> m;
		static int cntt=0;
		//goto or while loop for returning
		int tttt1;
		cout<<"Enter the number of fixtures played :";
		cin>>tttt1;
		while(tttt1--)
		{
		string s1,s2;
		int matchr1=0,matchr2=0,matchr3,matchr4;//match1 and match3, match2 and match4 are the runs scored by the winning and losing teams(scored and extras)
		cout<<"Enter the names of the winning team :"; 
		cin>>s1;
		cout<<"Enter the names of the losing team :"; 
		cin>>s2;// function in the next line takes input as string
			if(hash.tfind(s1,m)==0)
			{
			ccc++;
			m.insert({s1,cntt});
	        cntt++;
	        }
	        if(hash.tfind(s2,m)==0)
			{
			ccc++;
			m.insert({s2,cntt});
	        cntt++;
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
				hash.ssearchup(ss,tt,m);
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
		/*for(int i=0;i<2;i++)
		{
			string ss2;
			if(i==0)
			{
				ss2=s1;
			}
			else
			{
				ss2=s2;
			}
			cout<<ss2<<" :"<<endl;
			hash.disp(ss2,m);
			cout<<endl;
		}*/
		cout<<"In this match between "<<s1<<" and "<<s2<<endl<<s1<<" won by "<<(matchr1+matchr3)-(matchr2+matchr4)<<" runs"<<endl<<endl;
	}
		int tttt2;
		cout<<"Enter the number of teams whose player stats you want to view :";
		cin>>tttt2;
		while(tttt2--)
		{
			cout<<"Team name :";
			string sk;
			cin>>sk;
			cout<<sk<<":"<<endl;
			hash.disp(sk,m);
			cout<<endl;
		}
			int ch,chh;
			maxx:
cout<<"enter 1 to find highest run scorer "<<"\n"<<"enter 2 to find highest wicket taker"<<endl;
cin>>ch;
if(ch==1)
{hash.maxrun();}
else if(ch==2)
{hash.maxwicket();}
else{cout<<"invalid choice entered"<<endl;
    cout<<"enter 1 to enter these details again"<<"\n"<<"enter 2 to end this program"<<endl;
    cin>>chh;
    if(chh==1)
    goto maxx;
    else{ exit(0);}
}


		return 0;
	  }