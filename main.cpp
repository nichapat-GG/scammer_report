#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct scammer_phone{
    string phoneNum; // phoneNum = 1 เบอร์
    int reportN; // reportN = จำนวนแจ้ง
};

//func สำหรับเพิ่มข้อมูลใน struct !!กันลืม
void NewReport(scammer_phone *sp){
    (*sp).reportN++; //เข้าถึงสมาชิก struct ด้วย pointer
}

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
                sp.phoneNum += phone[i];
            }else{
                sp.reportN = sp.reportN * 10 + (phone[i] - '0');
            }
        }
        scammer_data.push_back(sp);
    }
    source.close();

    string phoneForSearch;
    cout << "Enter your Phone Number (do not include '-') : ";
    cin >> phoneForSearch;

    bool found = false;

    for(int i = 0; i < scammer_data.size(); i++){
        if(phoneForSearch == scammer_data[i].phoneNum){
            int risk;
            string riskLevel;
            if(scammer_data[i].reportN > 5){
                risk = 100;
                riskLevel = "High";
            }else if(scammer_data[i].reportN >= 3){
                risk = scammer_data[i].reportN*20;
                riskLevel = "Medium";
            }else{
                risk = scammer_data[i].reportN*20;
                riskLevel = "Low";
            }

            cout << "===============================\n";
            cout << "   Phone Number : " << scammer_data[i].phoneNum << endl;
            cout << "   Report Number : " << scammer_data[i].reportN << endl;
            cout << "   Risk Level : " << risk << "% (" << riskLevel << ")" << endl;
            if(risk == 100){
                cout << " ! WARNING : Do not answer !\n";
            }
            cout << "===============================\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout << "can not found." << endl;
        
        char ans;
        cout << "Do you want to report this number? (y/n) : ";
        cin >> ans;

        if(ans == 'y' || ans == 'Y'){
            
        }
    }
}