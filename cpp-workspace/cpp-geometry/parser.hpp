//
//  parser.hpp
//  cpp-geo
//
//  Created by Jacob An on 2022/05/18.
//

#ifndef parser_hpp
#define parser_hpp

#include <vector>
#include <string>
#include <sstream>
#include "geometry.hpp"
#include "canvas2d.hpp"

class parser {
public:
    
    std::vector<std::string> split(std::string str, char Delimiter) {
        // istringstream에 str을 담는다.
        std::istringstream iss(str);
        // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼
        std::string buffer;
        
        std::vector<std::string> result;
        
        while (getline(iss, buffer, Delimiter))
            // 절삭된 문자열을 vector에 저장
            result.push_back(buffer);
        
        return result;
    }
    
    canvas2d parse_canvas(const std::string& line) {
        std::vector<std::string> result = split(line, ',');
        
        // 너비, 높이, 공백을 채울 문자를 잘라낸 vector에서 할당
        int width = std::stoi(result.at(0));
        int height = std::stoi(result.at(1));
        char c_empty = result.at(2)[0];
        
        // 캔버스 생성
        canvas2d canvas = canvas2d(width, height, c_empty);
        
        return canvas;
    }
    
    geometry* parse_geometry(const std::string& line) {
        std::vector<std::string> result = split(line, ',');
        
        // 0, 1번째는 2차원 좌표이므로 고차원을 계산하기 위해 길이 지정
        int N = int(result.size() - 2);
        // point 일 때
        if (result.at(0).compare("point") == 0) {
            // int 타입일 때
            if (result.at(1).compare("int") == 0) {
                // 메모리 할당
                int *coords = (int *)malloc(sizeof(int) * (result.size()-2));
                // 문자열을 정수로 캐스팅 후 대입
                for (int i = 2; i < result.size(); i++)
                    coords[i] = std::stoi(result.at(i));
                
                // 2차원일 때
                if (N == 2) {
                    geometry *g = new point<int,2>(coords);
                    return g;
                // 고차원일 때
                } else if (N > 2) {
                    geometry *g = new point<int,3>(coords);
                    return g;
                }
            // 실수 타입일 때
            } else if (result.at(1).compare("float") == 0) {
                float *coords = (float *)malloc(sizeof(float) * (result.size()-2));
                for (int i = 2; i < result.size(); i++)
                    coords[i] = std::stoi(result.at(i));
                
                if (N == 2) {
                    geometry *g = new point<float,2>(coords);
                    return g;
                } else if (N > 2) {
                    geometry *g = new point<float,2>(coords);
                    return g;
                }
            }
        // rectangle일 때
        } else if (result.at(0).compare("rectangle") == 0) {
            // 정수 실수에 관계없이 정수형으로 저장
            float x_1 = std::stoi(result.at(2));
            float y_1 = std::stoi(result.at(3));
            float x_2 = std::stoi(result.at(4));
            float y_2 = std::stoi(result.at(5));
            
            // geometry 인스턴스 생성
            geometry *g = new rectangle<float>(x_1, y_1, x_2, y_2);
            return g;
        }
        return nullptr;
    }
};

#endif /* parser_hpp */
