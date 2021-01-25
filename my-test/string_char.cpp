#include <iostream>
#include <string.h>
using namespace std;

int main(){
    //
    string str1 = "123\0abc8";  //自面值常亮是char* 型，赋给string时就已经在'\0'处截断，只保留了“123”
    char* p1   = (char* )str1.data();   //string::data() 等同于string::c_str()
    cout<<"str1 is : "<<str1<<", and equal to "<<"p1 : "<<p1<<endl;
    cout<<"sizeof str1 : "<<str1.size()<<endl;
    int size1 = 0;   while(*p1){ size1++; p1++; }
    cout<<"sizeof p1 : "<<size1<<endl<<endl;

    string str2(8, 's');
    str2[3] = '\0';
    char* p2 = (char*)str2.c_str();
    cout<<"str2 is : "<<str2<<", and equal to "<<"p2 : "<<p2<<endl;   //此处字符指针只输出了'\0'之前的内容，是因为cout<< 遇到'\0' 就停止了。
    cout<<"sizeof str2 : "<<str2.size()<<endl;
    int size2 = 0;   while(*p2){ size2++; p2++; }
    cout<<"sizeof p2 : "<<size2<<endl<<endl;

    string str3(8, 's');
    str3[3] = '\0';
    char* p3 = (char*)str2.c_str();
    str3.assign(p3,8);
    cout<<"str3 is : "<<str3<<", and equal to "<<"p3 : "<<p3<<endl;
    cout<<"sizeof str3 : "<<str3.size()<<endl;
    int size3 = 0;   while(*p3){ size3++; p3++;}
    cout<<"sizeof p3 : "<<size3<<endl<<endl;

    string str4(8, 's');
    char* p4 = (char*) str4.data();
    int size4 = 0;  while(*p4){size4++; p4++; };
    cout<<"sizeof p4 : "<<size4<<endl<<endl;


}