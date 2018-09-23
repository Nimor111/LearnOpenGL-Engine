#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.05f;
const float ZOOM = 45.0f;

class Camera {
private:
    // calculates the front vector from the Camera's Euler Angles
    void updateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        front.y = sin(glm::radians(this->pitch));
        front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

        this->front = glm::normalize(front);

        this->right = glm::normalize(glm::cross(this->front, this->worldUp));
        this->up = glm::normalize(glm::cross(this->right, this->front));
    }

public:
    // Camera Attrs
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler angles
    float yaw;
    float pitch;

    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
        : front(glm::vec3(0.0f, 0.0f, -1.0f))
        , yaw(YAW)
        , pitch(PITCH)
        , movementSpeed(SPEED)
        , mouseSensitivity(SENSITIVITY)
        , zoom(ZOOM)
    {
        this->position = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;

        updateCameraVectors();
    }

    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW, float pitch = PITCH)
        : front(glm::vec3(0.0, 0.0f, -1.0f))
        , movementSpeed(SPEED)
        , mouseSensitivity(SENSITIVITY)
        , zoom(ZOOM)
    {
        this->position = glm::vec3(posX, posY, posZ);
        this->worldUp = glm::vec3(upX, upY, upZ);
        this->yaw = yaw;
        this->pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(this->position, this->position + this->front, this->up);
    }

    void processKeyboard(Direction direction, float deltaTime)
    {
        float velocity = this->movementSpeed * deltaTime;
        if (direction == FORWARD) {
            this->position += this->front * velocity;
        }
        if (direction == BACKWARD) {
            this->position -= this->front * velocity;
        }
        if (direction == LEFT) {
            this->position -= this->right * velocity;
        }
        if (direction == RIGHT) {
            this->position += this->right * velocity;
        }
        // user stays at ground level
        this->position.y = 0.0f;
    }

    void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true)
    {
        xOffset *= this->mouseSensitivity;
        yOffset *= this->mouseSensitivity;

        this->yaw += xOffset;
        this->pitch += yOffset;

        if (constrainPitch) {
            if (this->pitch > 89.0f) {
                this->pitch = 89.0f;
            }
            if (this->pitch < -89.0f) {
                this->pitch = -89.0f;
            }
        }

        this->updateCameraVectors();
    }

    void processMouseScroll(float yOffset)
    {
        if (this->zoom >= 1.0f && this->zoom <= 45.0f) {
            this->zoom -= yOffset;
        }
        if (this->zoom <= 1.0f) {
            this->zoom = 1.0f;
        }
        if (this->zoom >= 45.0f) {
            this->zoom = 45.0f;
        }
    }
};

#endif /* CAMERA_H */
