#include "sysutil.h"
#include <stdlib.h>
#include <string.h>

/*=========================================================================*
 *				env_prefix				   *
 *=========================================================================*/
int env_prefix(const char *env, const char *prefix)
{
/* An environment setting may be prefixed by a word, usually "pci".  
 * - env: environment variable to inspect
 * - prefix: prefix to test for
 * Return TRUE if a given prefix is used.
 */
  char value[EP_BUF_SIZE];
  char punct[] = ":,;.";
  int s;
  size_t n;

  if ((s = env_get_param(env, value, sizeof(value))) != 0) {
  	if (s != ESRCH)		/* only error allowed */
  	printf("WARNING: env_get_param() failed in env_prefix(): %d\n", s);
  	return FALSE;
  }
  n = strlen(prefix);
  return(strncmp(value, prefix, n) == 0
	&& strchr(punct, value[n]) != NULL);
}
