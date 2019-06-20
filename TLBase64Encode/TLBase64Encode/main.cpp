//
//  main.cpp
//  TLBase64Encode
//
//  Created by 突突兔 on 6/17/19.
//  Copyright © 2019 突突兔. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "HihaBase64.h"

#include <vector>
#include <string>

using namespace std;


int main(int argc, const char * argv[]) {
    
//    if (argc !=2) return -1;
//
//    FILE *fin = fopen(argv[1], "rt");
//    if (!fin) return -2;
//
//    vector<string> results;
//    char buf[1024 * 64+1];
//
//    while (fgets(buf, sizeof(buf)-1, fin)) {
//        if (strstr(buf, "@")) {
//
//        } else {
//            results.emplace_back(buf);
//        }
//    }
//
//    fclose(fin);
//
//    FILE *fout = fopen(argv[1], "wt");
//    fprintf(fout, "%s\n", R"(#import "NSString+HihaBase64.h")");
//    for (auto &it : results) {
//        fprintf(fout, "%s\n",  it.c_str());
//    }
//    fclose(fout);
//
    
    
    if (argc != 2) {
        throw logic_error("Just follow the path of the file");
    }
    string filePath = argv[1];
    ifstream in(filePath);
    if (!in) {
        throw invalid_argument("Invalid File");
    }

    vector<string> results;
    string s;
    
    while (getline(in, s)) {
        auto atLocation = s.find("@");
        if (atLocation == string::npos) {
            results.push_back(s);
            continue;
        }
        auto semicolonLocation = s.find(";");
        auto plainString = s.substr(0, atLocation);
        string subString = s.substr(atLocation + 2, semicolonLocation - atLocation - 3);

        string encodeString = HihaBase64_encode(subString.c_str());
        string result = plainString;
        std::ostringstream tail;
        tail << "[NSString From:" << "\"" << encodeString << "\"" << "]"
        << ";"
        << " // "
        << subString;
        result += tail.str();
        cout << result << endl;
        results.push_back(result);
    }
    in.close();
    ofstream out(filePath);
    if (!out) {
        throw invalid_argument("Invalid File");
    }
    out << R"(#import "NSString+HihaBase64.h")" << "\n";
    for (const auto &str : results) {
        out << str << "\n";
    }
    out.close();
    
    return 0;
}
