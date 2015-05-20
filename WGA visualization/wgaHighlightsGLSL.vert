#version 330

uniform int whichHighlight;
in vec3 vPosition;
uniform camera {
    mat4 modelvMatrix;
    mat4 projMatrix;
    mat4 fixedPanelMatrix;
};
uniform mat4 blobSpec[24];
uniform vec4 lightSpec[24];
out vec4 coloring;

void main() {
    
    coloring =lightSpec[gl_InstanceID];
    gl_Position = projMatrix * modelvMatrix * blobSpec[gl_InstanceID]*vec4(vPosition,1.0);


}