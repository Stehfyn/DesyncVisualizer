#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    void SetView(glm::mat4);
    void Update(float dt);
    
  
  private:
    glm::mat4 projection;
    glm::mat4 view;
    unsigned int m_w, m_h;

public:
    float fov = 45.0f;
    float yaw =0.0f;
    float pitch = -90.0f;

    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;
    glm::mat4 translation = glm::mat4(1.0f);
    glm::mat4 rotation = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

};

#endif /* CAMERA_H */
