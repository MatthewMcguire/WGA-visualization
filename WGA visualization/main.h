//
//  main.h
//  WGA visualization
//
//  Created by Matthew McGuire on 4/24/15.
//  Copyright (c) 2015 Matthew McGuire. All rights reserved.
//

#include <cstring>
#include <vector>
#include <cmath>
#include "lib3D.h"
#include "BetterSphere.h"
#include "vis_helpers.h"
#include <AntTweakBar.h>

/* Load and parse the artworks metadata */
std::string sourceDir ="/Users/matthew/Dropbox/_interactive/expierments/";
std::string sourceFile = sourceDir + "wgaCatalog3-2015.txt";
WorkList works(sourceFile);

struct hightlightOnce
{
    std::string name;
    int drawingIndex;
};
class Highlights
{
private:
    std::vector<hightlightOnce> artworksMap;
    void updateHighlistOnce(int, std::string);
    std::map<float, glm::vec3> colorRange;
public:
    Highlights(int);
    void updateHighlistNames(std::vector<std::string>);
    void updateHighlightColors(std::vector<float>);
    void printColorSpec(void);
    void draw(void);
    int numIndices;
    int numVertices;
    std::vector<point3> vertices;
    std::vector<unsigned int> indices;
    std::vector<vec4> colorSpec;
};

// Constructor: creates a vector of empty highlightOnce objects
Highlights::Highlights(int n)
{
    // create a vector of n hightlightOnce objects
    for(int i = 0; i < n; ++i)
    {
        hightlightOnce temphighlightOnce;
        temphighlightOnce.name = "";
        temphighlightOnce.drawingIndex = i;
        artworksMap.push_back(temphighlightOnce);
    }
    
    // create a shape of vertices and indices in clip coordinates
    vertices.push_back(vec3(0.0,0.0,0.0));  // centered at the center!
    indices.push_back(0);
    int numPointsOnCircle = 500;            // a fair number for a smooth curve
    float xVal, yVal;
    for (int i = 0; i< numPointsOnCircle; ++i)      // verts for a parametric circle
    {
        float scaly = 0.02;
        xVal = scaly*cosf((2.0*M_PI/numPointsOnCircle)*float(i));
        yVal = scaly*sinf((2.0*M_PI/numPointsOnCircle)*float(i));
        
        vertices.push_back(vec3(xVal,yVal,0.0));
        indices.push_back(i+1);
    }
    indices.push_back(1);                   // to close the triangle fan
    numVertices = int(vertices.size());
    numIndices = int(indices.size());
    colorRange.insert(std::pair<float, glm::vec3>(0.05,glm::vec3(1.0,.961,.941)));
    colorRange.insert(std::pair<float, glm::vec3>(0.10,glm::vec3(.996,.878,.823)));
    colorRange.insert(std::pair<float, glm::vec3>(0.15,glm::vec3(.988,.733,.631)));
    colorRange.insert(std::pair<float, glm::vec3>(0.20,glm::vec3(.988,.573,.447)));
    colorRange.insert(std::pair<float, glm::vec3>(0.25,glm::vec3(.984,.416,.290)));
    colorRange.insert(std::pair<float, glm::vec3>(0.30,glm::vec3(.937,.231,.173)));
    colorRange.insert(std::pair<float, glm::vec3>(0.35,glm::vec3(.796,.094,.114)));
    colorRange.insert(std::pair<float, glm::vec3>(0.40,glm::vec3(.647,.059,.082)));
    colorRange.insert(std::pair<float, glm::vec3>(0.45,glm::vec3(.404,.0,.051)));
    
}
// method to add a name to a Highlight instance
void Highlights::updateHighlistOnce(int d, std::string n)
{
    std::vector<hightlightOnce>::iterator itr;
    for(itr = artworksMap.begin(); itr < artworksMap.end(); ++itr)
        if ((*itr).drawingIndex == d)
            (*itr).name = n;
}
// method to pass list of country names to populate the Highlights instances
void Highlights::updateHighlistNames(std::vector<std::string> nameList)
{
    size_t names = nameList.size();
    for(int i = 0; i < names; ++i)
    {
        updateHighlistOnce(i, nameList[i]);
    }
}
void Highlights::draw(void)
{
    glEnable(GL_BLEND);
        glDrawElementsInstanced
        (
         GL_TRIANGLE_FAN,
         numIndices,
         GL_UNSIGNED_INT,
         (void*)(0),
         24
         );
    glDisable(GL_BLEND);
}

void Highlights::updateHighlightColors(std::vector<float> w)
{
    std::vector<float> stats = w;
    colorSpec.clear();
    float transparency = .75;
    glm::vec4 highlight = vec4(1,1,1,transparency); // this should never get used, but good to be safe
    for(int i = 0; i< 24; ++i)
    {   // this brief loop imposes the darkest possible color of the color range on the country
        std::map<float, glm::vec3>::iterator iter = colorRange.begin();
        while(iter++->first < stats[i])
            highlight =vec4(iter->second,transparency);
        colorSpec.push_back(highlight);
    }

}

void Highlights::printColorSpec(void)
{
    for(int i = 0; i<24; ++i) std::cout << i << " " << colorSpec[i][0] << "," << colorSpec[i][1]
        <<"," << colorSpec[i][2] << "," <<colorSpec[i][3] << std::endl;
}

class Timeline
{
private:
    vec2 center;
    float left,right;
    float top, bottom;
    float sliderWidthPortion,sliderHeightPortion;
    float timelinePortion;   // what portion of the width is filled with the timeline
    vec4 bBoxLeftSlider;
    vec4 bBoxRightSlider;
    float chamfDivisorV,chamfDivisorH;
    float chamferV,chamferH;
    float SliderVertPos;
    float sliderHeight,sliderWidth;
    float teardropIncrements;
    vec2 teardrop(int, float,float);
    float histoLeft,histoRight;
    float histoTop,histoBottom;
    std::vector<float> histogram;
    void generatePanelVertices(void);
    void generatePanelIndices(void);
    void generateHistogramVerticesAndIndices(void);

public:
    Timeline(vec2, float, float, std::vector<float>);
    std::vector<vec2> bgVertices;
    std::vector<unsigned int> bgIndices;
    std::vector<vec2> sliderVertices;
    std::vector<unsigned int> sliderIndices;
    std::vector<vec2> stMap;
    std::vector<vec2> stMapSlider;
    std::vector<vec2> histoVertices;
    std::vector<unsigned int> histoIndices;
    int numBgVertices;
    int numBgIndices;
    int numSliderVertices;
    int numSliderIndices;
    size_t numHistoBins;
    int numHistoVertices;
    int numHistoIndices;
    void printBoundingBoxes(void);
    bool hidden;
    bool hovered(vec2);
    float lSliderPos, rSliderPos;
    float leftLastPreviousLoc=0.0, rightLastPreviousLoc=0.0;
    int lowestSliderYear, highestSliderYear;
    void Draw(int);
    int clickedOnSlider(void);
    void moveSlider(int, float);
    void updateHistogram(std::vector<float>);
    void showHide();
    void bBoxUpdate(void);
    void updateYearMarks(void);
};




using namespace myOpenGl3D;     // remove this sometime

/*======================================================*/
/* construct the basic visual objects with global scope */

// Sphere with three parameters: #fan lines, # band lines, radius
BetterSphere basicSphere(100,100,1.0);

// Timeline panel with three parameters: center, width, and height (in clip coords)
Timeline mainPanel(point2(0.0,-0.8), 1.2f, 0.4f, works.getDecadeHisto());

Highlights countryContrib(24);

/*======================================================*/

// overall settings for the shaders
const int numVAO = 5;
const int numBuffers = 14;
const int numUBuffs = 4;
GLuint program[5];
GLuint shaderBuffer[numBuffers];
GLuint uBlockBinding​[numUBuffs];
GLuint attribLocation[8];
GLuint VertexArrayID[numVAO];
GLint uniformLocation[9];
GLuint textureName[2];
const int numberCountries = 24;

// general GLFW setup settings
GLuint mainWinWidth = 850;
GLuint mainWinHeight = 850;
GLfloat halfWinWidth = mainWinWidth/2.0;
GLfloat halfWinHeight = mainWinHeight/2.0;
char windowName[50];
GLuint shaderProg;
GLFWwindow* mainWin;
float bgClearColor[] = { 0.14f,0.14f,0.145f}; // Background color
float pointy[] = {-.5,1.0,-1.0};
vec3 startv = vec3(pointy[0],pointy[1],pointy[2]);
GLdouble fps[2], nowFPS;
GLuint fpsCounter = 0;;

// simple toggle between points, outlines, and filled polygons
int vertexIter;
enum PollyModes {LINE, SURFACE, POINT};
PollyModes polygonModeToggle = LINE;
GLint showControls = 1;

// for the camera functions, the model view and projection matrices
// the camera begins at (0,0,1), looking at the origin
matr4 modelvMatrix;
matr4 projMatrix;
matr4 fixedPanelMatrix;
matr4 *blobSpec = new matr4[24];
vec4 *lightSpec = new vec4[24];
// For spherical coordinates camera spec
GLfloat camEyeθ = M_PI;
GLfloat camEyeφ = (M_PI/2.5);
GLfloat camEyeR = 4.0f;
point3 camEye = euclidCamera(camEyeR,camEyeθ,camEyeφ);
point3 camRight = {cos(camEyeθ),0,-sin(camEyeθ)};
point3 camAt = point3(0.0f,0.0f,0.0f);
point3 camUp = point3(0.0f,1.0f,0.0f);

GLfloat prLeft = -4.0f;
GLfloat prRight = 4.0f;
GLfloat prBottom = -4.0f;
GLfloat prTop = 4.0f;
GLfloat prFar = -4.0f;
GLfloat prNear = 4.0f;
GLfloat accelFactor = 0.2f;
GLfloat zoomFactor = 0.15f;
GLfloat frFOV =20.0;
GLfloat frAspect = 1.0f;
GLfloat frNear = 0.1f;
GLfloat frFar = 6000.0f;


// locate and connect the uniform block that carries the camera matrices
// these are made global in scope so the initialization and updae functions
// can share the uniform black connection.

GLuint uBlockIndex[numUBuffs];
GLint uBlockSize[numUBuffs];

/*-- (begin) variables for Camera Uniform block ---*/
GLubyte * uBufferC;
enum {ModelvMatrix,ProjMatrix,FixedPanelMatrix,numCameraBlockVars};
GLubyte * modelMatrixAddr;
GLubyte * projMatrixAddr;
GLubyte * fixedPanelMatrixAddr;
/*-- (end) variables for Camera Uniform block ---*/

// provide space for ALL uniform blocks
size_t uVarMemorySize[numCameraBlockVars];
enum mouseNav { NoClick = 0, RightClick=1, LeftClickRelease=-100, LeftSliderMoving=-1, RightSliderMoving=-2, LeftClickPress=-50};
vec2 currentCursor;
vec2 initLClickPos(0.0,0.0);  // records the position of the cursor at begin of Dragging
vec2 lClickDragVector(0.0,0.0); // records the displacement of cursor during Dragging
GLint mouseNav = NoClick;
GLfloat rShift;     // metric of the amount of scrolling done on the mouse
GLboolean donePausing = GL_TRUE;
GLdouble lastPauseEnd;
GLdouble pauseLength = 0.02; // (pauseLength)^-1 = 100 hz update rate for mouse-driven events
vec2 sliderOffset = vec2(0.0,0.0);  // store displacement of sliders L and R
TwBar *myBar, *myOtherBar;

// Quit callback function: when window closed or program terminated
void quitApp(GLFWwindow *mainWin)
{
    glfwDestroyWindow(mainWin);
    TwTerminate();
    glfwTerminate();
    exit(0);
}
void togglePolyMode(void)
{
    switch(polygonModeToggle) {
        case LINE:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            polygonModeToggle = SURFACE;
            break;
        case SURFACE:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            polygonModeToggle = POINT;
            break;
        case POINT:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            polygonModeToggle = LINE;
            break;
    }
}
// keyboard input callback function
void asciiTyping(GLFWwindow* mainWin, unsigned int key)
{
    switch (key) {
        case 'Q':
        case 'q':
            quitApp(mainWin);
            break;
        case '+':
        case '=':
            prLeft *= (1.0- zoomFactor);
            prRight *= (1.0- zoomFactor);
            prTop *= (1.0- zoomFactor);
            prBottom *= (1.0- zoomFactor);
            prNear *= (1.0- zoomFactor);
            prFar *= (1.0- zoomFactor);
            break;
        case '_':
        case '-':
            prLeft *= (1.0+ zoomFactor);
            prRight *= (1.0+ zoomFactor);
            prTop *= (1.0+ zoomFactor);
            prBottom *= (1.0+ zoomFactor);
            prNear *= (1.0+ zoomFactor);
            prFar *= (1.0+ zoomFactor);
            break;
        case 'w':
            prLeft -= zoomFactor;
            prRight += zoomFactor;
            frFOV -=(zoomFactor*5.0);
            break;
        case 'e':
            prLeft += zoomFactor;
            prRight -= zoomFactor;
            frFOV += (zoomFactor*5.0);
            break;
        case 's':
            prTop -= zoomFactor;
            prBottom += zoomFactor;
            frNear -= zoomFactor;
            break;
        case 'd':
            prTop += zoomFactor;
            prBottom -= zoomFactor;
            frNear += zoomFactor;
            break;
        case 'x':
            prNear +=zoomFactor;
            prFar -= zoomFactor;
            frFar -=(zoomFactor*5.0);
            break;
        case 'c':
            prNear -= zoomFactor;
            prFar += zoomFactor;
            frFar +=(zoomFactor*5.0);
            break;
        case 'm':
            togglePolyMode();
            break;
        case 'r':
            std::cout<< "modelvMatrix:" << std::endl;
            std::cout << modelvMatrix[0][0] << " "<< modelvMatrix[1][0] << " "<< modelvMatrix[2][0] << " "<< modelvMatrix[3][0] << std::endl;
            std::cout << modelvMatrix[0][1] << " "<< modelvMatrix[1][1] << " "<< modelvMatrix[2][1] << " "<< modelvMatrix[3][1] << std::endl;
            std::cout << modelvMatrix[0][2] << " "<< modelvMatrix[1][2] << " "<< modelvMatrix[2][2] << " "<< modelvMatrix[3][2] << std::endl;
            std::cout << modelvMatrix[0][3] << " "<< modelvMatrix[1][3] << " "<< modelvMatrix[2][3] << " "<< modelvMatrix[3][3] << std::endl;
            works.printSummary();
            countryContrib.printColorSpec();
        default:
            break;
    }
    //TwEventCharModsGLFW3(mainWin, key, 0);
    TwEventCharGLFW(key,0);
}
// keyboard special key callback function
void specialKeyTyping(GLFWwindow* mainWin, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE) { // only take action when the key is released
        return;
    }
    switch (key) {
        case GLFW_KEY_ESCAPE:
            quitApp(mainWin);
            break;
        case GLFW_KEY_UP:
            break;
        case GLFW_KEY_DOWN:
            break;
        case GLFW_KEY_LEFT:
            break;
        case GLFW_KEY_RIGHT:
            break;
        case GLFW_KEY_SPACE:
            TwGetParam(myBar, NULL, "visible", TW_PARAM_INT32, 1, &showControls);
            if (showControls ==0) showControls = 1;
            else showControls = 0;
            TwSetParam(myBar, NULL, "visible", TW_PARAM_INT32, 1, &showControls);
        default:
            break;
    }
    //    TwEventKeyGLFW3(mainWin, key, scancode, action, mods);
    TwEventKeyGLFW(key, action);
}
void windowReshape(GLFWwindow* window, int width, int height)
{
    mainWinWidth = width;
    mainWinHeight = height;
    halfWinHeight = mainWinWidth/2.0;
    halfWinHeight = mainWinHeight/2.0;
}
void screenCursor(GLFWwindow* mainWin, double xpos, double ypos)
{
    currentCursor[0] = xpos;
    currentCursor[1] = ypos;
    TwEventMousePosGLFW(xpos, ypos);
}
void mouseFunc(GLFWwindow* window, int button, int action, int mods)
{
    // key: mouseNav = 0 if no mouse button is pressed (and hence no animation)
    //      mouseNav = 1 if right click is held, and camera spins
    //      mouseNav = -1 if left click has engaged slider left
    //      mouseNav = -2 if left click has engaged slider right
    //      mouseNav = -100 for end of dragging, to signal update of histo and map
    //      mouseNav = -50 for event of left click and signal to test for bbox

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        mouseNav = 1;
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        if (mouseNav == -1 || mouseNav == -2)   // if dragging = true
            mouseNav = -100; //set dragging = histo and map update
        else
            mouseNav = 0;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        mouseNav = -50;     // signal to check for bbox and possible dragging
    if (button != GLFW_MOUSE_BUTTON_LEFT && button != GLFW_MOUSE_BUTTON_RIGHT)
        mouseNav = 0;
    //    TwEventMouseButtonGLFW3(window, button,action,mods);
    TwEventMouseButtonGLFW( button,action);
}
void scrollFunc(GLFWwindow* mainWin, double xOffset, double yOffset)
{
    rShift = sqrt(fabs(yOffset)) * sgn(yOffset) * accelFactor;
    camEyeR *= (1.0+rShift);
    //    TwEventScrollGLFW3(mainWin, xOffset, yOffset);
    TwEventMouseWheelGLFW(yOffset);
}
void moveCamera(void)
{
    // get current mouse cursor
    // normalize to [-1,1]
    GLfloat displacedHorizontal = (currentCursor[0]-halfWinWidth)/halfWinWidth;
    GLfloat displacedVertical = (currentCursor[1]-halfWinHeight)/halfWinHeight;
    
    // compute acceleration
    // modify polar angles
    camEyeθ += fabs(accelFactor*pow(displacedHorizontal,2.0))* sgn(displacedHorizontal);
    camEyeφ += fabs(accelFactor*pow(displacedVertical,2.0))* sgn(displacedVertical);
    camEyeθ = smallPiBound(camEyeθ);
    camEyeφ = smallPiBound(camEyeφ);
    camRight = {cos(camEyeθ),0,-sin(camEyeθ)};
    camUp = glm::cross(camEye,camRight);
}


Timeline::Timeline(vec2 centerPt, float width, float height, std::vector<float> initialDecadeHisto)
{
    // set various parameters
    hidden = false;
    center = centerPt;
    left = center.x-width/2.0;
    right = center.x + width/2.0;
    top = center.y + height/2.0;
    bottom = center.y - height/2.0;
    timelinePortion = 0.7;
    sliderWidthPortion = 0.05;
    sliderHeightPortion = 0.4;
    chamfDivisorV=15.0,chamfDivisorH=45.0;
    chamferV = height/chamfDivisorV;
    chamferH = width/chamfDivisorH;
    SliderVertPos = bottom+4/chamfDivisorV;
    sliderHeight = sliderHeightPortion*(top-bottom);
    sliderWidth = sliderWidthPortion*(right-left);
    histoLeft=left+1.8*sliderWidth;
    histoRight=right-1.8*sliderWidth;
    lSliderPos = histoLeft;
    rSliderPos = histoRight;
    histoTop = top-sliderHeight/3.0;
    histoBottom = bottom + sliderHeight;
    histogram = initialDecadeHisto;     // initialize histogram with parameter
    numHistoBins = histogram.size();
    lowestSliderYear = 950;
    highestSliderYear = 1900;
    
    // construct initial vertices for the panel, sliders, and default histogram
    generatePanelVertices();
    generatePanelIndices();
    generateHistogramVerticesAndIndices();
    
    // set the initial bounding boxes for the sliders
    float bBox_x1 = lSliderPos+sliderOffset[0]-(sliderWidth/2.0);
    float bBox_y1 = SliderVertPos+(sliderHeight/2.0);
    float bBox_x2 = lSliderPos+sliderOffset[0]+(sliderWidth/2.0);
    float bBox_y2 = SliderVertPos-(sliderHeight/2.0);
    bBoxLeftSlider = vec4(bBox_x1,bBox_y1,bBox_x2,bBox_y2);
    bBox_x1 =rSliderPos+sliderOffset[1]-(sliderWidth/2.0);
    bBox_x2 = rSliderPos+sliderOffset[1]+(sliderWidth/2.0);
    bBoxRightSlider = vec4(bBox_x1,bBox_y1,bBox_x2,bBox_y2);
    
}
bool Timeline::hovered(vec2 mouseCurrent)
{
    float displacedHorizontal = (mouseCurrent[0]-halfWinWidth)/halfWinWidth;
    float displacedVertical = (halfWinHeight-mouseCurrent[1])/halfWinHeight;
    if(displacedHorizontal<-.75 || displacedHorizontal > .75) return false;
    if(displacedVertical > -.5) return false;
    return true;
}
int Timeline::clickedOnSlider(void)
{
    // if current mouse position is in a slider bbox,
    // return -1 (left) or -2 (right) otherwise, return 0
    float xP = (currentCursor[0]-halfWinWidth)/halfWinWidth;
    float yP = (halfWinHeight-currentCursor[1])/halfWinHeight;
    
    if (yP > bBoxLeftSlider[1] || yP < bBoxLeftSlider[3]) return 0;
    if (xP > bBoxLeftSlider[0] && xP < bBoxLeftSlider[2]) return -1;
    if (xP > bBoxRightSlider[0] && xP < bBoxRightSlider[2]) return -2;
    return 0;
}
vec2 Timeline::teardrop(int m, float t, float scale)
{
    return vec2(sin(t)*pow(sin(t/2.0),m)*scale, cos(t)*scale);
}
void Timeline::generatePanelVertices(void)
{
    numBgVertices = 9;
    numBgIndices = 10;
    // calculate vertices
    // for background:
    bgVertices.push_back(center);
    bgVertices.push_back(point2(left+chamferH,bottom));
    bgVertices.push_back(point2(right-chamferH,bottom));
    bgVertices.push_back(point2(right,bottom+chamferV));
    bgVertices.push_back(point2(right,top-chamferV));
    bgVertices.push_back(point2(right-chamferH,top));
    bgVertices.push_back(point2(left+chamferH,top));
    bgVertices.push_back(point2(left,top-chamferV));
    bgVertices.push_back(point2(left,bottom+chamferV));

    stMap.push_back(vec2(0.5,0.829));
    stMap.push_back(vec2((0.002+1/chamfDivisorH),0.6582));
    stMap.push_back(vec2(0.998-1/chamfDivisorH,0.6582));
    stMap.push_back(vec2(0.998,0.6582+.3418/chamfDivisorV));
    stMap.push_back(vec2(0.998,1.0-.3418/chamfDivisorV));
    stMap.push_back(vec2(0.998-1/chamfDivisorH,1.0));
    stMap.push_back(vec2(0.002+1/chamfDivisorH,1.0));
    stMap.push_back(vec2(0.002,1.0-.3418/chamfDivisorV));
    stMap.push_back(vec2(0.002,0.6582+.3418/chamfDivisorV));


    // form a slider shape in the manner of a teasdrop, drawn parametrically
    teardropIncrements = 30;
    int mTeardrop = 1;
    vec2 v;
    stMapSlider.clear();
    float sliderW = .12, sliderH = .12*1.89;      // in clip coords
    
    // left slider
    sliderVertices.push_back(vec2(lSliderPos,SliderVertPos));
    sliderVertices.push_back(vec2(lSliderPos-sliderW/2.0,SliderVertPos-sliderH/2.0));
    sliderVertices.push_back(vec2(lSliderPos+sliderW/2.0,SliderVertPos-sliderH/2.0));
    sliderVertices.push_back(vec2(lSliderPos+sliderW/2.0,SliderVertPos+sliderH/2.0));
    sliderVertices.push_back(vec2(lSliderPos-sliderW/2.0,SliderVertPos+sliderH/2.0));
    
    // right slider
    sliderVertices.push_back(vec2(rSliderPos,SliderVertPos));
    sliderVertices.push_back(vec2(rSliderPos-sliderW/2.0,SliderVertPos-sliderH/2.0));
    sliderVertices.push_back(vec2(rSliderPos+sliderW/2.0,SliderVertPos-sliderH/2.0));
    sliderVertices.push_back(vec2(rSliderPos+sliderW/2.0,SliderVertPos+sliderH/2.0));
    sliderVertices.push_back(vec2(rSliderPos-sliderW/2.0,SliderVertPos+sliderH/2.0));
    
    float vFact = .61/sliderH, wFact = .318/sliderW;
    float lTexturePos = .16, rTexturePos = .84, TextureVertPos = .3;
    stMapSlider.push_back(vec2(lTexturePos,TextureVertPos));
    stMapSlider.push_back(vec2(lTexturePos-(sliderW/2.0)*wFact,TextureVertPos-(sliderH/2.0)*vFact));
    stMapSlider.push_back(vec2(lTexturePos+(sliderW/2.0)*wFact,TextureVertPos-(sliderH/2.0)*vFact));
    stMapSlider.push_back(vec2(lTexturePos+(sliderW/2.0)*wFact,TextureVertPos+(sliderH/2.0)*vFact));
    stMapSlider.push_back(vec2(lTexturePos-(sliderW/2.0)*wFact,TextureVertPos+(sliderH/2.0)*vFact));
    
    stMapSlider.push_back(vec2(rTexturePos,TextureVertPos));
    stMapSlider.push_back(vec2(rTexturePos-(sliderW/2.0)*wFact,TextureVertPos-(sliderH/2.0)*vFact));
    stMapSlider.push_back(vec2(rTexturePos+(sliderW/2.0)*wFact,TextureVertPos-(sliderH/2.0)*vFact));
    stMapSlider.push_back(vec2(rTexturePos+(sliderW/2.0)*wFact,TextureVertPos+(sliderH/2.0)*vFact));
    stMapSlider.push_back(vec2(rTexturePos-(sliderW/2.0)*wFact,TextureVertPos+(sliderH/2.0)*vFact));
    
//    for (int q = 0; q< (teardropIncrements-1); ++q)
//    {
//        v = vec2(lSliderPos,SliderVertPos)+teardrop(mTeardrop, q*M_PI*2.0/teardropIncrements, 0.06);
//        sliderVertices.push_back(v);
//        stMapSlider.push_back(v-vec2(lSliderPos,SliderVertPos)+vec2(.16,.3));
//    }
//    for (int q = 0; q< (teardropIncrements-1); ++q)
//    {
//        v = vec2(rSliderPos,SliderVertPos)+teardrop(mTeardrop, q*M_PI*2.0/teardropIncrements,0.06);
//        sliderVertices.push_back(v);
//        stMapSlider.push_back(v-vec2(rSliderPos,SliderVertPos)+vec2(.84,.3));
//    }
    numSliderVertices = int(sliderVertices.size());

}
void Timeline::generatePanelIndices(void)
{
    
    unsigned int myVInd[] = {0,1,2,3,4,5,6,7,8,1};
    bgIndices.insert(bgIndices.begin(), myVInd,myVInd+numBgIndices);

    unsigned int mySInd[] = {0,1,2,3,4,1,5,6,7,8,9,6};
    sliderIndices.insert(sliderIndices.begin(), mySInd, mySInd+12);
    
//    for (int q = 0; q < (2*teardropIncrements-2); ++q) sliderIndices.push_back(q);
    numSliderIndices = int(sliderIndices.size());
}
void Timeline::printBoundingBoxes(void)
{
    std::cout << "Left BBox: (" << bBoxLeftSlider[0] << "," << bBoxLeftSlider[1];
    std::cout << ") ("<< bBoxLeftSlider[2] << "," << bBoxLeftSlider[3] << ")";
    std::cout << "  Right BBox: (" << bBoxRightSlider[0] << "," << bBoxRightSlider[1];
    std::cout << ") ("<< bBoxRightSlider[2] << "," << bBoxRightSlider[3] << ")" << std::endl;
}
void Timeline::Draw(int whichObject)
{
    // only draw if not hidden
    if (hidden==true) return;
    
    switch (whichObject)
    {
        case 0:     // draw background
            for (int j = 0; j < 1; ++j) {
                glDrawElements
                (
                GL_TRIANGLE_FAN,
                numBgIndices,
                GL_UNSIGNED_INT,
                (void*)(j* 8 * sizeof(GLuint))
                 );
            }
            break;
        case 1:     // draw left and right sliders
            glEnable(GL_BLEND);
            for (int j = 0; j < 2; ++j) {
                glUniform1i(uniformLocation[3], (j+1));
                glDrawElements
                (
                GL_TRIANGLE_FAN,
                (numSliderIndices/2),
                GL_UNSIGNED_INT,
                (void*)(j* (numSliderIndices/2) * sizeof(GLuint))
                );
            }
            glDisable(GL_BLEND);
            break;
        case 2:     // draw histogram
            /*==-- First, draw the bins             --==*/
            glEnable(GL_BLEND);
            // whichElement =1 for bins, =2 for histogram line
             glUniform1i(uniformLocation[5],1);
            for (int j = 0; j < (numHistoBins); ++j) {
                glDrawElements
                (
                 GL_TRIANGLE_FAN,
                 4,
                 GL_UNSIGNED_INT,
                 (void*)(j* 4 * sizeof(GLuint))
                 );
            }
            /*==-- Second, draw the top accentLine  --==*/
            glUniform1i(uniformLocation[5],2);
                glDrawElements
                (
                 GL_LINE_STRIP,
                 int(numHistoBins),
                 GL_UNSIGNED_INT,
                 (void*)(numHistoBins* 4 * sizeof(GLuint))
                 );
             glDisable(GL_BLEND);
            break;
        default:
            break;
    }
}
void Timeline::bBoxUpdate(void)
{
    bBoxLeftSlider[0] = (lSliderPos+sliderOffset[0])-(sliderWidth/2.0);
    bBoxLeftSlider[2] = (lSliderPos+sliderOffset[0])+(sliderWidth/2.0);
    bBoxRightSlider[0] =(rSliderPos+sliderOffset[1])-(sliderWidth/2.0);
    bBoxRightSlider[2] = (rSliderPos+sliderOffset[1])+(sliderWidth/2.0);

}
void Timeline::moveSlider(int slider, float displace)
{
    displace = displace/halfWinWidth;  // convert pixel distance to clip coords
    if(slider == -1)    // left slider movement
    {
        // move the left slider and adjust the bounding box
        sliderOffset[0] = displace+leftLastPreviousLoc;
        // keep the left slider on the timeline, but to the left of the other slider
        if (sliderOffset[0] + lSliderPos < histoLeft)
            sliderOffset[0] = histoLeft - lSliderPos;
        if (sliderOffset[0]+ lSliderPos > sliderOffset[1] + rSliderPos-1.3*sliderWidth)
            sliderOffset[0] = sliderOffset[1] + rSliderPos-1.3*sliderWidth - lSliderPos;
    }
    if(slider == -2)     // right slider movement
    {
        // move the right slider and adjust the bounding box
        sliderOffset[1] =displace+rightLastPreviousLoc;
        // keep the right slider on the timeline, but to the right of the other slider
        if (sliderOffset[1] + rSliderPos > histoRight)
            sliderOffset[1] = histoRight-rSliderPos;
        if (sliderOffset[1]+ rSliderPos < sliderOffset[0] + lSliderPos+1.3*sliderWidth)
            sliderOffset[1] = sliderOffset[0] + lSliderPos+1.3*sliderWidth - rSliderPos;
    }
    // write the current offset values to the GPU for drawing
    glUseProgram(program[2]);
    glUniform2f(uniformLocation[4], sliderOffset[0],sliderOffset[1]);
    bBoxUpdate();

}
void Timeline::updateHistogram(std::vector<float> newHistogram)
{
    // update data in this object
    histogram = newHistogram;
    numHistoBins = histogram.size();
    
    // calculate new histogram vertices and indices
    generateHistogramVerticesAndIndices();
    
    // redraw histogram vertices in GPU
    glUseProgram(program[3]);
    glBindVertexArray(VertexArrayID[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[9]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(histoIndices[0])*numHistoIndices,&histoIndices.front(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(histoVertices[0])*numHistoVertices,&histoVertices.front(),GL_STATIC_DRAW);
    glBindVertexArray(0);

}
void Timeline::generateHistogramVerticesAndIndices(void)
{
    /*==-- (BEGIN) Generate initial vertices and indices for histogram  --==*/
    /*==-- the histogram data consists of a vector of float values      --==*/
    /*==-- in the range [0,1]. They are provided from the DataSource    --==*/
    /*==-- class. Each vector value represents the proportion of works  --==*/
    /*==-- (adjust for current filters) that are from a particular      --==*/
    /*==-- decade. The vertices will be plotted on the timeline control --==*/
    float histoBinWidth = (histoRight-histoLeft)/numHistoBins;
    float maxHistoVal = *(std::max_element(histogram.begin(), histogram.end()));
    float histoBinHeightFactor = (histoTop-histoBottom)/(maxHistoVal);
    float nextVertX, nextVertY;     // temporary values to push into histo vector
    histoVertices.clear();
    histoIndices.clear();
    for (int j = 0; j < numHistoBins; ++j)
    {   // This FOR loop creates vertices for the histogram rectangle bins
        nextVertX = histoLeft+histoBinWidth*j;
        nextVertY = histoBottom;
        histoVertices.push_back(vec2(nextVertX, nextVertY));
        nextVertX = histoLeft+histoBinWidth*(j+1);
        histoVertices.push_back(vec2(nextVertX, nextVertY));
        nextVertY = histoBottom+histoBinHeightFactor*histogram[j];
        histoVertices.push_back(vec2(nextVertX, nextVertY));
        nextVertX = histoLeft+histoBinWidth*j;
        histoVertices.push_back(vec2(nextVertX, nextVertY));
        histoIndices.push_back(4*j);
        histoIndices.push_back(4*j+1);
        histoIndices.push_back(4*j+2);
        histoIndices.push_back(4*j+3);
    }   // this FOR loop creates vertices for a line across the top of the bins
    for (int j=0;j < numHistoBins; ++j)
    {
        nextVertX=(histoVertices[4*j+2][0]+ histoVertices[4*j+3][0])/2.0;
        nextVertY=(histoVertices[4*j+2][1]);
        histoVertices.push_back(vec2(nextVertX,nextVertY));
        histoIndices.push_back(j+4*int(numHistoBins));
    }
    numHistoVertices = int(histoVertices.size());
    numHistoIndices = int(histoIndices.size());
    /*==-- (END) Generate initial vertices and indices for histogram  --==*/
}
void Timeline::showHide()
{
    hidden = (!hidden);
   
}
void Timeline::updateYearMarks()
{
    lowestSliderYear = 950+950*(lSliderPos + sliderOffset[0]-histoLeft)/(histoRight-histoLeft);
    highestSliderYear = 950+950*(rSliderPos + sliderOffset[1]-histoLeft)/(histoRight-histoLeft);
}


void initGLFW()
{
    glfwSetErrorCallback(errorCallb);
    if (!glfwInit()) {
        std::cout << "failed to initialize!" << std::endl;
        exit(4);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 32);
    glfwWindowHint(GLFW_SAMPLES, 16);
    strcpy(windowName,"Art Object Visualization");
    mainWin = glfwCreateWindow(mainWinWidth, mainWinHeight, windowName, NULL, NULL);
    if (!mainWin) {
        glfwTerminate();
        exit(3);
    }
    glfwMakeContextCurrent(mainWin);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //    /* With Retina on Mac OS X, GLFW's FramebufferSize dne WindowSize */
    //    glfwGetFramebufferSize(wind, &fbwidth, &fbheight);
    //
    //    // call the reshape first, since it is not called at window creation
    //    windowReshape(wind, fbwidth, fbheight);  // shape view port
    //--- register callbacks with GLFW ----
    //    /* function to handle window resizes */
    //    glfwSetFramebufferSizeCallback(wind, fbreshape);
    glfwSetWindowSizeCallback(mainWin, windowReshape);
    glfwSetWindowCloseCallback(mainWin,quitApp);  // for window close
    glfwSetKeyCallback(mainWin, specialKeyTyping);
    glfwSetCharCallback(mainWin, asciiTyping);
    glfwSetCursorPosCallback(mainWin, screenCursor);
    glfwSetScrollCallback(mainWin, scrollFunc);
    glfwSetMouseButtonCallback(mainWin, mouseFunc);
    glfwSwapInterval(0);    // allows more than 60 FPS (at risk of tearing!)
}
void initOpenGL(sphereSpec calcio, Timeline Histo)
{
    glEnable(GL_DEPTH_TEST);
    program[0] = prepareShaders("wgaSphereGLSL.vert", "wgaSphereGLSL.frag");
    program[1] = prepareShaders("wgaPanelGLSL.vert", "wgaPanelGLSL.frag");
    program[2] = prepareShaders("wgaSliderGLSL.vert", "wgaSliderGLSL.frag");
    program[3] = prepareShaders("wgaHistoGLSL.vert", "wgaHistoGLSL.frag");
    program[4] = prepareShaders("wgaHighlightsGLSL.vert", "wgaHighlightsGLSL.frag");
  
    /*--- (BEGIN) Create VAO and buffer stuff  ---*/
    glGenBuffers(numBuffers,shaderBuffer);
    glGenVertexArrays(numVAO,VertexArrayID);
    /*--- (END) Create VAO and buffer stuff  ---*/

    /*--- (BEGIN) Sphere Preparation  ---*/
    // program 0 has shaders that do perspective and lighting model
    // program 0 will use VAO 0
    glUseProgram(program[0]);
    // Sphere Indices and Vertices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(calcio.indices[0]) * calcio.numIndices),&calcio.indices.front(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[1]);
    glBufferData(GL_ARRAY_BUFFER, ((sizeof(calcio.vertices[0])+sizeof(calcio.norms[0])) * calcio.numVertices),NULL,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, (sizeof(calcio.vertices[0]) * calcio.numVertices), &calcio.vertices.front());
    glBufferSubData(GL_ARRAY_BUFFER, (sizeof(calcio.vertices[0]) * calcio.numVertices), (sizeof(calcio.norms[0]) * calcio.numVertices), &calcio.norms.front());
    
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(calcio.stMap[0])*calcio.numVertices,&calcio.stMap.front(), GL_STATIC_DRAW);
    
    // Vertex Array Object 0 is for the Sphere
    glBindVertexArray(VertexArrayID[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[0]);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[1]);
    attribLocation[0] = glGetAttribLocation(program[0], "vPosition");
    glVertexAttribPointer(attribLocation[0],3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
    
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[6]);
    attribLocation[4] = glGetAttribLocation(program[0], "stMap");
    glVertexAttribPointer(attribLocation[4],2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
    glBindVertexArray(0);
    /*--- (END) Sphere Preparation  ---*/
    
    /*--- (BEGIN) Panel Preparation  ---*/
    // program 1 has shaders that draw a textured panel without perspective
    // program 1 will use VAO 1
    glUseProgram(program[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Histo.bgIndices[0])*Histo.numBgIndices,&Histo.bgIndices.front(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Histo.bgVertices[0])*Histo.numBgVertices,&Histo.bgVertices.front(),GL_STATIC_DRAW);
    
    // Vertex Array Object 1 is for the Panel
    glBindVertexArray(VertexArrayID[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[2]);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[3]);
    attribLocation[1] = glGetAttribLocation(program[1], "vPosition");
    glVertexAttribPointer(attribLocation[1],2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));

    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Histo.stMap[0])*Histo.numBgVertices,&Histo.stMap.front(), GL_STATIC_DRAW);
    attribLocation[3] = glGetAttribLocation(program[1], "stMap");
    glVertexAttribPointer(attribLocation[3],2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
    glBindVertexArray(0);
    /*--- (END) Panel Preparation  ---*/
    
    /*--- (BEGIN) Slider Preparation  ---*/
    // program 2 has shaders that draw panel sliders without perspective
    // program 2 will use VAO 2
    glUseProgram(program[2]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[7]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Histo.sliderIndices[0])*Histo.numSliderIndices,&Histo.sliderIndices.front(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[8]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Histo.sliderVertices[0])*Histo.numSliderVertices,&Histo.sliderVertices.front(),GL_STATIC_DRAW);
    
    // Vertex Array Object 2 is for the Sliders
    glBindVertexArray(VertexArrayID[2]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[7]);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[8]);
    attribLocation[2] = glGetAttribLocation(program[2], "vPosition");
    glVertexAttribPointer(attribLocation[2],2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
    
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[11]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Histo.stMapSlider[0])*Histo.numSliderVertices,&Histo.stMapSlider.front(), GL_STATIC_DRAW);
    attribLocation[6] = glGetAttribLocation(program[2], "stMapSlider");
    glVertexAttribPointer(attribLocation[6],2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
    uniformLocation[3] = glGetUniformLocation(program[2], "whichSlider");
    uniformLocation[4] = glGetUniformLocation(program[2], "sliderOffsetsHorizontal");
    glUniform2f(uniformLocation[4], sliderOffset[0],sliderOffset[1]);
    glBindVertexArray(0);
    /*--- (END) Slider Preparation  ---*/
    
    /*==-- (BEGIN) Histogram preparation        --==*/
    // program 3 has shaders that draw the histogram without perspective
    // program 3 will use VAO 3
    glUseProgram(program[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[9]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Histo.histoIndices[0])*Histo.numHistoIndices,&Histo.histoIndices.front(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Histo.histoVertices[0])*Histo.numHistoVertices,&Histo.histoVertices.front(),GL_STATIC_DRAW);
    
    // Vertex Array Object 2 is for the Histogram
    glBindVertexArray(VertexArrayID[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[9]);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[10]);
    attribLocation[5] = glGetAttribLocation(program[3], "vPosition");
    glVertexAttribPointer(attribLocation[5],2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
    uniformLocation[5] = glGetUniformLocation(program[3], "whichElement");
    glBindVertexArray(0);
    /*==-- (END) Histogram preparation        --==*/

    /*--- (BEGIN) Highlights preparation  ---*/
    glUseProgram(program[4]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[12]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(countryContrib.indices[0])*countryContrib.numIndices,&countryContrib.indices.front(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[13]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(countryContrib.vertices[0])*countryContrib.numVertices,&countryContrib.vertices.front(),GL_STATIC_DRAW);

    // Vertex Array Object 4 is for the Highlights
    glBindVertexArray(VertexArrayID[4]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[12]);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[13]);
    attribLocation[7] = glGetAttribLocation(program[4], "vPosition");
    glVertexAttribPointer(attribLocation[7],3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));
    glBindVertexArray(0);
    
    // connect Highlight spec matrices
    uniformLocation[8] = glGetUniformLocation(program[4], "lightSpec");
    uniformLocation[7] = glGetUniformLocation(program[4], "blobSpec");
    
    startv = glm::normalize(vec3(0.0,0.0,1.0));

    // my goodness, I really need to replace this sequence with a simple function and array
    vec3 endv = glm::normalize(vec3(-.2,1.3 ,-1.24));
    glm::mat4 rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[0] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;

    endv = glm::normalize(vec3(-.16,1.85 ,-1.51));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[1] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;

    endv = glm::normalize(vec3(-.47,1.79 ,-1.52));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[2] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;

    endv = glm::normalize(vec3(.01,1.04 ,-1.17));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[3] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;

    endv = glm::normalize(vec3(-.22,1.93 ,-1.34));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[4] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;

    endv = glm::normalize(vec3(-.13,1.88 ,-1.44));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[5] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;

    endv = glm::normalize(vec3(.02, 1.45,-1.12));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[6] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;

    endv = glm::normalize(vec3(-.48,2.12 ,-0.95));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[7] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.02, 1.3,-1.12));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[8] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.07,1.23 ,-1.18));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[9] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.25,1.86 ,-1.44));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[10] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.59,1.25 ,-1.26));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[11] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.44,1.49 ,-1.37));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[12] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(0.17,1.50 ,-1.12));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[13] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.3,1.13 ,-1.24));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[14] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.13,1.88 ,-1.44));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[15] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-0.17,2.22 ,-1.24));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[16] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.51,2.07 ,-1.52));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[17] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(0.17,0.98 ,-1.12));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[18] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.88,2.14 ,-1.22));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[19] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(.08, 1.95,-1.22));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[20] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(0.08,0.96,-1.15));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[21] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.33,2.11 ,-1.24));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[22] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    endv = glm::normalize(vec3(-.17,1.24 ,-1.17));
    rotateFirst = glm::mat4_cast(RotationBetweenVectors(startv, endv));
    blobSpec[23] = glm::translate(glm::mat4(1.0),endv)*rotateFirst;
    
    countryContrib.updateHighlightColors(works.getAllPercs());
    for(int i = 0; i<24; ++i)
        lightSpec[i] = countryContrib.colorSpec[i];
    glUniformMatrix4fv(uniformLocation[7], 24, GL_FALSE, glm::value_ptr(blobSpec[0]));
    glUniform4fv(uniformLocation[8], 24, glm::value_ptr(lightSpec[0]));
    for(int i = 0; i<24; ++i) std::cout << i << " " << lightSpec[i].x << "," << lightSpec[i].y
        <<"," << lightSpec[i].z << "," <<lightSpec[i].w << std::endl;
    
    /*--- (END)  Highlights preparation  ---*/

    /*--- (BEGIN) Uniform block: Camera  ---*/
    glUseProgram(program[0]);
    uBlockIndex[0] = glGetUniformBlockIndex(program[0], "camera");
    if (uBlockIndex[0] == GL_INVALID_INDEX) {
        std::cout << "Unable to find 'camera' uniform block in the program." << std::endl; exit(EXIT_FAILURE);
    } ;
    glGetActiveUniformBlockiv(program[4], uBlockIndex[0], GL_UNIFORM_BLOCK_DATA_SIZE, &uBlockSize[0]);
    uBufferC = (GLubyte *) malloc(uBlockSize[0]);
    if (uBufferC==NULL) {
        std::cout << "Failed while allocating uniform block buffer." << std::endl; exit(EXIT_FAILURE);
    }
    const char* uVarNames[numCameraBlockVars] = {"modelvMatrix","projMatrix","fixedPanelMatrix"};
    GLuint uVarIndices[numCameraBlockVars];
    GLint uVarSize[numCameraBlockVars];
    GLint uVarOffset[numCameraBlockVars];
    GLint uVarType[numCameraBlockVars];
    glGetUniformIndices(program[0], numCameraBlockVars,uVarNames,uVarIndices);
    glGetActiveUniformsiv(program[0], numCameraBlockVars, uVarIndices, GL_UNIFORM_OFFSET, uVarOffset);
    glGetActiveUniformsiv(program[0], numCameraBlockVars, uVarIndices, GL_UNIFORM_SIZE, uVarSize);
    glGetActiveUniformsiv(program[0], numCameraBlockVars, uVarIndices, GL_UNIFORM_TYPE, uVarType);
    
    modelMatrixAddr = uBufferC+uVarOffset[ModelvMatrix];
    uVarMemorySize[0] = uVarSize[ModelvMatrix]*TypeSize(uVarType[ModelvMatrix]) ;
    projMatrixAddr =uBufferC+uVarOffset[ProjMatrix];
    uVarMemorySize[1] =uVarSize[ProjMatrix]*TypeSize(uVarType[ProjMatrix]);
    fixedPanelMatrixAddr =uBufferC+uVarOffset[FixedPanelMatrix];
    uVarMemorySize[2] =uVarSize[FixedPanelMatrix]*TypeSize(uVarType[FixedPanelMatrix]);
    
    memcpy(modelMatrixAddr,&modelvMatrix, uVarMemorySize[0]);
    memcpy(projMatrixAddr,&projMatrix, uVarMemorySize[1]);
    memcpy(fixedPanelMatrixAddr,&fixedPanelMatrix, uVarMemorySize[2]);
    uBlockBinding​[0]= 1;
    glUniformBlockBinding(program[0], uBlockIndex[0],uBlockBinding​[0]);
    glBindBufferBase(GL_UNIFORM_BUFFER, uBlockBinding​[0], shaderBuffer[4]);
    glBindBuffer(GL_UNIFORM_BUFFER, shaderBuffer[4]);
    glBufferData(GL_UNIFORM_BUFFER, uBlockSize[0], uBufferC, GL_STATIC_DRAW);
    
    uBlockBinding​[1]= 2;
    glUniformBlockBinding(program[4], uBlockIndex[0],uBlockBinding​[1]);
    glBindBufferBase(GL_UNIFORM_BUFFER, uBlockBinding​[1], shaderBuffer[4]);
    glBindBuffer(GL_UNIFORM_BUFFER, shaderBuffer[4]);
    glBufferData(GL_UNIFORM_BUFFER, uBlockSize[0], uBufferC, GL_STATIC_DRAW);
//    --- (END) Uniform block: Camera  ---

//    attribLocation[1] = glGetAttribLocation(program[0], "vNormal");
//    glVertexAttribPointer(attribLocation[1],3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));

    glClearColor(bgClearColor[0],bgClearColor[1], bgClearColor[2], 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
//     glEnable(GL_CULL_FACE);
    
}
void initTextures()
{
    /*--- (BEGIN) Texture preparation: Earth map  ---*/
    glGenTextures(2, textureName);
    
    glUseProgram(program[0]);
    glBindVertexArray(VertexArrayID[0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureName[0]);
    loadTextureImg("equEarth-2048.gif");
    
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    uniformLocation[1] = glGetUniformLocation(program[0], "samplePanel");
    glUniform1i(uniformLocation[1], 0);
    /*--- (END) Texture preparation: Earth map  ---*/

    /*--- (BEGIN) Texture preparation: Panel and sliders  ---*/
    glUseProgram(program[1]);
    glBindVertexArray(VertexArrayID[1]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureName[1]);
    loadTextureImg("timelineTexture-annun.gif");
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    uniformLocation[2] = glGetUniformLocation(program[1], "samplePanel");
    glUniform1i(uniformLocation[2], 1);
    
    glUseProgram(program[2]);
    glBindVertexArray(VertexArrayID[2]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureName[1]);
    uniformLocation[6] = glGetUniformLocation(program[2], "sampleSlider");
    glUniform1i(uniformLocation[2], 1);
    /*--- (END) Texture preparation: Panel and sliders  ---*/
}

void updateCamera(void)
{
//    glUseProgram(program[0]);
    camEye = euclidCamera(camEyeR,camEyeθ,camEyeφ);
    modelvMatrix = glm::lookAt(camEye,camAt,camUp);
    projMatrix = glm::perspective(frFOV,frAspect,frNear,frFar);
//    projMatrix = glm::ortho(prLeft, prRight, prBottom, prTop, prNear, prFar);

    memcpy(modelMatrixAddr,&modelvMatrix, uVarMemorySize[0]);
    memcpy(projMatrixAddr,&projMatrix, uVarMemorySize[1]);
    memcpy(fixedPanelMatrixAddr,&fixedPanelMatrix, uVarMemorySize[2]);
    glBindBuffer(GL_UNIFORM_BUFFER, shaderBuffer[4]);
    glBufferData(GL_UNIFORM_BUFFER, uBlockSize[0], uBufferC, GL_STATIC_DRAW);
}

void drawPanel()
{
    /*==-- (BEGIN) Draw timeline background             --==*/
    glUseProgram(program[1]);
    glBindVertexArray(VertexArrayID[1]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureName[1]);

    glEnableVertexAttribArray(attribLocation[1]);
    glEnableVertexAttribArray(attribLocation[3]);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[2]);
    mainPanel.Draw(0);
    glDisableVertexAttribArray(attribLocation[1]);
    glDisableVertexAttribArray(attribLocation[3]);
     /*==-- (END) Draw timeline background              --==*/
    
    /*==-- (BEGIN) Draw histogram bins and top line     --==*/
    glUseProgram(program[3]);
    glBindVertexArray(VertexArrayID[3]);
    glEnableVertexAttribArray(attribLocation[5]);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[10]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[9]);
    mainPanel.Draw(2);
    glDisableVertexAttribArray(attribLocation[5]);
    /*==-- (BEGIN) Draw histogram bins and top line     --==*/
    
    /*==-- (BEGIN) Draw timeline sliders                --==*/
    glUseProgram(program[2]);
    glBindVertexArray(VertexArrayID[2]);
    glEnableVertexAttribArray(attribLocation[2]);
    glEnableVertexAttribArray(attribLocation[6]);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[8]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[7]);
    mainPanel.Draw(1);
    glDisableVertexAttribArray(attribLocation[2]);
    glDisableVertexAttribArray(attribLocation[6]);
    /*==-- (END) Draw timeline sliders                  --==*/
}

void drawSphere()
{
    
    glUseProgram(program[0]);
    glBindVertexArray(VertexArrayID[0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureName[0]);
    
    glEnableVertexAttribArray(attribLocation[0]);
    glEnableVertexAttribArray(attribLocation[4]);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[0]);
    
    glDrawElements(GL_TRIANGLE_FAN,(basicSphere.theSphere.fans+2),GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
    for (int j = 0; j<(basicSphere.theSphere.bands-2); j++) {
        glDrawElements(GL_TRIANGLE_STRIP,(2*basicSphere.theSphere.fans+2), GL_UNSIGNED_INT,
                       (void*)(((basicSphere.theSphere.fans+2)+j*(2*basicSphere.theSphere.fans+2)) * sizeof(GLuint)));
    }
    glDrawElements(GL_TRIANGLE_FAN,(basicSphere.theSphere.fans+2),GL_UNSIGNED_INT,
                   (void*)((basicSphere.theSphere.numIndices-basicSphere.theSphere.fans-2) * sizeof(GLuint)));
    glDisableVertexAttribArray(attribLocation[0]);
    glDisableVertexAttribArray(attribLocation[4]);
}

void drawHighlights()
{
    /*==-- (BEGIN) Draw highlights instance     --==*/
    glUseProgram(program[4]);
    glBindVertexArray(VertexArrayID[4]);
    glUniform4fv(uniformLocation[8], 24, glm::value_ptr(lightSpec[0]));
    glEnableVertexAttribArray(attribLocation[7]);
    glBindBuffer(GL_ARRAY_BUFFER, shaderBuffer[13]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderBuffer[12]);
    countryContrib.draw();

    glDisableVertexAttribArray(attribLocation[7]);
    /*==-- (END) Draw highlights instance     --==*/

}

#ifndef WGA_visualization_main_h
#define WGA_visualization_main_hq


#endif
