#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include <3ds.h>

#include "LGremote.h"

Result http_post(const char* url, const char* data){
	Result ret=0;
	httpcContext context;
	char *newurl=NULL;
	u32 statuscode=0;
	u32 contentsize=0, readsize=0, size=0;
	u8 *buf, *lastbuf;

		ret = httpcOpenContext(&context, HTTPC_METHOD_POST, url, 0);
//		printf("return from httpcOpenContext: %" PRIx32 "\n",ret);

//		ret = httpcSetSSLOpt(&context, SSLCOPT_DisableVerify);
//		printf("return from httpcSetSSLOpt: %" PRIx32 "\n",ret);

//		ret = httpcSetKeepAlive(&context, HTTPC_KEEPALIVE_ENABLED);
//		printf("return from httpcSetKeepAlive: %" PRIx32 "\n",ret);

		ret = httpcAddRequestHeaderField(&context, "User-Agent", "3dsLGremote 0.1.0");
//		printf("return from httpcAddRequestHeaderField: %" PRIx32 "\n",ret);

		ret = httpcAddRequestHeaderField(&context, "Content-Type", "application/atom+xml");
//		printf("return from httpcAddRequestHeaderField: %" PRIx32 "\n",ret);

		ret = httpcAddPostDataRaw(&context, (u32*)data, strlen(data));
//		printf("return from httpcAddPostDataRaw: %" PRIx32 "\n",ret);

		ret = httpcBeginRequest(&context);
		if(ret!=0){
			httpcCloseContext(&context);
			if(newurl!=NULL) free(newurl);
			return ret;
		}

		ret = httpcGetResponseStatusCode(&context, &statuscode);
		if(ret!=0){
			httpcCloseContext(&context);
			if(newurl!=NULL) free(newurl);
			return ret;
		}
//                printf("Status code $\n", statuscode);

	gfxSwapBuffers();

	httpcCloseContext(&context);
	free(buf);
	if (newurl!=NULL) free(newurl);

	return 0;
}

const size_t MAX_BODY_LEN = 512;
const size_t MAX_URL_LEN = 64;
int main(){
	Result ret=0;
	gfxInitDefault();
	httpcInit(4 * 1024 * 1024);
        char body[MAX_BODY_LEN];
        u32 kDown, kHeld;
        circlePosition pos;
        touchPosition touch;

        char *ip = "192.168.1.137";
        char *port = "8080";
        char url[MAX_URL_LEN];

	consoleInit(GFX_TOP, NULL);

        puts("Connecting to TV");
        puts("Circle Pad to move mouse\nL shoulder to click");
        puts("D-pad for directional movement");
        puts("X - Power off");
        puts("Y - Home");
        puts("A - Back");
        puts("B - OK");
        puts("Holding R shoulder");
        puts("D-up - Volume up");
        puts("D-down - Volume down");

        snprintf(url, MAX_URL_LEN, "http://%s:%s%s", ip, port, authURL);
	http_post(url, reqKey);

        snprintf(body, MAX_BODY_LEN, authKey, 428887);
        http_post(url, body);

        snprintf(url, MAX_URL_LEN, "http://%s:%s%s", ip, port, cmdURL);

	while (aptMainLoop()){
		gspWaitForVBlank();

		hidScanInput();
                hidCircleRead(&pos);
                hidTouchRead(&touch);
		kDown = hidKeysDown();
                kHeld = hidKeysHeld();

                if (touch.px > 0) {
                  snprintf(body, MAX_BODY_LEN, handleTouchMove, touch.px - 314/2, -234/2 + touch.py);
                  http_post(url, body);
                }
                 else if (kDown & KEY_TOUCH) {
                  http_post(url, handleTouchClick);
                }
                else if (pos.dx > 15 || pos.dx < -15 || pos.dy > 15 || pos.dy < -15) {
                  snprintf(body, MAX_BODY_LEN, handleTouchMove, pos.dx, -pos.dy);
                  http_post(url, body);
                }
                else if (kDown & KEY_L) {
                  http_post(url, handleTouchClick);
                }
                else if (kDown & KEY_DUP && kHeld & KEY_R) {
                  snprintf(body, MAX_BODY_LEN, handleKeyInput, 24);
                  http_post(url, body);
                }
                else if (kDown & KEY_DDOWN && kHeld & KEY_R) {
                  snprintf(body, MAX_BODY_LEN, handleKeyInput, 25);
                  http_post(url, body);
                }
                else if (kDown & KEY_DUP) {
                  snprintf(body, MAX_BODY_LEN, handleKeyInput, 12);
                  http_post(url, body);
                }
                else if (kDown & KEY_DDOWN) {
                  snprintf(body, MAX_BODY_LEN, handleKeyInput, 13);
                  http_post(url, body);
                }
                else if (kDown & KEY_DLEFT) {
                  snprintf(body, MAX_BODY_LEN, handleKeyInput, 14);
                  http_post(url, body);
                }
                else if (kDown & KEY_DRIGHT) {
                  snprintf(body, MAX_BODY_LEN, handleKeyInput, 15);
                  http_post(url, body);
                }
                else if (kDown & KEY_X) {
                  snprintf(body, MAX_BODY_LEN, handleKeyInput, 1);
                  http_post(url, body);
                }
                else if (kDown & KEY_B) {
                  snprintf(body, MAX_BODY_LEN, handleKeyInput, 20);
                  http_post(url, body);
                }
                else if (kDown & KEY_A) {
                  snprintf(body, MAX_BODY_LEN, handleKeyInput, 23);
                  http_post(url, body);
                }
                else if (kDown & KEY_Y) {
                  snprintf(body, MAX_BODY_LEN, handleKeyInput, 21);
                  http_post(url, body);
                }
		else if (kDown & KEY_START)
			break;

	}

	httpcExit();
	gfxExit();
	return 0;
}

