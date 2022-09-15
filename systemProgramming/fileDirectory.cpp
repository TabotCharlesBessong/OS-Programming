
#include <Windows.h>
#include <iostream>
using namespace std;

int main () {
  // cout<<"Hello world"<<endl;
  BOOL bDir ;
  bDir = CreateDirectory(L"H:\\MERNSTACK2\\OS-Programming\\Dir1", NULL);
  if(bDir == FALSE) {
    cout<<"Create directory failed and error No: "<<GetLastError()<<endl;
  }
  cout<<"Create directory successful: "<<endl;

  bDir = RemoveDirectory(L"H:\\MERNSTACK2\\OS-Programming\\Dir1");

  if(bDir == FALSE) {
    cout<<"Delete directory failed and error No: "<<GetLastError()<<endl;
  }
  cout<<"Delete directory successful: "<<endl;

  system("PAUSE");
  return 0; 
}
