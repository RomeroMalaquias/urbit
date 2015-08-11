
/*============================================================================

This C source file is part of the SoftFloat IEEE Floating-Point Arithmetic
Package, Release 3, by John R. Hauser.

Copyright 2011, 2012, 2013, 2014 The Regents of the University of California
(Regents).  All Rights Reserved.  Redistribution and use in source and binary
forms, with or without modification, are permitted provided that the following
conditions are met:

Redistributions of source code must retain the above copyright notice,
this list of conditions, and the following two paragraphs of disclaimer.
Redistributions in binary form must reproduce the above copyright notice,
this list of conditions, and the following two paragraphs of disclaimer in the
documentation and/or other materials provided with the distribution.  Neither
the name of the Regents nor the names of its contributors may be used to
endorse or promote products derived from this software without specific prior
written permission.

IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
HEREUNDER IS PROVIDED "AS IS".  REGENTS HAS NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

=============================================================================*/

#include <stdint.h>
#include "platform.h"
#include "internals.h"

struct exp32_sig128
 softfloat_normSubnormalF128Sig( uint_fast64_t sig64, uint_fast64_t sig0 )
{
    int_fast8_t shiftCount;
    struct exp32_sig128 z;

    if ( ! sig64 ) {
        shiftCount = softfloat_countLeadingZeros64( sig0 ) - 15;
        z.exp = -63 - shiftCount;
        if ( shiftCount < 0 ) {
            z.sig.v64 = sig0>>-shiftCount;
            z.sig.v0  = sig0<<(shiftCount & 63);
        } else {
            z.sig.v64 = sig0<<shiftCount;
            z.sig.v0  = 0;
        }
    } else {
        shiftCount = softfloat_countLeadingZeros64( sig64 ) - 15;
        z.exp = 1 - shiftCount;
        z.sig = softfloat_shortShiftLeft128( sig64, sig0, shiftCount );
    }
    return z;

}
