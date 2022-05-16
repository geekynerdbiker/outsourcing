#include <iostream>
#include <stdio.h>
#include <vector>
#include <GL/glew.h>
#include <GLUT/GLUT.h>
#include <glm/glm.hpp>

//uniform float uBlend;
//out vec4 vColor;
//out float vLightIntensity;
//const float SIDE = 2.;
//const vec3 LIGHTPOS = vec3( 5., 10., 10. );
//
//void main()
//{
//    vec4 vertex0 = aVertex;
//    vertex0.xyz *= 4./length(vertex0.xyz);
//    vertex0.xyz = clamp( vertex0.xyz, -SIDE, SIDE );
//    vec3 tnorm = normalize( uNormalMatrix * aNormal );
//    vec3 ECposition = vec3( uModelViewMatrix * aVertex );
//    vLightIntensity = abs( dot(normalize(LIGHTPOS - ECposition),
//                               tnorm));
//    if( vLightIntensity < 0.2 )
//        vLightIntensity = 0.2;
//    vColor = aColor;
//    gl_Position = uModelViewProjectionMatrix *
//    mix( aVertex, vertex0, uBlend );
//}


std::vector < unsigned int > vertexIndices, uvIndices, normalIndices;
std::vector < glm::vec3 > temp_vertices;
std::vector < glm::vec2 > temp_uvs;
std::vector < glm::vec3 > temp_normals;


float param = 0.0;

bool loadFile(std::string path) {
    File * file = fopen(path, "r");
    if (file == NULL) {
        perror("No File Exception.\n");
        return false;
    }
    
    while( 1 ){
        char lineHeader[128];
        
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;
        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
            
        }
    }
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    glRotatef(param, 0.0, 0.0, 1.0);
    glFlush();
    
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
    switch (KeyPressed) {
        case '1':
            for (float i = 0; i <= 1; i += 0.1) {
                param = i;
                glutPostRedisplay();
            }
            break;
            
        case '2':
            float new_param;
            std::cin >> new_param;
            param = new_param;
            glutPostRedisplay();
            break;
            
        default:
            break;
    }
}

int main(int argc, char* argv[]) {
    float param;
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutKeyboardFunc(MyKeyboard);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
}
