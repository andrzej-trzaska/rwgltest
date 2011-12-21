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

#include "Sound.h"

Sound::Sound(void) {
	buffer = alutCreateBufferHelloWorld();
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	init();
}

Sound::Sound(string filename) {
	buffer = alutCreateBufferFromFile(filename.c_str());
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	init();
}

void Sound::play(void) {
	alSourcei(source, AL_LOOPING, AL_FALSE);
	alSourcePlay(source);
}

void Sound::stop(void) {
	alSourceStop(source);
}

void Sound::loop(void) {
	alSourcei(source, AL_LOOPING, AL_TRUE);
	alSourcePlay(source);
}

void Sound::init(void) {
    for(ALuint i = 0;i < 3;i++){
        sourcePos[i] = 0;
        sourceVel[i] = 0;
    }
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
	alSourcefv(source, AL_POSITION, sourcePos);
    alSourcefv(source, AL_VELOCITY, sourceVel);
}

void Sound::setPosition(ALfloat pos[3]) {
	this->sourcePos[0] = pos[0];
	this->sourcePos[1] = pos[1];
	this->sourcePos[2] = pos[2];
	alSourcefv(source, AL_POSITION, sourcePos);
}

void Sound::setPosition(ALfloat x, ALfloat y, ALfloat z) {
	this->sourcePos[0] = x;
	this->sourcePos[1] = y;
	this->sourcePos[2] = z;
	alSourcefv(source, AL_POSITION, sourcePos);
}

Sound::~Sound(void) {

}

