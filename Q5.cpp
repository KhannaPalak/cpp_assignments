#include<iostream>
#include<vector>
#include<string>
using namespace std;
      
int main(){
int arr[3][3]={1,2,3,4,5,6,7,8,9};
//orignal
for(int i=0;i<=2;i++){
    for(int j=0;j<=2;j++){
        cout<<arr[i][j]<<" ";
    }
    cout<<endl;    
}
cout<<endl;
//transpose
for(int i=0;i<=2;i++){
    for(int j=i+1;j<=2;j++){
        swap(arr[i][j],arr[j][i]);
          }
    cout<<endl;
}
//rotate  90
 for (int i = 0; i < 3; i++) {
        swap(arr[i][0], arr[i][2]);
    }

    for(int i=0;i<=2;i++){
    for(int j=0;j<=2;j++){
        cout<<arr[i][j]<<" ";
    }
    cout<<endl;
    
}
cout<<endl;
}