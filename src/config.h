#pragma once

int parseConfig(const char*config, char *host, char *keyStr) {
  u32 ip[4];
  u32 port;
  u32 key;
  if (strlen(config) > 31) {
    return -1;
  }
  sscanf(config, "%u@%u.%u.%u.%u:%u", &key, &ip[0], &ip[1], &ip[2], &ip[3], &port);
  snprintf(keyStr, 7, "%06u", key);
  snprintf(host, 32, "%u.%u.%u.%u:%u", ip[0] % 256, ip[1] % 256, ip[2] % 256, ip[3] % 256, port % 65336);
  printf("Host: %s\nKey: %s\n", host, keyStr);
  return 0;
}

int readConfigFile(char *buf, size_t buf_len){
  FILE *fp;
  fp = fopen("lastTV", "r");
  if(fp != NULL) {
    fseek(fp, 0, SEEK_END);
    size_t len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (len < buf_len) {
      fread(buf, 1, 31, fp);
      fclose(fp);
     return 1;
    }
  }
  fclose(fp);
  return 0;
}

int saveConfigFile(char *host, char *key){
  FILE *fp;
  fp = fopen("lastTV", "w");
  char buf[32];
  snprintf(buf, 32, "%s@%s", key, host);
  fwrite(buf,strlen(buf), 1, fp);
  return 0;
}
