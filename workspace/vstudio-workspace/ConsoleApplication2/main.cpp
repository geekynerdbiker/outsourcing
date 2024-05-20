#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
// #include <cmath>
#include <math.h>
#include <time.h>

//#pragma comment(lib, "libmx.lib")
//#pragma comment(lib, "libmat.lib")
//#pragma comment(lib, "libeng.lib")

#define PI 3.141592

using namespace std;

bool compare(vector<double>& v1, vector<double>& v2) {
    if (v1[5] == v2[5])
        return v1[3] > v2[3];
    else return v1[5] < v2[5];
}

bool compare2(vector<double>& v1, vector<double>& v2) {
    if (v1[0] == v2[0]) 
        if (v1[1] == v2[1])
            if (v1[2] == v2[2])
                return v1[3] < v2[3];
            else
                return v1[2] < v2[2];
        else
            return v1[1] < v2[1];
    return v1[0] < v2[0];
}

bool compare3(vector<double>& v1, vector<double>& v2) {
    if (v1[3] == v2[3])
        return v1[0] < v2[0];
    else return v1[3] < v2[3];
}

vector<double> cross(vector<double> v1, vector<double> v2) {
    return { v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0] };
}

vector<double> add(vector<double> v1, vector<double> v2) {
    return { v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2] };
}

vector<double> sub(vector<double> v1, vector<double> v2) {
    return { v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2] };
}

vector<double> mul(vector<double> l, double x) {
    return { l[0] * x,l[1] * x, l[2] * x };
}

vector<double> div(vector<double> l, double x) {
    return { l[0] / x,l[1] / x, l[2] / x };
}

double magnitude(vector<double> v) {
    return sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));
}

vector<vector<double>> closestApproach(vector<double> l1, vector<double> l2) {
    vector<double> v1 = { sub({l1[0],l1[1],l1[2]}, { l1[3],l1[4],l1[5] }) };
    vector<double> v2 = { sub({l2[0],l2[1],l2[2]}, { l2[3],l2[4],l2[5] }) };

    vector<double> n = cross(v1, v2);
    double dot = inner_product(n.begin(), n.end(), n.begin(), 0);

    if (dot < 1) {
        return { {0} };
    }
    else {
        vector<double> point1 = { l1[0], l1[1], l1[2] };
        vector<double> point2 = { l2[0], l2[1], l2[2] };

        vector<double> c1 = cross(v1, n);
        vector<double> c2 = cross(v2, n);
        vector<double> min = sub(point1, point2);

        double tt = inner_product(c2.begin(), c2.end(), min.begin(), 0) / dot;
        double ttt = inner_product(c1.begin(), c1.end(), min.begin(), 0) / dot;

        vector<double> p1 = add(point1, mul(v1, tt));
        vector<double> p2 = add(point2, mul(v2, ttt));

        return { p1, p2 };
    }

}

double angleCalculation(vector<double> p1, vector<double> p2, vector<double> midpoint, vector<double> l1, vector<double> l2) {
    vector<double> p1_move = sub(p1, midpoint);
    vector<double> p2_move = sub(p2, midpoint);

    vector<double> point1 = add({ l1[0],l1[1],l1[2] }, p1_move);
    vector<double> point2 = add({ l2[0],l2[1],l2[2] }, p2_move);

    vector<double> v1 = { sub(point1, midpoint) };
    vector<double> v2 = { sub(point2, midpoint) };

    double dot = inner_product(v1.begin(), v1.end(), v2.begin(), 0);

    double mag1 = magnitude(v1);
    double mag2 = magnitude(v2);

    double cos = dot / (mag1 * mag2);
    double rad = acos(cos);

    double angle = 180 - ((rad * 180) / PI);

    if (angle > 90)
        angle = 180 - angle;
    
    return angle;
}

int main(int argc, char** argv) {

    //string filePath = "";
    string output = "";

    //if (argc > 1) {
    //    for (int i = 0; i < argc; i++) {
    //        if (string(argv[i]) == "-i") filePath = string(argv[i + 1]);
    //        if (string(argv[i]) == "-o") output = string(argv[i + 1]);
    //    }
    //}

    cout << endl << "!!!!! Start data sorting !!!!!" << endl << endl;

    clock_t start, finish;
    double duration;

    start = clock();

     string filePath = "input data.txt"; // 경로 수정 필요

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }
    vector<vector<double>> data;
    vector<double> col_x, col_y, col_z, col_e, col_m, col_l, col_id, col_type, col_t;

    double x, y, z, e, m, l, id, type, t;
    while (true) {
        file >> x >> y >> z >> e >> m >> l >> id >> type >> t;

        if (x == 0 || y == 0 || z == 0 || e == 0 || m == 0 || l == 0 || id == 0 || type == 0 || t == 0)
            continue;
        if (id == 1)
            continue;
        if (type == 13) {
            col_x.push_back(x);
            col_y.push_back(y);
            col_z.push_back(z);
            col_e.push_back(e);
            col_m.push_back(m);
            col_l.push_back(l);
            col_id.push_back(id);
            col_type.push_back(type);
            col_t.push_back(t);
        }
        if (file.eof())
            break;
    }

    file.close();

    data.push_back(col_x);
    data.push_back(col_y);
    data.push_back(col_z);
    data.push_back(col_e);
    data.push_back(col_m);
    data.push_back(col_l);
    data.push_back(col_id);
    data.push_back(col_type);
    data.push_back(col_t);

    int k = 0, index = 0;
    vector<vector<vector<double>>> data2;
    vector<double> uniques;

    for (int i = 0; i < col_id.size(); i++)
        uniques.push_back(col_id[i]);
    sort(uniques.begin(), uniques.end());
    uniques.erase(unique(uniques.begin(), uniques.end()),uniques.end());

    for (int i = 0; index < col_id[col_id.size() - 1]; i++) {
        if (col_id[k] > uniques.size())
            break;
        vector<vector<double>> temp;

        while (index == col_id[k]) {
            vector<double> row;
            row.push_back(col_x[k]);
            row.push_back(col_y[k]);
            row.push_back(col_z[k]);
            row.push_back(col_e[k]);
            row.push_back(col_m[k]);
            row.push_back(col_l[k]);
            row.push_back(col_id[k]);
            row.push_back(col_type[k]);
            row.push_back(col_t[k]);

            temp.push_back(row);
            k++;
        }

        sort(temp.begin(), temp.end(), compare);

        int id = 0;
        for (int j = 0; j < temp.size(); j++) {
            while (j < temp.size() && temp[j][5] == id)
                temp.erase(temp.begin() + j);
            id++;
        }

        while (index < col_id[k])
            index++;

        if (temp.size() == 6)
            data2.push_back(temp);
    }

    vector<vector<double>> data3;

    for (int i = 0; i < data2.size(); i++) {
        vector<double> row;
        row.push_back(data2[i][0][6]);

        for (int j = 0; j < 6; j++) {
            row.push_back(data2[i][j][0]);
            row.push_back(data2[i][j][1]);
            row.push_back(data2[i][j][2]);
            row.push_back(data2[i][j][3]);
            row.push_back(data2[i][j][4]);
        }

        data3.push_back(row);
    }


    vector<vector<double>> line1, line2;

    for (int i = 0; i < data3.size(); i++) {
        vector<double> row1, row2;

        row1.push_back(data3[i][1]);
        row1.push_back(data3[i][2]);
        row1.push_back(data3[i][3]);
        row1.push_back(data3[i][11]);
        row1.push_back(data3[i][12]);
        row1.push_back(data3[i][13]);
        line1.push_back(row1);

        row2.push_back(data3[i][16]);
        row2.push_back(data3[i][17]);
        row2.push_back(data3[i][18]);
        row2.push_back(data3[i][26]);
        row2.push_back(data3[i][27]);
        row2.push_back(data3[i][28]);
        line2.push_back(row2);
    }

    for (int i = 0; i < line1.size(); i++) {
        line1[i][0] += 50;
        line1[i][1] += 50;
        line1[i][2] = round(line1[i][2] * 10) / 10;
        line1[i][3] += 50;
        line1[i][4] += 50;
        line1[i][5] = round(line1[i][5] * 10) / 10;

        line2[i][0] += 50;
        line2[i][1] += 50;
        line2[i][2] = round(line2[i][2] * 10) / 10;
        line2[i][3] += 50;
        line2[i][4] += 50;
        line2[i][5] = round(line2[i][5] * 10) / 10;
    }

    vector<double> angles;
    vector<vector<double>> midpoints;
    for (int i = 0; i < line1.size(); i++) {
        vector<vector<double>> cA = closestApproach(line1[i], line2[i]);

        if (cA.size() != 1) {
            vector<double> midpoint = { div(add(cA[0], cA[1]),2) };

            angles.push_back(angleCalculation(cA[0], cA[1], midpoint, line1[i], line2[i]));
            midpoints.push_back(midpoint);
        }
    }

    vector<vector<double>> rst;

    for (int i = 0; i < midpoints.size(); i++) {
        vector<double> r;

        r.push_back(angles[i]);
        for (int j = 0; j < 3; j++)
            r.push_back(midpoints[i][j]);
        
        rst.push_back(r);
    }


    /*
    MATFile* output;
    mxArray* arr;

    output = matOpen("test.mat", "w");
    arr = mxCreateDoubleMatrix(3, 4, mxREAL);

    memcpy((void*)(mxGetPr(arr)), (void*)result, sizeof(data));
    matPutVariable(output, "LocalDouble", arr);

    mxDestroyArray(arr);

    ofstream fout("aluminum.txt");
    */
    ofstream fout;

     fout.open("aluminum.txt", ios::out);
    // fout.open(output + ".txt", ios::out);

     //sort(rst.begin(), rst.end(), compare2);
    for (int i = 0; i < rst.size(); i++) {
        if (!isnan(rst[i][0]))
            fout << rst[i][0] << "\t" << rst[i][1] << "\t" << rst[i][2] << "\t" << rst[i][3] << endl;
    }
    fout.close();

    finish = clock();

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << endl << "The total run time is " << duration << " sec" << endl << endl;

    return 0;
}
