#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
      
int main(){
    string word;
    string reverse_word;
    cout<<"enter string: ";
    cin>>word;
    reverse_word=word;
    reverse(reverse_word.begin(),reverse_word.end());
    if(word==reverse_word) cout<<"palindrome";
    else cout<<"not palindrome";

}