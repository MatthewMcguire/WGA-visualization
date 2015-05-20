#version 330
// whichElement =1 for bins, =2 for histogram line
uniform int whichElement;
in vec2 vPosition;

void main() {
    if (whichElement==1)
        gl_Position = vec4(vPosition,-0.05,1.0);
    if (whichElement==2)
        gl_Position = vec4(vPosition,-0.06,1.0);

}