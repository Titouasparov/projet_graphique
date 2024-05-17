#include "viewer.h"
#include "triangle.h"
#include "pyramid.h"
#include "cylinder.h"
#include "node.h"
#include "shader.h"
#include <string>

#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    Viewer viewer;

    // get shader directory
    std::string shader_dir = SHADER_DIR;

    Shader *color_shader = new Shader(shader_dir + "node.vert", shader_dir + "node.frag");

    glm::mat4 human_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        
    Node* human = new Node(human_mat);

    // Torso
    Shape* torso = new Cylinder(color_shader);
    glm::mat4 torso_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.8f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* torso_node = new Node(torso_mat);
    torso_node->add(torso);

    // Neck
    Shape* neck = new Cylinder(color_shader);
    glm::mat4 neck_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.3f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* neck_node = new Node(neck_mat);
    neck_node->add(neck);

    // Head
    Shape* head = new Cylinder(color_shader);
    glm::mat4 head_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.4f, 0.4f));
    Node* head_node = new Node(head_mat);
    head_node->add(head);

    // Right Upper Arm
    Shape* right_upper_arm = new Cylinder(color_shader);
    glm::mat4 right_upper_arm_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.8f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.5f, 0.2f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* right_upper_arm_node = new Node(right_upper_arm_mat);
    right_upper_arm_node->add(right_upper_arm);

    // Right Lower Arm
    Shape* right_lower_arm = new Cylinder(color_shader);
    glm::mat4 right_lower_arm_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.3f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.5f, 0.2f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* right_lower_arm_node = new Node(right_lower_arm_mat);
    right_lower_arm_node->add(right_lower_arm);

    // Create the left upper arm
    glm::mat4 left_upper_arm_tra_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.8f, 0.0f));
    glm::mat4 left_upper_arm_rot_mat = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 left_upper_arm_sca_mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.5f, 0.2f));

    Node* left_upper_arm_node = new Node(left_upper_arm_tra_mat * left_upper_arm_rot_mat * left_upper_arm_sca_mat);
    Shape* left_upper_arm = new Cylinder(color_shader);
    left_upper_arm_node->add(left_upper_arm);

    // Create the left lower arm
    glm::mat4 left_lower_arm_tra_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.3f, 0.0f));
    glm::mat4 left_lower_arm_rot_mat = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 left_lower_arm_sca_mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.5f, 0.2f));

    Node* left_lower_arm_node = new Node(left_lower_arm_tra_mat * left_lower_arm_rot_mat * left_lower_arm_sca_mat);
    Shape* left_lower_arm = new Cylinder(color_shader);
    left_lower_arm_node->add(left_lower_arm);

    // Create the right upper leg
    glm::mat4 right_upper_leg_tra_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, -0.8f, 0.0f));
    glm::mat4 right_upper_leg_rot_mat = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 right_upper_leg_sca_mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f));

    Node* right_upper_leg_node = new Node(right_upper_leg_tra_mat * right_upper_leg_rot_mat * right_upper_leg_sca_mat);
    Shape* right_upper_leg = new Cylinder(color_shader);
    right_upper_leg_node->add(right_upper_leg);

    // Create the right lower leg
    glm::mat4 right_lower_leg_tra_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, -1.5f, 0.0f));
    glm::mat4 right_lower_leg_rot_mat = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 right_lower_leg_sca_mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f));

    Node* right_lower_leg_node = new Node(right_lower_leg_tra_mat * right_lower_leg_rot_mat * right_lower_leg_sca_mat);
    Shape* right_lower_leg = new Cylinder(color_shader);
    right_lower_leg_node->add(right_lower_leg);

    // Create the left upper leg
    glm::mat4 left_upper_leg_tra_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.2f, -0.8f, 0.0f));
    glm::mat4 left_upper_leg_rot_mat = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 left_upper_leg_sca_mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f));
    
    Node* left_upper_leg_node = new Node(left_upper_leg_tra_mat * left_upper_leg_rot_mat * left_upper_leg_sca_mat);
    Shape* left_upper_leg = new Cylinder(color_shader);
    left_upper_leg_node->add(left_upper_leg);

    // Create the left lower leg
    glm::mat4 left_lower_leg_tra_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.2f, -1.5f, 0.0f));
    glm::mat4 left_lower_leg_rot_mat = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 left_lower_leg_sca_mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f));

    Node* left_lower_leg_node = new Node(left_lower_leg_tra_mat * left_lower_leg_rot_mat * left_lower_leg_sca_mat);
    Shape* left_lower_leg = new Cylinder(color_shader);
    left_lower_leg_node->add(left_lower_leg);

    // Add the root node to the scene
    human->add(torso_node);
    human->add(neck_node);
    human->add(head_node);
    human->add(right_upper_arm_node);
    human->add(right_lower_arm_node);
    human->add(left_upper_arm_node);
    human->add(left_lower_arm_node);
    human->add(left_lower_leg_node);
    human->add(left_upper_leg_node);
    human->add(right_lower_leg_node);
    human->add(right_upper_leg_node);

    viewer.scene_root->add(human);

    viewer.run();
}