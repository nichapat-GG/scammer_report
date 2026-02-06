#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct scammer_phone{
    string phoneNum; // phoneNum = 1 เบอร์
    int reportN; // reportN = จำนวนแจ้ง
};

int main(){
    vector<scammer_phone> scammer_data;
    ifstream source;
    source.open("scammer_data.txt");

    string phone;
    //อ่านเป็น phoneNum|reportN
    while(getline(source,phone)){
        scammer_phone sp;  //sp.phoneNum & sp.reportN
        sp.phoneNum = "";
        sp.reportN = 0;
        bool afterBar = false;  //ยังไม่เจอขีด |
       
        for(int i = 0; i < phone.length(); i++){
            if(phone[i] == '|'){
                afterBar = true;
                continue;
            }
            if(!afterBar){
                sp.phoneNum += phone[i]; //ก่อน | คือเบอร์
            }else{
                sp.reportN = sp.reportN * 10 + (phone[i] - '0'); //สูตรแปลง char เป็น int
            }
        }
        scammer_data.push_back(sp);
    }

    for(int i = 0; i < scammer_data.size(); i++){
        cout << "Phone Number : " << scammer_data[i].phoneNum;
        cout << " | Reports : " << scammer_data[i].reportN << endl;
    }

    return 0;
}