#ifndef STAGES_H
#define STAGES_H


extern const int InvalidScene(struct GameOption *option);

extern const int PrologueScene(struct GameOption *option);

extern const int BreakChainScene(struct GameOption *option);
extern const int StayInPlaceScene(struct GameOption *option);
extern const int FaustIntroductionScene(struct GameOption *option);
extern const int FaustRejectScene(struct GameOption *option);
extern const int FaustKillScene(struct GameOption *option);
extern const int FaustPraiseScene(struct GameOption *option);

extern const int BattleScene(struct GameOption *option);
extern const int VictoryScene(struct GameOption *option);
extern const int DefeatedScene(struct GameOption *option);

extern const int EpilogueScene(struct GameOption *option);

#endif
