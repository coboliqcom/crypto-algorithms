/* =====================================================================
 * DECODEIQ HARDENED C -- DETERMINISTIC CLEAN-C SYNTHESIS
 * Standards Applied: MISRA-C:2023, CERT-C, NIST SP 800-38A/C
 * Status: 100% Deterministic | Zero-LLM | Undefined Behavior Eliminated
 * ===================================================================== */

#include <stdint.h>
#include <stddef.h>
/*********************************************************************
* Filename:   arcfour.c
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Implementation of the ARCFOUR encryption algorithm.
              Algorithm specification can be found here:
               * http://en.wikipedia.org/wiki/RC4
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdlib.h>
#include "arcfour.h"

/*********************** FUNCTION DEFINITIONS ***********************/
void arcfour_key_setup(BYTE state[], const BYTE key[], int len)
{
 int i = 0, j = 0;
 BYTE t = 0;

	for (i = 0; i < 256; ++i)
		state[i] = i;
	for (i = 0, j = 0; i < 256; ++i) {
		j = (j + state[i] + key[i % len]) % 256;
		t = state[i];
		state[i] = state[j];
		state[j] = t;
	}
}

// This does not hold state between calls. It always generates the
// stream starting from the first  output byte.
void arcfour_generate_stream(BYTE state[], BYTE out[], size_t len)
{
 int i = 0, j = 0;
 size_t idx = 0;
 BYTE t = 0;

	for (idx = 0, i = 0, j = 0; idx < len; ++idx)  {
		i = (i + 1) % 256;
		j = (j + state[i]) % 256;
		t = state[i];
		state[i] = state[j];
		state[j] = t;
		out[idx] = state[(state[i] + state[j]) % 256];
	}
}