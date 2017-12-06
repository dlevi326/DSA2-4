#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iterator>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include <string.h>



using namespace std;

int dynam[1001][1001];

void printarr(int size1, int size2){

	for(int i=0;i<=size1;i++){
		for(int j=0;j<=size2;j++){
			std::cout<<dynam[i][j]<<" ";
		}
		std::cout<<std::endl;
	}

}

string checkWord(string s1,string s2, string s3){

	dynam[0][0]=1;
	for(int i=0;i<=s1.length();i++){
		for(int j=0;j<=s2.length();j++){
			if(j==0&&i==0){
				continue;
			}
			if(dynam[i][j-1]||dynam[i-1][j]){

				if(s2[j-1]==s3[i+j-1]){
					dynam[i][j] = 2;
				}
				else if(s1[i-1]==s3[i+j-1]){
					dynam[i][j] = 1;
				}
				else{
					dynam[i][j] = 0;
				}
			}

			else{
				dynam[i][j] = 0;
			}
		}
	}
	//printarr(s1.length(),s2.length());

	string newword = s3;

	int i = s1.length();
	int j = s2.length();

	if(dynam[s1.length()][s2.length()]){
		while(i>0||j>0){
			if(dynam[i][j]!=0){
				//cout<<newword<<endl;
				if(s2[j-1]==s1[i-1]){

					if(dynam[i][j-1]){
						j--;
					}
					else if(dynam[i-1][j]){
						newword[i+j-1] = toupper(s3[i+j-1]);
						i--;
					}

				}
				else if(s2[j-1]==s3[j+i-1]&&j!=0){
					j--;
				}
				else if(s1[i-1]==s3[j+i-1]){
					newword[i+j-1] = toupper(s3[i+j-1]);
					i--;
				}
			}
			else{
				//cout<<"help please"<<endl;
			}
		}
	}
	else{
		return "*** NOT A MERGE ***\n";
	}
	

	return newword+"\n";

}
int main(){

	cout<<"Enter name of input file: ";
	string filein;
	cin>>filein;
	ifstream file;
    file.open(filein);
    if (!file.is_open()){
    	cout<<"ERROR"<<endl;
    }
	

    string fileout;
    cout<<"Enter output file: ";
    cin>>fileout;
    ofstream file2;
    file2.open(fileout);
    if (!file2.is_open()){
    	cout<<"ERROR"<<endl;
    }


    //string line;
    std::string word1,word2,word3;
    while(getline(file,word1)){
    	getline(file,word2);
    	getline(file,word3);
    	file2<<checkWord(word1,word2,word3);
    	
    }


	return 0;
}















