//
//  definitions.h
//  canyon-flight
//
//  Created by Santhos Baala RS on 09/03/15.
//
//

#ifndef canyon_flight_definitions_h
#define canyon_flight_definitions_h

#define SCALE_640_WIDTH(x, width) (((x) / 640.0f) * width)
#define SCALE_960_HEIGHT(y, height) (((y) / 960.0f) * height)
#define SCALE_960_HEIGHT_INVERSE(value, height) (((value) * (960)) / (height))

#define CLIFF_COLLISION_MASK 0x000001
#define CIRCLE_COLLISION_MASK 0x000002

#define TTF_FONT_FILE "zorque.ttf"
#define SCORE_LABEL_SCALE 0.075

#define MAX_CLIFF_SPAWN_RATE 0.225
#define MIN_CLIFF_SPAWN_RATE 0.125


#endif
