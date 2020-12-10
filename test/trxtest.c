//gcc -I. -Iminiz.h zip.c trxtest.c -o tst; ./tst

#include <zip.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#if defined(_MSC_VER) || defined(__MINGW64__) || defined(__MINGW32__)
#define MZ_FILE_STAT_STRUCT _stat
#define MZ_FILE_STAT _stat
#else
#define MZ_FILE_STAT_STRUCT stat
#define MZ_FILE_STAT stat
#endif

#define ZIPNAME "small.trx\0"

static void test_list_entries(void) {
  struct zip_t *zip = zip_open(ZIPNAME, 0, 'r');
  assert(zip != NULL);

  int i = 0, n = zip_total_entries(zip);
  for (; i < n; ++i) {
    assert(0 == zip_entry_openbyindex(zip, i));
    fprintf(stdout, "[%d]: %s", i, zip_entry_name(zip));
    if (zip_entry_isdir(zip)) {
      fprintf(stdout, " (DIR)");
    }
    fprintf(stdout, "\n");
    assert(0 == zip_entry_close(zip));
  }

  zip_close(zip);
}

int main(int argc, char *argv[]) {
  test_list_entries();

  fprintf(stdout, "ALL TEST SUCCESS!\n");

  return 0;
}
