#include "StringApp.h"

int alpabets[26] = { 0 };

StringApp::StringApp() {
    cout << "Input : ";
	getline(cin, input);
    
    cout << "Gap size : ";
    cin >> gap;
}

void StringApp::printAlpabets() {
	string alph = input;
	for (int i = 0; i < input.length(); i++)
		alph[i] = tolower(input[i]);

	for (int i = 0; i < input.length(); i++)
		if (alph[i] >= 'a' && alph[i] <= 'z')
			alpabets[int(alph[i]) - 97]++;

	for (int i = 0; i < 26; i++)
		if (alpabets[i] != 0)
            cout << "[" << char(i + 97) << ":" << alpabets[i] << "] ";
    
    cout << endl;
}

void StringApp::setFormat() {
	int crtPos = 0;

    corr = input;
	for (int i = 0; i < input.length(); i++)
		if (input[i] != ' ') {
            corr[i] = toupper(input[i]);
			crtPos = i + 1;
			break;
		}
    
	for (int i = crtPos; i < input.length(); i++)
        corr[i] = tolower(input[i]);
}

void StringApp::printSentence() {
    cout << "Corrected sentence ==> " << corr << endl;
    
    string encoded = input;
    for (int i = 0; i < input.length(); i++)
        if (encoded[i] >= 'A' && encoded[i] <= 'Z') {
            if (input[i] + gap < 'A')
                encoded[i] = input[i] + gap + 26;
            else if (input[i] + gap > 'Z')
                encoded[i] = input[i] + gap - 26;
            else encoded[i] = input[i] + gap;
        } else if (encoded[i] >= 'a' && encoded[i] <= 'z') {
            if (input[i] + gap < 'a')
                encoded[i] = input[i] + gap + 26;
            else if (input[i] + gap > 'z')
                encoded[i] = input[i] + gap - 26;
            else encoded[i] = input[i] + gap;
        } else if (encoded[i] >= '0' && encoded[i] <= '9') {
            if (input[i] + (gap % 10) < '0')
                encoded[i] = input[i] + (gap % 10) + 10;
            else if (input[i] + (gap % 10) > '9')
                encoded[i] = input[i] + (gap % 10) - 10;
            else encoded[i] = input[i] + (gap % 10);
        }

    cout << "  Encoded sentence ==> " << encoded << endl;
}

int main() {
    StringApp s;

    s.setFormat();
    s.printAlpabets();
    s.printSentence();
    
    return 0;
}
