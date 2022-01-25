#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream source;
    source.open(filename.c_str());
    string textline;
    char check[] = "%[^:]: %d %d %d";
    char name[100];
    int score1,score2,score3;
    while(getline(source,textline)){
        sscanf(textline.c_str(),check,name,&score1,&score2,&score3);
        names.push_back(name);
        scores.push_back(score1+score2+score3);
        grades.push_back(score2grade(score1+score2+score3));
    }
    source.close();
}

void getCommand(string &command,string &key){
     string keyy;
     int temp;
     cout << "Please input your command: ";
     getline(cin,keyy);
     temp = keyy.find_first_of(" ");
     command = keyy.substr(0,temp);
     key=keyy.substr(temp+1);
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool check = false;
    for(unsigned int i=0;i<names.size();i++){
        if(key == toUpperStr(names[i])){
            check = true;
            cout << "---------------------------------" << endl;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------" << endl;
        }
    }
    if(check == false){
        cout << "---------------------------------" << endl;
        cout << "Cannot found." << endl;
        cout << "---------------------------------" << endl;
    }
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout<<"---------------------------------"<<endl;
    for(unsigned int i=0;i<grades.size();i++){
        if(key[0]==grades[i]){
            cout << names[i] << " " << "(" << scores[i] << ")" << endl;
        }
    }
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
