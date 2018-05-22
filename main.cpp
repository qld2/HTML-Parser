#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string findAttribute(string line) {
    unsigned long separator = line.find("~");
    return line.substr(separator + 1);
}

string findTag(string line) {
    unsigned long separator = line.find("~");
    return line.substr(0, separator);
}

unsigned int findLineNumber(vector<string> lines, string input, int lineStart){
    unsigned long firstPeriod = input.find(".");
    unsigned long squiggly = input.find("~");
    string name, otherTags;

    if (firstPeriod == -1) {
        name = input.substr(1, squiggly);
    } else {
        name = input.substr(1, firstPeriod);
        otherTags = input.substr(firstPeriod + 1, squiggly);
    }

    for (int i = lineStart; i < lines.size() / 2; i++) {
        if (firstPeriod == -1) {
            if (lines[i].find(name) != -1) {
                return (unsigned) i;
            }
        } else {
            if (lines[i].find(name) != -1) {
                return findLineNumber(lines, otherTags, i);
            }
        }
    }
}

string findAttributeValue(string line, string attribute) {
    unsigned long startingIndex = line.find(attribute);
    unsigned long quoteCounter = 0;
    unsigned long start = 0, end = 0;

    for (unsigned long i = startingIndex; i < line.length(); i++) {

        if (line[i] == '\"') {
            quoteCounter++;
            if (quoteCounter == 1) {
                start = i + 1;
            }

            if (quoteCounter == 2) {
                end = i;
                break;
            }
        }
    }

    return line.substr(start, end);
}

int main() {
    unsigned long numOfLines, numOfQueries;
    cin >> numOfLines >> numOfQueries;

    vector<string> lines(numOfLines);
    vector<string> queries(numOfQueries);

    for (int i = 0; i < numOfLines; i++) {
        string in, temp;
        cin >> temp;

        while (temp[temp.length() - 1] != '>') {
            in += temp;
            in += " ";
            cin >> temp;
        }
        in += temp;
        lines[i] = in;
    }

    for (unsigned long i = 0; i < numOfQueries; i++) {
        cin >> queries[i];
    }


    for (int i = 0; i < numOfQueries; i++) {
        string attribute = findAttribute(queries[i]);
        string tag = findTag(queries[i]);

        cout << attribute << " " << tag << endl;

        int lineNum = findLineNumber(lines, tag, 0);

        //string attributeValue = findAttributeValue(queries[lineNum], attribute);
        cout << lineNum <<endl;
    }

    for (int i = 0; i < numOfQueries; i++) {
        cout << queries[i] <<endl;
    }


    return 0;
}
