#include <iostream>

using namespace std;

void preKMP(string pattern, int *longestPrefixSuffix, int M) {
    int lenght = 0, i = 1;
    longestPrefixSuffix[0] = 0;
    while (i < M) {
        if (pattern[i] == pattern[lenght]) {
            lenght++;
            longestPrefixSuffix[i] = lenght;
            i++;
        }
        else {
            if (lenght == 0) {
                longestPrefixSuffix[i] = 0;
                i++;
            }
            else
                lenght = longestPrefixSuffix[lenght - 1];
        }
    }
}


bool KMP(string pattern, string text) {
    int M = pattern.length();
    int N = text.length();
    int *longestPrefixSuffix = new int[M];
    int i = 0, j = 0;

    preKMP(pattern, longestPrefixSuffix, M);

    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M)
            return true;

        else if (i < N && pattern[j] != text[i]) {
            if (j == 0)
                i = i + 1;
            else
                j = longestPrefixSuffix[j - 1];
        }
    }
    return false;
}

void transformToPattern(string &text){
    for(int i = 0; i < text.length(); i++) {
        if (text[i] >= 97 && text[i] <= 122)
            text[i] = 'a';
        else if(text[i] >= 65 && text[i] <= 90)
            text[i] = 'A';
        else if(text[i] >= 48 && text[i] <= 57)
            text[i] = '0';
        else if(text[i] == 33 || text[i] == 44
                || text[i] ==  45 || text[i] == 46
                || text[i] == 58 || text[i] == 59
                || text[i] == 63)
            text[i] = '.';
        else
            continue;
    }
}

int main() {
    string text, pattern;

    getline(cin, pattern);
    getline(cin, text);

    transformToPattern(text);

    if(KMP(pattern, text))
        cout << "T" << endl;
    else
        cout << "N" << endl;
    return 0;
}
