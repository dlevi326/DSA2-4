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

	if(s1.length()+s2.length()!=s3.length()){
		return "*** NOT A MERGE ***\n"; 
	}

	// Fill array
	for (int a = 0; a < 1001; a++) {
		for (int b = 0; b < 1001; b++) {
			dynam[a][b] = 0;
		}
	}

	dynam[0][0] = 1;

	for(int i=0;i<=s2.length();i++){
		for(int j=0;j<=s1.length();j++){
			if(!dynam[i][j]){
				continue;
			}

			if(s1[j] == s3[i+j] && !dynam[i][j+1]){
				dynam[i][j+1] = 1;
			}
			if(s2[i] == s3[i+j] && !dynam[i+1][j]){
				dynam[i+1][j] = 2;
			}
		}
	}



	//printarr(s2.length(),s1.length());
	//cout<<endl;

	string word = s3;
	int j=s1.length(),i=s2.length();

	// Trace back up array
	while(i+j>0){
		if(!dynam[i][j]){
			return "*** NOT A MERGE ***\n";
		}
		if(dynam[i][j]==1){
			word[i+j-1] = toupper(s3[i+j-1]);
			j--;
		}
		if(dynam[i][j]==2){
			i--;
		}
	}

	return word+ '\n';

	
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















