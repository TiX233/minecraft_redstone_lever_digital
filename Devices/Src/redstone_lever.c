#include "redstone_lever.h"
#include "myTasks.h"

void rs_lever_init(struct rs_lever_stu *rsl){
    for(uint8_t i = 0; i < RS_LEVER_CH_NUM; i ++){
        rsl->io.pin_write(&(rsl->io.channels[i]), 1);
    }

    for(uint8_t i = 0; i < RS_LEVER_CH_NUM; i ++){
        for(uint8_t j = 0; j < RS_CHANNEL_STEP_max; j ++){
            rsl->io.channels[i].pin_script[j] = 1;
        }
    }
    rsl->led_pin_write(1);
}

uint8_t my_rs_io_pin_read(struct rs_channel_stu *ch){
    return HAL_GPIO_ReadPin(ch->pin.port, ch->pin.pin);
}

void my_rs_io_pin_write(struct rs_channel_stu *ch, uint8_t pin_state){
    HAL_GPIO_WritePin(ch->pin.port, ch->pin.pin, pin_state);
}

static uint8_t flag_output;
void my_rs_io_callback_communication_init(struct rs_io_stu *io){
    // 设置引脚通信脚本
    if(my_rs_lever.button_pin_read()){ // 按键松开，不输出信号，熄灭 led
        for(uint8_t i = 0; i < RS_LEVER_CH_NUM; i ++){
            for(uint8_t j = RS_CHANNEL_STEP_3_set_r16; j < RS_CHANNEL_STEP_19_set_ack; j ++){
                my_rs_lever.io.channels[i].pin_script[j] = 1;
            }
        }

        // my_rs_lever.led_pin_write(1);
        flag_output = 0;
    }else { // 按键按下，输出强度为 16 的信号，点亮 led
        for(uint8_t i = 0; i < RS_LEVER_CH_NUM; i ++){
            for(uint8_t j = RS_CHANNEL_STEP_3_set_r16; j < RS_CHANNEL_STEP_19_set_ack; j ++){
                my_rs_lever.io.channels[i].pin_script[j] = 0;
            }
        }

        // my_rs_lever.led_pin_write(0);
        flag_output = 1;
    }

    // 确保 1ms 后再进入通信
    task_rs_io.topic.flag = 0;
}

void my_rs_io_callback_channel_change(struct rs_io_stu *io){
    // 没有事情需要做
}

void my_rs_io_callback_communication_over(struct rs_io_stu *io){
    my_rs_lever.led_pin_write(!flag_output);
}


void my_rs_lever_led_pin_write(uint8_t pin_state){
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, pin_state);
}

uint8_t my_rs_lever_button_pin_read(void){
    return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
}
