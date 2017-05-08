#include <iostream>
using namespace std;
int getLongestPalindrome(string A, int n);
int main()
{
	string A="babcaaccabab";
	int result=getLongestPalindrome(A,12);
	cout<<result<<endl;
	return 0;
}
int getLongestPalindrome(string A, int n) 
{
        // write code here
    int i,j,k;
    i=0;
    k=n-1;
    int count=0,max=0;
    int flag;
    while(i<n)
    {	
    	cout<<A[i]<<A[k]<<endl;
    	if(A[i]!=A[k])
    	{
    		count=0;
    		for(j=n-1;j>i;j--)
        		if(A[i]==A[j])
            	{
            		if(A[i] == A[j-1] && A[i] != A[i+1] && A[i+1]!=A[j-1])
            		{
            			i=i-1;
            			count=-1;
            			
            		}
            		flag=i;
            		count++;
                	k=j-1;
                	break;	
            	}  	
    	}
    	else
    	{
    		count++;
    		k--;

    	}	
        if(count>max)
           max=count;
       	//if(k<flag)break;
       	i++;  
        cout<<i<<","<<k<<","<<count<<endl;
       	
        
    }
    return max;
}