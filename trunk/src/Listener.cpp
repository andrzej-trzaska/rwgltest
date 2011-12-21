/* Copyright (C) 2011 Andrzej Trzaska
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Listener.h"

Listener::Listener(void) {
	for(ALuint i = 0; i < 3; i++) {
		listenerPos[i] = 0;
		listenerOri[i] = 0;
		listenerVel[i] = 0;
	}

    alListenerfv(AL_POSITION, listenerPos);
    alListenerfv(AL_VELOCITY, listenerVel);
    alListenerfv(AL_ORIENTATION, listenerOri);
}

void Listener::setPos(ALfloat pos[3]) {
	this->listenerPos[0] = pos[0];
	this->listenerPos[1] = pos[1];
	this->listenerPos[2] = pos[2];
    alListenerfv(AL_POSITION, listenerPos);
}

void Listener::setPos(ALfloat x, ALfloat y, ALfloat z) {
	this->listenerPos[0] = x;
	this->listenerPos[1] = y;
	this->listenerPos[2] = z;
    alListenerfv(AL_POSITION, listenerPos);
}

Listener::~Listener(void) {
}

