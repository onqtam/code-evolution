/******************************************************************************
 *                                                                            *
 *  POP SHOTS.                                                                *
 *                                                                            *
 *  Technological School Electronic Systems                                   *
 *  Technical University of Sofia                                             *
 *                                                                            *
 *  Copyright (C) 2009-2010 Viktor Kirilov ( n1ntendo@abv.bg )                *
 *                                                                            *
 ******************************************************************************/

#ifndef DEBUG
#define DEBUG

#include <stdio.h>

/**
 * used for easy printing (for debugging mainly)
 * usage:    PRINT(hello)
 */
#define PRINT(message) fprintf(stderr,#message"\n");



#endif
