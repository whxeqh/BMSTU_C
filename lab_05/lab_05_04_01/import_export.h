#ifndef IMPORT_EXPORT_H
#define IMPORT_EXPORT_H

#include <stdio.h>
#include "errors.h"

int import(FILE *file_txt, FILE *file_bin);
int export(FILE *file_bin, FILE *file_txt);

#endif
