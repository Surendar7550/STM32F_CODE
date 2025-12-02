/*
 * fsm.h
 *
 *  Created on: Jul 29, 2025
 *      Author: surendar
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

typedef enum {
    STATE_IDLE,
    STATE_SELECTING_PRODUCT,
    STATE_PROCESSING_PAYMENT,
    STATE_DISPENSING_PRODUCT
} FSM_State;

void FSM_Init(void);
void FSM_Update(char input);


#endif /* INC_FSM_H_ */
