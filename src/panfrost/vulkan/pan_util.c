/*
 * Copyright © 2015 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "pan_private.h"

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/u_math.h"
#include "vk_enum_to_str.h"

/* TODO: Add Android support to pan_log funcs */

/** Log an error message.  */
void pan_printflike(1, 2) pan_loge(const char *format, ...)
{
   va_list va;

   va_start(va, format);
   pan_loge_v(format, va);
   va_end(va);
}

/** \see pan_loge() */
void
pan_loge_v(const char *format, va_list va)
{
   fprintf(stderr, "vk: error: ");
   vfprintf(stderr, format, va);
   fprintf(stderr, "\n");
}

/** Log an error message.  */
void pan_printflike(1, 2) pan_logi(const char *format, ...)
{
   va_list va;

   va_start(va, format);
   pan_logi_v(format, va);
   va_end(va);
}

/** \see pan_logi() */
void
pan_logi_v(const char *format, va_list va)
{
   fprintf(stderr, "tu: info: ");
   vfprintf(stderr, format, va);
   fprintf(stderr, "\n");
}

void pan_printflike(3, 4)
   __pan_finishme(const char *file, int line, const char *format, ...)
{
   va_list ap;
   char buffer[256];

   va_start(ap, format);
   vsnprintf(buffer, sizeof(buffer), format, ap);
   va_end(ap);

   fprintf(stderr, "%s:%d: FINISHME: %s\n", file, line, buffer);
}

VkResult
__vk_errorf(struct pan_instance *instance,
            VkResult error,
            const char *file,
            int line,
            const char *format,
            ...)
{
   va_list ap;
   char buffer[256];

   const char *error_str = vk_Result_to_str(error);

#ifndef DEBUG
   return error;
#endif

   if (format) {
      va_start(ap, format);
      vsnprintf(buffer, sizeof(buffer), format, ap);
      va_end(ap);

      fprintf(stderr, "%s:%d: %s (%s)\n", file, line, buffer, error_str);
   } else {
      fprintf(stderr, "%s:%d: %s\n", file, line, error_str);
   }

   return error;
}
