#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include <iomanip>
#include <regex>
#include "Expression.h"


struct csv_line     
{
    //int num;
    std::string A;
    std::string B;
    std::string Cell;

    std::string* getCols() {
        std::string* Cols = new std::string[3];
        Cols[0] = A; Cols[1] = B; Cols[2] = Cell;
        return Cols;
    }

    void setA(std::string A) {
        this->A = A;
    }

    void setB(std::string B) {
        this->B = B;
    }

    void setCell(std::string Cell) {
        this->Cell = Cell;
    }

    std::string getByCell(char* &cell) {
        if (strcmp(cell, "A") == 0)
            return A;
        else if (strcmp(cell, "B") == 0)
            return B;
        else if (strcmp(cell, "Cell") == 0)
            return Cell;
        else return NULL;
    }
};

void getLetterAndNum(const char* ref, char*& str, char*& dig) {
    str = strdup(ref);

    int i, j;
    for (i = 0; str[i] != '\0'; ++i) {
        while (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '\0')) {
            for (j = i; str[j] != '\0'; ++j) {
                str[j] = str[j + 1];
            }
        }
    }

    dig = strdup(ref);
    for (i = 0; dig[i] != '\0'; ++i) {
        while (!((dig[i] >= '0' && dig[i] <= '9') || dig[i] == '\0')) {
            for (j = i; dig[j] != '\0'; ++j) {
                dig[j] = dig[j + 1];
            }
        }
    }
}

std::vector<std::string>split(const std::string& s, std::string rgx_str = "\\s+") {


    std::vector<std::string> elems;

    std::regex rgx(rgx_str);

    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;

    while (iter != end) {
        elems.push_back(*iter);
        ++iter;
    }

    return elems;

}

bool isDigit(const std::string& s) {
    return s.find_first_not_of("0123456789") == std::string::npos;
}