decisionEng::decisionEng(field State *_state)
{ 
 state = _state;
}

void decisionEng::supplyMessage(uint8_t mask)
{
 bool *i = &mask;
 state->new1 = *i;
 i++;
 state->new2 = *i;
 i++;
 state->new3 = *i;
 i++;
 state->new4 = *i;
}

void decisionEng::spentMessage(uint8_t mask)
{
 bool *i = &mask;
 state->spent1 = *i;
 i++;
 state->spent2 = *i;
 i++;
 state->spent3 = *i;
 i++;
 state->spent4 = *i;
}

