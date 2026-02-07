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
            int reportNum = scammer_data[i].reportN;
            string riskLevel;
            if(reportNum > 9){
                risk = 100;
                riskLevel = "High";
            }else if(reportNum >= 5){
                risk = reportNum*20;
                riskLevel = "Medium";
            }else{
                risk = reportNum*20;
                riskLevel = "Low";
            }

            cout << "===============================\n";
            cout << "   Phone Number : " << scammer_data[i].phoneNum << endl;
            cout << "   Report Number : " << reportNum << endl;
            cout << "   Risk Level : " << risk << "% (" << riskLevel << ")" << endl;
            if(risk == 100){
                cout << " ! WARNING : Do not answer !\n";
            }
            cout << "===============================\n";

            NewReport(&scammer_data[i]); //เพิ่มจำนวนการแจ้งทันทีที่มีการค้นเจอข้อมูล

            ofstream outFile("scammer_data.txt");
            for(int i = 0; i < scammer_data.size(); i++){
                outFile << scammer_data[i].phoneNum << "|" << scammer_data[i].reportN << endl;
            }
            outFile.close();
            
            found = true;
            break;
        }
    }
    if(!found){
        cout << "===============================\n";
        cout << "         can not found." << endl;
        cout << "===============================\n";
        
        char ans;
        cout << "Do you want to report this number? (y/n) : "; //จะแจ้งเพิ่มไหม
        cin >> ans;

        if(ans == 'y' || ans == 'Y'){
            //สร้างข้อมูลใหม่ เบอร์ที่แจ้งกับเริ่มต้นแจ้งครั้งที่ 1
            scammer_phone newPhone;
            newPhone.phoneNum = phoneForSearch;
            newPhone.reportN = 1;
            scammer_data.push_back(newPhone);

            ofstream outFile;
            outFile.open("scammer_data.txt", ios::app); //ios::app เขียนข้อมูลต่อท้าย ข้อมูลเก่าไม่โดนลบ
            outFile <<phoneForSearch << "|1\n" << endl;
            outFile.close();

            cout << " << Thank you for New Report >> " << endl;
        }else{
            cout << " << Thank you >> ";
        }
    }
}