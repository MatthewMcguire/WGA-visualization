//
//  tweakbarFunctions.h
//  WGA visualization
//
//  Created by Matthew McGuire on 5/5/15.
//  Copyright (c) 2015 Matthew McGuire. All rights reserved.
//

#ifndef WGA_visualization_tweakbarFunctions_h
#define WGA_visualization_tweakbarFunctions_h
void pushVisualChanges(void)
{
    mainPanel.updateHistogram(works.getDecadeHisto());
    countryContrib.updateHighlightColors(works.getAllPercs());
    for(int i = 0; i<24; ++i)
        lightSpec[i] = countryContrib.colorSpec[i];
}

void TW_CALL Callb_type_genre(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("type_genre");
    if (stateCheck)
    {
        works.setFilterState("type_genre", false);
        TwSetParam(myBar, "type_genre", "label", TW_PARAM_CSTRING, 1, "(Genre)");
    }
    else
    {
        works.setFilterState("type_genre", true);
        TwSetParam(myBar, "type_genre", "label", TW_PARAM_CSTRING, 1, "Genre");
    }
    pushVisualChanges();
}
void TW_CALL Callb_type_historical(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("type_historical");
    if (stateCheck)
    {
        works.setFilterState("type_historical", false);
        TwSetParam(myBar, "type_historical", "label", TW_PARAM_CSTRING, 1, "(Historical)");
    }
    else
    {
        works.setFilterState("type_historical", true);
        TwSetParam(myBar, "type_historical", "label", TW_PARAM_CSTRING, 1, "Historical");
    }
    pushVisualChanges();
}
void TW_CALL Callb_type_interior(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("type_interior");
    if (stateCheck)
    {
        works.setFilterState("type_interior", false);
        TwSetParam(myBar, "type_interior", "label", TW_PARAM_CSTRING, 1, "(Interior)");
    }
    else
    {
        works.setFilterState("type_interior", true);
        TwSetParam(myBar, "type_interior", "label", TW_PARAM_CSTRING, 1, "Interior");
    }
    pushVisualChanges();
}
void TW_CALL Callb_type_landscape(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("type_landscape");
    if (stateCheck)
    {
        works.setFilterState("type_landscape", false);
        TwSetParam(myBar, "type_landscape", "label", TW_PARAM_CSTRING, 1, "(Landscape)");
    }
    else
    {
        works.setFilterState("type_landscape", true);
        TwSetParam(myBar, "type_landscape", "label", TW_PARAM_CSTRING, 1, "Landscape");
    }
    pushVisualChanges();
}
void TW_CALL Callb_type_mythological(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("type_mythological");
    if (stateCheck)
    {
        works.setFilterState("type_mythological", false);
        TwSetParam(myBar, "type_mythological", "label", TW_PARAM_CSTRING, 1, "(Mythological)");
    }
    else
    {
        works.setFilterState("type_mythological", true);
        TwSetParam(myBar, "type_mythological", "label", TW_PARAM_CSTRING, 1, "Mythological");
    }
    pushVisualChanges();
}
void TW_CALL Callb_type_other(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("type_other");
    if (stateCheck)
    {
        works.setFilterState("type_other", false);
        TwSetParam(myBar, "type_other", "label", TW_PARAM_CSTRING, 1, "(Other)");
    }
    else
    {
        works.setFilterState("type_other", true);
        TwSetParam(myBar, "type_other", "label", TW_PARAM_CSTRING, 1, "Other");
    }
    pushVisualChanges();
}
void TW_CALL Callb_type_portrait(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("type_portrait");
    if (stateCheck)
    {
        works.setFilterState("type_portrait", false);
        TwSetParam(myBar, "type_portrait", "label", TW_PARAM_CSTRING, 1, "(Portrait)");
    }
    else
    {
        works.setFilterState("type_portrait", true);
        TwSetParam(myBar, "type_portrait", "label", TW_PARAM_CSTRING, 1, "Portrait");
    }
    pushVisualChanges();
}
void TW_CALL Callb_type_religious(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("type_religious");
    if (stateCheck)
    {
        works.setFilterState("type_religious", false);
        TwSetParam(myBar, "type_religious", "label", TW_PARAM_CSTRING, 1, "(Religious)");
    }
    else
    {
        works.setFilterState("type_religious", true);
        TwSetParam(myBar, "type_religious", "label", TW_PARAM_CSTRING, 1, "Religious");
    }
    pushVisualChanges();
}
void TW_CALL Callb_type_still_life(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("type_still-life");
    if (stateCheck)
    {
        works.setFilterState("type_still-life", false);
        TwSetParam(myBar, "type_still-life", "label", TW_PARAM_CSTRING, 1, "(Still-Life)");
    }
    else
    {
        works.setFilterState("type_still-life", true);
        TwSetParam(myBar, "type_still-life", "label", TW_PARAM_CSTRING, 1, "Still-Life");
    }
    pushVisualChanges();
}
void TW_CALL Callb_type_study(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("type_study");
    if (stateCheck)
    {
        works.setFilterState("type_study", false);
        TwSetParam(myBar, "type_study", "label", TW_PARAM_CSTRING, 1, "(Study)");
    }
    else
    {
        works.setFilterState("type_study", true);
        TwSetParam(myBar, "type_study", "label", TW_PARAM_CSTRING, 1, "Study");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Austrian(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Austrian");
    if (stateCheck)
    {
        works.setFilterState("school_Austrian", false);
        TwSetParam(myBar, "school_Austrian", "label", TW_PARAM_CSTRING, 1, "(Austria)");
    }
    else
    {
        works.setFilterState("school_Austrian", true);
        TwSetParam(myBar, "school_Austrian", "label", TW_PARAM_CSTRING, 1, "Austria");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Belgian(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Belgian");
    if (stateCheck)
    {
        works.setFilterState("school_Belgian", false);
        TwSetParam(myBar, "school_Belgian", "label", TW_PARAM_CSTRING, 1, "(Belgium)");
    }
    else
    {
        works.setFilterState("school_Belgian", true);
        TwSetParam(myBar, "school_Belgian", "label", TW_PARAM_CSTRING, 1, "Belgium");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Bohemian(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Bohemian");
    if (stateCheck)
    {
        works.setFilterState("school_Bohemian", false);
        TwSetParam(myBar, "school_Bohemian", "label", TW_PARAM_CSTRING, 1, "(Bohemia)");
    }
    else
    {
        works.setFilterState("school_Bohemian", true);
        TwSetParam(myBar, "school_Bohemian", "label", TW_PARAM_CSTRING, 1, "Bohemia");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Catalan(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Catalan");
    if (stateCheck)
    {
        works.setFilterState("school_Catalan", false);
        TwSetParam(myBar, "school_Catalan", "label", TW_PARAM_CSTRING, 1, "(Catalonia)");
    }
    else
    {
        works.setFilterState("school_Catalan", true);
        TwSetParam(myBar, "school_Catalan", "label", TW_PARAM_CSTRING, 1, "Catalonia");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Danish(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Danish");
    if (stateCheck)
    {
        works.setFilterState("school_Danish", false);
        TwSetParam(myBar, "school_Danish", "label", TW_PARAM_CSTRING, 1, "(Denmark)");
    }
    else
    {
        works.setFilterState("school_Danish", true);
        TwSetParam(myBar, "school_Danish", "label", TW_PARAM_CSTRING, 1, "Denmark");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Dutch(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Dutch");
    if (stateCheck)
    {
        works.setFilterState("school_Dutch", false);
        TwSetParam(myBar, "school_Dutch", "label", TW_PARAM_CSTRING, 1, "(Holland)");
    }
    else
    {
        works.setFilterState("school_Dutch", true);
        TwSetParam(myBar, "school_Dutch", "label", TW_PARAM_CSTRING, 1, "Holland");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_English(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_English");
    if (stateCheck)
    {
        works.setFilterState("school_English", false);
        TwSetParam(myBar, "school_English", "label", TW_PARAM_CSTRING, 1, "(England)");
    }
    else
    {
        works.setFilterState("school_English", true);
        TwSetParam(myBar, "school_English", "label", TW_PARAM_CSTRING, 1, "England");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Finnish(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Finnish");
    if (stateCheck)
    {
        works.setFilterState("school_Finnish", false);
        TwSetParam(myBar, "school_Finnish", "label", TW_PARAM_CSTRING, 1, "(Finland)");
    }
    else
    {
        works.setFilterState("school_Finnish", true);
        TwSetParam(myBar, "school_Finnish", "label", TW_PARAM_CSTRING, 1, "Finland");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Flemish(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Flemish");
    if (stateCheck)
    {
        works.setFilterState("school_Flemish", false);
        TwSetParam(myBar, "school_Flemish", "label", TW_PARAM_CSTRING, 1, "(Flanders)");
    }
    else
    {
        works.setFilterState("school_Flemish", true);
        TwSetParam(myBar, "school_Flemish", "label", TW_PARAM_CSTRING, 1, "Flanders");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_French(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_French");
    if (stateCheck)
    {
        works.setFilterState("school_French", false);
        TwSetParam(myBar, "school_French", "label", TW_PARAM_CSTRING, 1, "(France)");
    }
    else
    {
        works.setFilterState("school_French", true);
        TwSetParam(myBar, "school_French", "label", TW_PARAM_CSTRING, 1, "France");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_German(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_German");
    if (stateCheck)
    {
        works.setFilterState("school_German", false);
        TwSetParam(myBar, "school_German", "label", TW_PARAM_CSTRING, 1, "(Germany)");
    }
    else
    {
        works.setFilterState("school_German", true);
        TwSetParam(myBar, "school_German", "label", TW_PARAM_CSTRING, 1, "Germany");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Greek(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Greek");
    if (stateCheck)
    {
        works.setFilterState("school_Greek", false);
        TwSetParam(myBar, "school_Greek", "label", TW_PARAM_CSTRING, 1, "(Greece)");
    }
    else
    {
        works.setFilterState("school_Greek", true);
        TwSetParam(myBar, "school_Greek", "label", TW_PARAM_CSTRING, 1, "Greece");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Hungarian(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Hungarian");
    if (stateCheck)
    {
        works.setFilterState("school_Hungarian", false);
        TwSetParam(myBar, "school_Hungarian", "label", TW_PARAM_CSTRING, 1, "(Hungary)");
    }
    else
    {
        works.setFilterState("school_Hungarian", true);
        TwSetParam(myBar, "school_Hungarian", "label", TW_PARAM_CSTRING, 1, "Hungary");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Irish(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Irish");
    if (stateCheck)
    {
        works.setFilterState("school_Irish", false);
        TwSetParam(myBar, "school_Irish", "label", TW_PARAM_CSTRING, 1, "(Ireland)");
    }
    else
    {
        works.setFilterState("school_Irish", true);
        TwSetParam(myBar, "school_Irish", "label", TW_PARAM_CSTRING, 1, "Ireland");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Italian(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Italian");
    if (stateCheck)
    {
        works.setFilterState("school_Italian", false);
        TwSetParam(myBar, "school_Italian", "label", TW_PARAM_CSTRING, 1, "(Italy)");
    }
    else
    {
        works.setFilterState("school_Italian", true);
        TwSetParam(myBar, "school_Italian", "label", TW_PARAM_CSTRING, 1, "Italy");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Netherlandish(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Netherlandish");
    if (stateCheck)
    {
        works.setFilterState("school_Netherlandish", false);
        TwSetParam(myBar, "school_Netherlandish", "label", TW_PARAM_CSTRING, 1, "(Netherlands)");
    }
    else
    {
        works.setFilterState("school_Netherlandish", true);
        TwSetParam(myBar, "school_Netherlandish", "label", TW_PARAM_CSTRING, 1, "Netherlands");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Norwegian(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Norwegian");
    if (stateCheck)
    {
        works.setFilterState("school_Norwegian", false);
        TwSetParam(myBar, "school_Norwegian", "label", TW_PARAM_CSTRING, 1, "(Norway)");
    }
    else
    {
        works.setFilterState("school_Norwegian", true);
        TwSetParam(myBar, "school_Norwegian", "label", TW_PARAM_CSTRING, 1, "Norway");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Polish(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Polish");
    if (stateCheck)
    {
        works.setFilterState("school_Polish", false);
        TwSetParam(myBar, "school_Polish", "label", TW_PARAM_CSTRING, 1, "(Poland)");
    }
    else
    {
        works.setFilterState("school_Polish", true);
        TwSetParam(myBar, "school_Polish", "label", TW_PARAM_CSTRING, 1, "Poland");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Portuguese(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Portuguese");
    if (stateCheck)
    {
        works.setFilterState("school_Portuguese", false);
        TwSetParam(myBar, "school_Portuguese", "label", TW_PARAM_CSTRING, 1, "(Portugal)");
    }
    else
    {
        works.setFilterState("school_Portuguese", true);
        TwSetParam(myBar, "school_Portuguese", "label", TW_PARAM_CSTRING, 1, "Portugal");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Russian(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Russian");
    if (stateCheck)
    {
        works.setFilterState("school_Russian", false);
        TwSetParam(myBar, "school_Russian", "label", TW_PARAM_CSTRING, 1, "(Russia)");
    }
    else
    {
        works.setFilterState("school_Russian", true);
        TwSetParam(myBar, "school_Russian", "label", TW_PARAM_CSTRING, 1, "Russia");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Scottish(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Scottish");
    if (stateCheck)
    {
        works.setFilterState("school_Scottish", false);
        TwSetParam(myBar, "school_Scottish", "label", TW_PARAM_CSTRING, 1, "(Scotland)");
    }
    else
    {
        works.setFilterState("school_Scottish", true);
        TwSetParam(myBar, "school_Scottish", "label", TW_PARAM_CSTRING, 1, "Scotland");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Spanish(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Spanish");
    if (stateCheck)
    {
        works.setFilterState("school_Spanish", false);
        TwSetParam(myBar, "school_Spanish", "label", TW_PARAM_CSTRING, 1, "(Spain)");
    }
    else
    {
        works.setFilterState("school_Spanish", true);
        TwSetParam(myBar, "school_Spanish", "label", TW_PARAM_CSTRING, 1, "Spain");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Swedish(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Swedish");
    if (stateCheck)
    {
        works.setFilterState("school_Swedish", false);
        TwSetParam(myBar, "school_Swedish", "label", TW_PARAM_CSTRING, 1, "(Sweden)");
    }
    else
    {
        works.setFilterState("school_Swedish", true);
        TwSetParam(myBar, "school_Swedish", "label", TW_PARAM_CSTRING, 1, "Sweden");
    }
    pushVisualChanges();
}
void TW_CALL Callb_school_Swiss(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("school_Swiss");
    if (stateCheck)
    {
        works.setFilterState("school_Swiss", false);
        TwSetParam(myBar, "school_Swiss", "label", TW_PARAM_CSTRING, 1, "(Switzerland)");
    }
    else
    {
        works.setFilterState("school_Swiss", true);
        TwSetParam(myBar, "school_Swiss", "label", TW_PARAM_CSTRING, 1, "Switzerland");
    }
   pushVisualChanges();
}
void TW_CALL Callb_form_tapestry(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_tapestry");
    if (stateCheck)
    {
        works.setFilterState("form_tapestry", false);
        TwSetParam(myBar, "form_tapestry", "label", TW_PARAM_CSTRING, 1, "(Tapestry)");
    }
    else
    {
        works.setFilterState("form_tapestry", true);
        TwSetParam(myBar, "form_tapestry", "label", TW_PARAM_CSTRING, 1, "Tapestry)");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_stained_glass(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_stained-glass");
    if (stateCheck)
    {
        works.setFilterState("form_stained-glass", false);
        TwSetParam(myBar, "form_stained-glass", "label", TW_PARAM_CSTRING, 1, "(Stained Glass)");
    }
    else
    {
        works.setFilterState("form_stained-glass", true);
        TwSetParam(myBar, "form_stained-glass", "label", TW_PARAM_CSTRING, 1, "Stained Glass)");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_sculpture(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_sculpture");
    if (stateCheck)
    {
        works.setFilterState("form_sculpture", false);
        TwSetParam(myBar, "form_sculpture", "label", TW_PARAM_CSTRING, 1, "(Sculpture)");
    }
    else
    {
        works.setFilterState("form_sculpture", true);
        TwSetParam(myBar, "form_sculpture", "label", TW_PARAM_CSTRING, 1, "Sculpture");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_painting(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_painting");
    if (stateCheck)
    {
        works.setFilterState("form_painting", false);
        TwSetParam(myBar, "form_painting", "label", TW_PARAM_CSTRING, 1, "(Painting)");
    }
    else
    {
        works.setFilterState("form_painting", true);
        TwSetParam(myBar, "form_painting", "label", TW_PARAM_CSTRING, 1, "Painting");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_others(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_others");
    if (stateCheck)
    {
        works.setFilterState("form_others", false);
        TwSetParam(myBar, "form_others", "label", TW_PARAM_CSTRING, 1, "(Others)");
    }
    else
    {
        works.setFilterState("form_others", true);
        TwSetParam(myBar, "form_others", "label", TW_PARAM_CSTRING, 1, "Others");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_mosaic(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_mosaic");
    if (stateCheck)
    {
        works.setFilterState("form_mosaic", false);
        TwSetParam(myBar, "form_mosaic", "label", TW_PARAM_CSTRING, 1, "(Mosaic)");
    }
    else
    {
        works.setFilterState("form_mosaic", true);
        TwSetParam(myBar, "form_mosaic", "label", TW_PARAM_CSTRING, 1, "Mosaic");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_metalwork(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_metalwork");
    if (stateCheck)
    {
        works.setFilterState("form_metalwork", false);
        TwSetParam(myBar, "form_metalwork", "label", TW_PARAM_CSTRING, 1, "(Metalwork)");
    }
    else
    {
        works.setFilterState("form_metalwork", true);
        TwSetParam(myBar, "form_metalwork", "label", TW_PARAM_CSTRING, 1, "Metalwork");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_illumination(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_illumination");
    if (stateCheck)
    {
        works.setFilterState("form_illumination", false);
        TwSetParam(myBar, "form_illumination", "label", TW_PARAM_CSTRING, 1, "(Illumination)");
    }
    else
    {
        works.setFilterState("form_illumination", true);
        TwSetParam(myBar, "form_illumination", "label", TW_PARAM_CSTRING, 1, "Illumination");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_graphics(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_graphics");
    if (stateCheck)
    {
        works.setFilterState("form_graphics", false);
        TwSetParam(myBar, "form_graphics", "label", TW_PARAM_CSTRING, 1, "(Graphics)");
    }
    else
    {
        works.setFilterState("form_graphics", true);
        TwSetParam(myBar, "form_graphics", "label", TW_PARAM_CSTRING, 1, "Graphics");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_glassware(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_glassware");
    if (stateCheck)
    {
        works.setFilterState("form_glassware", false);
        TwSetParam(myBar, "form_glassware", "label", TW_PARAM_CSTRING, 1, "(Glassware)");
    }
    else
    {
        works.setFilterState("form_glassware", true);
        TwSetParam(myBar, "form_glassware", "label", TW_PARAM_CSTRING, 1, "Glassware");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_furniture(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_furniture");
    if (stateCheck)
    {
        works.setFilterState("form_furniture", false);
        TwSetParam(myBar, "form_furniture", "label", TW_PARAM_CSTRING, 1, "(Furniture)");
    }
    else
    {
        works.setFilterState("form_furniture", true);
        TwSetParam(myBar, "form_furniture", "label", TW_PARAM_CSTRING, 1, "Furniture");
    }
    pushVisualChanges();
}
void TW_CALL Callb_form_ceramics(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_ceramics");
    if (stateCheck)
    {
        works.setFilterState("form_ceramics", false);
        TwSetParam(myBar, "form_ceramics", "label", TW_PARAM_CSTRING, 1, "(Ceramics)");
    }
    else
    {
        works.setFilterState("form_ceramics", true);
        TwSetParam(myBar, "form_ceramics", "label", TW_PARAM_CSTRING, 1, "Ceramics");
    }
   pushVisualChanges();
}
void TW_CALL Callb_form_architecture(void * /*clientData*/)
{
    bool stateCheck = works.getFilterState("form_architecture");
    if (stateCheck)
    {
        works.setFilterState("form_architecture", false);
        TwSetParam(myBar, "form_architecture", "label", TW_PARAM_CSTRING, 1, "(Architecture)");
    }
    else
    {
        works.setFilterState("form_architecture", true);
        TwSetParam(myBar, "form_architecture", "label", TW_PARAM_CSTRING, 1, "Architecture");
    }
    pushVisualChanges();
}

void initTweakbar(void)
{
    TwInit(TW_OPENGL_CORE, NULL);
    TwWindowSize(mainWinWidth, mainWinHeight);

    myBar = TwNewBar("Filters");
    int paramVal1 = 1;
    TwSetParam(myBar, NULL, "iconified", TW_PARAM_INT32, 1, &paramVal1);
    int paramVal2[] = {250,300};
    TwSetParam(myBar, NULL, "size", TW_PARAM_INT32, 2, &paramVal2);
    paramVal1 = 1;
    TwSetParam(myBar, NULL, "resizable", TW_PARAM_INT32, 1, &paramVal1);
    paramVal1 = 3;
    TwSetParam(NULL, NULL, "fontsize", TW_PARAM_INT32, 1, &paramVal1);

    TwAddButton(myBar, "school_Austrian", Callb_school_Austrian, NULL, " group='School' label='Austria' ");
    TwAddButton(myBar, "school_Belgian", Callb_school_Belgian, NULL, " group='School' label='Belgium' ");
    TwAddButton(myBar, "school_Bohemian", Callb_school_Bohemian, NULL, " group='School' label='Bohemia' ");
    TwAddButton(myBar, "school_Catalan", Callb_school_Catalan, NULL, " group='School' label='Catalonia' ");
    TwAddButton(myBar, "school_Danish", Callb_school_Danish, NULL, " group='School' label='Denmark' ");
    TwAddButton(myBar, "school_Dutch", Callb_school_Dutch, NULL, " group='School' label='Holland' ");
    TwAddButton(myBar, "school_English", Callb_school_English, NULL, " group='School' label='England' ");
    TwAddButton(myBar, "school_Finnish", Callb_school_Finnish, NULL, " group='School' label='Finland' ");
    TwAddButton(myBar, "school_Flemish", Callb_school_Flemish, NULL, " group='School' label='Flanders' ");
    TwAddButton(myBar, "school_French", Callb_school_French, NULL, " group='School' label='France' ");
    TwAddButton(myBar, "school_German", Callb_school_German, NULL, " group='School' label='Germany' ");
    TwAddButton(myBar, "school_Greek", Callb_school_Greek, NULL, " group='School' label='Greece' ");
    TwAddButton(myBar, "school_Hungarian", Callb_school_Hungarian, NULL, " group='School' label='Hungary' ");
    TwAddButton(myBar, "school_Irish", Callb_school_Irish, NULL, " group='School' label='Ireland' ");
    TwAddButton(myBar, "school_Italian", Callb_school_Italian, NULL, " group='School' label='Italy' ");
    TwAddButton(myBar, "school_Netherlandish", Callb_school_Netherlandish, NULL, " group='School' label='Netherlands' ");
    TwAddButton(myBar, "school_Norwegian", Callb_school_Norwegian, NULL, " group='School' label='Norway' ");
    TwAddButton(myBar, "school_Polish", Callb_school_Polish, NULL, " group='School' label='Poland' ");
    TwAddButton(myBar, "school_Portuguese", Callb_school_Portuguese, NULL, " group='School' label='Portugal' ");
    TwAddButton(myBar, "school_Russian", Callb_school_Russian, NULL, " group='School' label='Russia' ");
    TwAddButton(myBar, "school_Scottish", Callb_school_Scottish, NULL, " group='School' label='Scotland' ");
    TwAddButton(myBar, "school_Spanish", Callb_school_Spanish, NULL, " group='School' label='Spain' ");
    TwAddButton(myBar, "school_Swedish", Callb_school_Swedish, NULL, " group='School' label='Sweden' ");
    TwAddButton(myBar, "school_Swiss", Callb_school_Swiss, NULL, " group='School' label='Switzerland' ");

    TwAddButton(myBar, "type_genre", Callb_type_genre, NULL, " group='Type' label='Genre' ");
    TwAddButton(myBar, "type_historical", Callb_type_historical, NULL, " group='Type' label='Historical' ");
    TwAddButton(myBar, "type_interior", Callb_type_interior, NULL, " group='Type' label='Interior' ");
    TwAddButton(myBar, "type_landscape", Callb_type_landscape, NULL, " group='Type' label='Landscape' ");
    TwAddButton(myBar, "type_mythological", Callb_type_mythological, NULL, " group='Type' label='Mythological' ");
    TwAddButton(myBar, "type_other", Callb_type_other, NULL, " group='Type' label='Other' ");
    TwAddButton(myBar, "type_portrait", Callb_type_portrait, NULL, " group='Type' label='Portrait' ");
    TwAddButton(myBar, "type_religious", Callb_type_religious, NULL, " group='Type' label='Religious' ");
    TwAddButton(myBar, "type_still-life", Callb_type_still_life, NULL, " group='Type' label='Still-Life' ");
    TwAddButton(myBar, "type_study", Callb_type_study, NULL, " group='Type' label='Study' ");

    TwAddButton(myBar, "form_architecture", Callb_form_architecture, NULL, " group='Form' label='Architecture' ");
    TwAddButton(myBar, "form_ceramics", Callb_form_ceramics, NULL, " group='Form' label='Ceramics' ");
    TwAddButton(myBar, "form_furniture", Callb_form_furniture, NULL, " group='Form' label='Furniture' ");
    TwAddButton(myBar, "form_glassware", Callb_form_glassware, NULL, " group='Form' label='Glassware' ");
    TwAddButton(myBar, "form_graphics", Callb_form_graphics, NULL, " group='Form' label='Graphics' ");
    TwAddButton(myBar, "form_illumination", Callb_form_illumination, NULL, " group='Form' label='Illumination' ");
    TwAddButton(myBar, "form_metalwork", Callb_form_metalwork, NULL, " group='Form' label='Metalwork' ");
    TwAddButton(myBar, "form_mosaic", Callb_form_mosaic, NULL, " group='Form' label='Mosaic' ");
    TwAddButton(myBar, "form_others", Callb_form_others, NULL, " group='Form' label='Others' ");
    TwAddButton(myBar, "form_painting", Callb_form_painting, NULL, " group='Form' label='Painting' ");
    TwAddButton(myBar, "form_sculpture", Callb_form_sculpture, NULL, " group='Form' label='Sculpture' ");
    TwAddButton(myBar, "form_stained-glass", Callb_form_stained_glass, NULL, " group='Form' label='Stained Glass' ");
    TwAddButton(myBar, "form_tapestry", Callb_form_tapestry, NULL, " group='Form' label='Tapestry' ");

    paramVal1 = 0;
    TwSetParam(myBar, "School", "opened", TW_PARAM_INT32, 1, &paramVal1);
    TwSetParam(myBar, "Type", "opened", TW_PARAM_INT32, 1, &paramVal1);

    myOtherBar = TwNewBar("Parameters");
    paramVal1 = 1;
    TwSetParam(myOtherBar, NULL, "iconified", TW_PARAM_INT32, 1, &paramVal1);
    paramVal2[0] = 230; paramVal2[1] = 200;
    TwSetParam(myOtherBar, NULL, "size", TW_PARAM_INT32, 2, &paramVal2);
    paramVal2[0] = 620; paramVal2[1] = 10;
    TwSetParam(myOtherBar, NULL, "position", TW_PARAM_INT32, 2, &paramVal2);
    paramVal1 = 1;
    TwSetParam(myOtherBar, NULL, "resizable", TW_PARAM_INT32, 1, &paramVal1);
    paramVal1 = 0;
    TwAddVarRW(myOtherBar, "bgClearColor", TW_TYPE_COLOR3F, &bgClearColor, " group='Display' label='Background color' ");

    TwSetParam(myOtherBar, "Display", "opened", TW_PARAM_INT32, 1, &paramVal1);

}

#endif
