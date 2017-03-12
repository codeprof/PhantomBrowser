//SAFE SEARCH WHITELIST - CREATED 2017-03-12
#include <stdio.h>
#include <string.h>

static char* ss_whitelist[667];
static char* ss_whitelist2[667];
void init_safesearch_ignore_list(){
  static int isinitalized = 0;
  if (isinitalized == 0) {
  ss_whitelist[0] = (char*)"localhost";
  }
  isinitalized = 1;
}

int is_in_safesearch_ignore_list(char * host) {
  int i;
  for (i = 0; i < 667; i++) {
    if (strcasecmp(ss_whitelist[i], host) == 0) return 1;
    int host_len  = strlen(host);
    int item_len  = strlen(ss_whitelist2[i]);
    if (host_len > item_len) {
      if (strcasecmp(ss_whitelist2[i], host + (host_len - item_len)) == 0) return 1;
    }
  }
  return 0;
}