/*
Copyright  © 2024 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/


// GrayCodeGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "GrayCodeGenerator.h"


#define WIDTH 8

void putBit(int w, u64 x)
{
    if (w>1)
    {
        putBit(w - 1, x >> 1);
    }
    printf("%c", x & 1 ? '1' : '0');

}

#ifdef OS_WINDOWS
#define FSTRING "I64"
#else
#define FSTRING "l"
#endif

int main()
{
    GrayCodeGeneratorClass GC;

    GC.Init(WIDTH, 0x7FFFFFFAA);

    u64 o= 0, oold= 0;
    for (u64 i = 0; i <= (((u64) 1) << WIDTH); i++) {
        o = GC.Next();
        printf(" %8" FSTRING "d  %8" FSTRING "X  ",i, o );
        putBit(WIDTH, o);
        printf("  ");
        putBit(WIDTH, o^oold);
        oold = o;
        printf("\n");
    }
    printf("\n");
    printf("\n");

    GC.Init(WIDTH, 0x7FFFFFFAA);
    for (u64 i = 0; i <= (((u64)1) << WIDTH); i++) {
        o = GC.Previous();
        printf(" %8" FSTRING "d  %8" FSTRING "X  ", i, o);
        putBit(WIDTH, o);
        printf("  ");
        putBit(WIDTH, o ^ oold);
        oold = o;
        printf("\n");
    }
    printf("\n");
    printf("\n");


    GC.Init(WIDTH, 0x7FFFFFFAA);

    for (u64 i = 0; i <= (((u64)1) << WIDTH); i++) {
        o = GC.Next();
        printf(" %8" FSTRING "d  %8" FSTRING "X  ", i, o);
        putBit(WIDTH, o);
        printf("  ");
        putBit(WIDTH, o ^ oold);
        oold = o;
        printf("\n");
        o = GC.Previous();
        printf(" %8" FSTRING "d  %8" FSTRING "X  ", i, o);
        putBit(WIDTH, o);
        printf("  ");
        putBit(WIDTH, o ^ oold);
        oold = o;
        printf("\n");
    }
    printf("\n");
    printf("\n");

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
