#pragma once
/*
Copyright  © 2024 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/


#ifdef OS_WINDOWS    // windows
#define WIN
typedef unsigned __int64  u64;
typedef __int64  s64;
#else   //linux
#define NOTWIN
#include <stdlib.h>
#include <cstdint>
typedef  uint64_t  u64;
typedef  int64_t  s64;
#endif


class GrayCodeGeneratorClass
{
public:
	GrayCodeGeneratorClass(): mask(0), state(0) {};
	~GrayCodeGeneratorClass() {};

	inline void Init(unsigned int _width, u64 FirstValue = 0) {
		
		if (0 < _width && _width < 65) {
			switch (_width)
			{
			case 64: mask = 0xFFFFFFFFFFFFFFFF;
				break;
			default: mask = ((u64)1) << _width;
				mask--;
				break;
			}

			state = (FirstValue & mask);
			/*
			   'state' is now initialized to
					 Firstvalue ^ [Firstvalue/2] ^  [Firstvalue/4] ^ [Firstvalue/8] ^.......
			   an infinite sum, where the terms eventurally become 0, so we can stop there
				(note:  [X] is the integer part of X )

			   The output :  state ^ (state >>1)  then becomes

					 Firstvalue ^ [Firstvalue/2] ^  [Firstvalue/4] ^ [Firstvalue/8] ^.......
				^                 [Firstvalue/2] ^  [Firstvalue/4] ^ [Firstvalue/8] ^.......
				where all terms except the first cancel..
			*/
			u64 temp = (FirstValue & mask) >> 1;
			while (temp) {
				state ^= temp; 
				temp = temp >> 1; 
			}

		}
		else { 
			mask = 0; 
			state = 0;
		}
	};

	/* 
	   the order 'state' is incremented  or decremented below is a choice. 
	   Not sure there is a 'right' way....
	*/
	inline u64 Next() { 
		u64 res = state ^ (state >> 1) ; 
		state = (state + 1) & mask; 
		return mask & res;
	};

	inline u64 Previous() { 
		if (state)  state = (state - 1) & mask;
		else 		state = mask;
		return mask & (state ^ (state >> 1));
	};

private:
	u64 state;
	u64 mask;
};
