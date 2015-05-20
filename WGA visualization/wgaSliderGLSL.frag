#version 330

in vec2 stMapped;
uniform sampler2D sampleSlider;
//uniform int whichSlider;
in vec4 gl_FragCoord;
out vec4 fragColored;

void main() {

    fragColored =  vec4(0.75,0.75,0.75,0.9)*texture(sampleSlider, stMapped);

}