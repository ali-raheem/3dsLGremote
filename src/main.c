#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include <3ds.h>

#include "LGremote.h"
#include "LGremoteKeyCodes.h"

#include "bottom_bin.h"

#include "http.h"
#include "config.h"

const size_t MAX_BODY_LEN = 512;
const size_t MAX_URL_LEN = 64;
u32 host_key[6] = {0,0,0,0,0,8080};
u32 host_key_selected = 0;
u32 MODE = 0;

int main(){
  Result ret = 0;
  gfxInitDefault();
  httpcInit(4 * 1024 * 1024);
  char body[MAX_BODY_LEN];
  u32 kDown, kHeld;
  circlePosition pos;
  touchPosition touch;
  char host[32];
  char key[7];
  char url[MAX_URL_LEN];

  consoleInit(GFX_TOP, NULL);
  gfxSetDoubleBuffering(GFX_BOTTOM, false);

  u8 *fb = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
  memcpy(fb, bottom_bin, bottom_bin_size);

  puts("Connecting to TV");
  puts("Circle Pad to move mouse\nL shoulder to click");
  puts("D-pad for directional movement");
  puts("X - Apps");
  puts("Y - Home");
  puts("A - Back");
  puts("B - OK");
  puts("");
  puts("Holding R shoulder");
  puts("X - Power");
  puts("D-up - Volume up");
  puts("D-down - Volume down");
  puts("L shoulder - Toggle Settings Mode");
  puts("In Settings Mode");
  puts("D-Left/Right - Cycle through whats being set");
  puts("Numpad to set numbers, green to auth, red to clear value.");
  puts("");
  puts("IF YOU ARE IP SETTINGS ARE WRONG TIME OUT WILL TAKE AGES. TURN OFF WIFI UNTIL YOU HAVE SET THEM!!");
  ret = readConfigFile(&url, MAX_URL_LEN);
  if(ret == 1) {
    ret = parseConfig(url, host, key);
  }

  puts("Trying to show key");
  snprintf(url, MAX_URL_LEN, "http://%s%s", host, authURL);
  ret = http_post(url, reqKey);

  puts("Trying to auth");
  snprintf(body, MAX_BODY_LEN, authKey, key);
  http_post(url, body);

  puts("Ready to play...");
  snprintf(url, MAX_URL_LEN, "http://%s%s", host, cmdURL);

  while (aptMainLoop()){
    gspWaitForVBlank();

    hidScanInput();
    hidCircleRead(&pos);
    hidTouchRead(&touch);
    kDown = hidKeysDown();
    kHeld = hidKeysHeld();

    if (kHeld & KEY_R && kDown & KEY_L) {
      MODE = !MODE;
      puts(MODE?"SETTINGS MODE":"CONTROL MODE");
    }
    if(MODE){
      if (kDown & KEY_DRIGHT)
        if (host_key_selected < 5)
          host_key_selected++;
      if (kDown & KEY_DLEFT)
        if (host_key_selected > 0)
          host_key_selected--;
      if (kDown & KEY_TOUCH) {
        if (touch.px < 180) {
          u32 tmp = (touch.px/60 + 3 * (touch.py/60)) + 1;
          if (tmp == 11) {
            tmp = 0;
          }else if (tmp == 10) {
            snprintf(url, MAX_URL_LEN, "%u@%u.%u.%u.%u:%u", host_key[0], host_key[1],
                     host_key[2], host_key[3], host_key[4], host_key[5]);
            parseConfig(url, host, key);
            snprintf(body, MAX_BODY_LEN, authKey, key);
            http_post(url, body);
            snprintf(url, MAX_URL_LEN, "http://%s%s", host, cmdURL);
            MODE = !MODE;
            saveConfigFile(host, key);
            puts("Saving config...");
          }else if (tmp == 12) {
            host_key[host_key_selected] = 0;
          }
          if(tmp < 10) {
            host_key[host_key_selected] *= 10;
            host_key[host_key_selected] += tmp;
          }
        }
      }
      if(kDown){
        printf("Setting %u\n", host_key_selected);
        u32 i;
        puts("KEY@IP.IP.IP.IP:PORT");
        for(i = 0; i < 6; i++)
          printf(i == host_key_selected?"****":"   ");
        puts("");
        printf("%06u@%03u.%03u.%03u.%03u:%u\n", host_key[0], host_key[1], host_key[2],
               host_key[3], host_key[4], host_key[5]);
      }

    }else{
      if (kHeld & KEY_R) {
        if (kDown & KEY_DUP) {
          snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_VOLUME_UP);
          http_post(url, body);
        }
        else if (kDown & KEY_DDOWN) {
          snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_VOLUME_DOWN);
          http_post(url, body);
        }
        else if (kDown & KEY_X) {
          snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_POWER);
          http_post(url, body);
        }
        else if (kDown & KEY_Y) {
          snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_EXIT);
          http_post(url, body);
        }
        else if (kDown & KEY_A) {
          snprintf(body, MAX_BODY_LEN, authKey, key);
          http_post(url, body);
          snprintf(url, MAX_URL_LEN, "http://%s%s", host, cmdURL);
        }
        else if (kDown & KEY_DLEFT) {
          if(LGKeyIndex < LGKeyCount)
            LGKeyIndex++;
          puts(LGKeyName[LGKeyIndex]);
        }
        else if (kDown & KEY_DRIGHT) {
          if(LGKeyIndex > 0)
            LGKeyIndex--;
          puts(LGKeyName[LGKeyIndex]);
      }
      else if (kDown & KEY_B) {
        snprintf(body, MAX_BODY_LEN, handleKeyInput, LGKeyCode[LGKeyIndex]);
        http_post(url, body);
      }
    }
    //    else if (kDown & KEY_TOUCH) {
    //nothing.
    //      puts("");
    //    }
    else if (kDown & KEY_TOUCH) {
      if (touch.px < 180) {
        u32 tmp = (touch.px/60 + 3 * (touch.py/60)) + 1;
//        printf("Guessing you touched: %i tap at x: %04u, y: %04u\n", tmp, touch.px, touch.py);
        if (tmp < 10) {
          tmp += LG_NUM_0;
        }else if(tmp == 10){
          tmp = LG_OK;
          }else if(tmp == 11){
          tmp = LG_NUM_0;
        }else if (tmp == 12){
          tmp = LG_BACK;
          }
        snprintf(body, MAX_BODY_LEN, handleKeyInput, tmp);
        http_post(url, body);
      }
    }
    else if (pos.dx > 15 || pos.dx < -15 || pos.dy > 15 || pos.dy < -15) {
      snprintf(body, MAX_BODY_LEN, handleTouchMove, pos.dx, -pos.dy);
      http_post(url, body);
    }
    else if (kDown & KEY_L) {
      http_post(url, handleTouchClick);
    }
    else if (kDown & KEY_DUP) {
      snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_UP);
      http_post(url, body);
    }
    else if (kDown & KEY_DDOWN) {
      snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_DOWN);
      http_post(url, body);
    }
    else if (kDown & KEY_DLEFT) {
      snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_LEFT);
      http_post(url, body);
    }
    else if (kDown & KEY_DRIGHT) {
      snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_RIGHT);
      http_post(url, body);
    }
    else if (kDown & KEY_B) {
      snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_OK);
      http_post(url, body);
    }
    else if (kDown & KEY_A) {
      snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_BACK);
      http_post(url, body);
    }
    else if (kDown & KEY_Y) {
      snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_HOME);
      http_post(url, body);
    }
    else if (kDown & KEY_X) {
      snprintf(body, MAX_BODY_LEN, handleKeyInput, LG_APPS);
      http_post(url, body);
    }
    else if (kDown & KEY_START) {
      break;
    }
  }
  }
  httpcExit();
  gfxExit();
  return 0;
}

