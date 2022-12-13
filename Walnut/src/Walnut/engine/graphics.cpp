#include "graphics.h"

struct TranslationInfo
{
    glm::mat4 source;
    glm::mat4 destination;
};

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

// (Part 1): See aforementioned in header comment
bool Graphics::Initialize(int width, int height)
{

  // For OpenGL 3

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  // Find where vertex attributes are in shader
  m_vertPos = m_shader->GetAttribLocation("v_position");
  m_vertCol = m_shader->GetAttribLocation("v_color");

  m_Plane = new Plane(glm::vec3(.25, .25, .25), false);
  m_Plane->Initialize(m_vertPos, m_vertCol);

  m_Plane->translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0f, 0.0f));
  m_Plane->scale = glm::scale(glm::mat4(1.0f), { 50.0f,1.0f,50.0f });
  m_Plane->rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

  int numSquares = 50;
  float pwidth = 50;
  float packing = .01;
  glm::vec3 scale = glm::vec3(packing, 1.0, 50.);
  for (int i = 0; i < (numSquares+1); i++)
  {
      //vertical
      Plane* checkerV = new Plane(glm::vec3(1.,1.,1.), false);
      checkerV->Initialize(m_vertPos, m_vertCol);
             
      checkerV->translation = glm::translate(glm::mat4(1.0f), glm::vec3( -(pwidth / 2.0) + i, 0.1, 0.0));
      checkerV->scale       = glm::scale(glm::mat4(1.0f), scale);
      checkerV->rotation    = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

      m_Checkers.push_back(checkerV);

      //horizontal
      Plane* checkerH = new Plane(glm::vec3(1., 1., 1.), false);
      checkerH->Initialize(m_vertPos, m_vertCol);

      checkerH->translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.1, -(pwidth / 2.0) + i));
      checkerH->scale = glm::scale(glm::mat4(1.0f), scale);
      checkerH->rotation = glm::rotate(glm::mat4(1.0f), 1.57f, glm::vec3(0.0f, 1.0f, .0f));

      m_Checkers.push_back(checkerH);
  }
  
  m_Player = new Plane(glm::vec3(1.0f, 0.0f, 0.0f), true, 15.0f);
  m_Player->Initialize(m_vertPos, m_vertCol);

  m_Player->translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.15, 0.0));
  m_Player->scale = glm::scale(glm::mat4(1.0f), {1.0f,1.0f,1.0f});
  m_Player->rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

  m_Server = new Plane(glm::vec3(0.0f, 1.0f, 0.0f), true, 15.0f);
  m_Server->Initialize(m_vertPos, m_vertCol);

  m_Server->translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.15, 0.0));
  m_Server->scale = glm::scale(glm::mat4(1.0f), { 1.0f,1.0f,1.0f });
  m_Server->rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

  m_Other = new Plane(glm::vec3(0.0f, 0.0f, 1.0f), true, 15.0f);
  m_Other->Initialize(m_vertPos, m_vertCol);
    
  m_Other->translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.15, 0.0));
  m_Other->scale = glm::scale(glm::mat4(1.0f), { 1.0f,1.0f,1.0f });
  m_Other->rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}
// (Part 1): See aforementioned in header comment
void Graphics::Update(float dt, float rttPlayer, float rttOther)
{
    float toServerHolder = (rttPlayer / 1000.0f) / 2.0f;
    float toOtherHolder = (rttOther / 1000.0f) / 2.0f;
    static float toServer = (rttPlayer / 1000.0f) / 2.0f;
    static float toOther = (rttOther / 1000.0f) / 2.0f;

    static float t = 0.0f;
    toServer -= dt;
    toOther -= dt;
    float interpFactor = 1.0f / toOther;
    t += dt * interpFactor;
    //static std
    static glm::mat4 lastTranslation = m_Player->translation;
    static TranslationInfo OtherInterp{lastTranslation,lastTranslation};

    if (toServer < 0.0f)
    {
        m_Server->translation = lastTranslation;
        lastTranslation = m_Player->translation;
        toServer = toServerHolder;
    }

    if (toOther < 0.0f)
    {

        OtherInterp.source = m_Other->translation;
        OtherInterp.destination = m_Server->translation;
        t = 0.0f;
        toOther = toOtherHolder;
    }

    if (t >= 1.0f) t = 1.0f;
    m_Other->translation = glm::interpolate(OtherInterp.source, OtherInterp.destination, t);

    for (int i = 0; i < m_Checkers.size(); i++)
    {
        Plane* checker = m_Checkers.at(i);
        checker->Update();
    }
    m_Plane->Update();
    m_Player->Update();
    m_Server->Update();
    m_Other->Update();

}
void Graphics::Update2(float dt, NetworkSettings ns)
{
    static float interpTimer = 0.0f;
    static float sendTimer = 0.0f;
    static float latencyTimer = 0.0f;
    static float otherTimer = 0.0f;
    static int tickrateCheck = (int)ns.tickrate;
    static std::deque<glm::mat4> translationQueue{m_Player->translation};
    static std::deque<glm::mat4> translationPropagatedQueue{ m_Player->translation };
    static TranslationInfo OtherInterp{ m_Server->translation, m_Server->translation};
    float packetSendInterval = 1.0f / ns.tickrate;

    if (sendTimer >= packetSendInterval) //send translation
    {
        if(!translationQueue.empty()) translationQueue.pop_front();
        if ((int)ns.tickrate != tickrateCheck)
        {
            translationQueue.clear();
        }
        translationQueue.push_back(m_Player->translation);
        sendTimer = 0.0f;
    }

    if (latencyTimer >= ((ns.rttPlayer / 1000.0f) / 2.0f))
    {
        if (!translationPropagatedQueue.empty()) translationPropagatedQueue.pop_front();
        m_Server->translation = translationQueue.front();
        translationPropagatedQueue.push_back(m_Server->translation);
    }

    if (otherTimer >= ((ns.rttPlayer / 1000.0f) / 2.0f) + (ns.rttOther / 1000.0f) /2.0f)
    {
        OtherInterp.source = m_Other->translation;
        OtherInterp.destination = translationPropagatedQueue.front();
        interpTimer = 0.0f;
    }

    if (interpTimer >= 1.0f) interpTimer = 1.0f;
    m_Other->translation = OtherInterp.destination;//glm::interpolate(OtherInterp.source, OtherInterp.destination, interpTimer);

    sendTimer += dt;
    latencyTimer += dt;
    otherTimer += dt;
    interpTimer += dt * 1.0f / ((ns.rttPlayer / 1000.0f) / 2.0f) + (1.0f / ((ns.rttOther / 1000.0f) / 2.0f));

    for (int i = 0; i < m_Checkers.size(); i++)
    {
        Plane* checker = m_Checkers.at(i);
        checker->Update();
    }
    m_Plane->Update();
    m_Player->Update();
    m_Server->Update();
    m_Other->Update();
}
// (Part 1): See aforementioned in header comment
void Graphics::Render()
{
  //clear the screen
  glClearColor(0.01, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  std::stack<Object*> renderStack;

  renderStack.push(m_Other);
  renderStack.push(m_Server);
  renderStack.push(m_Player);
  renderStack.push(m_Plane);

  for (int i = 0; i < m_Checkers.size(); i++)
  {
      renderStack.push(m_Checkers.at(i));
  }
  while (!renderStack.empty())
  {
      if (renderStack.top() != NULL)
      {
          glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(renderStack.top()->GetModel()));
          renderStack.top()->Render(m_vertPos, m_vertCol);
      }
      renderStack.pop();
  }
  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}


// (Part 1): See aforementioned in header comment
std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}
