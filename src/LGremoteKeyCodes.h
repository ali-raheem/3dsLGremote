#pragma once

#define LG_POWER        1
#define LG_NUM_0        2
#define LG_NUM_1        3
#define LG_NUM_2        4
#define LG_NUM_3        5
#define LG_NUM_4        6
#define LG_NUM_5        7
#define LG_NUM_6        8
#define LG_NUM_7        9
#define LG_NUM_8        10
#define LG_NUM_9        11
#define LG_UP   12
#define LG_DOWN         13
#define LG_LEFT         14
#define LG_RIGHT        15
#define LG_OK   20
#define LG_HOME         21
#define LG_MENU         22
#define LG_BACK         23
#define LG_VOLUME_UP    24
#define LG_VOLUME_DOWN  25
#define LG_MUTE         26
#define LG_CHANNEL_UP   27
#define LG_CHANNEL_DOWN         28
#define LG_BLUE         29
#define LG_GREEN        30
#define LG_RED  31
#define LG_YELLOW       32
#define LG_PLAY         33
#define LG_PAUSE        34
#define LG_STOP         35
#define LG_FF   36
#define LG_REW  37
#define LG_SKIP_FF      38
#define LG_SKIP_REW     39
#define LG_REC  40
#define LG_REC_LIST     41
#define LG_LIVE         43
#define LG_EPG  44
#define LG_INFO         45
#define LG_ASPECT       46
#define LG_EXT  47
#define LG_PIP  48
#define LG_SUBTITLE     49
#define LG_PROGRAM_LIST         50
#define LG_TEXT         51
#define LG_MARK         52
#define LG_3D   400
#define LG_3D_LR        401
#define LG_DASH         402
#define LG_PREV         403
#define LG_FAV  404
#define LG_QUICK_MENU   405
#define LG_TEXT_OPTION  406
#define LG_AUDIO_DESC   407
#define LG_NETCAST      408
#define LG_ENERGY_SAVE  409
#define LG_AV   410
#define LG_SIMPLINK 411
#define LG_EXIT 412
#define LG_RESERVED     413
#define LG_PIP_CHANNEL_UP       414
#define LG_PIP_CHANNEL_DOWN     415
#define LG_PIP_SWITCH   416
#define LG_APPS         417

const char * LGKeyName[] = {
"POWER",
"NUM_0",
"NUM_1",
"NUM_2",
"NUM_3",
"NUM_4",
"NUM_5",
"NUM_6",
"NUM_7",
"NUM_8",
"NUM_9",
"UP",
"DOWN",
"LEFT",
"RIGHT",
"OK",
"HOME",
"MENU",
"BACK",
"VOLUME_UP",
"VOLUME_DOWN",
"MUTE",
"CHANNEL_UP",
"CHANNEL_DOWN",
"BLUE",
"GREEN",
"RED",
"YELLOW",
"PLAY",
"PAUSE",
"STOP",
"FF",
"REW",
"SKIP_FF",
"SKIP_REW",
"REC",
"REC_LIST",
"LIVE",
"EPG",
"INFO",
"ASPECT",
"EXT",
"PIP",
"SUBTITLE",
"PROGRAM_LIST",
"TEXT",
"MARK",
"3D",
"3D_LR",
"DASH",
"PREV",
"FAV",
"QUICK_MENU",
"TEXT_OPTION",
"AUDIO_DESC",
"NETCAST",
"ENERGY_SAVE",
"AV",
"SIMPLINK",
"EXIT",
"RESERVED",
"PIP_CHANNEL_UP",
"PIP_CHANNEL_DOWN",
"PIP_SWITCH",
"APPS"};

const u32 LGKeyCode[] = {
1,
2,
3,
4,
5,
6,
7,
8,
9,
10,
11,
12,
13,
14,
15,
20,
21,
22,
23,
24,
25,
26,
27,
28,
29,
30,
31,
32,
33,
34,
35,
36,
37,
38,
39,
40,
41,
43,
44,
45,
46,
47,
48,
49,
50,
51,
52,
400,
401,
402,
403,
404,
405,
406,
407,
408,
409,
410,
411,
412,
413,
414,
415,
416,
417};

u32 LGKeyIndex = 0;
const u32 LGKeyCount = 64;
