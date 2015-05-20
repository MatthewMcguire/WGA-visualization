#version 330

in vec4 gl_FragCoord;
// whichElement =1 for bins, =2 for histogram line
uniform int whichElement;
out vec4 fragColored;

void main() {
    if (whichElement==1)
        fragColored =  vec4(0.22,0.41,0.55,0.8);
    if (whichElement==2)
        fragColored =  vec4(0.66,0.66,0.66,0.8);
}