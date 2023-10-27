#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm.hpp"
#include "GL/ext.hpp"
#include "GL/freeglut_ext.h"
#include "GL/gtc/matrix_transform.hpp"

using namespace std;

glm::mat4 defaultMatrix = glm::mat4(1.0f);
glm::mat4 transMatrix[4];
glm::mat4 rotMatrix[4];

glm::mat4 smallFallMatrix[4];
glm::mat4 bigFallMatrix[4];

GLuint program;
GLuint VAO[5];
GLuint VBO[5];

int width = 650;
int height = 650;

int objectColor = 0;

int type[4] = { 0, 0, 0, 0 };
int cnt[4] = { 0, 0, 0, 0 };

bool timer = false;
bool fill = true;
bool isRoad = false;
bool isDragged = false;

bool collide_1[4] = { false, false, false, false };
bool collide_2[4] = { false, false, false, false };
bool collide_3[4] = { false, false, false, false };
bool collide_4[4] = { false, false, false, false };
bool isSliced[4] = { false, false, false, false };

float den;
float ua;
float ub;

float x[5];
float y[5];

float speed = 1.0f;
float color = 1.0f;

float slice[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float remain[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float collide_tr[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float collide_sq[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

float smallFall[4] = { 0.f, 0.f, 0.f, 0.f };
float bigFall[4] = { 0.f, 0.f, 0.f, 0.f };

float transX[4] = { -1.2f, 1.2f, -1.2f, 1.2f };
float transY[4] = { 0.125f, 0.725f, -1.075f, -0.475f };


GLuint loadShaders(const char* path_vertex, const char* path_fragment) {
    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    string VertexShaderCode;
    ifstream VertexShaderStream(path_vertex, ios::in);
    
    if (VertexShaderStream.is_open()) {
        stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    } else {
        printf("Cannot read file\n");
        return -1;
    }
    
    string FragmentShader;
    ifstream FragmentShaderStream(path_fragment, ios::in);
    if (FragmentShaderStream.is_open()) {
        stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShader = sstr.str();
        FragmentShaderStream.close();
    } else {
        printf("Cannot read file\n");
        return -1;
    }
    
    GLint result = GL_FALSE;
    int length;
    
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShader, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShader);
    
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    
    if (length > 0) {
        vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShader, length, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }
    
    char const* FragmentSourcePointer = FragmentShader.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    
    if (length > 0) {
        vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }
    
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShader);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (length > 0) {
        vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, length, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
    
    glDetachShader(ProgramID, VertexShader);
    glDetachShader(ProgramID, FragmentShaderID);
    
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShaderID);
    
    return ProgramID;
}

void convertDeviceXY(int x, int y, float* ox, float* oy) {
    int w = width;
    int h = height;
    
    *ox = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
    *oy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}

void tick(int n) {
    for (int i = 0; i < 4; i++) {
        cnt[i] = 0;
        
        if (!isSliced[i]) {
            if (i == 0) {
                transX[i] += 0.03f * speed;
                transY[i] -= 0.015f * speed;
            } else if (i == 1) {
                transX[i] -= 0.03f * speed;
                transY[i] -= 0.015f * speed;
            } else if (i == 2) {
                transX[i] += 0.03f * speed;
                transY[i] += 0.015f * speed;
            } else if (i == 3) {
                transX[i] -= 0.03f * speed;
                transY[i] += 0.015f * speed;
            }
            
            transMatrix[i] = glm::mat4(1.0f);
            transMatrix[i] = glm::translate(transMatrix[i], glm::vec3(transX[i], transY[i], 0.f));
            
            x[1] = slice[0];
            x[2] = slice[2];
            y[1] = slice[1];
            y[2] = slice[3];
            
            if (i < 2) {
                x[3] = 0.f + transX[i];
                x[4] = -0.2f + transX[i];
                y[3] = 0.35f + transY[i];
                y[4] = 0.f + transY[i];
                
                den = (y[4] - y[3]) * (x[2] - x[1]) - (x[4] - x[3]) * (y[2] - y[1]);
                ua = ((x[4] - x[3]) * (y[1] - y[3]) - (y[4] - y[3]) * (x[1] - x[3])) / den;
                ub = ((x[2] - x[1]) * (y[1] - y[3]) - (y[2] - y[1]) * (x[1] - x[3])) / den;
                
                if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1 && den != 0.f) {
                    cnt[i]++;
                    collide_1[i] = true;
                    
                    collide_tr[0] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                    collide_tr[1] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                }
                
                x[3] = 0.f + transX[i];
                x[4] = 0.2f + transX[i];
                y[3] = 0.35f + transY[i];
                y[4] = 0.f + transY[i];
                
                den = (y[4] - y[3]) * (x[2] - x[1]) - (x[4] - x[3]) * (y[2] - y[1]);
                ua = ((x[4] - x[3]) * (y[1] - y[3]) - (y[4] - y[3]) * (x[1] - x[3])) / den;
                ub = ((x[2] - x[1]) * (y[1] - y[3]) - (y[2] - y[1]) * (x[1] - x[3])) / den;
                
                if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1 && den != 0.f) {
                    cnt[i]++;
                    collide_2[i] = true;
                    
                    if (collide_1[i]) {
                        collide_tr[2] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                        collide_tr[3] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                    } else {
                        collide_tr[0] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                        collide_tr[1] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                    }
                }
                
                x[3] = -0.2f + transX[i];
                x[4] = 0.2f + transX[i];
                y[3] = 0.f + transY[i];
                y[4] = 0.f + transY[i];
                
                den = (y[4] - y[3]) * (x[2] - x[1]) - (x[4] - x[3]) * (y[2] - y[1]);
                ua = ((x[4] - x[3]) * (y[1] - y[3]) - (y[4] - y[3]) * (x[1] - x[3])) / den;
                ub = ((x[2] - x[1]) * (y[1] - y[3]) - (y[2] - y[1]) * (x[1] - x[3])) / den;
                
                if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1 && den != 0.f) {
                    cnt[i]++;
                    collide_3[i] = true;
                    
                    collide_tr[2] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                    collide_tr[3] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                }
            } else {
                x[3] = -0.175f + transX[i];
                x[4] = -0.175f + transX[i];
                y[3] = 0.f + transY[i];
                y[4] = 0.35f + transY[i];
                
                den = (y[4] - y[3]) * (x[2] - x[1]) - (x[4] - x[3]) * (y[2] - y[1]);
                ua = ((x[4] - x[3]) * (y[1] - y[3]) - (y[4] - y[3]) * (x[1] - x[3])) / den;
                ub = ((x[2] - x[1]) * (y[1] - y[3]) - (y[2] - y[1]) * (x[1] - x[3])) / den;
                
                if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1 && den != 0.f) {
                    cnt[i]++;
                    collide_1[i] = true;
                    
                    collide_sq[0] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                    collide_sq[1] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                }
                
                x[3] = -0.175f + transX[i];
                x[4] = 0.175f + transX[i];
                y[3] = 0.35f + transY[i];
                y[4] = 0.35f + transY[i];
                
                den = (y[4] - y[3]) * (x[2] - x[1]) - (x[4] - x[3]) * (y[2] - y[1]);
                ua = ((x[4] - x[3]) * (y[1] - y[3]) - (y[4] - y[3]) * (x[1] - x[3])) / den;
                ub = ((x[2] - x[1]) * (y[1] - y[3]) - (y[2] - y[1]) * (x[1] - x[3])) / den;
                
                if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1 && den != 0.f) {
                    cnt[i]++;
                    collide_2[i] = true;
                    
                    if (collide_1[i]) {
                        collide_sq[2] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                        collide_sq[3] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                    } else {
                        collide_sq[0] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                        collide_sq[1] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                    }
                }
                
                x[3] = 0.175f + transX[i];
                x[4] = 0.175f + transX[i];
                y[3] = 0.f + transY[i];
                y[4] = 0.35f + transY[i];
                
                den = (y[4] - y[3]) * (x[2] - x[1]) - (x[4] - x[3]) * (y[2] - y[1]);
                ua = ((x[4] - x[3]) * (y[1] - y[3]) - (y[4] - y[3]) * (x[1] - x[3])) / den;
                ub = ((x[2] - x[1]) * (y[1] - y[3]) - (y[2] - y[1]) * (x[1] - x[3])) / den;
                
                if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1 && den != 0.f) {
                    cnt[i]++;
                    collide_3[i] = true;
                    
                    if (collide_1[i] || collide_2[i]) {
                        collide_sq[2] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                        collide_sq[3] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                    } else {
                        collide_sq[0] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                        collide_sq[1] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                    }
                }
                
                x[3] = -0.175f + transX[i];
                x[4] = 0.175f + transX[i];
                y[3] = 0.f + transY[i];
                y[4] = 0.f + transY[i];
                
                den = (y[4] - y[3]) * (x[2] - x[1]) - (x[4] - x[3]) * (y[2] - y[1]);
                ua = ((x[4] - x[3]) * (y[1] - y[3]) - (y[4] - y[3]) * (x[1] - x[3])) / den;
                ub = ((x[2] - x[1]) * (y[1] - y[3]) - (y[2] - y[1]) * (x[1] - x[3])) / den;
                
                if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1 && den != 0.f) {
                    cnt[i]++;
                    collide_4[i] = true;
                    
                    if (collide_1[i] || collide_2[i] || collide_3[i]) {
                        collide_sq[2] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                        collide_sq[3] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                    } else {
                        collide_sq[0] = x[1] + (ua * (x[2] - x[1])) - transX[i];
                        collide_sq[1] = y[1] + (ua * (y[2] - y[1])) - transY[i];
                    }
                }
            }
        }
        
        if (cnt[i] >= 2)
            isSliced[i] = true;
        
        if (isSliced[i]) {
            smallFall[i] -= 0.015f;
            bigFall[i] -= 0.01f;
            smallFallMatrix[i] = glm::translate(smallFallMatrix[i], glm::vec3(0.f, smallFallValue[i], 0.f));
            bigFallMatrix[i] = glm::translate(bigFallMatrix[i], glm::vec3(0.f, bigFallValue[i], 0.f));
            
            if (i == 0 || i == 2)
                rotMatrix[i] = glm::rotate(rotMatrix[i], glm::radians(-3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            else if (i == 1 || i == 3)
                rotMatrix[i] = glm::rotate(rotMatrix[i], glm::radians(3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            
            if (i < 2) {
                if (collide_1[i] && collide_2[i])
                    type[i] = 1;
                else if (collide_2[i] && collide_3[i])
                    type[i] = 2;
                else if (collide_1[i] && collide_3[i])
                    type[i] = 3;
            } else {
                if (collide_1[i] && collide_2[i])
                    type[i] = 1;
                else if (collide_2[i] && collide_3[i])
                    type[i] = 2;
                else if (collide_1[i] && collide_4[i])
                    type[i] = 3;
                else if (collide_3[i] && collide_4[i])
                    type[i] = 4;
                else if (collide_2[i] && collide_4[i])
                    type[i] = 5;
                else if (collide_1[i] && collide_3[i])
                    type[i] = 6;
            }
        }
        
        if (bigFall[i] < -0.3f || transX[0] > 1.2f || transX[2] > 1.2f || transX[1] < -1.2 || transX[3] < -1.2f) {
            isSliced[i] = false;
            collide_1[i] = false;
            collide_2[i] = false;
            collide_3[i] = false;
            collide_4[i] = false;
            
            smallFallMatrix[i] = glm::mat4(1.0f);
            bigFallMatrix[i] = glm::mat4(1.0f);
            rotMatrix[i] = glm::mat4(1.0f);
            type[i] = 0;
            
            smallFall[i] = 0.f;
            bigFall[i] = 0.f;
            
            if (i == 0) {
                transX[i] = -1.2f;
                transY[i] = 0.125f;
            } else if (i == 1) {
                transX[i] = 1.2f;
                transY[i] = 0.725f;
            } else if (i == 2) {
                transX[i] = -1.2f;
                transY[i] = -1.075f;
            } else if (i == 3) {
                transX[i] = 1.2f;
                transY[i] = -0.475f;
            }
            
            transMatrix[i] = glm::mat4(1.0f);
            transMatrix[i] = glm::translate(transMatrix[i], glm::vec3(transX[i], transY[i], 0.f));
        }
    }
    
    if (isDragged) {
        slice[0] = 1.0f;
        slice[1] = 1.0f;
        slice[2] = 1.0f;
        slice[3] = 1.0f;
        
        isDragged = false;
    }
    
    if (color > 0)
    {
        color -= 0.1;
    }
    
    glutPostRedisplay();
    
    if (!timer) {
        timer = true;
        glutTimerFunc(50, tick, 1);
    }
    timer = false;
}

void mouse(int button, int state, int x, int y) {
    float ox;
    float oy;
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        convertDeviceXY(x, y, &ox, &oy);
        cout << "x : " << ox << " y : " << oy << endl;
        
        slice[0] = ox;
        slice[1] = oy;
        slice[2] = ox;
        slice[3] = oy;
        
        remain[0] = ox;
        remain[1] = oy;
        remain[2] = ox;
        remain[3] = oy;
    }
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        convertDeviceXY(x, y, &ox, &oy);
        cout << "x : " << ox << " y : " << oy << endl;
        
        slice[2] = ox;
        slice[3] = oy;
        remain[2] = ox;
        remain[3] = oy;
        
        color = 1.0f;
        isDragged = true;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '=':
            if (speed < 2.8f)
                speed += 0.4f;
            break;
            
        case '-':
            if (speed > 0.4f)
                speed -= 0.4f;
            break;
            
        case 'r':
            if (isRoad)
                isRoad = false;
            else
                isRoad = true;
            break;
            
        case 'w':
            if (fill) {
                glPolygonMode(GLenum(GL_FRONT_AND_BACK), GLenum(GL_LINE));
                fill = false;
            } else {
                glPolygonMode(GLenum(GL_FRONT_AND_BACK), GLenum(GL_FILL));
                fill = true;
            }
            break;
            
        case 'q':
            exit(0);
    }
    
    glutPostRedisplay();
}

void drawTriangle() {
    float triangleVertexData[] = {
         0.f, 0.35f, 0.f,                            0.0f, 0.0f, 0.0f,
        -0.2f, 0.f, 0.f,                            0.0f, 0.0f, 0.0f,
        0.2f, 0.f, 0.f,                                0.0f, 0.0f, 0.0f,
        
        0.f, 0.35f, 0.f,                            0.0f, 0.0f, 0.0f,
        collide_tr[0], collide_tr[1], 0.0f,    0.0f, 0.0f, 0.0f,
        collide_tr[2], collide_tr[3], 0.0f,    0.0f, 0.0f, 0.0f,
        -0.2f, 0.f, 0.f,                            0.0f, 0.0f, 0.0f,
        0.2f, 0.f, 0.f,                                0.0f, 0.0f, 0.0f,
        
        0.2f, 0.f, 0.f,                                0.0f, 0.0f, 0.0f,
        collide_tr[2], collide_tr[3], 0.f,    0.0f, 0.0f, 0.0f,
        collide_tr[0], collide_tr[1], 0.f,    0.0f, 0.0f, 0.0f,
        -0.2f, 0.f, 0.f,                            0.0f, 0.0f, 0.0f,
        0.f, 0.35f, 0.f,                            0.0f, 0.0f, 0.0f,
        
        -0.2f, 0.f, 0.f,                            0.0f, 0.0f, 0.0f,
        collide_tr[2], collide_tr[3], 0.f,    0.0f, 0.0f, 0.0f,
        collide_tr[0], collide_tr[1], 0.f,    0.0f, 0.0f, 0.0f,
        0.2f, 0.f, 0.f,                                0.0f, 0.0f, 0.0f,
        0.f, 0.35f, 0.f,                            0.0f, 0.0f, 0.0f,
    };
    
    glUseProgram(program);
    
    unsigned int modelLocation = glGetUniformLocation(program, "transform");
    
    for (int i = 0; i < 2; i++) {
        if (i == 0)
            objectColor = 0;
        else
            objectColor = 1;
        
        if (objectColor == 0) {
            for (int j = 0; j < 108; j++) {
                if (j % 6 == 3)
                    triangleVertexData[j] = 1.0f;
                else if (j % 6 == 4)
                    triangleVertexData[j] = 0.0f;
                else if (j % 6 == 5)
                    triangleVertexData[j] = 0.0f;
            }
        } else if (objectColor == 1) {
            for (int j = 0; j < 108; j++) {
                if (j % 6 == 3)
                    triangleVertexData[j] = 0.0f;
                else if (j % 6 == 4)
                    triangleVertexData[j] = 0.0f;
                else if (j % 6 == 5)
                    triangleVertexData[j] = 1.0f;
            }
        }
        
        glGenVertexArrays(1, &VAO[i]); glBindVertexArray(VAO[i]);
        glGenBuffers(1, &VBO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertexData), triangleVertexData, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        if (type[i] == 0) {
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transMatrix[i]));
            glDrawArrays(GL_TRIANGLES, 0, 3);
        } else {
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(smallFallMatrix[i] * transMatrix[i] * rotMatrix[i]));
            glDrawArrays(GL_TRIANGLES, 3 + ((sliceType[i] - 1) * 5), 3);
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(bigFallMatrix[i] * transMatrix[i] * rotMatrix[i]));
            glDrawArrays(GL_TRIANGLES, 4 + ((sliceType[i] - 1) * 5), 3);
            glDrawArrays(GL_TRIANGLES, 5 + ((sliceType[i] - 1) * 5), 3);
        }
    }
}

void drawSquare() {
    float squareVertexData[] = {
        -0.175f, 0.35f, 0.f,                0.0f, 0.0f, 0.0f,
        -0.175f, 0.f, 0.f,                    0.0f, 0.0f, 0.0f,
        0.175f, 0.35f, 0.f,                    0.0f, 0.0f, 0.0f,
        0.175f, 0.0f, 0.f,                    0.0f, 0.0f, 0.0f,
        
        -0.175f, 0.35f, 0.f,                0.0f, 0.0f, 0.0f,
        collide_sq[0], collide_sq[1], 0.f,    0.0f, 0.0f, 0.0f,
        collide_sq[2], collide_sq[3], 0.f,    0.0f, 0.0f, 0.0f,
        -0.175f, 0.f, 0.f,                    0.0f, 0.0f, 0.0f,
        0.175f, 0.35f, 0.f,                    0.0f, 0.0f, 0.0f,
        0.175f, 0.0f, 0.f,                    0.0f, 0.0f, 0.0f,
        
        0.175f, 0.35f, 0.f,                    0.0f, 0.0f, 0.0f,
        collide_sq[0], collide_sq[1], 0.f,    0.0f, 0.0f, 0.0f,
        collide_sq[2], collide_sq[3], 0.f,    0.0f, 0.0f, 0.0f,
        -0.175f, 0.35f, 0.f,                0.0f, 0.0f, 0.0f,
        0.175f, 0.0f, 0.f,                    0.0f, 0.0f, 0.0f,
        -0.175f, 0.f, 0.f,                    0.0f, 0.0f, 0.0f,
        
        -0.175f, 0.f, 0.f,                    0.0f, 0.0f, 0.0f,
        collide_sq[0], collide_sq[1], 0.f,    0.0f, 0.0f, 0.0f,
        collide_sq[2], collide_sq[3], 0.f,    0.0f, 0.0f, 0.0f,
        -0.175f, 0.35f, 0.f,                0.0f, 0.0f, 0.0f,
        0.175f, 0.0f, 0.f,                    0.0f, 0.0f, 0.0f,
        0.175f, 0.35f, 0.f,                    0.0f, 0.0f, 0.0f,
        
        0.175f, 0.0f, 0.f,                    0.0f, 0.0f, 0.0f,
        collide_sq[0], collide_sq[1], 0.f,    0.0f, 0.0f, 0.0f,
        collide_sq[2], collide_sq[3], 0.f,    0.0f, 0.0f, 0.0f,
        0.175f, 0.35f, 0.f,                    0.0f, 0.0f, 0.0f,
        -0.175f, 0.f, 0.f,                    0.0f, 0.0f, 0.0f,
        -0.175f, 0.35f, 0.f,                0.0f, 0.0f, 0.0f,
        
        -0.175f, 0.35f, 0.f,                0.0f, 0.0f, 0.0f,
        -0.175f, 0.f, 0.f,                    0.0f, 0.0f, 0.0f,
        collide_sq[0], collide_sq[1], 0.f,    0.0f, 0.0f, 0.0f,
        collide_sq[2], collide_sq[3], 0.f,    0.0f, 0.0f, 0.0f,
        0.175f, 0.35f, 0.f,                    0.0f, 0.0f, 0.0f,
        0.175f, 0.0f, 0.f,                    0.0f, 0.0f, 0.0f,
        
        -0.175f, 0.35f, 0.f,                0.0f, 0.0f, 0.0f,
        0.175f, 0.35f, 0.f,                    0.0f, 0.0f, 0.0f,
        collide_sq[0], collide_sq[1], 0.f,    0.0f, 0.0f, 0.0f,
        collide_sq[2], collide_sq[3], 0.f,    0.0f, 0.0f, 0.0f,
        -0.175f, 0.f, 0.f,                    0.0f, 0.0f, 0.0f,
        0.175f, 0.0f, 0.f,                    0.0f, 0.0f, 0.0f,
    };
    
    glUseProgram(program);
    
    unsigned int modelLocation = glGetUniformLocation(program, "transform");
    
    for (int i = 2; i < 4; i++) {
        if (i == 2)
            objectColor = 0;
        else
            objectColor = 1;
        
        if (objectColor == 0) {
            for (int j = 0; j < 240; j++) {
                if (j % 6 == 3)
                    squareVertexData[j] = 1.0f;
                else if (j % 6 == 4)
                    squareVertexData[j] = 1.0f;
                else if (j % 6 == 5)
                    squareVertexData[j] = 0.0f;
            }
        } else if (objectColor == 1) {
            for (int j = 0; j < 240; j++) {
                if (j % 6 == 3)
                    squareVertexData[j] = 0.0f;
                else if (j % 6 == 4)
                    squareVertexData[j] = 1.0f;
                else if (j % 6 == 5)
                    squareVertexData[j] = 1.0f;
            }
        }
        
        glGenVertexArrays(1, &VAO[i]); glBindVertexArray(VAO[i]);
        glGenBuffers(1, &VBO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertexData), squareVertexData, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        if (type[i] == 0) {
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transMatrix[i]));
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawArrays(GL_TRIANGLES, 1, 3);
        } else {
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(smallFallMatrix[i] * transMatrix[i] * rotMatrix[i]));
            
            if (type[i] < 5)
                glDrawArrays(GL_TRIANGLES, 4 + ((sliceType[i] - 1) * 6), 3);
            else {
                glDrawArrays(GL_TRIANGLES, 4 + ((sliceType[i] - 1) * 6), 3);
                glDrawArrays(GL_TRIANGLES, 5 + ((sliceType[i] - 1) * 6), 3);
            }
            
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(bigFallMatrix[i] * transMatrix[i] * rotMatrix[i]));
            
            if (type[i] < 5) {
                glDrawArrays(GL_TRIANGLES, 5 + ((sliceType[i] - 1) * 6), 3);
                glDrawArrays(GL_TRIANGLES, 6 + ((sliceType[i] - 1) * 6), 3);
                glDrawArrays(GL_TRIANGLES, 7 + ((sliceType[i] - 1) * 6), 3);
            } else {
                glDrawArrays(GL_TRIANGLES, 6 + ((sliceType[i] - 1) * 6), 3);
                glDrawArrays(GL_TRIANGLES, 7 + ((sliceType[i] - 1) * 6), 3);
            }
        }
    }
}

void drawSlice() {
    float vertexData[] = {
        slice[0], slice[1], 0.f,        1.0f, 1.0f, 1.0f,
        slice[2], slice[3], 0.f,        1.0f, 1.0f, 1.0f,
        
        remain[0], remain[1], 0.f,        color, color, color,
        remain[2], remain[3], 0.f,        color, color, color,
        
    };
    
    glUseProgram(program);
    
    unsigned int modelLocation = glGetUniformLocation(program, "transform");
    
    glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
    glGenBuffers(1, &VBO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(defaultMatrix));
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_LINES, 2, 2);
}

void drawPath() {
    float vertexData[] = {
        -1.2f, -0.9f, 0.f,        0.5f, 0.5f, 0.0f,
        1.2, 0.3f, 0.f,            0.5f, 0.5f, 0.0f,
        
        -1.2f, -0.3f, 0.f,        0.0f, 0.0f, 0.5f,
        1.2, 0.9f, 0.f,            0.0f, 0.0f, 0.5f,
        
        -1.2f, 0.3f, 0.f,        0.5f, 0.0f, 0.0f,
        1.2, -0.9f, 0.f,        0.5f, 0.0f, 0.0f,
        
        -1.2f, 0.9f, 0.f,        0.0f, 0.5f, 0.5f,
        1.2, -0.3f, 0.f,        0.0f, 0.5f, 0.5f,
        
    };
    
    glUseProgram(program);
    
    unsigned int modelLocation = glGetUniformLocation(program, "transform");
    
    glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
    glGenBuffers(1, &VBO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(defaultMatrix));
    
    glDrawArrays(GL_LINES, 0, 2);
    glDrawArrays(GL_LINES, 2, 2);
    glDrawArrays(GL_LINES, 4, 2);
    glDrawArrays(GL_LINES, 6, 2);
}

void initialzie() {
    glEnable(GL_DEPTH_TEST);
    
    program = loadShaders("vs.glsl", "fs.glsl");
    glutTimerFunc(10, tick, 1);
}

GLvoid onDisplay() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawTriangle();
    drawSquare();
    
    if (isRoad)
        drawPath();
    
    drawSlice();
    glutSwapBuffers();
}

GLvoid onReshape(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(300, 0);
    glutInitWindowSize(width, height);
    glutCreateWindow("practice_1");
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "Unable to initialize GLEW" << endl;
        exit(-1);
    } else {
        cout << "GLEW Initialized\n";
    }
    
    for (int i = 0; i < 4; i++)
    {
        transMatrix[i] = glm::mat4(1.0f);
        rotMatrix[i] = glm::mat4(1.0f);
        smallFallMatrix[i] = glm::mat4(1.0f);
        bigFallMatrix[i] = glm::mat4(1.0f);
    }
    
    initialzie();
    
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onReshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
}
