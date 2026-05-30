#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"

void __attribute__((section(".append_text"))) EffectCyberJar(void)
{
    u8 i, k;
    u8 activeTurn = WhoseTurn();
    u8 inactiveTurn = 1 - activeTurn;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    {
        if (gTurnZones[1][i]->id != CARD_NONE)
            ClearZoneAndSendMonToGraveyard(gTurnZones[1][i], INACTIVE_DUELIST);
        if (gTurnZones[2][i]->id != CARD_NONE)
            ClearZoneAndSendMonToGraveyard(gTurnZones[2][i], ACTIVE_DUELIST);
    }

    for (i = 0; i < 2; i++)
    {
        u8 turn = (i == 0) ? activeTurn : inactiveTurn;
        struct DuelCard **monsterRow = (i == 0) ? gTurnZones[2] : gTurnZones[1];
        u8 handSize = 0;
        u8 drawn = 0;

        for (k = 0; k < MAX_ZONES_IN_ROW; k++)
            if (gDuel.hands[turn][k].id != CARD_NONE)
                handSize++;

        while (handSize < 5)
        {
            u16 drawnCard;
            s8 emptyZone;

            if (gDuelDecks[turn].cardsDrawn >= NumCardsInDeck(turn))
            {
                DeclareLoser(turn);
                break;
            }
            drawnCard = gDuelDecks[turn].cards[gDuelDecks[turn].cardsDrawn];
            gDuelDecks[turn].cardsDrawn++;

            SetCardInfo(drawnCard);
            emptyZone = FirstEmptyZoneInRow(monsterRow);

            if (GetTypeGroup(drawnCard) == TYPE_GROUP_MONSTER
                && gCardInfo.level >= 1 && gCardInfo.level <= 4
                && NumEmptyZonesInRow(monsterRow) > 0)
            {
                monsterRow[emptyZone]->id = drawnCard;
                monsterRow[emptyZone]->isFaceUp = TRUE;
                monsterRow[emptyZone]->isLocked = TRUE;
                monsterRow[emptyZone]->isDefending = FALSE;
                monsterRow[emptyZone]->permStage = 0;
                monsterRow[emptyZone]->tempStage = 0;
                monsterRow[emptyZone]->unk4 = 0;
                monsterRow[emptyZone]->unkTwo = 0;
                monsterRow[emptyZone]->willChangeSides = 0;
            }
            else
            {
                for (k = 0; k < MAX_ZONES_IN_ROW; k++)
                    if (gDuel.hands[turn][k].id == CARD_NONE)
                    {
                        gDuel.hands[turn][k].id = drawnCard;
                        handSize++;
                        break;
                    }
            }
            drawn++;
            if (drawn >= 10)
                break;
        }
    }

    RecalculateAllDynamicEquips();

    if (!gHideEffectText)
    {
        gCardEffectTextData.cardId = CYBER_JAR;
        ActivateCardEffectText();
    }
}
