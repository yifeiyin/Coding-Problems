#include <iostream>
#include <cmath>

using namespace std;

typedef long long T;

void fatalError(string msg) {
    cout << "ERROR!! " << msg << endl;
    exit(1);
}

string GetSuffixForCurrentGroup(T magInThrees) {
    switch (magInThrees) {
        case 0: return "";            break;      
        case 1: return "thousand";    break;        
        case 2: return "million";     break;        
        case 3: return "billion";     break;        
        case 4: return "trillion";    break;        
        case 5: return "quadrillion"; break;
    }
    fatalError("GetSuffixForCurrentGroup" + to_string(magInThrees));
    return "";
}

string GetTextForNumberLessThanTen(T number) {
    switch (number) {
        case 0: return "";          break;
        case 1: return "one";       break;   
        case 2: return "two";       break;   
        case 3: return "three";     break;   
        case 4: return "four";      break;   
        case 5: return "five";      break;   
        case 6: return "six";       break;   
        case 7: return "seven";     break;   
        case 8: return "eight";     break;   
        case 9: return "nine";      break;   
    }   
    fatalError("GetTextForNumberLessThanTen");
    return "";
}

string GetTextForOnes(T number) {
    return GetTextForNumberLessThanTen(number);
}

string GetTextForTens(T number) {
    switch (number) {
        case 2: return "twenty";        break;
        case 3: return "thirty";        break;
        case 4: return "forty";         break;
        case 5: return "fifty";         break;
        case 6: return "sixty";         break;
        case 7: return "seventy";       break;
        case 8: return "eighty";        break;
        case 9: return "ninety";        break;
    }
    fatalError("GetTextForTens");
    return "";
}

string GetTextForNumbersForAGroup(T number) {
    string result = "";

    T theHundredsDigit = number / 100;
    T theTensDigit     = (number - 100 * theHundredsDigit) / 10;
    T theOnesDigit     = (number - 100 * theHundredsDigit - 10 * theTensDigit) / 1;
    
    if (theHundredsDigit > 0) {
        result += GetTextForNumberLessThanTen(theHundredsDigit);
        result += "hundred";
    }

    if (theTensDigit >= 2) {
        result += GetTextForTens(theTensDigit) + GetTextForOnes(theOnesDigit);
    
    } else if (theTensDigit == 0) {
        result += GetTextForOnes(theOnesDigit);
    } else {
        switch (theTensDigit * 10 + theOnesDigit) {
            case 10: result += "ten";       break;
            case 11: result += "eleven";    break;
            case 12: result += "twelve";    break;
            case 13: result += "thirteen";  break;
            case 14: result += "fourteen";  break;
            case 15: result += "fifteen";   break;
            case 16: result += "sixteen";   break;
            case 17: result += "seventeen"; break;
            case 18: result += "eighteen";  break;
            case 19: result += "nineteen";  break;
            default: fatalError("number < 10 or number > 19: " + to_string(theTensDigit * 10 + theOnesDigit));
        }
    }
    return result;
}

string NumberOfLetters(T number) {
    T magnitude = 0;
    
    while (number > pow(10, magnitude)) {
        magnitude++;
    }

    T magnitudeInTheGroupOfThree = magnitude % 3;
    T groupOfThreesCount = (magnitude - magnitudeInTheGroupOfThree) / 3 + 1;

    string result = "";
    
    for (T groupOfThree = 0; groupOfThree < groupOfThreesCount; groupOfThree++) {
        
        T numberGroup = number % T(pow(10, 3 * (groupOfThree+1))) / pow(10, 3 * groupOfThree);
        
        if (numberGroup == 0) {
            continue;
        }
        string resultForThisGroup = GetTextForNumbersForAGroup(numberGroup);

        // cout << "        CurrentGroup: " << numberGroup << endl;

        string suffixForCurrentGroup = GetSuffixForCurrentGroup(groupOfThree);
        resultForThisGroup += suffixForCurrentGroup;
        result = resultForThisGroup + result;
    }

    return result;
}

void letterNumberMain(T initialNumber) {
    string newNumberString = NumberOfLetters(initialNumber);
    T newNumber = newNumberString.length();

    while(newNumber != 4) {
        // cout << newNumberString << " \t\t";
        cout << newNumber << endl;
        
        newNumberString = NumberOfLetters(newNumber);
        newNumber = newNumberString.length();
    }
    cout << 4 << endl;
    cout << "----" << endl;
}

int main() {
    T input = 0;
    cin >> input;

    while (input) {
        letterNumberMain(input);

        cin.clear();
        cin >> input;
    }
    cout << "Bye!" << endl;
    return 0;
}