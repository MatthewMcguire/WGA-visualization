//
//  main.cpp
//  WGA visualization
//
//  Created by Matthew McGuire on 4/24/15.
//  Copyright (c) 2015 Matthew McGuire. All rights reserved.
//

#include "main.h"
#include <cstddef>
#include "tweakbarFunctions.h"

/* Primary GLFW display loop */
void updateDisplay() {
    glClearColor(bgClearColor[0],bgClearColor[1], bgClearColor[2], 1);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );
    if (donePausing==GL_TRUE) {
        switch(mouseNav)
        {
            case RightClick:        // camera spins on right click
                moveCamera();
                break;
            case LeftClickRelease:  // an engaged slider is released
                mouseNav = NoClick;
                // report on new timeline values
                mainPanel.leftLastPreviousLoc = sliderOffset[0];
                mainPanel.rightLastPreviousLoc = sliderOffset[1];
                mainPanel.bBoxUpdate();
                // calculate new time interval with which to filter the data
                mainPanel.updateYearMarks();
                std::cout << "left mark: " << mainPanel.lSliderPos + sliderOffset[0];
                std::cout << " right mark: " << mainPanel.rSliderPos + sliderOffset[1] << std::endl;
                std::cout << "left Year: " << mainPanel.lowestSliderYear<< " right Year: " << mainPanel.highestSliderYear;
                std::cout << std::endl;
                
                // update works Dataset filters (and metrics) with correct begin year and end year
                works.adjustTimeframes(mainPanel.lowestSliderYear, mainPanel.highestSliderYear);
                
                // update panel histogram
                mainPanel.updateHistogram(works.getDecadeHisto());
                countryContrib.updateHighlightColors(works.getAllPercs());
                for(int i = 0; i<24; ++i)
                    lightSpec[i] = countryContrib.colorSpec[i];
                break;
            case LeftSliderMoving:    // set left slider displacement = cursor displacement
                lClickDragVector = currentCursor-initLClickPos;
                mainPanel.moveSlider(-1, lClickDragVector[0]);
                break;
            case RightSliderMoving:    // set right slider displacement = cursor displacement
                lClickDragVector = currentCursor-initLClickPos;
                mainPanel.moveSlider(-2, lClickDragVector[0]);
                break;
            case LeftClickPress:   // if in bounding box, set dragging = true and set cursor displace reference
                mouseNav = mainPanel.clickedOnSlider();
                if (mouseNav != LeftClickPress) initLClickPos = currentCursor;
                break;
            default:
                break;
        }

        lastPauseEnd = glfwGetTime();
        donePausing = GL_FALSE;
        updateCamera();
    }
    
    drawPanel();
    drawSphere();
    drawHighlights();
    TwDraw();
    
    nowFPS = glfwGetTime();
    if(nowFPS > fps[1] + 1.0) {
        char newTitle[50];
        std::strcpy(newTitle, ("Art Object Visualization (" + std::to_string(fpsCounter) + " fps)").c_str());
        glfwSetWindowTitle(mainWin,newTitle );
       
        fpsCounter = 0;
        fps[1]=nowFPS;
    }
    else fpsCounter++;
    glfwSwapBuffers(mainWin);
    glfwMakeContextCurrent(mainWin);
    if(donePausing==GL_FALSE && (glfwGetTime()-lastPauseEnd)> pauseLength) donePausing = GL_TRUE;
}


int main(int argc, const char * argv[]) {
    fps[0] = glfwGetTime();
    assert (restart_gl_log ());
    gl_log (" starting GLFW\n% s\n", glfwGetVersionString ());
    /* Initialize graphics environment */
    initGLFW();

    log_gl_params();
    
    initTweakbar();
    initOpenGL(basicSphere.theSphere, mainPanel);
    initTextures();
    
    countryContrib.updateHighlistNames(works.getCountriesList());

    
    fps[1] = glfwGetTime();
    std::cout << "it took " << fps[1]-fps[0] << " sec. to get going!" << std::endl;
    
    /* Enter the main interactive display loop*/
    do{
        if(mainPanel.hovered(currentCursor))
            mainPanel.hidden=false;
        else
            mainPanel.hidden=true;
        updateDisplay();
        glfwPollEvents();
    } while (!glfwWindowShouldClose(mainWin));
    
    /* Exit */
    std::cout << "You should not see this message.\n";
    return 0;
}
