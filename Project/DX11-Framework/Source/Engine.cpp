/****************************************************************************/
/*!
\file
   Engine.cpp
\Author
   Ryan Dugie
\brief
    Copyright (c) Ryan Dugie. All rights reserved.
    Licensed under the Apache License 2.0

    Parent class of the entire application
*/
/****************************************************************************/
/*============================================================================*\
|| ------------------------------ INCLUDES ---------------------------------- ||
\*============================================================================*/

#include "DX11PCH.hpp"
#include "Engine.hpp"

/*============================================================================*\
|| --------------------------- GLOBAL VARIABLES ----------------------------- ||
\*============================================================================*/

/*============================================================================*\
|| -------------------------- STATIC FUNCTIONS ------------------------------ ||
\*============================================================================*/

/*============================================================================*\
|| -------------------------- PUBLIC FUNCTIONS ------------------------------ ||
\*============================================================================*/

/****************************************************************************/
/*!
\brief
  Create the engine
*/
/****************************************************************************/
DX11::Engine::Engine() :
    pPreviousTime(glfwGetTime()),
    pStartTime(float(pPreviousTime)),
    pGameLoopIterations(0),
    pFPSCalcInterval(1),
    pDeltaTime(1),
    pFPS(1) {}

/****************************************************************************/
/*!
\brief
  Initialize the engine
*/
/****************************************************************************/
void DX11::Engine::Init()
{
    mWindow = mRenderer.Window(); 
}

/****************************************************************************/
/*!
\brief
  Update the engine
*/
/****************************************************************************/
void DX11::Engine::Run()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        float dt = UpdateDT();
        mRenderer.Draw(dt);
    }
}

/****************************************************************************/
/*!
\brief
  Cleanup
*/
/****************************************************************************/
void DX11::Engine::ShutDown()
{
    mWindow = nullptr;
}

/*============================================================================*\
|| ------------------------- PRIVATE FUNCTIONS ------------------------------ ||
\*============================================================================*/

/****************************************************************************/
/*!
\brief
  Update DT
*/
/****************************************************************************/
float DX11::Engine::UpdateDT()
{
    /* calcualte dt */
    double currentTime = glfwGetTime();
    double deltaTime_ = currentTime - pPreviousTime;
    pPreviousTime = currentTime;

    // get time since start of 1-second interval
    float elapsedTime = float(currentTime - pStartTime);
    ++pGameLoopIterations;

    // after 1 second, calulate fps
    if (elapsedTime > pFPSCalcInterval)
    {
        pFPS = pGameLoopIterations / elapsedTime;
        pStartTime = float(currentTime);
        pGameLoopIterations = 0;
    }

    //return dt
    return float(deltaTime_);
}
