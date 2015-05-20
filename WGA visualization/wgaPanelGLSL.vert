#version 330

in vec2 stMap;
in vec2 vPosition;
out vec2 stMapped;

void main() {
    stMapped= stMap;
    gl_Position = vec4(vPosition,0.0,1.0);

}