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

bool checkWord5(string s1,string s2, string s3){

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
	printarr(s1.length(),s2.length());

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
		return false;
	}
	cout<<newword<<endl;

	return true;

}


bool checkWord4(std::string s1, std::string s2, std::string s3){
	//if (s1.length() + s2.length() != s3.length()) {
	//	return false;
	//}

	for(int i=0;i<1001;i++){
		for(int j=0;j<1001;j++){
			dynam[i][j] = 0;
		}
	}

	// s1 is 1
	// s2 is 2
	dynam[0][0] = 1;

	for(int i=0;i<=s2.length();i++){
		for(int j=0;j<=s1.length();j++){
			if(!dynam[j][i]){
				continue;
			}

			if(s1[j] == s3[i+j] && !dynam[j+1][i]){
				dynam[j+1][i] = 1;
			}

			if(s2[i] == s3[i+j]  && !dynam[j][i+1]){
				dynam[j][i+1] = 2;
			}
		}
	}

	int s1len = s1.length(), s2len = s2.length();
	std::string newword = s3;

	while(s1len+s2len>0){
		if(!dynam[s1len][s2len]){
			return false;
		}

		int ind = s1len+s2len-1;
		if(dynam[s1len][s2len]==1){
			newword[ind] = std::toupper(s3[ind]);
		}

		if(s2len > 0 && dynam[s1len][s2len-1]){
			s2len--;
		}
		else if(s1len > 0 && dynam[s1len-1][s2len]){
			s1len--;
		}
	}

	std::cout<<newword<<std::endl;
	return true;
}

bool checkWord3(std::string s1, std::string s2, std::string * s) {
	if (s1.length() + s2.length() != s->length()) {
		return false;
	}

	// Reset M
	for (int n = 0; n < 1001; ++n) {
		for (int m = 0; m < 1001; ++m) {
			dynam[n][m] = 0;
		}
	}
	dynam[0][0] = 1;

	// Fill out M
	int s1Char = 1, s2Char = 2;
	for (int j = 0; (unsigned) j <= s2.length(); ++j) {
		for (int i = 0; (unsigned) i <= s1.length(); ++i) {
			if (!dynam[i][j]) {
				continue;
			}
			if (s1[i] == (*s)[i + j] && !dynam[i + 1][j]) {
				dynam[i + 1][j] = s1Char;
			}
			if (s2[j] == (*s)[i + j] && !dynam[i][j + 1]) {
				dynam[i][j + 1] = s2Char;
			}
		}
	}

	printarr(s2.length()+1,s1.length()+1);

	// Walk up matrix to see if s is a valid merge
	int i = s1.length(), j = s2.length(), index;
	while (i + j > 0) {
		// Check failed case
		if (!dynam[i][j]) {
			return false;
		}

		index = i + j - 1;
		if (dynam[i][j] == s1Char) {
			(*s)[index] -= 32; // Convert to uppercase if from s1
		}

		// Prioritize first string
		if (j > 0 && dynam[i][j - 1]) {
			--j;
		} else if (i > 0 && dynam[i - 1][j]) {
			--i;
		}
	}

	return true;
}

int main(){

	std::cout<<"Enter name of input file: ";
	std::string filein;
	std::cin>>filein;

	std::ifstream file;
	file.open(filein);
	if (!file.is_open()){
    	std::cout<<"ERROR"<<std::endl;
    } 

    //string line;
    std::string word1,word2,word3;
    while(getline(file,word1)){
    	getline(file,word2);
    	getline(file,word3);
    	if(checkWord5(word1,word2,word3)){
			//std::cout<<word3<<std::endl;
		}
		else{
			std::cout<<"** Not a Word **"<<std::endl;
		}
    	
    }


	return 0;
}















