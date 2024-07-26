#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Point3D {
    double x, y, z;
};

struct Vector3D {
    double x, y, z;
    
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
    
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
    
    double dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    Vector3D cross(const Vector3D& other) const {
        return Vector3D(y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x);
    }
    
    double length() const {
        return sqrt(x * x + y * y + z * z);
    }
};

bool cmp(const Vector3D &p1, const Vector3D &p2)
{
    if(p1.x < p2.x){
        return true;
    }
    else if(p1.x == p2.x){
        if(p1.z == p1.z) return p1.y < p2.y;
        else if(p1.z > p2.z) return true;
    }
    else{
        return false;
    }
}

double calculateShadowArea(const Point3D& p1, const Point3D& p2, const Point3D& light) {
    Vector3D v1(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
    Vector3D v2(light.x - p1.x, light.y - p1.y, light.z - p1.z);
    
    Vector3D normal = v1.cross(v2);
    
    // 그림자가 땅에 수직으로 투영된다고 가정
    double area = fabs(normal.x * p1.z + normal.y * p1.z + normal.z * p1.z) / normal.length();
    
    return area;
}

Vector3D calculateSquareNormal(const vector<int>& square, const Vector3D* pointlist) 
{
    Vector3D p1( pointlist[square[1]]- pointlist[square[0]]);
    Vector3D p2( pointlist[square[3]]- pointlist[square[0]]);
    
    Vector3D normal = p1.cross(p2);
    return normal;
} 


int main() {
    Point3D p1, p2, light;
    
    cin >> p1.x >> p1.y >> p1.z;
    cin >> p2.x >> p2.y >> p2.z;
    cin >> light.x >> light.y >> light.z;
    
    Vector3D hexa[8] =  {
        {p1.x, p1.y, p1.z},
        {p1.x, p1.y, p2.z},
        {p1.x, p2.y, p1.z},
        {p2.x, p1.y, p1.z},
        {p1.x, p2.y, p2.z},
        {p2.x, p1.y, p2.z},
        {p2.x, p2.y, p1.z},
        {p2.x, p2.y, p2.z}
        
    };
    std::sort(hexa, hexa+6, cmp);
    vector<vector<int>> index = {
        {1,5,6,2},
        {5,7,8,6},
        {7,3,4,8},
        {1,3,4,2},
        {2,6,8,4},
        {5,1,3,6}
    };
  
    
    double shadowArea = calculateShadowArea(p1, p2, light);
    
    std::cout << shadowArea << endl;
    
    return 0;
}