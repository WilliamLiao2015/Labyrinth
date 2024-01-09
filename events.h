#ifndef EVENTS_H
#define EVENTS_H


extern const int EventDispatcher(struct GameOption *option);
extern const int EncounterPlayerEvent(struct GameOption *option);

extern const int EncounterGhostEvent(struct GameOption *option);
extern const int GetTreasureEvent(struct GameOption *option);
extern const int EncounterBeastEvent(struct GameOption *option);
extern const int GetExperienceBottleEvent(struct GameOption *option);
extern const int EncounterMarketEvent(struct GameOption *option);

typedef int GameStage(struct GameOption *option);

struct EventType {
    char name[20];
    char description[100];
    GameStage *instances[10];
};

#endif
