#include <Windows.h>
#include <iostream>
using namespace std;

int main () {

  BOOL bFile;
  bFile = CopyFile(L"H:\\MERNSTACK2\\advancedOS\\.gitignore",L"H:\\MERNSTACK2\\advancedOS\\test.txt",TRUE);

  if(bFile == FALSE) {
    cout << "Failed to copy file Error No: "<<GetLastError()<< endl;
  }
  cout<<"Copied the file successfully"<<endl;
  system("PAUSE");
  return 0;
}