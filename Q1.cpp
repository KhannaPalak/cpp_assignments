#include<iostream>
#include<vector>
#include<string>
using namespace std;
// no. manipulation and prime no.
int next_prime(int x) 
{
    x++;
    while (true) 
    {
        int i=0;
        for (i=2; i<= x; i++) 
        {
            if (x % i == 0) 
            {
                break;
            }
        }
        if (i*i> x) 
        {
            return x;
        }
        x++;
    }
}
int main()
{
    cout<<"enter a positive natural integer ";
    int x;
    cin>>x;
    
    if (x < 2) 
    {
        cout <<  " is not a prime number and has no factor" << endl;
    }

    int factor=0,i;
    for(i=2;i<=x;i++)
    {
       if(x%i==0){
        factor+=1;
        cout<<i<<" "<<" is the factor of "<<x<<endl;
       }
    }

    if(factor==1)
    {
        cout<<"it is a prime no\n";
        int next_prime_no=next_prime(x);
        cout << "The next prime number is: " << next_prime_no << endl;
    } 
    
    if(factor>1)
    {
        cout<<"it is not a prime no";
    }
     



    return 0;
        
}
