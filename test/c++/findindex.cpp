#include <iostream>
#include <string>
using namespace std;
#define Buf 100
int main()
{
	string s;
	while(cin>>s)
	{
		int len=s.size();
		for(int i=0;i<len-1;i++)	
		{
			bool first=false;
			if(s[i]=='#')continue;	
			for(int j=i+1;j<len;j++)
			{
				//cout<<s[j]<<s[i]<<endl;
				if(s[j]==s[i])
				{
					if(!first)
					{
						cout<<s[i]<<","<<i<<";";
	 					first=true;
					}
					cout<<s[j]<<","<<j<<";";
	            	s[j]='#'; 
				}
				   
			}	
		  	if(first)
		  		cout<<endl;
		}
	}
	
	return 0;

}