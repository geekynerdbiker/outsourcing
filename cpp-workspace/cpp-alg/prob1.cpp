#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstring>
#include <cmath>
#include <utility>
using namespace std;

struct Point {
    double x, y;
};

double dist(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double minimalTriangulation(vector<Point> vertices, vector<vector<vector<int>>> &result) {
    if (vertices.size() < 3)
        return 0;
    
    vector<vector<double>> table(vertices.size() - 1, vector<double>(vertices.size() - 1, 0));
    
    for (int gap = 0; gap < vertices.size() - 1; gap++) {
        for (int i = 0, j = gap; j < vertices.size() - 1; i++, j++) {
            if (j < i+2)
                table[i][j] = 0.0;
            else {
                table[i][j] = INT_MAX;
                
                for (int k = i+1; k < j; k++) {
                    double val =  table[i][k] + table[k][j] + dist(vertices[i], vertices[j]);
                    
                    
                    table[i][j] = min(val, table[i][j]);
                    if (table[i][j] == val) {
                        result[i][j][0] = i;
                        result[i][j][1] = k;
                        result[i][j][2] = j;
                    }
                }
            }
        }
    }
    
    return table[0][vertices.size()-2];
}

void backTrack(vector<vector<vector<int>>> &table, vector<pair<int, int>> &result, int x, int y) {
    if (abs(table[x][y][0] - table[x][y][1]) >= 2) {
        result.push_back(make_pair(table[x][y][0], table[x][y][1]));
        backTrack(table, result, table[x][y][0], table[x][y][1]);
    }
    if (abs(table[x][y][1] - table[x][y][2]) >= 2) {
            result.push_back(make_pair(table[x][y][1], table[x][y][2]));
        backTrack(table, result, table[x][y][1], table[x][y][2]);
    }
}

int prob1(string inputFile, string outputFile) {
    vector<Point> vertices;
    
    string line;
    ifstream ifile(inputFile);
    ofstream ofile(outputFile);
    
    if (!ifile.is_open()) {
        cerr << "Could not open input file" << endl;
        return EXIT_FAILURE;
    }
    
    if (!ofile.is_open()) {
        cerr << "Could not open output file" << endl;
        return EXIT_FAILURE;
    }
    
    bool n = false;
    while (getline(ifile, line)) {
        if (!n) {
            n = true;
        } else {
            stringstream sstream(line);
            string token;
            
            Point p;
            
            getline(sstream, token, ' ');
            p.x = atof(token.c_str());
            
            getline(sstream, token, ' ');
            p.y = atof(token.c_str());
            
            vertices.push_back(p);
        }
    }
    
    vector<vector<vector<int>>> table(vertices.size() - 1, vector<vector<int>>(vertices.size() - 1, vector<int>(3, 0)));
    ofile << minimalTriangulation(vertices, table) << endl;
    
    int x = 0, y = vertices.size() - 2;
    ofile << x << " " << y << endl;
    vector<pair<int, int>> result;
    backTrack(table, result, x, y);
    
    sort(result.begin(), result.end());
    for (int i = 0; i < result.size(); i++)
        ofile << result[i].first << " " << result[i].second << endl;
    
    ifile.close();
    ofile.close();
    
    return 0;
}

int main(int argc, char** argv) {
    string line;
    ifstream ifile("PT_test_command.txt");
    
    if (!ifile.is_open()) {
        cerr << "Could not open input file" << endl;
        return EXIT_FAILURE;
    }
    
    int n = 0;
    while (getline(ifile, line)) {
        if (n == 0) {
            n = atoi(line.c_str());
        } else {
            stringstream sstream(line);
            string token;
            
            getline(sstream, token, ' ');
            string inputFile = token;
            
            getline(sstream, token, '\r');
            string outputFile = token;
            cout << outputFile << endl;
            prob1(inputFile, outputFile);
        }
    }
    ifile.close();
}
