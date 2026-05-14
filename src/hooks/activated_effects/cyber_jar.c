#include "global.h"
#include "common-chax.h"

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
        u8 handSize = 0;

        for (k = 0; k < MAX_ZONES_IN_ROW; k++)
            if (gDuel.hands[turn][k].id != CARD_NONE)
                handSize++;

        while (handSize < 5)
        {
            u16 drawnCard;

            if (gDuelDecks[turn].cardsDrawn >= NumCardsInDeck(turn))
            {
                DeclareLoser(turn);
                break;
            }
            drawnCard = gDuelDecks[turn].cards[gDuelDecks[turn].cardsDrawn];
            gDuelDecks[turn].cardsDrawn++;

            for (k = 0; k < MAX_ZONES_IN_ROW; k++)
                if (gDuel.hands[turn][k].id == CARD_NONE)
                {
                    gDuel.hands[turn][k].id = drawnCard;
                    handSize++;
                    break;
                }
        }
    }

    if (!gHideEffectText)
    {
        gCardEffectTextData.cardId = CYBER_JAR;
        ActivateCardEffectText();
    }
}
