#include "cardManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

extern map<string, Card*> allclasses;

CardManager::~CardManager(){
    vector<Card*>::iterator iter;
    for (iter = myclasses.begin(); iter != myclasses.end(); ++iter) {
		delete (*iter);
	}
}

void CardManager::printAll(){  //1. view (목록 추가하기)
    for (int i=0; i<myclasses.size(); i++){
        cout << i+1 << " | " << myclasses[i]->toString() << endl;
    }
}

void CardManager::addCard(){ //2. ADD(과목추가하기)
    string code, grade;
	cout << ">> Enter class code > ";
	cin >> code;

    if(allclasses.count(code)>0){

    /*
    if (code == allclasses[code]){
        //입력받은 과목코드가 이미 존재한다는 경고 출력
    cout << "The Card of " << code << "already exists." << endl;
    }
*/


        cout << allclasses[code]->toStringShort() << endl;
	    cout << ">> Enter grade > ";
	    cin >> grade;

        //등급입력할 때 유효성검사하기 (그레이드 점수만 가능)
        Card* new_card = new Card(allclasses[code], grade);
        myclasses.push_back(new_card);
        count++;
        total_credit += new_card->getCredit();
    }
    else{
        cout << "No such class." << endl;
    }
}

void CardManager::editCard(){ // 3.Change(수정하기)
	int no;
    string new_grade;
	cout << ">> Enter a Card number > ";
	cin >> no;
    cout << myclasses[no-1]->toString() << endl;
    cout << ">> Enter new grade > ";
    cin >> new_grade;
    myclasses[no-1]->setGrade(new_grade);
    cout << "Grade changed." << endl;	
} //


void CardManager::sortByCode(){ //4.Sort (과목코드별로 정렬하기)
    sort(myclasses.begin(), myclasses.end(), Card::cmpCode);
}


void CardManager::findCards(string name){ //5.Search (과목코드로 찾기)
	int found = 0;
	cout << "Searching keyword: " << name << endl;
    for (int i=0; i<myclasses.size(); i++){
		if(myclasses[i]->getName().find(name) != string::npos){
			found++;
            cout << i+1 << " | " << myclasses[i]->toString() << endl;
		}
	}
	cout << count << " classes found.\n";
}

void CardManager::loadCards(string filename){ //6.Load (로드하기)
    string line, code, grade;
    int count=0;
	ifstream file(filename);
	while(!file.eof()){
        if(file.eof()) break;
		file >> code >> grade;
        Card* new_card = new Card(allclasses[code], grade);
        myclasses.push_back(new_card);
        count++;
        total_credit += new_card->getCredit();
	}
	file.close();
    cout << count << " classes are loaded.\n";
}

/*
//기능 추가하기 : 나의 수강 삭제하기
bool CardManager::removeCard(const std::string& courseCode) {
    int code;
    cout<< " enter the code: ";
    cin >> code ;

    for (auto it = code; it != code; ++it) {
        if (it->getCourseCode() == courseCode) {
            code.erase(it);
            return true;
        } 
    }
    return false;
}
*/