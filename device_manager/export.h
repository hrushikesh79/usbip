/* SPDX-License-Identifier: GPL-2.0-only
*
* header file for export.c 
*
* Copyright (C) 2023 Samsung Electronics Co., Ltd.
*
* Author: Hrushikesh Reddy Mudhireddy  (h.mudhireddy)
*/





#ifndef EXPORT_H
#define EXPORT_H

/* Function declarations */

#include<stdio.h>
#include<stdlib.h>
#include <string.h>


int bind(const char* busId);
void unbind(const char* busId);
#endif /* EXPORT */
