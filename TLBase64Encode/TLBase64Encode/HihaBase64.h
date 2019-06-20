//
//  HihaBase64.h
//  HihaBase64
//
//  Created by 突突兔 on 6/17/19.
//  Copyright © 2019 突突兔. All rights reserved.
//

#ifndef HihaBase64_h
#define HihaBase64_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *HihaBase64_encode(const char *str);
char *HihaBase64_decode(const char *code);
void HihaBase64_free(char *ptr);

#endif /* HihaBase64_h */
