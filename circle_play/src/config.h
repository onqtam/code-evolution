#ifndef __CONFIG_H__
#define __CONFIG_H__

#define COLLECT_ALL_RAYS 0
#define DISPLAY_PROJECTIONS 0

#define USE_BINARY_SEARCH 1
#define MAX_BINARY_SEARCH_DEPTH 10

//set to 1.0 to disable the effect of adaptability (tangent accumulation and calculation will still happen...)
#define ADAPTIVITY_MAX_COEF 1000.0

#define DISTANCE_EPSILON 1e-2

#define SCR_HEIGHT 800
#define SCR_WIDTH SCR_HEIGHT

#endif // __CONFIG_H__
