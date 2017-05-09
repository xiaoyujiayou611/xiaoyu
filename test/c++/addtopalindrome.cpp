#include <iostream>
//#include <cstring>
#include <string>
using namespace std;
string addToPalindrome(string A,int n);
//string temp=new string();
int main()
{
	string A="abbbbbaa";
	string s(11,' ');
	s=addToPalindrome(A,8);
	cout<<s<<endl;
	return 0;
}

string addToPalindrome(string A,int n)
{
	string temp(n-1,' ');
	int l=0;
	int timesoflast[n-1];
	/*if(n<=2&&A[1] != A[0])
		temp=A[0];
	else
	{	*/
		int j=0,t=0,k=0,i;
		for(i=0;i<n-1;i++)
			if(A[n-1]==A[i])
				timesoflast[j++]=i;

		for(i=0;i<j;i++)
		{
			t=timesoflast[i];
			cout<<i<<endl;
			for(k=n-1;k>t;k--)
			{
				
				if(A[k]!= A[t])
				{
					//cout<<t<<","<<k<<endl;
					cout<<A[t]<<A[k]<<endl;
					break;
				}
						
				else
				{
					cout<<t<<","<<k<<endl;
					cout<<A[t]<<A[k]<<endl;
					t++;

				} 
				if(t-k==1 || t==k)
				break;
			}	
			//if(timesoflast[i]==n-2)
				//k++;	
			if(t-k==1 || t==k)
				break;
		}
		
		cout<<i<<","<<j<<endl;
		cout<<t<<","<<k<<endl;
		if(i==j)//&& !(t-k==1 || t==k))
			while(n-2>=0)
			{
				temp[l++]=A[n-2];
				n--;
			}	
		else
		{
			//cout<<"1"<<endl;
			k=timesoflast[i]-1;
			cout<<k<<endl;
			while(k>=0)
				temp[l++]=A[k--];

		}
					
	
	//cout<<l<<endl;

	string result=temp.substr(0,l);
	//result=temp;
	return result;
}