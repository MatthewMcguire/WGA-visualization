#version 330

in vec2 stMap;
in vec4 vPosition;
out vec2 stMapped;
uniform camera {
    mat4 modelvMatrix;
    mat4 projMatrix;
    mat4 fixedPanelMatrix;
};


void main() {

    gl_Position = projMatrix * modelvMatrix * vPosition;
    stMapped = stMap;

//    NB: Code set aside for the lighting model, once added
//    gl_Position = projMatrix * modelvMatrix * sphSpec[gl_InstanceID] * vPosition;
//    vN = mat3(modelvMatrix)*vNormal;
//    if(lightLoc.w == 0.0) {vtL = vec3(lightLoc);}
//    else {vtL= vec3(modelvMatrix*lightLoc-modelvMatrix*vPosition).xyz;}
//    vtC = vec3(modelvMatrix*vPosition).xyz;
}