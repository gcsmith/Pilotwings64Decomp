#ifndef APP_BALL_TARGET_H
#define APP_BALL_TARGET_H

#include <PR/ultratypes.h>

// initialize the ball target module
void ballTgtInit(void);

// updates ball target dobj state based on terrain loaded
void ballTgtUpdateState(void);

// parses run-time ball target structs from BTGT filesystem data
void ballTgtLoad(void);

// determines if any of the balls have entered any of the ball targets
// this is determined by the ball distance, ball size, goal size
// if any ball has entered a goal, plays *gong* sfx and returns TRUE
// otherwise, returns FALSE
s32 ballTgtInGoal(void);

// deinitialize the ball target module
void ballTgtDeinit(void);

// get the count of the number of the goals which have a ball in them
u8 ballTgtGetGoalCount(void);

// get the total score from all ball targets. this is computed by adding up
// all the scores for the ball targets that have a ball in them
s16 ballTgtGetScore(void);

#endif // APP_BALL_TARGET_H
