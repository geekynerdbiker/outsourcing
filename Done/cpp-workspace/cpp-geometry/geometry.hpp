//
//  geometry.hpp
//  cpp-geo
//
//  Created by Jacob An on 2022/05/18.
//

#ifndef geometry_hpp
#define geometry_hpp

#include <string>

class geometry {
public:
    virtual void draw2canvas() {}
};

template <typename T, int N>
class point : public geometry {
public:
    T x, y, data = 0;
    
    // 생성자
    point<T, N>(const T* coords) {
        // 좌표를 타입에 상관없이 정수로 캐스팅
        x = (int)coords[1];
        y = (int)coords[0];
        
        // 2차원일 때
        if (N < 2)
            data = 1;
        // 단일 값이 10보다 큰 경우 캐릭터 형일 경우를 위함
        else if (coords[2] > 10) {
            data = (char)coords[2];
        // 고차원일 때
        } else {
            data = 0;
            for (int i = 2; i < N; i++)
                data += coords[i];
            // 값이 10보다 커지면 나머지 연산
            data = (int)data % 10;
        }
    };
    
    ~point<T, N>() {};
    
    virtual void draw2canvas() {}
    T getData() { return getData(); }
};

template <typename T>
class rectangle : public geometry {
public:
    T x1, x2, y1, y2;
    // 생성자
    rectangle<T>(T x_1, T y_1, T x_2, T y_2) {
        x1 = (int)x_1;
        y1 = (int)y_1;
        x2 = (int)x_2;
        y2 = (int)y_2;
    }
    
    ~rectangle<T>() {}
    
    bool is_equal(const rectangle<T>& other) {
        // 두 사각형 좌표 일치
        if (x1 == other.x1 && x2 == other.x2 && y1 == other.y1 && y2 == other.y2)
            return true;
        // 한 사각형 x좌표 반전
        else if (x1 == other.x2 && x2 == other.x1 && y1 == other.y1 && y2 == other.y2)
            return true;
        // 한 사각형 y좌표 반전
        else if (x1 == other.x1 && x2 == other.x2 && y1 == other.y2 && y2 == other.y1)
            return true;
        // 한 사각형 x, y좌표 반전
        else if (x1 == other.x2 && x2 == other.x1 && y1 == other.y2 && y2 == other.y1)
            return true;
        return false;
    }
    
    bool is_intersect(const rectangle<T>& other) {
        if (is_equal(other))
            return false;
        
        // 범위 지정을 위해 큰값 작은값 정리
        T smallX = x1 < x2 ? x1 : x2;
        T largeX = smallX == x1 ? x1 : x2;
        
        T smallY = y1 < y2 ? y1 : y2;
        T largeY = smallX == y1 ? y1 : y2;
        
        
        // 한 점이 사각형에 포함
        if (other.x1 > smallX && other.x1 < largeX && other.y1 > smallY && other.y1 < largeY)
            return true;
        else if (other.x2 > smallX && other.x2 < largeX && other.y2 > smallY && other.y2 < largeY)
            return true;
        // 두 변을 공유
        else if ((other.x1 == x1 && other.x2 == x2) || (other.x1 == x2 && other.x2 == x1))
            return true;
        else if ((other.y1 == y1 && other.y2 == y2) || (other.y1 == y2 && other.y2 == y1))
            return true;
        return false;
    }
    
    bool is_line_overlap(const rectangle<T>& other) {
        if (is_equal(other) || is_intersect(other)) return false;
        // 세로변 공유
        if ((x1 == other.x1 || x1 == other.x2 || x2 == other.x1 || x2 == other.x2))
            return true;
        // 가로변 공유
        if ((y1 == other.y1 || y1 == other.y2 || y2 == other.y1 || x2 == other.y2))
            return true;
        return false;
    }
    
    bool is_point_match(const rectangle<T>& other) {
        if (is_equal(other) || is_intersect(other) || is_line_overlap(other))
            return false;
        if ((x1 == other.x1 && y1 == other.y1) || (x1 == other.x2 && y1 == other.y2) || (x2 == other.x1 && y2 == other.y1) || (x2 == other.x2 && y2 == other.y2))
            return true;
                
        return false;
    }
    
    bool is_disjoint(const rectangle<T>& other) {
        return !(is_equal(other) || is_intersect(other) || is_line_overlap(other) || is_point_match(other));
    }
    
    virtual void draw2canvas() {}
};
#endif /* geometry_hpp */
