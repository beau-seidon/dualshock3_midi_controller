#pragma once

#include "diatonic_intervals.h"



struct DiatonicMode {
    const int ionian[8] =     {P1, M2, M3, P4, P5, M6, M7, P8};   // 0                    w w h w w w h
    const int dorian[8] =     {P1, M2, m3, P4, P5, M6, m7, P8};   // b7, b3               w h w w w h w
    const int phrygian[8] =   {P1, m2, m3, P4, P5, m6, m7, P8};   // b7, b3, b6, b2       h w w w h w w
    const int lydian[8] =     {P1, M2, M3, TT, P5, M6, M7, P8};   // #4                   w w w h w w h
    const int mixolydian[8] = {P1, M2, M3, P4, P5, M6, m7, P8};   // b7                   w w h w w h w
    const int aeolian[8] =    {P1, M2, m3, P4, P5, m6, m7, P8};   // b7, b3, b6           w h w w h w w 
    const int locrian[8] =    {P1, m2, m3, P4, TT, m6, m7, P8};   // b7, b3, b6, b2, b5   h w w h w w w
};
