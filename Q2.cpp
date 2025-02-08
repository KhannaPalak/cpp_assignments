#include<iostream>
#include<vector>
#include<string>
using namespace std;

//ARRAY OPERATIONS:
//FUNCN FOR SECOND LARGEST NO.
void second_largest(int arr[],int size)
{
    int max=INT_MIN; 
    int second_max=INT_MIN;
    for(int i=0;i<size;i++)
    {
        if(arr[i]>max)
        {
            second_max=max;
            max=arr[i];
        }
        else if (arr[i] > second_max && arr[i] != max) 
        {
            second_max = arr[i];
        }
    }
   cout<<second_max;
}
        
//FUNCN FOR SECPND SMALLEST NO.
void second_smallest(int arr[],int size){
    int min=INT_MAX;
    int second_min=INT_MAX;
    for(int i=0;i<size;i++)
    {
        if(arr[i]<min)
        {
            second_min=min;
            min=arr[i];
        }
        else if (arr[i] < second_min && arr[i] != min) 
        {
            second_min = arr[i];
        }
    }
    
   cout<<second_min;
}
 
int main(){
    int size;
    cout<<"enetr size ";
    cin>>size;
    int arr[size];
    cout<<"accept the array ";
    for(int i=0;i<size;i++){
        cin>>arr[i];
    }
    cout<<"reverse of the array: ";
     for(int i=(size-1);i>=0;i--){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"second largest element in array= "; 
    second_largest(arr,size);
    cout<<endl;
    cout<<"second smallest element in array= "; 
    second_smallest(arr,size);

    return 0;
        
}