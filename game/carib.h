﻿#ifndef __CARIB_H__
#define __CARIB_H__

#include <gfx.h>
#include <stuff/menu.h>
#include <stuff/anim.h>

const char CaribVersionStr[]="CPoker2 ver. 1.50 A20";

#define BLACK	0x000000
#define BLUE    0x0000FF
#define GREEN   0x00FF00

#define RED 	0xFF0000
#define WHITE   0xFFFFFF

#define GRAY    0x808080
#define YELLOW  0x00FFFF

extern IMAGE intro;

void print(color_t color, const char* format, ... );

// Денежное состояние терминала
#pragma pack(1)
typedef struct
{
    int     game;           // 1 - 1я раздача, 2- 2я, и т.д. 0- начало игры или вне игры (paid==0)
   	uint32  lights;
    int32   credit;
   	int32   win;            
    int32   LastWin;
   	int32   paid;
    int32   ante;           // текущее значение ставки
   	int32   cards[5];       // 0 - карты нет, 1-52 карты, 53 - джокер, 54 - рубашка, +100 - hold
} TerminalState;
#pragma pack()

enum NETWORK_CMD
{
    NCMD_NO_CMD=0,
    NCMD_TERMINAL_KEY,      // пакет содержит код нажатой клавиши
    NCMD_T_UPDATE_STATE,    // Обновление данных терминал
    NCMD_TERMINAL_MONEY // Поступление денег с терминала
};

struct NetworkMsgBase
{
    uint16  from;   // идентификатор (номер) рабочего места
    uint16  to;     // кому (в принципе, слышат все...)
    uint32  cmd;    // код команды
};

// NCMD_T_UPDATE_STATE
struct NetworkMsgTState:NetworkMsgBase
{
    TerminalState tstate;
};

// NCMD_TERMINAL_KEY
struct NetworkMsgTKey:NetworkMsgBase
{
    uint32  key;    // key data for NCMD_TERMINAL_KEY
};

// NCMD_TERMINAL_KEY
struct NetworkMsgTMoney:NetworkMsgBase
{
    uint32  channel;    // data for NCMD_TERMINAL_MONEY
    uint32  value;
};

typedef union _NetworkMsg
{
    NetworkMsgBase      common;
    NetworkMsgTState    state;
    NetworkMsgTKey      key;
    NetworkMsgTMoney    money;
} NetworkMsg;

#endif
