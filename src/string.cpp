/*
 * string.cpp
 *
 *  Created on: May 3, 2016
 *      Author: chris
 */

#include <string.h>
#include <memory.h>
#include <feta.h>

namespace feta {

Size stringlength(String str) {
	return stringLength(str);
}
Size stringLength(String str) {
	const strchar* char_ptr;
	const unsigned long int* longword_ptr;
	unsigned long int longword, himagic, lomagic;

	/* Handle the first few characters by reading one character at a time.
	 Do this until CHAR_PTR is aligned on a longword boundary.  */
	for (char_ptr = str;
			((unsigned long int) char_ptr & (sizeof(longword) - 1)) != 0;
			++char_ptr)
		if (*char_ptr == '\0')
			return char_ptr - str;

	/* All these elucidatory comments refer to 4-byte longwords,
	 but the theory applies equally well to 8-byte longwords.  */

	longword_ptr = (unsigned long int*) char_ptr;

	/* Bits 31, 24, 16, and 8 of this number are zero.  Call these bits
	 the "holes."  Note that there is a hole just to the left of
	 each byte, with an extra at the end:

	 bits:  01111110 11111110 11111110 11111111
	 bytes: AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD

	 The 1-bits make sure that carries propagate to the next 0-bit.
	 The 0-bits provide holes for carries to fall into.  */
	himagic = 0x80808080L;
	lomagic = 0x01010101L;
	if (sizeof(longword) > 4) {
		/* 64-bit version of the magic.  */
		/* Do the shift in two steps to avoid a warning if long has 32 bits.  */
		himagic = ((himagic << 16) << 16) | himagic;
		lomagic = ((lomagic << 16) << 16) | lomagic;
	}
	if (sizeof(longword) > 8) {
		SNH;
	}

	/* Instead of the traditional loop which tests each character,
	 we will test a longword at a time.  The tricky part is testing
	 if *any of the four* bytes in the longword in question are zero.  */
	for (;;) {
		/* We tentatively exit the loop if adding MAGIC_BITS to
		 LONGWORD fails to change any of the hole bits of LONGWORD.

		 1) Is this safe?  Will it catch all the zero bytes?
		 Suppose there is a byte with all zeros.  Any carry bits
		 propagating from its left will fall into the hole at its
		 least significant bit and stop.  Since there will be no
		 carry from its most significant bit, the LSB of the
		 byte to the left will be unchanged, and the zero will be
		 detected.

		 2) Is this worthwhile?  Will it ignore everything except
		 zero bytes?  Suppose every byte of LONGWORD has a bit set
		 somewhere.  There will be a carry into bit 8.  If bit 8
		 is set, this will carry into bit 16.  If bit 8 is clear,
		 one of bits 9-15 must be set, so there will be a carry
		 into bit 16.  Similarly, there will be a carry into bit
		 24.  If one of bits 24-30 is set, there will be a carry
		 into bit 31, so all of the hole bits will be changed.

		 The one misfire occurs when bits 24-30 are clear and bit
		 31 is set; in this case, the hole at bit 31 is not
		 changed.  If we had access to the processor carry flag,
		 we could close this loophole by putting the fourth hole
		 at bit 32!

		 So it ignores everything except 128's, when they're aligned
		 properly.  */

		longword = *longword_ptr++;

		if (
#if 0
		/* Add MAGIC_BITS to LONGWORD.  */
		(((longword + magic_bits)

						/* Set those bits that were unchanged by the addition.  */
						^ ~longword)

				/* Look at only the hole bits.  If any of the hole bits
				 are unchanged, most likely one of the bytes was a
				 zero.  */
				& ~magic_bits)
#else
		((longword - lomagic) & himagic)
#endif
				!= 0) {
			/* Which of the bytes was the zero?  If none of them were, it was
			 a misfire; continue the search.  */

			const strchar* cp = (const strchar*) (longword_ptr - 1);

			if (cp[0] == 0)
				return cp - str;
			if (cp[1] == 0)
				return cp - str + 1;
			if (cp[2] == 0)
				return cp - str + 2;
			if (cp[3] == 0)
				return cp - str + 3;
			if (sizeof(longword) > 4) {
				if (cp[4] == 0)
					return cp - str + 4;
				if (cp[5] == 0)
					return cp - str + 5;
				if (cp[6] == 0)
					return cp - str + 6;
				if (cp[7] == 0)
					return cp - str + 7;
			}
		}
	}

	SNH;
	return NULL;
}

Boolean strequ(String one, String two) {
	return stringEquals(one, two);
}
Boolean stringEquals(String one, String two) {
	for (uinteger i = 0; true; i++) {
		char a = one[i];
		char b = two[i];

		// check equality (also checks null termination)
		if (a != b) {
			return false;
		}

		// if we've hit the end, all previous checks have passed, return true
		if (a == '\0') {
			return true;
		}
	}

	SNH;
	return false;
}

String charListToString(List<strchar>* list) {
	// end string
	strchar* str = (strchar*) create((list->size() + 1) * sizeof(strchar));

	// copy the list of characters to an actual string
	Iterator<strchar> stringIterator = list->iterator();
	uinteger strIndex = 0;
	while (stringIterator.hasNext()) {
		str[strIndex] = stringIterator.next();
		strIndex++;
	}
	str[strIndex] = '\0'; // null terminate

	// return
	return str;
}

String substring(String string, uinteger start, uinteger end) {
	strchar* newString = (strchar*) create(sizeof(strchar) * (end - start) + 1);

	for (uinteger i = start; i < end; i++) {
		newString[i - start] = string[i];
	}

	newString[end - start] = '\0';

	return newString;
}

Boolean stringStartsWith(String string, String beginning) {
	for (uinteger i = 0; true; i++) {
		strchar s = string[i];
		strchar b = beginning[i];

		// if we've found the end of beginning, all previous checks have passed
		if (b == '\0') {
			return true;
		}

		// if it's the end of the string, beginning is longer than the string
		if (s == '\0') {
			return false;
		}

		// verify equality
		if (s != b) {
			return false;
		}
	}

	SNH;
	return false;
}

static Strchar returnedString[10];
String toString(int value, int base) {
	strchar* str = returnedString;
	strchar* rc;
	strchar* ptr;
	strchar* low;
	// Check for supported base.
	if (base < 2 || base > 36) {
		*str = '\0';
		return str;
	}
	rc = ptr = str;
	// Set '-' for negative decimals.
	if (value < 0 && base == 10) {
		*ptr++ = '-';
	}
	// Remember where the numbers start.
	low = ptr;
	// The actual conversion.
	do {
		// Modulo is negative for negative value. This trick makes abs() unnecessary.
		*ptr++ =
				"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35
						+ value % base];
		value /= base;
	} while (value);
	// Terminating the string.
	*ptr-- = '\0';
	// Invert the numbers.
	while (low < ptr) {
		strchar tmp = *low;
		*low++ = *ptr;
		*ptr-- = tmp;
	}
	return rc;
}

String concat(String one, String two) {
	size oneSize = stringlength(one);
	size twoSize = stringlength(two);
	strchar* newString = (strchar*) create(
			(size) ((oneSize + twoSize) * sizeof(strchar) + 1));

	for (uinteger i = 0; i < oneSize + twoSize; i++) {
		if (i < oneSize) {
			newString[i] = one[i];
		} else {
			newString[i] = two[i - oneSize];
		}
	}

	return newString;
}

String operator ""_H(const Strchar* arr, size length) {
	// create
	strchar* str = (strchar*) create(length * sizeof(strchar) + 1);

	// copy
	for (uinteger i = 0; i < length; i++) {
		str[i] = arr[i];
	}

	// null terminate
	((uint8*) str)[length * sizeof(strchar)] = 0;

	// return
	return (String) str;
}

}
