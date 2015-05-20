#version 330

in vec4 gl_FragCoord;
in vec2 stMapped;
uniform sampler2D samplePanel;
out vec4 fragColored;

void main() {

    fragColored =  texture(samplePanel, stMapped);
}