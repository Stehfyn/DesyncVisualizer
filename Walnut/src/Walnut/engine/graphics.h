#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;
//(Part 1): Include all of our helper symbols that are necessary to render based off our
// model-view-projection matrix
#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "cube.h"
#include "triangle.h"
#include "Pyramid.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Plane.h"
#include <stack>
#include <cmath>
#include <deque>
#include "Walnut/editor/SceneHelpers.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();

    bool Initialize(int width, int height);

    void Update(float dt, float rttPlayer, float rttOther);
    void Update2(float dt, NetworkSettings ns);

    void Render();

    Camera* getCamera() { return m_camera; }
    Plane* getPlayer() { return m_Player; }

  private:
    std::string ErrorString(GLenum error);

    stack<glm::mat4> modelStack;

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    GLint m_vertPos;
    GLint m_vertCol;

    Plane* m_Player;
    Plane* m_Server;
    Plane* m_Other;

    Plane* m_Plane;
    std::vector<Plane*> m_Checkers;
};

#endif /* GRAPHICS_H */
