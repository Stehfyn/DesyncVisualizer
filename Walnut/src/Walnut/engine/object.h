#ifndef OBJECT_H
#define OBJECT_H
// (Part 1): Include std::vector as well as our opengl headers grabbed by glew, our glfw3 symbols for our window, as well as glm symbols
// for all our matrix math (matrix math done for us yay!) This header (graphics_headers.h) also defines the structure of "what is a vertex" in relation to how our program
// uses them. Additionally some macros defined before header includes to switch on or off certain library capabilities
#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    // (Part 1): This does lots of things, but in an overarching concept kind of way it sets up communication between our cpu and gpu. Explicitly we set up
    // a vertex array object as our contained in which our object data lives, then set up VBOs for our vertices and indices respectively by composing this vao.
    // The process of doing so for each VBO, one for our vertices, one for our indices, goes glGenBuffers (give me a buffer on the gpu) -> glBindBuffer (bind this buffer as vertex attributes) ->
    // glBufferData (Those vertex attributes live here on the cpu and are of this size, grab them from here, the contents will be modified once and used many times (STATIC_DRAW)) -> glVertexAttribPointer (hey gpu, my vertex structure is like this!) and this
    // last step is done for both color and position because we defined our vertex like so in our graphics_header.h :)
    void Initialize(GLint posAttribLoc, GLint colAttribLoc);
    // (Part 1): In this implementation, we can update any of our matrices through this as process a new frame, a triangle only updates its position, while a cube updates its position and its rotation
    virtual void Update();
    virtual void Update(glm::mat4 in);
    // (Part 1): All the steps to actually draw the object. Executed each frame, We bind our previously generated vao again, then we bind our respective vertex and index buffers (VBOs) again,
    // then enable our vertex attribute arrays for our position and color respectively. Initialize() sets up the what, where, and how in the pipeline between the cpu and gpu,
    // while this just "switches it all on" when we need it. After switching on our vao, its vbos, and the array attributes, we can make draw calls(hey gpu, do it like this!). We use
    // triple pairs of vertices here to draw triangles in this implementation, and we use that as a primitive to build both an actual triangle and all 6 sides of a cube! (8 vertex pairs)
    // Once done rendering, we reverse the order of our calls, and disable those vertex attributes, and then effectively unbind our vbos and element buffers.
    virtual void Render(GLint posAttribLoc, GLint colAttribLoc);
    // (Part 1): The method in which the indices and vertices are populated, i.e. part of the inherent attributes of a shape in addition to the pattern of how we draw from those indices. 
    // In this implementation I overload this function to create different vertices and indices depending on if its a triangle or cube.
    virtual void createVertices() = 0;
    // (Part 1): Helper method used to get the model matrix of an object, it's used to populate the uniform value of an object's model matrix, so all gpu programs running can see these values
    // when executing
    glm::mat4 GetModel();
    // (Part 1): Helper method used to set the speed of an object, used in Update() on each new frame.
    void setSpeed(glm::vec3 spd) { m_speed = spd; }
  public:
      // (Part 1): Explicitly decomposed the rotation, translation (position), and scale out of our model matrix, makes it easier to "talk about"
      // these things independently from one another in the implementation.
      glm::mat4 model;

      glm::mat4 rotation;
      glm::mat4 translation;
      glm::mat4 scale;
      glm::vec3 m_speed = glm::vec3(0., 0., 0.);

protected:

    GLuint vao;

    GLuint VB;
    GLuint IB;
    //pa3
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    float angle;
    //pa4
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
};

#endif /* OBJECT_H */
