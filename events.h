#ifndef EVENTS_H
#define EVENTS_H


extern const int EventDispatcher(struct GameOption *option);


extern const int EncounterGhostEvent(struct GameOption *option);


typedef int GameStage(struct GameOption *option);

struct EventType {
    char name[20];
    char description[100];
    GameStage *instances[10];
};

#endif
