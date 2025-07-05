//
// Created by 15089 on 25-7-5.
// 二分查找法
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

bool hasFound(vector<int> &array, int target) {
  int start = 0, end = array.size()-1;
  while (start <= end) {
    int mid = start + (end-start)/2;
    if(array[mid] == target) {
      return true;
    }else if(array[mid] > target) {
      end = mid -1;
    }else if(array[mid] < target) {
      start = mid + 1;
    }
  }
  return false;
}

bool findNumberIn2DArray(vector<vector<int>> &matrix, int target) {
  if((matrix.size() == 0)||(matrix[0].size() == 0)) return false;
  for(int i = 0;i < matrix.size(); i++){
    if(hasFound(matrix[i], target)) return true;
  }
  return false;
}

// 解析输入字符串为二维数组
vector<vector<int>> parseMatrix(const string &input) {
    vector<vector<int>> matrix;
    size_t l = input.find('['), r = input.rfind(']');
    string arr = input.substr(l + 1, r - l - 1);
    stringstream ss(arr);
    string row;
    while (getline(ss, row, ']')) {
        size_t pos = row.find('[');
        if (pos != string::npos) row = row.substr(pos + 1);
        else if (row.empty() || row[0] == ',') continue;
        vector<int> nums;
        stringstream rs(row);
        string num;
        while (getline(rs, num, ',')) {
            if (!num.empty()) nums.push_back(stoi(num));
        }
        if (!nums.empty()) matrix.push_back(nums);
    }
    return matrix;
}

int main() {
    string line;
    getline(cin, line);
    size_t comma = line.find(',');
    int target = stoi(line.substr(0, comma));
    string matrixStr = line.substr(comma + 1);
    vector<vector<int>> matrix = parseMatrix(matrixStr);

    bool found = findNumberIn2DArray(matrix, target);
    cout << (found ? "true" : "false") << endl;
    return 0;
}
