#include <bits/stdc++.h>

using namespace std;

vector<string>cross;
vector<string>wordList;

bool fillWord(int n){
    
    if(n>=wordList.size())
        return true;
    
    bool success;
    //i - crossword's row
    //j - crossword's column
    int a, b, letter; //a - row, b - column, letter - index of the current letter
    for(int i=0;i<10;i++){ // 10 rows of the crossword
        for(int j=0;j<10;j++){ //10 colmns of the crossword
            a=i, b=j;
            
            vector<string>tmp=cross; //in case of backtracking
            
            //checking horizontaly
            for(letter=0;letter<wordList[n].size() && b+letter<10;letter++){
                if(cross[a][b+letter]!='-' && cross[a][b+letter]!=wordList[n][letter])
                    break;
            }
            if(letter==wordList[n].size()){
                for(letter=0;letter<wordList[n].size();letter++){
                    cross[a][b+letter]=wordList[n][letter];
                }
                success=fillWord(n+1);
                if(success)
                    return success;
                else
                    cross=tmp; //when we did not placed the n+1-th word in the crossword 
                //then we need to backtrack to the last word we succesfully placed
            }
            
            //checking vertically
            for(letter=0;letter<wordList[n].size() && a+letter<10;letter++){
                if(cross[a+letter][b]!='-' && cross[a+letter][b]!=wordList[n][letter])
                    break;
            }
            if(letter==wordList[n].size()){
                for(letter=0;letter<wordList[n].size();letter++)
                    cross[a+letter][b]=wordList[n][letter];
                success=fillWord(n+1);
                if(success)
                    return success;
                else
                    cross=tmp;
            }
            
        }
    }
    return false;
}

vector<string> crosswordPuzzle(vector<string> crossword, string words) {
    //word splitting
    string s="";
    for(int i=0;i<words.size();i++){
        if(words[i]==';'){
            wordList.push_back(s);
            s="";
        }
        else {
            s+=words[i];
        }
    }
    wordList.push_back(s);
    
    cross=crossword;
    
    fillWord(0);
    
    return cross;
    
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

    for (int i = 0; i < 10; i++) {
        string crossword_item;
        getline(cin, crossword_item);

        crossword[i] = crossword_item;
    }

    string words;
    getline(cin, words);

    vector<string> result = crosswordPuzzle(crossword, words);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
