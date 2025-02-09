#include <iostream>
using namespace std;

void SpiralOrder(int n, int arr[][100]) {  
    int top = 0, bottom = n - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
       // 1 2 3 4
        for (int i = left; i <= right; i++){
            cout << arr[top][i] << " ";}
        top++;

        //8 12 
        for (int i = top; i <= bottom; i++){
            cout << arr[i][right] << " ";}
        right--;

        // 13 14 15 16
        if (top <= bottom) {  
            for (int i = right; i >= left; i--){
                cout << arr[bottom][i] << " ";}
            bottom--;
        }

        
        if (left <= right) {
            for (int i = bottom; i >= top; i--){
                 cout << arr[i][left] << " ";
            }
               
            left++;
        }
    }
}

int main() {
    int size;
    cout << "Enter size: ";
    cin >> size;

    int arr[100][100]; 
    int num = 1;
    for (int i = 0; i < size; i++) { 
        for (int j = 0; j < size; j++) {  
            arr[i][j] = num++; 
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Spiral Order: ";
    SpiralOrder(size, arr);

    return 0;
}