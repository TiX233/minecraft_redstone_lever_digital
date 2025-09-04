#ifndef __RS_LINE_H__
#define __RS_LINE_H__

#include "redstone.h"

typedef enum {
    RS_LEVER_CH1_up = 0,
    RS_LEVER_CH2_down,
    RS_LEVER_CH3_left,
    RS_LEVER_CH4_right,

    RS_LEVER_CH_NUM,
} rs_lever_chs_e;

struct rs_lever_stu {
    void (*led_pin_write)(uint8_t pin_state);
    uint8_t (*button_pin_read)(void);

    struct rs_io_stu io;
};


void rs_lever_init(struct rs_lever_stu *rsl);

uint8_t my_rs_io_pin_read(struct rs_channel_stu *ch);
void my_rs_io_pin_write(struct rs_channel_stu *ch, uint8_t pin_state);

void my_rs_io_callback_channel_change(struct rs_io_stu *io);
void my_rs_io_callback_communication_init(struct rs_io_stu *io);
void my_rs_io_callback_communication_over(struct rs_io_stu *io);

void my_rs_lever_led_pin_write(uint8_t pin_state);
uint8_t my_rs_lever_button_pin_read(void);

#endif // __RS_LINE_H__
