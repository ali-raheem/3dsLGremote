#pragma once

Result http_post(const char* url, const char* data){
  Result ret;
  httpcContext context;
  char *newurl = NULL;
  u32 statuscode;

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
/*
  if(statuscode == 200) {
    puts("Command OK.");
  }else{
    puts("Command FAIL.");
  }
*/
  if(ret!=0){
    httpcCloseContext(&context);
    if(newurl!=NULL) free(newurl);
    return ret;
  }

//  gfxSwapBuffers();

  httpcCloseContext(&context);
  if (newurl!=NULL) free(newurl);

  return 0;
}
