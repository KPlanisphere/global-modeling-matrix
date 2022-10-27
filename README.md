# Global Modeling Matrix

### Description
This project, completed as part of the course work at the Benemérita Universidad Autónoma de Puebla, focuses on implementing a global modeling matrix to manage 3D transformations for multiple objects. The objective is to use a combination of rotation, scaling, and translation to manipulate the position and orientation of 3D objects in space.

### Overview
OpenGL uses transformation matrices to manage the position, rotation, and scaling of objects. This project demonstrates how to use a global modeling matrix to apply transformations efficiently to multiple objects. The implementation includes operations for rotation, scaling, and translation, and leverages a stack to handle multiple transformation states.

### Objectives
- Implement a global modeling matrix for 3D transformations using OpenGL.
- Apply learned concepts to rotate, scale, and translate multiple 3D objects.
- Develop an understanding of transformation matrices and their applications in computer graphics.

### Key Features
- **Initialization**: Set up the OpenGL environment and window properties.
- **Transformation Functions**: Implement functions for rotating, scaling, and translating objects.
- **Matrix Operations**: Utilize matrix multiplication for applying transformations.
- **Global Modeling Matrix**: Manage transformations using a global modeling matrix.
- **Animation Loop**: Continuously apply transformations to animate 3D objects.

### Project Structure
The project includes the following main components:

#### Initialization
This function sets up the OpenGL environment, defining the color of the window and the projection parameters.

```cpp
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)WIDTH / HEIGHT, ZNEAR, ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EYE_X, EYE_Y, EYE_Z, CENTER_X, CENTER_Y, CENTER_Z, UP_X, UP_Y, UP_Z);
    glClearColor(0, 0, 0, 0);
}
```

#### Global Modeling Matrix

This function manages the global modeling matrix and applies transformations.

```cpp
void Operaciones3D::GlobalModelingMatrix(char eje, float theta, float sx, float sy, float sz, float tx, float ty, float tz) {
    LoadIdentity(A);
    switch (eje) {
        case 'X':
            rotateX(DegToRad(theta));
            break;
        case 'Y':
            rotateY(DegToRad(theta));
            break;
        case 'Z':
            rotateZ(DegToRad(theta));
            break;
    }
    translate(tx, ty, tz);
    MultM(T, A, A);
    Escalado(sx, sy, sz);
    MultM(E, A, A);
}
``` 

#### Main Function

This function initializes the graphics window and starts the main loop.

```cpp
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Global Modeling Matrix | Jesus Huerta Aguilar");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keys);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
```

#### Display Function

This function handles the rendering of objects using the global modeling matrix.

```cpp
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    glColor3f(1.0f, 1.0f, 1.0f);
    S.ShowStage();
    glutSwapBuffers();
}
```

#### Transformation Functions

These functions define the rotation, scaling, and translation matrices and multiply them with the transformation matrix.

```cpp
void translate(float dx, float dy, float dz) {
    float T[4][4] = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
    MultM(R, T, A);
}

void rotateX(float theta) {
    float R[4][4] = {
        {1, 0, 0, 0},
        {0, cos(theta), -sin(theta), 0},
        {0, sin(theta), cos(theta), 0},
        {0, 0, 0, 1}
    };
    MultM(T, R, A);
}

void rotateY(float theta) {
    float R[4][4] = {
        {cos(theta), 0, sin(theta), 0},
        {0, 1, 0, 0},
        {-sin(theta), 0, cos(theta), 0},
        {0, 0, 0, 1}
    };
    MultM(T, R, A);
}

void rotateZ(float theta) {
    float R[4][4] = {
        {cos(theta), -sin(theta), 0, 0},
        {sin(theta), cos(theta), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    MultM(T, R, A);
}
```

#### Matrix Multiplication Function

This function multiplies two 4x4 matrices.

```cpp
void MultM(float A[4][4], float B[4][4], float C[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
```

### Execution

The project initializes a graphical window and applies global transformations to the pyramid. The transformations are continuous, providing a dynamic visual representation of the 3D modeling matrix operations.

#### Pressing "1"

<p align= "center">
    <img src="https://github.com/KPlanisphere/binary-tree-operations/assets/60454942/92bdf505-8219-40c7-bf56-cedd1b863c2b" style="width: 70%; height: auto;">
</p>

<p align= "center">
    <img src="https://github.com/KPlanisphere/binary-tree-operations/assets/60454942/418d0c4c-5164-48ce-b3b3-5698f1dd9aea" style="width: 70%; height: auto;">
</p>

#### Pressing "Q"

<p align= "center">
    <img src="https://github.com/KPlanisphere/binary-tree-operations/assets/60454942/c3e60f77-83be-4cbd-8e76-70176e46224f" style="width: 70%; height: auto;">
</p>

<p align= "center">
    <img src="https://github.com/KPlanisphere/binary-tree-operations/assets/60454942/721e6e3c-b19c-458a-9194-9495cc529fbb" style="width: 70%; height: auto;">
</p>

#### Pressing "A"

<p align= "center">
    <img src="https://github.com/KPlanisphere/binary-tree-operations/assets/60454942/c292c32e-ff9b-497d-9dc9-d89d470ee68e" style="width: 70%; height: auto;">
</p>

<p align= "center">
    <img src="https://github.com/KPlanisphere/binary-tree-operations/assets/60454942/b6bb2a36-6944-4d7e-bc37-7c63cd462b28" style="width: 70%; height: auto;">
</p>