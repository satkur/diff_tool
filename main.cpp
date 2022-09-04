#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// エラーメッセージ定義
constexpr char* ARGC_ERR_MSG = "Usage: This program compares 2 file. Set command line args like this\n\n    diff_tool.exe [file1path] [file2path]\n";
constexpr char* FILE_OPEN_ERR_MSG = "Error: Failed to open file.";

/// @brief ファイル内容をstd::vectorに取り込む
/// @param ifs 
/// @param lines 
void readLines(std::ifstream& ifs, std::vector<std::string>& lines) {
    std::string s;

    while(std::getline(ifs, s)) {
        lines.push_back(s);
    }
}

/// @brief ファイル同士を並び順無視で比較する
/// @param ifs1 
/// @param ifs2 
void compareIgnoreOrder(std::ifstream& ifs1, std::ifstream& ifs2) {
    std::vector<std::string> list1;
    readLines(ifs1, list1);

    std::vector<std::string> list2;
    readLines(ifs2, list2);

    std::cout << "<- only:" << std::endl;
    for(auto e : list1) {
        if(std::binary_search(list2.begin(), list2.end(), e)) {
            std::cout << e << std::endl;
        }
    }

    std::cout << std::endl;

    std::cout << "-> only:" << std::endl;
    for(auto e : list1) {
        if(std::binary_search(list2.begin(), list2.end(), e)) {
            std::cout << e << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    //system("echo hello world ");

    if (argc < 2) {
        std::cerr << ARGC_ERR_MSG << std::endl;
        return -1;
    }

    char* path1 = argv[0];
    char* path2 = argv[1];

    std::ifstream ifsFile1(path1);
    if(ifsFile1.fail()) {
        std::cerr << FILE_OPEN_ERR_MSG << " " << path1 << std::endl;
        return -1;
    }
    
    std::ifstream ifsFile2(path2);
    if(ifsFile2.fail()) {
        std::cerr << FILE_OPEN_ERR_MSG << " " << path2 << std::endl;
        return -1;
    }
    
    compareIgnoreOrder(ifsFile1, ifsFile2);

    return 0;
}
