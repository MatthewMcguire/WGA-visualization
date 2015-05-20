#version 330

in vec2 stMapSlider;
in vec2 vPosition;
// whichSlider = 1 when drawing left slider, 2 when drawing right slider
uniform int whichSlider;
// sliderOffsetsHorizontal[0] for left x-axis offset, [1] for right
uniform vec2 sliderOffsetsHorizontal;
out vec2 stMapped;

void main() {
    vec4 offset = vec4(0.0);
    if(whichSlider == 1) offset = vec4(sliderOffsetsHorizontal[0],0.0,0.0,0.0);
    if(whichSlider == 2) offset = vec4(sliderOffsetsHorizontal[1],0.0,0.0,0.0);
    gl_Position = vec4(vPosition,-0.1,1.0)+offset;
    stMapped= stMapSlider;
    
}