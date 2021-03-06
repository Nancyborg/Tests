/* 
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote prducts derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ROS_MBEDHARDWARE_H_
#define ROS_MBEDHARDWARE_H_

#include "mbed.h"
#include "MODSERIAL.h"

#ifndef ROSSERIAL_BAUDRATE
#define ROSSERIAL_BAUDRATE 115200
#endif

#ifndef ROSSERIAL_TX
#define ROSSERIAL_TX USBTX
#endif
#ifndef ROSSERIAL_RX
#define ROSSERIAL_RX USBRX
#endif

class MbedHardware {
public:
    MbedHardware()
            : iostream(ROSSERIAL_TX, ROSSERIAL_RX) {
        baud_ = ROSSERIAL_BAUDRATE;
        t.start();
    }

    void setBaud(int baud) {
        this->baud_= baud;
        iostream.baud(baud_);
    }

    int getBaud() {
        return baud_;
    }

    void init() {
        iostream.baud(baud_);
    }

    int read() {
        if (iostream.readable()) {
            return iostream.getc();
        } else {
            return -1;
        }
    }
    void write(uint8_t* data, int length) {
        for (int i = 0; i < length; i++)
            iostream.putc(data[i]);
    }

    unsigned long time() {
        return t.read_ms();
    }

protected:
    long baud_;
    MODSERIAL iostream;
    Timer t;
};


#endif /* ROS_MBEDHARDWARE_H_ */
