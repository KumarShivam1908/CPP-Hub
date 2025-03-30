#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include<iostream>


Camera::Camera(){
    // Assume we are placed at the origin
    mEye = glm::vec3(0.0f, 0.0f, 3.0f);  // Position the camera 3 units away from the object
    //assume we are looking out into the world
    // note This is along -z because otherwise we would be looking at the back of the triangle
    mViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    // assume we start on a perfect plane
    mUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::GetViewMatrix() const{
    // Fix: We need to look at a point in front of us, not directly at the view direction
    return glm::lookAt(mEye, mEye + mViewDirection, mUpVector);
}

void Camera::MouseLook(int mouseX, int  mouseY){
    // Implementation if needed
    std::cout<<"Mouse x = "<<mouseX<<" Mouse y = "<<mouseY<<std::endl;
}

void Camera::MoveForward(float speed) {
    
    // Implementation if needed
    mEye.z -= speed;
}

void Camera::MoveBackward(float speed){
    // Implementation if needed
    mEye.z += speed;
}

void Camera::MoveLeft(float speed){
    // Implementation if needed
}

void Camera::MoveRight(float speed){
    // Implementation if needed
}