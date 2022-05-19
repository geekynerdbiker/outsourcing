//
//  canvas2d.hpp
//  cpp-geo
//
//  Created by Jacob An on 2022/05/18.
//

#ifndef canvas2d_hpp
#define canvas2d_hpp

#include <iostream>
#include <string>
#include <vector>
#include "geometry.hpp"

class canvas2d : public std::vector<geometry*> {
private:
    // 캔버스 데이터 저장을 위한 이차원 벡터
    std::vector<std::vector<geometry*>> c;
public:
    // 생성자
    canvas2d(int width, int height, char c_empty) {
        // 높이의 갯수만큼 벡터 생성
        for (int i = 0; i < height; i++) {
            std::vector<geometry*> v;
            int *s = (int *)malloc(sizeof(int) * 3);
            
            for (int j = 0; j < width; j++) {
                s[0] = j;
                s[1] = i;
                s[2] = c_empty;
                
                // geometry 인스턴스 생성
                geometry *g = new point<int, 3>(s);
                v.push_back(g);
            }
            c.push_back(v);
        }
    }
    
    // 캔버스 출력함수
    void draw2stdout() {
        for (int i = 0; i < c.size(); i++) {
            for (int j = 0; j < c.at(i).size(); j++) {
                std::cout << c.at(i).at(j);
            }
            std::cout << std::endl;
        }
    }
};

#endif /* canvas2d_hpp */
