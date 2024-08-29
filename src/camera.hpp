#pragma once
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>

#include "input.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

class Camera
{
//----------------------------------------------------------------------------
public:
//----------------------------------------------------------------------------
    GLFWwindow* windowHandle = nullptr;

    //----------------------------------------------------------------------------
    // Recalculate view with input handling functions
    glm::mat4 recalculateView(float deltaTime)
    {
        glm::vec2 mousePos = Input::getMousePosition(windowHandle);
        glm::vec2 delta = (mousePos - lastMousePosition) * 0.002f;
        lastMousePosition = mousePos;
        
        forwardDirection = CenterPosition - EyePosition;
        rightVector = glm::cross(forwardDirection, upVector);

        if(windowHandle != nullptr )
        {
            if (!Input::isMouseButtonDown(windowHandle, GLFW_MOUSE_BUTTON_RIGHT))
            {
                glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                
                if (Input::isKeyDown(windowHandle, GLFW_KEY_KP_0))
                    resetToInitialPos();
                if (Input::isKeyDown(windowHandle, GLFW_KEY_KP_1))
                   orbitStartAnimation(ViewType::VT_FRONT);
                if (Input::isKeyDown(windowHandle, GLFW_KEY_KP_3))
                    orbitStartAnimation(ViewType::VT_RIGHT);
                animateResetUpdate();
                return glm::lookAt(EyePosition, CenterPosition, upVector);
            }
            glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + 2);
            
            if (Input::isKeyDownRepeat(windowHandle, GLFW_KEY_E))
                moveUpDirection(deltaTime);
            if (Input::isKeyDownRepeat(windowHandle, GLFW_KEY_Q))
                moveDownDirection(deltaTime);
            if (Input::isKeyDownRepeat(windowHandle, GLFW_KEY_W))
                moveForward(deltaTime);
            if (Input::isKeyDownRepeat(windowHandle, GLFW_KEY_S))
                moveBack(deltaTime);
            if (Input::isKeyDownRepeat(windowHandle, GLFW_KEY_D))
                moveRightDirection(deltaTime);
            if (Input::isKeyDownRepeat(windowHandle, GLFW_KEY_A))
                moveLeftDirection(deltaTime);

            if (delta.x != 0.0f || delta.y != 0.0f)
            {
                float pitchDelta = delta.y * rotationSpeed;
                float yawDelta = delta.x * rotationSpeed;

                glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightVector), glm::angleAxis(-yawDelta, upVector)));
                forwardDirection = glm::rotate(q, forwardDirection);
                CenterPosition = EyePosition + forwardDirection;
                EyePosition = CenterPosition - forwardDirection;
            }
        }
        return glm::lookAt(EyePosition, CenterPosition, upVector);
    }
    
//----------------------------------------------------------------------------
// Projection and Direction functions
//----------------------------------------------------------------------------
    
    //----------------------------------------------------------------------------
    glm::mat4 perspectiveProjection(float aspectRatio)
    {
        return glm::perspective(glm::radians(VerticalFOV), aspectRatio, NearClip, FarClip);
    }

    //----------------------------------------------------------------------------
    glm::mat4 inverseProjection(glm::mat4 perspectiveProjection, glm::mat4 view)
    {
        return glm::inverse(perspectiveProjection * view);
    }

    //----------------------------------------------------------------------------
    glm::vec3 getEyePosition()
    {
        return EyePosition;
    }
    
    //----------------------------------------------------------------------------
    glm::vec3 getCenterPosition()
    {
        return CenterPosition;
    }

    //----------------------------------------------------------------------------
    glm::vec3 getEnvironmentUpVector()
    {
        return upVector;
    }
    
    
//----------------------------------------------------------------------------
private:
//----------------------------------------------------------------------------
    double resetAnimationStart = 0;
    double orbitAnimationStart = 0;
    
    float VerticalFOV = 38.0f;
    float NearClip = 0.1f;
    float FarClip = 1000.0f;
    float speed = 2.0f;
    float rotationSpeed = 0.3f;
    
    glm::vec2 lastMousePosition{ 0.0f, 0.0f };
    
    glm::vec3 CenterPosition{0.0f, 0.0f, 0.0f};
    
    glm::vec3 EyePosition{5.0f, -5.0f, 5.0f};
    glm::vec3 startEye, startCenter, targetEyePosition, targetCenterPosition;
    
    glm::vec3 rightVector{0.0f, 0.0f, 0.0f};
    glm::vec3 upVector{0.0f, 0.0f, 1.0f};
    glm::vec3 forwardDirection{};
    
    glm::mat4 Projection{ 1.0f };
    glm::mat4 View{ 1.0f };
    glm::mat4 InverseProjection{ 1.0f };
    glm::mat4 InverseView{ 1.0f };
    
    //----------------------------------------------------------------------------
    enum class ViewType
    {
        VT_FRONT,
        VT_RIGHT,
        VT_INVERT_RIGHT,
        VT_TOP,
        VT_ISOMETRIC
    };
    glm::vec3 SetViewOrbit(ViewType view)
    {
        glm::vec3 foc = getCenterPosition();
        glm::vec3 pos = getEyePosition();
        glm::vec3 up  = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 axis, newPos;
        float radius = distance(foc, pos);

        switch (view)
        {
        case ViewType::VT_FRONT:
            axis = { 0, +1, 0 };
            break;
        case ViewType::VT_RIGHT:
            axis = { +1, 0, 0 };
            break;
        case ViewType::VT_INVERT_RIGHT:
            axis = { -1, 0, 0 };
            break;
        case ViewType::VT_TOP:
            axis = { 0, 0, +1 };
            up   = { 0, -1, 0 };
            break;
        case ViewType::VT_ISOMETRIC:
            axis = { -1, +1, +1 };
            up = { 0, 0, 1 };
            break;
        }

        newPos[0] = foc[0] + glm::clamp(radius, 0.0f, 100.0f) * axis[0];
        newPos[1] = foc[1] + glm::clamp(radius, 0.0f, 100.0f) * axis[1];
        newPos[2] = foc[2] + glm::clamp(radius, 0.0f, 100.0f) * axis[2];

        upVector = up;
        return newPos;
    }

    //----------------------------------------------------------------------------
    void resetToInitialPos()
    {
        if((float)resetAnimationStart == 0.0f)
        {
            startCenter = getCenterPosition();
            startEye = getEyePosition();
            targetCenterPosition = glm::vec3(0.0f,  0.0f, 0.0f);
            targetEyePosition    = glm::vec3(5.0f, -5.0f, 5.0f);
            resetAnimationStart  = glfwGetTime();
        }
    }
    
    //----------------------------------------------------------------------------
    void orbitStartAnimation(ViewType view)
    {
        if((float)resetAnimationStart == 0.0f)
        {
            startCenter = getCenterPosition();
            targetCenterPosition = startCenter;
            startEye = getEyePosition();
            targetEyePosition = SetViewOrbit(view);
            resetAnimationStart  = glfwGetTime();
        }
    }

    //----------------------------------------------------------------------------
    void animateResetUpdate()
    {
        if (resetAnimationStart > 0)
        {
            const double timeSinceStart = glfwGetTime() - resetAnimationStart;
            const double t = glm::min((float)(timeSinceStart / (rotationSpeed * 0.2)), 1.0f);
                
            CenterPosition = glm::mix(startCenter, targetCenterPosition, t);
            EyePosition = glm::mix(startEye, targetEyePosition, t);

            if (timeSinceStart >= (rotationSpeed * 0.2)) { resetAnimationStart = 0; }
        }
    }
    
    //----------------------------------------------------------------------------
    void moveUpDirection(float deltaTime)
    {
        CenterPosition += upVector * speed * deltaTime;
        EyePosition += upVector * speed * deltaTime;
    }

    //----------------------------------------------------------------------------
    void moveDownDirection(float deltaTime)
    {
        CenterPosition -= upVector * speed * deltaTime;
        EyePosition -= upVector * speed * deltaTime;
    }
    
    //----------------------------------------------------------------------------
    void moveForward(float deltaTime)
    {
        CenterPosition += forwardDirection * speed * deltaTime;
        EyePosition += forwardDirection * speed * deltaTime;
    }

    //----------------------------------------------------------------------------
    void moveBack(float deltaTime)
    {
        CenterPosition -= forwardDirection * speed * deltaTime;
        EyePosition -= forwardDirection * speed * deltaTime;
    }

    //----------------------------------------------------------------------------
    void moveRightDirection(float deltaTime)
    {
        CenterPosition += rightVector * speed * deltaTime;
        EyePosition += rightVector * speed * deltaTime;
    }
    
    //----------------------------------------------------------------------------
    void moveLeftDirection(float deltaTime)
    {
        CenterPosition -= rightVector * speed * deltaTime;
        EyePosition -= rightVector * speed * deltaTime;
    }
};
